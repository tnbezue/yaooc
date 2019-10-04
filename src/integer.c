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

int yaooc_integer_rich_compare(const_pointer p1,const_pointer p2)
{
  yaooc_integer_const_pointer vp1=p1;
  yaooc_integer_const_pointer vp2=p2;
  return vp1->value_-vp2->value_;
}


/* Constructors for yaooc_integer */
void yaooc_integer_ctor_int(pointer p,va_list args)
{
  yaooc_integer_pointer this=p;
  this->value_ = va_arg(args,long long);
}

/* yaooc_integer protected members */

/* Class table methods for yaooc_integer */
void yaooc_integer_swap(pointer p,pointer o)
{
  yaooc_integer_pointer this=p;
  yaooc_integer_pointer other=o;
  SWAP(long long,this->value_,other->value_);
}

void yaooc_integer_set(pointer p,long long value)
{
  yaooc_integer_pointer this=p;
  this->value_=value;
}

long long yaooc_integer_get(const_pointer p)
{
  return ((yaooc_integer_const_pointer)p)->value_;
}

void yaooc_integer_to_stream(const_pointer p,ostream_pointer s)
{
	yaooc_integer_const_pointer this=p;
	yaooc_ostream_pointer strm=s;
	M(strm,printf,"%ld",this->value_);
}

void yaooc_integer_from_stream(pointer p,istream_pointer s)
{
	yaooc_integer_pointer this=p;
	yaooc_istream_pointer strm=s;
	M(strm,scanf,"%ld",&this->value_);
}

/* Class table for yaooc_integer */
yaooc_integer_class_table_t yaooc_integer_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
  .type_name_ = (const char*) "yaooc_integer_t",
  .swap = (void (*) (pointer,pointer)) yaooc_integer_swap,
  .set = (void (*) (pointer,long long)) yaooc_integer_set,
  .get = (long long(*) (const_pointer)) yaooc_integer_get,
};

DEFINE_TYPE_INFO(yaooc_integer,Y,N,Y,Y,Y,Y,Y,Y,yaooc_object);

/* yaooc_unsigned_integer private members */

/* yaooc_unsigned_integer type info members */
void yaooc_unsigned_integer_default_ctor(pointer p)
{
	yaooc_unsigned_integer_pointer this=p;
	this->value_=0;
}

void yaooc_unsigned_integer_copy_ctor(pointer p,const_pointer s)
{
	yaooc_unsigned_integer_pointer this=p;
	yaooc_unsigned_integer_const_pointer src=s;
	this->value_=src->value_;
}

void yaooc_unsigned_integer_assign(pointer p,const_pointer s)
{
	yaooc_unsigned_integer_pointer this=p;
	yaooc_unsigned_integer_const_pointer src=s;
	this->value_=src->value_;
}

int yaooc_unsigned_integer_rich_compare(const_pointer p1,const_pointer p2)
{
	yaooc_unsigned_integer_const_pointer vp1=p1;
	yaooc_unsigned_integer_const_pointer vp2=p2;
	return (int)(vp1->value_-vp2->value_);
}


/* Constructors for yaooc_unsigned_integer */
void yaooc_unsigned_integer_ctor_unsigned_int(pointer p,va_list args)
{
	yaooc_unsigned_integer_pointer this=p;
	this->value_ = va_arg(args,unsigned long long);
}

/* yaooc_unsigned_integer protected members */

/* Class table methods for yaooc_unsigned_integer */
void yaooc_unsigned_integer_swap(pointer p,pointer o)
{
	yaooc_unsigned_integer_pointer this=p;
	yaooc_unsigned_integer_pointer other=o;
	SWAP(unsigned long long,this->value_,other->value_);
}

void yaooc_unsigned_integer_set(pointer p,unsigned long long value)
{
	yaooc_unsigned_integer_pointer this=p;
	this->value_=value;
}

unsigned long long yaooc_unsigned_integer_get(const_pointer p)
{
	return ((yaooc_unsigned_integer_const_pointer)p)->value_;
}

void yaooc_unsigned_integer_to_stream(const_pointer p,ostream_pointer s)
{
	yaooc_unsigned_integer_const_pointer this=p;
	yaooc_ostream_pointer strm=s;
	M(strm,printf,"%lu",this->value_);
}

void yaooc_unsigned_integer_from_stream(pointer p,istream_pointer s)
{
	yaooc_unsigned_integer_pointer this=p;
	yaooc_istream_pointer strm=s;
	M(strm,scanf,"%lu",&this->value_);
}

/* Class table for yaooc_integer */
yaooc_unsigned_integer_class_table_t yaooc_unsigned_integer_class_table =
{
	.parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
	.type_name_ = (const char*) "yaooc_unsigned_integer_t",
	.swap = (void (*) (pointer,pointer)) yaooc_unsigned_integer_swap,
	.set = (void (*) (pointer,unsigned long long)) yaooc_unsigned_integer_set,
	.get = (unsigned long long(*) (const_pointer)) yaooc_unsigned_integer_get,
};

DEFINE_TYPE_INFO(yaooc_unsigned_integer,Y,N,Y,Y,Y,Y,Y,Y,yaooc_object);

/*  End YAOOC PreProcessor generated content */
