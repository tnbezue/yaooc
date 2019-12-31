#include <yaooc/integer.h>
void yaooc_integer_default_ctor(pointer __pthis__)
{
yaooc_integer_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_integer);


this->value_=(long long)0;

}
void yaooc_integer_dtor(pointer __pthis__)
{
yaooc_integer_pointer this=__pthis__;(void)this;


}
void yaooc_integer_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaooc_integer_pointer this=__pthis__;(void)this;
yaooc_integer_const_pointer src=__psrc__;(void)src;


call_default_ctor_static(this,yaooc_integer);
assign_static(this,src,yaooc_integer);

}
void yaooc_integer_assign(pointer __pthis__,const_pointer __psrc__)
{
yaooc_integer_pointer this=__pthis__;(void)this;
yaooc_integer_const_pointer src=__psrc__;(void)src;

assign_static(this,src,yaooc_object);
this->value_=src->value_;

}
int yaooc_integer_rich_compare(const_pointer __plhs__,const_pointer __prhs__)
{
yaooc_integer_const_pointer lhs=__plhs__;(void)lhs;
yaooc_integer_const_pointer rhs=__prhs__;(void)rhs;


    if(lhs->value_<rhs->value_)
      return -1;
    if(lhs->value_>rhs->value_)
      return 1;
    return 0;
  
}
void yaooc_integer_to_stream(const_pointer __pthis__,ostream_pointer __pstrm__)
{
yaooc_integer_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__pstrm__;(void)ostrm;


    M(ostrm,printf,"%" PRId64,this->value_);
  
}
void yaooc_integer_from_stream(pointer __pthis__,ostream_pointer __pstrm__)
{
yaooc_integer_pointer this=__pthis__;(void)this;
yaooc_istream_pointer istrm=__pstrm__;(void)istrm;


    M(istrm,scanf,"%" SCNd64,&this->value_);
  
}
void yaooc_integer_ctor_int(pointer __pthis,va_list __con_args__){
yaooc_integer_pointer this=__pthis;(void)this;
long long v = va_arg(__con_args__,long long);

call_default_ctor_static(this,yaooc_integer);


    M(this,set,v);
  
}
void yaooc_integer_swap(pointer __pthis__,pointer o)
{
yaooc_integer_pointer this=__pthis__;(void)this;
#define super() yaooc_integer_parent_class_table->swap(this,o)
#define PM(method,...) CTM((*yaooc_integer_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_integer_t* other=o;
      SWAP(long long,this->value_,other->value_);
    
#undef PM
#undef super
}
void yaooc_integer_set(pointer __pthis__,long long v)
{
yaooc_integer_pointer this=__pthis__;(void)this;
#define super() yaooc_integer_parent_class_table->set(this,v)
#define PM(method,...) CTM((*yaooc_integer_parent_class_table),this,method,## __VA_ARGS__)


      this->value_=v;
    
#undef PM
#undef super
}
long long yaooc_integer_get(const_pointer __pthis__)
{
yaooc_integer_const_pointer this=__pthis__;(void)this;
#define super() yaooc_integer_parent_class_table->get(this)
#define PM(method,...) CTM((*yaooc_integer_parent_class_table),this,method,## __VA_ARGS__)


      return this->value_;
    
#undef PM
#undef super
}
yaooc_integer_class_table_t yaooc_integer_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_object_class_table,
.type_name_ = (const char*)"yaooc_integer_t",
.swap = (void(*)(pointer,pointer)) yaooc_integer_swap,
.set = (void(*)(pointer,long long)) yaooc_integer_set,
.get = (long long(*)(const_pointer)) yaooc_integer_get,
};
const type_info_t __yaooc_integer_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_integer_t),
.rich_compare_=yaooc_integer_rich_compare,
.to_stream_=yaooc_integer_to_stream,
.from_stream_=yaooc_integer_from_stream,
.default_ctor_=yaooc_integer_default_ctor,
.dtor_=yaooc_integer_dtor,
.copy_ctor_=yaooc_integer_copy_ctor,
.assign_=yaooc_integer_assign,
.class_table_=(const class_table_t*) &yaooc_integer_class_table,
.parent_=&__yaooc_object_ti
};
const type_info_t* const yaooc_integer_ti=&__yaooc_integer_ti;
