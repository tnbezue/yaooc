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
#include <yaooc/ordered_set.h>

#include <string.h>
#include <stdio.h>

void yaooc_ordered_set_ctor(pointer p,va_list args)
{
  call_constructor(p,yaooc_unique_ordered_array_container_ctor,va_arg(args,const type_info_t*));
}

iterator yaooc_ordered_set_insert(pointer p,const_iterator value)
{
	return yaooc_unique_ordered_array_container_insert(p,yaooc_array_container_end(p),value);
}
iterator yaooc_ordered_set_insert_range(pointer p,const_iterator first,const_iterator last)
{
	return yaooc_unique_ordered_array_container_insert_range(p,yaooc_array_container_end(p),first,last);
}

iterator yaooc_ordered_set_erase(pointer p,iterator pos)
{
	return yaooc_array_container_erase(p,pos);
}

iterator yaooc_ordered_set_erase_range(pointer p,iterator first,iterator last)
{
	return yaooc_array_container_erase_range(p,first,last);
}
iterator yaooc_ordered_set_find(pointer p,const_iterator value)
{
	iterator end=yaooc_array_container_end(p);
	yaooc_ordered_array_container_find_result_t fr=yaooc_ordered_array_container_find_private(p,value);
	if(!fr.found_)
		return end;
//	return yaooc_ordered_array_container_begin(p)+fr.index_;
  return fr.position_;
}

const_iterator yaooc_ordered_set_cfind(const_pointer p,const_iterator value)
{
	const_iterator end=yaooc_array_container_end((pointer)p);
	yaooc_ordered_array_container_find_result_t fr=yaooc_ordered_array_container_find_private((pointer)p,value);
	if(!fr.found_)
		return end;
//	return yaooc_ordered_array_container_cbegin(p)+fr.index_;
  return fr.position_;
}

pointer yaooc_ordered_set_sunion(const_pointer p,const_pointer o)
{
	return (pointer)p;
}

/*
yaooc_ordered_set_pointer yaooc_ordered_set_sunion_(pointer p,const_pointer o)
{
	yaooc_ordered_set_pointer this=p;
	const char* is=(const char*)yaooc_array_container_cbegin(o);
	const char* end=(const char*)yaooc_array_container_cend(o);
	yaooc_size_type element_size=yaooc_sizeof(this->type_info_);
	for(;is!=end;is+=element_size)
		yaooc_ordered_set_insert(this,is);
	return this;
}

yaooc_ordered_set_pointer yaooc_ordered_set_sdiff(pointer p,const_pointer o)
{
	yaooc_ordered_set_pointer new_ordered_set=new_copy(p);
	return yaooc_ordered_set_sdiff_(new_ordered_set,o);
}

yaooc_ordered_set_pointer yaooc_ordered_set_sdiff_(pointer p,const_pointer o)
{
	yaooc_ordered_set_pointer this=p;
	const char* is=(const char*)yaooc_array_container_cbegin(o);
	const char* end=(const char*)yaooc_array_container_cend(o);
	yaooc_size_type element_size=yaooc_sizeof(this->type_info_);
	pointer item;
	for(;is!=end;is+=element_size) {
		item=M(this,find,is);
		if(item != M(this,end))
			yaooc_ordered_set_erase(this,(pointer)item);
	}
	return this;
}
*/
