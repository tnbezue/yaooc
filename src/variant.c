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
/* Begin YAOOCPP output */

#include <yaooc/variant.h>
#include <string.h>

/* Private variables implementation for yaooc_variant */

/* Private methods prototypes for yaooc_variant */

/* Type Info implemmentation for yaooc_variant */
void yaooc_variant_default_ctor(pointer p)
{
  yaooc_variant_pointer this=p;
  this->type_=VAR_NONE;
	this->dbl_=0;
}

void yaooc_variant_dtor(pointer p)
{
  yaooc_variant_pointer this=p;
	switch(this->type_) {
  	case VAR_NONE:
  	case VAR_CHAR:
  	case VAR_UCHAR:
  	case VAR_SHORT:
  	case VAR_USHORT:
  	case VAR_INT:
  	case VAR_UINT:
  	case VAR_LONG:
  	case VAR_ULONG:
  	case VAR_DOUBLE:
			break;

  	case VAR_CHAR_PTR:
		case VAR_VOID_PTR:
			free(this->chr_ptr_);
  		break;

  	case VAR_OBJECT:
  		delete(this->obj_);
  		break;
  }
	yaooc_variant_default_ctor(this);
}

void yaooc_variant_copy_ctor(pointer p,const_pointer s)
{
  yaooc_variant_default_ctor(p);
  yaooc_variant_assign(p,s);
}

void yaooc_variant_assign(pointer p,const_pointer s)
{
  yaooc_variant_pointer this=p;
  yaooc_variant_const_pointer src=s;
	yaooc_variant_set(this,src->type_,yaooc_variant_value(src));
}

/* Constructors implementation for yaooc_variant */

/* Private methods implementation for yaooc_variant */

/* Protected implementation for yaooc_variant */

/* Table implementation for yaooc_variant */
yaooc_variant_type_t yaooc_variant_type(const_pointer p)
{
  yaooc_variant_const_pointer this=p;
  return this->type_;
}

void yaooc_variant_set(pointer p,yaooc_variant_type_t t,const void* value)
{
  yaooc_variant_pointer this=p;
	yaooc_variant_dtor(this);
	switch(t) {
		case VAR_NONE:
			break;

		case VAR_CHAR:
		case VAR_UCHAR:
			this->ch_=*(const char*)value;
			break;

		case VAR_SHORT:
		case VAR_USHORT:
			this->sh_=*(const short*)value;
			break;

		case VAR_INT:
		case VAR_UINT:
			this->int_=*(const int*)value;
			break;

		case VAR_LONG:
		case VAR_ULONG:
			this->long_=*(const long long*)value;
			break;

		case VAR_DOUBLE:
			this->dbl_=*(const double*)value;
			break;

		case VAR_CHAR_PTR:
			this->chr_ptr_=strdup(value);
			break;

		case VAR_VOID_PTR:
			this->void_ptr_=(void*)value;
			break;

		case VAR_OBJECT:
			this->obj_=new_copy(value);
			break;
	}
	this->type_=t;
}

const void* yaooc_variant_value(const_pointer p)
{
  yaooc_variant_const_pointer this=p;
	const void* ret=NULL;
	switch(this->type_) {
  	case VAR_NONE:
  		break;

  	case VAR_CHAR:
  	case VAR_UCHAR:
  		ret = &this->ch_;
  		break;

  	case VAR_SHORT:
  	case VAR_USHORT:
  		ret = &this->sh_;
  		break;

  	case VAR_INT:
  	case VAR_UINT:
  		ret = &this->int_;
  		break;

  	case VAR_LONG:
  	case VAR_ULONG:
  		ret = &this->long_;
  		break;

  	case VAR_DOUBLE:
  		ret = &this->dbl_;
  		break;

  	case VAR_CHAR_PTR:
  		ret = this->chr_ptr_;
  		break;

  	case VAR_VOID_PTR:
  		ret = this->void_ptr_;
  		break;

  	case VAR_OBJECT:
  		ret = this->obj_;
  		break;
  }
	return ret;
}


/* Class table definition for yaooc_variant */
yaooc_variant_class_table_t yaooc_variant_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
  .type_name_ = (const char*) "yaooc_variant_t",
  .swap = (void(*)(pointer, pointer)) yaooc_variant_swap,
  .type = (yaooc_variant_type_t(*)(const_pointer)) yaooc_variant_type,
  .set = (void(*)(pointer, yaooc_variant_type_t,const void*)) yaooc_variant_set,
  .value = (const void*(*)(const_pointer)) yaooc_variant_value,
};

/* Type info structure for yaooc_variant */
DEFINE_TYPE_INFO(yaooc_variant,Y,Y,Y,Y,N,N,N,Y,yaooc_object);

/* End YAOOCPP output */

