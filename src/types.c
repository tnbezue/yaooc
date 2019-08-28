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

#include <yaooc/new.h>
#include <string.h>
#include <math.h>
/*
  Type info for POD
*/
#define POD_TYPE_INFO_IMPLEMENTATION(T) \
bool T ## _less_than_compare(const T ## _t * v1,const T ## _t * v2) { return *v1 < *v2; } \
__DEFINE_POD_TYPE_INFO__(T,(less_than_compare)T ## _less_than_compare,(to_stream)T ## _to_stream,(from_stream) T ## _from_stream)

POD_TYPE_INFO_IMPLEMENTATION(char);
POD_TYPE_INFO_IMPLEMENTATION(uchar);
POD_TYPE_INFO_IMPLEMENTATION(short);
POD_TYPE_INFO_IMPLEMENTATION(ushort);
POD_TYPE_INFO_IMPLEMENTATION(int);
POD_TYPE_INFO_IMPLEMENTATION(uint);
POD_TYPE_INFO_IMPLEMENTATION(long);
POD_TYPE_INFO_IMPLEMENTATION(ulong);
bool double_less_than_compare(const double* lhs,const double* rhs)
{
  if(fabs(*lhs-*rhs)<0.000001)
    return false;
  return *lhs < *rhs;
}
const pod_type_info_t __double_ti ={
  .min_flag_=0,
  .pod_flag_=1,
	.type_size_ = sizeof(double),
	.less_than_compare_ = (less_than_compare) double_less_than_compare ,
	.to_stream_ = (to_stream) double_to_stream,
	.from_stream_ = (from_stream) double_from_stream,
};
const type_info_t* const double_ti = (const type_info_t*)&__double_ti;

//POD_TYPE_INFO_IMPLEMENTATION(double);
//POD_TYPE_INFO_IMPLEMENTATION(pointer);
bool pointer_less_than_compare(const pointer *lhs,const pointer *rhs) { return *lhs < *rhs; }

POD_TYPE_INFO_IMPLEMENTATION(size);
const pod_type_info_t __pointer_ti ={
  .min_flag_=0,
  .pod_flag_=1,
	.type_size_ = sizeof(pointer),
	.less_than_compare_ = (less_than_compare) pointer_less_than_compare ,
	.to_stream_ = (to_stream) NULL,
	.from_stream_ = (from_stream) NULL,
};
const type_info_t* const pointer_ti = (const type_info_t*)&__pointer_ti;

bool yaooc_ccs_less_than_compare(const_pointer p1,const_pointer p2)
{
	return strcmp(p1,p2) < 0;
}

//DEFINE_TYPE_INFO(yaooc_ccs,N,N,N,N,Y,Y,Y,N,NULL)
DEFINE_POD_TYPE_INFO(yaooc_ccs,Y,Y,Y);
