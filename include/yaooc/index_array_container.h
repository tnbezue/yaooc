#ifndef __YAOOC_INDEX_CONTAINER_INCLUDED__
#define __YAOOC_INDEX_CONTAINER_INCLUDED__

#include <yaooc/array_container.h>

class_table(yaooc_index_array_container)
{
  yaooc_array_container_class_members_t;
};

class_instance(yaooc_index_array_container)
{
	yaooc_array_container_instance_members_t;
	yaooc_size_type* index_;
};

class(yaooc_index_array_container);
ISA_DEFINITION(yaooc_index_array_container,yaooc_array_container)

typedef struct {
	yaooc_size_type	index_;  // index in ordered index array of where insertion should occur
	bool found_;		// indicates whether found
} yaooc_index_array_container_find_result_t;

// Container contructors
// args: 1- const type_info_t*
void yaooc_index_array_container_ctor(pointer p,va_list args);

void yaooc_index_array_container_internal_ctor(yaooc_index_array_container_pointer this,const type_info_t* ti);

void yaooc_index_array_container_resize(pointer,yaooc_size_type,const_pointer);
void yaooc_index_array_container_reserve(pointer,yaooc_size_type);
void yaooc_insert_index(pointer,yaooc_size_type,yaooc_size_type,yaooc_size_type,yaooc_size_type);
#define yaooc_index_array_container_clear   yaooc_array_container_clear
void yaooc_index_array_container_shrink_to_fit(pointer p); // shrink array capcity
#define yaooc_index_array_container_at yaooc_array_container_at
#define yaooc_index_array_container_cat yaooc_array_container_cat
#define yaooc_index_array_container_size yaooc_array_container_size
#define yaooc_index_array_container_capacity yaooc_array_container_capacity
#define yaooc_index_array_container_empty yaooc_array_container_empty
#define yaooc_index_array_container_clear yaooc_array_container_clear
#define yaooc_index_array_container_begin yaooc_array_container_begin
#define yaooc_index_array_container_end yaooc_array_container_end
#define yaooc_index_array_container_get_type_info yaooc_array_container_get_type_info

iterator yaooc_index_array_container_insert(pointer,const_iterator,const_pointer); //,yaooc_size_type n);  // insert n elements starting a pos
iterator yaooc_index_array_container_insert_range(pointer,const_iterator,const_iterator,const_iterator);
iterator yaooc_index_array_container_insert_n(pointer,const_iterator,yaooc_size_type,const_pointer);
iterator yaooc_index_array_container_erase(pointer,iterator);  // erase n elements starting at pos
iterator yaooc_index_array_container_erase_range(pointer,iterator,iterator);  // erase n elements starting at pos
void yaooc_index_array_container_swap(pointer,pointer);

yaooc_index_array_container_find_result_t
	yaooc_index_array_container_private_find(yaooc_index_array_container_const_pointer p,const_pointer value);
iterator yaooc_index_array_container_find(const_pointer p,const_pointer value);
bool yaooc_index_array_container_increase_capacity(pointer p,yaooc_size_type n);

#define yaooc_index_array_container_default_ctor yaooc_array_container_default_ctor
//void yaooc_index_array_container_dtor(pointer);
void yaooc_index_array_container_copy_ctor(pointer,const_pointer);
void yaooc_index_array_container_assign(pointer,const_pointer);

#define YAOOC_INDEX_ARRAY_CONTAINER_CLASS_MEMBERS \
  { \
    YAOOC_ARRAY_CONTAINER_CLASS_MEMBERS \
  }

#endif
