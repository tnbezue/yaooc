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

#include <yaooc/integer.h>
#include <yaooc/stream.h>

#include <stdio.h>

/*  Begin YAOOC PreProcessor generated content */


/* yaooc_integer private members */

/* yaooc_integer type info members */
void yaooc_integer_default_ctor(pointer p)
{
  yaooc_integer_pointer this=p;
  this->value_=0;
}

void yaooc_integer_copy_ctor(pointer p,const_pointer s)
{
  yaooc_integer_pointer this=p;
  yaooc_integer_const_pointer src=s;
  this->value_=src->value_;
}

void yaooc_integer_assign(pointer p,const_pointer s)
{
  yaooc_integer_pointer this=p;
  yaooc_integer_const_pointer src=s;
  this->value_=src->value_;
}

bool yaooc_integer_less_than_compare(const_pointer p1,const_pointer p2)
{
  yaooc_integer_const_pointer vp1=p1;
  yaooc_integer_const_pointer vp2=p2;
  return vp1->value_<vp2->value_;
}


/* Constructors for yaooc_integer */
void yaooc_integer_ctor_int(pointer p,va_list args)
{
  yaooc_integer_pointer this=p;
  this->value_ = va_arg(args,long);
}

/* yaooc_integer protected members */

/* Class table methods for yaooc_integer */
const char* yaooc_integer_isa(const_pointer p) { return "yaooc_integer_t"; }

void yaooc_integer_swap(pointer p,pointer o)
{
  yaooc_integer_pointer this=p;
  yaooc_integer_pointer other=o;
  SWAP(long,this->value_,other->value_);
}

void yaooc_integer_set(pointer p,long value)
{
  yaooc_integer_pointer this=p;
  this->value_=value;
}

long yaooc_integer_get(const_pointer p)
{
  return ((yaooc_integer_const_pointer)p)->value_;
}

void yaooc_integer_to_stream(const_pointer p,pointer s)
{
	yaooc_integer_const_pointer this=p;
	yaooc_ostream_pointer strm=s;
	M(strm,printf,"%ld",this->value_);
}

void yaooc_integer_from_stream(pointer p,pointer s)
{
	yaooc_integer_pointer this=p;
	yaooc_istream_pointer strm=s;
	M(strm,scanf,"%ld",&this->value_);
}

/* Class table for yaooc_integer */
yaooc_integer_class_table_t yaooc_integer_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
  .isa = (const char* (*) (const_pointer)) yaooc_integer_isa,
  .is_descendant = (bool (*) (const_pointer,const char*)) yaooc_object_is_descendant,
  .swap = (void (*) (pointer,pointer)) yaooc_integer_swap,
  .set = (void (*) (pointer,long)) yaooc_integer_set,
  .get = (long (*) (const_pointer)) yaooc_integer_get,
};

DEFINE_TYPE_INFO(yaooc_integer,yaooc_integer_default_ctor,NULL,yaooc_integer_copy_ctor,
		yaooc_integer_assign,yaooc_integer_less_than_compare,yaooc_integer_to_stream,
		yaooc_integer_from_stream,&yaooc_integer_class_table,yaooc_object)

/*  End YAOOC PreProcessor generated content */
