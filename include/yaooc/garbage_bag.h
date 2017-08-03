#ifndef __GARBAGE_BAG_INCLUDED__
#define __GARBAGE_BAG_INCLUDED__

#include <yaooc/object.h>

/*
  Pointers stored in pointer bag are deleted when pointer bag is deleted.
  Items must be dynamically allocated (new, new_ctor, etc) -- not static (newp, newp_ctor, etc)
*/
typedef pointer* yaooc_garbage_bag_iterator;
typedef const pointer* yaooc_garbage_bag_const_iterator;
class_table(yaooc_garbage_bag)
{
  yaooc_object_class_members_t;
	void* (*push)(pointer,pointer);
  void (*push_list)(pointer,...);
  void (*remove)(pointer,pointer);
  void (*clear)(pointer);
  void (*delete_all)(pointer);
  size_t (*size)(const_pointer);
  bool (*empty)(const_pointer);
  yaooc_garbage_bag_iterator (*begin)(pointer);
  yaooc_garbage_bag_iterator (*end)(pointer);
  yaooc_garbage_bag_const_iterator (*cbegin)(const_pointer);
  yaooc_garbage_bag_const_iterator (*cend)(const_pointer);
};

class_instance(yaooc_garbage_bag)
{
  pointer* array_;
  size_t size_;
  size_t capacity_;
};
class(yaooc_garbage_bag);

ISA_DEFINITION(yaooc_garbage_bag,yaooc_object)
void yaooc_garbage_bag_swap(pointer,pointer);
void* yaooc_garbage_bag_push(pointer,pointer);
void yaooc_garbage_bag_remove(pointer,pointer);
void yaooc_garbage_bag_push_list(pointer,...);
void yaooc_garbage_bag_delete_all(pointer);
void yaooc_garbage_bag_clear(pointer);
size_t yaooc_garbage_bag_size(const_pointer);
bool yaooc_garbage_bag_empty(const_pointer);
yaooc_garbage_bag_iterator yaooc_garbage_bag_begin(pointer);
yaooc_garbage_bag_iterator yaooc_garbage_bag_end(pointer);

#define yaooc_garbage_bag_CLASS_MEMBERS \
  { \
    yaooc_garbage_bag_isa, \
    yaooc_garbage_bag_is_descendent, \
    yaooc_garbage_bag_swap \
  }, \
	yaooc_garbage_bag_push, \
  yaooc_garbage_bag_push_list,\
	yaooc_garbage_bag_remove, \
  yaooc_garbage_bag_clear, \
  yaooc_garbage_bag_delete_all,  \
  yaooc_garbage_bag_size, \
  yaooc_garbage_bag_empty, \
  yaooc_garbage_bag_begin, \
  yaooc_garbage_bag_end, \
  (yaooc_garbage_bag_const_iterator (*)(const_pointer))yaooc_garbage_bag_begin, \
  (yaooc_garbage_bag_const_iterator (*)(const_pointer))yaooc_garbage_bag_end, \

/*
  Macros to help resouce cleanup.  See test_garbage_bag and gen_template for examples of usage
*/
/* Use this at start of routine */
#define GB_INIT  yaooc_garbage_bag_pointer local_pb=real_new_array(yaooc_garbage_bag_ti,1)
/* Saves objects to be deleted at end */
#define GB_SAVE(ptr) (local_pb->class_table_->push(local_pb,ptr))
/* Clears objects, thus none will be deleted at end */
#define GB_CLEAR  (local_pb->class_table_->clear(local_pb))
/* Delete pointer bag and contained pointer */
#define GB_EXIT   delete(local_pb)

#endif
