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

#include <yaooc/real.h>
#include <yaooc/stream.h>
#include <stdio.h>

/*  Begin YAOOC PreProcessor generated content */


/* yaooc_real private members */

/* yaooc_real type info members */
void yaooc_real_default_ctor(pointer p)
{
  yaooc_real_pointer this=p;
  this->value_=0.0;
}

void yaooc_real_copy_ctor(pointer p,const_pointer s)
{
  yaooc_real_pointer this=p;
  yaooc_real_const_pointer src=s;
  this->value_=src->value_;
}

void yaooc_real_assign(pointer p,const_pointer s)
{
  yaooc_real_pointer this=p;
  yaooc_real_const_pointer src=s;
  this->value_=src->value_;
}

bool yaooc_real_less_than_compare(const_pointer p1,const_pointer p2)
{
  yaooc_real_const_pointer vp1=p1;
  yaooc_real_const_pointer vp2=p2;
  return vp1->value_<vp2->value_;
}


/* Constructors for yaooc_real */
void yaooc_real_ctor_real(pointer p,va_list args)
{
  yaooc_real_pointer this=p;
  this->value_ = va_arg(args,double);
}

/* yaooc_real protected members */

/* Class table methods for yaooc_real */
const char* yaooc_real_isa(const_pointer p) { return "yaooc_real_t"; }

void yaooc_real_swap(pointer p,pointer o)
{
  yaooc_real_pointer this=p;
  yaooc_real_pointer other=o;
  SWAP(double,this->value_,other->value_);
}

void yaooc_real_set(pointer p,double value)
{
  yaooc_real_pointer this=p;
  this->value_=value;
}

double yaooc_real_get(const_pointer p)
{
  return ((yaooc_real_const_pointer)p)->value_;
}

void yaooc_real_to_stream(const_pointer p,pointer s)
{
	yaooc_real_const_pointer this=p;
	yaooc_ostream_pointer strm=s;
	M(strm,printf,"%lf",this->value_);
}

void yaooc_real_from_stream(pointer p,pointer s)
{
	yaooc_real_pointer this=p;
	yaooc_istream_pointer strm=s;
	M(strm,scanf,"%lf",&this->value_);
}

/* Class table for yaooc_real */
yaooc_real_class_table_t yaooc_real_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
  .isa = (const char* (*) (const_pointer)) yaooc_real_isa,
  .is_descendant = (bool (*) (const_pointer,const char*)) yaooc_object_is_descendant,
  .swap = (void (*) (pointer,pointer)) yaooc_real_swap,
  .set = (void (*) (pointer,double)) yaooc_real_set,
  .get = (double (*) (const_pointer)) yaooc_real_get,
};

DEFINE_TYPE_INFO(yaooc_real,Y,N,Y,Y,Y,Y,Y,Y,yaooc_object)

/*  End YAOOC PreProcessor generated content */
