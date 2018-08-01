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

#include <yaooc/types.h>
#include <yaooc/new.h>
#include <yaooc/macros.h>
#include <string.h>
/*
  Type info for POD
*/
#define POD_TYPE_INFO_IMPLEMENTATION(T) \
bool T ## _less_than_compare(const T ## _t * v1,const T ## _t * v2) { return *v1 < *v2; } \
__DEFINE_TYPE_INFO__(T,NULL,NULL,NULL,NULL,(less_than_compare)T ## _less_than_compare,(to_stream)T ## _to_stream,(from_stream) T ## _from_stream,NULL,NULL)

POD_TYPE_INFO_IMPLEMENTATION(char)
POD_TYPE_INFO_IMPLEMENTATION(uchar)
POD_TYPE_INFO_IMPLEMENTATION(short)
POD_TYPE_INFO_IMPLEMENTATION(ushort)
POD_TYPE_INFO_IMPLEMENTATION(int)
POD_TYPE_INFO_IMPLEMENTATION(uint)
POD_TYPE_INFO_IMPLEMENTATION(long)
POD_TYPE_INFO_IMPLEMENTATION(ulong)
POD_TYPE_INFO_IMPLEMENTATION(double)
POD_TYPE_INFO_IMPLEMENTATION(pointer)
POD_TYPE_INFO_IMPLEMENTATION(size)

bool yaooc_ccs_less_than_compare(const_pointer p1,const_pointer p2)
{
	return strcmp(p1,p2) < 0;
}

DEFINE_TYPE_INFO(yaooc_ccs,N,N,N,N,Y,Y,Y,N,NULL)
