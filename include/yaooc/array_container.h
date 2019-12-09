#ifndef __ARRAY_CONTAINER_INCLUDED__
#define __ARRAY_CONTAINER_INCLUDED__

#include <yaooc/object.h>

#include <yaooc/algorithm.h>
#include <yaooc/stream.h>
void throw_yaooc_array_container_exception(pointer,const char*);

yaooc_class_table(yaooc_array_container) {
  yaooc_object_class_table_t;
bool (*increase_capacity)(pointer,size_t);
size_t (*size_needed)(const_pointer,size_t);
size_t (*size)(const_pointer);
size_t (*capacity)(const_pointer);
bool (*empty)(const_pointer);
iterator (*begin)(pointer);
iterator (*end)(pointer);
const_iterator (*cbegin)(const_pointer);
const_iterator (*cend)(const_pointer);
};
#define yaooc_array_container_parent_class_table ((yaooc_object_class_table_t*)(yaooc_array_container_class_table.parent_class_table_))

yaooc_class_instance(yaooc_array_container) {
char* array_;
const type_info_t* type_info_;
size_t size_;
size_t capacity_;
};

yaooc_class(yaooc_array_container);
void yaooc_array_container_default_ctor(pointer);
void yaooc_array_container_dtor(pointer);
void yaooc_array_container_copy_ctor(pointer,const_pointer);
void yaooc_array_container_assign(pointer,const_pointer);
int yaooc_array_container_rich_compare(const_pointer,const_pointer);
void yaooc_array_container_to_stream(const_pointer,ostream_pointer);
void yaooc_array_container_ctor_ti(pointer,va_list);
 void yaooc_array_container_swap(pointer,pointer);
 bool yaooc_array_container_increase_capacity(pointer,size_t);
 size_t yaooc_array_container_size_needed(const_pointer,size_t);
 size_t yaooc_array_container_size(const_pointer);
 size_t yaooc_array_container_capacity(const_pointer);
 bool yaooc_array_container_empty(const_pointer);
 iterator yaooc_array_container_begin(pointer);
 iterator yaooc_array_container_end(pointer);
#define yaooc_array_container_cbegin yaooc_array_container_begin
#define yaooc_array_container_cend yaooc_array_container_end
 iterator yaooc_array_container_insert_space(pointer,const_iterator,size_t);
 iterator yaooc_array_container_erase_space(pointer,const_iterator,size_t);
 iterator yaooc_array_container_replace_space(pointer,const_iterator,const_iterator,size_t);
 iterator yaooc_array_container_find(pointer,const_pointer);
 iterator yaooc_array_container_insert(pointer,const_iterator,const_pointer);
 iterator yaooc_array_container_insertn(pointer,const_iterator,size_t,const_pointer);
 iterator yaooc_array_container_insert_range(pointer,const_iterator,const_iterator,const_iterator);
 iterator yaooc_array_container_erase(pointer,const_iterator);
 iterator yaooc_array_container_erase_range(pointer,const_iterator,const_iterator);
 size_t yaooc_array_container_erase_value(pointer,const_pointer);
 iterator yaooc_array_container_at(const_pointer,size_t);
 void yaooc_array_container_shrink_to_fit(pointer);
 void yaooc_array_container_reserve(pointer,size_t);
 void yaooc_array_container_resize(pointer,size_t);
 void yaooc_array_container_resize_value(pointer,size_t,const_pointer);
 void yaooc_array_container_clear(pointer);
#define YAOOC_ARRAY_CONTAINER_INITIAL_CAPACITY 16

#define FOR_EACH(ITER,ARRAY) for(ITER=M(ARRAY,begin);ITER!=M(ARRAY,end);ITER++)
#define CFOR_EACH(ITER,ARRAY) for(ITER=M(ARRAY,cbegin);ITER!=M(ARRAY,cend);ITER++)

#define TYPE_INFO(p) (((yaooc_array_container_const_pointer)p)->type_info_)
#define TYPE_SIZE(p) (yaooc_sizeof(TYPE_INFO(p)))
#define SIZE(p)  (((yaooc_array_container_const_pointer)p)->size_)
#define CAPACITY(p)  (((yaooc_array_container_const_pointer)p)->capacity_)
#define BEGIN(p) (((yaooc_array_container_pointer)p)->array_)
#define AT(p,i) (BEGIN(p)+((i)*TYPE_SIZE(p)))
#define END(p)  AT(p,SIZE(p))
#define INDEX(p,pos) (((yaooc_private_const_iterator)(pos)-BEGIN(p))/TYPE_SIZE(p))



#endif
