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

#ifndef __YAOOC_ORDERED_MAP_INCLUDED__
#define __YAOOC_ORDERED_MAP_INCLUDED__

#include <yaooc/unique_ordered_array_container.h>
#include <yaooc/pair.h>

#define ORDERED_MAP_DEFINITION(K,V,NAME) \
PAIR_DEFINITION(K,V, NAME ## _ordered_map_pair); \
typedef NAME ## _ordered_map_pair_t* NAME ## _iterator; \
typedef const NAME ## _ordered_map_pair_t* NAME ## _const_iterator; \
yaooc_class_table(NAME) {\
  yaooc_unique_ordered_array_container_class_table_t; \
  NAME ## _iterator (*insert)(pointer,const K ## _t*,const V ## _t*); \
  NAME ## _iterator (*erase) (pointer,NAME ## _const_iterator); \
  NAME ## _iterator (*erase_range)(pointer,NAME ## _const_iterator,NAME ## _const_iterator); \
  size_t (*erase_key) (pointer,const K ## _t*); \
  V ## _t* (*at)(const_pointer, const K ## _t*); \
  NAME ## _iterator (*find)(const_pointer,const K ## _t*); \
  void (*reserve) (pointer,size_t); \
	void (*shrink_to_fit)(pointer); \
  void (*clear)(pointer); \
};\
yaooc_class_instance(NAME) { \
  yaooc_unique_ordered_array_container_class_instance_t; \
};\
yaooc_class(NAME); \
NAME ## _iterator NAME ## _insert(pointer,const K ## _t*,const V ## _t*); \
size_t NAME ## _erase_key(pointer,const K ## _t*); \
V ## _t* NAME ## _at(const_pointer,const K ## _t*); \
NAME ## _iterator NAME ## _find(const_pointer,const K ## _t*)

#define ORDERED_MAP_IMPLEMENTATION(K,V,NAME) \
PAIR_IMPLEMENTATION(K,V,NAME ## _ordered_map_pair); \
NAME ## _iterator NAME ## _insert(pointer p,const K ## _t* k,const V ## _t* v) \
{ \
  NAME ## _ordered_map_pair_t pair; \
  NAME ## _iterator ptr; \
  make_ ## NAME ## _ordered_map_pair(&pair,k,v); \
  yaooc_ordered_array_container_find_result_t fr = yaooc_ordered_array_container_find_protected(p,&pair); \
  if(fr.found_) { \
    ptr=(NAME ## _iterator)fr.position_; \
    assign_static((pointer)&ptr->first,k,K); \
    assign_static(&ptr->second,v,V); \
  } else { \
    __newp_array_copy_static((pointer)&pair.first,K ## _ti,k,1); \
    __newp_array_copy_static(&pair.second,V ## _ti,v,1); \
    ptr = yaooc_unique_ordered_array_container_insert(p,END(p),&pair); \
		__deletep_array((pointer)&pair.first,K ## _ti,1); \
    __deletep_array(&pair.second,V ## _ti,1); \
 } \
  return ptr; \
} \
size_t NAME ## _erase_key(pointer p,const K ## _t* k) \
{\
  NAME ## _ordered_map_pair_t pair; \
  make_ ## NAME ## _ordered_map_pair(&pair,k,NULL); \
  return yaooc_ordered_array_container_erase_value(p,&pair); \
}\
V ## _t* NAME ## _at(const_pointer p,const K ## _t* k) \
{ \
  return &(NAME ## _find(p,k)->second); \
} \
NAME ## _iterator NAME ## _find(const_pointer p,const K ## _t* k) \
{ \
  NAME ## _ordered_map_pair_t pair; \
  make_ ## NAME ## _ordered_map_pair(&pair,k,NULL); \
  NAME ## _iterator ptr = yaooc_ordered_array_container_find(p,&pair); \
  return ptr; \
} \
void NAME ## _default_ctor(pointer p) { call_constructor(p,yaooc_array_container_ctor_ti,NAME ## _ordered_map_pair_ti); } \
NAME ## _class_table_t NAME ## _class_table = { \
  .parent_class_table_ = (const class_table_t*)&yaooc_unique_ordered_array_container_class_table, \
  .type_name_ = # NAME "_t", \
  .swap = (void (*) (pointer p,pointer)) yaooc_ordered_array_container_swap, \
  .increase_capacity = (bool(*)(pointer,size_t)) yaooc_array_container_increase_capacity, \
  .size_needed = (size_t (*)(const_pointer,size_t)) yaooc_array_container_size_needed, \
  .size = (size_t (*) (const_pointer)) yaooc_array_container_size, \
  .capacity = (size_t (*) (const_pointer)) yaooc_array_container_capacity, \
  .empty = (bool (*) (const_pointer)) yaooc_array_container_empty, \
  .begin = (iterator (*) (pointer)) yaooc_array_container_begin, \
  .end = (iterator (*) (pointer)) yaooc_array_container_end, \
  .cbegin = (const_iterator (*) (const_pointer)) yaooc_array_container_begin, \
  .cend = (const_iterator (*) (const_pointer)) yaooc_array_container_end, \
  .insert = NAME ## _insert, \
	.erase = (NAME ## _iterator (*) (pointer,NAME ## _const_iterator)) yaooc_array_container_erase, \
	.erase_range = (NAME ## _iterator (*) (pointer,NAME ## _const_iterator,NAME ## _const_iterator)) yaooc_array_container_erase_range, \
  .erase_key = NAME ## _erase_key, \
  .at = NAME ## _at, \
  .find = NAME ## _find, \
  .reserve = yaooc_array_container_reserve, \
  .shrink_to_fit = yaooc_array_container_shrink_to_fit, \
  .clear  = yaooc_array_container_clear, \
}; \
DEFINE_TYPE_INFO(NAME,Y,N,N,N,N,N,N,Y,yaooc_unique_ordered_array_container)

#endif
