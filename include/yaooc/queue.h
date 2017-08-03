#ifndef __YAOOC_queue_INCLUDED__
#define __YAOOC_queue_INCLUDED__

#include <yaooc/container.h>

pointer yaooc_queue_front(pointer);
const_pointer yaooc_queue_cfront(const_pointer);
pointer yaooc_queue_back(pointer);
const_pointer yaooc_queue_cback(const_pointer);
void yaooc_queue_push(pointer,const_pointer);
void yaooc_queue_pop(pointer);

#define QUEUE_DEFINITION(T) \
typedef T ## _t* T ## _queue_iterator; \
typedef T ## _t* T ## _queue_const_iterator; \
class_table(T ## _queue) {\
  yaooc_container_class_members_t; \
  T ## _t* (*front) (pointer); \
  const T ## _t* (*cfront) (const_pointer); \
  T ## _t* (*back) (pointer); \
  const T ## _t* (*cback) (const_pointer); \
  void (*push)(pointer,const_pointer); \
  void (*pop)(pointer); \
  T ## _queue_iterator(*begin) (pointer); \
  T ## _queue_iterator(*end) (pointer); \
  T ## _queue_const_iterator(*cbegin) (const_pointer); \
  T ## _queue_const_iterator(*cend) (const_pointer); \
};\
class_instance(T ## _queue) {\
  yaooc_container_instance_members_t; \
};\
class(T ## _queue); \
ISA_DEFINITION(T ## _queue,yaooc_container)

#define QUEUE_IMPLEMENTATION(T) \
void T ## _queue_default_ctor(pointer p) { call_constructor(p,yaooc_container_ctor,T ## _ti); } \
ISA_IMPLEMENTATION(T ## _queue,yaooc_container) \
T ## _queue_class_members_t T ## _queue_class_members = \
{\
  { \
    { \
      T ## _queue_isa, \
      T ## _queue_is_descendent, \
      yaooc_container_swap \
    }, \
    YAOOC_CONTAINER_NEW_METHODS \
  }, \
  (T ## _t* (*) (pointer)) yaooc_queue_front, \
  (const T ## _t* (*) (const_pointer)) yaooc_queue_front, \
  (T ## _t* (*) (pointer)) yaooc_queue_back, \
  (const T ## _t* (*) (const_pointer)) yaooc_queue_back ,\
  (void (*)(pointer,const_pointer)) yaooc_queue_push ,\
  (void (*)(pointer)) yaooc_queue_pop, \
  (T ## _queue_iterator(*)(pointer)) yaooc_container_begin, \
  (T ## _queue_iterator(*)(pointer)) yaooc_container_end, \
  (T ## _queue_const_iterator(*)(const_pointer)) yaooc_container_begin, \
  (T ## _queue_const_iterator(*)(const_pointer)) yaooc_container_end \
};\
DEFINE_TYPE_INFO(T ## _queue,T ## _queue_default_ctor,NULL,NULL,NULL,NULL, \
        &T ## _queue_class_members,yaooc_container)

#endif
