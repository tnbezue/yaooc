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

#include <yaooc/object.h>

#include <string.h>

/* Private members for yaooc_object */

/* Protected members for yaooc_object */

/* Typeinfo for yaooc_object */
void yaooc_object_default_ctor(pointer p) { }

void yaooc_object_copy_ctor(pointer p,const_pointer o) { }

bool yaooc_object_less_than_compare(const_pointer p1,const_pointer p2)
{
  return false;
}

/* Additional constructors for yaooc_object */

/* Class table members for yaooc_object */
const char* yaooc_object_isa(const_pointer p) { return "yaooc_object_t"; }

bool yaooc_object_is_descendant(const_pointer p,const char* s)
{
  yaooc_object_class_table_t* current_class_table=(yaooc_object_class_table_t*)(((yaooc_object_pointer)p)->class_table_);
  while(current_class_table != NULL) {
    if(strcmp(current_class_table->isa(p),s) == 0)
      return true;
    current_class_table=(yaooc_object_class_table_t*)current_class_table->parent_class_table_;
  }
  return false;
}

void yaooc_object_swap(pointer d,pointer s)
{
}

char* yaooc_object_to_s(const_pointer p)
{
  return NULL;
};

/* Instance members for yaooc_object */

/* yaooc_object class table */
yaooc_object_class_table_t yaooc_object_class_table =
{
  .parent_class_table_ = (const class_table_t*) NULL,
  .isa = (const char* (*) (const_pointer p)) yaooc_object_isa,
  .is_descendant = (bool (*) (const_pointer p,const char*)) yaooc_object_is_descendant,
  .swap = (void (*) (pointer p,pointer)) yaooc_object_swap,
};


DEFINE_TYPE_INFO(yaooc_object,Y,N,Y,Y,Y,N,N,Y,NULL)
