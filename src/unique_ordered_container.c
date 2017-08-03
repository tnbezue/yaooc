#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <yaooc/unique_ordered_container.h>

#define SIZE(ptr,pos) (((ptr)->size_-(pos))*(ptr)->type_info_->type_size_)

iterator yaooc_unique_ordered_container_insert(pointer p,const_iterator pos,const_pointer value)
{
	yaooc_unique_ordered_container_pointer this=p;
	return yaooc_unique_ordered_container_insert_range(p,pos,value,((yaooc_private_const_iterator)value)+this->type_info_->type_size_);
}

iterator yaooc_unique_ordered_container_insert_range(pointer p,const_iterator pos,const_iterator f,const_iterator l)
{
	yaooc_unique_ordered_container_pointer this=p;
	yaooc_private_iterator ptr=(yaooc_private_iterator)pos;
	assert((yaooc_private_const_iterator)yaooc_unique_ordered_container_begin(this) <= ptr && ptr <= (yaooc_private_const_iterator)yaooc_unique_ordered_container_end(this) && "Insert position out of range");
	yaooc_private_const_iterator first=f;
	yaooc_private_const_iterator last=l;
	assert(first <= last && "First > last for insert");
//	size_t ofs=ptr-(yaooc_private_const_iterator)yaooc_unique_ordered_container_begin(this);
	size_t element_size=this->type_info_->type_size_;
	size_t n=(last-first)/element_size;
	yaooc_unique_ordered_container_increase_capacity(this,n);
//	ptr=(yaooc_private_iterator)yaooc_unique_ordered_container_begin(this)+ofs;
	iterator rpos=NULL;
	for(;first!=last;first+=element_size) {
		yaooc_unique_ordered_container_find_result_t fr=yaooc_unique_ordered_container_find_private(p,first);
		if(!fr.found_) {
			yaooc_container_insert_n_private(this,INDEX(this,fr.position_),1,first);
		}
	}
	return rpos;
}

iterator yaooc_unique_ordered_container_resize(pointer p,const_iterator pos,const_pointer v)
{
  return yaooc_unique_ordered_container_insert(p,yaooc_unique_ordered_container_end(p),v);
}

iterator yaooc_unique_ordered_container_insert_n(pointer p,const_iterator pos,size_t size,const_pointer value)
{
  return yaooc_unique_ordered_container_insert(p,pos,value);
}

ISA_IMPLEMENTATION(yaooc_unique_ordered_container,yaooc_ordered_container)

DEFINE_TYPE_INFO(yaooc_unique_ordered_container,NULL,NULL,NULL,NULL,NULL,NULL,yaooc_ordered_container)
