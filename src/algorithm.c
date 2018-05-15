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
#include <yaooc/algorithm.h>

iterator __yaooc_find(const type_info_t* ti,const_iterator f,const_iterator l,const_pointer value)
{
	yaooc_private_const_iterator first=f;
	yaooc_private_const_iterator last=l;
  less_than_compare lt_cmp=get_lt_cmp(ti);
  if(lt_cmp) {
    while(first!=last && (lt_cmp(first,value) || lt_cmp(value,first)))
      first+=ti->type_size_;
  }
	return (iterator)first;
}

iterator __yaooc_copy(const type_info_t* ti,const_iterator f,const_iterator l,iterator d)
{
	yaooc_private_const_iterator first=f;
	yaooc_private_const_iterator last=l;
  yaooc_private_iterator dst=d;
  if(get_assignment(ti)) {
    for(;first!=last;dst+=ti->type_size_,first+=ti->type_size_)
      __assign_static(dst,first,ti);
  } else {
    memcpy(dst,first,last-first);
    dst+=last-first;
  }
	return dst;
}

void __yaooc_fill(const type_info_t* ti,iterator f,iterator l,const_pointer value)
{
 	yaooc_private_iterator first=f;
	yaooc_private_iterator last=l;
  assignment assign_func=get_assignment(ti);
  if(assign_func) {
    for(;first!=last;first+=ti->type_size_)
      assign_func(first,value);
  } else {
    for(;first!=last;first+=ti->type_size_)
      memcpy(first,value,ti->type_size_);
  }
}


/*
  User must update count of destination if needed.
  Number of elements copied is (returned dest - initial dest)/ti->type_size_
*/
iterator __yaooc_copy_if(const type_info_t* ti,const_iterator f,const_iterator l,iterator d,bool(*fun)(const void*))
{
	yaooc_private_const_iterator first=f;
	yaooc_private_const_iterator last=l;
  yaooc_private_iterator dst=d;
  assignment assign_func=get_assignment(ti);
  for(;first!=last;first+=ti->type_size_) {
    if(fun(first)) {
      if(assign_func) {
        assign_func(dst,first);
      } else {
        memcpy(dst,first,ti->type_size_);
      }
      dst+=ti->type_size_;
    }
  }
	return dst;

}

void __yaooc_for_each(const type_info_t* ti,iterator f,iterator l,void(*fun)(void*))
{
	yaooc_private_iterator first=f;
	yaooc_private_iterator last=l;
	for(;first!=last;first+=ti->type_size_) {
		fun(first);
	}
}

size_t __yaooc_count(const type_info_t* ti,const_iterator f,const_iterator l,const_pointer value)
{
	size_t count=0;
	yaooc_private_const_iterator first=f;
	yaooc_private_const_iterator last=l;
	less_than_compare lt_cmp=get_lt_cmp(ti);
  if(lt_cmp) {
    for(;first!=last;first+=ti->type_size_) {
      if(!(lt_cmp(first,value) || lt_cmp(value,first)))
        count++;
    }
  }
	return count;
}

size_t __yaooc_count_if(const type_info_t*ti,const_iterator f,const_iterator l,bool(*fun)(const void*))
{
  size_t count=0;
	yaooc_private_const_iterator first=f;
	yaooc_private_const_iterator last=l;
	for(;first!=last;first+=ti->type_size_) {
		if(fun(first))
			count++;
	}
	return count;
}
