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

#include <yaooc/ordered_map.h>

#include <string.h>
#include <stdio.h>

yaooc_ordered_array_container_find_result_t yaooc_ordered_map_insert(pointer p,const_iterator value)
{
	yaooc_unique_ordered_array_container_pointer this=p;
	yaooc_unique_ordered_array_container_find_result_t fr=yaooc_unique_ordered_array_container_find_private(p,value);
  if(!fr.found_) {
    yaooc_size_type index=INDEX(this,fr.position_);
    if(yaooc_unique_ordered_array_container_increase_capacity(this,1))
      fr.position_=BEGIN(this)+index*yaooc_sizeof(this->type_info_);
		yaooc_array_container_insert_n_private(this,index,1,value);
	}
	return fr;

//  return yaooc_unique_ordered_array_container_insert(p,yaooc_array_container_end(p),value);
}

iterator yaooc_ordered_map_insert_range(pointer p,const_iterator first,const_iterator last)
{
	return yaooc_unique_ordered_array_container_insert_range(p,yaooc_array_container_end(p),first,last);
}

void yaooc_ordered_map_ctor(pointer p,va_list args)
{
	call_constructor(p,yaooc_unique_ordered_array_container_ctor,va_arg(args,const type_info_t*));
}

iterator yaooc_ordered_map_private_find(pointer p,const_pointer k,yaooc_size_type ks,yaooc_size_type os)
{
  char obj[os];
  memcpy(obj,k,ks);
  return yaooc_unique_ordered_array_container_find(p,obj);
}

/*iterator yaooc_ordered_map_private_insert_pair(pointer p,const_pointer k,const type_info* k_ti,const_pointer v,const type_info* v_ti)
{
  iterator pos
}
*/
/*
iterator yaooc_ordered_map_private_find(pointer p,const_pointer k,yaooc_size_type ks,yaooc_size_type os)
{
  char obj[os];
  memcpy(obj,k,ks);
  return yaooc_unique_container_find(p,obj);
}
*/
