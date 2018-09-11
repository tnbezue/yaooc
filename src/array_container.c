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
#include <yaooc/array_container.h>
#include <yaooc/algorithm.h>

/* Private members for yaooc_array_container */


/* Protected members for yaooc_array_container */
iterator yaooc_array_container_find(const_pointer p,const_pointer value)
{
  return __yaooc_find(TYPE_INFO(p),BEGIN(p),END(p),value);
}

iterator yaooc_array_container_insert(pointer p,const_iterator pos,const_pointer value)
{
  return yaooc_array_container_insertn(p,pos,1,value);
}

iterator yaooc_array_container_insert_range(pointer p,const_iterator pos,const_iterator f,const_iterator l)
{
  size_t n=DISTANCE(TYPE_INFO(p),f,l);
  yaooc_private_iterator dpos=yaooc_array_container_insert_space(p,pos,n);
  __newp_array_copy_range_static(dpos,TYPE_INFO(p),f,n);
  return dpos;
}

iterator yaooc_array_container_insertn(pointer p,const_iterator pos,size_t n,const_pointer val)
{
  yaooc_private_iterator ret=yaooc_array_container_insert_space(p,pos,n);
  __newp_array_copy_static(ret,TYPE_INFO(p),val,n);
  return ret;
}

iterator yaooc_array_container_erase(pointer p,const_iterator pos)
{
  return yaooc_array_container_erase_range(p,pos,pos+((yaooc_array_container_const_pointer)p)->type_info_->type_size_);
}

iterator yaooc_array_container_erase_range(pointer p,const_iterator f,const_iterator l)
{
//  yaooc_array_container_pointer this=p;
  iterator ret=(iterator)f;
  size_t n=DISTANCE(TYPE_INFO(p),f,l);
  __deletep_array(ret,TYPE_INFO(p),n);
  return yaooc_array_container_erase_space(p,ret,n);
}

size_t yaooc_array_container_erase_value(pointer p,const_pointer value)
{
  yaooc_array_container_pointer this=p;
  size_t ret=0;
  yaooc_private_iterator pos=END(this)-TYPE_SIZE(this);
  while(pos >= BEGIN(this) && SIZE(this)>0) {
    if(__op_eq_static(pos,value,this->type_info_)) {
      __deletep_array(pos,this->type_info_,1);
      yaooc_array_container_erase_space(this,pos,1);
      ret++;
    }
    pos-=TYPE_SIZE(this);
  }
  return ret;
}
/*
iterator yaooc_array_container_at(const_pointer p,size_t i)
{
  return AT(p,i);
}
*/
void yaooc_array_container_resize_value(pointer p,size_t n,const_pointer val)
{
//  yaooc_array_container_pointer this=p;
  if(n<SIZE(p)) {
    yaooc_array_container_erase_range(p,AT(p,n),END(p));
  } else if(n > SIZE(p)){
    yaooc_array_container_insertn(p,END(p),n-SIZE(p),val);
  }
}

void yaooc_array_container_resize(pointer p,size_t n)
{
//  yaooc_array_container_pointer this=p;
  pointer temp=__new_array(TYPE_INFO(p),1);
  yaooc_array_container_resize_value(p,n,temp);
  delete(temp);
}

void yaooc_array_container_clear(pointer p)
{
  if(SIZE(p) > 0) {
    __deletep_array(BEGIN(p),TYPE_INFO(p),SIZE(p));
    ((yaooc_array_container_pointer)p)->size_=0;
  }
}

/* Typeinfo for yaooc_array_container */

void yaooc_array_container_dtor(pointer p)
{
  yaooc_array_container_pointer this=p;
  yaooc_array_container_clear(this);
}

void yaooc_array_container_copy_ctor(pointer d,const_pointer s)
{
  yaooc_array_container_const_pointer src=s;
  call_constructor(d,yaooc_array_container_ctor_ti,src->type_info_);
  yaooc_array_container_assign(d,s);
}

void yaooc_array_container_assign(pointer d,const_pointer s)
{
  yaooc_array_container_clear(d);
  yaooc_array_container_insert_range(d,BEGIN(d),BEGIN(s),END(s));
}

bool yaooc_array_container_less_than_compare(const_pointer p1,const_pointer p2)
{
  yaooc_array_container_const_pointer this=p1;
  yaooc_array_container_const_pointer other=p2;
  size_t n=M(this,size)<M(other,size) ? M(this,size) : M(other,size);
  size_t i;
  less_than_compare lt_cmp=get_lt_cmp(TYPE_INFO(this));
  for(i=0;i<n;i++) {
    if(lt_cmp(AT(this,i),AT(other,i)))
       return true;
    if(lt_cmp(AT(other,i),AT(this,i)))
      return false;
  }
  return M(this,size) < M(other,size);
}

/* Class table members for yaooc_array_container */

/* Instance members for yaooc_array_container */


yaooc_array_container_class_table_t yaooc_array_container_class_table = {
  .parent_class_table_ = (const class_table_t*) &yaooc_pod_array_class_table,
  .type_name_ = (const char* ) "yaooc_array_container_t",
  .swap = (void (*) (pointer p,pointer)) yaooc_array_container_swap,
  .increase_capacity = (bool (*) (pointer,size_t)) yaooc_pod_array_increase_capacity,
  .size_needed = (size_t (*)(const_pointer,size_t)) yaooc_pod_array_size_needed,
  .size = (size_t (*) (const_pointer p)) yaooc_array_container_size,
  .capacity = (size_t (*) (const_pointer p)) yaooc_array_container_capacity,
  .empty = (bool (*) (const_pointer p)) yaooc_array_container_empty,
  .begin = (iterator (*) (const_pointer p)) yaooc_array_container_begin,
  .end = (iterator (*) (const_pointer p)) yaooc_array_container_end,
};

DEFINE_TYPE_INFO(yaooc_array_container,N,Y,Y,Y,Y,N,N,Y,yaooc_pod_array)

