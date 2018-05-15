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
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <yaooc/vector.h>

/*
void yaooc_vector_ctor_ti(pointer p,va_list args)
{
  call_constructor(p,yaooc_array_container_ctor_ti,va_arg(args,const type_info_t*));
}
*/
iterator yaooc_vector_push_back(pointer p,const_pointer v)
{
	return yaooc_array_container_insert(p,END(p),v);
}

void yaooc_vector_pop_back(pointer this)
{
  if(SIZE(this) > 0)
    yaooc_array_container_erase(this,AT(this,SIZE(this)-1));
}
/*
iterator yaooc_vector_front(pointer this)
{
	return BEGIN(this);
}
*/
iterator yaooc_vector_back(pointer this)
{
  if(SIZE(this) > 0)
    return AT(this,SIZE(this)-1);
	return END(this);
}
