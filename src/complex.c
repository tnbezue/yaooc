/* Begin YAOOCPP output */

#include <yaooc/complex.h>
#include <math.h>

/* Private variables implementation for yaooc_complex */

/* Private methods prototypes for yaooc_complex */

/* Type Info implemmentation for yaooc_complex */
static const double eps=1e-6;
bool yaooc_complex_less_than_compare(const_pointer p1,const_pointer p2)
{
  yaooc_complex_const_pointer lhs=p1;
  yaooc_complex_const_pointer rhs=p2;
  if(fabs(lhs->real_-rhs->real_) > eps)
    return lhs->real_ < rhs->real_;
  if(fabs(lhs->imag_-rhs->imag_) > eps)
    return lhs->imag_ < rhs->imag_;
  return false;
}

void yaooc_complex_to_stream(const_pointer p,ostream_pointer o)
{
  yaooc_complex_const_pointer this=p;
  yaooc_ostream_pointer ostrm=o;
  M(ostrm,printf,"(%lg %c %lgi)",this->real_,(this->imag_ < 0 ? '-' : '+'),fabs(this->imag_));
}

void yaooc_complex_from_stream(pointer p,istream_pointer i)
{
  yaooc_complex_pointer this=p;
  yaooc_istream_pointer istrm=i;
  double r,img;
  int n=-1;
  char sign=' ';
  printf("TTTT%d\n",n);
  M(istrm,scanf,"%*[ \t\r\n]( %lg %1[+-] %lg %*1[i]%*[ ])%n",&r,&sign,&img,&n);
  printf("n is %d and sign is \"%c\"\n",n,sign);
  if(n<0 || (sign != '+' && sign != '-'))
    THROW(new_ctor(yaooc_complex_exception,yaooc_complex_exception_ctor_v,"Invalid complex number encountered while reading stream"));
  this->real_=r;
  this->imag_=(sign=='+' ? 1 : -1)*img;
}

/* Constructors implementation for yaooc_complex */
void yaooc_complex_ctor_r_i(pointer p,va_list args)
{
  yaooc_complex_pointer this=p;
  this->real_ = va_arg(args, double);
  this->imag_ = va_arg(args, double);
}


/* Private methods implementation for yaooc_complex */

/* Protected implementation for yaooc_complex */

/* Table implementation for yaooc_complex */
yaooc_complex_t* yaooc_complex_times_real(pointer p,double d)
{
  yaooc_complex_t* ret=new_copy_static(yaooc_complex,p);
  M(ret,times_real_,d);
  return ret;
}

void yaooc_complex_times_real_(pointer p,double d)
{
  yaooc_complex_pointer this=p;
  this->real_*=d;
  this->imag_*=d;
}

yaooc_complex_t* yaooc_complex_divided_by_real(pointer p,double d)
{
  yaooc_complex_t* ret=new_copy_static(yaooc_complex,p);
  M(ret,divided_by_real_,d);
  return ret;
}

void yaooc_complex_divided_by_real_(pointer p,double d)
{
  yaooc_complex_pointer this=p;
  this->real_/=d;
  this->imag_/=d;
}

yaooc_complex_t* yaooc_complex_plus_complex(pointer p,const_pointer o)
{
  yaooc_complex_t* ret=new_copy_static(yaooc_complex,p);
  M(ret,plus_complex_,o);
  return ret;
}

void yaooc_complex_plus_complex_(pointer p,const_pointer o)
{
  yaooc_complex_pointer this=p;
  yaooc_complex_const_pointer other=o;
  this->real_+=other->real_;
  this->imag_+=other->imag_;
}

yaooc_complex_t* yaooc_complex_minus_complex(pointer p,const_pointer o)
{
  yaooc_complex_t* ret=new_copy_static(yaooc_complex,p);
  M(ret,minus_complex_,o);
  return ret;
}

void yaooc_complex_minus_complex_(pointer p,const_pointer o)
{
  yaooc_complex_pointer this=p;
  yaooc_complex_const_pointer other=o;
  this->real_-=other->real_;
  this->imag_-=other->imag_;
}

yaooc_complex_t* yaooc_complex_times_complex(pointer p,const_pointer o)
{
  yaooc_complex_t* ret=new_copy_static(yaooc_complex,p);
  M(ret,times_complex_,o);
  return ret;
}

void yaooc_complex_times_complex_(pointer p,const_pointer o)
{
  yaooc_complex_pointer this=p;
  yaooc_complex_const_pointer other=o;
  double temp=this->real_*other->real_ - this->imag_*other->imag_;
  this->imag_=this->imag_*other->real_ + this->real_*other->imag_;
  this->real_=temp;
}

yaooc_complex_t* yaooc_complex_divided_by_complex(pointer p,const_pointer o)
{
  yaooc_complex_t* ret=new_copy_static(yaooc_complex,p);
  M(ret,divided_by_complex_,o);
  return ret;
}

void yaooc_complex_divided_by_complex_(pointer p,const_pointer o)
{
  yaooc_complex_pointer this=p;
  yaooc_complex_const_pointer other=o;
  yaooc_complex_t temp=*other;
  temp.imag_=-temp.imag_;
  M(this,times_complex_,&temp);
  M(this,divided_by_real_,other->real_*temp.real_-other->imag_*temp.imag_);
}

double yaooc_complex_magnitude(const_pointer p)
{
  yaooc_complex_const_pointer this=p;
  return sqrt(this->real_*this->real_ + this->imag_*this->imag_);
}

double yaooc_complex_direction(const_pointer p)
{
  yaooc_complex_const_pointer this=p;
  double ret=atan2(this->imag_,this->real_);
  if(ret<0)
    ret += 2*M_PI;
  return ret;
}


/* Class table definition for yaooc_complex */
yaooc_complex_class_table_t yaooc_complex_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
  .type_name_ = (const char*) "yaooc_complex_t",
  .swap = (void(*)(pointer, pointer)) yaooc_complex_swap,
  .times_real = (yaooc_complex_t*(*)(pointer, double)) yaooc_complex_times_real,
  .times_real_ = (void(*)(pointer, double)) yaooc_complex_times_real_,
  .divided_by_real = (yaooc_complex_t*(*)(pointer, double)) yaooc_complex_divided_by_real,
  .divided_by_real_ = (void(*)(pointer, double)) yaooc_complex_divided_by_real_,
  .plus_complex = (yaooc_complex_t*(*)(pointer, const_pointer)) yaooc_complex_plus_complex,
  .plus_complex_ = (void(*)(pointer, const_pointer)) yaooc_complex_plus_complex_,
  .minus_complex = (yaooc_complex_t*(*)(pointer, const_pointer)) yaooc_complex_minus_complex,
  .minus_complex_ = (void(*)(pointer, const_pointer)) yaooc_complex_minus_complex_,
  .times_complex = (yaooc_complex_t*(*)(pointer, const_pointer)) yaooc_complex_times_complex,
  .times_complex_ = (void(*)(pointer, const_pointer)) yaooc_complex_times_complex_,
  .divided_by_complex = (yaooc_complex_t*(*)(pointer, const_pointer)) yaooc_complex_divided_by_complex,
  .divided_by_complex_ = (void(*)(pointer, const_pointer)) yaooc_complex_divided_by_complex_,
  .magnitude = (double(*)(const_pointer)) yaooc_complex_magnitude,
  .direction = (double(*)(const_pointer)) yaooc_complex_direction,
};

/* Type info structure for yaooc_complex */
DEFINE_TYPE_INFO(yaooc_complex,N,N,N,N,Y,Y,Y,Y,yaooc_object);

/* Private variables implementation for yaooc_complex_exception */

/* Private methods prototypes for yaooc_complex_exception */

/* Type Info implemmentation for yaooc_complex_exception */
/* Constructors implementation for yaooc_complex_exception */

/* Private methods implementation for yaooc_complex_exception */

/* Protected implementation for yaooc_complex_exception */

/* Table implementation for yaooc_complex_exception */

/* Class table definition for yaooc_complex_exception */
yaooc_complex_exception_class_table_t yaooc_complex_exception_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_exception_class_table,
  .type_name_ = (const char*) "yaooc_complex_exception_t",
  .swap = (void(*)(pointer, pointer)) yaooc_complex_exception_swap,
  .what = (const char*(*)(const_pointer)) yaooc_complex_exception_what,
};

/* Type info structure for yaooc_complex_exception */
DEFINE_TYPE_INFO(yaooc_complex_exception,N,N,N,N,N,N,N,Y,yaooc_exception);

/* End YAOOCPP output */

