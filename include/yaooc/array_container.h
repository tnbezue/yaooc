#ifndef __yaooc_array_container_INCLUDED__
#define __yaooc_array_container_INCLUDED__

#include <yaooc/object.h>

struct container_private_class_methods_s;
typedef struct container_private_class_methods_s container_private_class_methods_t;

bool yaooc_array_container_increase_capacity(pointer,yaooc_size_type);
yaooc_size_type yaooc_array_container_size_needed(const_pointer,yaooc_size_type);
/*
	Class methods exposed by base container.  Base container does not expose begin, cbegin, end, and cend
  because they should return an interator that is specific to the type stored in container -- not the generic
  iterator (void *)
*/
class_table(yaooc_array_container)
{
  yaooc_object_class_members_t;
  bool (*empty)(const_pointer);
  yaooc_size_type (*size)(const_pointer);
  yaooc_size_type (*capacity)(const_pointer);
  void (*reserve)(pointer,yaooc_size_type);
  void (*clear)(pointer);
};

class_instance(yaooc_array_container)
{
  container_private_class_methods_t* private_class_table_; /* Private class table for container */
	char* array_;
	const type_info_t* type_info_;
	yaooc_size_type	capacity_;
	yaooc_size_type size_;
};

class(yaooc_array_container);

const char* yaooc_array_container_isa(const_pointer);
bool yaooc_array_container_is_descendent(const_pointer,const char*);
void yaooc_array_container_swap(pointer,pointer);
ISA_DEFINITION(yaooc_array_container,yaooc_object)

#define YAOOC_ARRAY_CONTAINER_NEW_METHODS \
  yaooc_array_container_empty, \
  yaooc_array_container_size, \
  yaooc_array_container_capacity, \
  yaooc_array_container_reserve, \
  yaooc_array_container_clear

#define YAOOC_ARRAY_CONTAINER_CLASS_MEMBERS \
  { \
    yaooc_array_container_isa, \
    yaooc_array_container_is_descendent, \
    yaooc_array_container_swap \
  }, \
  YAOOC_ARRAY_CONTAINER_NEW_METHODS

// Container contructors
// args: 1- const type_info_t*
void yaooc_array_container_ctor(pointer p,va_list args);

void yaooc_array_container_resize(pointer,yaooc_size_type,const_pointer);
void yaooc_array_container_reserve(pointer,yaooc_size_type);
void yaooc_array_container_clear(pointer); // remove all elements from array
void yaooc_array_container_shrink_to_fit(pointer p); // shrink array capcity
iterator yaooc_array_container_at(pointer,yaooc_size_type pos); // returns pointer to element at pos
//const_iterator yaooc_array_container_cat(const_pointer,size_t pos); // returns pointer to element at pos
yaooc_size_type yaooc_array_container_size(const_pointer); // return size
yaooc_size_type yaooc_array_container_capacity(const_pointer); // return size
bool yaooc_array_container_empty(const_pointer); // indicates if array is empty
iterator yaooc_array_container_begin(pointer);
iterator yaooc_array_container_end(pointer);
const type_info_t* yaooc_array_container_get_type_info(const_pointer p);

iterator yaooc_array_container_insert(pointer,const_iterator,const_pointer); //,yaooc_size_type n);  // insert n elements starting a pos
iterator yaooc_array_container_insert_range(pointer,const_iterator,const_iterator,const_iterator);
iterator yaooc_array_container_insert_n(pointer,const_iterator,yaooc_size_type,const_pointer);
iterator yaooc_array_container_erase(pointer,iterator);  // erase n elements starting at pos
iterator yaooc_array_container_erase_range(pointer,iterator,iterator);  // erase n elements starting at pos
yaooc_size_type yaooc_array_container_erase_value(pointer,const_pointer);
iterator yaooc_array_container_find(const_pointer p,const_pointer value);

void yaooc_array_container_default_ctor(pointer);
void yaooc_array_container_dtor(pointer);
void yaooc_array_container_copy_ctor(pointer,const_pointer);
void yaooc_array_container_assign(pointer,const_pointer);

void yaooc_array_container_insert_range_private(pointer p,yaooc_size_type index,const_iterator f,const_iterator l);
void yaooc_array_container_erase_range_private(pointer p,iterator f,iterator l);
/*
	Some useful macros
*/
#define AT(ptr,index) (((yaooc_array_container_pointer)ptr)->array_+(index)*((yaooc_array_container_pointer)ptr)->type_info_->type_size_)
#define BEGIN(ptr) (((yaooc_array_container_pointer)ptr)->array_)
#define END(ptr) (((yaooc_array_container_pointer)ptr)->array_+((yaooc_array_container_pointer)ptr)->size_*((yaooc_array_container_pointer)ptr)->type_info_->type_size_)
#define CBEGIN(ptr) ((yaooc_private_const_iterator)((yaooc_array_container_pointer)ptr)->array_)
#define CEND(ptr) ((yaooc_private_const_iterator)(((yaooc_array_container_pointer)ptr)->array_+((yaooc_array_container_pointer)ptr)->size_*((yaooc_array_container_pointer)ptr)->type_info_->type_size_))
#define I_AT(ptr,index) ((ptr)->array_+((ptr)->index_[index])*(ptr)->type_info_->type_size_)
#define INDEX(ptr,pos) (((char*)pos - BEGIN(ptr))/(ptr)->type_info_->type_size_)
#define BYTE_DIFF(ptr,i,j) (((j)-(i))*(ptr)->type_info_->type_size_)
#define BYTES_TO_END(ptr,i) BYTE_DIFF(ptr,i,(ptr)->size_)
void yaooc_array_container_insert_n_private(pointer p,yaooc_size_type index,yaooc_size_type n,const_pointer value);

#define CONTAINER_INSERT_SPACE(pthis,pos,n) { \
	memmove(pthis->array_+(pos+n)*pthis->type_info_->type_size_, \
	pthis->array_+(pos)*pthis->type_info_->type_size_, \
	(pthis->size_-pos)*pthis->type_info_->type_size_); \
}

#define	CONTAINER_DELETE_SPACE(pthis,pos,n) { \
	memmove(pthis->array_*(pos)*pthis->type_info_->type_size_, \
		pthis->array_+(pos+n)*pthis->type_info_->type_size_, \
		(pthis->size_-(pos+n))*pthis->type_info_->type_size_); \
}

/*
	Pointer is between begin and end
*/
#define WITHIN_BOUNDS(p,ptr,err_msg) \
	assert((yaooc_private_iterator)yaooc_array_container_begin(p) <= (yaooc_private_iterator)ptr \
			&& (yaooc_private_iterator)ptr <= (yaooc_private_iterator)yaooc_array_container_end(p) \
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
	assert((yaooc_private_iterator)yaooc_array_container_begin(p) <= (yaooc_private_iterator)f \
			&& (yaooc_private_iterator)l <= (yaooc_private_iterator)yaooc_array_container_end(p) \
			&& err_msg)


#define FOR_EACH(ITER,CONT) for(ITER=M(CONT,begin);ITER!=M(CONT,end);ITER++)
#define CFOR_EACH(ITER,CONT) for(ITER=M(CONT,cbegin);ITER!=M(CONT,cend);ITER++)


/*
 * Private (so don't look below this line) container methods
 */

typedef struct container_private_class_methods_s container_private_class_methods_t;
struct container_private_class_methods_s
{
  yaooc_size_type (*size_needed)(const_pointer,yaooc_size_type);
  bool (*increase_capacity)(pointer,yaooc_size_type);
};
#define CPM(ptr,method,...) ((container_private_class_methods_t*)(ptr)->private_class_table_)->method(ptr,##__VA_ARGS__)
#define POS(ptr,pos)   (pos)*((ptr)->type_info_->type_size_)
#define MIDDLE(ptr,n)  (n)*((ptr)->type_info_->type_size_)
#define BACK(ptr,pos,n) (((ptr)->size_)-((pos)+(n)))*((ptr)->type_info_->type_size_)

/* void yaooc_index_container_print_indexes(pointer p,FILE*); */

#endif
