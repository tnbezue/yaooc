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

#ifndef __YAOOC_ARRAY_CONTAINER_INCLUDED__
#define __YAOOC_ARRAY_CONTAINER_INCLUDED__

#include <yaooc/pod_array.h>

typedef uint32_t yaooc_array_index_t;

/*  Begin YAOOC PreProcessor generated content */

/*
  Class definition for yaooc_array_container
*/
yaooc_class_table(yaooc_array_container)
{
  yaooc_pod_array_class_table_t;
};

yaooc_class_instance(yaooc_array_container)
{
  yaooc_pod_array_class_instance_t;
};

yaooc_class(yaooc_array_container);

/* Prototypes for type info */
void yaooc_array_container_dtor(pointer);
void yaooc_array_container_copy_ctor(pointer,const_pointer);
void yaooc_array_container_assign(pointer,const_pointer);
bool yaooc_array_container_less_than_compare(const_pointer,const_pointer);

/* Prototypes for Constructors */
#define yaooc_array_container_ctor_ti yaooc_pod_array_ctor_ti

/* Prototypes for class table members */
const char* yaooc_array_container_isa(const_pointer);
#define yaooc_array_container_is_descendant yaooc_object_is_descendant
#define yaooc_array_container_swap yaooc_pod_array_swap
#define yaooc_array_container_empty yaooc_pod_array_empty
#define yaooc_array_container_size yaooc_pod_array_size
#define yaooc_array_container_capacity yaooc_pod_array_capacity
#define yaooc_array_container_begin yaooc_pod_array_begin
#define yaooc_array_container_end yaooc_pod_array_end

/* Prototypes for class instance members */

/* Prototypes for class protected member */
#define yaooc_array_container_insert_space yaooc_pod_array_insert_space
#define yaooc_array_container_erase_space yaooc_pod_array_erase_space
#define yaooc_array_container_replace_space yaooc_pod_array_replace_space
#define yaooc_array_container_increase_capacity yaooc_pod_array_increase_capacity
#define yaooc_array_container_size_needed yaooc_pod_array_size_needed
iterator yaooc_array_container_find(const_pointer,const_pointer);
iterator yaooc_array_container_insert(pointer,const_iterator,const_pointer);
iterator yaooc_array_container_insertn(pointer,const_iterator,size_t,const_pointer);
iterator yaooc_array_container_insert_range(pointer,const_iterator,const_iterator,const_iterator);
iterator yaooc_array_container_erase(pointer,const_iterator);
iterator yaooc_array_container_erase_range(pointer,const_iterator,const_iterator);
size_t yaooc_array_container_erase_value(pointer,const_pointer);
#define yaooc_array_container_at yaooc_pod_array_at
void yaooc_array_container_resize(pointer,size_t);
void yaooc_array_container_resize_value(pointer,size_t,const_pointer);
#define yaooc_array_container_shrink_to_fit yaooc_pod_array_shrink_to_fit
#define yaooc_array_container_reserve yaooc_pod_array_reserve
void yaooc_array_container_clear(pointer);

/*  End YAOOC PreProcessor generated content */


#endif
