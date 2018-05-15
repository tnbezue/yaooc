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

#ifndef __INTEGER_INCLUDED__
#define __INTEGER_INCLUDED__

#include <yaooc/object.h>

/*  Begin YAOOC PreProcessor generated content */


/*
  Class definition for yaooc_integer
*/
class_table(yaooc_integer)
{
  yaooc_object_class_table_t;
  void (*set)(pointer,long);
  long (*get)(const_pointer);
};
#define yaooc_integer_parent_class_table ((yaooc_object_class_table_t*)(yaooc_integer_class_table.parent_class_table_))

class_instance(yaooc_integer)
{
  yaooc_object_class_instance_t;
  long value_;
};

class(yaooc_integer);

/* Prototypes for yaooc_integer type info */
void yaooc_integer_default_ctor(pointer);
void yaooc_integer_copy_ctor(pointer,const_pointer);
void yaooc_integer_assign(pointer,const_pointer);
bool yaooc_integer_less_than_compare(const_pointer,const_pointer);

/* Prototypes for yaooc_integer constructors */
void yaooc_integer_ctor_int(pointer,va_list);

/* Prototypes for yaooc_integer class table */
const char* yaooc_integer_isa(const_pointer);
#define yaooc_integer_is_descendant yaooc_object_is_descendant
void yaooc_integer_swap(pointer,pointer);
char* yaooc_integer_to_s(const_pointer);
void yaooc_integer_set(pointer,long);
long yaooc_integer_get(const_pointer);

/* Prototypes for yaooc_integer protected members */

/*  End YAOOC PreProcessor generated content */

#endif
