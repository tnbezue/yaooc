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
#include <yaooc/algorithm.h>

iterator __yaooc_find(const type_info_t* ti,const_iterator f,const_iterator l,const_pointer value)
{
	yaooc_private_const_iterator first=f;
	yaooc_private_const_iterator last=l;
  less_than_compare lt_cmp=get_lt_cmp(ti);
	size_t type_size=yaooc_sizeof(ti);
  if(lt_cmp) {
    while(first!=last && (lt_cmp(first,value) || lt_cmp(value,first)))
      first+=type_size;
  }
	return (iterator)first;
}

const_iterator __yaooc_find_if(const type_info_t* ti,const_iterator f,const_iterator l,bool(*fun)(const void*))
{
	yaooc_private_const_iterator first=f;
	yaooc_private_const_iterator last=l;
	size_t type_size=yaooc_sizeof(ti);
	for(;first!=last;first+=type_size)
		if(fun(first))
			break;
	return first;
}

const_iterator __yaooc_find_if_not(const type_info_t* ti,const_iterator f,const_iterator l,bool(*fun)(const void*))
{
	yaooc_private_const_iterator first=f;
	yaooc_private_const_iterator last=l;
	size_t type_size=yaooc_sizeof(ti);
	for(;first!=last;first+=type_size)
		if(!fun(first))
			break;
	return first;
}

bool __yaooc_all_of(const type_info_t* ti,const_iterator f,const_iterator l,bool(*fun)(const void*))
{
	return __yaooc_find_if_not(ti,f,l,fun) == l;
}

bool __yaooc_any_of(const type_info_t* ti,const_iterator f,const_iterator l,bool(*fun)(const void*))
{
	return __yaooc_find_if(ti,f,l,fun) != l;
}

bool __yaooc_none_of(const type_info_t* ti,const_iterator f,const_iterator l,bool(*fun)(const void*))
{
	return __yaooc_find_if(ti,f,l,fun) == l;
}

iterator __yaooc_copy(const type_info_t* ti,const_iterator f,const_iterator l,iterator d)
{
	yaooc_private_const_iterator first=f;
	yaooc_private_const_iterator last=l;
  yaooc_private_iterator dst=d;
  if(get_assignment(ti)) {
		size_t type_size=yaooc_sizeof(ti);
    for(;first!=last;dst+=type_size,first+=type_size)
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
	size_t type_size=yaooc_sizeof(ti);
  if(assign_func) {
    for(;first!=last;first+=type_size)
      assign_func(first,value);
  } else {
    for(;first!=last;first+=type_size)
      memcpy(first,value,type_size);
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
	size_t type_size=yaooc_sizeof(ti);
  for(;first!=last;first+=type_size) {
    if(fun(first)) {
      if(assign_func) {
        assign_func(dst,first);
      } else {
        memcpy(dst,first,type_size);
      }
      dst+=type_size;
    }
  }
	return dst;

}

void __yaooc_for_each(const type_info_t* ti,iterator f,iterator l,void(*fun)(void*))
{
	yaooc_private_iterator first=f;
	yaooc_private_iterator last=l;
	size_t type_size=yaooc_sizeof(ti);
	for(;first!=last;first+=type_size) {
		fun(first);
	}
}

size_t __yaooc_count(const type_info_t* ti,const_iterator f,const_iterator l,const_pointer value)
{
	size_t count=0;
	yaooc_private_const_iterator first=f;
	yaooc_private_const_iterator last=l;
	less_than_compare lt_cmp=get_lt_cmp(ti);
	size_t type_size=yaooc_sizeof(ti);
  if(lt_cmp) {
    for(;first!=last;first+=type_size) {
      if(!(lt_cmp(first,value) || lt_cmp(value,first)))
        count++;
    }
  } else { // All are equal if not lt_cmp
		count=(last-first)/type_size;
	}
	return count;
}

size_t __yaooc_count_if(const type_info_t*ti,const_iterator f,const_iterator l,bool(*fun)(const void*))
{
  size_t count=0;
	yaooc_private_const_iterator first=f;
	yaooc_private_const_iterator last=l;
	size_t type_size=yaooc_sizeof(ti);
	for(;first!=last;first+=type_size) {
		if(fun(first))
			count++;
	}
	return count;
}
