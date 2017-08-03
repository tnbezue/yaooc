#ifndef __VECTOR_INCLUDED__
#define __VECTOR_INCLUDED__

#include <yaooc/container.h>

// Constructors
void yaooc_vector_ctor(pointer,va_list);

// Member functions
iterator yaooc_vector_push_back(pointer this,const_pointer v);
void yaooc_vector_pop_back(pointer this);
iterator yaooc_vector_front(pointer this);
iterator yaooc_vector_back(pointer this);

#define VECTOR_DEFINITION(T) \
typedef T ## _t* T ## _vector_iterator; \
typedef const T ## _t* T ## _vector_const_iterator; \
class_table(T ##_vector) \
{ \
  yaooc_container_class_members_t; \
	T ## _vector_iterator (*push_back)(pointer,const_pointer); \
  T ## _vector_iterator (*push_back_v)(pointer,T ## _t); \
	void (*pop_back)(pointer); \
	T ## _vector_iterator (*insert)(pointer,const_iterator,const_pointer); \
	T ## _vector_iterator (*insert_v)(pointer,const_iterator,T ## _t); \
	T ## _vector_iterator (*insert_range)(pointer,const_iterator,const_iterator,const_iterator); \
	T ## _vector_iterator (*front) (pointer); \
	T ## _vector_const_iterator (*cfront) (const_pointer); \
	T ## _vector_iterator (*back) (pointer); \
	T ## _vector_const_iterator (*cback) (const_pointer); \
  T ## _vector_iterator (*at)(pointer,size_t); \
  T ## _vector_const_iterator (*cat) (const_pointer,size_t); \
	void (*resize)(pointer,size_t,const_pointer); \
	void (*shrink_to_fit)(pointer); \
	T ## _vector_iterator (*erase) (pointer,iterator); \
	T ## _vector_iterator (*erase_range) (pointer,iterator,iterator); \
  T ## _vector_iterator (*begin)(pointer); \
  T ## _vector_iterator (*end)(pointer); \
  T ## _vector_const_iterator (*cbegin)(const_pointer); \
  T ## _vector_const_iterator (*cend)(const_pointer); \
};\
class_instance(T ##_vector) \
{ \
	yaooc_container_instance_members_t; \
}; \
class(T ##_vector);\
ISA_DEFINITION(T ## _vector,yaooc_container)

#define VECTOR_IMPLEMENTATION(T) \
void T ## _vector_default_ctor(pointer p) { call_constructor(p,yaooc_vector_ctor,T ## _ti); } \
T ## _vector_iterator T ## _vector_push_back_v(pointer p,T ## _t v) { return yaooc_vector_push_back(p,&v); } \
T ## _vector_iterator T ## _vector_insert_v(pointer p,const_iterator pos,T ## _t v) { return yaooc_container_insert(p,pos,&v); } \
ISA_IMPLEMENTATION(T ## _vector,yaooc_container) \
T ## _vector_class_members_t T ## _vector_class_members = \
{ \
  { \
    { \
      T ## _vector_isa, \
      T ## _vector_is_descendent, \
      yaooc_container_swap \
    }, \
    YAOOC_CONTAINER_NEW_METHODS \
  }, \
  (T ## _vector_iterator (*)(pointer,const_pointer)) yaooc_vector_push_back, \
  (T ## _vector_iterator (*)(pointer,T ## _t)) T ## _vector_push_back_v, \
	(void (*)(pointer)) yaooc_vector_pop_back, \
	(T ## _vector_iterator (*)(pointer,const_iterator,const_pointer)) yaooc_container_insert, \
	(T ## _vector_iterator (*)(pointer,const_iterator,T ## _t)) T ## _vector_insert_v, \
	(T ## _vector_iterator (*)(pointer,const_iterator,const_iterator,const_iterator)) yaooc_container_insert_range, \
	(T ## _vector_iterator (*) (pointer)) yaooc_vector_front, \
	(T ## _vector_const_iterator (*) (const_pointer)) yaooc_vector_front, \
	(T ## _vector_iterator (*) (pointer)) yaooc_vector_back, \
	(T ## _vector_const_iterator (*) (const_pointer)) yaooc_vector_back, \
  (T ## _vector_iterator (*)(pointer,size_t)) yaooc_container_at, \
  (T ## _vector_const_iterator (*) (const_pointer,size_t)) yaooc_container_at, \
	(void (*)(pointer,size_t,const_pointer)) yaooc_container_resize, \
	(void (*)(pointer)) yaooc_container_shrink_to_fit, \
	(T ## _vector_iterator (*) (pointer,iterator)) yaooc_container_erase, \
	(T ## _vector_iterator (*) (pointer,iterator,iterator)) yaooc_container_erase_range, \
  (T ## _vector_iterator (*)(pointer)) yaooc_container_begin, \
  (T ## _vector_iterator (*)(pointer)) yaooc_container_end, \
  (T ## _vector_const_iterator (*)(const_pointer)) yaooc_container_begin, \
  (T ## _vector_const_iterator (*)(const_pointer)) yaooc_container_end \
}; \
DEFINE_TYPE_INFO(T ## _vector,T ## _vector_default_ctor,NULL,NULL,NULL,NULL, \
    &T ## _vector_class_members,yaooc_container)

#define VECTOR(T) \
VECTOR_DEFINITION(T) \
VECTOR_IMPLEMENTATION(T)

#endif
