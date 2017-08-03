#ifndef __YAOOC_UNIQUE_CONTAINER_INCLUDED__
#define __YAOOC_UNIQUE_CONTAINER_INCLUDED__

#include <yaooc/container.h>
/*
	"Public" methods.  Private methods would have to be exposed by derived classes
*/

class_table(yaooc_unique_container)
{
  yaooc_container_class_members_t;
};

class_instance(yaooc_unique_container)
{
	yaooc_container_instance_members_t;
};

class(yaooc_unique_container);

ISA_DEFINITION(yaooc_unique_container,yaooc_container)

// Container contructors
// args: 1- const type_info_t*
#define yaooc_unique_container_ctor yaooc_container_ctor

/*
	Only call this from decendant class constructors
*/
#define yaooc_unique_container_internal_ctor yaooc_container_internal_ctor

void yaooc_unique_container_resize(pointer,size_t,const_pointer);
#define yaooc_unique_container_reserve yaooc_container_reserve
#define yaooc_unique_container_clear yaooc_container_clear
#define yaooc_unique_container_shrink_to_fit yaooc_container_shrink_to_fit
#define yaooc_unique_container_at yaooc_container_at
#define yaooc_unique_container_cat yaooc_container_cat
#define yaooc_unique_container_size yaooc_container_size
#define yaooc_unique_container_capacity yaooc_container_capacity
#define yaooc_unique_container_empty yaooc_container_empty
#define yaooc_unique_container_begin yaooc_container_begin
#define yaooc_unique_container_end yaooc_container_end
#define yaooc_unique_container_cbegin yaooc_container_cbegin
#define yaooc_unique_container_cend yaooc_container_cend
#define yaooc_unique_container_get_type_info yaooc_container_get_type_info

iterator yaooc_unique_container_insert(pointer,const_iterator,const_pointer);
iterator yaooc_unique_container_insert_range(pointer,const_iterator,const_iterator,const_iterator);
iterator yaooc_unique_container_insert_n(pointer,const_iterator,size_t,const_pointer);
#define yaooc_unique_container_erase yaooc_container_erase
#define yaooc_unique_container_erase_range yaooc_container_erase_range
size_t yaooc_unique_container_erase_value(pointer p,const_pointer value);
#define yaooc_unique_container_find yaooc_container_find
#define yaooc_unique_container_cfind yaooc_container_cfind
#define yaooc_unique_container_increase_capacity yaooc_container_increase_capacity

#define YAOOC_UNIQUE_CONTAINER_CLASS_MEMBERS \
  { \
    YAOOC_CONTAINER_CLASS_MEMBERS \
  }

#endif
