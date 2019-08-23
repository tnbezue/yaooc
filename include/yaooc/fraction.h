#ifndef __FRATION_INCLUDED__
#define __FRATION_INCLUDED__

/* Begin YAOOCPP output */
#include <yaooc/exception.h>
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

/*
  Class Definition for yaooc_fraction_exception
*/
yaooc_class_table(yaooc_fraction_exception) {
  yaooc_exception_class_table_t;
};
#define yaooc_fraction_exception_parent_class_table ((yaooc_exception_class_table_t*)(yaooc_fraction_exception_class_table.parent_class_table_))

yaooc_class_instance(yaooc_fraction_exception) {
  yaooc_exception_class_instance_t;
};

yaooc_class(yaooc_fraction_exception);

/* Type Info Prototypes for yaooc_fraction_exception */
#define yaooc_fraction_exception_default_ctor yaooc_exception_default_ctor
#define yaooc_fraction_exception_dtor yaooc_exception_dtor
#define yaooc_fraction_exception_copy_ctor yaooc_exception_copy_ctor
#define yaooc_fraction_exception_assign yaooc_exception_assign

/* Constructors prototypes for yaooc_fraction_exception */
#define yaooc_fraction_exception_ctor_v yaooc_exception_ctor_v

/* Table prototypes for yaooc_fraction_exception */
#define yaooc_fraction_exception_swap yaooc_exception_swap
#define yaooc_fraction_exception_what yaooc_exception_what

/* Protected prototypes for yaooc_fraction_exception */

/* End YAOOCPP output */


#endif
