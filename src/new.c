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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <yaooc/new.h>

#ifdef __YAOOC_USE_GC__
/*
  Garbage collection finalizer.  When garbage collector is enabled, the finalizer calls the destructor for the allocated object
*/
static void __yaooc_gc_finalizer__(GC_PTR obj, GC_PTR x)
{
  memory_header_t* mh=(memory_header_t*)obj;
  __deletep_array(mh->ptr_,mh->type_info_,mh->n_elem_);
}
/*
  If garbase collection is enabled, before assigning the finalizer, check if finalizer will be needed.
  If a detructor will not be executed when object is destroyed, there is no need to assign the finalizer.
*/
bool has_destructor(const type_info_t* ti)
{
  while(ti) {
    if(ti->dtor_)
      return true;
    ti=ti->parent_;
  }
  return false;
}

#endif
/*
	Allocate memory and setup memory header
*/
memory_header_t* allocate_memory(const type_info_t* ti,size_t n_elements)
{
  assert(ti->type_size_ > 0 && "Cannot allocate element of size 0");
	memory_header_t* mh=MALLOC(n_elements*ti->type_size_+offsetof(memory_header_t,ptr_));
	assert(mh);

#ifdef __YAOOC_USE_GC__
  if(has_destructor(ti))
    GC_register_finalizer(mh, __yaooc_gc_finalizer__, 0, 0, 0);
#endif
	mh->type_info_=ti;
	mh->n_elem_=n_elements;
	return mh;
}

/* ********** new default ctor ********* */
/*
	Recurse until a default ctor found or root is reached
*/
default_constructor get_default_ctor(const type_info_t* ti)
{
  while(ti != NULL) {
    if(ti->default_ctor_ != NULL) {
      return ti->default_ctor_;
    }
    ti=ti->parent_;
  }
	return NULL;
}

pointer __newp_array(pointer ptr,const type_info_t* ti,size_t n_elements)
{
	size_t i;
	yaooc_private_iterator iptr;
	default_constructor default_ctor=get_default_ctor(ti);
	const class_table_t* ct=ti->class_table_;
	size_t element_size=ti->type_size_;
	if(ct) {
		iptr=ptr;
		for(i=0;i<n_elements;i++) {
			copy_class_table(iptr,ct);
			iptr+=element_size;
		}
	}
	if(default_ctor) {
		iptr=ptr;
		for(i=0;i<n_elements;i++) {
			default_ctor(iptr);
			iptr+=element_size;
		}
	}
	return ptr;
}

pointer __new_array(const type_info_t* ti,size_t n)
{
	memory_header_t* mh=allocate_memory(ti,n);
	return __newp_array(mh->ptr_,ti,n);
}

/* ************* new copy constructor *********
*/
/*
	Recurse until a copy ctor found or root is reached
*/
copy_constructor get_copy_ctor(const type_info_t* ti)
{
  while(ti != NULL) {
    if(ti->copy_ctor_ != NULL) {
      return ti->copy_ctor_;
    }
    ti=ti->parent_;
  }
	return NULL;
}

/*
  The one object at src is copy constructred to n objects starting at dst
*/
pointer __newp_array_copy_static(pointer dst,const type_info_t* ti,const_pointer src,size_t n_elements)
{
	yaooc_private_iterator idst;//=dst;
	size_t i;
	size_t element_size=ti->type_size_;
	copy_constructor copy_ctor=get_copy_ctor(ti);
//	bool has_class_table = ti->class_table_ != NULL;
  if(copy_ctor) {
    if(ti->class_table_ !=NULL)
      for(i=0,idst=dst;i<n_elements;i++,idst+=element_size)
        copy_class_table(idst,((base_object_t*)src)->class_table);
    for(i=0,idst=dst;i<n_elements;i++,idst+=element_size)
      copy_ctor(idst,src);
  } else {
    for(i=0,idst=dst;i<n_elements;i++,idst+=element_size)
      memcpy(idst,src,element_size); // class table pointer included in copy
	}
	return dst;
}

pointer __new_array_copy_static(const type_info_t* ti,const_pointer src,size_t n)
{
	memory_header_t* mh=allocate_memory(ti,n);
	return __newp_array_copy_static(mh->ptr_,ti,src,n);
}

pointer __new_array_copy(const_pointer src,size_t n)
{
	return __new_array_copy_static(get_type_info(src),src,n);
}

pointer __newp_array_copy(pointer dst,const_pointer src,size_t n)
{
	return __newp_array_copy_static(dst,get_type_info(src),src,n);
}

/*
  Each object starting at src is copy constructed to objects starting at dst
*/
pointer __newp_array_copy_range_static(pointer dst,const type_info_t* ti,const_pointer src,size_t n_elements)
{
	yaooc_private_iterator idst; //=dst;
  yaooc_private_const_iterator isrc;//=src;
	size_t i;
	size_t element_size=ti->type_size_;
//	bool has_class_table = ti->class_table_ != NULL;
	copy_constructor copy_ctor=get_copy_ctor(ti);
  if(copy_ctor) {
    if(ti->class_table_ != NULL) {
      for(i=0,idst=dst,isrc=src;i<n_elements;i++,idst+=element_size,isrc+=element_size)
        copy_class_table(idst,((base_object_t*)isrc)->class_table);
    }
    for(i=0,idst=dst,isrc=src;i<n_elements;i++,idst+=element_size,isrc+=element_size)
			copy_ctor(idst,isrc);
  } else {
    memcpy(dst,src,element_size*n_elements); // class table pointer included in copy
	}
	return dst;
}

pointer __new_array_copy_range_static(const type_info_t* ti,const_pointer src,size_t n)
{
	memory_header_t* mh=allocate_memory(ti,n);
	return __newp_array_copy_range_static(mh->ptr_,ti,src,n);
}

pointer __new_array_copy_range(const_pointer src,size_t n)
{
	return __new_array_copy_range_static(get_type_info(src),src,n);
}

pointer __newp_array_copy_range(pointer dst,const_pointer src,size_t n)
{
	return __newp_array_copy_range_static(dst,get_type_info(src),src,n);
}


/* ************ new Constructor ***************
	New using a constructor other than default or copy constructor
*/

static void new_ctor_private(yaooc_private_iterator ptr,const type_info_t* ti,size_t n_elements,constructor ctor,va_list args)
{
	size_t i;
	const class_table_t* ct=ti->class_table_;
	size_t element_size=ti->type_size_;
	va_list args2;
	for(i=0;i<n_elements;i++) {
		if(ct)
			copy_class_table(ptr,ct);
		va_copy(args2,args);
		ctor(ptr,args2);
		va_end(args2);
		ptr+=element_size;
	}
}

pointer __new_array_ctor(const type_info_t* ti,size_t n,constructor ctor,...)
{
	va_list args;
	va_start(args,ctor);
	memory_header_t* mh=allocate_memory(ti,n);
	new_ctor_private(mh->ptr_,ti,n,ctor,args);
	va_end(args);
	return mh->ptr_;
}

pointer __newp_array_ctor(void* ptr,const type_info_t* ti,size_t n,constructor ctor,...)
{
	va_list args;
	va_start(args,ctor);
	new_ctor_private(ptr,ti,n,ctor,args);
	va_end(args);
	return ptr;
}

void call_constructor(pointer ptr,constructor ctor,...)
{
	va_list args;
	va_start(args,ctor);
  if(ctor)
    ctor(ptr,args);
	va_end(args);
}

const class_table_t* super_class_table(const_pointer p)
{
  memory_header_t* mh=get_memory_header(p);
  return mh->type_info_->parent_==NULL ? NULL : mh->type_info_->parent_->class_table_;
}
/* **************** Delete ************* */
void __deletep_array(void* ptr,const type_info_t* ti,size_t n)
{
	size_t i;
  // Execute dtors for each item (if not null)
  while(ti != NULL) {
    if(ti->dtor_ != NULL) {
      void* obj=ptr;
      for(i=0;i<n;i++) {
        ti->dtor_(obj);
        obj+=ti->type_size_;
      }
    }
    ti=ti->parent_;
  }
}

void delete_array(void* ptr)
{
	if(ptr) {
		memory_header_t* mh=get_memory_header(ptr);
#ifdef __YAOOC_USE_GC__
    GC_register_finalizer(mh, 0, 0, 0, 0);  // Remove finalizer
#endif
		__deletep_array(ptr,mh->type_info_,mh->n_elem_);
    FREE(mh);
	}
}

void __delete_list(void* ptr,...)
{
  if(ptr) {
    delete(ptr);
    va_list args;
    va_start (args,ptr);
    while((ptr = va_arg(args,void*)) != NULL)
      delete(ptr);
    va_end(args);
  }
}

/*
	**************** Renew ***************
*/
memory_header_t* reallocate_memory(pointer old_ptr,size_t n)
{
	memory_header_t* mh=get_memory_header(old_ptr);
	/* If the same size, renew not needed */
	if(n != mh->n_elem_) {
#ifdef __YAOOC_USE_GC__
    GC_register_finalizer(mh, 0, 0, 0, 0);  // Remove finalizer from old allocated memory
#endif
		/*
			If shrinking array, delete items at end and adjust size.
			If increasing array, calling routine must intialize addition space and adjust size
		*/
		if(n < mh->n_elem_) {
			__deletep_array(mh->ptr_+n*mh->type_info_->type_size_,mh->type_info_,mh->n_elem_-n);
			mh->n_elem_=n;
		}
		mh=REALLOC(mh,n*mh->type_info_->type_size_+offsetof(memory_header_t,ptr_));
#ifdef __YAOOC_USE_GC__
  if(has_destructor(mh->type_info_))
    GC_register_finalizer(mh, __yaooc_gc_finalizer__, 0, 0, 0);
#endif
	}
	return mh;
}

pointer renew_array(pointer ptr,size_t n)
{
	memory_header_t* mh=reallocate_memory(ptr,n);
	if(n > mh->n_elem_) {
		__newp_array(mh->ptr_+mh->n_elem_*mh->type_info_->type_size_,mh->type_info_,n-mh->n_elem_);
		mh->n_elem_=n;
	}
	return mh->ptr_;
}

pointer renew_array_copy(pointer ptr,size_t n,const_pointer src)
{
	memory_header_t* mh=reallocate_memory(ptr,n);
	if(n > mh->n_elem_) {
		__newp_array_copy_static(mh->ptr_+mh->n_elem_*mh->type_info_->type_size_,mh->type_info_,src,n-mh->n_elem_);
		mh->n_elem_=n;
	}
	return mh->ptr_;
}

pointer renew_array_ctor(pointer ptr,size_t n,constructor ctor,...)
{
	memory_header_t* mh=reallocate_memory(ptr,n);
	if(n > mh->n_elem_) {
		va_list args;
		va_start(args,ctor);
		new_ctor_private(mh->ptr_+mh->n_elem_*mh->type_info_->type_size_,mh->type_info_,n-mh->n_elem_,ctor,args);
		va_end(args);
		mh->n_elem_=n;
	}
	return mh->ptr_;
}

/*
	***********  Assignment  *************
*/

/*
	Recurse until an assignment method found.  Return false if root is reached without finding method.
*/
assignment get_assignment(const type_info_t* ti)
{
	while(ti) {
		if(ti->assign_)
			return ti->assign_;
		ti=ti->parent_;
	}
	return NULL;
}

pointer __assign_static(pointer dst,const_pointer src,const type_info_t* ti)
{
	assignment assign_func=get_assignment(ti);
	if(assign_func) {
		assign_func(dst,src);
	} else {
    /*
      If no assignment function found, assume this is POD
    */
		memcpy(dst,src,ti->type_size_);
	}
	return dst;
}

/*
	Compare functions for POD
*/
less_than_compare get_lt_cmp(const type_info_t* ti)
{
	while(ti) {
		if(ti->less_than_compare_)
			return ti->less_than_compare_;
		ti=ti->parent_;
	}
	return NULL;
}

bool op_eq(const_pointer v1,const_pointer v2)
{
	less_than_compare lt_cmp=get_lt_cmp(get_type_info(v1));
	return lt_cmp ? !(lt_cmp(v1,v2) || lt_cmp(v2,v1)): true;
}

bool op_ne(const_pointer v1,const_pointer v2)
{
	less_than_compare lt_cmp=get_lt_cmp(get_type_info(v1));
	return lt_cmp ? (lt_cmp(v1,v2) || lt_cmp(v2,v1)): false;
}

bool op_gt(const_pointer v1,const_pointer v2)
{
	less_than_compare lt_cmp=get_lt_cmp(get_type_info(v1));
	return lt_cmp ? lt_cmp(v2,v1): false;
}

bool op_ge(const_pointer v1,const_pointer v2)
{
	less_than_compare lt_cmp=get_lt_cmp(get_type_info(v1));
	return lt_cmp ? !lt_cmp(v1,v2): true;
}

bool op_lt(const_pointer v1,const_pointer v2)
{
	less_than_compare lt_cmp=get_lt_cmp(get_type_info(v1));
	return lt_cmp ? lt_cmp(v1,v2): false;
}

bool op_le(const_pointer v1,const_pointer v2)
{
	less_than_compare lt_cmp=get_lt_cmp(get_type_info(v1));
	return lt_cmp ? !lt_cmp(v2,v1): true;
}

bool __op_eq_static(const_pointer v1,const_pointer v2,const type_info_t* ti)
{
	less_than_compare lt_cmp=get_lt_cmp(ti);
	return lt_cmp ? !(lt_cmp(v1,v2) || lt_cmp(v2,v1)) : true;
}

bool __op_ne_static(const_pointer v1,const_pointer v2,const type_info_t* ti)
{
	less_than_compare lt_cmp=get_lt_cmp(ti);
	return lt_cmp ? (lt_cmp(v1,v2) || lt_cmp(v2,v1)) : false;
}

bool __op_gt_static(const_pointer v1,const_pointer v2,const type_info_t* ti)
{
	less_than_compare lt_cmp=get_lt_cmp(ti);
	return lt_cmp ? lt_cmp(v2,v1) : false;
}

bool __op_ge_static(const_pointer v1,const_pointer v2,const type_info_t* ti)
{
	less_than_compare lt_cmp=get_lt_cmp(ti);
	return lt_cmp ? !lt_cmp(v1,v2) : true;
}

bool __op_lt_static(const_pointer v1,const_pointer v2,const type_info_t* ti)
{
	less_than_compare lt_cmp=get_lt_cmp(ti);
	return lt_cmp ? lt_cmp(v1,v2) : false;
}

bool __op_le_static(const_pointer v1,const_pointer v2,const type_info_t* ti)
{
	less_than_compare lt_cmp=get_lt_cmp(ti);
	return lt_cmp ? !lt_cmp(v2,v1) : true;
}

to_stream get_to_stream(const type_info_t* ti)
{
	while(ti != NULL) {
		if(ti->to_stream_ != NULL)
			return ti->to_stream_;
		ti=ti->parent_;
	}
	return NULL;
}

from_stream get_from_stream(const type_info_t* ti)
{
	while(ti != NULL) {
		if(ti->from_stream_ != NULL)
			return ti->from_stream_;
		ti=ti->parent_;
	}
	return NULL;
}


/*
  Utility functions
*/
/*
  Swaps objects.  Brute force object swap.  Only reliable works with object of the same type (and size)
*/
void swap_object(void *obj1,void* obj2,size_t obj_size)
{
  if(obj_size > 0) {
    void* temp=MALLOC(obj_size);
    assert(temp && "Error in swap_object");
    memcpy(temp,obj1,obj_size);
    memcpy(obj1,obj2,obj_size);
    memcpy(obj2,temp,obj_size);
    FREE(temp);
  };
}

char* yaooc_strdup(const char* str)
{
  char* dup_str=NULL;
  if(str) {
    size_t len=strlen(str);
    dup_str=__new_array(char_ti,len+1);
    strcpy(dup_str,str);
  }
  return dup_str;
}

char* yaooc_upcase(const char* str)
{
  char* uc_str=yaooc_strdup(str);
  if(uc_str) {
    char* ptr;
    for(ptr=uc_str;*ptr;ptr++)
      *ptr=toupper(*ptr);
  }
  return uc_str;
}

char* yaooc_downcase(const char* str)
{
  char* uc_str=yaooc_strdup(str);
  if(uc_str) {
    char* ptr;
    for(ptr=uc_str;*ptr;ptr++)
      *ptr=tolower(*ptr);
  }
  return uc_str;
}
