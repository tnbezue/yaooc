#ifndef __YAOOC_CONTAINER_INCLUDED__
#define __YAOOC_CONTAINER_INCLUDED__

#include <yaooc/object.h>

/*
  Container "private" methods
*/
typedef struct container_private_class_methods_s container_private_class_methods_t;
struct container_private_class_methods_s
{
  size_t (*size_needed)(const_pointer,size_t);
  bool (*increase_capacity)(pointer,size_t);
};
/*
  CPM (Container Private Method) calls a container private method
*/
#define CPM(ptr,method,...) ((container_private_class_methods_t*)(ptr)->private_class_table_)->method(ptr,##__VA_ARGS__)

bool yaooc_container_increase_capacity(pointer,size_t);
size_t yaooc_container_size_needed(const_pointer,size_t);
/*
	Class methods exposed by base container.  Base container does not expose begin, cbegin, end, and cend
  because they should return an interator that is specific to the type stored in container -- not the generic
  iterator (void *)
*/
class_table(yaooc_container)
{
  yaooc_object_class_members_t;
  bool (*empty)(const_pointer);
  size_t (*size)(const_pointer);
  size_t (*capacity)(const_pointer);
  void (*reserve)(pointer,size_t);
  void (*clear)(pointer);
};

class_instance(yaooc_container)
{
  void* private_class_table_; /* Private class table for container */
	char* array_; /* container */
	const type_info_t* type_info_;
	size_t	capacity_;
	size_t size_;
};

class(yaooc_container);

const char* yaooc_container_isa(const_pointer);
bool yaooc_container_is_descendent(const_pointer,const char*);
void yaooc_container_swap(pointer,pointer);
ISA_DEFINITION(yaooc_container,yaooc_object)

#define YAOOC_CONTAINER_NEW_METHODS \
  yaooc_container_empty, \
  yaooc_container_size, \
  yaooc_container_capacity, \
  yaooc_container_reserve, \
  yaooc_container_clear

#define YAOOC_CONTAINER_CLASS_MEMBERS \
  { \
    yaooc_container_isa, \
    yaooc_container_is_descendent, \
    yaooc_container_swap \
  }, \
  YAOOC_CONTAINER_NEW_METHODS

// Container contructors
// args: 1- const type_info_t*
void yaooc_container_ctor(pointer p,va_list args);

void yaooc_container_resize(pointer,size_t,const_pointer);
void yaooc_container_reserve(pointer,size_t);
void yaooc_container_clear(pointer); // remove all elements from array
void yaooc_container_shrink_to_fit(pointer p); // shrink array capcity
iterator yaooc_container_at(pointer,size_t pos); // returns pointer to element at pos
//const_iterator yaooc_container_cat(const_pointer,size_t pos); // returns pointer to element at pos
size_t yaooc_container_size(const_pointer); // return size
size_t yaooc_container_capacity(const_pointer); // return size
bool yaooc_container_empty(const_pointer); // indicates if array is empty
iterator yaooc_container_begin(pointer);
iterator yaooc_container_end(pointer);
const type_info_t* yaooc_container_get_type_info(const_pointer p);

iterator yaooc_container_insert(pointer,const_iterator,const_pointer); //,size_t n);  // insert n elements starting a pos
iterator yaooc_container_insert_range(pointer,const_iterator,const_iterator,const_iterator);
iterator yaooc_container_insert_n(pointer,const_iterator,size_t,const_pointer);
iterator yaooc_container_erase(pointer,iterator);  // erase n elements starting at pos
iterator yaooc_container_erase_range(pointer,iterator,iterator);  // erase n elements starting at pos
size_t yaooc_container_erase_value(pointer,const_pointer);
iterator yaooc_container_find(const_pointer p,const_pointer value);

void yaooc_container_default_ctor(pointer);
void yaooc_container_dtor(pointer);
void yaooc_container_copy_ctor(pointer,const_pointer);
void yaooc_container_assign(pointer,const_pointer);

void yaooc_container_insert_range_private(pointer p,size_t index,const_iterator f,const_iterator l);
void yaooc_container_erase_range_private(pointer p,iterator f,iterator l);
/*
	Some useful macros
*/
#define AT(ptr,index) (((yaooc_container_pointer)ptr)->array_+(index)*((yaooc_container_pointer)ptr)->type_info_->type_size_)
#define BEGIN(ptr) (((yaooc_container_pointer)ptr)->array_)
#define END(ptr) (((yaooc_container_pointer)ptr)->array_+((yaooc_container_pointer)ptr)->size_*((yaooc_container_pointer)ptr)->type_info_->type_size_)
#define CBEGIN(ptr) ((yaooc_private_const_iterator)((yaooc_container_pointer)ptr)->array_)
#define CEND(ptr) ((yaooc_private_const_iterator)(((yaooc_container_pointer)ptr)->array_+((yaooc_container_pointer)ptr)->size_*((yaooc_container_pointer)ptr)->type_info_->type_size_))
#define I_AT(ptr,index) ((ptr)->array_+((ptr)->index_[index])*(ptr)->type_info_->type_size_)
#define INDEX(ptr,pos) (((char*)pos - BEGIN(ptr))/(ptr)->type_info_->type_size_)
#define BYTE_DIFF(ptr,i,j) (((j)-(i))*(ptr)->type_info_->type_size_)
#define BYTES_TO_END(ptr,i) BYTE_DIFF(ptr,i,(ptr)->size_)
void yaooc_container_insert_n_private(pointer p,size_t index,size_t n,const_pointer value);

#define CONTAINER_INSERT_SPACE(pthis,pos,n) { \
	memmove(pthis->array_+(pos+n)*pthis->type_info_->type_size_, \
	pthis->array_+(pos)*pthis->type_info_->type_size_, \
	(pthis->size_-pos)*pthis->type_info_->type_size_); \
}

#define	CONTAINER_DELETE_SPACE(pthis,pos,n) { \
	memmove(pthis->array_*(pos)*pthis->type_info_->type_size_, \
		pthis->array_+(pos+n)*pthis->type_info_->type_size_, \
		_nn_*pthis->type_info_->type_size_); \
}

/*
	Pointer is between begin and end
*/
#define WITHIN_BOUNDS(p,ptr,err_msg) \
	assert((yaooc_private_iterator)yaooc_container_begin(p) <= (yaooc_private_iterator)ptr \
			&& (yaooc_private_iterator)ptr <= (yaooc_private_iterator)yaooc_container_end(p) \
			&& err_msg)

/*
	Ensure first < last
*/
#define PROPER_RANGE(f,l,err_msg) \
	assert((yaooc_private_iterator)f <= (yaooc_private_iterator)l && err_msg)

/*
	Ensure first and last within bounds.
*/
#define FIRST_LAST_WITHIN_BOUNDS(p,f,l,err_msg) \
	assert((yaooc_private_iterator)yaooc_container_begin(p) <= (yaooc_private_iterator)f \
			&& (yaooc_private_iterator)l <= (yaooc_private_iterator)yaooc_container_end(p) \
			&& err_msg)


#define FOR_EACH(ITER,CONT) for(ITER=M(CONT,begin);ITER!=M(CONT,end);ITER++)
#define CFOR_EACH(ITER,CONT) for(ITER=M(CONT,cbegin);ITER!=M(CONT,cend);ITER++)

#endif
