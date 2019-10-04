/* Begin YAOOCPP output */

#include <yaooc/complex.h>
#include <math.h>
#include <ctype.h>

/* Private variables implementation for yaooc_complex */

/* Private methods prototypes for yaooc_complex */

/* Type Info implemmentation for yaooc_complex */
static const double eps=1e-6;
int yaooc_complex_rich_compare(const_pointer p1,const_pointer p2)
{
  yaooc_complex_const_pointer lhs=p1;
  yaooc_complex_const_pointer rhs=p2;
  double lhs_magnitude = lhs->real_*lhs->real_ + lhs->imag_*lhs->imag_;
  double rhs_magnitude = rhs->real_*rhs->real_ + rhs->imag_*rhs->imag_;
  double diff = lhs_magnitude < rhs_magnitude;
  if(diff < eps)
    return 0;
  if(diff < 0)
    return -1;
  return 1;
}

void yaooc_complex_to_stream(const_pointer p,ostream_pointer o)
{
  yaooc_complex_const_pointer this=p;
  yaooc_ostream_pointer ostrm=o;
  M(ostrm,printf,"(%lg %c %lgi)",this->real_,(this->imag_ < 0 ? '-' : '+'),fabs(this->imag_));
}

static int parse_real(const char* str)
{
  int whole=0,fraction=0;
  const char* ptr=str;
  const char *temp=ptr;
  while(isdigit(*ptr)) ptr++;
  if(ptr > temp) {
    whole=1;
  }
  if(*ptr=='.') {
    ptr++;
    temp=ptr;
    while(isdigit(*ptr)) ptr++;
    if(whole || ptr>temp)
      fraction=1;
  }
  if(whole || fraction) {
    if(*ptr=='e' || *ptr=='E') {
      ptr++;
      if(*ptr=='-' || *ptr=='+') ptr++;
      temp=ptr;
      while(isdigit(*ptr)) ptr++;
      if(ptr == temp)
        return 0;
    }
    return ptr-str;
  }
  return 0;
}

// form 1 [+|-]?digit+ws[+|]ws*digit+iws*EOS
static int imaginary_form1(const char* str)
{
  if(*str == '+' || *str == '-') str++;
//  const char* temp=str;
  int n=parse_real(str);
  if(n > 0) {
    str+=n;
    while(*str==' ') str++;
    if(*str == '+' || *str == '-') {
      str++;
      while(*str==' ') str++;
      n=parse_real(str);
      if(n>0) {
        str+=n;
        if(*str == 'i') {
          str++;
          while(*str==' ') str++;
          if(*str == 0)
            return 1;
        }
      }
    }
  }
  return 0;
}

// form2(real part only): [+-]?
static int imaginary_form2(const char* str)
{
  if(*str == '+' || *str == '-') str++;
//  const char* temp=str;
  int n=parse_real(str);
  if(n > 0) {
    str+=n;
    if(*str == 'i') {
      str++;
      while(*str==' ') str++;
      if(*str == 0)
        return 1;
    }
  }
  return 0;
}

static int imaginary_form3(const char* str)
{
  if(*str == '+' || *str == '-') str++;
//  const char* temp=str;
  int n=parse_real(str);
  if(n > 0) {
    str+=n;
    while(*str==' ') str++;
    if(*str == 0)
      return 1;
  }
  return 0;
}

void yaooc_complex_from_stream(pointer p,istream_pointer i)
{
  yaooc_complex_pointer this=p;
  yaooc_istream_pointer istrm=i;
  double r=0,img=0;
  char temp[256],sign;
  int n=-1;
  M(istrm,scanf," (%255[^)])%n",temp,&n);
  if(n>0) {
    temp[n]=0;
    char* ptr=temp;
    while(*ptr==' ') ptr++; // skip spaces
    if(*ptr) {
      if(imaginary_form1(ptr)) {
        sscanf(ptr,"%lg %c %lg",&r,&sign,&img);
        if(sign=='-')
          img=-img;
      } else if(imaginary_form2(ptr)) {
        sscanf(ptr,"%lg",&img);
      } else if(imaginary_form3(ptr)) {
        sscanf(ptr,"%lg",&r);
      } else
        THROW(new_ctor(yaooc_complex_exception,yaooc_complex_exception_ctor_v,"Invalid complex number encountered while reading stream"));
    }
  } else
    THROW(new_ctor(yaooc_complex_exception,yaooc_complex_exception_ctor_v,"Invalid complex number encountered while reading stream"));
  this->real_=r;
  this->imag_=img;
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

void yaooc_complex_from_polar(pointer p,double magnitude,double angle)
{
  yaooc_complex_pointer this=p;
  this->real_=magnitude*cos(angle);
  this->imag_=magnitude*sin(angle);
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
  .from_polar = (void(*)(pointer,double,double)) yaooc_complex_from_polar,
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

