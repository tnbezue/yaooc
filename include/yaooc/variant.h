#ifndef __VARIANT_INCLUDED__
#define __VARIANT_INCLUDED__

#include <yaooc/base_parser.h>
#include <yaooc/exception.h>
typedef enum { VAR_NONE, VAR_CHAR, VAR_UCHAR, VAR_SHORT, VAR_USHORT, VAR_INT, VAR_UINT, VAR_LONG, VAR_ULONG,
			VAR_DOUBLE,VAR_CHAR_PTR,VAR_VOID_PTR,VAR_OBJECT_PTR} yaooc_variant_type_t;
typedef union {
  char ch_;
  unsigned char uch_;
  short sh_;
  unsigned short ush_;
  int int_;
  unsigned int uint_;
  long long long_;
  unsigned long long ulong_;
  double dbl_;
  char* chr_ptr_;
  void* void_ptr_;
  yaooc_object_t* obj_ptr_;
} __variant_t;

yaooc_class_table(yaooc_variant) {
  yaooc_object_class_table_t;
void (*set)(pointer,yaooc_variant_type_t,const void*);
const void* (*value)(const_pointer);
};
#define yaooc_variant_parent_class_table ((yaooc_object_class_table_t*)(yaooc_variant_class_table.parent_class_table_))

yaooc_class_instance(yaooc_variant) {
__variant_t ;
yaooc_variant_type_t type_;
};

yaooc_class(yaooc_variant);
void yaooc_variant_default_ctor(pointer);
void yaooc_variant_dtor(pointer);
void yaooc_variant_copy_ctor(pointer,const_pointer);
void yaooc_variant_assign(pointer,const_pointer);
 void yaooc_variant_swap(pointer,pointer);
 void yaooc_variant_set(pointer,yaooc_variant_type_t,const void*);
 const void* yaooc_variant_value(const_pointer);

#endif
