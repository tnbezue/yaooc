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

#include <yaooc/new.h>
#include <string.h>
#include <math.h>
/*
  Type info for POD
*/
#define POD_TYPE_INFO_IMPLEMENTATION(T) \
int T ## _rich_compare(const T ## _t * lhs,const T ## _t * rhs) { return (*lhs > *rhs) - (*lhs < *rhs); } \
__DEFINE_POD_TYPE_INFO__(T,(rich_compare)T ## _rich_compare,(to_stream)T ## _to_stream,(from_stream) T ## _from_stream)

POD_TYPE_INFO_IMPLEMENTATION(char);
POD_TYPE_INFO_IMPLEMENTATION(uchar);
POD_TYPE_INFO_IMPLEMENTATION(short);
POD_TYPE_INFO_IMPLEMENTATION(ushort);
POD_TYPE_INFO_IMPLEMENTATION(int);
POD_TYPE_INFO_IMPLEMENTATION(uint);
POD_TYPE_INFO_IMPLEMENTATION(long);
POD_TYPE_INFO_IMPLEMENTATION(ulong);
int double_rich_compare(const double* lhs,const double* rhs)
{
  if(fabs(*lhs-*rhs)<1e-8)
    return 0;
  if(*lhs < *rhs)
    return -1;
  return 1;
}
const pod_type_info_t __double_ti ={
  .min_flag_=0,
  .pod_flag_=1,
	.type_size_ = sizeof(double),
	.rich_compare_ = (rich_compare) double_rich_compare ,
	.to_stream_ = (to_stream) double_to_stream,
	.from_stream_ = (from_stream) double_from_stream,
};
const type_info_t* const double_ti = (const type_info_t*)&__double_ti;

//POD_TYPE_INFO_IMPLEMENTATION(double);
//POD_TYPE_INFO_IMPLEMENTATION(pointer);
bool pointer_rich_compare(const pointer *lhs,const pointer *rhs) { return *lhs < *rhs; }

POD_TYPE_INFO_IMPLEMENTATION(size);
const pod_type_info_t __pointer_ti ={
  .min_flag_=0,
  .pod_flag_=1,
	.type_size_ = sizeof(pointer),
	.rich_compare_ = (rich_compare) pointer_rich_compare ,
	.to_stream_ = (to_stream) NULL,
	.from_stream_ = (from_stream) NULL,
};
const type_info_t* const pointer_ti = (const type_info_t*)&__pointer_ti;

int yaooc_ccs_rich_compare(const_pointer p1,const_pointer p2)
{
	return strcmp(p1,p2);
}

//DEFINE_TYPE_INFO(yaooc_ccs,N,N,N,N,Y,Y,Y,N,NULL)
DEFINE_POD_TYPE_INFO(yaooc_ccs,Y,Y,Y);
