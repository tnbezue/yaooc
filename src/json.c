#include <yaooc/json.h>
yaooc_json_exception_class_table_t yaooc_json_exception_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_exception_class_table,
.type_name_ = (const char*)"yaooc_json_exception_t",
.swap = (void(*)(pointer,pointer)) yaooc_json_exception_swap,
.what = (const char*(*)(const_pointer)) yaooc_json_exception_what,
.error_code = (int(*)(const_pointer)) yaooc_json_exception_error_code,
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



    const type_info_t* ti=this->class_table_->__this_ti__;
    while(ti != yaooc_json_value_ti)
    {
      if(ti->dtor_)
        ti->dtor_(this);
      ti=ti->parent_;
    }
  


  
}
void yaooc_json_value_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaooc_json_value_pointer this=__pthis__;(void)this;
yaooc_json_value_const_pointer src=__psrc__;(void)src;



    static _Thread_local bool active=false; 
    if(!active) {
      active=true;
      copy_constructor copy_ctor=get_copy_ctor(this->class_table_->__this_ti__);
      if(copy_ctor != yaooc_json_value_copy_ctor) {
        copy_ctor(this,src);
        active=false;
        return;
      }
    }
    active=false;
  


call_default_ctor_static(this,yaooc_json_value);
assign_static(this,src,yaooc_json_value);

}
void yaooc_json_value_assign(pointer __pthis__,const_pointer __psrc__)
{
yaooc_json_value_pointer this=__pthis__;(void)this;
yaooc_json_value_const_pointer src=__psrc__;(void)src;



    static _Thread_local bool active=false; 
    if(!active) {
      assignment assign_method=get_assignment(this->class_table_->__this_ti__);
      if(assign_method != NULL) {
        assign_method(this,src);
        active=false;
        return;
      }
    }
    active=false;
  


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
    }
  
}
int yaooc_json_value_rich_compare(const_pointer __plhs__,const_pointer __prhs__)
{
yaooc_json_value_const_pointer lhs=__plhs__;(void)lhs;
yaooc_json_value_const_pointer rhs=__prhs__;(void)rhs;



    static bool active=false;
    if(!active) {
      rich_compare rc= get_rich_compare(lhs->class_table_->__this_ti__);
      if(rc != NULL) {
        int ret=rc(lhs,rhs);
        active=false;
        return ret;
      }
    }
    active=false;
  


    if(lhs->type_ == JSON_UNDEFINED) {
      if(rhs->type_ == JSON_UNDEFINED)
        return 0;
      return -1; 
    } else if(rhs->type_ == JSON_UNDEFINED)
      return 1;
    return 0;  
  
}
void yaooc_json_value_to_stream(const_pointer __pthis__,ostream_pointer __pstrm__)
{
yaooc_json_value_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__pstrm__;(void)ostrm;



    to_stream ts=get_to_stream(this->class_table_->__this_ti__);
    if(ts != yaooc_json_value_to_stream) {
      ts(this,ostrm);
      return;
    }
  


  
}
void yaooc_json_value_from_stream(pointer __pthis__,ostream_pointer __pstrm__)
{
yaooc_json_value_pointer this=__pthis__;(void)this;
yaooc_istream_pointer istrm=__pstrm__;(void)istrm;



    from_stream fs=get_from_stream(this->class_table_->__this_ti__);
    if(fs != yaooc_json_value_from_stream) {
      fs(this,istrm);
      return;
    }
  


}
yaooc_json_type_t yaooc_json_value_type(const_pointer __pthis__)
{
yaooc_json_value_const_pointer this=__pthis__;(void)this;
#define super() yaooc_json_value_parent_class_table->type(this)
#define PM(method,...) CTM((*yaooc_json_value_parent_class_table),this,method,## __VA_ARGS__)

 return this->type_; 
#undef PM
#undef super
}
yaooc_json_value_class_table_t yaooc_json_value_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_object_class_table,
.type_name_ = (const char*)"yaooc_json_value_t",
.swap = (void(*)(pointer,pointer)) yaooc_json_value_swap,
.type = (yaooc_json_type_t(*)(const_pointer)) yaooc_json_value_type,
.__this_ti__ = (const type_info_t*)&__yaooc_json_value_ti,
};
const type_info_t __yaooc_json_value_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_json_value_t),
.rich_compare_=yaooc_json_value_rich_compare,
.to_stream_=yaooc_json_value_to_stream,
.from_stream_=yaooc_json_value_from_stream,
.default_ctor_=yaooc_json_value_default_ctor,
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
      THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,51,"Attempt to assign non json null to json null"));
    if(this->type_==JSON_UNDEFINED)
      newp(this,yaooc_json_null);
    else if(this->type_ != JSON_NULL)
      THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,51,"Attempt to assign non json null to json null"));
  
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
    THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,52,"Invalid comparison to JSON_NULL"));
    return 0;
  
}
void yaooc_json_null_to_stream(const_pointer __pthis__,ostream_pointer __pstrm__)
{
yaooc_json_null_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__pstrm__;(void)ostrm;


    M(ostrm,printf,"null");
  
}
yaooc_json_null_class_table_t yaooc_json_null_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_json_value_class_table,
.type_name_ = (const char*)"yaooc_json_null_t",
.swap = (void(*)(pointer,pointer)) yaooc_json_null_swap,
.type = (yaooc_json_type_t(*)(const_pointer)) yaooc_json_null_type,
.__this_ti__ = (const type_info_t*)&__yaooc_json_null_ti,
};
const type_info_t __yaooc_json_null_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_json_null_t),
.rich_compare_=yaooc_json_null_rich_compare,
.to_stream_=yaooc_json_null_to_stream,
.from_stream_=NULL,
.default_ctor_=yaooc_json_null_default_ctor,
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


    
    if(src->type_==JSON_BOOL) {
      if(this->type_ == JSON_UNDEFINED)
        newp(this,yaooc_json_bool);
      if(this->type_ != JSON_BOOL)
        THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,53,"Attempt to assign non json bool to json bool"));
      this->bool_=src->bool_;
    } else
      THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,53,"Attempt to assign non json bool to json bool"));
  
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
    THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,54,"Invalid comparison to JSON_BOOL"));
    return 0;
  
}
void yaooc_json_bool_to_stream(const_pointer __pthis__,ostream_pointer __pstrm__)
{
yaooc_json_bool_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__pstrm__;(void)ostrm;


    M(ostrm,printf,"%s",(this->bool_ ? "true" : "false"));
  
}
void yaooc_json_bool_ctor_bool(pointer __pthis,va_list __con_args__){
yaooc_json_bool_pointer this=__pthis;(void)this;
int v = va_arg(__con_args__,int);

call_default_ctor_static(this,yaooc_json_bool);


    this->bool_=v;
  
}
bool yaooc_json_bool_get(const_pointer __pthis__)
{
yaooc_json_bool_const_pointer this=__pthis__;(void)this;
#define super() yaooc_json_bool_parent_class_table->get(this)
#define PM(method,...) CTM((*yaooc_json_bool_parent_class_table),this,method,## __VA_ARGS__)

 return this->bool_; 
#undef PM
#undef super
}
void yaooc_json_bool_set(pointer __pthis__,bool v)
{
yaooc_json_bool_pointer this=__pthis__;(void)this;
#define super() yaooc_json_bool_parent_class_table->set(this,v)
#define PM(method,...) CTM((*yaooc_json_bool_parent_class_table),this,method,## __VA_ARGS__)

 this->bool_ =v; 
#undef PM
#undef super
}
yaooc_json_bool_class_table_t yaooc_json_bool_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_json_value_class_table,
.type_name_ = (const char*)"yaooc_json_bool_t",
.swap = (void(*)(pointer,pointer)) yaooc_json_bool_swap,
.type = (yaooc_json_type_t(*)(const_pointer)) yaooc_json_bool_type,
.__this_ti__ = (const type_info_t*)&__yaooc_json_bool_ti,
.get = (bool(*)(const_pointer)) yaooc_json_bool_get,
.set = (void(*)(pointer,bool)) yaooc_json_bool_set,
};
const type_info_t __yaooc_json_bool_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_json_bool_t),
.rich_compare_=yaooc_json_bool_rich_compare,
.to_stream_=yaooc_json_bool_to_stream,
.from_stream_=NULL,
.default_ctor_=yaooc_json_bool_default_ctor,
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


    if(src->type_==JSON_INTEGER) {
      if(this->type_ == JSON_UNDEFINED)
        newp(this,yaooc_json_integer);
      if(this->type_ != JSON_INTEGER)
        THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,54,"Attempt to assign non json integer to json integer"));
      this->int_=src->int_;
    } else
      THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,54,"Attempt to assign non json integer to json integer"));
  
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
    THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,55,"Invalid comparison to json integer"));
    return 0;
  
}
void yaooc_json_integer_to_stream(const_pointer __pthis__,ostream_pointer __pstrm__)
{
yaooc_json_integer_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__pstrm__;(void)ostrm;


    M(ostrm,printf,"%lld",this->int_);
  
}
void yaooc_json_integer_ctor_int(pointer __pthis,va_list __con_args__){
yaooc_json_integer_pointer this=__pthis;(void)this;
int v = va_arg(__con_args__,int);

call_default_ctor_static(this,yaooc_json_integer);


    this->int_=v;
  
}
int64_t yaooc_json_integer_get(const_pointer __pthis__)
{
yaooc_json_integer_const_pointer this=__pthis__;(void)this;
#define super() yaooc_json_integer_parent_class_table->get(this)
#define PM(method,...) CTM((*yaooc_json_integer_parent_class_table),this,method,## __VA_ARGS__)

 return this->int_; 
#undef PM
#undef super
}
void yaooc_json_integer_set(pointer __pthis__,int64_t v)
{
yaooc_json_integer_pointer this=__pthis__;(void)this;
#define super() yaooc_json_integer_parent_class_table->set(this,v)
#define PM(method,...) CTM((*yaooc_json_integer_parent_class_table),this,method,## __VA_ARGS__)

 this->int_ =v; 
#undef PM
#undef super
}
yaooc_json_integer_class_table_t yaooc_json_integer_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_json_value_class_table,
.type_name_ = (const char*)"yaooc_json_integer_t",
.swap = (void(*)(pointer,pointer)) yaooc_json_integer_swap,
.type = (yaooc_json_type_t(*)(const_pointer)) yaooc_json_integer_type,
.__this_ti__ = (const type_info_t*)&__yaooc_json_integer_ti,
.get = (int64_t(*)(const_pointer)) yaooc_json_integer_get,
.set = (void(*)(pointer,int64_t)) yaooc_json_integer_set,
};
const type_info_t __yaooc_json_integer_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_json_integer_t),
.rich_compare_=yaooc_json_integer_rich_compare,
.to_stream_=yaooc_json_integer_to_stream,
.from_stream_=NULL,
.default_ctor_=yaooc_json_integer_default_ctor,
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


    if(src->type_==JSON_REAL) {
      if(this->type_ == JSON_UNDEFINED)
        newp(this,yaooc_json_real);
      if(this->type_ != JSON_REAL)
        THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,55,"Attempt to assign non json real to json real"));
      this->real_=src->real_;
    } else
      THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,55,"Attempt to assign non json real to json real"));
  
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
    THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,55,"Invalid comparison to json real"));
    return 0;
  
}
void yaooc_json_real_to_stream(const_pointer __pthis__,ostream_pointer __pstrm__)
{
yaooc_json_real_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__pstrm__;(void)ostrm;


    M(ostrm,printf,"%lg",this->real_);
  
}
void yaooc_json_real_ctor_real(pointer __pthis,va_list __con_args__){
yaooc_json_real_pointer this=__pthis;(void)this;
double v = va_arg(__con_args__,double);

call_default_ctor_static(this,yaooc_json_real);


    this->real_=v;
  
}
double yaooc_json_real_get(const_pointer __pthis__)
{
yaooc_json_real_const_pointer this=__pthis__;(void)this;
#define super() yaooc_json_real_parent_class_table->get(this)
#define PM(method,...) CTM((*yaooc_json_real_parent_class_table),this,method,## __VA_ARGS__)

 return this->real_; 
#undef PM
#undef super
}
void yaooc_json_real_set(pointer __pthis__,double v)
{
yaooc_json_real_pointer this=__pthis__;(void)this;
#define super() yaooc_json_real_parent_class_table->set(this,v)
#define PM(method,...) CTM((*yaooc_json_real_parent_class_table),this,method,## __VA_ARGS__)

 this->real_ =v; 
#undef PM
#undef super
}
yaooc_json_real_class_table_t yaooc_json_real_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_json_value_class_table,
.type_name_ = (const char*)"yaooc_json_real_t",
.swap = (void(*)(pointer,pointer)) yaooc_json_real_swap,
.type = (yaooc_json_type_t(*)(const_pointer)) yaooc_json_real_type,
.__this_ti__ = (const type_info_t*)&__yaooc_json_real_ti,
.get = (double(*)(const_pointer)) yaooc_json_real_get,
.set = (void(*)(pointer,double)) yaooc_json_real_set,
};
const type_info_t __yaooc_json_real_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_json_real_t),
.rich_compare_=yaooc_json_real_rich_compare,
.to_stream_=yaooc_json_real_to_stream,
.from_stream_=NULL,
.default_ctor_=yaooc_json_real_default_ctor,
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
      if(this->type_ == JSON_UNDEFINED)
        newp(this,yaooc_json_string);
      if(this->type_ != JSON_STRING)
        THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,56,"Attempt to assign non json string to json string"));
      deletep(this,yaooc_json_string);
      newp(this,yaooc_json_string);
      this->string_=src->string_ ? STRDUP(src->string_) : NULL;
    } else
      THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,56,"Attempt to assign non json string to json string"));
  
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
    THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,53,"Invalid comparison to json string"));
    return 0;
  
}
void yaooc_json_string_to_stream(const_pointer __pthis__,ostream_pointer __pstrm__)
{
yaooc_json_string_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__pstrm__;(void)ostrm;


    if(this->string_)
      M(ostrm,printf,"\"%s\"",this->string_);
    else
      M(ostrm,printf,"(null)");
  
}
void yaooc_json_string_ctor_ccs(pointer __pthis,va_list __con_args__){
yaooc_json_string_pointer this=__pthis;(void)this;
const char* v = va_arg(__con_args__,const char*);

call_default_ctor_static(this,yaooc_json_string);


    this->string_ = v ? STRDUP(v) : NULL;
  
}
void yaooc_json_string_ctor_ccs_size(pointer __pthis,va_list __con_args__){
yaooc_json_string_pointer this=__pthis;(void)this;
const char* v = va_arg(__con_args__,const char*);
size_t n = va_arg(__con_args__,size_t);

call_default_ctor_static(this,yaooc_json_string);


    if(v && n > 0) {
      this->string_ = MALLOC(n+1);
      strncpy(this->string_,v,n);
      this->string_[n]=0;
    }
  
}
const char* yaooc_json_string_get(const_pointer __pthis__)
{
yaooc_json_string_const_pointer this=__pthis__;(void)this;
#define super() yaooc_json_string_parent_class_table->get(this)
#define PM(method,...) CTM((*yaooc_json_string_parent_class_table),this,method,## __VA_ARGS__)

 return this->string_; 
#undef PM
#undef super
}
void yaooc_json_string_set(pointer __pthis__,const char* v)
{
yaooc_json_string_pointer this=__pthis__;(void)this;
#define super() yaooc_json_string_parent_class_table->set(this,v)
#define PM(method,...) CTM((*yaooc_json_string_parent_class_table),this,method,## __VA_ARGS__)


    M(this,clear);
    if(v) this->string_ = STRDUP(v);
  
#undef PM
#undef super
}
void yaooc_json_string_clear(pointer __pthis__)
{
yaooc_json_string_pointer this=__pthis__;(void)this;
#define super() yaooc_json_string_parent_class_table->clear(this)
#define PM(method,...) CTM((*yaooc_json_string_parent_class_table),this,method,## __VA_ARGS__)


    if(this->string_) {
      FREE(this->string_);
      this->string_=NULL;
    }
  
#undef PM
#undef super
}
yaooc_json_string_class_table_t yaooc_json_string_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_json_value_class_table,
.type_name_ = (const char*)"yaooc_json_string_t",
.swap = (void(*)(pointer,pointer)) yaooc_json_string_swap,
.type = (yaooc_json_type_t(*)(const_pointer)) yaooc_json_string_type,
.__this_ti__ = (const type_info_t*)&__yaooc_json_string_ti,
.get = (const char*(*)(const_pointer)) yaooc_json_string_get,
.set = (void(*)(pointer,const char*)) yaooc_json_string_set,
.clear = (void(*)(pointer)) yaooc_json_string_clear,
};
const type_info_t __yaooc_json_string_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_json_string_t),
.rich_compare_=yaooc_json_string_rich_compare,
.to_stream_=yaooc_json_string_to_stream,
.from_stream_=NULL,
.default_ctor_=yaooc_json_string_default_ctor,
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


    if(this->array_) {
      delete(this->array_);
      this->array_=NULL;
    }
  
}
void yaooc_json_array_assign(pointer __pthis__,const_pointer __psrc__)
{
yaooc_json_array_pointer this=__pthis__;(void)this;
yaooc_json_array_const_pointer src=__psrc__;(void)src;


    if(src->type_==JSON_ARRAY) {
      if(this->type_ == JSON_UNDEFINED)
        newp(this,yaooc_json_array);
      if(this->type_!=JSON_ARRAY)
        THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,53,"Attempt to assign non json string to json string"));
      assign_static(this->array_,src->array_,yaooc_json_value_array);
    } else
      THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,53,"Attempt to assign non json string to json string"));
  
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
    THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,54,"Invalid comparison to json array"));
    return 0;
  
}
void yaooc_json_array_to_stream(const_pointer __pthis__,ostream_pointer __pstrm__)
{
yaooc_json_array_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__pstrm__;(void)ostrm;


    M(ostrm,printf,"[");
    if(M(this->array_,size)>0) {
      yaooc_json_value_array_const_iterator i = M(this->array_,cbegin);
      STREAM(ostrm,O_OBJ(yaooc_json_value,*i));
      for(i++;i!=M(this->array_,cend);i++) {
        M(ostrm,printf,",");
        STREAM(ostrm,O_OBJ(yaooc_json_value,*i));
      }
    }
    M(ostrm,printf,"]");
  
}
void yaooc_json_array_insert(pointer __pthis__,pointer v)
{
yaooc_json_array_pointer this=__pthis__;(void)this;
#define super() yaooc_json_array_parent_class_table->insert(this,v)
#define PM(method,...) CTM((*yaooc_json_array_parent_class_table),this,method,## __VA_ARGS__)


    M(this->array_,push_back,v);
  
#undef PM
#undef super
}
size_t yaooc_json_array_size(const_pointer __pthis__)
{
yaooc_json_array_const_pointer this=__pthis__;(void)this;
#define super() yaooc_json_array_parent_class_table->size(this)
#define PM(method,...) CTM((*yaooc_json_array_parent_class_table),this,method,## __VA_ARGS__)


    return M(this->array_,size);
  
#undef PM
#undef super
}
yaooc_json_array_class_table_t yaooc_json_array_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_json_value_class_table,
.type_name_ = (const char*)"yaooc_json_array_t",
.swap = (void(*)(pointer,pointer)) yaooc_json_array_swap,
.type = (yaooc_json_type_t(*)(const_pointer)) yaooc_json_array_type,
.__this_ti__ = (const type_info_t*)&__yaooc_json_array_ti,
.insert = (void(*)(pointer,pointer)) yaooc_json_array_insert,
.size = (size_t(*)(const_pointer)) yaooc_json_array_size,
};
const type_info_t __yaooc_json_array_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_json_array_t),
.rich_compare_=yaooc_json_array_rich_compare,
.to_stream_=yaooc_json_array_to_stream,
.from_stream_=NULL,
.default_ctor_=yaooc_json_array_default_ctor,
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
      if(this->type_ == JSON_UNDEFINED)
        newp(this,yaooc_json_object);
      if(this->type_ != JSON_OBJECT)
        THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,54,"Attempt to assign non json object to json object"));
      assign_static(this->object_,src->object_,yaooc_json_string_value_map);
    } else
      THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,54,"Attempt to assign non json object to json object"));
  
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
    THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,54,"Invalid comparison to json object"));
    return 0;
  
}
void yaooc_json_object_to_stream(const_pointer __pthis__,ostream_pointer __pstrm__)
{
yaooc_json_object_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__pstrm__;(void)ostrm;


    M(ostrm,printf,"{");
    yaooc_json_string_value_map_const_iterator i;
    CFOR_EACH(i,this->object_) {
      STREAM(ostrm,S_OBJ(yaooc_json_string),i->first);
      M(ostrm,printf,":");
      STREAM(ostrm,S_OBJ(yaooc_json_string),i->second);
    }
    M(ostrm,printf,"}");
  
}
void yaooc_json_object_insert(pointer __pthis__,const_pointer key,const_pointer value)
{
yaooc_json_object_pointer this=__pthis__;(void)this;
#define super() yaooc_json_object_parent_class_table->insert(this,key,value)
#define PM(method,...) CTM((*yaooc_json_object_parent_class_table),this,method,## __VA_ARGS__)


      M(this->object_,insert,key,value);
    
#undef PM
#undef super
}
yaooc_json_object_class_table_t yaooc_json_object_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_json_value_class_table,
.type_name_ = (const char*)"yaooc_json_object_t",
.swap = (void(*)(pointer,pointer)) yaooc_json_object_swap,
.type = (yaooc_json_type_t(*)(const_pointer)) yaooc_json_object_type,
.__this_ti__ = (const type_info_t*)&__yaooc_json_object_ti,
.insert = (void(*)(pointer,const_pointer,const_pointer)) yaooc_json_object_insert,
};
const type_info_t __yaooc_json_object_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_json_object_t),
.rich_compare_=yaooc_json_object_rich_compare,
.to_stream_=yaooc_json_object_to_stream,
.from_stream_=NULL,
.default_ctor_=yaooc_json_object_default_ctor,
.dtor_=yaooc_json_object_dtor,
.copy_ctor_=NULL,
.assign_=yaooc_json_object_assign,
.class_table_=(const class_table_t*) &yaooc_json_object_class_table,
.parent_=&__yaooc_json_value_ti
};
const type_info_t* const yaooc_json_object_ti=&__yaooc_json_object_ti;
