#ifndef __COMPLEX_INCLUDED__
#define __COMPLEX_INCLUDED__

/* Begin YAOOCPP output */

#include <yaooc/object.h>
#include <yaooc/stream.h>
/*
  Class Definition for yaooc_complex
*/
yaooc_class_table(yaooc_complex) {
  yaooc_object_class_table_t;
  yaooc_complex_t* (*times_real)(pointer, double);
  void (*times_real_)(pointer, double);
  yaooc_complex_t* (*divided_by_real)(pointer, double);
  void (*divided_by_real_)(pointer, double);
  yaooc_complex_t* (*plus_complex)(pointer, const_pointer);
  void (*plus_complex_)(pointer, const_pointer);
  yaooc_complex_t* (*minus_complex)(pointer, const_pointer);
  void (*minus_complex_)(pointer, const_pointer);
  yaooc_complex_t* (*times_complex)(pointer, const_pointer);
  void (*times_complex_)(pointer, const_pointer);
  yaooc_complex_t* (*divided_by_complex)(pointer, const_pointer);
  void (*divided_by_complex_)(pointer, const_pointer);
  double (*magnitude)(const_pointer);
  double (*direction)(const_pointer);
  void (*from_polar)(pointer,double,double);
};
#define yaooc_complex_parent_class_table ((yaooc_object_class_table_t*)(yaooc_complex_class_table.parent_class_table_))

yaooc_class_instance(yaooc_complex) {
  double real_;
  double imag_;
};

yaooc_class(yaooc_complex);

/* Type Info Prototypes for yaooc_complex */
#define yaooc_complex_default_ctor yaooc_object_default_ctor
#define yaooc_complex_dtor yaooc_object_dtor
#define yaooc_complex_copy_ctor yaooc_object_copy_ctor
#define yaooc_complex_assign yaooc_object_assign
bool yaooc_complex_less_than_compare(const_pointer,const_pointer);
void yaooc_complex_to_stream(const_pointer,ostream_pointer);
void yaooc_complex_from_stream(pointer,istream_pointer);

/* Constructors prototypes for yaooc_complex */
void yaooc_complex_ctor_r_i(pointer,va_list);

/* Table prototypes for yaooc_complex */
#define yaooc_complex_swap yaooc_object_swap
yaooc_complex_t* yaooc_complex_times_real(pointer, double);
void yaooc_complex_times_real_(pointer, double);
yaooc_complex_t* yaooc_complex_divided_by_real(pointer, double);
void yaooc_complex_divided_by_real_(pointer, double);
yaooc_complex_t* yaooc_complex_plus_complex(pointer, const_pointer);
void yaooc_complex_plus_complex_(pointer, const_pointer);
yaooc_complex_t* yaooc_complex_minus_complex(pointer, const_pointer);
void yaooc_complex_minus_complex_(pointer, const_pointer);
yaooc_complex_t* yaooc_complex_times_complex(pointer, const_pointer);
void yaooc_complex_times_complex_(pointer, const_pointer);
yaooc_complex_t* yaooc_complex_divided_by_complex(pointer, const_pointer);
void yaooc_complex_divided_by_complex_(pointer, const_pointer);
double yaooc_complex_magnitude(const_pointer);
double yaooc_complex_direction(const_pointer);
void yaooc_complex_from_polar(pointer,double,double);

/* Protected prototypes for yaooc_complex */

/*
  Class Definition for yaooc_complex_exception
*/
yaooc_class_table(yaooc_complex_exception) {
  yaooc_exception_class_table_t;
};
#define yaooc_complex_exception_parent_class_table ((yaooc_exception_class_table_t*)(yaooc_complex_exception_class_table.parent_class_table_))

yaooc_class_instance(yaooc_complex_exception) {
  yaooc_exception_class_instance_t;
};

yaooc_class(yaooc_complex_exception);

/* Type Info Prototypes for yaooc_complex_exception */
#define yaooc_complex_exception_default_ctor yaooc_exception_default_ctor
#define yaooc_complex_exception_dtor yaooc_exception_dtor
#define yaooc_complex_exception_copy_ctor yaooc_exception_copy_ctor
#define yaooc_complex_exception_assign yaooc_exception_assign

/* Constructors prototypes for yaooc_complex_exception */
#define yaooc_complex_exception_ctor_v yaooc_exception_ctor_v

/* Table prototypes for yaooc_complex_exception */
#define yaooc_complex_exception_swap yaooc_exception_swap
#define yaooc_complex_exception_what yaooc_exception_what

/* Protected prototypes for yaooc_complex_exception */

/* End YAOOCPP output */


#endif
