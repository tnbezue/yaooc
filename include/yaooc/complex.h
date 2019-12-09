#ifndef __COMPLEX_INCLUDED__
#define __COMPLEX_INCLUDED__

#include <yaooc/object.h>

#include <yaooc/stream.h>

yaooc_class_table(yaooc_complex) {
  yaooc_object_class_table_t;
void (*set)(pointer,double,double);
void (*set_polar)(pointer,double,double);
yaooc_complex_t* (*times)(pointer,yaooc_complex_t*);
void (*times_)(pointer,yaooc_complex_t*);
yaooc_complex_t* (*divided_by)(pointer,yaooc_complex_t*);
void (*divided_by_)(pointer,yaooc_complex_t*);
yaooc_complex_t* (*plus)(pointer,yaooc_complex_t*);
void (*plus_)(pointer,yaooc_complex_t*);
yaooc_complex_t* (*minus)(pointer,yaooc_complex_t*);
void (*minus_)(pointer,yaooc_complex_t*);
double (*magnitude)(const_pointer);
double (*direction)(const_pointer);
};
#define yaooc_complex_parent_class_table ((yaooc_object_class_table_t*)(yaooc_complex_class_table.parent_class_table_))

yaooc_class_instance(yaooc_complex) {
double real_;
double imag_;
};

yaooc_class(yaooc_complex);
void yaooc_complex_default_ctor(pointer);
void yaooc_complex_dtor(pointer);
void yaooc_complex_copy_ctor(pointer,const_pointer);
void yaooc_complex_assign(pointer,const_pointer);
void yaooc_complex_to_stream(const_pointer,ostream_pointer);
void yaooc_complex_ctor_r_i(pointer,va_list);
 void yaooc_complex_swap(pointer,pointer);
 void yaooc_complex_set(pointer,double,double);
 void yaooc_complex_set_polar(pointer,double,double);
 yaooc_complex_t* yaooc_complex_times(pointer,yaooc_complex_t*);
 void yaooc_complex_times_(pointer,yaooc_complex_t*);
 yaooc_complex_t* yaooc_complex_divided_by(pointer,yaooc_complex_t*);
 void yaooc_complex_divided_by_(pointer,yaooc_complex_t*);
 yaooc_complex_t* yaooc_complex_plus(pointer,yaooc_complex_t*);
 void yaooc_complex_plus_(pointer,yaooc_complex_t*);
 yaooc_complex_t* yaooc_complex_minus(pointer,yaooc_complex_t*);
 void yaooc_complex_minus_(pointer,yaooc_complex_t*);
 double yaooc_complex_magnitude(const_pointer);
 double yaooc_complex_direction(const_pointer);

#endif
