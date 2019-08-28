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

#ifndef __REAL_INCLUDED__
#define __REAL_INCLUDED__

#include <yaooc/object.h>

/*  Begin YAOOC PreProcessor generated content */


/*
  Class definition for yaooc_real
*/
yaooc_class_table(yaooc_real)
{
  yaooc_object_class_table_t;
  void (*set)(pointer,double);
  double (*get) (const_pointer);
};
#define yaooc_real_parent_class_table ((yaooc_object_class_table_t*)(yaooc_real_class_table.parent_class_table_))

yaooc_class_instance(yaooc_real)
{
  double value_;
};

yaooc_class(yaooc_real);

/* Prototypes for yaooc_real type info */
void yaooc_real_default_ctor(pointer);
void yaooc_real_copy_ctor(pointer,const_pointer);
void yaooc_real_assign(pointer,const_pointer);
bool yaooc_real_less_than_compare(const_pointer,const_pointer);

/* Prototypes for yaooc_real constructors */
void yaooc_real_ctor_real(pointer,va_list);

/* Prototypes for yaooc_real class table */
void yaooc_real_swap(pointer,pointer);
char* yaooc_real_to_s(const_pointer);
void yaooc_real_set(pointer,double);
double yaooc_real_get(const_pointer);

/* Prototypes for yaooc_real protected members */

/*  End YAOOC PreProcessor generated content */

#endif
