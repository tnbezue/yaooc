/* Begin YAOOCPP output */

#include <yaooc/fraction.h>
#include <math.h>

/* Private variables implementation for yaooc_fraction */

/* Private methods prototypes for yaooc_fraction */

/* Type Info implemmentation for yaooc_fraction */
void yaooc_fraction_default_ctor(pointer p)
{
  yaooc_fraction_pointer this=p;
  this->numerator_=0;
  this->denominator_=1;
}

bool yaooc_fraction_less_than_compare(const_pointer p1,const_pointer p2)
{
  yaooc_fraction_const_pointer lhs=p1;
  yaooc_fraction_const_pointer rhs=p2;
  return (((int64_t)lhs->numerator_)*((int64_t)rhs->denominator_) - ((int64_t)rhs->numerator_)*((int64_t)lhs->denominator_)) < 0;
}

void yaooc_fraction_to_stream(const_pointer p,ostream_pointer o)
{
  yaooc_fraction_const_pointer this=p;
  yaooc_ostream_pointer ostrm=o;
  M(ostrm,printf,"%d",this->numerator_);
  if(this->denominator_ != 1)
    M(ostrm,printf,"/%d",this->denominator_);
}

void yaooc_fraction_from_stream(pointer p,istream_pointer i)
{
//  yaooc_fraction_pointer this=p;
  yaooc_istream_pointer istrm=i;
  int32_t num=1,dem=1;
  int n = M(istrm,scanf,"%d",&num);
  if(n == 1) {
    if(M(istrm,peek) == '/') {
      char temp[64];
      n=M(istrm,scanf,"/%[0123456789]",&temp);
      if(n==1)
        dem=atoi(temp);
      else
        THROW(new_ctor(yaooc_fraction_exception,yaooc_fraction_exception_ctor_v,"Invalid fraction encountered while reading stream"));
    }
  } else
    THROW(new_ctor(yaooc_fraction_exception,yaooc_fraction_exception_ctor_v,"Invalid fraction encountered while reading stream"));
  yaooc_fraction_set(p,num,dem);
}

/* Constructors implementation for yaooc_fraction */
void yaooc_fraction_ctor_n_d(pointer p,va_list args)
{
  int64_t n = va_arg(args, int32_t);
  int64_t d = va_arg(args, int32_t);
  yaooc_fraction_set(p,n,d);
}

void yaooc_fraction_ctor_mixed(pointer p,va_list args)
{
  int64_t w = va_arg(args, int32_t);
  int64_t n = va_arg(args, int32_t);
  int64_t d = va_arg(args, int32_t);
  yaooc_fraction_set(p,w*d + (w < 0 ? -1 : 1)*n,d);
}

void yaooc_fraction_ctor_double(pointer p,va_list args)
{
  yaooc_fraction_pointer this=p;
  double d = va_arg(args, double);
  M(this,from_double,d);
}


/* Private methods implementation for yaooc_fraction */

/* Protected implementation for yaooc_fraction */
double yaooc_fraction_epsilon=0.000005;
int64_t yaooc_fraction_gcd(int64_t a,int64_t b)
{
  int64_t t;
  while(b!=0) {
    t = b;
    b = a % b;
    a = t;
  }
  return a;
}

yaooc_fraction_t* yaooc_fraction_plus_fraction(const_pointer p,yaooc_fraction_const_pointer b)
{
  yaooc_fraction_t* ret=new_copy_static(yaooc_fraction,p);
  M(ret,plus,b);
  return ret;
}

yaooc_fraction_t* yaooc_fraction_minus_fraction(const_pointer p,yaooc_fraction_const_pointer b)
{
  yaooc_fraction_t* ret=new_copy_static(yaooc_fraction,p);
  M(ret,minus,b);
  return ret;
}

yaooc_fraction_t* yaooc_fraction_times_fraction(const_pointer p,yaooc_fraction_const_pointer b)
{
  yaooc_fraction_t* ret=new_copy_static(yaooc_fraction,p);
  M(ret,times,b);
  return ret;
}

yaooc_fraction_t* yaooc_fraction_divided_by_fraction(const_pointer p,yaooc_fraction_const_pointer b)
{
  yaooc_fraction_t* ret=new_copy_static(yaooc_fraction,p);
  M(ret,divided_by,b);
  return ret;
}


/* Table implementation for yaooc_fraction */
void yaooc_fraction_plus(pointer p,const_pointer other)
{
  yaooc_fraction_pointer this=p;
  yaooc_fraction_const_pointer b=other;
  yaooc_fraction_set(this,((int64_t)this->numerator_)*((int64_t)b->denominator_) + ((int64_t)b->numerator_)*((int64_t)this->denominator_),
              ((int64_t)this->denominator_)*((int64_t)b->denominator_));
}

void yaooc_fraction_minus(pointer p,const_pointer other)
{
  yaooc_fraction_pointer this=p;
  yaooc_fraction_const_pointer b=other;
  yaooc_fraction_set(this,((int64_t)this->numerator_)*((int64_t)b->denominator_) - ((int64_t)b->numerator_)*((int64_t)this->denominator_),
              ((int64_t)this->denominator_)*((int64_t)b->denominator_));
}

void yaooc_fraction_times(pointer p,const_pointer other)
{
  yaooc_fraction_pointer this=p;
  yaooc_fraction_const_pointer b=other;
  yaooc_fraction_set(this,((int64_t)this->numerator_)*((int64_t)b->numerator_),
              ((int64_t)this->denominator_)*((int64_t)b->denominator_));
}

void yaooc_fraction_divided_by(pointer p,const_pointer other)
{
  yaooc_fraction_pointer this=p;
  yaooc_fraction_const_pointer b=other;
  yaooc_fraction_set(this,((int64_t)this->numerator_)*((int64_t)b->denominator_),
              ((int64_t)this->denominator_)*((int64_t)b->numerator_));
}

void yaooc_fraction_set(pointer p,int64_t n,int64_t d)
{
  yaooc_fraction_pointer this=p;
  if(d < 0) {
    n=-n;
    d=-d;
  }
  int64_t divisor=yaooc_fraction_gcd(abs(n),d);
  this->numerator_=n/divisor;
  this->denominator_=d/divisor;
}

void yaooc_fraction_set_mixed(pointer p,int64_t w,int64_t n,int64_t d)
{
  yaooc_fraction_set(p,w*d+(w<0 ? -1 : 1)*n,d);
}

double yaooc_fraction_to_double(const_pointer p)
{
  yaooc_fraction_const_pointer this=p;
  return ((double)this->numerator_)/((double)this->denominator_);
}

void yaooc_fraction_from_double(pointer p,double d)
{
  int sign = d < 0 ? -1 : 1;
  int64_t whole = abs(d);
  double fract=fabs(d)-whole;
  int64_t numerator=0;
  int64_t denominator=1; // Round to next whole number if very close to it
  if(fract > yaooc_fraction_epsilon) {
    // Starting approximation is 1 for numerator and 1/fract for denominator
    // For example, if converting 0.06 to fraction, 1/0.06 = 16.666666667
    // So starting fraction is 1/16
    numerator=1;
    denominator=1/fract+yaooc_fraction_epsilon; // Round to next whole number if very close to it
    while(1) {
      // End if it's close enough to fract
      double value=(double)numerator/(double)denominator;
      double diff=value-fract;
      if(fabs(diff) < yaooc_fraction_epsilon)
        break;
      // The desired fraction is current fraction (numerator/denominator) +/- the difference
      // Convert difference to fraction in the same manner as starting approximation
      // (numerator = 1 and denominator = 1/diff) and add to current fraction.
      // numerator/denominator + 1/dd = (numerator*dd + denominator)/(denominator*dd)
      int64_t dd;
      dd=fabs(1.0/diff)+yaooc_fraction_epsilon; // Round to next whole number if very close to it.
      numerator=numerator*dd+(diff < 0 ? 1 : -1)*denominator;
      denominator*=dd;
    }
  }
  // Reduce fraction by dividing numerator and denominator by greatest common divisor
  yaooc_fraction_set(p,sign*(whole*denominator+numerator),denominator);
}

yaooc_string_t* yaooc_fraction_to_s(const_pointer p)
{
  yaooc_fraction_const_pointer this=p;
  char str[64];
  int np=sprintf(str,"%d",this->numerator_);
  if(this->denominator_!=1)
    sprintf(str+np,"/%d",this->denominator_);
  return new_ctor(yaooc_string,yaooc_string_ctor_ccs,str);
}

yaooc_string_t* yaooc_fraction_to_mixed_s(const_pointer p)
{
  yaooc_fraction_const_pointer this=p;
  yaooc_string_t* ret;
  int32_t whole=this->numerator_/this->denominator_;
  if(whole != 0) {
    int32_t num=this->numerator_-whole*this->denominator_;
    char str[128];
    int np=sprintf(str,"%d",whole);
    if(this->numerator_ != 0)
      sprintf(str+np," %d/%d",num,this->denominator_);
    ret=new_ctor(yaooc_string,yaooc_string_ctor_ccs,str);
  } else
    ret=yaooc_fraction_to_s(this);
  return ret;
}


/* Class table definition for yaooc_fraction */
yaooc_fraction_class_table_t yaooc_fraction_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
  .type_name_ = (const char*) "yaooc_fraction_t",
  .swap = (void(*)(pointer, pointer)) yaooc_fraction_swap,
  .plus = (void(*)(pointer, const_pointer)) yaooc_fraction_plus,
  .minus = (void(*)(pointer, const_pointer)) yaooc_fraction_minus,
  .times = (void(*)(pointer, const_pointer)) yaooc_fraction_times,
  .divided_by = (void(*)(pointer, const_pointer)) yaooc_fraction_divided_by,
  .set = (void(*)(pointer, int64_t, int64_t)) yaooc_fraction_set,
  .set_mixed = (void(*)(pointer, int64_t, int64_t, int64_t)) yaooc_fraction_set_mixed,
  .to_double = (double(*)(const_pointer)) yaooc_fraction_to_double,
  .from_double = (void(*)(pointer, double)) yaooc_fraction_from_double,
  .to_s = (yaooc_string_t*(*)(const_pointer)) yaooc_fraction_to_s,
  .to_mixed_s = (yaooc_string_t*(*)(const_pointer)) yaooc_fraction_to_mixed_s,
};

/* Type info structure for yaooc_fraction */
DEFINE_TYPE_INFO(yaooc_fraction,Y,N,N,N,Y,Y,Y,Y,yaooc_object);

/* Private variables implementation for yaooc_fraction_exception */

/* Private methods prototypes for yaooc_fraction_exception */

/* Type Info implemmentation for yaooc_fraction_exception */
/* Constructors implementation for yaooc_fraction_exception */

/* Private methods implementation for yaooc_fraction_exception */

/* Protected implementation for yaooc_fraction_exception */

/* Table implementation for yaooc_fraction_exception */

/* Class table definition for yaooc_fraction_exception */
yaooc_fraction_exception_class_table_t yaooc_fraction_exception_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_exception_class_table,
  .type_name_ = (const char*) "yaooc_fraction_exception_t",
  .swap = (void(*)(pointer, pointer)) yaooc_fraction_exception_swap,
  .what = (const char*(*)(const_pointer)) yaooc_fraction_exception_what,
};

/* Type info structure for yaooc_fraction_exception */
DEFINE_TYPE_INFO(yaooc_fraction_exception,N,N,N,N,N,N,N,Y,yaooc_exception);

/* End YAOOCPP output */

