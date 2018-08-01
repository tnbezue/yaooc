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

#include <yaooc/pointer_bag.h>

/*  Begin YAOOC PreProcessor generated content */

/* Private members for yaooc_pointer_bag */

/* Protected members for yaooc_pointer_bag */

/* Typeinfo for yaooc_pointer_bag */
/*YAOOC_POD_ARRAY_IMPLEMENTATION(pointer,pointer_bag_array)*/
void yaooc_pointer_bag_default_ctor(pointer p)
{
#ifndef __YAOOC_USE_GC__
//  yaooc_pointer_bag_pointer this=p;
  call_constructor(p,yaooc_pod_array_ctor_ti,pointer_ti);
#endif
}

void yaooc_pointer_bag_dtor(pointer p)
{
#ifndef __YAOOC_USE_GC__
//  yaooc_pointer_bag_pointer this=p;
  yaooc_pointer_bag_delete_all(p);
#endif
}

/* Additional constructors for yaooc_pointer_bag */

/* Class table members for yaooc_pointer_bag */
const char* yaooc_pointer_bag_isa(const_pointer p)
{
  return "yaooc_pointer_bag_t";
}
/*
void yaooc_pointer_bag_swap(pointer p,pointer p2)
{
  yaooc_pointer_bag_pointer this=p;
  yaooc_pointer_bag_pointer other=p2;
  SWAP(pointer_bag_array_t*,this->pointers_,other->pointers_);
}
*/
pointer yaooc_pointer_bag_push(pointer p,pointer v)
{
#ifndef __YAOOC_USE_GC__
//  yaooc_pointer_bag_pointer this=p;
  if(v != NULL) {
    yaooc_pod_array_insert(p,END(p),&v);
  }
	return v;
#endif
}

void yaooc_pointer_bag_push_list(pointer p,...)
{
#ifndef __YAOOC_USE_GC__
  yaooc_pointer_bag_pointer this=p;
	// Last one must be NULL
	void* ptr;
	va_list args;
	va_start (args,p);
	while(1) {
		ptr = va_arg(args,pointer);
		if(ptr == NULL)
			break;
		yaooc_pointer_bag_push(this,ptr);
	}
	va_end(args);
#endif
}

void yaooc_pointer_bag_remove(pointer p,pointer v)
{
#ifndef __YAOOC_USE_GC__
  yaooc_pointer_bag_pointer this=p;
  pointer_bag_iterator i=yaooc_pod_array_find(this,&v);
  if(i!=M(this,end)) {
    yaooc_pod_array_erase(p,i);
  }
#endif
}

void yaooc_pointer_bag_clear(pointer p)
{
#ifndef __YAOOC_USE_GC__
  yaooc_pod_array_clear(p);
#endif
}

void yaooc_pointer_bag_delete_all(pointer p)
{
#ifndef __YAOOC_USE_GC__
  yaooc_pointer_bag_pointer this=p;
  pointer_bag_iterator i;
  FOR_EACH(i,this) {
    delete(*i);
  }
  yaooc_pod_array_clear(p);
#endif
}


/* Instance members for yaooc_pointer_bag */

/* Class table for yaooc_pointer_bag */
yaooc_pointer_bag_class_table_t yaooc_pointer_bag_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_pod_array_class_table,
  .isa = (const char* (*) (const_pointer p)) yaooc_pointer_bag_isa,
  .is_descendant = (bool (*) (const_pointer p,const char*)) yaooc_pointer_bag_is_descendant,
  .swap = (void (*) (pointer p,pointer)) yaooc_pod_array_swap,
  .increase_capacity = (bool (*) (pointer,size_t)) yaooc_pod_array_increase_capacity,
  .size_needed = (size_t (*)(const_pointer,size_t)) yaooc_pod_array_size_needed,
  .size = (size_t (*) (const_pointer)) yaooc_pod_array_size,
  .capacity = (size_t (*) (const_pointer)) yaooc_pod_array_capacity,
  .empty = (bool (*) (const_pointer)) yaooc_pod_array_empty,
  .begin = (iterator (*) (const_pointer)) yaooc_pod_array_begin,
  .end = (iterator (*) (const_pointer)) yaooc_pod_array_end,
  .push = (pointer (*) (pointer p,pointer)) yaooc_pointer_bag_push,
  .push_list = (void (*) (pointer p,...)) yaooc_pointer_bag_push_list,
  .remove = (void (*) (pointer p,pointer)) yaooc_pointer_bag_remove,
  .clear = (void (*) (pointer p)) yaooc_pointer_bag_clear,
  .delete_all = (void (*) (pointer p)) yaooc_pointer_bag_delete_all,
};

DEFINE_TYPE_INFO(yaooc_pointer_bag,Y,Y,N,N,N,N,N,Y,yaooc_pod_array)
