#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <yaooc/container.h>
#include <yaooc/algorithm.h>
#include <yaooc/container.h>

static container_private_class_methods_t container_private_class_methods=
{
  yaooc_container_size_needed,
  yaooc_container_increase_capacity
};

/*
  Overridden object methods
*/
ISA_IMPLEMENTATION(yaooc_container,yaooc_object)
void yaooc_container_swap(pointer p1,pointer p2)
{
  yaooc_container_pointer this1=p1;
  yaooc_container_pointer this2=p2;
  assert(this1->type_info_==this2->type_info_ &&
      strcmp(M(this1,isa),M(this2,isa)) == 0 &&
      "Attempt to swap containers of different types");
  SWAP(char*,this1->array_,this2->array_)
  SWAP(const type_info_t*,this1->type_info_,this2->type_info_)
  SWAP(size_t,this1->capacity_,this2->capacity_)
  SWAP(size_t,this1->size_,this2->size_)
}

#define INITIAL_CAPACITY 16

void yaooc_container_clear(pointer p)
{
	yaooc_container_pointer this=p;
  /*
    If using garbage collector.  Still run delete on items in container in case
    resources other than memory needs to be released.
  */
	real_deletep_array(this->array_,this->type_info_,this->size_);
	this->size_=0;
}

/*
  Returns the number of bytes required to contain n elements.  Default is type_size * N
  Derived classes can override this method.  For example, string classes needs 1 extra
  byte.
*/
size_t yaooc_container_size_needed(const_pointer p,size_t n)
{
	yaooc_container_const_pointer this=p;
  return n*this->type_info_->type_size_;
}

bool yaooc_container_increase_capacity(pointer p,size_t n)
{
	yaooc_container_pointer this=p;
	bool rc=false;
	size_t new_capacity=this->size_+n;
	if(new_capacity > this->capacity_) {
		if(this->capacity_==0) this->capacity_=INITIAL_CAPACITY;
		while(new_capacity > this->capacity_) this->capacity_<<=1;
		this->array_=(char*)REALLOC(this->array_,CPM(this,size_needed,this->capacity_));
		debug(DEBUG_CONTAINER) {
			printf("increase_capacity: %zu %zu %zu\n",this->capacity_,this->size_,this->type_info_->type_size_);
		}
		assert(this->array_);
		rc=true;
	}
	return rc;
}

void yaooc_container_reserve(pointer p,size_t n)
{
	yaooc_container_pointer this=p;
	if(n > this->capacity_)
    CPM(this,increase_capacity,n-this->size_);
}

void yaooc_container_resize(pointer p,size_t new_size,const_pointer value)
{
	yaooc_container_pointer this=p;
	if(new_size > this->size_) {
		yaooc_container_insert_n(this,yaooc_container_end(this),new_size-this->size_,value);
	} else {
		yaooc_container_erase_range(this,AT(this,new_size),yaooc_container_end(p));
	}
}

/* *****
	The default constructor should never be used because type info would be undefined -- which is not useful.
***** */
void yaooc_container_default_ctor(pointer p)
{
	assert(0 && "Default constructor for any container is not useful");
}

void yaooc_container_ctor(pointer p,va_list args)
{
  yaooc_container_pointer this=p;
  this->private_class_table_=&container_private_class_methods;
	this->array_=NULL;
	this->type_info_=va_arg(args,const type_info_t*);
	this->capacity_=0;
	this->size_=0;
}

void yaooc_container_dtor(pointer p)
{
	yaooc_container_pointer this=p;
	if(this->array_) {
    M(this,clear);
#ifndef __YAOOC_USE_GC__
		FREE(this->array_);
#endif
		this->array_=NULL;
	}
}

void yaooc_container_assign(pointer d,const_pointer s)
{
	yaooc_container_pointer dst=d;
	yaooc_container_const_pointer src=s;
  if(dst->capacity_ < src->size_) {
    CPM(dst,increase_capacity,src->size_-dst->capacity_);
    real_newp_array(BEGIN(dst),dst->type_info_,src->size_-dst->size_);
  }
  dst->size_=src->size_;
  yaooc_copy(dst->type_info_,CBEGIN(src),CEND(src),BEGIN(dst));
  dst->private_class_table_=src->private_class_table_;
}

void yaooc_container_copy_ctor(pointer d,const_pointer s)
{
	yaooc_container_const_pointer src=s;
  call_constructor(d,yaooc_container_ctor,src->type_info_);
  yaooc_container_assign(d,s);
}

bool yaooc_container_lt_compare(const_pointer v1,const_pointer v2)
{
	return false;
}

yaooc_container_class_members_t yaooc_container_class_members = { YAOOC_CONTAINER_CLASS_MEMBERS };

DEFINE_TYPE_INFO(yaooc_container,yaooc_container_default_ctor,yaooc_container_dtor
      ,yaooc_container_copy_ctor,yaooc_container_assign,NULL,&yaooc_container_class_members,yaooc_object)

iterator yaooc_container_find(const_pointer p,const_pointer value)
{
	yaooc_container_const_pointer this=p;
	return yaooc_find(this->type_info_,CBEGIN(p),CEND(p),value);
}

/*
const_iterator yaooc_container_cfind(const_pointer p,const_pointer value)
{
	yaooc_container_const_pointer this=p;
	return yaooc_find(this->type_info_,CBEGIN(p),CEND(p),value);
//	return yaooc_container_find(p,value);
}
*/
/*
	All checks have been performed, space has been allocated, just do the insert
*/
void yaooc_container_insert_range_private(pointer p,size_t index,const_iterator f,const_iterator l)
{
	yaooc_container_pointer this=p;
	yaooc_private_const_iterator first=f;
	yaooc_private_const_iterator last=l;
	size_t n=(last-first)/this->type_info_->type_size_;
//	memmove(AT(this,index+n),ptr,BYTES_TO_END(this,index));
	yaooc_private_iterator ptr=AT(this,index);
	CONTAINER_INSERT_SPACE(this,index,n);
	for(;first!=last;first+=this->type_info_->type_size_,ptr+=this->type_info_->type_size_)
		real_newp_array_copy_static(ptr,this->type_info_,first,1);
	this->size_+=n;
}

void yaooc_container_insert_n_private(pointer p,size_t index,size_t n,const_pointer value)
{
	yaooc_container_pointer this=p;
	CONTAINER_INSERT_SPACE(this,index,n);
	real_newp_array_copy_static(AT(this,index),this->type_info_,value,n);
	this->size_+=n;
}


iterator yaooc_container_insert_n(pointer p,const_iterator pos,size_t n,const_pointer value)
{
	yaooc_container_pointer this=p;
	yaooc_private_const_iterator cbegin=CBEGIN(p);
	assert(cbegin <= (yaooc_private_const_iterator)(pos) && (yaooc_private_const_iterator)(pos) <= (yaooc_private_const_iterator)CEND(p) && "Insert position out of range");
	/*
		 Save offset because increase capacity may relocate array -- thus begin would change
	*/
	size_t ofs=((yaooc_private_const_iterator)pos-cbegin)/this->type_info_->type_size_;
  CPM(this,increase_capacity,n);
	yaooc_container_insert_n_private(this,ofs,n,value);
	return AT(this,ofs);
}

iterator yaooc_container_insert(pointer p,const_iterator pos,const_pointer value)
{
	return yaooc_container_insert_n(p,pos,1,value);
}

iterator yaooc_container_insert_range(pointer p,const_iterator pos,const_iterator f,const_iterator l)
{
	WITHIN_BOUNDS(p,pos,"first > last in yaooc_container_insert_range");
	PROPER_RANGE(f,l,"First > last in yaooc_container_insert_range");
	yaooc_container_pointer this=p;
	yaooc_private_const_iterator ptr=pos;
	yaooc_private_const_iterator first=f;
	yaooc_private_const_iterator last=l;
	size_t ofs=ptr-(yaooc_private_const_iterator)yaooc_container_begin(this);
	size_t element_size=this->type_info_->type_size_;
	size_t n=(last-first)/element_size;
  CPM(this,increase_capacity,n);
	ptr=(yaooc_private_const_iterator)yaooc_container_begin(this)+ofs;
	size_t diff=last-first;
	memmove((iterator)(ptr+diff),ptr,(yaooc_private_const_iterator)yaooc_container_end(p)-ptr);
	iterator rpos=(yaooc_private_iterator)ptr;
	size_t i;
	for(i=0;i<n;i++) {
		real_newp_array_copy_static((iterator)ptr,this->type_info_,first,1);
		ptr+=element_size;
		first+=element_size;
	}
	this->size_+=n;
	return rpos;
}

void yaooc_container_erase_range_private(pointer p,iterator f,iterator l)
{
	yaooc_private_iterator first=f;
	yaooc_private_iterator last=l;
	yaooc_container_pointer this=p;
	yaooc_private_iterator end=yaooc_container_end(p);
	size_t n=(last - first)/this->type_info_->type_size_;
	real_deletep_array(first,this->type_info_,n);
	memmove(first,last,end-(yaooc_private_iterator)last);
	this->size_-=n;
}

iterator yaooc_container_erase_range(pointer p,iterator f,iterator l)
{
	PROPER_RANGE(f,l,"First > last in yaooc_container_erase_range");
	FIRST_LAST_WITHIN_BOUNDS(p,f,l,"Invalid range in yaooc_container_erase_range");
	yaooc_container_erase_range_private(p,f,l);
	return f;
}

iterator yaooc_container_erase(pointer p,iterator pos)
{
	WITHIN_BOUNDS(p,pos,"Position out of bounds in yaooc_container_erase");
	yaooc_container_pointer this=p;
	yaooc_container_erase_range_private(p,pos,(char*)pos+this->type_info_->type_size_);
	return pos;
}

void yaooc_container_shrink_to_fit(pointer p)
{
	yaooc_container_pointer this=p;
	if(this->array_) {
		size_t new_cap=16;
		while(new_cap < this->size_) new_cap <<=1;
		if(new_cap != this->capacity_) {
			this->array_=REALLOC(this->array_,(this->capacity_=new_cap)*this->type_info_->type_size_);
		}
	}
}

size_t yaooc_container_erase_value(pointer p,const_pointer value)
{
	yaooc_container_pointer this=p;
	size_t i=0,n_erased=0;
	while(i<this->size_) {
		if(op_eq_static(AT(this,i),value,this->type_info_)) {
			/*
				If there are consecutive equal values, delete the range
			*/
			size_t j,n=1;
			for(j=i+1;j<this->size_;j++) {
				if(op_ne_static(AT(this,j),value,this->type_info_))
					break;
				n++;
			}
			yaooc_container_erase_range_private(this,AT(this,i),AT(this,i+n));
			n_erased+=n;
		} else
      i++;
	}
	return n_erased;
}

iterator yaooc_container_at(pointer p,size_t pos)
{
	yaooc_container_pointer this=p;
	return this->array_ ? AT(this,pos) : NULL;
}
/*
const_iterator yaooc_container_cat(const_pointer p,size_t pos)
{
	const yaooc_container_const_pointer this=p;
	return this->array_ ? AT(this,pos) : NULL;
}
*/
size_t yaooc_container_size(const_pointer this)
{
	return ((yaooc_container_pointer)this)->size_;
}

size_t yaooc_container_capacity(const_pointer this)
{
	return ((yaooc_container_pointer)this)->capacity_;
}

bool yaooc_container_empty(const_pointer this)
{
	return ((yaooc_container_pointer)this)->size_ == 0;
}

iterator yaooc_container_begin(pointer p)
{
	return yaooc_container_at(p,0);
}

iterator yaooc_container_end(pointer p)
{
	yaooc_container_pointer this=p;
	return yaooc_container_at(p,this->size_);
}
/*
const_iterator yaooc_container_cbegin(const_pointer p)
{
	return yaooc_container_cat(p,0);
}

const_iterator yaooc_container_cend(const_pointer p)
{
	yaooc_container_const_pointer this=p;
	return yaooc_container_cat(this,this->size_);
}
*/
const type_info_t* yaooc_container_get_type_info(const_pointer p)
{
	return ((yaooc_container_const_pointer)p)->type_info_;
}
