#include <yaooc/json.h>
yaooc_json_exception_class_table_t yaooc_json_exception_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_exception_class_table,
.type_name_ = (const char*)"yaooc_json_exception_t",
.swap = (void(*)(pointer,pointer)) yaooc_json_exception_swap,
.what = (const char*(*)(const_pointer)) yaooc_json_exception_what,
};
const type_info_t __yaooc_json_exception_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_json_exception_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=NULL,
.dtor_=NULL,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaooc_json_exception_class_table,
.parent_=&__yaooc_exception_ti
};
const type_info_t* const yaooc_json_exception_ti=&__yaooc_json_exception_ti;
void yaooc_json_value_default_ctor(pointer __pthis__)
{
yaooc_json_value_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_json_value);



    this->type_=JSON_UNDEFINED;
    this->real_=0;
  
}
void yaooc_json_value_dtor(pointer __pthis__)
{
yaooc_json_value_pointer this=__pthis__;(void)this;


    if(this->type_ != JSON_UNDEFINED)
      M(this,virtual_dtor);
  
}
void yaooc_json_value_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaooc_json_value_pointer this=__pthis__;(void)this;
yaooc_json_value_const_pointer src=__psrc__;(void)src;


call_default_ctor_static(this,yaooc_json_value);
assign_static(this,src,yaooc_json_value);

}
void yaooc_json_value_assign(pointer __pthis__,const_pointer __psrc__)
{
yaooc_json_value_pointer this=__pthis__;(void)this;
yaooc_json_value_const_pointer src=__psrc__;(void)src;


    if(this->type_ == JSON_UNDEFINED) {

      switch(src->type_) {
        case JSON_UNDEFINED:
          break;

        case JSON_NULL:
          this->type_=JSON_NULL;
          break;

        case JSON_BOOL:
          this->type_=JSON_BOOL;
          this->bool_=src->bool_;
          break;

        case JSON_INTEGER:
          this->type_=JSON_INTEGER;
          this->int_=src->int_;
          break;

        case JSON_REAL:
          this->type_=JSON_REAL;
          this->real_=src->real_;
          break;

        case JSON_STRING:
          this->type_=JSON_STRING;
          this->string_=src->string_ ? STRDUP(src->string_) : NULL;
          break;

        case JSON_ARRAY:
          this->type_=JSON_ARRAY;
          this->array_=new(yaooc_json_value_array);
          assign_static(this->array_,src->array_,yaooc_json_value_array);
          break;

        case JSON_OBJECT:
          this->type_=JSON_OBJECT;
          this->array_=new(yaooc_json_string_value_map);
          assign_static(this->object_,src->object_,yaooc_json_string_value_map);
          break;
      }
    } else {
      M(this,virtual_assign,src);
    }
  
}
int yaooc_json_value_rich_compare(const_pointer __plhs__,const_pointer __prhs__)
{
yaooc_json_value_const_pointer lhs=__plhs__;(void)lhs;
yaooc_json_value_const_pointer rhs=__prhs__;(void)rhs;

    if(lhs->type_ == JSON_UNDEFINED) {
      if(rhs->type_ == JSON_UNDEFINED)
        return 0;
      return -1;
    }
    return M(lhs,virtual_rich_compare,rhs);
  
}
void yaooc_json_value_virtual_dtor(pointer __pthis__)
{
yaooc_json_value_pointer this=__pthis__;(void)this;
#define super() yaooc_json_value_parent_class_table->virtual_dtor(this)
#define PM(method,...) CTM((*yaooc_json_value_parent_class_table),this,method,## __VA_ARGS__)


    
#undef PM
#undef super
}
void yaooc_json_value_virtual_assign(pointer __pthis__,const_pointer src)
{
yaooc_json_value_pointer this=__pthis__;(void)this;
#define super() yaooc_json_value_parent_class_table->virtual_assign(this,src)
#define PM(method,...) CTM((*yaooc_json_value_parent_class_table),this,method,## __VA_ARGS__)


    
#undef PM
#undef super
}
int yaooc_json_value_virtual_rich_compare(const_pointer __pthis__,const_pointer other)
{
yaooc_json_value_const_pointer this=__pthis__;(void)this;
#define super() yaooc_json_value_parent_class_table->virtual_rich_compare(this,other)
#define PM(method,...) CTM((*yaooc_json_value_parent_class_table),this,method,## __VA_ARGS__)


      return 0;
    
#undef PM
#undef super
}
yaooc_json_value_class_table_t yaooc_json_value_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_object_class_table,
.type_name_ = (const char*)"yaooc_json_value_t",
.swap = (void(*)(pointer,pointer)) yaooc_json_value_swap,
.virtual_dtor = (void(*)(pointer)) yaooc_json_value_virtual_dtor,
.virtual_assign = (void(*)(pointer,const_pointer)) yaooc_json_value_virtual_assign,
.virtual_rich_compare = (int(*)(const_pointer,const_pointer)) yaooc_json_value_virtual_rich_compare,
};
const type_info_t __yaooc_json_value_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_json_value_t),
.rich_compare_=yaooc_json_value_rich_compare,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=NULL,
.dtor_=yaooc_json_value_dtor,
.copy_ctor_=yaooc_json_value_copy_ctor,
.assign_=yaooc_json_value_assign,
.class_table_=(const class_table_t*) &yaooc_json_value_class_table,
.parent_=&__yaooc_object_ti
};
const type_info_t* const yaooc_json_value_ti=&__yaooc_json_value_ti;
void yaooc_json_null_default_ctor(pointer __pthis__)
{
yaooc_json_null_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_json_null);



    this->type_=JSON_NULL;
  
}
void yaooc_json_null_assign(pointer __pthis__,const_pointer __psrc__)
{
yaooc_json_null_pointer this=__pthis__;(void)this;
yaooc_json_null_const_pointer src=__psrc__;(void)src;



    if(src->type_!=JSON_NULL)
      THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,"Attempt to assign non json null to json null"));
  
}
int yaooc_json_null_rich_compare(const_pointer __plhs__,const_pointer __prhs__)
{
yaooc_json_null_const_pointer lhs=__plhs__;(void)lhs;
yaooc_json_null_const_pointer rhs=__prhs__;(void)rhs;


    if(lhs->type_==JSON_NULL) {
      if(rhs->type_==JSON_NULL)
        return 0;
      if(rhs->type_==JSON_UNDEFINED)
        return 1;
    } else if(rhs->type_==JSON_NULL) {
      if(lhs->type_==JSON_UNDEFINED)
        return -1;
    }
    THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,"Invalid comparison to JSON_NULL"));
    return 0;
  
}
void yaooc_json_null_virtual_dtor(pointer __pthis__)
{
yaooc_json_null_pointer this=__pthis__;(void)this;
#define super() yaooc_json_null_parent_class_table->virtual_dtor(this)
#define PM(method,...) CTM((*yaooc_json_null_parent_class_table),this,method,## __VA_ARGS__)


    
#undef PM
#undef super
}
void yaooc_json_null_virtual_assign(pointer __pthis__,const_pointer src)
{
yaooc_json_null_pointer this=__pthis__;(void)this;
#define super() yaooc_json_null_parent_class_table->virtual_assign(this,src)
#define PM(method,...) CTM((*yaooc_json_null_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_json_null_assign(this,src);
    
#undef PM
#undef super
}
int yaooc_json_null_virtual_rich_compare(const_pointer __pthis__,const_pointer other)
{
yaooc_json_null_const_pointer this=__pthis__;(void)this;
#define super() yaooc_json_null_parent_class_table->virtual_rich_compare(this,other)
#define PM(method,...) CTM((*yaooc_json_null_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_json_null_rich_compare(this,other);
    
#undef PM
#undef super
}
yaooc_json_null_class_table_t yaooc_json_null_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_json_value_class_table,
.type_name_ = (const char*)"yaooc_json_null_t",
.swap = (void(*)(pointer,pointer)) yaooc_json_null_swap,
.virtual_dtor = (void(*)(pointer)) yaooc_json_null_virtual_dtor,
.virtual_assign = (void(*)(pointer,const_pointer)) yaooc_json_null_virtual_assign,
.virtual_rich_compare = (int(*)(const_pointer,const_pointer)) yaooc_json_null_virtual_rich_compare,
};
const type_info_t __yaooc_json_null_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_json_null_t),
.rich_compare_=yaooc_json_null_rich_compare,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=NULL,
.dtor_=NULL,
.copy_ctor_=NULL,
.assign_=yaooc_json_null_assign,
.class_table_=(const class_table_t*) &yaooc_json_null_class_table,
.parent_=&__yaooc_json_value_ti
};
const type_info_t* const yaooc_json_null_ti=&__yaooc_json_null_ti;
void yaooc_json_bool_default_ctor(pointer __pthis__)
{
yaooc_json_bool_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_json_bool);



    this->type_=JSON_BOOL;
    this->bool_=false;
  
}
void yaooc_json_bool_assign(pointer __pthis__,const_pointer __psrc__)
{
yaooc_json_bool_pointer this=__pthis__;(void)this;
yaooc_json_bool_const_pointer src=__psrc__;(void)src;



    if(src->type_==JSON_BOOL)
      this->bool_=src->bool_;
    THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,"Attempt to assign non json bool to json bool"));
  
}
int yaooc_json_bool_rich_compare(const_pointer __plhs__,const_pointer __prhs__)
{
yaooc_json_bool_const_pointer lhs=__plhs__;(void)lhs;
yaooc_json_bool_const_pointer rhs=__prhs__;(void)rhs;


    if(lhs->type_==JSON_BOOL) {
      if(rhs->type_==JSON_BOOL)
        return lhs->bool_<rhs->bool_;
      if(rhs->type_==JSON_UNDEFINED)
        return 1;
    } else if(rhs->type_==JSON_BOOL) {
      if(lhs->type_==JSON_UNDEFINED)
        return -1;
    }
    THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,"Invalid comparison to JSON_BOOL"));
    return 0;
  
}
void yaooc_json_bool_ctor_bool(pointer __pthis,va_list __con_args__){
yaooc_json_bool_pointer this=__pthis;(void)this;
int v = va_arg(__con_args__,int);

call_default_ctor_static(this,yaooc_json_bool);


    this->bool_=v;
  
}
void yaooc_json_bool_virtual_dtor(pointer __pthis__)
{
yaooc_json_bool_pointer this=__pthis__;(void)this;
#define super() yaooc_json_bool_parent_class_table->virtual_dtor(this)
#define PM(method,...) CTM((*yaooc_json_bool_parent_class_table),this,method,## __VA_ARGS__)


    
#undef PM
#undef super
}
void yaooc_json_bool_virtual_assign(pointer __pthis__,const_pointer src)
{
yaooc_json_bool_pointer this=__pthis__;(void)this;
#define super() yaooc_json_bool_parent_class_table->virtual_assign(this,src)
#define PM(method,...) CTM((*yaooc_json_bool_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_json_bool_assign(this,src);
    
#undef PM
#undef super
}
int yaooc_json_bool_virtual_rich_compare(const_pointer __pthis__,const_pointer other)
{
yaooc_json_bool_const_pointer this=__pthis__;(void)this;
#define super() yaooc_json_bool_parent_class_table->virtual_rich_compare(this,other)
#define PM(method,...) CTM((*yaooc_json_bool_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_json_bool_rich_compare(this,other);
    
#undef PM
#undef super
}
yaooc_json_bool_class_table_t yaooc_json_bool_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_json_value_class_table,
.type_name_ = (const char*)"yaooc_json_bool_t",
.swap = (void(*)(pointer,pointer)) yaooc_json_bool_swap,
.virtual_dtor = (void(*)(pointer)) yaooc_json_bool_virtual_dtor,
.virtual_assign = (void(*)(pointer,const_pointer)) yaooc_json_bool_virtual_assign,
.virtual_rich_compare = (int(*)(const_pointer,const_pointer)) yaooc_json_bool_virtual_rich_compare,
};
const type_info_t __yaooc_json_bool_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_json_bool_t),
.rich_compare_=yaooc_json_bool_rich_compare,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=NULL,
.dtor_=NULL,
.copy_ctor_=NULL,
.assign_=yaooc_json_bool_assign,
.class_table_=(const class_table_t*) &yaooc_json_bool_class_table,
.parent_=&__yaooc_json_value_ti
};
const type_info_t* const yaooc_json_bool_ti=&__yaooc_json_bool_ti;
void yaooc_json_integer_default_ctor(pointer __pthis__)
{
yaooc_json_integer_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_json_integer);



    this->type_=JSON_INTEGER;
    this->int_=0;
  
}
void yaooc_json_integer_assign(pointer __pthis__,const_pointer __psrc__)
{
yaooc_json_integer_pointer this=__pthis__;(void)this;
yaooc_json_integer_const_pointer src=__psrc__;(void)src;


    if(src->type_==JSON_INTEGER)
      this->int_=src->int_;
    THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,"Attempt to assign non json integer to json integer"));
  
}
int yaooc_json_integer_rich_compare(const_pointer __plhs__,const_pointer __prhs__)
{
yaooc_json_integer_const_pointer lhs=__plhs__;(void)lhs;
yaooc_json_integer_const_pointer rhs=__prhs__;(void)rhs;


    if(lhs->type_==JSON_INTEGER) {
      if(rhs->type_==JSON_INTEGER) {
        if(lhs->int_<rhs->int_)
          return -1;
        if(lhs->int_>rhs->int_)
          return 1;
        return 0;
      }
      if(rhs->type_==JSON_UNDEFINED)
        return 1;
    } else if(rhs->type_==JSON_INTEGER) {
      if(lhs->type_==JSON_UNDEFINED)
        return -1;
    }
    THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,"Invalid comparison to json integer"));
    return 0;
  
}
void yaooc_json_integer_ctor_int(pointer __pthis,va_list __con_args__){
yaooc_json_integer_pointer this=__pthis;(void)this;
int v = va_arg(__con_args__,int);

call_default_ctor_static(this,yaooc_json_integer);


    this->int_=v;
  
}
void yaooc_json_integer_virtual_dtor(pointer __pthis__)
{
yaooc_json_integer_pointer this=__pthis__;(void)this;
#define super() yaooc_json_integer_parent_class_table->virtual_dtor(this)
#define PM(method,...) CTM((*yaooc_json_integer_parent_class_table),this,method,## __VA_ARGS__)


    
#undef PM
#undef super
}
void yaooc_json_integer_virtual_assign(pointer __pthis__,const_pointer src)
{
yaooc_json_integer_pointer this=__pthis__;(void)this;
#define super() yaooc_json_integer_parent_class_table->virtual_assign(this,src)
#define PM(method,...) CTM((*yaooc_json_integer_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_json_integer_assign(this,src);
    
#undef PM
#undef super
}
int yaooc_json_integer_virtual_rich_compare(const_pointer __pthis__,const_pointer other)
{
yaooc_json_integer_const_pointer this=__pthis__;(void)this;
#define super() yaooc_json_integer_parent_class_table->virtual_rich_compare(this,other)
#define PM(method,...) CTM((*yaooc_json_integer_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_json_integer_rich_compare(this,other);
    
#undef PM
#undef super
}
yaooc_json_integer_class_table_t yaooc_json_integer_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_json_value_class_table,
.type_name_ = (const char*)"yaooc_json_integer_t",
.swap = (void(*)(pointer,pointer)) yaooc_json_integer_swap,
.virtual_dtor = (void(*)(pointer)) yaooc_json_integer_virtual_dtor,
.virtual_assign = (void(*)(pointer,const_pointer)) yaooc_json_integer_virtual_assign,
.virtual_rich_compare = (int(*)(const_pointer,const_pointer)) yaooc_json_integer_virtual_rich_compare,
};
const type_info_t __yaooc_json_integer_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_json_integer_t),
.rich_compare_=yaooc_json_integer_rich_compare,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=NULL,
.dtor_=NULL,
.copy_ctor_=NULL,
.assign_=yaooc_json_integer_assign,
.class_table_=(const class_table_t*) &yaooc_json_integer_class_table,
.parent_=&__yaooc_json_value_ti
};
const type_info_t* const yaooc_json_integer_ti=&__yaooc_json_integer_ti;
void yaooc_json_real_default_ctor(pointer __pthis__)
{
yaooc_json_real_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_json_real);



    this->type_=JSON_REAL;
    this->real_=0;
  
}
void yaooc_json_real_assign(pointer __pthis__,const_pointer __psrc__)
{
yaooc_json_real_pointer this=__pthis__;(void)this;
yaooc_json_real_const_pointer src=__psrc__;(void)src;


    if(src->type_==JSON_REAL)
      this->real_=src->real_;
    THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,"Attempt to assign non json real to json real"));
  
}
int yaooc_json_real_rich_compare(const_pointer __plhs__,const_pointer __prhs__)
{
yaooc_json_real_const_pointer lhs=__plhs__;(void)lhs;
yaooc_json_real_const_pointer rhs=__prhs__;(void)rhs;


    if(lhs->type_==JSON_REAL) {
      if(rhs->type_==JSON_REAL) {
        if(lhs->real_<rhs->real_)
          return -1;
        if(lhs->real_>rhs->real_)
          return 1;
        return 0;
      }
      if(rhs->type_==JSON_UNDEFINED)
        return 1;
    } else if(rhs->type_==JSON_REAL) {
      if(lhs->type_==JSON_UNDEFINED)
        return -1;
    }
    THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,"Invalid comparison to json real"));
    return 0;
  
}
void yaooc_json_real_ctor_int(pointer __pthis,va_list __con_args__){
yaooc_json_real_pointer this=__pthis;(void)this;
double v = va_arg(__con_args__,double);

call_default_ctor_static(this,yaooc_json_real);


    this->real_=v;
  
}
void yaooc_json_real_virtual_dtor(pointer __pthis__)
{
yaooc_json_real_pointer this=__pthis__;(void)this;
#define super() yaooc_json_real_parent_class_table->virtual_dtor(this)
#define PM(method,...) CTM((*yaooc_json_real_parent_class_table),this,method,## __VA_ARGS__)


    
#undef PM
#undef super
}
void yaooc_json_real_virtual_assign(pointer __pthis__,const_pointer src)
{
yaooc_json_real_pointer this=__pthis__;(void)this;
#define super() yaooc_json_real_parent_class_table->virtual_assign(this,src)
#define PM(method,...) CTM((*yaooc_json_real_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_json_real_assign(this,src);
    
#undef PM
#undef super
}
int yaooc_json_real_virtual_rich_compare(const_pointer __pthis__,const_pointer other)
{
yaooc_json_real_const_pointer this=__pthis__;(void)this;
#define super() yaooc_json_real_parent_class_table->virtual_rich_compare(this,other)
#define PM(method,...) CTM((*yaooc_json_real_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_json_real_rich_compare(this,other);
    
#undef PM
#undef super
}
yaooc_json_real_class_table_t yaooc_json_real_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_json_value_class_table,
.type_name_ = (const char*)"yaooc_json_real_t",
.swap = (void(*)(pointer,pointer)) yaooc_json_real_swap,
.virtual_dtor = (void(*)(pointer)) yaooc_json_real_virtual_dtor,
.virtual_assign = (void(*)(pointer,const_pointer)) yaooc_json_real_virtual_assign,
.virtual_rich_compare = (int(*)(const_pointer,const_pointer)) yaooc_json_real_virtual_rich_compare,
};
const type_info_t __yaooc_json_real_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_json_real_t),
.rich_compare_=yaooc_json_real_rich_compare,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=NULL,
.dtor_=NULL,
.copy_ctor_=NULL,
.assign_=yaooc_json_real_assign,
.class_table_=(const class_table_t*) &yaooc_json_real_class_table,
.parent_=&__yaooc_json_value_ti
};
const type_info_t* const yaooc_json_real_ti=&__yaooc_json_real_ti;
void yaooc_json_string_default_ctor(pointer __pthis__)
{
yaooc_json_string_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_json_string);



    this->type_=JSON_STRING;
    this->string_=NULL;
  
}
void yaooc_json_string_dtor(pointer __pthis__)
{
yaooc_json_string_pointer this=__pthis__;(void)this;


    if(this->string_!=NULL)
      FREE(this->string_);
  
}
void yaooc_json_string_assign(pointer __pthis__,const_pointer __psrc__)
{
yaooc_json_string_pointer this=__pthis__;(void)this;
yaooc_json_string_const_pointer src=__psrc__;(void)src;


    if(src->type_==JSON_STRING) {
      deletep(this,yaooc_json_string);
      newp(this,yaooc_json_string);
      this->string_=src->string_ ? STRDUP(src->string_) : NULL;
    }
    THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,"Attempt to assign non json string to json string"));
  
}
int yaooc_json_string_rich_compare(const_pointer __plhs__,const_pointer __prhs__)
{
yaooc_json_string_const_pointer lhs=__plhs__;(void)lhs;
yaooc_json_string_const_pointer rhs=__prhs__;(void)rhs;


    if(lhs->type_==JSON_STRING) {
      if(rhs->type_==JSON_STRING) {
        if(lhs->string_ == NULL) {
          if(rhs->string_ == NULL)
            return 0;
          return -1;
        }
        if(rhs->string_ == NULL)
          return 1;
        return strcmp(lhs->string_,rhs->string_);
      }
      if(rhs->type_==JSON_UNDEFINED)
        return 1;
    } else if(rhs->type_==JSON_STRING) {
      if(lhs->type_==JSON_UNDEFINED)
        return -1;
    }
    THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,"Invalid comparison to json string"));
    return 0;
  
}
void yaooc_json_string_ctor_ccs(pointer __pthis,va_list __con_args__){
yaooc_json_string_pointer this=__pthis;(void)this;
const char* v = va_arg(__con_args__,const char*);

call_default_ctor_static(this,yaooc_json_string);


    this->string_ = v ? STRDUP(v) : NULL;
  
}
void yaooc_json_string_virtual_dtor(pointer __pthis__)
{
yaooc_json_string_pointer this=__pthis__;(void)this;
#define super() yaooc_json_string_parent_class_table->virtual_dtor(this)
#define PM(method,...) CTM((*yaooc_json_string_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_json_string_dtor(this);
    
#undef PM
#undef super
}
void yaooc_json_string_virtual_assign(pointer __pthis__,const_pointer src)
{
yaooc_json_string_pointer this=__pthis__;(void)this;
#define super() yaooc_json_string_parent_class_table->virtual_assign(this,src)
#define PM(method,...) CTM((*yaooc_json_string_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_json_string_assign(this,src);
    
#undef PM
#undef super
}
int yaooc_json_string_virtual_rich_compare(const_pointer __pthis__,const_pointer other)
{
yaooc_json_string_const_pointer this=__pthis__;(void)this;
#define super() yaooc_json_string_parent_class_table->virtual_rich_compare(this,other)
#define PM(method,...) CTM((*yaooc_json_string_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_json_string_rich_compare(this,other);
    
#undef PM
#undef super
}
yaooc_json_string_class_table_t yaooc_json_string_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_json_value_class_table,
.type_name_ = (const char*)"yaooc_json_string_t",
.swap = (void(*)(pointer,pointer)) yaooc_json_string_swap,
.virtual_dtor = (void(*)(pointer)) yaooc_json_string_virtual_dtor,
.virtual_assign = (void(*)(pointer,const_pointer)) yaooc_json_string_virtual_assign,
.virtual_rich_compare = (int(*)(const_pointer,const_pointer)) yaooc_json_string_virtual_rich_compare,
};
const type_info_t __yaooc_json_string_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_json_string_t),
.rich_compare_=yaooc_json_string_rich_compare,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=NULL,
.dtor_=yaooc_json_string_dtor,
.copy_ctor_=NULL,
.assign_=yaooc_json_string_assign,
.class_table_=(const class_table_t*) &yaooc_json_string_class_table,
.parent_=&__yaooc_json_value_ti
};
const type_info_t* const yaooc_json_string_ti=&__yaooc_json_string_ti;
VECTOR_IMPLEMENTATION(yaooc_json_value,yaooc_json_value_array);


void yaooc_json_array_default_ctor(pointer __pthis__)
{
yaooc_json_array_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_json_array);



    this->type_=JSON_ARRAY;
    this->array_=new(yaooc_json_value_array);
  
}
void yaooc_json_array_dtor(pointer __pthis__)
{
yaooc_json_array_pointer this=__pthis__;(void)this;


    delete(this->array_);
  
}
void yaooc_json_array_assign(pointer __pthis__,const_pointer __psrc__)
{
yaooc_json_array_pointer this=__pthis__;(void)this;
yaooc_json_array_const_pointer src=__psrc__;(void)src;


    if(src->type_==JSON_ARRAY) {
      assign_static(this->array_,src->array_,yaooc_json_value_array);
    }
    THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,"Attempt to assign non json string to json string"));
  
}
int yaooc_json_array_rich_compare(const_pointer __plhs__,const_pointer __prhs__)
{
yaooc_json_array_const_pointer lhs=__plhs__;(void)lhs;
yaooc_json_array_const_pointer rhs=__prhs__;(void)rhs;


    if(lhs->type_==JSON_ARRAY) {
      if(rhs->type_==JSON_ARRAY) {
        return op_rich_compare_static(lhs,rhs,yaooc_json_value_array);
      }
      if(rhs->type_==JSON_UNDEFINED)
        return 1;
    } else if(rhs->type_==JSON_ARRAY) {
      if(lhs->type_==JSON_UNDEFINED)
        return -1;
    }
    THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,"Invalid comparison to json array"));
    return 0;
  
}
void yaooc_json_array_virtual_dtor(pointer __pthis__)
{
yaooc_json_array_pointer this=__pthis__;(void)this;
#define super() yaooc_json_array_parent_class_table->virtual_dtor(this)
#define PM(method,...) CTM((*yaooc_json_array_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_json_array_dtor(this);
    
#undef PM
#undef super
}
void yaooc_json_array_virtual_assign(pointer __pthis__,const_pointer src)
{
yaooc_json_array_pointer this=__pthis__;(void)this;
#define super() yaooc_json_array_parent_class_table->virtual_assign(this,src)
#define PM(method,...) CTM((*yaooc_json_array_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_json_array_assign(this,src);
    
#undef PM
#undef super
}
int yaooc_json_array_virtual_rich_compare(const_pointer __pthis__,const_pointer other)
{
yaooc_json_array_const_pointer this=__pthis__;(void)this;
#define super() yaooc_json_array_parent_class_table->virtual_rich_compare(this,other)
#define PM(method,...) CTM((*yaooc_json_array_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_json_array_rich_compare(this,other);
    
#undef PM
#undef super
}
yaooc_json_array_class_table_t yaooc_json_array_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_json_value_class_table,
.type_name_ = (const char*)"yaooc_json_array_t",
.swap = (void(*)(pointer,pointer)) yaooc_json_array_swap,
.virtual_dtor = (void(*)(pointer)) yaooc_json_array_virtual_dtor,
.virtual_assign = (void(*)(pointer,const_pointer)) yaooc_json_array_virtual_assign,
.virtual_rich_compare = (int(*)(const_pointer,const_pointer)) yaooc_json_array_virtual_rich_compare,
};
const type_info_t __yaooc_json_array_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_json_array_t),
.rich_compare_=yaooc_json_array_rich_compare,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=NULL,
.dtor_=yaooc_json_array_dtor,
.copy_ctor_=NULL,
.assign_=yaooc_json_array_assign,
.class_table_=(const class_table_t*) &yaooc_json_array_class_table,
.parent_=&__yaooc_json_value_ti
};
const type_info_t* const yaooc_json_array_ti=&__yaooc_json_array_ti;
MINI_MAP_IMPLEMENTATION(yaooc_json_string,yaooc_json_value,yaooc_json_string_value_map);


void yaooc_json_object_default_ctor(pointer __pthis__)
{
yaooc_json_object_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_json_object);



    this->type_=JSON_OBJECT;
    this->object_=new(yaooc_json_string_value_map);
  
}
void yaooc_json_object_dtor(pointer __pthis__)
{
yaooc_json_object_pointer this=__pthis__;(void)this;


    delete(this->object_);
  
}
void yaooc_json_object_assign(pointer __pthis__,const_pointer __psrc__)
{
yaooc_json_object_pointer this=__pthis__;(void)this;
yaooc_json_object_const_pointer src=__psrc__;(void)src;


    if(src->type_==JSON_OBJECT) {
      assign_static(this->object_,src->object_,yaooc_json_string_value_map);
    }
    THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,"Attempt to assign non json object to json object"));
  
}
int yaooc_json_object_rich_compare(const_pointer __plhs__,const_pointer __prhs__)
{
yaooc_json_object_const_pointer lhs=__plhs__;(void)lhs;
yaooc_json_object_const_pointer rhs=__prhs__;(void)rhs;


    if(lhs->type_==JSON_OBJECT) {
      if(rhs->type_==JSON_OBJECT) {
        return 0;
      }
      if(rhs->type_==JSON_UNDEFINED)
        return 1;
    } else if(rhs->type_==JSON_OBJECT) {
      if(lhs->type_==JSON_UNDEFINED)
        return -1;
    }
    THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,"Invalid comparison to json object"));
    return 0;
  
}
void yaooc_json_object_virtual_dtor(pointer __pthis__)
{
yaooc_json_object_pointer this=__pthis__;(void)this;
#define super() yaooc_json_object_parent_class_table->virtual_dtor(this)
#define PM(method,...) CTM((*yaooc_json_object_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_json_object_dtor(this);
    
#undef PM
#undef super
}
void yaooc_json_object_virtual_assign(pointer __pthis__,const_pointer src)
{
yaooc_json_object_pointer this=__pthis__;(void)this;
#define super() yaooc_json_object_parent_class_table->virtual_assign(this,src)
#define PM(method,...) CTM((*yaooc_json_object_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_json_object_assign(this,src);
    
#undef PM
#undef super
}
int yaooc_json_object_virtual_rich_compare(const_pointer __pthis__,const_pointer other)
{
yaooc_json_object_const_pointer this=__pthis__;(void)this;
#define super() yaooc_json_object_parent_class_table->virtual_rich_compare(this,other)
#define PM(method,...) CTM((*yaooc_json_object_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_json_object_rich_compare(this,other);
    
#undef PM
#undef super
}
yaooc_json_object_class_table_t yaooc_json_object_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_json_value_class_table,
.type_name_ = (const char*)"yaooc_json_object_t",
.swap = (void(*)(pointer,pointer)) yaooc_json_object_swap,
.virtual_dtor = (void(*)(pointer)) yaooc_json_object_virtual_dtor,
.virtual_assign = (void(*)(pointer,const_pointer)) yaooc_json_object_virtual_assign,
.virtual_rich_compare = (int(*)(const_pointer,const_pointer)) yaooc_json_object_virtual_rich_compare,
};
const type_info_t __yaooc_json_object_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_json_object_t),
.rich_compare_=yaooc_json_object_rich_compare,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=NULL,
.dtor_=yaooc_json_object_dtor,
.copy_ctor_=NULL,
.assign_=yaooc_json_object_assign,
.class_table_=(const class_table_t*) &yaooc_json_object_class_table,
.parent_=&__yaooc_json_value_ti
};
const type_info_t* const yaooc_json_object_ti=&__yaooc_json_object_ti;
