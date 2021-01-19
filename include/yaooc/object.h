#ifndef __OBJECT_INCLUDED__
#define __OBJECT_INCLUDED__
#include <yaooc/new.h>
#include <yaooc/new.h>
void yaooc_pure_virtual(const char* method,const char* cls);

yaooc_class_table(yaooc_object) {
const class_table_t* parent_class_table_;
const char* type_name_;
void (*swap)(pointer,pointer);
};
yaooc_class_without_instance(yaooc_object);
 void yaooc_object_swap(pointer,pointer);
 bool yaooc_object_isa(const_pointer,const char*);
#define TYPE(p) ((yaooc_object_pointer)(p))->class_table_->type_name_
#define ISA(p,o) yaooc_object_isa(p,# o "_t")


#endif
