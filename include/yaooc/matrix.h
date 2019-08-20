#ifndef __MATRIX_INCLUDED__
#define __MATRIX_INCLUDED__

/* Begin YAOOCPP output */

#include <yaooc/object.h>
#include <yaooc/exception.h>

yaooc_class_forward(yaooc_matrix);
yaooc_matrix_pointer yaooc_matrix_yaooc_matrix_identity(unsigned int);

/*
  Class Definition for yaooc_matrix_exception
*/
yaooc_class_table(yaooc_matrix_exception) {
  yaooc_exception_class_table_t;
};
#define yaooc_matrix_exception_parent_class_table ((yaooc_exception_class_table_t*)(yaooc_matrix_exception_class_table.parent_class_table_))

yaooc_class_instance(yaooc_matrix_exception) {
  yaooc_exception_class_instance_t;
};

yaooc_class(yaooc_matrix_exception);

/* Type Info Prototypes for yaooc_matrix_exception */
#define yaooc_matrix_exception_default_ctor yaooc_exception_default_ctor
#define yaooc_matrix_exception_dtor yaooc_exception_dtor
#define yaooc_matrix_exception_copy_ctor yaooc_exception_copy_ctor
#define yaooc_matrix_exception_assign yaooc_exception_assign

/* Constructors prototypes for yaooc_matrix_exception */
#define yaooc_matrix_exception_ctor_v yaooc_exception_ctor_v

/* Table prototypes for yaooc_matrix_exception */
#define yaooc_matrix_exception_swap yaooc_exception_swap
#define yaooc_matrix_exception_what yaooc_exception_what

/* Protected prototypes for yaooc_matrix_exception */

/*
  Class Definition for yaooc_matrix
*/
yaooc_class_table(yaooc_matrix) {
  yaooc_object_class_table_t;
  unsigned int (*rows)(const_pointer);
  unsigned int (*cols)(const_pointer);
  double (*at)(pointer, unsigned int, unsigned int);
  void (*set)(pointer, unsigned int, unsigned int, double);
  yaooc_matrix_pointer (*transpose)(const_pointer);
  void (*transpose_)(pointer);
  yaooc_matrix_pointer (*inverse)(const_pointer);
  void (*inverse_)(pointer);
  yaooc_matrix_t* (*times)(const_pointer, const_pointer);
  yaooc_matrix_t* (*plus)(const_pointer, const_pointer);
  void (*plus_)(pointer, const_pointer);
  yaooc_matrix_pointer (*minus)(const_pointer, const_pointer);
  void (*minus_)(pointer, const_pointer);
  double (*determinant)(const_pointer);
  yaooc_matrix_t* (*sub_matrix)(const_pointer,unsigned int,unsigned int);
};
#define yaooc_matrix_parent_class_table ((yaooc_object_class_table_t*)(yaooc_matrix_class_table.parent_class_table_))

yaooc_class_instance(yaooc_matrix) {
  yaooc_object_class_instance_t;
  unsigned int rows_;
  unsigned int cols_;
  double** data_;
};

yaooc_class(yaooc_matrix);

/* Type Info Prototypes for yaooc_matrix */
void yaooc_matrix_default_ctor(pointer);
void yaooc_matrix_dtor(pointer);
void yaooc_matrix_copy_ctor(pointer,const_pointer);
void yaooc_matrix_assign(pointer,const_pointer);

/* Constructors prototypes for yaooc_matrix */
void yaooc_matrix_ctor_rows_cols(pointer,va_list);

/* Table prototypes for yaooc_matrix */
void yaooc_matrix_swap(pointer, pointer);
unsigned int yaooc_matrix_rows(const_pointer);
unsigned int yaooc_matrix_cols(const_pointer);
double yaooc_matrix_at(pointer, unsigned int, unsigned int);
void yaooc_matrix_set(pointer, unsigned int, unsigned int, double);
yaooc_matrix_pointer yaooc_matrix_transpose(const_pointer);
void yaooc_matrix_transpose_(pointer);
yaooc_matrix_pointer yaooc_matrix_inverse(const_pointer);
void yaooc_matrix_inverse_(pointer);
yaooc_matrix_pointer yaooc_matrix_times(const_pointer, const_pointer);
yaooc_matrix_pointer yaooc_matrix_plus(const_pointer, const_pointer);
void yaooc_matrix_plus_(pointer, const_pointer);
yaooc_matrix_pointer yaooc_matrix_minus(const_pointer, const_pointer);
void yaooc_matrix_minus_(pointer, const_pointer);
double yaooc_matrix_determinant(const_pointer);
yaooc_matrix_t* yaooc_matrix_sub_matrix(const_pointer,unsigned int,unsigned int);

/* Protected prototypes for yaooc_matrix */

/* End YAOOCPP output */


#endif
