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

#include <yaooc/memory.h>
#include <stdlib.h>

void dynamic_pointer_default_ctor(pointer p)
{
  (*(void**)p) = NULL;
}
void dynamic_pointer_dtor(pointer p)
{
  if((*(void**)p)) {
    delete ((*(void**)p));
    (*(void**)p)=NULL;
  }
}

void dynamic_pointer_copy_ctor(pointer d,const_pointer s)
{
  if((*(void**)s))
    (*(void**)d)=new_copy((*(void**)s));
  else
    (*(void**)d)=NULL;
}

void dynamic_pointer_assign(pointer d,const_pointer s)
{
  dynamic_pointer_dtor(d);
  dynamic_pointer_copy_ctor(d,s);
}

bool dynamic_pointer_less_than_compare(const_pointer p1,const_pointer p2)
{
  return op_lt(*(pointer_t**)p1,*(pointer_t**)p2);
}


/* Private members for yaooc_unique_ptr */

/* Protected members for yaooc_unique_ptr */

/* Typeinfo for yaooc_unique_ptr */
void yaooc_unique_ptr_default_ctor(pointer p)
{
  yaooc_unique_ptr_pointer this=p;
  this->ptr_=NULL;
}

void yaooc_unique_ptr_dtor(pointer p)
{
  yaooc_unique_ptr_pointer this=p;
  if(this->ptr_)
    delete(this->ptr_);
  this->ptr_=NULL;
}

void yaooc_unique_ptr_copy_ctor(pointer d,const_pointer s)
{
  yaooc_unique_ptr_default_ctor(d);
  yaooc_unique_ptr_assign(d,s);
}

void yaooc_unique_ptr_assign(pointer d,const_pointer s)
{
  yaooc_unique_ptr_pointer this=d;
  yaooc_unique_ptr_pointer src=(yaooc_unique_ptr_pointer)s;
  if(this->ptr_ != src->ptr_) {
    yaooc_unique_ptr_dtor(this);
    this->ptr_=src->ptr_;
    src->ptr_=NULL;
  }
}

static bool yaooc_memory_pointer_compare(const_pointer p1,const_pointer p2)
{

  if(p1==p2)
    return false;
  if(p1 != NULL) {
    if(p2 != NULL) {
      return op_lt(p1,p2);
    } else {
      return false;
    }
  }
  return true;
}

bool yaooc_unique_ptr_less_than_compare(const_pointer p1,const_pointer p2)
{
  return yaooc_memory_pointer_compare(((yaooc_unique_ptr_const_pointer)p1)->ptr_,((yaooc_unique_ptr_const_pointer)p2)->ptr_);
}

/* Additional constructors for yaooc_unique_ptr */

void yaooc_unique_ptr_ctor_ptr(pointer p,va_list args)
{
  yaooc_unique_ptr_default_ctor(p);
  yaooc_unique_ptr_reset(p,va_arg(args,pointer));
}

/* Class table members for yaooc_unique_ptr */
void yaooc_unique_ptr_swap(pointer p,pointer ptr)
{
  yaooc_unique_ptr_pointer this=p;
  yaooc_unique_ptr_pointer other=ptr;
  SWAP(pointer,this->ptr_,other->ptr_);
}


pointer yaooc_unique_ptr_get(const_pointer p)
{
  yaooc_unique_ptr_const_pointer this=p;
  return this->ptr_;
}

pointer yaooc_unique_ptr_release(pointer p)
{
  yaooc_unique_ptr_pointer this=p;
  pointer ret = this->ptr_;
  this->ptr_=NULL;
  return ret;
}

void yaooc_unique_ptr_reset(pointer p,pointer ptr)
{
  yaooc_unique_ptr_dtor(p);
  ((yaooc_unique_ptr_pointer)p)->ptr_=ptr;
}


/* Instance members for yaooc_unique_ptr */

yaooc_unique_ptr_class_table_t yaooc_unique_ptr_class_table = {
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
  .type_name_ = (const char*) "yaooc_unique_ptr_t",
  .swap = (void (*) (pointer p,pointer)) yaooc_unique_ptr_swap,
  .get = (pointer (*) (const_pointer p)) yaooc_unique_ptr_get,
  .release = (pointer (*) (pointer p)) yaooc_unique_ptr_release,
  .reset = (void (*) (pointer p,pointer)) yaooc_unique_ptr_reset,
};

DEFINE_TYPE_INFO(yaooc_unique_ptr,Y,Y,Y,Y,Y,N,N,Y,yaooc_object)
/* Private members for yaooc_shared_ptr */

/* Protected members for yaooc_shared_ptr */

/* Typeinfo for yaooc_shared_ptr */
struct yaooc_counter_s {
	void* ptr_;
	size_t count_;
};

static void yaooc_counter_default_ctor(pointer p)
{
  yaooc_counter_t* this=p;
	this->ptr_=NULL;
	this->count_=1;
}

static void yaooc_counter_ctor_ptr(pointer p,va_list args)
{
  yaooc_counter_t* this=p;
	this->ptr_=va_arg(args,pointer);
	this->count_=1;
}

DEFINE_TYPE_INFO(yaooc_counter,Y,N,N,N,N,N,N,N,NULL)

void yaooc_shared_ptr_acquire(pointer p,yaooc_counter_t* c)
{
	((yaooc_shared_ptr_pointer)p)->counter_=c;
	if(c) ++c->count_;
}

void yaooc_shared_ptr_default_ctor(pointer p)
{
  yaooc_shared_ptr_pointer this=p;
  this->counter_=NULL;
}

void yaooc_shared_ptr_dtor(pointer p)
{
  yaooc_shared_ptr_release(p);
}

void yaooc_shared_ptr_copy_ctor(pointer d,const_pointer s)
{
  yaooc_shared_ptr_default_ctor(d);
  yaooc_shared_ptr_assign(d,s);
}

void yaooc_shared_ptr_assign(pointer d,const_pointer s)
{
	if(s != d) {
		yaooc_shared_ptr_release(d);
		yaooc_shared_ptr_acquire(d,((yaooc_shared_ptr_const_pointer)s)->counter_);
	}
}

bool yaooc_shared_ptr_less_than_compare(const_pointer p1,const_pointer p2)
{
  return yaooc_memory_pointer_compare(yaooc_shared_ptr_get(p1),yaooc_shared_ptr_get(p2));
}

/* Additional constructors for yaooc_shared_ptr */
void yaooc_shared_ptr_ctor_ptr(pointer p,va_list args)
{
  yaooc_shared_ptr_default_ctor(p);
  yaooc_shared_ptr_reset(p,va_arg(args,pointer));

}

/* Class table members for yaooc_shared_ptr */
void yaooc_shared_ptr_swap(pointer p,pointer ptr)
{
  yaooc_shared_ptr_pointer this=p;
  yaooc_shared_ptr_pointer other=ptr;
  SWAP(yaooc_counter_t*,this->counter_,other->counter_);
}

pointer yaooc_shared_ptr_get(const_pointer p)
{
  yaooc_shared_ptr_const_pointer this=p;
  return this->counter_ ? this->counter_->ptr_ : NULL;
}

/*
const_pointer yaooc_shared_ptr_cget(const_pointer p)
{
  yaooc_shared_ptr_const_pointer this=p;
   ret;

  return ret;
}
*/
pointer yaooc_shared_ptr_release(pointer p)
{
  yaooc_shared_ptr_pointer this=p;
  pointer ret = yaooc_shared_ptr_get(p);
	if(this->counter_) {
		if(--this->counter_->count_ == 0) {
      delete(this->counter_->ptr_);  /* counter would have been null if ptr was null */
			delete(this->counter_);
		}
		this->counter_=NULL;
	}

  return ret;
}

void yaooc_shared_ptr_reset(pointer p,pointer ptr)
{
  yaooc_shared_ptr_pointer this=p;
  yaooc_shared_ptr_release(this);
  if(ptr != NULL)
    this->counter_=new_ctor(yaooc_counter,yaooc_counter_ctor_ptr,ptr);
}
/*
bool yaooc_shared_ptr_unique(const_pointer p)
{
  yaooc_shared_ptr_const_pointer this=p;
  bool ret;

  return ret;
}
*/
size_t yaooc_shared_ptr_count(const_pointer p)
{
  yaooc_shared_ptr_const_pointer this=p;
  return this->counter_ ? this->counter_->count_  : 0;
}


/* Instance members for yaooc_shared_ptr */

yaooc_shared_ptr_class_table_t yaooc_shared_ptr_class_table = {
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
  .type_name_ = (const char*) "yaooc_shared_ptr_t",
  .swap = (void (*) (pointer p,pointer)) yaooc_shared_ptr_swap,
  .get = (pointer (*) (const_pointer p)) yaooc_shared_ptr_get,
  .release = (pointer (*) (pointer p)) yaooc_shared_ptr_release,
  .reset = (void (*) (pointer p,pointer)) yaooc_shared_ptr_reset,
  .count = (size_t (*) (const_pointer p)) yaooc_shared_ptr_count,
};

DEFINE_TYPE_INFO(yaooc_shared_ptr,Y,Y,Y,Y,Y,N,N,Y,yaooc_object)

