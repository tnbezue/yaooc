/* Begin YAOOCPP output */

#include <yaooc/fraction.h>
#include <math.h>
/* Private variables implementation for yaooc_fraction */

/* Private methods prototypes for yaooc_fraction */

/* Type Info implemmentation for yaooc_fraction */
bool yaooc_fraction_less_than_compare(const_pointer p1,const_pointer p2)
{
  return yaooc_fraction_to_double(p1) < yaooc_fraction_to_double(p2);
}

void yaooc_fraction_to_stream(const_pointer p,ostream_pointer o)
{
  yaooc_fraction_const_pointer this=p;
  yaooc_ostream_pointer ostrm=o;
  M(ostrm,printf,"%ld",this->numerator_);
  if(this->denominator_ != 1)
    M(ostrm,printf,"/%ld",this->denominator_);
}

void yaooc_fraction_from_stream(pointer p,istream_pointer i)
{
  yaooc_fraction_pointer this=p;
  yaooc_istream_pointer istrm=i;
  int n = M(istrm,scanf,"%ld",&this->numerator_);
  if(n == 1) {
    if(M(istrm,peek) == '/') {
      M(istrm,scanf,"/%ld",&this->denominator_);
      yaooc_fraction_from_double(this,yaooc_fraction_to_double(this)); // reduce to lowest terms
    } else
      this->denominator_=1;
  }
}

/* Constructors implementation for yaooc_fraction */

/* Private methods implementation for yaooc_fraction */

/* Protected implementation for yaooc_fraction */
void yaooc_fraction_from_double(pointer p,double d)
{
  yaooc_fraction_pointer this=p;
  this->numerator_=0;
  this->denominator_=1;
  int is_neg = 0;
  if(d < 0) {
    is_neg=1;
    d=-d;
  }
  long whole = d;
  double fract=d-whole;
  while(1) {
    double value=yaooc_fraction_to_double(this);
    if(fabs(value - fract) < yaooc_fraction_epsilon)
      break;
    if(fract < value)
      this->denominator_++;
    else
      this->numerator_++;
  }
  this->numerator_+=whole*this->denominator_;
  if(is_neg) {
    this->numerator_=-this->numerator_;
  }

//    std::cout << integral << " + ";
//    std::cout << numerator << " / " << denominator << std::endl;
}

double yaooc_fraction_to_double(const_pointer p)
{
  yaooc_fraction_const_pointer this=p;
  return (((double)this->numerator_)/(double)this->denominator_);
}

double yaooc_fraction_epsilon=0.00005;

/* Type info structure for yaooc_fraction */
DEFINE_POD_TYPE_INFO(yaooc_fraction,Y,Y,Y)

/* End YAOOCPP output */

