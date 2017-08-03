#ifndef __YAOOC_ORDERED_SET_INCLUDED__
#define __YAOOC_ORDERED_SET_INCLUDED__
#include <stdlib.h>

#include <yaooc/unique_ordered_container.h>

// Constructor
void yaooc_ordered_set_ctor(pointer,va_list);

// Member methods
iterator yaooc_ordered_set_insert(pointer,const_pointer);
iterator yaooc_ordered_set_insert_range(pointer,const_iterator,const_iterator);
/*iterator yaooc_ordered_set_erase(pointer,iterator);
iterator yaooc_ordered_set_erase_range(pointer,iterator,iterator);
iterator yaooc_ordered_set_find(pointer,const_pointer);*/
pointer yaooc_ordered_set_sunion(const_pointer,const_pointer);
pointer yaooc_ordered_set_sdiff(const_pointer,const_pointer);

#define ORDERED_SET_DEFINITION(T) \
typedef T ## _t* T ## _ordered_set_iterator; \
typedef const T ## _t* T ## _ordered_set_const_iterator; \
class_table(T ## _ordered_set) { \
	yaooc_unique_ordered_container_class_members_t; \
	T ## _ordered_set_iterator (*insert)(pointer,const_iterator); \
	T ## _ordered_set_iterator (*insert_v)(pointer,T ## _t); \
	T ## _ordered_set_iterator (*insert_range)(pointer,const_iterator,const_iterator); \
	T ## _ordered_set_iterator (*erase) (pointer,iterator); \
	T ## _ordered_set_iterator (*erase_range) (pointer,iterator,iterator); \
	T ## _ordered_set_iterator (*find)(pointer,const_iterator); \
	T ## _ordered_set_iterator (*find_v)(pointer,T ## _t); \
	T ## _ordered_set_const_iterator (*cfind)(const_pointer,const_iterator); \
	T ## _ordered_set_const_iterator (*cfind_v)(const_pointer,T ## _t); \
	T ## _ordered_set_iterator (*begin) (pointer); \
	T ## _ordered_set_iterator (*end)(pointer); \
	T ## _ordered_set_const_iterator (*cbegin) (const_pointer); \
	T ## _ordered_set_const_iterator (*cend)(const_pointer); \
};\
class_instance(T ## _ordered_set) \
{\
	yaooc_unique_ordered_container_instance_members_t;\
};\
class(T ## _ordered_set); \
ISA_DEFINITION(T ## _ordered_set,yaooc_unique_ordered_container)

#define ORDERED_SET_IMPLEMENTATION(T) \
void T ## _ordered_set_default_ctor(pointer p) { call_constructor(p,yaooc_ordered_set_ctor,T ## _ti); } \
T ## _ordered_set_iterator T ## _ordered_set_insert_v(pointer p,T ## _t v) { return yaooc_ordered_set_insert(p,&v); } \
T ## _ordered_set_iterator T ## _ordered_set_find_v(pointer p,T ## _t v) { return yaooc_ordered_container_find(p,&v); } \
T ## _ordered_set_const_iterator T ## _ordered_set_cfind_v(const_pointer p,T ## _t v) { return yaooc_ordered_container_find(p,&v); } \
ISA_IMPLEMENTATION(T ## _ordered_set,yaooc_unique_ordered_container) \
T ## _ordered_set_class_members_t T ## _ordered_set_class_members = \
{\
  { \
    { \
      { \
        { \
          T ## _ordered_set_isa, \
          T ## _ordered_set_is_descendent, \
          yaooc_container_swap \
        }, \
        YAOOC_CONTAINER_NEW_METHODS \
      } \
    } \
  }, \
	(T ## _ordered_set_iterator (*)(pointer,const_iterator)) yaooc_ordered_set_insert, \
	(T ## _ordered_set_iterator (*)(pointer,T ## _t)) T ## _ordered_set_insert_v, \
	(T ## _ordered_set_iterator (*)(pointer,const_iterator,const_iterator)) yaooc_ordered_set_insert_range, \
	(T ## _ordered_set_iterator (*) (pointer,iterator)) yaooc_unique_ordered_container_erase, \
	(T ## _ordered_set_iterator (*) (pointer,iterator,iterator)) yaooc_unique_ordered_container_erase_range, \
	(T ## _ordered_set_iterator (*)(pointer,const_iterator)) yaooc_ordered_container_find, \
	(T ## _ordered_set_iterator (*)(pointer,T ## _t)) T ## _ordered_set_find_v, \
	(T ## _ordered_set_const_iterator (*)(const_pointer,const_iterator)) yaooc_ordered_container_find, \
	(T ## _ordered_set_const_iterator (*)(const_pointer,T ## _t)) T ## _ordered_set_cfind_v, \
	(T ## _ordered_set_iterator (*) (pointer)) yaooc_container_begin, \
	(T ## _ordered_set_iterator (*)(pointer)) yaooc_container_end, \
	(T ## _ordered_set_const_iterator (*) (const_pointer)) yaooc_container_begin, \
	(T ## _ordered_set_const_iterator (*)(const_pointer)) yaooc_container_end \
};\
DEFINE_TYPE_INFO(T ## _ordered_set,T ## _ordered_set_default_ctor,NULL,NULL,NULL,NULL, \
      &T ## _ordered_set_class_members,yaooc_unique_ordered_container)

#endif
