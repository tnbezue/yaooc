#ifndef __MEMORY_INCLUDED__
#define __MEMORY_INCLUDED__


#include <yaooc/object.h>

yaooc_struct(yaooc_dynamic_pointer) {
  void* ptr_;
};
void yaooc_dynamic_pointer_default_ctor(pointer);
void yaooc_dynamic_pointer_dtor(pointer);
void yaooc_dynamic_pointer_copy_ctor(pointer,const_pointer);
void yaooc_dynamic_pointer_assign(pointer,const_pointer);
int yaooc_dynamic_pointer_rich_compare(const_pointer,const_pointer);
void yaooc_dynamic_pointer_ctor_ptr(pointer,va_list);

#define yaooc_dynamic_pointer_get(p) ((yaooc_dynamic_pointer_pointer)p)->ptr_;
#define make_dynamic_pointer(p) &(yaooc_dynamic_pointer_t) { .ptr_=p }
#include <yaooc/vector.h>


yaooc_class_table(yaooc_unique_pointer) {
  yaooc_object_class_table_t;
  pointer (*get)(const_pointer);
  pointer (*release)(pointer);
  void (*reset)(pointer,pointer);
};
#define yaooc_unique_pointer_parent_class_table ((yaooc_object_class_table_t*)(yaooc_unique_pointer_class_table.parent_class_table_))

yaooc_class_instance(yaooc_unique_pointer) {
  void* ptr_;
};

yaooc_class(yaooc_unique_pointer);

void yaooc_unique_pointer_default_ctor(pointer);
void yaooc_unique_pointer_dtor(pointer);
void yaooc_unique_pointer_copy_ctor(pointer,const_pointer);
void yaooc_unique_pointer_assign(pointer,const_pointer);
int yaooc_unique_pointer_rich_compare(const_pointer,const_pointer);
void yaooc_unique_pointer_ctor_ptr(pointer,va_list);
void yaooc_unique_pointer_swap(pointer,pointer);
pointer yaooc_unique_pointer_get(const_pointer);
pointer yaooc_unique_pointer_release(pointer);
void yaooc_unique_pointer_reset(pointer,pointer);

#define UNIQUE_POINTER_DEFINITION(T,NAME) \
yaooc_class_table(NAME) \
{ \
  yaooc_object_class_table_t; \
  T ## _pointer (*get)(NAME ## _const_pointer); \
  T ## _pointer (*release)(NAME ## _pointer); \
  void (*reset)(NAME ## _pointer,T ## _pointer); \
}; \
yaooc_class_instance(NAME) \
{ \
  T ## _t* ptr_; \
}; \
yaooc_class(NAME); \
void NAME ## _ctor_ptr(pointer,va_list)

#define UNIQUE_POINTER_IMPLEMENTATION(T,NAME) \
void NAME ## _ctor_ptr(pointer p,va_list args) \
{ call_constructor(p,yaooc_unique_pointer_ctor_ptr,va_arg(args,pointer)); } \
NAME ## _class_table_t NAME ## _class_table = \
{ \
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table, \
  .type_name_ = (const char*) # NAME "_t", \
  .swap = (void(*) (pointer,pointer)) yaooc_unique_pointer_swap, \
  .get = (T ## _pointer (*)(NAME ## _const_pointer))yaooc_unique_pointer_get, \
  .reset = (void (*) (NAME ## _pointer,T ## _pointer)) yaooc_unique_pointer_reset, \
  .release = (T ## _pointer (*)(NAME ## _pointer))yaooc_unique_pointer_release \
}; \
DEFINE_TYPE_INFO(NAME,N,N,N,N,N,N,N,Y,yaooc_unique_pointer)


typedef struct yaooc_counter_s yaooc_counter_t;

yaooc_class_table(yaooc_shared_pointer) {
  yaooc_object_class_table_t;
  pointer (*get)(const_pointer);
  pointer (*release)(pointer);
  void (*reset)(pointer,pointer);
  size_t (*count)(const_pointer);
};
#define yaooc_shared_pointer_parent_class_table ((yaooc_object_class_table_t*)(yaooc_shared_pointer_class_table.parent_class_table_))

yaooc_class_instance(yaooc_shared_pointer) {
  yaooc_counter_t* counter_;
};

yaooc_class(yaooc_shared_pointer);

void yaooc_shared_pointer_default_ctor(pointer);
void yaooc_shared_pointer_dtor(pointer);
void yaooc_shared_pointer_copy_ctor(pointer,const_pointer);
void yaooc_shared_pointer_assign(pointer,const_pointer);
int yaooc_shared_pointer_rich_compare(const_pointer,const_pointer);
void yaooc_shared_pointer_ctor_ptr(pointer,va_list);
void yaooc_shared_pointer_swap(pointer,pointer);
pointer yaooc_shared_pointer_get(const_pointer);
pointer yaooc_shared_pointer_release(pointer);
void yaooc_shared_pointer_reset(pointer,pointer);
size_t yaooc_shared_pointer_count(const_pointer);
void yaooc_shared_pointer_acquire(pointer,yaooc_counter_t*);

#define SHARED_POINTER_DEFINITION(T,NAME) \
yaooc_class_table(NAME) \
{ \
  yaooc_object_class_table_t; \
 T ## _pointer (*get)(NAME ## _const_pointer); \
 T ## _pointer (*release)(NAME ## _pointer); \
  void (*reset)(NAME ## _pointer,T ## _pointer); \
  size_t (*count)(NAME ## _const_pointer); \
}; \
yaooc_class_instance(NAME) { \
 yaooc_counter_t* counter_; \
}; \
yaooc_class(NAME); \
void NAME ## _ctor_ptr(pointer this,va_list args)

#define SHARED_POINTER_IMPLEMENTATION(T,NAME) \
void NAME ## _ctor_ptr(pointer this,va_list args) \
 { call_constructor(this,yaooc_shared_pointer_ctor_ptr,va_arg(args,pointer)); } \
NAME ## _class_table_t NAME ## _class_table = {\
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table, \
  .type_name_ = (const char*) # NAME "_t", \
  .swap = (void (*) (pointer,pointer)) yaooc_shared_pointer_swap, \
  .get = (T ## _pointer (*) (NAME ## _const_pointer)) yaooc_shared_pointer_get, \
  .release = (T ## _pointer (*) (NAME ## _pointer)) yaooc_shared_pointer_release, \
  .reset = (void (*) (NAME ## _pointer,T ## _pointer)) yaooc_shared_pointer_reset, \
  .count = (size_t (*) (NAME ## _const_pointer)) yaooc_shared_pointer_count, \
};\
DEFINE_TYPE_INFO(NAME,N,N,N,N,N,N,N,Y,yaooc_shared_pointer)



#endif
