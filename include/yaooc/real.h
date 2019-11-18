#ifndef __REAL_INCLUDED__
#define __REAL_INCLUDED__


#include <yaooc/object.h>

yaooc_class_table(yaooc_real) {
  yaooc_object_class_table_t;
  void (*set)(pointer,double);
  double (*get)(const_pointer);
};
#define yaooc_real_parent_class_table ((yaooc_object_class_table_t*)(yaooc_real_class_table.parent_class_table_))

yaooc_class_instance(yaooc_real) {
  double value_;
};

yaooc_class(yaooc_real);

void yaooc_real_default_ctor(pointer);
void yaooc_real_dtor(pointer);
void yaooc_real_copy_ctor(pointer,const_pointer);
void yaooc_real_assign(pointer,const_pointer);
int yaooc_real_rich_compare(const_pointer,const_pointer);
void yaooc_real_ctor_real(pointer,va_list);
void yaooc_real_swap(pointer,pointer);
void yaooc_real_set(pointer,double);
double yaooc_real_get(const_pointer);

#endif
