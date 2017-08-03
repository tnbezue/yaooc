#include <assert.h>
#include <string.h>
#include <yaooc/unique_index_container.h>

//void yaooc_insert_index(yaooc_unique_index_container_pointer this,size_t,size_t,size_t,size_t);

iterator yaooc_unique_index_container_insert_n(pointer p,const_iterator pos,size_t n,const_pointer value)
{
  // For unique container, only one value can be inserted
  n=1;
	yaooc_unique_index_container_pointer this=p;
	yaooc_private_const_iterator ipos=pos;
	assert(CBEGIN(this) <= ipos && ipos <= CEND(this) && "Container insert position out of range");
	yaooc_index_container_find_result_t fr=yaooc_index_container_private_find(p,value);
  if(!fr.found_) {
    size_t index=(ipos-(char*)BEGIN(this))/this->type_info_->type_size_;
    yaooc_index_container_increase_capacity(this,1);
    ipos=(char*)BEGIN(this) + index*this->type_info_->type_size_;
    yaooc_insert_index(this,fr.index_,1,this->size_,index);
    yaooc_container_insert_n(this,ipos,n,value);
  } else {
    ipos=(char*)BEGIN(this) + fr.index_*this->type_info_->type_size_;
  }
	return (pointer)ipos;
}

iterator yaooc_unique_index_container_insert(pointer p,const_iterator pos,const_pointer value)
{
	return yaooc_unique_index_container_insert_n(p,pos,1,value);
}

iterator yaooc_unique_index_container_insert_range(pointer p,const_iterator pos,const_iterator f,const_iterator l)
{
	yaooc_unique_index_container_pointer this=p;
	yaooc_private_const_iterator first=f;
	yaooc_private_const_iterator last=l;
	yaooc_private_const_iterator ipos=pos;
	assert(first <= last && "First greater than last");
	assert(CBEGIN(this) <= ipos && ipos <= CEND(this) && "Container insert position out of range");
	size_t index=(ipos-this->array_)/this->type_info_->type_size_;
	size_t n = (last - first)/this->type_info_->type_size_;
	yaooc_index_container_increase_capacity(this,n);
	ipos=(char*)BEGIN(this) + index*this->type_info_->type_size_;
	iterator rpos=(iterator) ipos;
  size_t old_size=this->size_;
	for(;first!=last;first+=this->type_info_->type_size_) {
		yaooc_unique_index_container_insert_n(this,ipos,1,first);
    if(this->size_ != old_size) {
      old_size=this->size_;
      ipos+=this->type_info_->type_size_;
    }
	}
	return rpos;
}

void yaooc_unique_index_container_resize(pointer p,size_t new_size,const_pointer value)
{
  /*
    Don't allow unique index container to resize
  */
  assert(0 && "Unique index container not allowed to resize");
/*  yaooc_unique_index_container_pointer this=p;
	if(new_size > this->size_) {
		yaooc_unique_index_container_insert_n(this,yaooc_container_end(this),1,value);
	} else {
		yaooc_unique_index_container_erase_range(this,AT(this,new_size),AT(this,this->size_));
	}
*/
}

ISA_IMPLEMENTATION(yaooc_unique_index_container,yaooc_index_container)

DEFINE_TYPE_INFO(yaooc_unique_index_container,yaooc_container_default_ctor,
        NULL,NULL,NULL,NULL,NULL,yaooc_index_container)
