#include <yaooc/complex.h>
#include <math.h>
#include <ctype.h>


void yaooc_complex_default_ctor(pointer __pthis__)
{
yaooc_complex_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_complex);


this->real_=(double)0;
this->imag_=(double)0;

}
void yaooc_complex_dtor(pointer __pthis__)
{
yaooc_complex_pointer this=__pthis__;(void)this;


}
void yaooc_complex_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaooc_complex_pointer this=__pthis__;(void)this;
yaooc_complex_const_pointer src=__psrc__;(void)src;


call_default_ctor_static(this,yaooc_complex);
assign_static(this,src,yaooc_complex);

}
void yaooc_complex_assign(pointer __pthis__,const_pointer __psrc__)
{
yaooc_complex_pointer this=__pthis__;(void)this;
yaooc_complex_const_pointer src=__psrc__;(void)src;

assign_static(this,src,yaooc_object);
this->real_=src->real_;
this->imag_=src->imag_;

}
void yaooc_complex_to_stream(const_pointer __pthis__,ostream_pointer __pstrm__)
{
yaooc_complex_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__pstrm__;(void)ostrm;

      M(ostrm,printf,"(%lg %c %lgi)",this->real_,(this->imag_ < 0 ? '-' : '+'),fabs(this->imag_));
    
}
void yaooc_complex_ctor_r_i(pointer __pthis,va_list __con_args__){
yaooc_complex_pointer this=__pthis;(void)this;
double r = va_arg(__con_args__,double);
double i = va_arg(__con_args__,double);

call_parent_default_ctor_static(this,yaooc_complex);


      this->real_=r;
      this->imag_=i;
    
}
void yaooc_complex_swap(pointer __pthis__,pointer o)
{
yaooc_complex_pointer this=__pthis__;(void)this;
#define super() yaooc_complex_parent_class_table->swap(this,o)
#define PM(method,...) CTM((*yaooc_complex_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_complex_t* other=o;
      SWAP(double,this->real_,other->real_);
      SWAP(double,this->imag_,other->imag_);
    
#undef PM
#undef super
}
void yaooc_complex_set(pointer __pthis__,double r,double i)
{
yaooc_complex_pointer this=__pthis__;(void)this;
#define super() yaooc_complex_parent_class_table->set(this,r,i)
#define PM(method,...) CTM((*yaooc_complex_parent_class_table),this,method,## __VA_ARGS__)


      this->real_=r;
      this->imag_=i;
    
#undef PM
#undef super
}
void yaooc_complex_set_polar(pointer __pthis__,double magnitude,double angle)
{
yaooc_complex_pointer this=__pthis__;(void)this;
#define super() yaooc_complex_parent_class_table->set_polar(this,magnitude,angle)
#define PM(method,...) CTM((*yaooc_complex_parent_class_table),this,method,## __VA_ARGS__)


      this->real_=magnitude*cos(angle);
      this->imag_=magnitude*sin(angle);
    
#undef PM
#undef super
}
yaooc_complex_t* yaooc_complex_times(pointer __pthis__,yaooc_complex_t* o)
{
yaooc_complex_pointer this=__pthis__;(void)this;
#define super() yaooc_complex_parent_class_table->times(this,o)
#define PM(method,...) CTM((*yaooc_complex_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_complex_t* ret = new_copy_static(yaooc_complex,this);
      M(ret,times_,o);
      return ret;
    
#undef PM
#undef super
}
void yaooc_complex_times_(pointer __pthis__,yaooc_complex_t* other)
{
yaooc_complex_pointer this=__pthis__;(void)this;
#define super() yaooc_complex_parent_class_table->times_(this,other)
#define PM(method,...) CTM((*yaooc_complex_parent_class_table),this,method,## __VA_ARGS__)


      double temp=this->real_*other->real_ - this->imag_*other->imag_;
      this->imag_=this->imag_*other->real_ + this->real_*other->imag_;
      this->real_=temp;
    
#undef PM
#undef super
}
yaooc_complex_t* yaooc_complex_divided_by(pointer __pthis__,yaooc_complex_t* o)
{
yaooc_complex_pointer this=__pthis__;(void)this;
#define super() yaooc_complex_parent_class_table->divided_by(this,o)
#define PM(method,...) CTM((*yaooc_complex_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_complex_t* ret = new_copy_static(yaooc_complex,this);
      M(ret,divided_by_,o);
      return ret;
    
#undef PM
#undef super
}
void yaooc_complex_divided_by_(pointer __pthis__,yaooc_complex_t* o)
{
yaooc_complex_pointer this=__pthis__;(void)this;
#define super() yaooc_complex_parent_class_table->divided_by_(this,o)
#define PM(method,...) CTM((*yaooc_complex_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_complex_t temp = *o;
      temp.imag_=-temp.imag_;
      M(this,times_,&temp);
      double divisor=temp.real_*temp.real_+temp.imag_*temp.imag_;
      this->real_/=divisor;
      this->imag_/=divisor;
    
#undef PM
#undef super
}
yaooc_complex_t* yaooc_complex_plus(pointer __pthis__,yaooc_complex_t* o)
{
yaooc_complex_pointer this=__pthis__;(void)this;
#define super() yaooc_complex_parent_class_table->plus(this,o)
#define PM(method,...) CTM((*yaooc_complex_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_complex_t* ret = new_copy_static(yaooc_complex,this);
      M(ret,plus_,o);
      return ret;
    
#undef PM
#undef super
}
void yaooc_complex_plus_(pointer __pthis__,yaooc_complex_t* o)
{
yaooc_complex_pointer this=__pthis__;(void)this;
#define super() yaooc_complex_parent_class_table->plus_(this,o)
#define PM(method,...) CTM((*yaooc_complex_parent_class_table),this,method,## __VA_ARGS__)


      this->real_+=o->real_;
      this->imag_+=o->imag_;
    
#undef PM
#undef super
}
yaooc_complex_t* yaooc_complex_minus(pointer __pthis__,yaooc_complex_t* o)
{
yaooc_complex_pointer this=__pthis__;(void)this;
#define super() yaooc_complex_parent_class_table->minus(this,o)
#define PM(method,...) CTM((*yaooc_complex_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_complex_t* ret = new_copy_static(yaooc_complex,this);
      M(ret,minus_,o);
      return ret;
    
#undef PM
#undef super
}
void yaooc_complex_minus_(pointer __pthis__,yaooc_complex_t* o)
{
yaooc_complex_pointer this=__pthis__;(void)this;
#define super() yaooc_complex_parent_class_table->minus_(this,o)
#define PM(method,...) CTM((*yaooc_complex_parent_class_table),this,method,## __VA_ARGS__)


      this->real_-=o->real_;
      this->imag_-=o->imag_;
    
#undef PM
#undef super
}
double yaooc_complex_magnitude(const_pointer __pthis__)
{
yaooc_complex_const_pointer this=__pthis__;(void)this;
#define super() yaooc_complex_parent_class_table->magnitude(this)
#define PM(method,...) CTM((*yaooc_complex_parent_class_table),this,method,## __VA_ARGS__)


      return sqrt(this->real_*this->real_ + this->imag_*this->imag_);
    
#undef PM
#undef super
}
double yaooc_complex_direction(const_pointer __pthis__)
{
yaooc_complex_const_pointer this=__pthis__;(void)this;
#define super() yaooc_complex_parent_class_table->direction(this)
#define PM(method,...) CTM((*yaooc_complex_parent_class_table),this,method,## __VA_ARGS__)


      double ret=atan2(this->imag_,this->real_);
      if(ret<0)
        ret += 2*M_PI;
      return ret;
    
#undef PM
#undef super
}
yaooc_complex_class_table_t yaooc_complex_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_object_class_table,
.type_name_ = (const char*)"yaooc_complex_t",
.swap = (void(*)(pointer,pointer)) yaooc_complex_swap,
.set = (void(*)(pointer,double,double)) yaooc_complex_set,
.set_polar = (void(*)(pointer,double,double)) yaooc_complex_set_polar,
.times = (yaooc_complex_t*(*)(pointer,yaooc_complex_t*)) yaooc_complex_times,
.times_ = (void(*)(pointer,yaooc_complex_t*)) yaooc_complex_times_,
.divided_by = (yaooc_complex_t*(*)(pointer,yaooc_complex_t*)) yaooc_complex_divided_by,
.divided_by_ = (void(*)(pointer,yaooc_complex_t*)) yaooc_complex_divided_by_,
.plus = (yaooc_complex_t*(*)(pointer,yaooc_complex_t*)) yaooc_complex_plus,
.plus_ = (void(*)(pointer,yaooc_complex_t*)) yaooc_complex_plus_,
.minus = (yaooc_complex_t*(*)(pointer,yaooc_complex_t*)) yaooc_complex_minus,
.minus_ = (void(*)(pointer,yaooc_complex_t*)) yaooc_complex_minus_,
.magnitude = (double(*)(const_pointer)) yaooc_complex_magnitude,
.direction = (double(*)(const_pointer)) yaooc_complex_direction,
};
const type_info_t __yaooc_complex_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_complex_t),
.rich_compare_=NULL,
.to_stream_=yaooc_complex_to_stream,
.from_stream_=NULL,
.default_ctor_=yaooc_complex_default_ctor,
.dtor_=yaooc_complex_dtor,
.copy_ctor_=yaooc_complex_copy_ctor,
.assign_=yaooc_complex_assign,
.class_table_=(const class_table_t*) &yaooc_complex_class_table,
.parent_=&__yaooc_object_ti
};
const type_info_t* const yaooc_complex_ti=&__yaooc_complex_ti;
