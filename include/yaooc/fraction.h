#ifndef __FRACTION_INCLUDED__
#define __FRACTION_INCLUDED__

/* Begin YAOOCPP output */

#include <yaooc/exception.h>
#include <yaooc/macros.h>
#include <yaooc/stream.h>
#include <yaooc/string.h>

#define YAOOC_FRACTION_DEF_INIT (yaooc_fraction_t) { .class_table_=&yaooc_fraction_class_table, \
      .numerator_=0,.denominator_=1 }
/*
  Class Definition for yaooc_fraction
*/
yaooc_class_table(yaooc_fraction) {
  yaooc_object_class_table_t;
  void (*plus)(pointer, yaooc_fraction_t);
  void (*minus)(pointer, yaooc_fraction_t);
  void (*times)(pointer, yaooc_fraction_t);
  void (*divided_by)(pointer, yaooc_fraction_t);
  void (*set)(pointer, int32_t, int32_t);
  void (*set_mixed)(pointer, int32_t, int32_t, int32_t);
  double (*to_double)(const_pointer);
  void (*from_double)(pointer, double);
  yaooc_fraction_t (*round)(const_pointer,int);
  void (*round_)(pointer,int);
  yaooc_fraction_t (*abs)(const_pointer);
  void (*abs_)(pointer);
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
int yaooc_fraction_rich_compare(const_pointer,const_pointer);
void yaooc_fraction_to_stream(const_pointer,ostream_pointer);
void yaooc_fraction_from_stream(pointer,istream_pointer);

/* Constructors prototypes for yaooc_fraction */
void yaooc_fraction_ctor_n_d(pointer,va_list);
void yaooc_fraction_ctor_mixed(pointer,va_list);
void yaooc_fraction_ctor_double(pointer,va_list);

/* Table prototypes for yaooc_fraction */
void yaooc_fraction_swap(pointer,pointer);
void yaooc_fraction_plus(pointer, yaooc_fraction_t);
void yaooc_fraction_minus(pointer, yaooc_fraction_t);
void yaooc_fraction_times(pointer, yaooc_fraction_t);
void yaooc_fraction_divided_by(pointer, yaooc_fraction_t);
void yaooc_fraction_set(pointer, int32_t, int32_t);
void yaooc_fraction_set_mixed(pointer, int32_t, int32_t, int32_t);
double yaooc_fraction_to_double(const_pointer);
void yaooc_fraction_from_double(pointer, double);
yaooc_fraction_t yaooc_fraction_round(const_pointer,int);
void yaooc_fraction_round_(pointer,int);
yaooc_fraction_t yaooc_fraction_abs(const_pointer);
void yaooc_fraction_abs_(pointer);
yaooc_string_t* yaooc_fraction_to_s(const_pointer);
yaooc_string_t* yaooc_fraction_to_mixed_s(const_pointer);

/* Protected prototypes for yaooc_fraction */
extern double yaooc_fraction_epsilon;
extern int32_t yaooc_fraction_gcd(int32_t, int32_t);
extern yaooc_fraction_t yaooc_fraction_plus_fraction(yaooc_fraction_t, yaooc_fraction_t);
extern yaooc_fraction_t yaooc_fraction_minus_fraction(yaooc_fraction_t, yaooc_fraction_t);
extern yaooc_fraction_t yaooc_fraction_times_fraction(yaooc_fraction_t, yaooc_fraction_t);
extern yaooc_fraction_t yaooc_fraction_divided_by_fraction(yaooc_fraction_t, yaooc_fraction_t);
//extern void yaooc_fraction_adjust(pointer, int32_t,int32_t);

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
