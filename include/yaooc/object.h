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

#ifndef __YAOOC_OBJECT_INCLUDED__
#define __YAOOC_OBJECT_INCLUDED__

#include <yaooc/new.h>

/*  Begin YAOOC PreProcessor generated content */

/*
  Class definition for yaooc_object
*/
yaooc_class_table(yaooc_object)
{
  const class_table_t* parent_class_table_;
  const char* (*isa)(const_pointer);
  bool (*is_descendant)(const_pointer,const char*);
  void (*swap)(pointer,pointer);
};

yaooc_class_instance(yaooc_object)
{
};

yaooc_class(yaooc_object);

/* Prototypes for yaooc_object type info */
#define yaooc_object_default_ctor yaooc_object_do_nothing_default_ctor
#define yaooc_object_dtor yaooc_object_do_nothing_dtor
#define yaooc_object_copy_ctor yaooc_object_do_nothing_copy_ctor
#define yaooc_object_assign yaooc_object_do_nothing_assign

/* Constructors for yaooc_object */

/* Prototypes for yaooc_object class table*/
const char* yaooc_object_isa(const_pointer);
bool yaooc_object_is_descendant(const_pointer,const char*);
void yaooc_object_swap(pointer,pointer);

/* Prototypes for yaooc_object class instance*/

/* Prototypes for yaooc_object class protected items*/

/*  End YAOOC PreProcessor generated content */

#define ISA(p,o) (strcmp(((yaooc_object_pointer)(p))->class_table_->isa((p)),# o "_t") == 0)
#define IS_DESCENDANT(p,o) (((yaooc_object_pointer)(p))->class_table_->is_descendant((p),# o "_t"))

void yaooc_do_nothing_default_ctor(pointer);
#define yaooc_do_nothing_dtor yaooc_do_nothing_default_ctor
void yaooc_do_nothing_copy_ctor(pointer,const_pointer);
#define yaooc_do_nothing_assign yaooc_do_nothing_copy_ctor

#endif
