#ifndef __yaooc_unique_array_container_INCLUDED__
#define __yaooc_unique_array_container_INCLUDED__

#include <yaooc/array_container.h>
/*
	"Public" methods.  Private methods would have to be exposed by derived classes
*/

class_table(yaooc_unique_array_container)
{
  yaooc_array_container_class_members_t;
};

class_instance(yaooc_unique_array_container)
{
	yaooc_array_container_instance_members_t;
};

class(yaooc_unique_array_container);

ISA_DEFINITION(yaooc_unique_array_container,yaooc_array_container)

// Container contructors
// args: 1- const type_info_t*
#define yaooc_unique_array_container_ctor yaooc_array_container_ctor

/*
	Only call this from decendant class constructors
*/
#define yaooc_unique_array_container_internal_ctor yaooc_array_container_internal_ctor

void yaooc_unique_array_container_resize(pointer,yaooc_size_type,const_pointer);
#define yaooc_unique_array_container_reserve yaooc_array_container_reserve
#define yaooc_unique_array_container_clear yaooc_array_container_clear
#define yaooc_unique_array_container_shrink_to_fit yaooc_array_container_shrink_to_fit
#define yaooc_unique_array_container_at yaooc_array_container_at
#define yaooc_unique_array_container_cat yaooc_array_container_cat
#define yaooc_unique_array_container_size yaooc_array_container_size
#define yaooc_unique_array_container_capacity yaooc_array_container_capacity
#define yaooc_unique_array_container_empty yaooc_array_container_empty
#define yaooc_unique_array_container_begin yaooc_array_container_begin
#define yaooc_unique_array_container_end yaooc_array_container_end
#define yaooc_unique_array_container_cbegin yaooc_array_container_cbegin
#define yaooc_unique_array_container_cend yaooc_array_container_cend
#define yaooc_unique_array_container_get_type_info yaooc_array_container_get_type_info

iterator yaooc_unique_array_container_insert(pointer,const_iterator,const_pointer);
iterator yaooc_unique_array_container_insert_range(pointer,const_iterator,const_iterator,const_iterator);
iterator yaooc_unique_array_container_insert_n(pointer,const_iterator,yaooc_size_type,const_pointer);
#define yaooc_unique_array_container_erase yaooc_array_container_erase
#define yaooc_unique_array_container_erase_range yaooc_array_container_erase_range
yaooc_size_type yaooc_unique_array_container_erase_value(pointer p,const_pointer value);
#define yaooc_unique_array_container_find yaooc_array_container_find
#define yaooc_unique_array_container_cfind yaooc_array_container_cfind
#define yaooc_unique_array_container_increase_capacity yaooc_array_container_increase_capacity

#define YAOOC_UNIQUE_ARRAY_CONTAINER_CLASS_MEMBERS \
  { \
    YAOOC_ARRAY_CONTAINER_CLASS_MEMBERS \
  }

#endif
