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

#ifndef __YAOOC_MAP_INCLUDED__
#define __YAOOC_MAP_INCLUDED__

#include <yaooc/unique_array_container.h>
#include <yaooc/unique_index_array_container.h>

#include <yaooc/pair.h>

#define __MAP_DEFINITION(K,V,C,N) \
PAIR_DEFINITION(K,V, N ## _pair) \
typedef N ## _pair_t* N ## _iterator; \
typedef const N ## _pair_t* N ## _const_iterator; \
class_table(N) {\
  yaooc_ ## C ## _container_class_table_t; \
  N ## _iterator (*insert)(pointer,const K ## _t*,const V ## _t*); \
  N ## _iterator (*erase) (pointer,N ## _const_iterator); \
  N ## _iterator (*erase_range)(pointer,N ## _const_iterator,N ## _const_iterator); \
  size_t (*erase_key)(pointer,const K ## _t*); \
  V ## _t* (*at)(const_pointer, const K ## _t*); \
  N ## _iterator (*find)(const_pointer, const K ## _t*); \
  void (*reserve) (pointer,size_t); \
	void (*shrink_to_fit)(pointer); \
  void (*clear)(pointer); \
};\
class_instance(N) { \
  yaooc_ ## C ## _container_class_instance_t; \
};\
class(N); \
const char* N ## _isa(const_pointer); \
N ## _iterator N ## _insert(pointer,const K ## _t*,const V ## _t*); \
size_t N ## _erase_key(pointer,const K ## _t*); \
V ## _t* N ## _at(const_pointer,const K ## _t*); \
N ## _iterator N ## _find(const_pointer, const K ## _t*);

#define __MAP_IMPLEMENTATION(K,V,C,N) \
PAIR_IMPLEMENTATION(K,V,N ## _pair) \
const char* N ## _isa(const_pointer p) { return # N "_t"; } \
N ## _iterator N ## _insert(pointer p,const K ## _t* k,const V ## _t* v) \
{ \
  N ## _pair_t pair; \
  N ## _iterator ptr; \
  make_ ## N ## _pair(&pair,k,v); \
  ptr = yaooc_ ## C ## _container_find(p,&pair); \
  if((iterator)ptr != END(p)) { \
    assign_static((pointer)&ptr->first,k,K); \
    assign_static(&ptr->second,v,V); \
  } else { \
    __newp_array_copy_static((pointer)&pair.first,K ## _ti,k,1); \
    __newp_array_copy_static(&pair.second,V ## _ti,v,1); \
    ptr = yaooc_ ## C ## _container_insert(p,END(p),&pair); \
    __deletep_array((pointer)&pair.first,K ## _ti,1); \
    __deletep_array(&pair.second,V ## _ti,1); \
  } \
  return ptr; \
} \
V ## _t* N ## _at(const_pointer p, const K ## _t *k) \
{ \
  return &(N ## _find(p,k)->second); \
} \
N ## _iterator N ## _find(const_pointer p, const K ## _t* k) \
{ \
  N ## _pair_t pair; \
  make_ ## N ## _pair(&pair,k,NULL); \
  return (N ## _iterator) yaooc_ ## C ## _container_find(p,&pair); \
} \
size_t N ## _erase_key(pointer p, const K ## _t* k) \
{ \
  N ## _pair_t pair; \
  make_ ## N ## _pair(&pair,k,NULL); \
  size_t n = yaooc_ ## C ## _container_erase_value(p,&pair); \
  return n; \
} \
void N ## _default_ctor(pointer p) { call_constructor(p,yaooc_ ## C ## _container_ctor_ti,N ## _pair_ti); } \
N ## _class_table_t N ## _class_table = { \
  .parent_class_table_ = (const class_table_t*)&yaooc_ ## C ## _container_class_table, \
  .isa = N ## _isa, \
  .is_descendant = (bool (*) (const_pointer p,const char*)) yaooc_object_is_descendant, \
  .swap = (void (*) (pointer p,pointer)) yaooc_ ## C ## _container_swap, \
  .increase_capacity = (bool (*) (pointer,size_t)) yaooc_ ## C ## _container_increase_capacity, \
  .size_needed = (size_t (*)(const_pointer,size_t)) yaooc_ ## C ## _container_size_needed, \
  .size = (size_t (*) (const_pointer p)) yaooc_ ## C ## _container_size, \
  .capacity = (size_t (*) (const_pointer p)) yaooc_ ## C ## _container_capacity, \
  .empty = (bool (*) (const_pointer p)) yaooc_ ## C ## _container_empty, \
  .begin = (iterator (*) (const_pointer p)) yaooc_ ## C ## _container_begin, \
  .end = (iterator (*) (const_pointer p)) yaooc_ ## C ## _container_end, \
  .insert = N ## _insert, \
  .erase = (N ## _iterator (*) (pointer,N ## _const_iterator)) yaooc_ ## C ## _container_erase, \
  .erase_range = (N ## _iterator (*)(pointer,N ## _const_iterator,N ## _const_iterator)) yaooc_ ## C ## _container_erase_range, \
  .erase_key = (size_t (*)(pointer,const K ## _t*)) N ## _erase_key, \
  .at = N ## _at, \
  .find = (N ## _iterator (*)(const_pointer, const K ## _t*)) N ## _find, \
  .reserve = yaooc_ ## C ## _container_reserve, \
  .shrink_to_fit = yaooc_ ## C ## _container_shrink_to_fit, \
  .clear  = yaooc_ ## C ## _container_clear, \
}; \
DEFINE_TYPE_INFO(N,N ## _default_ctor,NULL,NULL,NULL,NULL,NULL,NULL,&N ## _class_table,yaooc_ ## C ## _container)

#define MINI_MAP_DEFINITION(K,V,N) __MAP_DEFINITION(K,V,array,N)
#define MINI_MAP_IMPLEMENTATION(K,V,N) __MAP_IMPLEMENTATION(K,V,array,N)

#define MAP_DEFINITION(K,V,N) __MAP_DEFINITION(K,V,index_array,N)
#define MAP_IMPLEMENTATION(K,V,N) __MAP_IMPLEMENTATION(K,V,index_array,N)

#endif
