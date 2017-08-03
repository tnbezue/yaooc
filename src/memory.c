#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <yaooc/memory.h>

void yaooc_unique_ptr_default_ctor(pointer p)
{
  ((yaooc_unique_ptr_pointer)p)->ptr_=NULL;
}

void yaooc_unique_ptr_dtor(pointer p)
{
  yaooc_unique_ptr_pointer this=p;
  if(this->ptr_)
    delete(this->ptr_);
}

void yaooc_unique_ptr_copy_ctor(pointer d,const_pointer s)
{
  yaooc_unique_ptr_default_ctor(d);
  yaooc_unique_ptr_assign(d,s);
}

void yaooc_unique_ptr_assign(pointer d,const_pointer s)
{
  yaooc_unique_ptr_pointer dst=d;
  yaooc_unique_ptr_pointer src=(yaooc_unique_ptr_pointer)s;
  /*
    Yeah, I know.  Changing the value of a const_pointer
  */
  if(dst->ptr_ != src->ptr_) {
    yaooc_unique_ptr_dtor(dst);
    dst->ptr_=src->ptr_;
    src->ptr_=NULL;
  }
}

/*
  NULL is considered to be less than anything else (other than another NULL)
*/
bool yaooc_unique_ptr_less_than_compare(const_pointer v1,const_pointer v2)
{
  const_pointer p1=((yaooc_unique_ptr_const_pointer)v1)->ptr_;
  const_pointer p2=((yaooc_unique_ptr_const_pointer)v2)->ptr_;
  if(p1 == p2)
    return false;
  if(p1 != NULL) {
    if(p2 != NULL) {
      return op_lt(p1,p2);
    } else
      return false;
  }
  return true;
}

ISA_IMPLEMENTATION(yaooc_unique_ptr,yaooc_object)

void yaooc_unique_ptr_swap(pointer p,pointer o)
{
  yaooc_unique_ptr_pointer this=p;
  yaooc_unique_ptr_pointer other=o;
  if(this != other) {
    SWAP(pointer,this->ptr_,other->ptr_);
  }
}

pointer yaooc_unique_ptr_get(pointer p)
{
  return ((yaooc_unique_ptr_pointer)p)->ptr_;
}

pointer yaooc_unique_ptr_release(pointer p)
{
  pointer temp=((yaooc_unique_ptr_pointer)p)->ptr_;
  ((yaooc_unique_ptr_pointer)p)->ptr_=NULL;
  return temp;
}

void yaooc_unique_ptr_set(pointer p,pointer v)
{
  yaooc_unique_ptr_dtor(p);
  ((yaooc_unique_ptr_pointer)p)->ptr_=v;
}

void yaooc_unique_ptr_ctor_ptr(pointer p,va_list args)
{
  yaooc_unique_ptr_default_ctor(p);
  yaooc_unique_ptr_set(p,va_arg(args,pointer));
}

yaooc_unique_ptr_class_members_t yaooc_unique_ptr_class_members =
{
  {
    yaooc_unique_ptr_isa,
    yaooc_unique_ptr_is_descendent,
    yaooc_unique_ptr_swap
  },
  yaooc_unique_ptr_get,
  (const_pointer(*)(const_pointer))yaooc_unique_ptr_get,
  yaooc_unique_ptr_set,
  yaooc_unique_ptr_release
};

DEFINE_TYPE_INFO(yaooc_unique_ptr,yaooc_unique_ptr_default_ctor,
    yaooc_unique_ptr_dtor,yaooc_unique_ptr_copy_ctor,yaooc_unique_ptr_assign,
    yaooc_unique_ptr_less_than_compare,&yaooc_unique_ptr_class_members,yaooc_object)


/*
  Shared pointer
*/
struct yaooc_counter_s {
	void* ptr_;
	unsigned int count_;
};


static void yaooc_counter_default_ctor(pointer p)
{
  yaooc_counter_t* this=p;
	this->ptr_=NULL;
	this->count_=1;
}

static void yaooc_counter_ctor(pointer p,va_list args)
{
  yaooc_counter_t* this=p;
	this->ptr_=va_arg(args,void *);
	this->count_=1;
}

DEFINE_TYPE_INFO(yaooc_counter,yaooc_counter_default_ctor,NULL,NULL,NULL,NULL,NULL,NULL)

void yaooc_shared_ptr_default_ctor(pointer this)
{
	((yaooc_shared_ptr_pointer)this)->counter_=NULL;
}

void yaooc_shared_ptr_ctor_ptr(pointer p,va_list args)
{
  yaooc_shared_ptr_pointer this=p;
  pointer ptr = va_arg(args,pointer);
	if(ptr == NULL)
		this->counter_=NULL;
	else
		this->counter_=new_ctor(yaooc_counter,yaooc_counter_ctor,ptr);
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

/*
  NULL is considered to be less than anything else (other than another NULL)
*/
bool yaooc_shared_ptr_less_than_compare(const_pointer p1,const_pointer p2)
{
  const_pointer p1p=M(((yaooc_shared_ptr_const_pointer)p1),cget);
  const_pointer p2p=M(((yaooc_shared_ptr_const_pointer)p2),cget);
  if(p1p == p2p)
    return false;
  if(p1p != NULL) {
    if(p2p != NULL) {
      return op_lt(p1p,p2p);
    } else
      return false;
  }
  return true;
}

void yaooc_shared_ptr_acquire(pointer p,yaooc_counter_t* c)
{
	((yaooc_shared_ptr_pointer)p)->counter_=c;
	if(c) ++c->count_;
}

void yaooc_shared_ptr_release(pointer p)
{
	yaooc_shared_ptr_pointer this=p;
  debug(DEBUG_SHARED_PTR) {
    printf("Releasing %p\n",this->counter_);
  }
	if(this->counter_) {
    debug(DEBUG_SHARED_PTR) {
      printf("Count is %d\n",this->counter_->count_);
    }
		if(--this->counter_->count_ == 0) {
      delete(this->counter_->ptr_);  /* counter would have been null if ptr was null */
			delete(this->counter_);
		}
		this->counter_=NULL;
	}
}

void yaooc_shared_ptr_reset(pointer p,pointer obj)
{
  yaooc_shared_ptr_pointer this=p;
  yaooc_shared_ptr_release(this);
  if(obj != NULL)
    this->counter_=new_ctor(yaooc_counter,yaooc_counter_ctor,obj);
}

void* yaooc_shared_ptr_get(pointer p)
{
  yaooc_shared_ptr_pointer this=p;
	return this->counter_ ? this->counter_->ptr_ : NULL;
}

bool yaooc_shared_ptr_unique(const_pointer p)
{
  yaooc_shared_ptr_const_pointer this=p;
	return this->counter_ ? this->counter_->count_ == 1 : true;
}

void yaooc_shared_ptr_swap(pointer p,pointer o)
{
  yaooc_shared_ptr_pointer this=p;
  yaooc_shared_ptr_pointer other=o;
  SWAP(yaooc_counter_t*,this->counter_,other->counter_);
}

unsigned int yaooc_shared_ptr_count(const_pointer p)
{
  yaooc_shared_ptr_const_pointer this=p;
	return this->counter_ ? this->counter_->count_  : 0;
}

ISA_IMPLEMENTATION(yaooc_shared_ptr,yaooc_object)

yaooc_shared_ptr_class_members_t yaooc_shared_ptr_class_members=
{
  {
    yaooc_shared_ptr_isa,
    yaooc_shared_ptr_is_descendent,
    yaooc_shared_ptr_swap
  },
  yaooc_shared_ptr_get,
  (const_pointer (*)(const_pointer))yaooc_shared_ptr_get,
  yaooc_shared_ptr_unique,
  yaooc_shared_ptr_release,
  yaooc_shared_ptr_reset,
  yaooc_shared_ptr_count
};

DEFINE_TYPE_INFO(yaooc_shared_ptr,yaooc_shared_ptr_default_ctor, \
        yaooc_shared_ptr_dtor,yaooc_shared_ptr_copy_ctor,yaooc_shared_ptr_assign, \
        yaooc_shared_ptr_less_than_compare,&yaooc_shared_ptr_class_members,yaooc_object)
