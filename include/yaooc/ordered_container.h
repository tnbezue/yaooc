#ifndef __YAOOC_ORDERED_CONTAINER_INCLUDED__
#define __YAOOC_ORDERED_CONTAINER_INCLUDED__

#include <yaooc/container.h>

class_table(yaooc_ordered_container)
{
  yaooc_container_class_members_t;
};

class_instance(yaooc_ordered_container)
{
	yaooc_container_instance_members_t;
};

class(yaooc_ordered_container);
ISA_DEFINITION(yaooc_ordered_container,yaooc_container)

// Container contructors
// args: 1- const type_info_t*
#define yaooc_ordered_container_ctor yaooc_container_ctor

#define yaooc_ordered_container_internal_ctor yaooc_container_internal_ctor

void yaooc_ordered_container_resize(pointer,size_t,const_pointer);
#define yaooc_ordered_container_reserve yaooc_container_reserve
#define yaooc_ordered_container_clear yaooc_container_clear
#define yaooc_ordered_container_shrink_to_fit yaooc_container_shrink_to_fit
#define yaooc_ordered_container_at yaooc_container_at
#define yaooc_ordered_container_size yaooc_container_size
#define yaooc_ordered_container_capacity yaooc_container_capacity
#define yaooc_ordered_container_empty yaooc_container_empty
#define yaooc_ordered_container_clear yaooc_container_clear
#define yaooc_ordered_container_begin yaooc_container_begin
#define yaooc_ordered_container_end yaooc_container_end
#define yaooc_ordered_container_cbegin yaooc_container_cbegin
#define yaooc_ordered_container_cend yaooc_container_cend
#define yaooc_ordered_container_get_type_info yaooc_container_get_type_info

iterator yaooc_ordered_container_insert(pointer,const_iterator,const_pointer); //,size_t n);  // insert n elements starting a pos
iterator yaooc_ordered_container_insert_range(pointer,const_iterator,const_iterator,const_iterator);
iterator yaooc_ordered_container_insert_n(pointer,const_iterator,size_t,const_pointer);
#define yaooc_ordered_container_erase yaooc_container_erase
#define yaooc_ordered_container_erase_range yaooc_container_erase_range
size_t yaooc_ordered_container_erase_value(pointer,const_pointer);

iterator yaooc_ordered_container_find(const_pointer p,const_pointer value);

#define yaooc_ordered_container_default_ctor yaooc_container_default_ctor
#define yaooc_ordered_container_dtor yaooc_container_dtor
#define yaooc_ordered_container_copy_ctor yaooc_container_copy_ctor
#define yaooc_ordered_container_assign yaooc_container_assign

#define yaooc_ordered_container_increase_capacity yaooc_container_increase_capacity

typedef struct {
	bool found_;			// indicates if item found
	yaooc_private_iterator position_;	// position at which it was found.  If found is false, indicates position to insert item
} yaooc_ordered_container_find_result_t;

yaooc_ordered_container_find_result_t yaooc_ordered_container_find_private(const_pointer p,const_pointer value);

#define YAOOC_ORDERED_CONTAINER_CLASS_MEMBERS \
  { \
    YAOOC_CONTAINER_CLASS_MEMBERS \
  }


#endif
