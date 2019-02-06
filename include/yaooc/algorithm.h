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

#ifndef __ALGORITHM_INCLUDED__
#define __ALGORITHM_INCLUDED__

#include <yaooc/new.h>

iterator __yaooc_find(const type_info_t*,const_iterator,const_iterator,const_pointer);
#define yaooc_find(T,F,L,V) __yaooc_find(T ## _ti,F,L,V)
iterator __yaooc_copy(const type_info_t*,const_iterator,const_iterator,iterator);
#define yaooc_copy(T,F,L,D) __yaooc_copy(T ## _ti,F,L,D)
void __yaooc_for_each(const type_info_t*,iterator,iterator,void(*f)(void*));
#define yaooc_for_each(T,F,L,FUN) __yaooc_for_each(T ## _ti,F,L,FUN)
size_t __yaooc_count(const type_info_t*,const_iterator,const_iterator,const_pointer);
#define yaooc_count(T,F,L,V) __yaooc_count(T ## _ti,F,L,V)
size_t __yaooc_count_if(const type_info_t*,const_iterator,const_iterator,bool(*fun)(const void*));
#define yaooc_count_if(T,F,L,FUN) __yaooc_count_if(T ## _ti,F,L,FUN)
void __yaooc_fill(const type_info_t*,iterator,iterator,const_pointer);
#define yaooc_fill(T,F,L,V) __yaooc_fill(T ## _ti,F,L,V)

#endif
