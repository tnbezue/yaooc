#include <string.h>
#include <yaooc/unique_index_array_container.h>
#ifdef __YAOOC_BOUNDS_CHECKING__
#include <assert.h>
#endif

//void yaooc_insert_index(yaooc_unique_index_array_container_pointer this,yaooc_size_type,yaooc_size_type,yaooc_size_type,yaooc_size_type);

iterator yaooc_unique_index_array_container_insert_n(pointer p,const_iterator pos,yaooc_size_type n,const_pointer value)
{
  // For unique container, only one value can be inserted
  n=1;
	yaooc_unique_index_array_container_pointer this=p;
	yaooc_private_const_iterator ipos=pos;
#ifdef __YAOOC_BOUNDS_CHECKING__
	assert(CBEGIN(this) <= ipos && ipos <= CEND(this) && "Container insert position out of range");
#endif
	yaooc_index_array_container_find_result_t fr=yaooc_index_array_container_private_find(p,value);
  if(!fr.found_) {
    yaooc_size_type index=(ipos-(char*)BEGIN(this))/this->type_info_->type_size_;
    yaooc_index_array_container_increase_capacity(this,1);
    ipos=(char*)BEGIN(this) + index*this->type_info_->type_size_;
    yaooc_insert_index(this,fr.index_,1,this->size_,index);
    yaooc_array_container_insert_n(this,ipos,n,value);
  } else {
    ipos=(char*)BEGIN(this) + fr.index_*this->type_info_->type_size_;
  }
	return (pointer)ipos;
}

iterator yaooc_unique_index_array_container_insert(pointer p,const_iterator pos,const_pointer value)
{
	return yaooc_unique_index_array_container_insert_n(p,pos,1,value);
}

iterator yaooc_unique_index_array_container_insert_range(pointer p,const_iterator pos,const_iterator f,const_iterator l)
{
	yaooc_unique_index_array_container_pointer this=p;
	yaooc_private_const_iterator first=f;
	yaooc_private_const_iterator last=l;
	yaooc_private_const_iterator ipos=pos;
#ifdef __YAOOC_BOUNDS_CHECKING__
	assert(first <= last && "First greater than last");
	assert(CBEGIN(this) <= ipos && ipos <= CEND(this) && "Container insert position out of range");
#endif
	yaooc_size_type index=(ipos-this->array_)/this->type_info_->type_size_;
	yaooc_size_type n = (last - first)/this->type_info_->type_size_;
	yaooc_index_array_container_increase_capacity(this,n);
	ipos=(char*)BEGIN(this) + index*this->type_info_->type_size_;
	iterator rpos=(iterator) ipos;
  yaooc_size_type old_size=this->size_;
	for(;first!=last;first+=this->type_info_->type_size_) {
		yaooc_unique_index_array_container_insert_n(this,ipos,1,first);
    if(this->size_ != old_size) {
      old_size=this->size_;
      ipos+=this->type_info_->type_size_;
    }
	}
	return rpos;
}

void yaooc_unique_index_array_container_resize(pointer p,yaooc_size_type new_size,const_pointer value)
{
  /*
    Don't allow unique index container to resize
  */
#ifdef __YAOOC_BOUNDS_CHECKING__
  assert(0 && "Unique index container not allowed to resize");
#endif
/*  yaooc_unique_index_array_container_pointer this=p;
	if(new_size > this->size_) {
		yaooc_unique_index_array_container_insert_n(this,yaooc_array_container_end(this),1,value);
	} else {
		yaooc_unique_index_array_container_erase_range(this,AT(this,new_size),AT(this,this->size_));
	}
*/
}

ISA_IMPLEMENTATION(yaooc_unique_index_array_container,yaooc_index_array_container)

DEFINE_TYPE_INFO(yaooc_unique_index_array_container,yaooc_array_container_default_ctor,
        NULL,NULL,NULL,NULL,NULL,yaooc_index_array_container)
