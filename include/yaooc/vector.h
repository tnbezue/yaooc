/*
		Copyright (C) 2016-2019  by Terry N Bezue

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef __VECTOR_INCLUDED__
#define __VECTOR_INCLUDED__

#include <yaooc/array_container.h>

// Constructors
void yaooc_vector_ctor_ti(pointer,va_list);

// Member functions
iterator yaooc_vector_push_back(pointer this,const_pointer v);
void yaooc_vector_pop_back(pointer this);
iterator yaooc_vector_back(pointer this);

#define VECTOR_DEFINITION(T,NAME) \
typedef T ## _t* NAME ## _iterator; \
typedef const T ## _t* NAME ## _const_iterator; \
yaooc_class_table(NAME) \
{ \
  yaooc_array_container_class_table_t; \
  NAME ## _iterator (*at)(const_pointer,size_t); \
  NAME ## _iterator (*push_back)(pointer,const T ## _t*); \
	void (*pop_back)(pointer); \
	NAME ## _iterator (*insert)(pointer,const_iterator,const T ## _t*); \
  NAME ## _iterator (*insertn)(pointer,const_iterator,size_t,const T ## _t*); \
	NAME ## _iterator (*insert_range)(pointer,const_iterator,const_iterator,const_iterator); \
	NAME ## _iterator (*erase) (pointer,iterator); \
	NAME ## _iterator (*erase_range) (pointer,iterator,iterator); \
  size_t (*erase_value) (pointer,const_pointer); \
  void (*reserve) (pointer,size_t); \
	NAME ## _iterator (*front) (pointer); \
	NAME ## _iterator (*back) (pointer); \
	void (*resize)(pointer,size_t); \
	void (*resize_value)(pointer,size_t,const_pointer); \
	void (*shrink_to_fit)(pointer); \
  void (*clear)(pointer); \
};\
yaooc_class_instance(NAME) \
{ \
	yaooc_array_container_class_instance_t; \
}; \
yaooc_class(NAME);\

#define VECTOR_IMPLEMENTATION(T,NAME) \
void NAME ## _default_ctor(pointer p) { call_constructor(p,yaooc_array_container_ctor_ti,T ## _ti); } \
NAME ## _class_table_t NAME ## _class_table = \
{ \
  .parent_class_table_ = (const class_table_t*) &yaooc_array_container_class_table, \
  .type_name_ = (const char*) #NAME "_t", \
  .swap = (void (*)(pointer,pointer)) yaooc_array_container_swap, \
  .increase_capacity = (bool (*) (pointer,size_t)) yaooc_array_container_increase_capacity, \
  .size_needed = (size_t (*)(const_pointer,size_t)) yaooc_array_container_size_needed, \
  .size = (size_t (*)(const_pointer)) yaooc_array_container_size, \
  .capacity = (size_t (*)(const_pointer)) yaooc_array_container_capacity, \
  .empty = (bool (*)(const_pointer)) yaooc_array_container_empty, \
  .begin = (iterator (*)(pointer)) yaooc_array_container_begin, \
  .end = (iterator (*)(pointer)) yaooc_array_container_end, \
  .cbegin = (const_iterator (*)(const_pointer)) yaooc_array_container_begin, \
  .cend = (const_iterator (*)(const_pointer)) yaooc_array_container_end, \
  .at = (NAME ## _iterator (*)(const_pointer,size_t)) yaooc_array_container_at, \
  .push_back = (NAME ## _iterator (*)(pointer,const T ## _t*)) yaooc_vector_push_back, \
	.pop_back = (void (*)(pointer)) yaooc_vector_pop_back, \
	.insert = (NAME ## _iterator (*)(pointer,const_iterator,const T ## _t*)) yaooc_array_container_insert, \
	.insertn = (NAME ## _iterator (*)(pointer,const_iterator,size_t n,const T ## _t*)) yaooc_array_container_insertn, \
	.insert_range = (NAME ## _iterator (*)(pointer,const_iterator,const_iterator,const_iterator)) yaooc_array_container_insert_range, \
	.erase = (NAME ## _iterator (*) (pointer,iterator)) yaooc_array_container_erase, \
	.erase_range = (NAME ## _iterator (*) (pointer,iterator,iterator)) yaooc_array_container_erase_range, \
  .erase_value = (size_t (*) (pointer,const_pointer)) yaooc_array_container_erase_value, \
  .reserve = (void (*)(pointer,size_t)) yaooc_array_container_reserve, \
	.front = (NAME ## _iterator (*) (pointer)) yaooc_array_container_begin, \
	.back = (NAME ## _iterator (*) (pointer)) yaooc_vector_back, \
	.resize = (void (*)(pointer,size_t)) yaooc_array_container_resize, \
	.resize_value = (void (*)(pointer,size_t,const_pointer)) yaooc_array_container_resize_value, \
	.shrink_to_fit = (void (*)(pointer)) yaooc_array_container_shrink_to_fit, \
	.clear = (void (*)(pointer)) yaooc_array_container_clear, \
}; \
DEFINE_TYPE_INFO(NAME ,Y,N,N,N,N,N,N,Y,yaooc_array_container)

#define VECTOR(T,NAME) \
VECTOR_DEFINITION(T,NAME) \
VECTOR_IMPLEMENTATION(T,NAME)

#endif
