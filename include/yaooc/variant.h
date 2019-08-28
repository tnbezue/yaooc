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
			VAR_DOUBLE,VAR_CHAR_PTR,VAR_VOID_PTR,VAR_OBJECT_PTR} yaooc_variant_type_t;
typedef union {
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
  yaooc_object_t* obj_ptr_;
} __variant_t;
//#define STATIC_VARIANT_CTOR(N,T,V) newp_ctor(&N,yaooc_variant,yaooc_variant_ctor_type_value,T,V)
#define STATIC_VARIANT_CTOR(N) N=((yaooc_variant_t) { .class_table_=&yaooc_variant_class_table,.type_=VAR_NONE})
#define STATIC_VARIANT_CTOR_I(N,I) N=((yaooc_variant_t) { .class_table_=&yaooc_variant_class_table,.type_=VAR_INT,.int_=I})
#define STATIC_VARIANT_CTOR_D(N,D) N=((yaooc_variant_t) { .class_table_=&yaooc_variant_class_table,.type_=VAR_DOUBLE,.dbl_=D})
#define STATIC_VARIANT_CTOR_S(N,S) N=((yaooc_variant_t) { .class_table_=&yaooc_variant_class_table,.type_=VAR_CHAR_PTR,.chr_ptr_=S})
#define STATIC_VARIANT_CTOR_V(N,V) N=((yaooc_variant_t) { .class_table_=&yaooc_variant_class_table,.type_=VAR_VOID_PTR,.void_ptr_=V})
#define STATIC_VARIANT_CTOR_O(N,O) N=((yaooc_variant_t) { .class_table_=&yaooc_variant_class_table,.type_=VAR_OBJECT_PTR,.obj_ptr_=O})
#define STATIC_VARIANT_DTOR(V) deletep(&V,yaooc_variant)
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
  yaooc_variant_type_t type_;
  __variant_t;
};

yaooc_class(yaooc_variant);

/* Type Info Prototypes for yaooc_variant */
void yaooc_variant_default_ctor(pointer);
void yaooc_variant_dtor(pointer);
void yaooc_variant_copy_ctor(pointer,const_pointer);
void yaooc_variant_assign(pointer,const_pointer);

/* Constructors prototypes for yaooc_variant */
void yaooc_variant_ctor_type_value(pointer,va_list);

/* Table prototypes for yaooc_variant */
#define yaooc_variant_isa yaooc_object_isa
void yaooc_variant_swap(pointer,pointer);
yaooc_variant_type_t yaooc_variant_type(const_pointer);
void yaooc_variant_set(pointer, yaooc_variant_type_t,const void*);
const void* yaooc_variant_value(const_pointer);

/* Protected prototypes for yaooc_variant */

/* End YAOOCPP output */


#endif
