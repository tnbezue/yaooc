#include <yaooc/fraction.h>

#include <math.h>

int yaooc_fraction_gcd(int a,int b)
{
  int t;
  while(b!=0) {
    t = b;
    b = a % b;
    a = t;
  }
  return a;
}


double yaooc_fraction_epsilon=5e-7;
void yaooc_fraction_swap(pointer __pthis__,pointer o)
{
yaooc_fraction_pointer this=__pthis__;(void)this;
#define super() yaooc_fraction_parent_class_table->swap(this,o)
#define PM(method,...) CTM((*yaooc_fraction_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_fraction_t* other=o;
      SWAP(int,this->numerator_,other->numerator_);
      SWAP(int,this->denominator_,other->denominator_);
    
#undef PM
#undef super
}
void yaooc_fraction_set(pointer __pthis__,int n,int d)
{
yaooc_fraction_pointer this=__pthis__;(void)this;
#define super() yaooc_fraction_parent_class_table->set(this,n,d)
#define PM(method,...) CTM((*yaooc_fraction_parent_class_table),this,method,## __VA_ARGS__)


      int divisor=yaooc_fraction_gcd(n,d);
      this->numerator_=n/divisor;
      this->denominator_=d/divisor;
    
#undef PM
#undef super
}
void yaooc_fraction_set_mixed(pointer __pthis__,int w,int n,int d)
{
yaooc_fraction_pointer this=__pthis__;(void)this;
#define super() yaooc_fraction_parent_class_table->set_mixed(this,w,n,d)
#define PM(method,...) CTM((*yaooc_fraction_parent_class_table),this,method,## __VA_ARGS__)


      M(this,set,w*d+(w<0 ? -1 : 1)*n,d);
    
#undef PM
#undef super
}
void yaooc_fraction_set_double(pointer __pthis__,double d)
{
yaooc_fraction_pointer this=__pthis__;(void)this;
#define super() yaooc_fraction_parent_class_table->set_double(this,d)
#define PM(method,...) CTM((*yaooc_fraction_parent_class_table),this,method,## __VA_ARGS__)


      int hm2=0,hm1=1,km2=1,km1=0,h=0,k=0;
      double v = d;
      while(true) {
        int a=v;
        h=a*hm1 + hm2;
        k=a*km1 + km2;
        if(fabs(d - (double)h/(double)k) < yaooc_fraction_epsilon)
          break;
        v = 1.0/(v -a);
        hm2=hm1;
        hm1=h;
        km2=km1;
        km1=k;
      }
      if(k<0) {
        k=-k;
        h=-h;
      }
      this->numerator_=h;
      this->denominator_=k;
    
#undef PM
#undef super
}
void yaooc_fraction_plus(pointer __pthis__,yaooc_fraction_t* other)
{
yaooc_fraction_pointer this=__pthis__;(void)this;
#define super() yaooc_fraction_parent_class_table->plus(this,other)
#define PM(method,...) CTM((*yaooc_fraction_parent_class_table),this,method,## __VA_ARGS__)


      M(this,set,this->numerator_*other->denominator_ + other->numerator_*this->denominator_,
          this->denominator_*other->denominator_);
    
#undef PM
#undef super
}
void yaooc_fraction_minus(pointer __pthis__,yaooc_fraction_t* other)
{
yaooc_fraction_pointer this=__pthis__;(void)this;
#define super() yaooc_fraction_parent_class_table->minus(this,other)
#define PM(method,...) CTM((*yaooc_fraction_parent_class_table),this,method,## __VA_ARGS__)


      M(this,set,this->numerator_*other->denominator_ - other->numerator_*this->denominator_,
        this->denominator_*other->denominator_);
    
#undef PM
#undef super
}
void yaooc_fraction_times(pointer __pthis__,yaooc_fraction_t* other)
{
yaooc_fraction_pointer this=__pthis__;(void)this;
#define super() yaooc_fraction_parent_class_table->times(this,other)
#define PM(method,...) CTM((*yaooc_fraction_parent_class_table),this,method,## __VA_ARGS__)


      M(this,set,this->numerator_*other->numerator_,this->denominator_*other->denominator_);
    
#undef PM
#undef super
}
void yaooc_fraction_divided_by(pointer __pthis__,yaooc_fraction_t* other)
{
yaooc_fraction_pointer this=__pthis__;(void)this;
#define super() yaooc_fraction_parent_class_table->divided_by(this,other)
#define PM(method,...) CTM((*yaooc_fraction_parent_class_table),this,method,## __VA_ARGS__)


      M(this,set,this->numerator_*other->denominator_,this->denominator_*other->numerator_);
    
#undef PM
#undef super
}
double yaooc_fraction_to_double(const_pointer __pthis__)
{
yaooc_fraction_const_pointer this=__pthis__;(void)this;
#define super() yaooc_fraction_parent_class_table->to_double(this)
#define PM(method,...) CTM((*yaooc_fraction_parent_class_table),this,method,## __VA_ARGS__)


      return (double)this->numerator_/(double)this->denominator_;
    
#undef PM
#undef super
}
yaooc_fraction_class_table_t yaooc_fraction_class_table ={
.parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
.type_name_ = (const char*) "yaooc_fraction_t",
.swap = (void(*)(pointer,pointer)) yaooc_fraction_swap,
.set = (void(*)(pointer,int,int)) yaooc_fraction_set,
.set_mixed = (void(*)(pointer,int,int,int)) yaooc_fraction_set_mixed,
.set_double = (void(*)(pointer,double)) yaooc_fraction_set_double,
.plus = (void(*)(pointer,yaooc_fraction_t*)) yaooc_fraction_plus,
.minus = (void(*)(pointer,yaooc_fraction_t*)) yaooc_fraction_minus,
.times = (void(*)(pointer,yaooc_fraction_t*)) yaooc_fraction_times,
.divided_by = (void(*)(pointer,yaooc_fraction_t*)) yaooc_fraction_divided_by,
.to_double = (double(*)(const_pointer)) yaooc_fraction_to_double,
};
void yaooc_fraction_default_ctor(pointer __pthis__)
{
yaooc_fraction_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_fraction);



    this->numerator_=0;
    this->denominator_=1;
  
}
void yaooc_fraction_dtor(pointer __pthis__)
{
yaooc_fraction_pointer this=__pthis__;(void)this;


}
void yaooc_fraction_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaooc_fraction_pointer this=__pthis__;(void)this;
yaooc_fraction_const_pointer src=__psrc__;(void)src;


call_default_ctor_static(this,yaooc_fraction);
assign_static(this,src,yaooc_fraction);

}
void yaooc_fraction_assign(pointer __pthis__,const_pointer __psrc__)
{
yaooc_fraction_pointer this=__pthis__;(void)this;
yaooc_fraction_const_pointer src=__psrc__;(void)src;

assign_static(this,src,yaooc_object);
this->numerator_=src->numerator_;
this->denominator_=src->denominator_;

}
const type_info_t __yaooc_fraction_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_fraction_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaooc_fraction_default_ctor,
.dtor_=yaooc_fraction_dtor,
.copy_ctor_=yaooc_fraction_copy_ctor,
.assign_=yaooc_fraction_assign,
.class_table_=(const class_table_t*) &yaooc_fraction_class_table,
.parent_=&__yaooc_object_ti
};
const type_info_t* const yaooc_fraction_ti=&__yaooc_fraction_ti;
