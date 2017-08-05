#include <yaooc/json.h>

void json_value_default_ctor(pointer p)
{
  json_value_pointer this=p;
  this->type_=JSON_UNDEFINED;
  this->real_=0;
}

void json_value_dtor(pointer p)
{
  json_value_pointer this=p;
  M(this,virtual_destructor);
}

void json_value_copy_ctor(pointer d,const_pointer s)
{
  json_value_pointer dst=d;
  M(dst,virtual_copy_ctor,s);
}

void json_value_assign(pointer d,const_pointer s)
{
  json_value_pointer dst=d;
  json_value_const_pointer src=s;
  M(dst,virtual_assign,src);
}

bool json_value_less_than_compare(const_pointer p1,const_pointer p2)
{
  json_value_const_pointer v1=p1;
  return M(v1,virtual_less_than_compare,p2);
}

/*
  Used for NULL, BOOL, INTEGER, and REAL
*/
void json_value_virtual_destructor(pointer p)
{
  json_value_pointer this=p;
  M(this,clear);
  this->real_=0; // effectively sets all union values to zero
}

void json_value_virtual_copy_ctor(pointer p,const_pointer s)
{
  /* this should never happen */
  puts("Aborting in virtual copy ctor");
  abort();
}

void json_value_virtual_assign(pointer p,const_pointer s)
{
  json_value_pointer dst=p;
  json_value_const_pointer src=s;
  if(dst->type_ != src->type_) { /* should never be equal but just in case */
    /* use virtual table of src to assign value */
    src->class_table_->virtual_assign(dst,src);
  }
}

bool json_value_virtual_less_than_compare(const_pointer p,const_pointer p2)
{
  abort();
  return false;
}

json_type_t json_value_type(const_pointer p)
{
  return ((json_value_const_pointer)p)->type_;
}

/*
  Should never get the base class json_value.
*/
int json_value_print_to_string(const_pointer p,char * str,int n)
{
  abort();
  return 0;
}

/*
  Used for UNDEFINED, NULL, BOOL, INTEGER, and REAL
*/
void json_value_clear(pointer p)
{
  json_value_pointer this=p;
  this->real_=0;
}

ISA_IMPLEMENTATION(json_value,yaooc_object)

void json_value_swap(pointer p,pointer o)
{
  swap_object(p,o,sizeof(json_value_t));
/*  json_value_pointer this=p;
  json_value_pointer other=o;
  SWAP(json_type_t,this->type_,other->type_);
  char temp[sizeof(json_data_t)];
  memcpy (temp,&this->real_,sizeof(json_data_t));
  memcpy (&this->real_,&other->real_,sizeof(json_data_t));
  memcpy (&other->real_,temp,sizeof(json_data_t));*/
}

json_value_class_members_t json_value_class_members = {
  {
    json_value_isa,
    json_value_is_descendent,
    json_value_swap
  },
  (void (*)(pointer)) json_value_virtual_destructor,
  (void (*)(pointer,const_pointer)) json_value_virtual_copy_ctor,
  (void (*)(pointer,const_pointer)) json_value_virtual_assign,
  (bool (*)(const_pointer,const_pointer)) json_value_virtual_less_than_compare,
  (json_type_t (*)(const_pointer)) json_value_type,
  (int (*)(const_pointer,char *,int)) json_value_print_to_string,
  (void (*)(pointer)) json_value_clear,
};

DEFINE_TYPE_INFO(json_value,json_value_default_ctor,json_value_dtor,json_value_copy_ctor,json_value_assign,json_value_less_than_compare,&json_value_class_members,yaooc_object)

void json_null_default_ctor(pointer p)
{
  ((json_null_pointer)p)->type_=JSON_NULL;
}

void json_null_virtual_copy_ctor(pointer d,const_pointer s)
{
  json_null_pointer this=d;
  this->type_=JSON_NULL;
}

void json_null_virtual_assign(pointer p,const_pointer s)
{
  /* Only allow assigning from a json_value (UNDEFINED) or a json_null */
  json_null_pointer dst=p;
  json_null_const_pointer src=s;
  if(dst->type_ == JSON_UNDEFINED)
    /*
      Normally need to destruct/construct dst but UNDEFINED json value doesn't have any resources to reclaim
    */
    newp(dst,json_null);
  if(dst->type_!= JSON_NULL) {
    fprintf(stderr,"Invalid json assignment from %d to %d",src->type_,dst->type_);
    abort();
  }
}

bool json_null_virtual_less_than_compare(const_pointer p1,const_pointer p2)
{
  return false;
}

int json_null_print_to_string(const_pointer p,char * str,int n)
{
  int ret=0;
  if(n>4) {
    ret=4;
    snprintf(str,n,"null");
  }
  return ret;
}
ISA_IMPLEMENTATION(json_null,json_value)

json_null_class_members_t json_null_class_members = {
  {
    {
      json_null_isa,
      json_null_is_descendent,
      json_value_swap
    },
    (void (*)(pointer)) json_value_virtual_destructor,
    (void (*)(pointer,const_pointer)) json_null_virtual_copy_ctor,
    (void (*)(pointer,const_pointer)) json_null_virtual_assign,
    (bool (*)(const_pointer,const_pointer)) json_null_virtual_less_than_compare,
    (json_type_t (*)(const_pointer)) json_value_type,
    (int (*)(const_pointer,char *,int)) json_null_print_to_string,
    (void (*)(pointer)) json_value_clear
  }
};

DEFINE_TYPE_INFO(json_null,json_null_default_ctor,NULL,NULL,NULL,NULL,&json_null_class_members,json_value)

void json_bool_default_ctor(pointer p)
{
  ((json_bool_pointer)p)->type_=JSON_BOOL;
  ((json_bool_pointer)p)->bool_=false;
}

void json_bool_ctor_bool(pointer p,va_list args)
{
  ((json_bool_pointer)p)->type_=JSON_BOOL;
  json_bool_set(p,va_arg(args,int));
};

void json_bool_virtual_copy_ctor(pointer d,const_pointer s)
{
  json_null_pointer dst=d;
  json_null_const_pointer src=s;
  dst->type_=src->type_;
  dst->bool_=src->bool_;
}

void json_bool_virtual_assign(pointer d,const_pointer s)
{
  json_null_pointer dst=d;
  json_null_const_pointer src=s;
  /* Only UNDEFINED and BOOL allowed */
  if(dst->type_ == JSON_UNDEFINED) {
    newp(dst,json_bool);
  }
  if(dst->type_ == JSON_BOOL)
    dst->bool_=src->bool_;
  else {
    fprintf(stderr,"Invalid conversion to json_bool\n");
    abort();
  }
}

bool json_bool_virtual_less_than_compare(const_pointer p1,const_pointer p2)
{
  json_bool_const_pointer bp1=p1;
  json_bool_const_pointer bp2=p2;
  return (int)bp1->bool_ < (int) bp2->bool_;
}

int json_bool_print_to_string(const_pointer p,char * str,int n)
{
  json_bool_const_pointer this=p;
  int ret=0;
  if(n>5) {
    ret=snprintf(str,n,"%s",this->bool_?"true":"false");
  }
  return ret;
}

bool json_bool_get(const_pointer p)
{
  return ((json_bool_const_pointer)p)->bool_;
}

void json_bool_set(pointer p,bool value)
{
  ((json_bool_pointer)p)->bool_=value;
}

ISA_IMPLEMENTATION(json_bool,json_value)

json_bool_class_members_t json_bool_class_members = {
  {
    {
      json_bool_isa,
      json_bool_is_descendent,
      json_value_swap
    },
    (void (*)(pointer)) json_value_virtual_destructor,
    (void (*)(pointer,const_pointer)) json_bool_virtual_copy_ctor,
    (void (*)(pointer,const_pointer)) json_bool_virtual_assign,
    (bool (*)(const_pointer,const_pointer)) json_bool_virtual_less_than_compare,
    (json_type_t (*)(const_pointer)) json_value_type,
    (int (*)(const_pointer,char *,int)) json_bool_print_to_string,
    (void (*)(pointer)) json_value_clear
  },
  (bool (*)(const_pointer)) json_bool_get,
  (void (*)(pointer,bool)) json_bool_set
};

DEFINE_TYPE_INFO(json_bool,json_bool_default_ctor,NULL,NULL,NULL,NULL,&json_bool_class_members,json_value)

void json_integer_default_ctor(pointer p)
{
  ((json_integer_pointer)p)->type_=JSON_INTEGER;
  ((json_integer_pointer)p)->real_=0;
}

void json_integer_virtual_copy_ctor(pointer d,const_pointer s)
{
  json_integer_pointer dst=d;
  json_integer_const_pointer src=s;
  dst->type_=src->type_;
  dst->int_=src->int_;
}

void json_integer_virtual_assign(pointer d,const_pointer s)
{
  json_integer_pointer dst=d;
  json_integer_const_pointer src=s;
  if(dst->type_ == JSON_UNDEFINED)
    newp(dst,json_integer);
  if(dst->type_ == JSON_INTEGER) {
    dst->int_=src->int_;
  } else {
    fprintf(stderr,"Invalid assignment to json_integer\n");
    abort();
  }
}

bool json_integer_virtual_less_than_compare(const_pointer p1,const_pointer p2)
{
  json_integer_const_pointer ip1=p1;
  json_integer_const_pointer ip2=p2;
  return ip1->int_ < ip2->int_;
}

int json_integer_print_to_string(const_pointer p,char * str,int n)
{
  json_integer_const_pointer this=p;
  int ret=snprintf(str,n,"%zu",this->int_);
  if(ret>n)
    ret=n;
  return ret;
}

void json_integer_clear(pointer p)
{
  json_integer_pointer this=p;
  this->int_=0;
}

int64_t json_integer_get(const_pointer p)
{
  return ((json_integer_const_pointer)p)->int_;
}

void json_integer_set(pointer p,int64_t value)
{
  ((json_integer_pointer)p)->int_=value;
}

void json_integer_ctor_int(pointer p,va_list args)
{
  ((json_integer_pointer)p)->type_=JSON_INTEGER;
  json_integer_set(p,va_arg(args,int64_t));
};

ISA_IMPLEMENTATION(json_integer,json_value)

json_integer_class_members_t json_integer_class_members = {
  {
    {
      json_integer_isa,
      json_integer_is_descendent,
      json_value_swap
    },
    (void (*)(pointer)) json_value_virtual_destructor,
    (void (*)(pointer,const_pointer)) json_integer_virtual_copy_ctor,
    (void (*)(pointer,const_pointer)) json_integer_virtual_assign,
    (bool (*)(const_pointer,const_pointer)) json_integer_virtual_less_than_compare,
    (json_type_t (*)(const_pointer)) json_value_type,
    (int (*)(const_pointer,char *,int)) json_integer_print_to_string,
    (void (*)(pointer)) json_integer_clear,
  },
  (int64_t (*)(const_pointer)) json_integer_get,
  (void (*)(pointer,int64_t)) json_integer_set,
};

DEFINE_TYPE_INFO(json_integer,json_integer_default_ctor,NULL,NULL,NULL,NULL,&json_integer_class_members,json_value)

void json_real_default_ctor(pointer p)
{
  ((json_real_pointer)p)->type_=JSON_REAL;
  ((json_real_pointer)p)->real_=0;
}

void json_real_virtual_copy_ctor(pointer d,const_pointer s)
{
  json_real_pointer dst=d;
  json_real_const_pointer src=s;
  dst->type_=src->type_;
  dst->real_=src->real_;
}

void json_real_virtual_assign(pointer d,const_pointer s)
{
  json_real_pointer dst=d;
  json_real_const_pointer src=s;
  if(dst->type_ == JSON_UNDEFINED)
    newp(dst,json_real);
  if(dst->type_ == JSON_REAL) {
    dst->real_=src->real_;
  } else {
    fprintf(stderr,"Invalid assignment to json_real\n");
    abort();
  }
}

bool json_real_virtual_less_than_compare(const_pointer p1,const_pointer p2)
{
  return ((json_real_const_pointer)p1)->real_ < ((json_real_const_pointer)p2)->real_;
}

int json_real_print_to_string(const_pointer p,char * str,int n)
{
  json_real_const_pointer this=p;
  int ret=snprintf(str,n,"%lg",this->real_);
  if(ret>n)
    ret=n;
  return ret;
}

void json_real_clear(pointer p)
{
  json_real_pointer this=p;
  this->real_=0;
}


double json_real_get(const_pointer p)
{
  json_real_const_pointer this=p;
  return this->real_;
}

void json_real_set(pointer p,double value)
{
  ((json_real_pointer)p)->real_=value;
}

void json_real_ctor_real(pointer p,va_list args)
{
  json_real_pointer this=p;
  this->type_=JSON_REAL;
  json_real_set(this,va_arg(args,double));
};

ISA_IMPLEMENTATION(json_real,json_value)

json_real_class_members_t json_real_class_members = {
  {
    {
      json_real_isa,
      json_real_is_descendent,
      json_value_swap
    },
    (void (*)(pointer)) json_value_virtual_destructor,
    (void (*)(pointer,const_pointer)) json_real_virtual_copy_ctor,
    (void (*)(pointer,const_pointer)) json_real_virtual_assign,
    (bool (*)(const_pointer,const_pointer)) json_real_virtual_less_than_compare,
    (json_type_t (*)(const_pointer)) json_value_type,
    (int (*)(const_pointer,char *,int)) json_real_print_to_string,
    (void (*)(pointer)) json_real_clear,
  },
  (double (*)(const_pointer)) json_real_get,
  (void (*)(pointer,double)) json_real_set,
};

DEFINE_TYPE_INFO(json_real,json_real_default_ctor,NULL,NULL,NULL,NULL,&json_real_class_members,json_value)

void json_string_default_ctor(pointer p)
{
  ((json_string_pointer)p)->type_=JSON_STRING;
  ((json_string_pointer)p)->string_=NULL;
}

void json_string_virtual_copy_ctor(pointer d,const_pointer s)
{
  json_string_default_ctor(d);
  json_string_virtual_assign(d,s);
}

void json_string_virtual_assign(pointer d,const_pointer s)
{
  json_string_pointer dst=d;
  json_string_const_pointer src=s;
  if(dst->type_ == JSON_UNDEFINED)
    newp(dst,json_string);
  if(dst->type_ == JSON_STRING) {
    M(dst,clear);
    if(src->string_)
      dst->string_=STRDUP(src->string_);
  } else {
    fprintf(stderr,"Invalid assignment to json_string\n");
    abort();
  }
}

bool json_string_virtual_less_than_compare(const_pointer p1,const_pointer p2)
{
  return strcmp(((json_string_const_pointer)p1)->string_,((json_string_const_pointer)p2)->string_) < 0;
}

int json_string_print_to_string(const_pointer p,char * str,int n)
{
  json_string_const_pointer this=p;
  int ret=snprintf(str,n,"\"%s\"",this->string_?this->string_:"");
  if(ret > n)
    ret=n;
  return ret;
}

void json_string_clear(pointer p)
{
  json_string_pointer this=p;
  if(this->string_) {
    FREE(this->string_);
    this->string_=NULL;
  }
}

const char * json_string_get(const_pointer p)
{
  json_string_const_pointer this=p;
  return this->string_;
}

void json_string_set(pointer p,const char * str)
{
  json_string_pointer this=p;
  json_string_clear(this);
  if(str)
    this->string_=STRDUP(str);
}

void json_string_ctor_ccs(pointer p,va_list args)
{
  json_string_default_ctor(p);
  json_string_set(p,va_arg(args,const char *));
};

ISA_IMPLEMENTATION(json_string,json_value)

json_string_class_members_t json_string_class_members = {
  {
    {
      json_string_isa,
      json_string_is_descendent,
      json_value_swap
    },
    (void (*)(pointer)) json_value_virtual_destructor,
    (void (*)(pointer,const_pointer)) json_string_virtual_copy_ctor,
    (void (*)(pointer,const_pointer)) json_string_virtual_assign,
    (bool (*)(const_pointer,const_pointer)) json_string_virtual_less_than_compare,
    (json_type_t (*)(const_pointer)) json_value_type,
    (int (*)(const_pointer,char *,int)) json_string_print_to_string,
    (void (*)(pointer)) json_string_clear,
  },
  (const char * (*)(const_pointer)) json_string_get,
  (void (*)(pointer,const char *)) json_string_set,
};

DEFINE_TYPE_INFO(json_string,json_string_default_ctor,NULL,NULL,NULL,NULL,&json_string_class_members,json_value)

VECTOR_IMPLEMENTATION(json_value)

void json_array_default_ctor(pointer p)
{
  json_array_pointer this=p;
  this->type_=JSON_ARRAY;
  this->array_=new(json_value_vector);
}

void json_array_virtual_destructor(pointer p)
{
  json_value_pointer this=p;
  delete(this->array_);
}

void json_array_virtual_copy_ctor(pointer d,const_pointer s)
{
  json_array_default_ctor(d);
  json_array_virtual_assign(d,s);
}

void json_array_virtual_assign(pointer d,const_pointer s)
{
  json_array_pointer dst=d;
  json_array_const_pointer src=s;
  if(dst->type_ == JSON_UNDEFINED)
    newp(dst,json_array);
  if(dst->type_ == JSON_ARRAY) {
    real_assign_static(dst->array_,src->array_,json_value_vector_ti);
  } else {
    fprintf(stderr,"Invalid assignment to json_array\n");
    abort();
  }
}

bool json_array_virtual_less_than_compare(const_pointer p1,const_pointer p2)
{
  return false;
}

int json_array_print_to_string(const_pointer p,char * str,int remaining)
{
  int n=0;
  if(remaining > 2) {
    json_array_const_pointer this=p;
    *str='['; n++; remaining--; str++;
    if(M(this->array_,size)>0) {
      json_array_const_iterator ia;
      int np;
      for(ia=M(this,cbegin);ia!=M(this,cend);ia++) {
        np=M(ia,print_to_string,str,remaining);
        str+=np;
        *str=','; n+=np+1; remaining-=np+1; str++;
      }
      str--; n--; remaining++; /* remove last comma */
    }
    *str=']'; n++;
    *(str+1)=0;
  }
  return n;
}

void json_array_clear(pointer p)
{
  json_array_pointer this=p;
  M(this->array_,clear);
}


void json_array_add(pointer p,const_pointer value)
{
  json_array_pointer this=p;
  M(this->array_,push_back,value);
}

json_value_pointer json_array_at(pointer p,yaooc_size_type i)
{
  json_array_pointer this=p;
  return M(this->array_,at,i);
}

yaooc_size_type json_array_size(const_pointer p)
{
  json_array_const_pointer this=p;
  return M(this->array_,size);
}

json_array_iterator json_array_begin(pointer p)
{
  json_array_pointer this=p;
  return M(this->array_,begin);
}

json_array_iterator json_array_end(pointer p)
{
  json_array_pointer this=p;
  return M(this->array_,end);
}

ISA_IMPLEMENTATION(json_array,json_value)

json_array_class_members_t json_array_class_members = {
  {
    {
      json_array_isa,
      json_array_is_descendent,
      json_value_swap
    },
    (void (*)(pointer)) json_array_virtual_destructor,
    (void (*)(pointer,const_pointer)) json_array_virtual_copy_ctor,
    (void (*)(pointer,const_pointer)) json_array_virtual_assign,
    (bool (*)(const_pointer,const_pointer)) json_array_virtual_less_than_compare,
    (json_type_t (*)(const_pointer)) json_value_type,
    (int (*)(const_pointer,char *,int)) json_array_print_to_string,
    (void (*)(pointer)) json_array_clear
  },
  (void (*)(pointer,const_pointer)) json_array_add,
  (json_value_pointer (*)(pointer,yaooc_size_type)) json_array_at,
  (json_value_const_pointer (*)(const_pointer,yaooc_size_type)) json_array_at,
  (yaooc_size_type (*)(pointer)) json_array_size,
  (json_array_iterator (*)(pointer)) json_array_begin,
  (json_array_iterator (*)(pointer)) json_array_end,
  (json_array_const_iterator (*)(const_pointer)) json_array_begin,
  (json_array_const_iterator (*)(const_pointer)) json_array_end,
};

DEFINE_TYPE_INFO(json_array,json_array_default_ctor,NULL,NULL,NULL,NULL,&json_array_class_members,json_value)

MAP_IMPLEMENTATION(json_string,json_value);
void json_object_default_ctor(pointer p)
{
  json_object_pointer this=p;
  this->type_=JSON_OBJECT;
  this->object_=new(json_string_json_value_map);
}

void json_object_virtual_destructor(pointer p)
{
  json_value_pointer this=p;
  delete(this->object_);
}

void json_object_virtual_copy_ctor(pointer d,const_pointer s)
{
  json_object_default_ctor(d);
  json_object_virtual_assign(d,s);
}

void json_object_virtual_assign(pointer d,const_pointer s)
{
  json_object_pointer dst=d;
  json_object_const_pointer src=s;
  if(dst->type_ == JSON_UNDEFINED)
    newp(dst,json_object);
  if(dst->type_ == JSON_OBJECT) {
    real_assign_static(dst->object_,src->object_,json_string_json_value_map_ti);
  } else {
    fprintf(stderr,"Invalid assignment to json_object\n");
    abort();
  }
}

bool json_object_virtual_less_than_compare(const_pointer p1,const_pointer p2)
{
  return false;
}

int json_object_print_to_string(const_pointer p,char * str,int remaining)
{
  json_object_const_pointer this=p;
  int ret=0;
  *str='{'; ret++; str++; remaining--;
  json_object_const_iterator io;
  int np;
  if(M(this,size) > 0) {
    for(io=M(this,cbegin);io!=M(this,cend);io++) {
      np=M(&io->first,print_to_string,str,remaining);
      str+=np; *str=':'; str++; remaining-=np+1; ret+=np+1;
      np=M(&io->second,print_to_string,str,remaining);
      str+=np; *str=','; str++; remaining-=np+1; ret+=np+1;
    }
    str--; remaining++; ret--; /* remove comma */
  }
  *str='}'; ret++; *(str+1)=0;
  return ret;
}

void json_object_clear(pointer p)
{
  json_object_pointer this=p;
  M(this->object_,clear);
}

void json_object_insert(pointer p,const_pointer key,const_pointer value)
{
  json_object_pointer this=p;
  /* key type must be string */
  M(this->object_,insert,key,value);
}

json_value_pointer json_object_at(pointer p,const_pointer key)
{
  json_object_pointer this=p;
  return M(this->object_,at,key);
}

yaooc_size_type json_object_size(const_pointer p)
{
  json_object_const_pointer this=p;
  return M(this->object_,size);
}

json_object_iterator json_object_begin(pointer p)
{
  json_object_pointer this=p;
  return M(this->object_,begin);
}

json_object_iterator json_object_end(pointer p)
{
  json_object_pointer this=p;
  return M(this->object_,end);
}

ISA_IMPLEMENTATION(json_object,json_value)

json_object_class_members_t json_object_class_members = {
  {
    {
      json_object_isa,
      json_object_is_descendent,
      json_value_swap
    },
    (void (*)(pointer)) json_object_virtual_destructor,
    (void (*)(pointer,const_pointer)) json_object_virtual_copy_ctor,
    (void (*)(pointer,const_pointer)) json_object_virtual_assign,
    (bool (*)(const_pointer,const_pointer)) json_object_virtual_less_than_compare,
    (json_type_t (*)(const_pointer)) json_value_type,
    (int (*)(const_pointer,char *,int)) json_object_print_to_string,
    (void (*)(pointer)) json_object_clear
  },
  (void (*)(pointer,const_pointer,const_pointer)) json_object_insert,
  (json_value_pointer (*)(pointer,const_pointer)) json_object_at,
  (json_value_const_pointer (*)(const_pointer,const_pointer)) json_object_at,
  (yaooc_size_type (*)(const_pointer)) json_object_size,
  (json_object_iterator (*)(pointer)) json_object_begin,
  (json_object_iterator (*)(pointer)) json_object_end,
  (json_object_const_iterator (*)(const_pointer)) json_object_begin,
  (json_object_const_iterator (*)(const_pointer)) json_object_end,
};

DEFINE_TYPE_INFO(json_object,json_object_default_ctor,NULL,NULL,NULL,NULL,&json_object_class_members,json_value)

