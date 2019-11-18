#ifndef __INTEGER_INCLUDED__
#define __INTEGER_INCLUDED__


#include <yaooc/object.h>


#include <yaooc/stream.h>

yaooc_class_table(yaooc_integer) {
  yaooc_object_class_table_t;
  void (*set)(pointer,long long);
  long long (*get)(const_pointer);
};
#define yaooc_integer_parent_class_table ((yaooc_object_class_table_t*)(yaooc_integer_class_table.parent_class_table_))

yaooc_class_instance(yaooc_integer) {
  long long value_;
};

yaooc_class(yaooc_integer);

void yaooc_integer_default_ctor(pointer);
void yaooc_integer_dtor(pointer);
void yaooc_integer_copy_ctor(pointer,const_pointer);
void yaooc_integer_assign(pointer,const_pointer);
int yaooc_integer_rich_compare(const_pointer,const_pointer);
void yaooc_integer_to_stream(const_pointer,ostream_pointer);
void yaooc_integer_from_stream(pointer,ostream_pointer);
void yaooc_integer_ctor_int(pointer,va_list);
void yaooc_integer_swap(pointer,pointer);
void yaooc_integer_set(pointer,long long);
long long yaooc_integer_get(const_pointer);

#endif
