#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <yaooc/new.h>
#include <yaooc/yaooc_debug.h>

/*
	Header for allocated objects.
*/
typedef struct {
	const type_info_t* type_info_;
	size_t	n_elem_;			// number of elements allocated
	char ptr_[0];
} memory_header_t;

memory_header_t* get_memory_header(const_pointer ptr)
{
	memory_header_t* mh=(memory_header_t*)((char*)ptr - offsetof(memory_header_t,ptr_));
	return mh;
}

const type_info_t* const get_type_info(const_pointer ptr)
{
	return get_memory_header(ptr)->type_info_;
}
#ifdef __YAOOC_USE_GC__
/*
  When using the garbage collector, don't need to specify a finalizer if there isn't a destructor.
  This function checks if a detructor will be executed when deleted.
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

/*
  Finalizer calls the destructor for the allocated object
*/
static void __yaooc_finalizer__(GC_PTR obj, GC_PTR x)
{
  memory_header_t* mh=(memory_header_t*)obj;
  real_deletep_array(mh->ptr_,mh->type_info_,mh->n_elem_);
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
    GC_register_finalizer(mh, __yaooc_finalizer__, 0, 0, 0);
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

pointer real_newp_array(pointer ptr,const type_info_t* ti,size_t n_elements)
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

pointer real_new_array(const type_info_t* ti,size_t n)
{
	memory_header_t* mh=allocate_memory(ti,n);
	return real_newp_array(mh->ptr_,ti,n);
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

pointer real_newp_array_copy_static(pointer dst,const type_info_t* ti,const_pointer src,size_t n_elements)
{
	yaooc_private_iterator idst=dst;
	size_t i;
	copy_constructor copy_ctor=get_copy_ctor(ti);
	size_t element_size=ti->type_size_;
	bool has_class_table = ti->class_table_ != NULL;
	for(i=0;i<n_elements;i++) {
		if(copy_ctor) {
			if(has_class_table) // if there is a class table, copy it from source rather than type info
				copy_class_table(idst,((base_object_t*)src)->class_table);
			copy_ctor(idst,src);
		} else {
			memcpy(idst,src,element_size); // class table pointer included in copy
		}
		idst+=element_size;
	}
	return dst;
}

pointer real_new_array_copy_static(const type_info_t* ti,const_pointer src,size_t n)
{
	memory_header_t* mh=allocate_memory(ti,n);
	return real_newp_array_copy_static(mh->ptr_,ti,src,n);
}

pointer real_new_array_copy(const_pointer src,size_t n)
{
	return real_new_array_copy_static(get_type_info(src),src,n);
}

pointer real_newp_array_copy(pointer dst,const_pointer src,size_t n)
{
	return real_newp_array_copy_static(dst,get_type_info(src),src,n);
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

pointer real_new_array_ctor(const type_info_t* ti,size_t n,constructor ctor,...)
{
	va_list args;
	va_start(args,ctor);
	memory_header_t* mh=allocate_memory(ti,n);
	new_ctor_private(mh->ptr_,ti,n,ctor,args);
	va_end(args);
	return mh->ptr_;
}

pointer real_newp_array_ctor(void* ptr,const type_info_t* ti,size_t n,constructor ctor,...)
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
void real_deletep_array(void* ptr,const type_info_t* ti,size_t n)
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
		real_deletep_array(ptr,mh->type_info_,mh->n_elem_);
    FREE(mh);
	}
}

void delete_list(pointer ptr,...)
{
  if(ptr) {
    delete(ptr);
    va_list args;
    va_start (args,ptr);
    while((ptr = va_arg(args,pointer)) != NULL)
      delete(ptr);
    va_end(args);
  }
}

#ifdef __YAOOC_USE_GC__
#endif
/*
	**************** Renew ***************
*/
typedef struct {
	iterator ptr; // pointer to beginning of array to be returned by calling function
	iterator dst; // pointer to where new members added -- NULL if no elements are added
	const type_info_t* ti;
	size_t	n;		// number of new elements
} renew_info_t;
renew_info_t renew_private(pointer old_ptr,size_t n_new)
{
	renew_info_t ri;
	memory_header_t* mh_old=get_memory_header(old_ptr);
	/* If the same size, renew not needed */
	if(n_new == mh_old->n_elem_) {
		ri.ptr=mh_old->ptr_;
		ri.dst=NULL;
		ri.n=0;
	} else {
		size_t n_copy;
#ifdef __YAOOC_USE_GC__
    GC_register_finalizer(mh_old, 0, 0, 0, 0);  // Remove finalizer from old allocated memory
#endif
		memory_header_t* mh_new=allocate_memory(mh_old->type_info_,n_new);
		ri.ptr=mh_new->ptr_;
		ri.ti=mh_new->type_info_;
		if(n_new < mh_old->n_elem_) {
			real_deletep_array(mh_old->ptr_+n_new*mh_old->type_info_->type_size_,mh_old->type_info_,mh_old->n_elem_-n_new);
			ri.dst=NULL;
			ri.n=0;
			n_copy=n_new;
		} else {
			ri.dst=mh_new->ptr_+mh_old->n_elem_*mh_old->type_info_->type_size_;
			ri.n=n_new-mh_old->n_elem_;
			n_copy=mh_old->n_elem_;
		}
		memcpy(mh_new->ptr_,old_ptr,n_copy*mh_new->type_info_->type_size_);
	}
	return ri;
}

pointer renew_array(pointer ptr,size_t n)
{
	renew_info_t ri=renew_private(ptr,n);
	if(ri.dst) {
		real_newp_array(ri.dst,ri.ti,ri.n);
	}
	return ri.ptr;
}

pointer renew_array_copy(pointer ptr,size_t n,const_pointer src)
{
	renew_info_t ri=renew_private(ptr,n);
	if(ri.dst) {
		real_newp_array_copy_static(ri.dst,ri.ti,src,ri.n);
	}
	return ri.ptr;
}

pointer renew_array_ctor(pointer ptr,size_t n,constructor ctor,...)
{
	renew_info_t ri=renew_private(ptr,n);
	if(ri.dst) {
		va_list args;
		va_start(args,ctor);
		new_ctor_private(ri.dst,ri.ti,ri.n,ctor,args);
		va_end(args);
	}
	return ri.ptr;
}

/*
	***********  Assignment  *************
*/

/*
	Recurse until an assignment method found.  Return false if root is reached without finding method.
*/
assignment get_assignment(const type_info_t* ti)
{
	if(ti) {
		return ti->assign_ ? ti->assign_ : get_assignment(ti->parent_);
	}
	return NULL;
}

pointer real_assign_static(pointer dst,const_pointer src,const type_info_t* ti)
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

pointer assign(pointer dst,const_pointer src)
{
	return real_assign_static(dst,src,get_type_info(src));
}

/*
	Compare functions for POD
*/
less_than_compare get_lt_cmp(const type_info_t* ti)
{
	if(ti) {
		return ti->less_than_compare_ ? ti->less_than_compare_ : get_lt_cmp(ti->parent_);
	}
	return NULL;
}

bool __lt_cmp__(const_pointer v1,const_pointer v2,less_than_compare lt_cmp_func)
{
  return lt_cmp_func(v1,v2);
}

bool op_eq(const_pointer v1,const_pointer v2)
{
	less_than_compare lt_cmp=get_lt_cmp(get_type_info(v1));
	return lt_cmp ? !(__lt_cmp__(v1,v2,lt_cmp) || __lt_cmp__(v2,v1,lt_cmp)): true;
}

bool op_ne(const_pointer v1,const_pointer v2)
{
	less_than_compare lt_cmp=get_lt_cmp(get_type_info(v1));
	return lt_cmp ? (__lt_cmp__(v1,v2,lt_cmp) || __lt_cmp__(v2,v1,lt_cmp)): false;
}

bool op_gt(const_pointer v1,const_pointer v2)
{
	less_than_compare lt_cmp=get_lt_cmp(get_type_info(v1));
	return lt_cmp ? __lt_cmp__(v2,v1,lt_cmp): false;
}

bool op_ge(const_pointer v1,const_pointer v2)
{
	less_than_compare lt_cmp=get_lt_cmp(get_type_info(v1));
	return lt_cmp ? !__lt_cmp__(v1,v2,lt_cmp): true;
}

bool op_lt(const_pointer v1,const_pointer v2)
{
	less_than_compare lt_cmp=get_lt_cmp(get_type_info(v1));
	return lt_cmp ? __lt_cmp__(v1,v2,lt_cmp): false;
}

bool op_le(const_pointer v1,const_pointer v2)
{
	less_than_compare lt_cmp=get_lt_cmp(get_type_info(v1));
	return lt_cmp ? !__lt_cmp__(v2,v1,lt_cmp): true;
}

bool op_eq_static(const_pointer v1,const_pointer v2,const type_info_t* ti)
{
	less_than_compare lt_cmp=get_lt_cmp(ti);
	return lt_cmp ? !(__lt_cmp__(v1,v2,lt_cmp) || __lt_cmp__(v2,v1,lt_cmp)) : true;
}

bool op_ne_static(const_pointer v1,const_pointer v2,const type_info_t* ti)
{
	less_than_compare lt_cmp=get_lt_cmp(ti);
	return lt_cmp ? (__lt_cmp__(v1,v2,lt_cmp) || __lt_cmp__(v2,v1,lt_cmp)) : false;
}

bool op_gt_static(const_pointer v1,const_pointer v2,const type_info_t* ti)
{
	less_than_compare lt_cmp=get_lt_cmp(ti);
	return lt_cmp ? __lt_cmp__(v2,v1,lt_cmp) : false;
}

bool op_ge_static(const_pointer v1,const_pointer v2,const type_info_t* ti)
{
	less_than_compare lt_cmp=get_lt_cmp(ti);
	return lt_cmp ? !__lt_cmp__(v1,v2,lt_cmp) : true;
}

bool op_lt_static(const_pointer v1,const_pointer v2,const type_info_t* ti)
{
	less_than_compare lt_cmp=get_lt_cmp(ti);
	return lt_cmp ? __lt_cmp__(v1,v2,lt_cmp) : false;
}

bool op_le_static(const_pointer v1,const_pointer v2,const type_info_t* ti)
{
	less_than_compare lt_cmp=get_lt_cmp(ti);
	return lt_cmp ? !__lt_cmp__(v2,v1,lt_cmp) : true;
}

/*
  Type info for POD
*/
#define POD_TYPE_INFO_IMPLEMENTATION(T) \
bool T ## _less_than_compare(T ## _const_pointer v1,T ## _const_pointer v2) { return *v1 < *v2; } \
DEFINE_TYPE_INFO(T,NULL,NULL,NULL,NULL,(less_than_compare)T ## _less_than_compare,NULL,NULL )

POD_TYPE_INFO_IMPLEMENTATION(char)
POD_TYPE_INFO_IMPLEMENTATION(uchar)
POD_TYPE_INFO_IMPLEMENTATION(int)
POD_TYPE_INFO_IMPLEMENTATION(uint)
POD_TYPE_INFO_IMPLEMENTATION(long)
POD_TYPE_INFO_IMPLEMENTATION(ulong)
POD_TYPE_INFO_IMPLEMENTATION(long_long)
POD_TYPE_INFO_IMPLEMENTATION(ulong_long)
POD_TYPE_INFO_IMPLEMENTATION(int16)
POD_TYPE_INFO_IMPLEMENTATION(uint16)
POD_TYPE_INFO_IMPLEMENTATION(int32)
POD_TYPE_INFO_IMPLEMENTATION(uint32)
POD_TYPE_INFO_IMPLEMENTATION(int64)
POD_TYPE_INFO_IMPLEMENTATION(uint64)
POD_TYPE_INFO_IMPLEMENTATION(double)

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
    dup_str=real_new_array(char_ti,len+1);
    strcpy(dup_str,str);
  }
  return dup_str;
}
