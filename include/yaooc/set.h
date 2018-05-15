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

#ifndef __YAOOC_SET_INCLUDED__
#define __YAOOC_SET_INCLUDED__
#include <stdlib.h>

#include <yaooc/unique_array_container.h>
#include <yaooc/unique_index_array_container.h>

#define __SET_DEFINITION(T,N,C) \
typedef const T ## _t* N ## _iterator; \
typedef const T ## _t* N ## _const_iterator; \
class_table(N) { \
	yaooc_ ## C ## _container_class_table_t; \
	N ## _iterator (*insert)(pointer,T ## _t*); \
	N ## _iterator (*insert_range)(pointer,const_iterator,const_iterator); \
	N ## _iterator (*erase) (pointer,iterator); \
	N ## _iterator (*erase_range) (pointer,iterator,iterator); \
	N ## _iterator (*find)(const_pointer,T ## _t*); \
};\
class_instance(N) \
{\
	yaooc_ ## C ## _container_class_instance_t;\
};\
class(N);\
const char* N ## _isa(const_pointer); \
N ## _iterator N ## _insert(pointer,T ## _t*); \
N ## _iterator N ## _insert_range(pointer,const_iterator,const_iterator); \
void N ## _default_ctor(pointer);

#define __SET_IMPLEMENTATION(T,N,C) \
void N ## _default_ctor(pointer p) { call_constructor(p,yaooc_ ## C ## _container_ctor_ti,T ## _ti); } \
const char* N ## _isa(const_pointer p) { return # N "_t"; } \
N ## _iterator N ## _insert(pointer p,T ## _t* v) \
{ \
  return yaooc_ ## C ## _container_insert(p,END(p),v); \
} \
N ## _iterator N ## _insert_range(pointer p,const_iterator f,const_iterator l) \
{ \
  return yaooc_ ## C ## _container_insert_range(p,END(p),f,l); \
} \
N ## _class_table_t N ## _class_table = { \
  .parent_class_table_ = (const class_table_t*)&yaooc_ ## C ## _container_class_table, \
  .isa = N ## _isa, \
  .is_descendant = (bool (*) (const_pointer p,const char*)) yaooc_object_is_descendant, \
  .swap = (void (*) (pointer p,pointer)) yaooc_ ## C ## _container_swap, \
  .size = (size_t (*) (const_pointer p)) yaooc_array_container_size, \
  .increase_capacity = (bool(*)(pointer,size_t)) yaooc_pod_array_increase_capacity, \
  .size_needed = (size_t (*)(const_pointer,size_t)) yaooc_pod_array_size_needed, \
  .empty = (bool (*) (const_pointer p)) yaooc_array_container_empty, \
  .begin = (iterator (*) (const_pointer p)) yaooc_array_container_begin, \
  .end = (iterator (*) (const_pointer p)) yaooc_array_container_end, \
  .insert = (N ## _iterator (*)(pointer,T ## _t*)) N ## _insert, \
  .insert_range = (N ## _iterator (*)(pointer,const_iterator,const_iterator)) N ## _insert_range, \
  .erase = (N ## _iterator (*)(pointer,iterator)) yaooc_ ## C ## _container_erase, \
  .erase_range = (N ## _iterator (*)(pointer,iterator,iterator)) yaooc_ ## C ## _container_erase_range, \
  .find = (N ## _iterator (*) (const_pointer,T ## _t*)) yaooc_ ## C ## _container_find \
};\
DEFINE_TYPE_INFO(N,N ## _default_ctor,NULL,NULL,NULL,NULL,NULL,NULL,&N ## _class_table,yaooc_ ## C ## _container)

#define MINI_SET_DEFINITION(T,N) __SET_DEFINITION(T,N,unique_array)
#define MINI_SET_IMPLEMENTATION(T,N) __SET_IMPLEMENTATION(T,N,unique_array)

#define SET_DEFINITION(T,N) __SET_DEFINITION(T,N,unique_index_array)
#define SET_IMPLEMENTATION(T,N) __SET_IMPLEMENTATION(T,N,unique_index_array)


#endif
