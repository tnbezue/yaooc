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

#include <yaooc/stack.h>

void yaooc_stack_push(pointer p,const_pointer v)
{
  yaooc_array_container_insert(p,BEGIN(p),v);
}

void yaooc_stack_pop(pointer p)
{
  if(SIZE(p) > 0)
    yaooc_array_container_erase(p,yaooc_array_container_begin(p));
}
