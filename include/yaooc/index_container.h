#ifndef __YAOOC_INDEX_CONTAINER_INCLUDED__
#define __YAOOC_INDEX_CONTAINER_INCLUDED__

#include <yaooc/container.h>

class_table(yaooc_index_container)
{
  yaooc_container_class_members_t;
};

class_instance(yaooc_index_container)
{
	yaooc_container_instance_members_t;
	size_t* index_;
};

class(yaooc_index_container);
ISA_DEFINITION(yaooc_index_container,yaooc_container)

typedef struct {
	size_t	index_;  // index in ordered index array of where insertion should occur
	bool found_;		// indicates whether found
} yaooc_index_container_find_result_t;

// Container contructors
// args: 1- const type_info_t*
void yaooc_index_container_ctor(pointer p,va_list args);

void yaooc_index_container_internal_ctor(yaooc_index_container_pointer this,const type_info_t* ti);

void yaooc_index_container_resize(pointer,size_t,const_pointer);
void yaooc_index_container_reserve(pointer,size_t);
void yaooc_insert_index(pointer,size_t,size_t,size_t,size_t);
#define yaooc_index_container_clear   yaooc_container_clear
void yaooc_index_container_shrink_to_fit(pointer p); // shrink array capcity
#define yaooc_index_container_at yaooc_container_at
#define yaooc_index_container_cat yaooc_container_cat
#define yaooc_index_container_size yaooc_container_size
#define yaooc_index_container_capacity yaooc_container_capacity
#define yaooc_index_container_empty yaooc_container_empty
#define yaooc_index_container_clear yaooc_container_clear
#define yaooc_index_container_begin yaooc_container_begin
#define yaooc_index_container_end yaooc_container_end
#define yaooc_index_container_get_type_info yaooc_container_get_type_info

iterator yaooc_index_container_insert(pointer,const_iterator,const_pointer); //,size_t n);  // insert n elements starting a pos
iterator yaooc_index_container_insert_range(pointer,const_iterator,const_iterator,const_iterator);
iterator yaooc_index_container_insert_n(pointer,const_iterator,size_t,const_pointer);
iterator yaooc_index_container_erase(pointer,iterator);  // erase n elements starting at pos
iterator yaooc_index_container_erase_range(pointer,iterator,iterator);  // erase n elements starting at pos
void yaooc_index_container_swap(pointer,pointer);

yaooc_index_container_find_result_t
	yaooc_index_container_private_find(yaooc_index_container_const_pointer p,const_pointer value);
iterator yaooc_index_container_find(const_pointer p,const_pointer value);
bool yaooc_index_container_increase_capacity(pointer p,size_t n);

#define yaooc_index_container_default_ctor yaooc_container_default_ctor
//void yaooc_index_container_dtor(pointer);
void yaooc_index_container_copy_ctor(pointer,const_pointer);
void yaooc_index_container_assign(pointer,const_pointer);

#define YAOOC_INDEX_CONTAINER_CLASS_MEMBERS \
  { \
    YAOOC_CONTAINER_CLASS_MEMBERS \
  }

#endif
