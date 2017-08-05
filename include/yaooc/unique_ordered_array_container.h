#ifndef __YAOOC_UNIQUE_ORDERED_ARRAY_CONTAINER_INCLUDED__
#define __YAOOC_UNIQUE_ORDERED_ARRAY_CONTAINER_INCLUDED__

#include <yaooc/ordered_array_container.h>

class_table(yaooc_unique_ordered_array_container)
{
  yaooc_ordered_array_container_class_members_t;
};

class_instance(yaooc_unique_ordered_array_container)
{
	yaooc_ordered_array_container_instance_members_t;
};

class(yaooc_unique_ordered_array_container);
ISA_DEFINITION(yaooc_unique_ordered_array_container,yaooc_ordered_array_container)

// Container contructors
// args: 1- const type_info_t*
#define yaooc_unique_ordered_array_container_ctor yaooc_ordered_array_container_ctor

#define yaooc_unique_ordered_array_container_internal_ctor yaooc_ordered_array_container_internal_ctor

/* Not useful for this type of container, but define it anyway */
iterator yaooc_unique_ordered_array_container_resize(pointer,const_iterator,const_pointer);
#define yaooc_unique_ordered_array_container_reserve yaooc_ordered_array_container_reserve
#define yaooc_unique_ordered_array_container_clear yaooc_ordered_array_container_clear
#define yaooc_unique_ordered_array_container_shrink_to_fit yaooc_ordered_array_container_shrink_to_fit
#define yaooc_unique_ordered_array_container_at yaooc_ordered_array_container_at
#define yaooc_unique_ordered_array_container_cat yaooc_ordered_array_container_cat
#define yaooc_unique_ordered_array_container_size yaooc_ordered_array_container_size
#define yaooc_unique_ordered_array_container_capacity yaooc_ordered_array_container_capacity
#define yaooc_unique_ordered_array_container_empty yaooc_ordered_array_container_empty
#define yaooc_unique_ordered_array_container_clear yaooc_ordered_array_container_clear
#define yaooc_unique_ordered_array_container_begin yaooc_ordered_array_container_begin
#define yaooc_unique_ordered_array_container_end yaooc_ordered_array_container_end
#define yaooc_unique_ordered_array_container_cbegin yaooc_ordered_array_container_cbegin
#define yaooc_unique_ordered_array_container_cend yaooc_ordered_array_container_cend
#define yaooc_unique_ordered_array_container_get_type_info yaooc_ordered_array_container_get_type_info

iterator yaooc_unique_ordered_array_container_insert(pointer,const_iterator,const_pointer); //,size_t n);  // insert n elements starting a pos
iterator yaooc_unique_ordered_array_container_insert_range(pointer,const_iterator,const_iterator,const_iterator);
/*
	Not useful for this type of container, but define if anyway
*/
iterator yaooc_unique_ordered_array_container_insert_n(pointer,const_iterator,yaooc_size_type,const_pointer);
#define yaooc_unique_ordered_array_container_erase yaooc_ordered_array_container_erase
#define yaooc_unique_ordered_array_container_erase_range yaooc_ordered_array_container_erase_range
#define yaooc_unique_ordered_array_container_erase_value yaooc_ordered_array_container_erase_value
#define yaooc_unique_ordered_array_container_find yaooc_ordered_array_container_find
#define yaooc_unique_ordered_array_container_cfind yaooc_ordered_array_container_cfind

#define yaooc_unique_ordered_array_container_default_ctor yaooc_ordered_array_container_default_ctor
#define yaooc_unique_ordered_array_container_dtor yaooc_ordered_array_container_dtor
#define yaooc_unique_ordered_array_container_copy_ctor yaooc_ordered_array_container_copy_ctor
#define yaooc_unique_ordered_array_container_assign yaooc_ordered_array_container_assign

#define yaooc_unique_ordered_array_container_increase_capacity yaooc_ordered_array_container_increase_capacity

#define yaooc_unique_ordered_array_container_find_result_t yaooc_ordered_array_container_find_result_t

#define yaooc_unique_ordered_array_container_find_private yaooc_ordered_array_container_find_private

#define YAOOC_UNIQUE_ORDERED_ARRAY_CONTAINER_CLASS_MEMBERS \
  { \
    YAOOC_ORDERED_ARRAY_CONTAINER_CLASS_MEMBERS \
  }


#endif
