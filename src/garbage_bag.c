#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <yaooc/garbage_bag.h>

void yaooc_garbage_bag_default_ctor(pointer p)
{
  yaooc_garbage_bag_pointer this=p;
  this->size_=0;
  this->capacity_=16;
  this->array_=(pointer*)MALLOC(this->capacity_*sizeof(pointer));
}


void yaooc_garbage_bag_dtor(pointer p)
{
  yaooc_garbage_bag_pointer this=p;
  yaooc_garbage_bag_delete_all(this);
  FREE(this->array_);
}

ISA_IMPLEMENTATION(yaooc_garbage_bag,yaooc_object)

void yaooc_garbage_bag_swap(pointer p,pointer o)
{
  yaooc_garbage_bag_pointer this=p;
  yaooc_garbage_bag_pointer other=o;
  SWAP(pointer*,this->array_,other->array_)
  SWAP(size_t,this->size_,other->size_)
  SWAP(size_t,this->capacity_,other->capacity_)
}

void* yaooc_garbage_bag_push(pointer p,pointer ptr)
{
  yaooc_garbage_bag_pointer this=p;
  if(this->size_==this->capacity_) {
    this->capacity_*=2;
    this->array_=(pointer*)REALLOC(this->array_,this->capacity_*sizeof(pointer));
  }
  /* Don't allow NULL pointers to be saved */
  if(ptr != NULL)
    this->array_[this->size_++]=ptr;
	return ptr;
}

void yaooc_garbage_bag_remove(pointer p,pointer ptr)
{
  yaooc_garbage_bag_pointer this=p;
  size_t i;
  for(i=0;i<this->size_;i++) {
    if(this->array_[i]==ptr) {
      memmove(this->array_+i,this->array_+i+1,(this->size_-(i+1))*sizeof(pointer));
      this->size_--;
    }
  }
}

void yaooc_garbage_bag_clear(pointer p)
{
  ((yaooc_garbage_bag_pointer)p)->size_=0;
}

size_t yaooc_garbage_bag_size(const_pointer p)
{
  return ((yaooc_garbage_bag_const_pointer)p)->size_;
}

bool yaooc_garbage_bag_empty(const_pointer p)
{
  return ((yaooc_garbage_bag_const_pointer)p)->size_==0;
}

yaooc_garbage_bag_iterator yaooc_garbage_bag_begin(pointer p)
{
  return ((yaooc_garbage_bag_pointer)p)->array_;
}

yaooc_garbage_bag_iterator yaooc_garbage_bag_end(pointer p)
{
  yaooc_garbage_bag_pointer this=p;
  return this->array_+this->size_;
}

void yaooc_garbage_bag_push_list(pointer p,...)
{
  yaooc_garbage_bag_pointer this=p;
	// Last one must be NULL
	void* ptr;
	va_list args;
	va_start (args,p);
	while(1) {
		ptr = va_arg(args,pointer);
		if(ptr == NULL)
			break;
		yaooc_garbage_bag_push(this,ptr);
	}
	va_end(args);
}

void yaooc_garbage_bag_delete_all(pointer p)
{
  yaooc_garbage_bag_pointer this=p;
  pointer* i=this->array_;
  pointer* end=this->array_+this->size_;
  for(i=this->array_;i!=end;i++) {
    delete(*i);
  }
  this->size_=0;
}

yaooc_garbage_bag_class_members_t yaooc_garbage_bag_class_members =
{
	yaooc_garbage_bag_CLASS_MEMBERS
};

DEFINE_TYPE_INFO(yaooc_garbage_bag,yaooc_garbage_bag_default_ctor,yaooc_garbage_bag_dtor,
      NULL,NULL,NULL,&yaooc_garbage_bag_class_members,NULL)
