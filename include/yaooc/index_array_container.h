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

#ifndef __INDEX_ARRAY_CONTAINER_INCLUDED__
#define __INDEX_ARRAY_CONTAINER_INCLUDED__

#include <yaooc/array_container.h>
#include <yaooc/uint24.h>
typedef yaooc_uint24_t yaooc_index_array_container_index_t;

typedef struct {
  // If found, lower_index to upper_index of index array of found item.
  // If not found, index in ordered index array of where insertion should occur
	size_t lower_index_;
  size_t upper_index_;
	bool found_;		// indicates whether found
} yaooc_index_array_container_find_result_t;


/*  Begin YAOOC PreProcessor generated content */

/*
  Class definition for yaooc_index_array_container
*/
yaooc_class_table(yaooc_index_array_container)
{
  yaooc_array_container_class_table_t;
};
#define yaooc_index_array_container_parent_class_table ((yaooc_array_container_class_table_t*)(yaooc_index_array_container_class_table.parent_class_table_))

yaooc_class_instance(yaooc_index_array_container)
{
  yaooc_array_container_class_instance_t;
  yaooc_index_array_container_index_t* indexes_;
};

yaooc_class(yaooc_index_array_container);
/* Prototypes for yaooc_index_array_container type info */
void yaooc_index_array_container_dtor(pointer);
void yaooc_index_array_container_copy_ctor(pointer,const_pointer);
void yaooc_index_array_container_assign(pointer,const_pointer);

/* Constructors for yaooc_index_array_container */
void yaooc_index_array_container_ctor_ti(pointer,va_list);

/* Prototypes for yaooc_index_array_container class table*/
void yaooc_index_array_container_swap(pointer,pointer);
#define yaooc_index_array_container_size yaooc_array_container_size
#define yaooc_index_array_container_capacity yaooc_array_container_capacity
#define yaooc_index_array_container_empty yaooc_array_container_empty
#define yaooc_index_array_container_begin yaooc_array_container_begin
#define yaooc_index_array_container_end yaooc_array_container_end
void yaooc_index_array_container_insert_index(pointer,size_t,size_t,size_t,size_t);
void yaooc_index_array_container_remove_index(pointer,size_t,size_t);

/* Prototypes for yaooc_index_array_container class instance*/

/* Prototypes for yaooc_index_array_container class protected items*/
bool yaooc_index_array_container_increase_capacity(pointer,size_t);
#define yaooc_index_array_container_size_needed yaooc_array_container_size_needed
iterator yaooc_index_array_container_insert(pointer,const_iterator,const_pointer);
iterator yaooc_index_array_container_insertn(pointer,const_iterator,size_t,const_pointer);
iterator yaooc_index_array_container_insert_range(pointer,const_iterator,const_iterator,const_iterator);
yaooc_index_array_container_find_result_t yaooc_index_array_container_find_protected(const_pointer,const_pointer);
iterator yaooc_index_array_container_find(const_pointer,const_pointer);
iterator yaooc_index_array_container_erase(pointer,const_iterator);
size_t yaooc_index_array_container_erase_value(pointer,const_pointer);
iterator yaooc_index_array_container_erase_range(pointer,const_iterator,const_iterator);
void yaooc_index_array_container_resize(pointer,size_t);
void yaooc_index_array_container_resize_value(pointer,size_t,const_pointer);
void yaooc_index_array_container_shrink_to_fit(pointer);
void yaooc_index_array_container_reserve(pointer,size_t);
#define yaooc_index_array_container_clear yaooc_array_container_clear
//iterator yaooc_index_array_container_at_i(const_pointer,size_t);
/*  End YAOOC PreProcessor generated content */

//#define AT_I(p,i) AT(p,((yaooc_index_array_container_const_pointer)(p))->indexes_[i])
#define AT_I(p,i) AT(p,yaooc_uint24_to_uint32(((yaooc_index_array_container_const_pointer)(p))->indexes_+i))

#endif
