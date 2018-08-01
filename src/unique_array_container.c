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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaooc/unique_array_container.h>

/* Private items for yaooc_unique_array_container */

/* Protected items for yaooc_unique_array_container */
iterator yaooc_unique_array_container_insert(pointer p,const_iterator pos,const_pointer value)
{
  return yaooc_unique_array_container_insert_range(p,pos,value,value+TYPE_SIZE(p));
}

/*
  Not really valid for unique array.  Can only insert 1 to be unique.
*/
iterator yaooc_unique_array_container_insertn(pointer p,const_iterator pos,size_t n,const_pointer value)
{
  return yaooc_unique_array_container_insert_range(p,pos,value,value+TYPE_SIZE(p));
}

iterator yaooc_unique_array_container_insert_range(pointer p,const_iterator pos,const_iterator f,const_iterator l)
{
  yaooc_unique_array_container_pointer this=p;
  size_t ipos=INDEX(this,pos);
  yaooc_private_const_iterator first=f;
  yaooc_private_const_iterator last=l;
  size_t index=(size_t)-1;
  iterator temp;
  for(;first<last;first+=TYPE_SIZE(p)) {
    if((temp = yaooc_array_container_find(this,first)) == END(this)) {
      temp=yaooc_array_container_insertn(this,AT(this,ipos),1,first);
      ipos++;
    }
    if(index == (size_t)-1)
      index=INDEX(p,temp);
  }
  /*
    index will only be -1 when zero elements are inserted
  */
  return AT(p,index==(size_t)-1 ? SIZE(p) : index);
}

void yaooc_unique_array_container_resize_value(pointer p,size_t n,const_pointer val)
{
  yaooc_unique_array_container_pointer this=p;
  if(n<this->size_) {
    yaooc_array_container_erase_range(p,AT(p,n),END(p));
  } else if(n > this->size_){
    yaooc_unique_array_container_insert_range(this,END(this),val,((yaooc_private_const_pointer)val)+TYPE_SIZE(p));
  }
}

void yaooc_unique_array_container_resize(pointer p,size_t n)
{
  yaooc_array_container_pointer this=p;
  pointer temp=__new_array(this->type_info_,1);
  yaooc_array_container_resize_value(p,n,temp);
  delete(temp);
}


/* Typeinfo for yaooc_unique_array_container */

/* Constructors for yaooc_unique_array_container */

/* Class table methods for yaooc_unique_array_container */
const char* yaooc_unique_array_container_isa(const_pointer p) { return "yaooc_unique_array_container_t"; }

/* Class table for yaooc_unique_array_container */
yaooc_unique_array_container_class_table_t yaooc_unique_array_container_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_array_container_class_table,
  .isa = (const char* (*) (const_pointer p)) yaooc_unique_array_container_isa,
  .is_descendant = (bool (*) (const_pointer p,const char*)) yaooc_unique_array_container_is_descendant,
  .swap = (void (*) (pointer p,pointer)) yaooc_unique_array_container_swap,
  .increase_capacity = (bool (*) (pointer,size_t)) yaooc_pod_array_increase_capacity,
  .size_needed = (size_t (*)(const_pointer,size_t)) yaooc_pod_array_size_needed,
  .size = (size_t (*) (const_pointer p)) yaooc_unique_array_container_size,
  .capacity = (size_t (*) (const_pointer p)) yaooc_unique_array_container_capacity,
  .empty = (bool (*) (const_pointer p)) yaooc_unique_array_container_empty,
  .begin = (iterator (*) (const_pointer p)) yaooc_unique_array_container_begin,
  .end = (iterator (*) (const_pointer p)) yaooc_unique_array_container_end,
};


DEFINE_TYPE_INFO(yaooc_unique_array_container,N,N,N,N,N,N,N,Y,yaooc_array_container)
