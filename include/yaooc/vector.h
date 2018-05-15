/*
		Copyright (C) 2016-2018  by Terry N Bezue

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

#define VECTOR_DEFINITION(T,N) \
typedef T ## _t* N ## _iterator; \
typedef const T ## _t* N ## _const_iterator; \
class_table(N) \
{ \
  yaooc_array_container_class_table_t; \
  N ## _iterator (*at)(const_pointer,size_t); \
  N ## _iterator (*push_back)(pointer,const T ## _t*); \
	void (*pop_back)(pointer); \
	N ## _iterator (*insert)(pointer,const_iterator,const T ## _t*); \
  N ## _iterator (*insertn)(pointer,const_iterator,size_t,const T ## _t*); \
	N ## _iterator (*insert_range)(pointer,const_iterator,const_iterator,const_iterator); \
	N ## _iterator (*erase) (pointer,iterator); \
	N ## _iterator (*erase_range) (pointer,iterator,iterator); \
  size_t (*erase_value) (pointer,const_pointer); \
  void (*reserve) (pointer,size_t); \
	N ## _iterator (*front) (pointer); \
	N ## _iterator (*back) (pointer); \
	void (*resize)(pointer,size_t); \
	void (*resize_value)(pointer,size_t,const_pointer); \
	void (*shrink_to_fit)(pointer); \
  void (*clear)(pointer); \
};\
class_instance(N) \
{ \
	yaooc_array_container_class_instance_t; \
}; \
class(N);\
const char* N ## _isa(const_pointer p);

#define VECTOR_IMPLEMENTATION(T,N) \
void N ## _default_ctor(pointer p) { call_constructor(p,yaooc_array_container_ctor_ti,T ## _ti); } \
const char* N ## _isa(const_pointer p) { return # N "_t"; } \
N ## _class_table_t N ## _class_table = \
{ \
  .parent_class_table_ = (const class_table_t*) &yaooc_array_container_class_table, \
  .isa = (const char* (*)(const_pointer)) N ## _isa, \
  .is_descendant = (bool (*)(const_pointer,const char*)) yaooc_object_is_descendant, \
  .swap = (void (*)(pointer,pointer)) yaooc_array_container_swap, \
  .increase_capacity = (bool (*) (pointer,size_t)) yaooc_pod_array_increase_capacity, \
  .size_needed = (size_t (*)(const_pointer,size_t)) yaooc_pod_array_size_needed, \
  .size = (size_t (*)(const_pointer)) yaooc_array_container_size, \
  .capacity = (size_t (*)(const_pointer)) yaooc_array_container_capacity, \
  .empty = (bool (*)(const_pointer)) yaooc_array_container_empty, \
  .begin = (iterator (*)(const_pointer)) yaooc_array_container_begin, \
  .end = (iterator (*)(const_pointer)) yaooc_array_container_end, \
  .at = (N ## _iterator (*)(const_pointer,size_t)) yaooc_array_container_at, \
  .push_back = (N ## _iterator (*)(pointer,const T ## _t*)) yaooc_vector_push_back, \
	.pop_back = (void (*)(pointer)) yaooc_vector_pop_back, \
	.insert = (N ## _iterator (*)(pointer,const_iterator,const T ## _t*)) yaooc_array_container_insert, \
	.insertn = (N ## _iterator (*)(pointer,const_iterator,size_t n,const T ## _t*)) yaooc_array_container_insertn, \
	.insert_range = (N ## _iterator (*)(pointer,const_iterator,const_iterator,const_iterator)) yaooc_array_container_insert_range, \
	.erase = (N ## _iterator (*) (pointer,iterator)) yaooc_array_container_erase, \
	.erase_range = (N ## _iterator (*) (pointer,iterator,iterator)) yaooc_array_container_erase_range, \
  .erase_value = (size_t (*) (pointer,const_pointer)) yaooc_array_container_erase_value, \
  .reserve = (void (*)(pointer,size_t)) yaooc_array_container_reserve, \
	.front = (N ## _iterator (*) (pointer)) yaooc_array_container_begin, \
	.back = (N ## _iterator (*) (pointer)) yaooc_vector_back, \
	.resize = (void (*)(pointer,size_t)) yaooc_array_container_resize, \
	.resize_value = (void (*)(pointer,size_t,const_pointer)) yaooc_array_container_resize_value, \
	.shrink_to_fit = (void (*)(pointer)) yaooc_array_container_shrink_to_fit, \
	.clear = (void (*)(pointer)) yaooc_array_container_clear, \
}; \
DEFINE_TYPE_INFO(N ,N ## _default_ctor,NULL,NULL,NULL,NULL,NULL,NULL,&N ## _class_table,yaooc_array_container)

#define VECTOR(T,N) \
VECTOR_DEFINITION(T,N) \
VECTOR_IMPLEMENTATION(T,N)

#endif
