/*
		Copyright (C) 2016-2020  by Terry N Bezue

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

#include <yaooc/algorithm.h>
#include <stdio.h>
#include <string.h>

iterator __yaooc_move(const_iterator f,const_iterator l,iterator d)
{
	size_t n_bytes=((yaooc_private_const_iterator)l - (yaooc_private_const_iterator)f);
	memmove(d,f,n_bytes);
	return ((yaooc_private_iterator)d)+n_bytes;
}

iterator __yaooc_find(const type_info_t* ti,const_iterator f,const_iterator l,const_pointer value)
{
	yaooc_private_const_iterator first=f;
	yaooc_private_const_iterator last=l;
  rich_compare rich_cmp=get_rich_compare(ti);
	size_t type_size=yaooc_sizeof(ti);
  if(rich_cmp) {
    while(first!=last && __op_ne__(first,value,rich_cmp))
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






iterator __yaooc_copy_if(const type_info_t* ti,const_iterator f,const_iterator l,iterator d,bool(*fun)(const void*))
{
	yaooc_private_const_iterator first=f;
	yaooc_private_const_iterator last=l;
  yaooc_private_iterator dst=d;
  assignment assign_func=get_assignment(ti);
	size_t type_size=yaooc_sizeof(ti);
  for(;first!=last;first+=type_size) {
    if(fun(first)) {
      if(assign_func)
        assign_func(dst,first);
      else
        memcpy(dst,first,type_size);
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
	rich_compare rich_cmp=get_rich_compare(ti);
	size_t type_size=yaooc_sizeof(ti);
  if(rich_cmp) {
    for(;first!=last;first+=type_size) {
      if(__op_eq__(first,value,rich_cmp))
        count++;
    }
  } else {
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





iterator __yaooc_remove(const type_info_t*ti,iterator f,iterator l,const_pointer value)
{
  yaooc_private_iterator first=f;
  yaooc_private_iterator last=l;
  rich_compare rich_cmp=get_rich_compare(ti);
  if(rich_cmp) {
  	size_t type_size=yaooc_sizeof(ti);
    while(first != last) {
      if(__op_eq__(first,value,rich_cmp)) {

        yaooc_private_iterator temp=first+type_size;
        for(;temp!=last;temp+=type_size) {
          if(__op_ne__(temp,value,rich_cmp))
            break;
        }
				last=yaooc_move(temp,last,first);
      } else {
        first+=type_size;
      }
    }
  }
  return first;
}

iterator __yaooc_remove_if(const type_info_t*ti,iterator f,iterator l,bool(*fun)(const void*))
{
  yaooc_private_iterator first=f;
  yaooc_private_iterator last=l;
	size_t type_size=yaooc_sizeof(ti);
  while(first != last) {
    if(fun(first)) {

      yaooc_private_iterator temp=first+type_size;
      for(;temp!=last;temp+=type_size) {
        if(!fun(temp))
          break;
      }
			last=yaooc_move(temp,last,first);
    } else {
      first+=type_size;
    }
  }
  return first;
}

iterator __yaooc_remove_copy(const type_info_t*ti,const_iterator f,const_iterator l,iterator d,const_pointer value)
{
  yaooc_private_const_iterator first=f;
  yaooc_private_const_iterator last=l;
  yaooc_private_iterator dst=d;
  rich_compare rich_cmp=get_rich_compare(ti);
  assignment assign_func=get_assignment(ti);
  if(rich_cmp) {
  	size_t type_size=yaooc_sizeof(ti);
  	for(;first != last;first+=type_size) {
      if(__op_ne__(first,value,rich_cmp)) {
        if(assign_func)
          assign_func(dst,first);
        else
          memcpy(dst,first,type_size);
        dst+=type_size;
      }
    }
  }
  return dst;
}

iterator __yaooc_remove_copy_if(const type_info_t*ti,const_iterator f,const_iterator l,iterator d,bool(*fun)(const void*))
{
  yaooc_private_const_iterator first=f;
  yaooc_private_const_iterator last=l;
  yaooc_private_iterator dst=d;
  assignment assign_func=get_assignment(ti);
	size_t type_size=yaooc_sizeof(ti);
	for(;first != last;first+=type_size) {
    if(!fun(first)) {
      if(assign_func)
        assign_func(dst,first);
      else
        memcpy(dst,first,type_size);
      dst+=type_size;
    }
  }
  return dst;
}

yaooc_iterator_pair_t __yaooc_mismatch(const type_info_t* ti,const_iterator f1,const_iterator l1,
				const_iterator f2,	const_iterator l2)
{
	yaooc_private_const_iterator first1=f1;
	yaooc_private_const_iterator last1=l1;
	yaooc_private_const_iterator first2=f2;
	yaooc_private_const_iterator last2=l2;
  rich_compare rich_cmp=get_rich_compare(ti);
  size_t type_size=yaooc_sizeof(ti);
  for(;first1!=last1 && first2!=last2;first1+=type_size,first2+=type_size) {
    if(__op_ne__(first1,first2,rich_cmp))
      break;
  }
	return (yaooc_iterator_pair_t) { first1,first2 };
}

const_iterator __yaooc_find_end(const type_info_t* ti,const_iterator f,const_iterator l,
      const_iterator sf,const_iterator sl)
{
  yaooc_private_const_iterator first=f;
  yaooc_private_const_iterator last=l;
  yaooc_private_const_iterator s_first=sf;
  yaooc_private_const_iterator s_last=sl;
	size_t type_size=yaooc_sizeof(ti);
  rich_compare rich_cmp=get_rich_compare(ti);
  yaooc_private_const_iterator pos=(yaooc_private_iterator)last;
  if(rich_cmp) {
    yaooc_private_iterator temp=(yaooc_private_iterator)last-(s_last-s_first);
    for(;temp>=first;temp-=type_size,last-=type_size) {
      if(__yaooc_mismatch(ti,temp,last,s_first,s_last).first == last) {
        pos=temp;
        break;
      }
    }
  } else {
    pos=last - (s_last-s_first);
    if(pos < first)
      pos=last;
  }
  return pos;
}

const_iterator __yaooc_find_first_of(const type_info_t* ti,const_iterator f,const_iterator l,
      const_iterator sf,const_iterator sl)
{
  yaooc_private_const_iterator first=f;
  yaooc_private_const_iterator last=l;
  yaooc_private_const_iterator s_first=sf;
  yaooc_private_const_iterator s_last=sl;
	size_t type_size=yaooc_sizeof(ti);
  rich_compare rich_cmp=get_rich_compare(ti);
  if(rich_cmp) {
    for(;first!=last;first+=type_size) {
      yaooc_private_const_iterator temp;
      for(temp=s_first;temp!=s_last;temp+=type_size) {
        if(__op_eq__(first,temp,rich_cmp))
          return first;
      }
    }
  }
  return last;
}

const_iterator __yaooc_search(const type_info_t* ti,const_iterator f,const_iterator l,
      const_iterator sf,const_iterator sl)
{
  yaooc_private_const_iterator first=f;
  yaooc_private_const_iterator last=l;
  yaooc_private_const_iterator s_first=sf;
  yaooc_private_const_iterator s_last=sl;
	size_t type_size=yaooc_sizeof(ti);
  if(s_first != s_last) {
    yaooc_private_const_iterator last_temp=first+(s_last-s_first);
    for(;first!=last && last_temp <= last;first+=type_size,last_temp+=type_size) {
      if(__yaooc_mismatch(ti,first,last_temp,sf,sl).first == last_temp)
        return first;
    }
  }
  return last;
}
