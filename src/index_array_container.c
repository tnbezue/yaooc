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
#include <yaooc/index_array_container.h>

/*  Begin YAOOC PreProcessor generated content */

/* Private items for yaooc_index_array_container */

/* Protected items for yaooc_index_array_container */
bool yaooc_index_array_container_increase_capacity(pointer p,size_t n)
{
  yaooc_index_array_container_pointer this=p;
//  bool ret=yaooc_array_container_increase_capacity(p,n);
  bool ret = yaooc_index_array_container_parent_class_table->increase_capacity(p,n);
  if(ret) {
    this->indexes_=REALLOC(this->indexes_,CAPACITY(p)*sizeof(yaooc_index_array_container_index_t));
  }
  return ret;
}

yaooc_index_array_container_find_result_t yaooc_index_array_container_find_protected(const_pointer p,const_pointer value)
{
  yaooc_index_array_container_const_pointer this=p;
  yaooc_index_array_container_find_result_t ret = { 0, 0, false };
  size_t lower=0,upper=this->size_-1,middle;
  less_than_compare lt_cmp=get_lt_cmp(this->type_info_);
  while(lower <= upper && upper != (size_t)-1) {
    middle=(lower+upper)>>1;
    const_pointer middle_value=AT_I(this,middle);
    if(lt_cmp(middle_value,value)) {
      lower=middle+1;
      ret.lower_index_=lower;
    } else if(lt_cmp(value,middle_value)) {
      upper=middle-1;
      ret.lower_index_=middle;
    } else {
      /*
        Find the range of element in container
      */
//      ret.lower_index_=middle;
//      ret.upper_index_=middle;
      size_t idx=middle-1;
      for(;idx>=0 && idx != (size_t)-1;idx--) {
        if(lt_cmp(AT_I(this,idx),value))
          break;
      }
      ret.lower_index_=idx+1;
      for(idx=middle+1;idx<SIZE(this);idx++) {
        if(lt_cmp(value,AT_I(this,idx)))
          break;
      }
      ret.upper_index_=idx-1;
      ret.found_=true;
      break;
    }
  }
  return ret;
}

void yaooc_index_array_container_insert_index(pointer p,size_t pos,size_t n,size_t value,size_t size)
{
  yaooc_index_array_container_pointer this=p;
  size_t i;
  size_t n_ge_value=size-value;
  for(i=0;i<size && n_ge_value>0;i++) {
    uint32_t temp=yaooc_uint24_to_uint32(this->indexes_+i);
    if(temp >= value) {
      yaooc_uint24_from_uint32(this->indexes_+i,temp+n);
      n_ge_value--;
    }
  }
  memmove(this->indexes_+pos+n,this->indexes_+pos,(size -pos)*sizeof(yaooc_index_array_container_index_t));
  for(i=0;i<n;i++,pos++)
    yaooc_uint24_from_uint32(this->indexes_+pos,value++);
}

void yaooc_index_array_container_remove_index(pointer p,size_t pos,size_t n)
{
  yaooc_index_array_container_pointer this=p;
  size_t i,j;
  size_t lower=pos;
  size_t upper=pos+n;
  size_t new_size=SIZE(p)-1;
  for(j=lower;j<upper;j++) {
    size_t n_gt_index=new_size-yaooc_uint24_to_uint32(this->indexes_+j);
    for(i=0; i<lower && n_gt_index > 0;i++) {
      uint32_t temp=yaooc_uint24_to_uint32(this->indexes_+i);
      if(temp > yaooc_uint24_to_uint32(this->indexes_+j)) {
        yaooc_uint24_from_uint32(this->indexes_+i,--temp);
        n_gt_index--;
      }
    }
    for(i=j+1; i<SIZE(p) && n_gt_index > 0;i++) {
      uint32_t temp=yaooc_uint24_to_uint32(this->indexes_+i);
      if(temp > yaooc_uint24_to_uint32(this->indexes_+j)) {
        yaooc_uint24_from_uint32(this->indexes_+i,--temp);
        n_gt_index--;
      }
    }
    new_size--;
  }
  memmove(this->indexes_+pos,this->indexes_+pos+n,(SIZE(p)-pos-n)*sizeof(yaooc_index_array_container_index_t));
}

/*
  When removing a range, after first removal, indexes are renumber so that next removal is for the
  same index. ** FIX ME ** develop a better algorithm
 */
void yaooc_index_array_container_remove_fixed_index(pointer p,size_t value,size_t n)
{
  yaooc_index_array_container_pointer this=p;
  size_t i,j;
  size_t save_size=SIZE(p);
  for(j=0;j<n;j++) {
    for(i=0;i<SIZE(p);i++) {
      if(value == yaooc_uint24_to_uint32(this->indexes_+i))
        break;
    }
    yaooc_index_array_container_remove_index(p,i,1);
    this->size_--;
  }
  this->size_=save_size;
}

iterator yaooc_index_array_container_insert(pointer p,const_iterator pos,const_pointer value)
{
  return yaooc_index_array_container_insertn(p,pos,1,value);
}

iterator yaooc_index_array_container_insertn(pointer p,const_iterator pos,size_t n,const_pointer val)
{
  size_t cur_size=SIZE(p);
  size_t idx=INDEX(p,pos);
  yaooc_index_array_container_find_result_t fr=yaooc_index_array_container_find_protected(p,val);
  iterator ret=yaooc_array_container_insertn(p,pos,n,val);
  yaooc_index_array_container_insert_index(p,fr.lower_index_,n,idx,cur_size);
  return ret;
}

iterator yaooc_index_array_container_insert_range(pointer p,const_iterator pos,const_iterator f,const_iterator l)
{
//  yaooc_index_array_container_pointer this=p;
//  size_t n = DISTANCE(TYPE_INFO(p),f,l);
  size_t idx=INDEX(p,pos);
  yaooc_private_const_iterator first=f;
  yaooc_private_const_iterator last=l;
//  yaooc_private_iterator ipos=AT(p,idx);
  for(;first < last;first+=TYPE_SIZE(p),idx++) {
    yaooc_index_array_container_find_result_t fr=yaooc_index_array_container_find_protected(p,first);
    size_t cur_size=SIZE(p);
    yaooc_array_container_insert(p,AT(p,idx),first);
    yaooc_index_array_container_insert_index(p,fr.lower_index_,1,idx,cur_size);
  }
  return AT(p,idx);
}

iterator yaooc_index_array_container_find(const_pointer p,const_pointer value)
{
  yaooc_index_array_container_find_result_t fr=yaooc_index_array_container_find_protected(p,value);
  return fr.found_ ? AT_I(p,fr.lower_index_) : END(p);
}

iterator yaooc_index_array_container_erase(pointer p,const_iterator pos)
{
//  yaooc_index_array_container_pointer this=p;
/*  size_t ofs=INDEX(p,pos);
  yaooc_index_array_container_remove_index(p,ofs);
  yaooc_array_container_erase_range(p,pos,pos+TYPE_SIZE(p));
  return (iterator)pos;*/
  return yaooc_index_array_container_erase_range(p,pos,((yaooc_private_const_iterator)pos)+TYPE_SIZE(p));
//  return (iterator)pos;
}

int cmp_size_t(const void* a,const void* b)
{
  if(*(size_t*)a < *(size_t*)b)
    return -1;
  if(*(size_t*)a > *(size_t*)b)
    return 1;
  return 0;
}

size_t yaooc_index_array_container_erase_value(pointer p,const_pointer value)
{
  yaooc_index_array_container_pointer this=p;
  size_t n_del=0;
  yaooc_index_array_container_find_result_t fr=yaooc_index_array_container_find_protected(p,value);
  if(fr.found_) {
    size_t i,j;
    n_del = fr.upper_index_-fr.lower_index_+1;
    size_t * indexes=__new_array(size_ti,n_del);
    for(j=0,i=fr.lower_index_;i<=fr.upper_index_;j++,i++) {
      indexes[j]=yaooc_uint24_to_uint32(this->indexes_+i);
    }
    qsort(indexes,n_del,sizeof(size_t),cmp_size_t);
    yaooc_index_array_container_remove_index(p,fr.lower_index_,n_del);
    for(j=n_del-1;j>=0 && j!=(size_t)-1;j--)
      yaooc_array_container_erase_range(p,AT(p,indexes[j]),AT(p,indexes[j]+1));
    delete(indexes);
  }
  return n_del;
}

iterator yaooc_index_array_container_erase_range(pointer p,const_iterator f,const_iterator l)
{
//  yaooc_index_array_container_pointer this=p;
  size_t n=DISTANCE(TYPE_INFO(p),f,l);
  size_t idx=INDEX(p,f);
  yaooc_index_array_container_remove_fixed_index(p,idx,n);
  return yaooc_array_container_erase_range(p,f,l);
}

void yaooc_index_array_container_resize_value(pointer p,size_t n,const_pointer value)
{
  if(n<SIZE(p)) {
    yaooc_index_array_container_erase_range(p,AT(p,n),END(p));
  } else {
    yaooc_index_array_container_insertn(p,END(p),n-SIZE(p),value);
  }
}

void yaooc_index_array_container_resize(pointer p,size_t n)
{
  pointer temp=__new_array(TYPE_INFO(p),1);
  yaooc_index_array_container_resize_value(p,n,temp);
  delete(temp);
}

void yaooc_index_array_container_shrink_to_fit(pointer p)
{
  yaooc_index_array_container_pointer this=p;
  size_t old_capacity=this->capacity_;
  yaooc_array_container_shrink_to_fit(p);
  if(this->capacity_ != old_capacity)
    this->indexes_=REALLOC(this->indexes_,this->capacity_*sizeof(yaooc_index_array_container_index_t));
}

void yaooc_index_array_container_reserve(pointer p,size_t n)
{
  yaooc_index_array_container_pointer this=p;
  size_t old_capacity=this->capacity_;
  yaooc_array_container_reserve(p,n);
  if(this->capacity_ != old_capacity)
    this->indexes_=REALLOC(this->indexes_,this->capacity_*sizeof(yaooc_index_array_container_index_t));
}

iterator yaooc_index_array_container_at_i(const_pointer p,size_t i)
{
  return AT_I(p,i);
}

/* Typeinfo for yaooc_index_array_container */

void yaooc_index_array_container_dtor(pointer p)
{
  yaooc_index_array_container_pointer this=p;
  if(this->indexes_ != NULL)
    FREE(this->indexes_);
}

void yaooc_index_array_container_copy_ctor(pointer d,const_pointer s)
{
  call_constructor(d,yaooc_index_array_container_ctor_ti,TYPE_INFO(s));
  yaooc_index_array_container_assign(d,s);
}

void yaooc_index_array_container_assign(pointer d,const_pointer s)
{
  yaooc_index_array_container_pointer dst=d;
  yaooc_index_array_container_const_pointer src=s;
  yaooc_array_container_assign(d,s);
  memcpy(dst->indexes_,src->indexes_,dst->size_*sizeof(size_t));
}

/* Constructors for yaooc_index_array_container */
void yaooc_index_array_container_ctor_ti(pointer p,va_list args)
{
  yaooc_index_array_container_pointer this=p;
  call_constructor(p,yaooc_array_container_ctor_ti,va_arg(args,const type_info_t*));
  this->indexes_=NULL;
}

/* Class table methods for yaooc_index_array_container */
void yaooc_index_array_container_swap(pointer p1,pointer p2)
{
  yaooc_array_container_swap(p1,p2);
  SWAP(yaooc_index_array_container_index_t*,((yaooc_index_array_container_pointer)p1)->indexes_,((yaooc_index_array_container_pointer)p2)->indexes_);
}

/* Class table for yaooc_index_array_container */
yaooc_index_array_container_class_table_t yaooc_index_array_container_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_array_container_class_table,
  .type_name_ = (const char*) "yaooc_index_array_container_t",
  .swap = (void (*) (pointer p,pointer)) yaooc_index_array_container_swap,
  .increase_capacity = (bool (*) (pointer,size_t))yaooc_index_array_container_increase_capacity,
  .size_needed = (size_t (*)(const_pointer,size_t)) yaooc_index_array_container_size_needed,
  .size = (size_t (*) (const_pointer p)) yaooc_index_array_container_size,
  .capacity = (size_t (*) (const_pointer p)) yaooc_index_array_container_capacity,
  .empty = (bool (*) (const_pointer p)) yaooc_index_array_container_empty,
  .begin = (iterator (*) (pointer p)) yaooc_index_array_container_begin,
  .end = (iterator (*) (pointer p)) yaooc_index_array_container_end,
  .cbegin = (const_iterator (*) (const_pointer p)) yaooc_index_array_container_begin,
  .cend = (const_iterator (*) (const_pointer p)) yaooc_index_array_container_end,
};


DEFINE_TYPE_INFO(yaooc_index_array_container,N,Y,Y,Y,N,N,N,Y,yaooc_array_container);

/*  End YAOOC PreProcessor generated content */
