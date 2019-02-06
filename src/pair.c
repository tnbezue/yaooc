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

#include <yaooc/pair.h>
#include <yaooc/stream.h>

void __pair_to_stream(const type_info_t* k_ti,const_pointer k,const type_info_t* v_ti,const_pointer v,pointer s)
{
	to_stream key_to_s = get_to_stream(k_ti);
	to_stream value_to_s = get_to_stream(v_ti);
	yaooc_ostream_pointer strm=s;
	if(key_to_s && value_to_s) {
		M(strm,printf,"{");
		key_to_s(k,s);
		M(strm,printf,",");
		value_to_s(v,s);
		M(strm,printf,"}");
	}
}

void __pair_from_stream(const type_info_t* k_ti,pointer k,const type_info_t* v_ti,pointer v,pointer s)
{
	from_stream key_from_s = get_from_stream(k_ti);
	from_stream value_from_s = get_from_stream(v_ti);
//	yaooc_istream_pointer strm=s;
	if(key_from_s && value_from_s) {
		key_from_s(k,s);
		value_from_s(v,s);
	}

}
