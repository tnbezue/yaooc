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

#ifndef __UNIQUE_INDEX_ARRAY_CONTAINER_INCLUDED__
#define __UNIQUE_INDEX_ARRAY_CONTAINER_INCLUDED__

#include <yaooc/index_array_container.h>

/*  Begin YAOOC PreProcessor generated content */


/*
  Class definition for yaooc_unique_index_array_container
*/
yaooc_class_table(yaooc_unique_index_array_container)
{
  yaooc_index_array_container_class_table_t;
};

yaooc_class_instance(yaooc_unique_index_array_container)
{
  yaooc_index_array_container_class_instance_t;
};

yaooc_class(yaooc_unique_index_array_container);
/* Prototypes for yaooc_unique_index_array_container type info */

/* Constructors for yaooc_unique_index_array_container */
#define yaooc_unique_index_array_container_ctor_ti yaooc_index_array_container_ctor_ti

/* Prototypes for yaooc_unique_index_array_container class table*/
#define yaooc_unique_index_array_container_swap yaooc_index_array_container_swap
#define yaooc_unique_index_array_container_size yaooc_index_array_container_size
#define yaooc_unique_index_array_container_capacity yaooc_index_array_container_capacity
#define yaooc_unique_index_array_container_empty yaooc_index_array_container_empty
#define yaooc_unique_index_array_container_begin yaooc_index_array_container_begin
#define yaooc_unique_index_array_container_end yaooc_index_array_container_end
#define yaooc_unique_index_array_container_size_needed yaooc_index_array_container_size_needed

/* Prototypes for yaooc_unique_index_array_container class instance*/

/* Prototypes for yaooc_unique_index_array_container class protected items*/
#define yaooc_unique_index_array_container_find yaooc_index_array_container_find
iterator yaooc_unique_index_array_container_insert(pointer,const_iterator,const_pointer);
iterator yaooc_unique_index_array_container_insertn(pointer,const_iterator,size_t,const_pointer);
iterator yaooc_unique_index_array_container_insert_range(pointer,const_iterator,const_iterator,const_iterator);
#define yaooc_unique_index_array_container_erase yaooc_index_array_container_erase
#define yaooc_unique_index_array_container_erase_range yaooc_index_array_container_erase_range
#define yaooc_unique_index_array_container_erase_value yaooc_index_array_container_erase_value
void yaooc_unique_index_array_container_resize(pointer,size_t);
void yaooc_unique_index_array_container_resize_value(pointer,size_t,const_pointer);

/*  End YAOOC PreProcessor generated content */

#endif
