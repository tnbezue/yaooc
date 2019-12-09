#ifndef __INDEX_ARRAY_CONTAINER_INCLUDED__
#define __INDEX_ARRAY_CONTAINER_INCLUDED__

#include <yaooc/array_container.h>

#include <yaooc/uint24.h>
typedef yaooc_uint24_t yaooc_index_array_container_index_t;
typedef struct {
  
  
	size_t lower_index_;
  size_t upper_index_;
	bool found_;		
} yaooc_index_array_container_find_result_t;

yaooc_class_table(yaooc_index_array_container) {
  yaooc_array_container_class_table_t;
};
#define yaooc_index_array_container_parent_class_table ((yaooc_array_container_class_table_t*)(yaooc_index_array_container_class_table.parent_class_table_))

yaooc_class_instance(yaooc_index_array_container) {
  yaooc_array_container_class_instance_t;
yaooc_index_array_container_index_t* indexes_;
};

yaooc_class(yaooc_index_array_container);
void yaooc_index_array_container_dtor(pointer);
void yaooc_index_array_container_copy_ctor(pointer,const_pointer);
void yaooc_index_array_container_assign(pointer,const_pointer);
void yaooc_index_array_container_ctor_ti(pointer,va_list);
#define yaooc_index_array_container_swap yaooc_array_container_swap
 bool yaooc_index_array_container_increase_capacity(pointer,size_t);
#define yaooc_index_array_container_size_needed yaooc_array_container_size_needed
#define yaooc_index_array_container_size yaooc_array_container_size
#define yaooc_index_array_container_capacity yaooc_array_container_capacity
#define yaooc_index_array_container_empty yaooc_array_container_empty
#define yaooc_index_array_container_begin yaooc_array_container_begin
#define yaooc_index_array_container_end yaooc_array_container_end
#define yaooc_index_array_container_cbegin yaooc_array_container_cbegin
#define yaooc_index_array_container_cend yaooc_array_container_cend
 yaooc_index_array_container_find_result_t yaooc_index_array_container_find_protected(const_pointer,const_pointer);
 void yaooc_index_array_container_insert_index(pointer,size_t,size_t,size_t,size_t);
 void yaooc_index_array_container_remove_index(pointer,size_t,size_t);
 void yaooc_index_array_container_remove_fixed_index(pointer,size_t,size_t);
 iterator yaooc_index_array_container_insert(pointer,const_iterator,const_pointer);
 iterator yaooc_index_array_container_insertn(pointer,const_iterator,size_t,const_pointer);
 iterator yaooc_index_array_container_insert_range(pointer,const_iterator,const_iterator,const_iterator);
 iterator yaooc_index_array_container_find(const_pointer,const_pointer);
 iterator yaooc_index_array_container_erase(pointer,const_iterator);
 size_t yaooc_index_array_container_erase_value(pointer,const_pointer);
 iterator yaooc_index_array_container_erase_range(pointer,const_iterator,const_iterator);
 void yaooc_index_array_container_resize_value(pointer,size_t,const_pointer);
 void yaooc_index_array_container_resize(pointer,size_t);
 void yaooc_index_array_container_shrink_to_fit(pointer);
 void yaooc_index_array_container_reserve(pointer,size_t);
 iterator yaooc_index_array_container_yaooc_index_array_container_at_i(pointer,const_pointer,size_t);
#define AT_I(p,i) AT(p,yaooc_uint24_to_uint32(((yaooc_index_array_container_const_pointer)(p))->indexes_+i))


#endif
