#ifndef __FRACTION_INCLUDED__
#define __FRACTION_INCLUDED__

#include <yaooc/object.h>

#include <yaooc/exception.h>
#include <yaooc/macros.h>
#include <yaooc/stream.h>
#include <yaooc/string.h>
int yaooc_fraction_gcd(int,int);

yaooc_class_table(yaooc_fraction) {
  yaooc_object_class_table_t;
void (*set)(pointer,int,int);
void (*set_mixed)(pointer,int,int,int);
void (*set_double)(pointer,double);
void (*plus)(pointer,yaooc_fraction_t*);
void (*minus)(pointer,yaooc_fraction_t*);
void (*times)(pointer,yaooc_fraction_t*);
void (*divided_by)(pointer,yaooc_fraction_t*);
double (*to_double)(const_pointer);
};
#define yaooc_fraction_parent_class_table ((yaooc_object_class_table_t*)(yaooc_fraction_class_table.parent_class_table_))

yaooc_class_instance(yaooc_fraction) {
int numerator_;
int denominator_;
};

yaooc_class(yaooc_fraction);
void yaooc_fraction_default_ctor(pointer);
void yaooc_fraction_dtor(pointer);
void yaooc_fraction_copy_ctor(pointer,const_pointer);
void yaooc_fraction_assign(pointer,const_pointer);
 void yaooc_fraction_swap(pointer,pointer);
 void yaooc_fraction_set(pointer,int,int);
 void yaooc_fraction_set_mixed(pointer,int,int,int);
 void yaooc_fraction_set_double(pointer,double);
 void yaooc_fraction_plus(pointer,yaooc_fraction_t*);
 void yaooc_fraction_minus(pointer,yaooc_fraction_t*);
 void yaooc_fraction_times(pointer,yaooc_fraction_t*);
 void yaooc_fraction_divided_by(pointer,yaooc_fraction_t*);
 double yaooc_fraction_to_double(const_pointer);
extern  double yaooc_fraction_epsilon;

#endif
