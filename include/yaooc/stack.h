#ifndef __YAOOC_STACK_INCLUDED__
#define __YAOOC_STACK_INCLUDED__

#include <yaooc/array_container.h>

pointer yaooc_stack_top(pointer);
const_pointer yaooc_stack_ctop(const_pointer);
void yaooc_stack_push(pointer,const_pointer);
void yaooc_stack_pop(pointer);

#define STACK_DEFINITION(T) \
typedef T ## _t* T ## _stack_iterator; \
typedef const T ## _t* T ## _stack_const_iterator; \
class_table(T ## _stack) {\
  yaooc_array_container_class_members_t; \
  T ## _t* (*top) (pointer); \
  const T ## _t* (*ctop) (const_pointer); \
  void (*push)(pointer,const_pointer); \
  void (*push_v)(pointer,T ## _t); \
  void (*pop)(pointer); \
  T ## _stack_iterator(*begin) (pointer); \
  T ## _stack_iterator(*end) (pointer); \
  T ## _stack_const_iterator(*cbegin) (const_pointer); \
  T ## _stack_const_iterator(*cend) (const_pointer); \
};\
class_instance(T ## _stack) {\
  yaooc_array_container_instance_members_t; \
};\
class(T ## _stack); \
ISA_DEFINITION(T ## _stack,yaooc_array_container)

#define STACK_IMPLEMENTATION(T) \
void T ## _stack_default_ctor(pointer p) { call_constructor(p,yaooc_array_container_ctor,T ## _ti); } \
void T ## _stack_push_v(pointer p,T ## _t v) { yaooc_stack_push(p,&v); } \
ISA_IMPLEMENTATION(T ## _stack,yaooc_array_container) \
T ## _stack_class_members_t T ## _stack_class_members = \
{\
  { \
    { \
      T ## _stack_isa, \
      T ## _stack_is_descendent, \
      yaooc_array_container_swap \
    }, \
    YAOOC_ARRAY_CONTAINER_NEW_METHODS \
  }, \
  (T ## _t* (*) (pointer)) yaooc_stack_top, \
  (const T ## _t* (*) (const_pointer)) yaooc_stack_top, \
  (void (*)(pointer,const_pointer)) yaooc_stack_push, \
  (void (*)(pointer,T ## _t)) T ## _stack_push_v, \
  (void (*)(pointer)) yaooc_stack_pop, \
  (T ## _stack_iterator(*)(pointer)) yaooc_array_container_begin, \
  (T ## _stack_iterator(*)(pointer)) yaooc_array_container_end, \
  (T ## _stack_const_iterator(*)(const_pointer)) yaooc_array_container_begin, \
  (T ## _stack_const_iterator(*)(const_pointer)) yaooc_array_container_end, \
};\
DEFINE_TYPE_INFO(T ## _stack,T ## _stack_default_ctor,NULL,NULL,NULL,NULL, \
        &T ## _stack_class_members,yaooc_array_container)

#endif
