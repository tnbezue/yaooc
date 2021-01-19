#ifndef __MATRIX_INCLUDED__
#define __MATRIX_INCLUDED__
#include <yaooc/new.h>
#include <yaooc/object.h>
#include <yaooc/exception.h>
yaooc_class_table(yaooc_matrix_exception) {
  yaooc_exception_class_table_t;
};
#define yaooc_matrix_exception_parent_class_table ((yaooc_exception_class_table_t*)(yaooc_matrix_exception_class_table.parent_class_table_))

yaooc_class_instance(yaooc_matrix_exception) {
  yaooc_exception_class_instance_t;
};

yaooc_class(yaooc_matrix_exception);
#define yaooc_matrix_exception_ctor_v yaooc_exception_ctor_v
#define yaooc_matrix_exception_swap yaooc_exception_swap
#define yaooc_matrix_exception_what yaooc_exception_what
#define yaooc_matrix_exception_error_code yaooc_exception_error_code
yaooc_class_forward(yaooc_matrix);

yaooc_matrix_pointer yaooc_matrix_identity(unsigned int rows);

yaooc_class_table(yaooc_matrix) {
  yaooc_object_class_table_t;
double (*at)(pointer,unsigned int,unsigned int);
void (*set)(pointer,unsigned int,unsigned int,double);
yaooc_matrix_pointer (*transpose)(const_pointer);
void (*transpose_)(pointer);
yaooc_matrix_pointer (*inverse)(const_pointer);
void (*inverse_)(pointer);
yaooc_matrix_pointer (*times)(const_pointer,yaooc_matrix_const_pointer);
yaooc_matrix_pointer (*plus)(const_pointer,yaooc_matrix_const_pointer);
void (*plus_)(pointer,yaooc_matrix_const_pointer);
yaooc_matrix_pointer (*minus)(const_pointer,yaooc_matrix_const_pointer);
void (*minus_)(pointer,yaooc_matrix_const_pointer);
double (*determinant)(const_pointer);
yaooc_matrix_pointer (*sub_matrix)(const_pointer,unsigned int,unsigned int);
};
#define yaooc_matrix_parent_class_table ((yaooc_object_class_table_t*)(yaooc_matrix_class_table.parent_class_table_))

yaooc_class_instance(yaooc_matrix) {
double** data_;
unsigned int rows_;
unsigned int cols_;
};

yaooc_class(yaooc_matrix);
void yaooc_matrix_default_ctor(pointer);
void yaooc_matrix_dtor(pointer);
void yaooc_matrix_copy_ctor(pointer,const_pointer);
void yaooc_matrix_assign(pointer,const_pointer);
void yaooc_matrix_ctor_rows_cols(pointer,va_list);
 void yaooc_matrix_swap(pointer,pointer);
 double yaooc_matrix_at(pointer,unsigned int,unsigned int);
 void yaooc_matrix_set(pointer,unsigned int,unsigned int,double);
 yaooc_matrix_pointer yaooc_matrix_transpose(const_pointer);
 void yaooc_matrix_transpose_(pointer);
 yaooc_matrix_pointer yaooc_matrix_inverse(const_pointer);
 void yaooc_matrix_inverse_(pointer);
 yaooc_matrix_pointer yaooc_matrix_times(const_pointer,yaooc_matrix_const_pointer);
 yaooc_matrix_pointer yaooc_matrix_plus(const_pointer,yaooc_matrix_const_pointer);
 void yaooc_matrix_plus_(pointer,yaooc_matrix_const_pointer);
 yaooc_matrix_pointer yaooc_matrix_minus(const_pointer,yaooc_matrix_const_pointer);
 void yaooc_matrix_minus_(pointer,yaooc_matrix_const_pointer);
 double yaooc_matrix_determinant(const_pointer);
 yaooc_matrix_pointer yaooc_matrix_sub_matrix(const_pointer,unsigned int,unsigned int);
 void yaooc_matrix_allocate(pointer);

#endif
