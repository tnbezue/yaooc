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

#include <string.h>
#include <stdio.h>
#include <yaooc/ordered_array_container.h>

/*  Begin YAOOC PreProcessor generated content */

/* Private items for yaooc_ordered_array_container */

/* Protected items for yaooc_ordered_array_container */

yaooc_ordered_array_container_find_result_t yaooc_ordered_array_container_find_protected(const_pointer p,const_pointer value)
{
  yaooc_ordered_array_container_const_pointer this=p;
  yaooc_ordered_array_container_find_result_t ret;
  ret.found_=false;
  ret.position_=AT(this,0);
//  size_t element_size=TYPE_SIZE(this);
  size_t lower=0,upper=SIZE(this)-1,middle=0,position=0;
  rich_compare rich_cmp=get_rich_compare(this->type_info_);
  while(lower <= upper && upper != (size_t)-1) {
    middle=(lower+upper)>>1;
    pointer middle_ptr=AT(this,middle);
    if(rich_cmp(middle_ptr,value) < 0) {
      lower=middle+1;
      position=lower;
    } else if(rich_cmp(middle_ptr,value) > 0) {
      upper=middle-1;
      position=middle;
    } else {
      ret.found_=true;
      /*
        Make sure value found is the first in container
      */

      while(middle > 0) {
        middle--;
        if(rich_cmp(AT(this,middle),value)!=0) {
          middle++;
          break;
        }
      }
      position=middle;
      break;
    }
  }
  ret.position_=AT(this,position);
  return ret;
}

iterator yaooc_ordered_array_container_find(const_pointer p,const_pointer value)
{
  yaooc_ordered_array_container_find_result_t fr=yaooc_ordered_array_container_find_protected(p,value);
	return fr.found_ ? fr.position_ : END(p);
}

/*
  Since this is an ordered array.  pos is ignored.  Keep it as argument so it is compatible with
  other containers.
*/
iterator yaooc_ordered_array_container_insert(pointer p,const_iterator pos,const_pointer value)
{
  yaooc_ordered_array_container_find_result_t ret=yaooc_ordered_array_container_find_protected(p,value);
//  size_t ofs=INDEX(p,ret.position_);
  return yaooc_array_container_insertn(p,ret.position_,1,value);
//  return AT(p,ofs);
}

iterator yaooc_ordered_array_container_insertn(pointer p,const_iterator pos,size_t n,const_pointer value)
{
  yaooc_ordered_array_container_find_result_t ret=yaooc_ordered_array_container_find_protected(p,value);
//  size_t index=INDEX(p,ret.position_);
  return yaooc_array_container_insertn(p,ret.position_,n,value);
//  return AT(p,index);
}

iterator yaooc_ordered_array_container_insert_range(pointer p,const_iterator pos,const_iterator f,const_iterator l)
{
  yaooc_private_iterator first=(yaooc_private_iterator)f;
  yaooc_private_iterator last=(yaooc_private_iterator)l;
  size_t index=(size_t)-1;
  for(;first!=last;first+=TYPE_SIZE(p)) {
    iterator temp=yaooc_ordered_array_container_insert(p,pos,first);
    if(index == (size_t)-1)
      index=INDEX(p,temp);
  }
  return AT(p,index == (size_t)-1 ? SIZE(p) : index);
}

size_t yaooc_ordered_array_container_erase_value(pointer p,const_pointer value)
{
  size_t ret=0;
  yaooc_ordered_array_container_find_result_t fr=yaooc_ordered_array_container_find_protected(p,value);
  if(fr.found_) {
    rich_compare rich_cmp=get_rich_compare(TYPE_INFO(p));
    yaooc_private_const_iterator first=fr.position_;
    yaooc_private_const_iterator last=fr.position_+TYPE_SIZE(p);
    while(last < END(p)) {
      if(rich_cmp(fr.position_,value)<0)
        break;
      last+=TYPE_SIZE(p);
    };
    ret=DISTANCE(TYPE_INFO(p),first,last);
    yaooc_array_container_erase_range(p,first,last);
  }
  return ret;
}

void yaooc_ordered_array_container_resize_value(pointer p,size_t n,const_pointer value)
{
  yaooc_ordered_array_container_pointer this=p;
  if(n<SIZE(this)) {
    yaooc_array_container_erase_range(p,AT(p,n),END(p));
  } else {
    yaooc_ordered_array_container_find_result_t fr=yaooc_ordered_array_container_find_protected(p,value);
    yaooc_array_container_insertn(p,fr.position_,n-SIZE(p),value);
  }
}

void yaooc_ordered_array_container_resize(pointer p,size_t n)
{
  yaooc_private_pointer temp=__new_array(TYPE_INFO(p),1);
  yaooc_ordered_array_container_resize_value(p,n,temp);
  delete(temp);
}

/* Typeinfo for yaooc_ordered_array_container */

/* Constructors for yaooc_ordered_array_container */

/* Class table methods for yaooc_ordered_array_container */

/* Class table for yaooc_ordered_array_container */
yaooc_ordered_array_container_class_table_t yaooc_ordered_array_container_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_array_container_class_table,
  .type_name_ = (const char*) "yaooc_ordered_array_container_t",
  .swap = (void (*) (pointer p,pointer)) yaooc_ordered_array_container_swap,
  .increase_capacity = (bool (*) (pointer,size_t)) yaooc_ordered_array_container_increase_capacity,
  .size_needed = (size_t (*)(const_pointer,size_t)) yaooc_ordered_array_container_size_needed,
  .size = (size_t (*) (const_pointer p)) yaooc_ordered_array_container_size,
  .capacity = (size_t (*) (const_pointer p)) yaooc_ordered_array_container_capacity,
  .empty = (bool (*) (const_pointer p)) yaooc_ordered_array_container_empty,
  .begin = (iterator (*) (pointer p)) yaooc_ordered_array_container_begin,
  .end = (iterator (*) (pointer p)) yaooc_ordered_array_container_end,
  .cbegin = (const_iterator (*) (const_pointer p)) yaooc_ordered_array_container_begin,
  .cend = (const_iterator (*) (const_pointer p)) yaooc_ordered_array_container_end,
};


DEFINE_TYPE_INFO(yaooc_ordered_array_container,N,N,N,N,N,N,N,Y,yaooc_array_container);
/*  End YAOOC PreProcessor generated content */
