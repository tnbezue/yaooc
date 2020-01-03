/*
		Copyright (C) 2016-2020  by Terry N Bezue

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

#ifndef __YAOOC_ORDERED_SET_INCLUDED__
#define __YAOOC_ORDERED_SET_INCLUDED__
#include <stdlib.h>

#include <yaooc/unique_ordered_array_container.h>

#define ORDERED_SET_DEFINITION(T,NAME) \
typedef const T ## _t* NAME ## _iterator; \
typedef const T ## _t* NAME ## _const_iterator; \
yaooc_class_table(NAME) { \
	yaooc_unique_ordered_array_container_class_table_t; \
	NAME ## _iterator (*insert)(pointer,const T ## _t*); \
	NAME ## _iterator (*insert_range)(pointer,const_iterator,const_iterator); \
	NAME ## _iterator (*erase) (pointer,iterator); \
	NAME ## _iterator (*erase_range) (pointer,iterator,iterator); \
	NAME ## _iterator (*find)(const_pointer,const T ## _t*); \
};\
yaooc_class_instance(NAME) \
{\
	yaooc_unique_ordered_array_container_class_instance_t;\
};\
yaooc_class(NAME);\
NAME ## _iterator NAME ## _insert(pointer,const T ## _t*); \
NAME ## _iterator NAME ## _insert_range(pointer,const_iterator,const_iterator); \
void NAME ## _default_ctor(pointer)

#define ORDERED_SET_IMPLEMENTATION(T,NAME) \
void NAME ## _default_ctor(pointer p) { call_constructor(p,yaooc_array_container_ctor_ti,T ## _ti); } \
NAME ## _iterator NAME ## _insert(pointer p,const T ## _t* v) \
{ \
  return yaooc_unique_ordered_array_container_insert(p,END(p),v); \
} \
NAME ## _iterator NAME ## _insert_range(pointer p,const_iterator f,const_iterator l) \
{ \
  return yaooc_unique_ordered_array_container_insert_range(p,END(p),f,l); \
} \
NAME ## _class_table_t NAME ## _class_table = { \
  .parent_class_table_ = (const class_table_t*)&yaooc_unique_ordered_array_container_class_table, \
  .type_name_ = # NAME "_t", \
  .swap = (void (*) (pointer p,pointer)) yaooc_array_container_swap, \
  .increase_capacity = (bool(*)(pointer,size_t)) yaooc_array_container_increase_capacity, \
  .size_needed = (size_t (*)(const_pointer,size_t)) yaooc_array_container_size_needed, \
  .size = (size_t (*) (const_pointer p)) yaooc_array_container_size, \
  .capacity = (size_t (*) (const_pointer p)) yaooc_array_container_capacity, \
  .empty = (bool (*) (const_pointer p)) yaooc_array_container_empty, \
  .begin = (iterator (*) (pointer p)) yaooc_array_container_begin, \
  .end = (iterator (*) (pointer p)) yaooc_array_container_end, \
  .cbegin = (const_iterator (*) (const_pointer p)) yaooc_array_container_begin, \
  .cend = (const_iterator (*) (const_pointer p)) yaooc_array_container_end, \
  .insert = (NAME ## _iterator (*)(pointer,const T ## _t*)) NAME ## _insert, \
  .insert_range = (NAME ## _iterator (*)(pointer,const_iterator,const_iterator)) NAME ## _insert_range, \
  .erase = (NAME ## _iterator (*)(pointer,iterator)) yaooc_array_container_erase, \
  .erase_range = (NAME ## _iterator (*)(pointer,iterator,iterator)) yaooc_array_container_erase_range, \
  .find = (NAME ## _iterator (*) (const_pointer,const T ## _t*)) yaooc_ordered_array_container_find \
};\
DEFINE_TYPE_INFO(NAME,Y,N,N,N,N,N,N,Y,yaooc_unique_ordered_array_container)

#endif
