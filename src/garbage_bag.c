#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaooc/garbage_bag.h>

/*
  If using garbage collection, then garbage bag is not needed.
*/
YAOOC_SIMPLE_ARRAY_IMPLEMENTATION(pointer)
YAOOC_SIMPLE_ARRAY_FIND_POD(pointer)

void yaooc_garbage_bag_default_ctor(pointer p)
{
#ifndef __YAOOC_USE_GC__
  yaooc_garbage_bag_pointer this=p;
  this->pointers_=new(pointer_simple_array);
#endif
}

void yaooc_garbage_bag_dtor(pointer p)
{
#ifndef __YAOOC_USE_GC__
  yaooc_garbage_bag_pointer this=p;
  yaooc_garbage_bag_delete_all(this);
  delete(this->pointers_);
#endif
}

ISA_IMPLEMENTATION(yaooc_garbage_bag,yaooc_object)

void yaooc_garbage_bag_swap(pointer p,pointer o)
{
#ifndef __YAOOC_USE_GC__
  yaooc_garbage_bag_pointer this=p;
  yaooc_garbage_bag_pointer other=o;
  SWAP(pointer_simple_array_t*,this->pointers_,other->pointers_)
#endif
}

void* yaooc_garbage_bag_push(pointer p,pointer ptr)
{
#ifndef __YAOOC_USE_GC__
  yaooc_garbage_bag_pointer this=p;
  if(ptr != NULL)
    pointer_simple_array_insert(this->pointers_,this->pointers_->size_,ptr);
	return ptr;
#endif
}

void yaooc_garbage_bag_remove(pointer p,pointer ptr)
{
#ifndef __YAOOC_USE_GC__
  yaooc_garbage_bag_pointer this=p;
  pointer_simple_array_iterator i=pointer_simple_array_find(this->pointers_,ptr);
  if(i!=SA_END(this->pointers_)) {
    pointer_simple_array_erase(this->pointers_,i-SA_BEGIN(this->pointers_));
  }
#endif
}

void yaooc_garbage_bag_clear(pointer p)
{
#ifndef __YAOOC_USE_GC__
  SA_CLEAR(((yaooc_garbage_bag_pointer)p)->pointers_);
#endif
}

yaooc_size_type yaooc_garbage_bag_size(const_pointer p)
{
#ifndef __YAOOC_USE_GC__
  return ((yaooc_garbage_bag_const_pointer)p)->pointers_->size_;
#else
  return 0;
#endif
}

bool yaooc_garbage_bag_empty(const_pointer p)
{
#ifndef __YAOOC_USE_GC__
  return ((yaooc_garbage_bag_const_pointer)p)->pointers_->size_==0;
#else
  return true;
#endif
}

void yaooc_garbage_bag_push_list(pointer p,...)
{
#ifndef __YAOOC_USE_GC__
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
#endif
}

void yaooc_garbage_bag_delete_all(pointer p)
{
#ifndef __YAOOC_USE_GC__
  yaooc_garbage_bag_pointer this=p;
  pointer_simple_array_iterator i;
  SA_ITERATE(i,this->pointers_) {
    delete(*i);
  }
  SA_CLEAR(this->pointers_);
#endif
}

yaooc_garbage_bag_class_members_t yaooc_garbage_bag_class_members =
{
	YAOOC_GARBAGE_BAG_CLASS_MEMBERS
};

DEFINE_TYPE_INFO(yaooc_garbage_bag,yaooc_garbage_bag_default_ctor,yaooc_garbage_bag_dtor,
      NULL,NULL,NULL,&yaooc_garbage_bag_class_members,NULL)
