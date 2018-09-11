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

#include <string.h>
#include <stdio.h>
#include <yaooc/unique_index_array_container.h>

/*  Begin YAOOC PreProcessor generated content */

/* Private items for yaooc_unique_index_array_container */

/* Protected items for yaooc_unique_index_array_container */
iterator yaooc_unique_index_array_container_insert(pointer p,const_iterator pos,const_pointer value)
{
  return yaooc_unique_index_array_container_insert_range(p,pos,value,((yaooc_private_const_pointer)value)+TYPE_SIZE(p));
}

iterator yaooc_unique_index_array_container_insertn(pointer p,const_iterator pos,size_t n,const_pointer value)
{
  /*
    Unique, so can only insert 1
  */
  return yaooc_unique_index_array_container_insert_range(p,pos,value,((yaooc_private_const_pointer)value)+TYPE_SIZE(p));
}

iterator yaooc_unique_index_array_container_insert_range(pointer p,const_iterator pos,const_iterator f,const_iterator l)
{
//  yaooc_unique_index_array_container_pointer this=p;
  size_t n = DISTANCE(TYPE_INFO(p),f,l);
  yaooc_array_index_t idx=INDEX(p,pos);
  yaooc_index_array_container_increase_capacity(p,n);
  yaooc_private_const_iterator first=f;
  yaooc_private_const_iterator last=l;
  yaooc_private_iterator ipos=AT(p,idx);
  size_t fpos=-1;
  for(;first < last;first+=TYPE_SIZE(p)) {
    yaooc_index_array_container_find_result_t fr=yaooc_index_array_container_find_protected(p,first);
    if(!fr.found_) {
      size_t cur_size=SIZE(p);
      yaooc_index_array_container_insert_index(p,fr.lower_index_,1,idx,cur_size);
      yaooc_array_container_insert_space(p,AT(p,idx),1);
      __newp_array_copy_static(ipos,TYPE_INFO(p),first,1);
      idx++;
      ipos+=TYPE_SIZE(p);
    }
    if(fpos == (size_t)-1)
      fpos=fr.lower_index_;
  }
  return AT(p,fpos == (size_t)-1 ? SIZE(p) : fpos);
}

void yaooc_unique_index_array_container_resize(pointer p,size_t n)
{
  pointer temp=__new_array(TYPE_INFO(p),1);
  yaooc_unique_index_array_container_resize_value(p,1,temp);
}

void yaooc_unique_index_array_container_resize_value(pointer p,size_t n,const_pointer value)
{
//  yaooc_unique_index_array_container_pointer this=p;
  if(n<SIZE(p)) {
    yaooc_index_array_container_erase_range(p,AT(p,n),END(p));
  } else {
    yaooc_unique_index_array_container_insert_range(p,END(p),value,((yaooc_private_const_pointer)value)+TYPE_SIZE(p));
  }
}



/* Typeinfo for yaooc_unique_index_array_container */
/* Constructors for yaooc_unique_index_array_container */

/* Class table methods for yaooc_unique_index_array_container */


/* Class table for yaooc_unique_index_array_container */
yaooc_unique_index_array_container_class_table_t yaooc_unique_index_array_container_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_index_array_container_class_table,
  .type_name_ = (const char*) "yaooc_unique_index_array_container_t",
  .swap = (void (*) (pointer p,pointer)) yaooc_unique_index_array_container_swap,
  .increase_capacity = (bool (*) (pointer,size_t))yaooc_index_array_container_increase_capacity,
  .size_needed = (size_t (*)(const_pointer,size_t)) yaooc_pod_array_size_needed,
  .size = (size_t (*) (const_pointer p)) yaooc_unique_index_array_container_size,
  .capacity = (size_t (*) (const_pointer p)) yaooc_unique_index_array_container_capacity,
  .empty = (bool (*) (const_pointer p)) yaooc_unique_index_array_container_empty,
  .begin = (iterator (*) (const_pointer p)) yaooc_unique_index_array_container_begin,
  .end = (iterator (*) (const_pointer p)) yaooc_unique_index_array_container_end,
};


DEFINE_TYPE_INFO(yaooc_unique_index_array_container,N,N,N,N,N,N,N,Y,yaooc_index_array_container)
/*  End YAOOC PreProcessor generated content */
