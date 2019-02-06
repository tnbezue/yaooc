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

#ifndef __YAOOC_QUEUE_INCLUDED__
#define __YAOOC_QUEUE_INCLUDED__

#include <yaooc/array_container.h>

void yaooc_queue_push(pointer,const_pointer);
void yaooc_queue_pop(pointer);

#define QUEUE_DEFINITION(T,NAME) \
typedef T ## _t* NAME ## _iterator; \
typedef T ## _t* NAME ## _const_iterator; \
yaooc_class_table(NAME) {\
  yaooc_array_container_class_table_t; \
  T ## _t* (*front) (pointer); \
  T ## _t* (*back) (pointer); \
  void (*push)(pointer,T ## _t*); \
  void (*pop)(pointer); \
};\
yaooc_class_instance(NAME) {\
  yaooc_array_container_class_instance_t; \
};\
yaooc_class(NAME);

#define QUEUE_IMPLEMENTATION(T,NAME) \
void NAME ## _default_ctor(pointer p) { call_constructor(p,yaooc_array_container_ctor_ti,T ## _ti); } \
NAME ## _class_table_t NAME ## _class_table = {\
  .parent_class_table_ = (const class_table_t*)&yaooc_array_container_class_table, \
  .type_name_ = #NAME "_t", \
  .swap = (void (*) (pointer,pointer)) yaooc_array_container_swap, \
  .increase_capacity = (bool(*)(pointer,size_t)) yaooc_array_container_increase_capacity, \
  .size_needed = (size_t (*)(const_pointer,size_t)) yaooc_array_container_size_needed, \
  .size = (size_t (*) (const_pointer)) yaooc_array_container_size, \
  .capacity = (size_t (*) (const_pointer)) yaooc_array_container_capacity, \
  .empty = (bool (*) (const_pointer)) yaooc_array_container_empty, \
  .begin = (iterator (*) (pointer)) yaooc_array_container_begin, \
  .end = (iterator (*) (pointer)) yaooc_array_container_end, \
  .cbegin = (const_iterator (*) (const_pointer)) yaooc_array_container_begin, \
  .cend = (const_iterator (*) (const_pointer)) yaooc_array_container_end, \
  .front = (T ## _t* (*) (pointer)) yaooc_array_container_begin, \
  .back = (T ## _t* (*) (pointer)) yaooc_array_container_end, \
  .push = (void (*)(pointer,T ## _t*)) yaooc_queue_push ,\
  .pop = (void (*)(pointer)) yaooc_queue_pop, \
};\
DEFINE_TYPE_INFO(NAME,Y,N,N,N,N,N,N,Y,yaooc_array_container)


#endif
