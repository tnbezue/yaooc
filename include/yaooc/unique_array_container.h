#ifndef __UNIQUE_ARRAY_CONTAINER_INCLUDED__
#define __UNIQUE_ARRAY_CONTAINER_INCLUDED__


#include <yaooc/array_container.h>

yaooc_class_table(yaooc_unique_array_container) {
  yaooc_array_container_class_table_t;
};
#define yaooc_unique_array_container_parent_class_table ((yaooc_array_container_class_table_t*)(yaooc_unique_array_container_class_table.parent_class_table_))

yaooc_class_instance(yaooc_unique_array_container) {
  yaooc_array_container_class_instance_t;
};

yaooc_class(yaooc_unique_array_container);

#define yaooc_unique_array_container_swap yaooc_array_container_swap
#define yaooc_unique_array_container_increase_capacity yaooc_array_container_increase_capacity
#define yaooc_unique_array_container_size_needed yaooc_array_container_size_needed
#define yaooc_unique_array_container_size yaooc_array_container_size
#define yaooc_unique_array_container_capacity yaooc_array_container_capacity
#define yaooc_unique_array_container_empty yaooc_array_container_empty
#define yaooc_unique_array_container_begin yaooc_array_container_begin
#define yaooc_unique_array_container_end yaooc_array_container_end
#define yaooc_unique_array_container_cbegin yaooc_array_container_cbegin
#define yaooc_unique_array_container_cend yaooc_array_container_cend
iterator yaooc_unique_array_container_insert(pointer,const_iterator,const_pointer);
iterator yaooc_unique_array_container_insertn(pointer,const_iterator,size_t,const_pointer);
iterator yaooc_unique_array_container_insert_range(pointer,const_iterator,const_iterator,const_iterator);
void yaooc_unique_array_container_resize_value(pointer,size_t,const_pointer);
void yaooc_unique_array_container_resize(pointer,size_t);

#endif
