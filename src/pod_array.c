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

#include <yaooc/pod_array.h>
#include <yaooc/algorithm.h>
#include <yaooc/string.h>
#include <yaooc/stream.h>
#include <string.h>

#define YAOOC_POD_ARRAY_INITIAL_CAPACITY 16

#define yaooc_pod_array_private_default_ctor(p) ((yaooc_pod_array_pointer)p)->array_=NULL, \
  ((yaooc_pod_array_pointer)p)->type_info_ = NULL, \
  ((yaooc_pod_array_pointer)p)->size_ = 0, \
  ((yaooc_pod_array_pointer)p)->capacity_ = 0

/*  Begin YAOOC PreProcessor generated content */

/* Private items for yaooc_pod_array */

/* Protected items for yaooc_pod_array */

bool yaooc_pod_array_increase_capacity(pointer p,size_t n)
{
  yaooc_pod_array_pointer this=p;
  size_t capacity_needed = this->size_+n;
  bool ret=false;
  if(capacity_needed > this->capacity_ || this->array_==NULL) {
    this->capacity_=YAOOC_POD_ARRAY_INITIAL_CAPACITY;
    while(capacity_needed > this->capacity_) this->capacity_ <<= 1;
    this->array_=REALLOC(this->array_,M(this,size_needed,this->capacity_)); //*TYPE_SIZE(this)+this->class_table_->extra_capacity_);
    ret=true;
  }
  return ret;
}

size_t yaooc_pod_array_size_needed(const_pointer p,size_t n)
{
  return n*TYPE_SIZE(p);
}

/* Insert space for n elements */
iterator yaooc_pod_array_insert_space(pointer p,const_iterator pos,size_t n)
{
  yaooc_pod_array_pointer this=p;
  debug(DEBUG_POD_ARRAY) {
    debug_printf("this: %p pos: %" PRIsYAOOC " n: %" PRIsYAOOC "  this_array: %p  this_size: %" PRIsYAOOC " this_cap: %" PRIsYAOOC "\n",
          p,index,n,BEGIN(p),SIZE(p),CAPACITY(p));
  }
  size_t index=INDEX(this,pos);  /* Save index because increase capacity may move array */
  M(this,increase_capacity,n);
  yaooc_private_iterator ret = AT(p,index);
  memmove(ret+n*TYPE_SIZE(p),ret,(this->size_-index)*TYPE_SIZE(p));
  this->size_+=n;
  return ret;
}

/*
  Remove n elements from array. Starting at position specified
*/
iterator yaooc_pod_array_erase_space(pointer p,const_iterator pos,size_t n)
{
  yaooc_pod_array_pointer this=p;
  yaooc_private_iterator ret=(yaooc_private_iterator)pos;
  size_t index=INDEX(p,pos);
//  printf("Erase Space: %p %p %" PRIsYAOOC "\n",ret,ret+n*TYPE_SIZE(p),(SIZE(p)-index-n)*TYPE_SIZE(p));
  memmove(ret,ret+n*TYPE_SIZE(p),(SIZE(p)-index-n)*TYPE_SIZE(p));
  this->size_-=n;
  return ret;
}

/*
  Replace space of n elements with space for count elements.
*/
iterator yaooc_pod_array_replace_space(pointer p,const_iterator first,const_iterator last,size_t count)
{
  yaooc_pod_array_pointer this=p;
  size_t index=INDEX(p,first);
  size_t n = DISTANCE(TYPE_INFO(p),first,last);
//  yaooc_private_iterator ret=(yaooc_private_iterator)pos;
  if(n < count ) {
    yaooc_pod_array_insert_space(this,AT(p,index+n),count-n);
  } else if(n > count) {
    yaooc_pod_array_erase_space(this,AT(p,index+count),n-count);
  }
  return AT(this,index);
}

iterator yaooc_pod_array_find(pointer p,const_pointer value)
{
  yaooc_private_iterator ipos=BEGIN(p);
  for(;ipos!=END(p);ipos+=TYPE_SIZE(p))
    if(memcmp(ipos,value,TYPE_SIZE(p))==0)
      break;
  return ipos;
}

iterator yaooc_pod_array_insert(pointer p,const_iterator pos,const_pointer value)
{
  return yaooc_pod_array_insertn(p,pos,1,value);
}

iterator yaooc_pod_array_insertn(pointer p,const_iterator pos,size_t n,const_pointer value)
{
  iterator new_pos=yaooc_pod_array_insert_space(p,pos,n);
  yaooc_private_iterator ipos;
  size_t i;
  for(i=0,ipos=new_pos;i<n;i++,ipos+=TYPE_SIZE(p))
    memcpy(ipos,value,TYPE_SIZE(p));
  return new_pos;
}

iterator yaooc_pod_array_insert_range(pointer p,const_iterator pos,const_iterator f,const_iterator l)
{
  iterator ret=yaooc_pod_array_insert_space(p,pos,DISTANCE(TYPE_INFO(p),f,l));
  memcpy(ret,f,((yaooc_private_const_iterator)l)-((yaooc_private_const_iterator)f));
  return ret;
}

iterator yaooc_pod_array_erase(pointer p,const_iterator pos)
{
  return yaooc_pod_array_erase_space(p,pos,1);
}

iterator yaooc_pod_array_erase_range(pointer p,const_iterator f,const_iterator l)
{
  return yaooc_pod_array_erase_space(p,f,DISTANCE(TYPE_INFO(p),f,l));
}

size_t yaooc_pod_array_erase_value(pointer p,const_pointer value)
{
  size_t ret=0;
  yaooc_private_iterator ipos=END(p)-TYPE_SIZE(p);
  for(;ipos>=BEGIN(p);ipos-=TYPE_SIZE(p))
    if(memcmp(ipos,value,TYPE_SIZE(p))) {
      ret++;
      yaooc_pod_array_erase_space(p,ipos,1);
    }
  return ret;
}

iterator yaooc_pod_array_at(const_pointer p,size_t i)
{
  return AT(p,i);
}

void yaooc_pod_array_shrink_to_fit(pointer p)
{
  yaooc_pod_array_pointer this=p;
  // Don't shrink to less than INITIAL_CAPACITY
  if(this->capacity_ > YAOOC_POD_ARRAY_INITIAL_CAPACITY && this->size_ < this->capacity_) {
    this->capacity_=this->size_ < YAOOC_POD_ARRAY_INITIAL_CAPACITY ? YAOOC_POD_ARRAY_INITIAL_CAPACITY : this->size_;
//    this->array_=REALLOC(this->array_,CAPACITY(this)*TYPE_SIZE(this));
    this->array_=REALLOC(this->array_,M(this,size_needed,this->capacity_)); //*TYPE_SIZE(this)+this->class_table_->extra_capacity_);
  }
}

void yaooc_pod_array_reserve(pointer p,size_t n)
{
  yaooc_pod_array_pointer this=p;
  if(n > this->capacity_)
    M(this,increase_capacity,n-this->capacity_);
}

void yaooc_pod_array_clear(pointer p)
{
  ((yaooc_pod_array_pointer)p)->size_=0;
}

/* Typeinfo for yaooc_pod_array */

void yaooc_pod_array_default_ctor(pointer p) { abort(); } /* Need to know type size */

void yaooc_pod_array_dtor(pointer p)
{
  yaooc_pod_array_pointer this=p;
  if(this->array_)
    free(this->array_);
}

void yaooc_pod_array_copy_ctor(pointer p,const_pointer s)
{
  yaooc_pod_array_private_default_ctor(p);
  ((yaooc_pod_array_pointer)p)->type_info_ = ((yaooc_pod_array_const_pointer)s)->type_info_;
  yaooc_pod_array_assign(p,s);
}

void yaooc_pod_array_assign(pointer d,const_pointer s)
{
//  assert(((yaooc_pod_array_const_pointer)p)->type_info_ == ((yaooc_pod_array_const_pointer)s)->type_info_);
  yaooc_pod_array_pointer this=d;
  yaooc_pod_array_const_pointer src=s;
  yaooc_pod_array_reserve(this,SIZE(s));
  this->size_=src->size_;
  memcpy(this->array_,src->array_,SIZE(this)*TYPE_SIZE(this));
}

/* Constructors for yaooc_pod_array */
void yaooc_pod_array_ctor_ti(pointer p,va_list args)
{
  yaooc_pod_array_pointer this=p;
  yaooc_pod_array_private_default_ctor(p);
  this->type_info_=va_arg(args,const type_info_t*);
}

/* Class table methods for yaooc_pod_array */
const char* yaooc_pod_array_isa(const_pointer p) { return "yaooc_pod_array_t"; }

void yaooc_pod_array_swap(pointer p,pointer p2)
{
  yaooc_pod_array_pointer this=p;
  yaooc_pod_array_pointer other=p2;
  SWAP(char*,this->array_,other->array_);
  SWAP(size_t,this->size_,other->size_);
  SWAP(size_t,this->capacity_,other->capacity_);
//  SWAP(size_t,this->,other->);
}

/*
char* yaooc_pod_array_to_s(const_pointer p)
{
  yaooc_pod_array_const_pointer this=p;
  yaooc_string_pointer temp=new(yaooc_string);
  M(temp,append,"[");
  char* ptr;
  if(SIZE(this) > 0) {
    yaooc_private_const_iterator i=BEGIN(this);
    ptr=M((yaooc_object_const_pointer)i,to_s);
    M(temp,append,ptr);
    i+=SIZE(this);
    delete(ptr);
    for(;i != END(this);i+=SIZE(this)) {
      M(temp,append," ,");
      ptr=M((yaooc_object_const_pointer)i,to_s);
      M(temp,append,ptr);
      delete(ptr);
    }
  }
  M(temp,append," ]");
  ptr=yaooc_strdup(M(temp,c_str));
  delete(temp);
  return ptr;
}
*/
size_t yaooc_pod_array_size(const_pointer p)
{
  return SIZE(p);
}

size_t yaooc_pod_array_capacity(const_pointer p)
{
  return CAPACITY(p);
}

bool yaooc_pod_array_empty(const_pointer p)
{
  return SIZE(p)==0;
}

iterator yaooc_pod_array_begin(const_pointer p)
{
  return BEGIN(p);
}

iterator yaooc_pod_array_end(const_pointer p)
{
  return END(p);
}

void yaooc_pod_array_to_stream(const_pointer p,pointer s)
{
	to_stream to_s = get_to_stream(TYPE_INFO(p));
	if(to_s) {
//		yaooc_pod_array_const_pointer this=p;
		yaooc_ostream_pointer strm=s;
		M(strm,printf,"[");
		if(SIZE(p) > 0) {
			yaooc_private_iterator ptr=BEGIN(p);
			to_s(ptr,strm);
			ptr+=TYPE_SIZE(p);
			while(ptr != END(p)) {
				to_s(ptr,strm);
				M(strm,printf,",");
				ptr+=TYPE_SIZE(p);
			}
		}
		M(strm,printf,"]");
	}
}

/* Class table for yaooc_pod_array */
yaooc_pod_array_class_table_t yaooc_pod_array_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
  .isa = (const char* (*) (const_pointer)) yaooc_pod_array_isa,
  .is_descendant = (bool (*) (const_pointer,const char*)) yaooc_pod_array_is_descendant,
  .swap = (void (*) (pointer,pointer)) yaooc_pod_array_swap,
  .increase_capacity = (bool (*) (pointer,size_t)) yaooc_pod_array_increase_capacity,
  .size_needed = (size_t (*)(const_pointer,size_t)) yaooc_pod_array_size_needed,
  .size = (size_t (*) (const_pointer)) yaooc_pod_array_size,
  .capacity = (size_t (*) (const_pointer)) yaooc_pod_array_capacity,
  .empty = (bool (*) (const_pointer)) yaooc_pod_array_empty,
  .begin = (iterator (*) (const_pointer)) yaooc_pod_array_begin,
  .end = (iterator (*) (const_pointer)) yaooc_pod_array_end,
};

DEFINE_TYPE_INFO(yaooc_pod_array,Y,Y,Y,Y,N,Y,N,Y,yaooc_object)
/*  End YAOOC PreProcessor generated content */
