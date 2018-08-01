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

#ifndef __UNIQUE_ARRAY_CONTAINER_INCLUDED__
#define __UNIQUE_ARRAY_CONTAINER_INCLUDED__

#include <yaooc/array_container.h>

/*
  Class definition for yaooc_unique_array_container
*/
yaooc_class_table(yaooc_unique_array_container)
{
  yaooc_array_container_class_table_t;
};

yaooc_class_instance(yaooc_unique_array_container)
{
  yaooc_array_container_class_instance_t;
};

yaooc_class(yaooc_unique_array_container);


/* Prototypes for yaooc_unique_array_container type info */
void yaooc_unique_array_container_default_ctor(pointer);

/* Constructors for yaooc_unique_array_container */
#define yaooc_unique_array_container_ctor_ti yaooc_array_container_ctor_ti

/* Prototypes for yaooc_unique_array_container class table*/
const char* yaooc_unique_array_container_isa(const_pointer);
#define yaooc_unique_array_container_is_descendant yaooc_array_container_is_descendant
#define yaooc_unique_array_container_swap yaooc_array_container_swap
#define yaooc_unique_array_container_size yaooc_array_container_size
#define yaooc_array_container_increase_capacity yaooc_pod_array_increase_capacity
#define yaooc_array_container_size_needed yaooc_pod_array_size_needed
#define yaooc_unique_array_container_capacity yaooc_array_container_capacity
#define yaooc_unique_array_container_empty yaooc_array_container_empty
#define yaooc_unique_array_container_begin yaooc_array_container_begin
#define yaooc_unique_array_container_end yaooc_array_container_end

/* Prototypes for yaooc_unique_array_container class instance*/

/* Prototypes for yaooc_unique_array_container class protected items*/
iterator yaooc_unique_array_container_insert(pointer,const_iterator,const_pointer);
iterator yaooc_unique_array_container_insertn(pointer,const_iterator,size_t,const_pointer);
iterator yaooc_unique_array_container_insert_range(pointer,const_iterator,const_iterator,const_iterator);
void yaooc_unique_array_container_resize(pointer,size_t);
void yaooc_unique_array_container_resize_value(pointer,size_t,const_pointer);

#endif
