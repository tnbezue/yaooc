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

#include <stdio.h>
#include <stdlib.h>
#include <yaooc/unique_ordered_array_container.h>

/*  Begin YAOOC PreProcessor generated content */

/* Private items for yaooc_unique_ordered_array_container */

/* Protected items for yaooc_unique_ordered_array_container */
iterator yaooc_unique_ordered_array_container_insert(pointer p,const_iterator pos,const_pointer value)
{
  yaooc_ordered_array_container_find_result_t ret=yaooc_ordered_array_container_find_protected(p,value);
  size_t ofs=INDEX(p,ret.position_);
  if(!ret.found_) {
    yaooc_array_container_insertn(p,ret.position_,1,value);
  }
  return AT(p,ofs);
}

iterator yaooc_unique_ordered_array_container_insertn(pointer p,const_iterator pos,size_t n,const_pointer val)
{
  return yaooc_unique_ordered_array_container_insert(p,pos,val); // unique, only insert 1
}

iterator yaooc_unique_ordered_array_container_insert_range(pointer p,const_iterator pos,const_iterator f,const_iterator l)
{
  yaooc_private_iterator first=(yaooc_private_iterator)f;
  yaooc_private_iterator last=(yaooc_private_iterator)l;
  size_t index=(size_t)-1;
  for(;first!=last;first+=TYPE_SIZE(p)) {
    iterator temp=yaooc_unique_ordered_array_container_insert(p,pos,first);
    if(index == (size_t)-1)
      index=INDEX(p,temp);
  }
  return AT(p,index == (size_t)-1 ? SIZE(p) : index);
}

void yaooc_unique_ordered_array_container_resize_value(pointer p,size_t n,const_pointer value)
{
  if(n < SIZE(p)) {
    yaooc_array_container_erase_range(p,AT(p,n),END(p));
  } else if (n > SIZE(p)) {
    yaooc_unique_ordered_array_container_insertn(p,END(p),1,value);
  }
}

void yaooc_unique_ordered_array_container_resize(pointer p,size_t n)
{
  pointer temp=__new_array(TYPE_INFO(p),1);
  yaooc_unique_ordered_array_container_resize_value(p,1,temp);
  delete(temp);
}


/* Typeinfo for yaooc_unique_ordered_array_container */
/* Constructors for yaooc_unique_ordered_array_container */

/* Class table methods for yaooc_unique_ordered_array_container */


/* Class table for yaooc_unique_ordered_array_container */
yaooc_unique_ordered_array_container_class_table_t yaooc_unique_ordered_array_container_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_ordered_array_container_class_table,
  .type_name_ = (const char*) "yaooc_unique_ordered_array_container_t",
  .swap = (void (*) (pointer p,pointer)) yaooc_unique_ordered_array_container_swap,
  .increase_capacity = (bool (*) (pointer,size_t)) yaooc_unique_ordered_array_container_increase_capacity,
  .size_needed = (size_t (*)(const_pointer,size_t)) yaooc_unique_ordered_array_container_size_needed,
  .size = (size_t (*) (const_pointer p)) yaooc_unique_ordered_array_container_size,
  .capacity = (size_t (*) (const_pointer p)) yaooc_unique_ordered_array_container_capacity,
  .empty = (bool (*) (const_pointer p)) yaooc_unique_ordered_array_container_empty,
  .begin = (iterator (*) (pointer p)) yaooc_unique_ordered_array_container_begin,
  .end = (iterator (*) (pointer p)) yaooc_unique_ordered_array_container_end,
  .cbegin = (const_iterator (*) (const_pointer p)) yaooc_unique_ordered_array_container_begin,
  .cend = (const_iterator (*) (const_pointer p)) yaooc_unique_ordered_array_container_end,
};


DEFINE_TYPE_INFO(yaooc_unique_ordered_array_container,N,N,N,N,N,N,N,Y,yaooc_ordered_array_container);
/*  End YAOOC PreProcessor generated content */
