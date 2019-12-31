#include <yaooc/real.h>
#include <math.h>


void yaooc_real_default_ctor(pointer __pthis__)
{
yaooc_real_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_real);


this->value_=(double)0;

}
void yaooc_real_dtor(pointer __pthis__)
{
yaooc_real_pointer this=__pthis__;(void)this;


}
void yaooc_real_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaooc_real_pointer this=__pthis__;(void)this;
yaooc_real_const_pointer src=__psrc__;(void)src;


call_default_ctor_static(this,yaooc_real);
assign_static(this,src,yaooc_real);

}
void yaooc_real_assign(pointer __pthis__,const_pointer __psrc__)
{
yaooc_real_pointer this=__pthis__;(void)this;
yaooc_real_const_pointer src=__psrc__;(void)src;

assign_static(this,src,yaooc_object);
this->value_=src->value_;

}
int yaooc_real_rich_compare(const_pointer __plhs__,const_pointer __prhs__)
{
yaooc_real_const_pointer lhs=__plhs__;(void)lhs;
yaooc_real_const_pointer rhs=__prhs__;(void)rhs;


    double diff=lhs->value_-rhs->value_;
    if(fabs(diff) < 1e-8)
      return 0;
    if(diff < 0)
      return -1;
    return 1;
  
}
void yaooc_real_ctor_real(pointer __pthis,va_list __con_args__){
yaooc_real_pointer this=__pthis;(void)this;
double v = va_arg(__con_args__,double);

call_parent_default_ctor_static(this,yaooc_real);
this->value_=v;


  
}
void yaooc_real_swap(pointer __pthis__,pointer o)
{
yaooc_real_pointer this=__pthis__;(void)this;
#define super() yaooc_real_parent_class_table->swap(this,o)
#define PM(method,...) CTM((*yaooc_real_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_real_pointer other=o;
      SWAP(double,this->value_,other->value_);
    
#undef PM
#undef super
}
void yaooc_real_set(pointer __pthis__,double v)
{
yaooc_real_pointer this=__pthis__;(void)this;
#define super() yaooc_real_parent_class_table->set(this,v)
#define PM(method,...) CTM((*yaooc_real_parent_class_table),this,method,## __VA_ARGS__)


      this->value_=v;
    
#undef PM
#undef super
}
double yaooc_real_get(const_pointer __pthis__)
{
yaooc_real_const_pointer this=__pthis__;(void)this;
#define super() yaooc_real_parent_class_table->get(this)
#define PM(method,...) CTM((*yaooc_real_parent_class_table),this,method,## __VA_ARGS__)

 return this->value_; 
#undef PM
#undef super
}
yaooc_real_class_table_t yaooc_real_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_object_class_table,
.type_name_ = (const char*)"yaooc_real_t",
.swap = (void(*)(pointer,pointer)) yaooc_real_swap,
.set = (void(*)(pointer,double)) yaooc_real_set,
.get = (double(*)(const_pointer)) yaooc_real_get,
};
const type_info_t __yaooc_real_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_real_t),
.rich_compare_=yaooc_real_rich_compare,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaooc_real_default_ctor,
.dtor_=yaooc_real_dtor,
.copy_ctor_=yaooc_real_copy_ctor,
.assign_=yaooc_real_assign,
.class_table_=(const class_table_t*) &yaooc_real_class_table,
.parent_=&__yaooc_object_ti
};
const type_info_t* const yaooc_real_ti=&__yaooc_real_ti;
