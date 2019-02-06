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
#ifndef __VARIANT_INCLUDED__
#define __VARIANT_INCLUDED__

/* Begin YAOOCPP output */

#include <yaooc/object.h>
#include <yaooc/stream.h>

typedef enum { VAR_NONE, VAR_CHAR, VAR_UCHAR, VAR_SHORT, VAR_USHORT, VAR_INT, VAR_UINT, VAR_LONG, VAR_ULONG,
			VAR_DOUBLE,VAR_CHAR_PTR,VAR_VOID_PTR,VAR_OBJECT} yaooc_variant_type_t;
/*
  Class Definition for yaooc_variant
*/
yaooc_class_table(yaooc_variant) {
  yaooc_object_class_table_t;
  yaooc_variant_type_t (*type)(const_pointer);
  void (*set)(pointer, yaooc_variant_type_t, const void*);
  const void* (*value)(const_pointer);
};
#define yaooc_variant_parent_class_table ((yaooc_object_class_table_t*)(yaooc_variant_class_table.parent_class_table_))

yaooc_class_instance(yaooc_variant) {
  yaooc_object_class_instance_t;
  yaooc_variant_type_t type_;
  union {
  char ch_;
  unsigned char uch_;
  short sh_;
  unsigned short ush_;
  int int_;
  unsigned int uint_;
  long long long_;
  unsigned long long ulong_;
  double dbl_;
  char* chr_ptr_;
	void* void_ptr_;
  yaooc_object_t* obj_;
  };
};

yaooc_class(yaooc_variant);

/* Type Info Prototypes for yaooc_variant */
void yaooc_variant_default_ctor(pointer);
void yaooc_variant_dtor(pointer);
void yaooc_variant_copy_ctor(pointer,const_pointer);
void yaooc_variant_assign(pointer,const_pointer);

/* Constructors prototypes for yaooc_variant */

/* Table prototypes for yaooc_variant */
#define yaooc_variant_isa yaooc_object_isa
#define yaooc_variant_swap yaooc_object_swap
yaooc_variant_type_t yaooc_variant_type(const_pointer);
void yaooc_variant_set(pointer, yaooc_variant_type_t,const void*);
const void* yaooc_variant_value(const_pointer);

/* Protected prototypes for yaooc_variant */

/* End YAOOCPP output */


#endif
