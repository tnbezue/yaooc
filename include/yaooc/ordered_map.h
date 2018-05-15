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

#ifndef __YAOOC_ORDERED_MAP_INCLUDED__
#define __YAOOC_ORDERED_MAP_INCLUDED__

#include <yaooc/unique_ordered_array_container.h>
#include <yaooc/pair.h>

#define ORDERED_MAP_DEFINITION(K,V,N) \
PAIR_DEFINITION(K,V, N ## _ordered_map_pair) \
typedef N ## _ordered_map_pair_t* N ## _iterator; \
typedef const N ## _ordered_map_pair_t* N ## _const_iterator; \
class_table(N) {\
  yaooc_unique_ordered_array_container_class_table_t; \
  N ## _iterator (*insert)(pointer,const K ## _t*,const V ## _t*); \
  N ## _iterator (*erase) (pointer,N ## _const_iterator); \
  N ## _iterator (*erase_range)(pointer,N ## _const_iterator,N ## _const_iterator); \
  size_t (*erase_key) (pointer,const K ## _t*); \
  V ## _t* (*at)(const_pointer, const K ## _t*); \
  N ## _iterator (*find)(const_pointer,const K ## _t*); \
  void (*reserve) (pointer,size_t); \
	void (*shrink_to_fit)(pointer); \
  void (*clear)(pointer); \
};\
class_instance(N) { \
  yaooc_unique_ordered_array_container_class_instance_t; \
};\
class(N); \
const char* N ## _isa(const_pointer); \
N ## _iterator N ## _insert(pointer,const K ## _t*,const V ## _t*); \
size_t N ## _erase_key(pointer,const K ## _t*); \
V ## _t* N ## _at(const_pointer,const K ## _t*); \
N ## _iterator N ## _find(const_pointer,const K ## _t*);

#define ORDERED_MAP_IMPLEMENTATION(K,V,N) \
PAIR_IMPLEMENTATION(K,V,N ## _ordered_map_pair) \
const char* N ## _isa(const_pointer p) { return # N "_t"; } \
N ## _iterator N ## _insert(pointer p,const K ## _t* k,const V ## _t* v) \
{ \
  N ## _ordered_map_pair_t pair; \
  N ## _iterator ptr; \
  make_ ## N ## _ordered_map_pair(&pair,k,v); \
  yaooc_ordered_array_container_find_result_t fr = yaooc_ordered_array_container_find_protected(p,&pair); \
  if(fr.found_) { \
    ptr=(N ## _iterator)fr.position_; \
    assign_static((pointer)&ptr->first,k,K); \
    assign_static(&ptr->second,v,V); \
  } else { \
    __newp_array_copy_static((pointer)&pair.first,K ## _ti,k,1); \
    __newp_array_copy_static(&pair.second,V ## _ti,v,1); \
    ptr = yaooc_unique_ordered_array_container_insert(p,END(p),&pair); \
  } \
  return ptr; \
} \
size_t N ## _erase_key(pointer p,const K ## _t* k) \
{\
  N ## _ordered_map_pair_t pair; \
  make_ ## N ## _ordered_map_pair(&pair,k,NULL); \
  return yaooc_ordered_array_container_erase_value(p,&pair); \
}\
V ## _t* N ## _at(const_pointer p,const K ## _t* k) \
{ \
  return &(N ## _find(p,k)->second); \
} \
N ## _iterator N ## _find(const_pointer p,const K ## _t* k) \
{ \
  N ## _ordered_map_pair_t pair; \
  make_ ## N ## _ordered_map_pair(&pair,k,NULL); \
  N ## _iterator ptr = yaooc_ordered_array_container_find(p,&pair); \
  return ptr; \
} \
void N ## _default_ctor(pointer p) { call_constructor(p,yaooc_array_container_ctor_ti,N ## _ordered_map_pair_ti); } \
N ## _class_table_t N ## _class_table = { \
  .parent_class_table_ = (const class_table_t*)&yaooc_unique_ordered_array_container_class_table, \
  .isa = N ## _isa, \
  .is_descendant = (bool (*) (const_pointer p,const char*)) yaooc_object_is_descendant, \
  .swap = (void (*) (pointer p,pointer)) yaooc_ordered_array_container_swap, \
  .increase_capacity = (bool(*)(pointer,size_t)) yaooc_pod_array_increase_capacity, \
  .size_needed = (size_t (*)(const_pointer,size_t)) yaooc_pod_array_size_needed, \
  .size = (size_t (*) (const_pointer)) yaooc_array_container_size, \
  .capacity = (size_t (*) (const_pointer)) yaooc_array_container_capacity, \
  .empty = (bool (*) (const_pointer)) yaooc_array_container_empty, \
  .begin = (iterator (*) (const_pointer)) yaooc_array_container_begin, \
  .end = (iterator (*) (const_pointer)) yaooc_array_container_end, \
  .insert = N ## _insert, \
	.erase = (N ## _iterator (*) (pointer,N ## _const_iterator)) yaooc_array_container_erase, \
	.erase_range = (N ## _iterator (*) (pointer,N ## _const_iterator,N ## _const_iterator)) yaooc_array_container_erase_range, \
  .erase_key = N ## _erase_key, \
  .at = N ## _at, \
  .find = N ## _find, \
  .reserve = yaooc_array_container_reserve, \
  .shrink_to_fit = yaooc_array_container_shrink_to_fit, \
  .clear  = yaooc_array_container_clear, \
}; \
DEFINE_TYPE_INFO(N,N ## _default_ctor,NULL,NULL,NULL,NULL,NULL,NULL,&N ## _class_table,yaooc_unique_ordered_array_container)

#endif
