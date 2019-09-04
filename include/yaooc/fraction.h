#ifndef __FRACTION_INCLUDED__
#define __FRACTION_INCLUDED__

/* Begin YAOOCPP output */

#include <yaooc/exception.h>
#include <yaooc/macros.h>
#include <yaooc/stream.h>
#include <yaooc/string.h>

/*
  Class Definition for yaooc_fraction
*/
yaooc_class_table(yaooc_fraction) {
  yaooc_object_class_table_t;
  void (*plus)(pointer, const_pointer);
  void (*minus)(pointer, const_pointer);
  void (*times)(pointer, const_pointer);
  void (*divided_by)(pointer, const_pointer);
  void (*set)(pointer, int64_t, int64_t);
  void (*set_mixed)(pointer, int64_t, int64_t, int64_t);
  double (*to_double)(const_pointer);
  void (*from_double)(pointer, double);
  yaooc_string_t* (*to_s)(const_pointer);
  yaooc_string_t* (*to_mixed_s)(const_pointer);
};
#define yaooc_fraction_parent_class_table ((yaooc_object_class_table_t*)(yaooc_fraction_class_table.parent_class_table_))

yaooc_class_instance(yaooc_fraction) {
  int32_t numerator_;
  int32_t denominator_;
};

yaooc_class(yaooc_fraction);

/* Type Info Prototypes for yaooc_fraction */
void yaooc_fraction_default_ctor(pointer);
#define yaooc_fraction_dtor yaooc_object_dtor
#define yaooc_fraction_copy_ctor yaooc_object_copy_ctor
#define yaooc_fraction_assign yaooc_object_assign
bool yaooc_fraction_less_than_compare(const_pointer,const_pointer);
void yaooc_fraction_to_stream(const_pointer,ostream_pointer);
void yaooc_fraction_from_stream(pointer,istream_pointer);

/* Constructors prototypes for yaooc_fraction */
void yaooc_fraction_ctor_n_d(pointer,va_list);
void yaooc_fraction_ctor_mixed(pointer,va_list);
void yaooc_fraction_ctor_double(pointer,va_list);

/* Table prototypes for yaooc_fraction */
#define yaooc_fraction_swap yaooc_object_swap
void yaooc_fraction_plus(pointer, const_pointer);
void yaooc_fraction_minus(pointer, const_pointer);
void yaooc_fraction_times(pointer, const_pointer);
void yaooc_fraction_divided_by(pointer, const_pointer);
void yaooc_fraction_set(pointer, int64_t, int64_t);
void yaooc_fraction_set_mixed(pointer, int64_t, int64_t, int64_t);
double yaooc_fraction_to_double(const_pointer);
void yaooc_fraction_from_double(pointer, double);
yaooc_string_t* yaooc_fraction_to_s(const_pointer);
yaooc_string_t* yaooc_fraction_to_mixed_s(const_pointer);

/* Protected prototypes for yaooc_fraction */
extern double yaooc_fraction_epsilon;
extern int64_t yaooc_fraction_gcd(int64_t, int64_t);
extern yaooc_fraction_t* yaooc_fraction_plus_fraction(const_pointer, yaooc_fraction_const_pointer);
extern yaooc_fraction_t* yaooc_fraction_minus_fraction(const_pointer, yaooc_fraction_const_pointer);
extern yaooc_fraction_t* yaooc_fraction_times_fraction(const_pointer, yaooc_fraction_const_pointer);
extern yaooc_fraction_t* yaooc_fraction_divided_by_fraction(const_pointer, yaooc_fraction_const_pointer);
//extern void yaooc_fraction_adjust(pointer, int64_t,int64_t);

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
