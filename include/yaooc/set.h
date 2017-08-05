#ifndef __YAOOC_SET_INCLUDED__
#define __YAOOC_SET_INCLUDED__
#include <stdlib.h>

#include <yaooc/unique_index_array_container.h>

// Constructor
void yaooc_set_ctor(pointer,va_list);

// Member methods
iterator yaooc_set_insert(pointer,const_pointer);
iterator yaooc_set_insert_range(pointer,const_iterator,const_iterator);
/*iterator yaooc_set_erase(pointer,iterator);
iterator yaooc_set_erase_range(pointer,iterator,iterator);
iterator yaooc_set_find(pointer,const_pointer);*/
pointer yaooc_set_sunion(const_pointer,const_pointer);
pointer yaooc_set_sdiff(const_pointer,const_pointer);
//const_iterator yaooc_set_cfind(const_pointer,const_pointer);

#define SET_DEFINITION(T) \
typedef T ## _t* T ## _set_iterator; \
typedef const T ## _t* T ## _set_const_iterator; \
class_table(T ## _set) { \
	yaooc_unique_index_array_container_class_members_t; \
	T ## _set_iterator (*insert)(pointer,const_iterator); \
	T ## _set_iterator (*insert_v)(pointer,T ## _t); \
	T ## _set_iterator (*insert_range)(pointer,const_iterator,const_iterator); \
	T ## _set_iterator (*erase) (pointer,iterator); \
	T ## _set_iterator (*erase_range) (pointer,iterator,iterator); \
	T ## _set_iterator (*find)(pointer,const_iterator); \
	T ## _set_const_iterator (*cfind)(const_pointer,const_iterator); \
	T ## _set_iterator (*begin) (pointer); \
	T ## _set_iterator (*end)(pointer); \
	T ## _set_const_iterator (*cbegin) (const_pointer); \
	T ## _set_const_iterator (*cend)(const_pointer); \
};\
class_instance(T ## _set) \
{\
	yaooc_unique_index_array_container_instance_members_t;\
};\
class(T ## _set);\
ISA_DEFINITION(T ## _set,yaooc_unique_index_array_container)

#define SET_IMPLEMENTATION(T) \
void T ## _set_default_ctor(pointer p) { call_constructor(p,yaooc_set_ctor,T ## _ti); } \
T ## _set_iterator T ## _set_insert_v(pointer p,T ## _t v) { return yaooc_set_insert(p,&v); } \
ISA_IMPLEMENTATION(T ## _set,yaooc_unique_index_array_container) \
T ## _set_class_members_t T ## _set_class_members = \
{\
  { \
    { \
      { \
        { \
          T ## _set_isa, \
          T ## _set_is_descendent, \
          yaooc_index_array_container_swap \
        }, \
        YAOOC_ARRAY_CONTAINER_NEW_METHODS \
      } \
    } \
  }, \
	(T ## _set_iterator (*)(pointer,const_iterator)) yaooc_set_insert, \
	(T ## _set_iterator (*)(pointer,T ## _t)) T ## _set_insert_v, \
	(T ## _set_iterator (*)(pointer,const_iterator,const_iterator)) yaooc_set_insert_range, \
	(T ## _set_iterator (*) (pointer,iterator)) yaooc_unique_index_array_container_erase, \
	(T ## _set_iterator (*) (pointer,iterator,iterator)) yaooc_unique_index_array_container_erase_range, \
	(T ## _set_iterator (*)(pointer,const_iterator)) yaooc_index_array_container_find, \
	(T ## _set_const_iterator (*)(const_pointer,const_iterator)) yaooc_index_array_container_find, \
	(T ## _set_iterator (*) (pointer)) yaooc_array_container_begin, \
	(T ## _set_iterator (*)(pointer)) yaooc_array_container_end, \
	(T ## _set_const_iterator (*) (const_pointer)) yaooc_array_container_begin, \
	(T ## _set_const_iterator (*)(const_pointer)) yaooc_array_container_end \
};\
DEFINE_TYPE_INFO(T ## _set,T ## _set_default_ctor,NULL,NULL,NULL,NULL, \
        &T ## _set_class_members,yaooc_unique_index_array_container)

#endif
