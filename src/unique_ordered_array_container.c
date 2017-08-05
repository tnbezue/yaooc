#include <string.h>
#include <stdio.h>
#include <yaooc/unique_ordered_array_container.h>
#ifdef __YAOOC_BOUNDS_CHECKING__
#include <assert.h>
#endif

#define SIZE(ptr,pos) (((ptr)->size_-(pos))*(ptr)->type_info_->type_size_)

iterator yaooc_unique_ordered_array_container_insert(pointer p,const_iterator pos,const_pointer value)
{
	yaooc_unique_ordered_array_container_pointer this=p;
	return yaooc_unique_ordered_array_container_insert_range(p,pos,value,((yaooc_private_const_iterator)value)+this->type_info_->type_size_);
}

iterator yaooc_unique_ordered_array_container_insert_range(pointer p,const_iterator pos,const_iterator f,const_iterator l)
{
	yaooc_unique_ordered_array_container_pointer this=p;
#ifdef __YAOOC_BOUNDS_CHECKING__
	yaooc_private_iterator ptr=(yaooc_private_iterator)pos;
	assert((yaooc_private_const_iterator)yaooc_unique_ordered_array_container_begin(this) <= ptr && ptr <= (yaooc_private_const_iterator)yaooc_unique_ordered_array_container_end(this) && "Insert position out of range");
#endif
	yaooc_private_const_iterator first=f;
	yaooc_private_const_iterator last=l;
#ifdef __YAOOC_BOUNDS_CHECKING__
	assert(first <= last && "First > last for insert");
#endif
//	yaooc_size_type ofs=ptr-(yaooc_private_const_iterator)yaooc_unique_ordered_array_container_begin(this);
	yaooc_size_type element_size=this->type_info_->type_size_;
	yaooc_size_type n=(last-first)/element_size;
	yaooc_unique_ordered_array_container_increase_capacity(this,n);
//	ptr=(yaooc_private_iterator)yaooc_unique_ordered_array_container_begin(this)+ofs;
	iterator rpos=NULL;
	for(;first!=last;first+=element_size) {
		yaooc_unique_ordered_array_container_find_result_t fr=yaooc_unique_ordered_array_container_find_private(p,first);
		if(!fr.found_) {
			yaooc_array_container_insert_n_private(this,INDEX(this,fr.position_),1,first);
		}
	}
	return rpos;
}

iterator yaooc_unique_ordered_array_container_resize(pointer p,const_iterator pos,const_pointer v)
{
  return yaooc_unique_ordered_array_container_insert(p,yaooc_unique_ordered_array_container_end(p),v);
}

iterator yaooc_unique_ordered_array_container_insert_n(pointer p,const_iterator pos,yaooc_size_type size,const_pointer value)
{
  return yaooc_unique_ordered_array_container_insert(p,pos,value);
}

ISA_IMPLEMENTATION(yaooc_unique_ordered_array_container,yaooc_ordered_array_container)

DEFINE_TYPE_INFO(yaooc_unique_ordered_array_container,NULL,NULL,NULL,NULL,NULL,NULL,yaooc_ordered_array_container)
