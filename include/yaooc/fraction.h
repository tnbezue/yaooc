#ifndef __FRATION_INCLUDED__
#define __FRATION_INCLUDED__

/* Begin YAOOCPP output */

#include <yaooc/macros.h>
#include <yaooc/stream.h>

/*
  Struct Definition for yaooc_fraction
*/
yaooc_pod_struct(yaooc_fraction) {
  long numerator_;
  long denominator_;
};

/* Protected prototypes for yaooc_fraction */
extern void yaooc_fraction_from_double(pointer, double);
extern double yaooc_fraction_to_double(const_pointer);
extern double yaooc_fraction_epsilon;

/* Type Info Prototypes for yaooc_fraction */
#define yaooc_fraction_default_ctor yaooc_do_nothing_default_ctor
#define yaooc_fraction_dtor yaooc_do_nothing_dtor
#define yaooc_fraction_copy_ctor yaooc_do_nothing_copy_ctor
#define yaooc_fraction_assign yaooc_do_nothing_assign
bool yaooc_fraction_less_than_compare(const_pointer,const_pointer);
void yaooc_fraction_to_stream(const_pointer,ostream_pointer);
void yaooc_fraction_from_stream(pointer,istream_pointer);

/* Constructor prototypes for yaooc_fraction */

/* End YAOOCPP output */


#endif
