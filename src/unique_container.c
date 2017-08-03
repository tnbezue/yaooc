#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <yaooc/unique_container.h>

iterator yaooc_unique_container_insert_n(pointer p,const_iterator pos,size_t n,const_pointer value)
{
	yaooc_unique_container_pointer this=p;
	return yaooc_unique_container_insert_range(p,pos,value,value+this->type_info_->type_size_);
}

iterator yaooc_unique_container_insert(pointer p,const_iterator pos,const_pointer value)
{
	yaooc_unique_container_pointer this=p;
	return yaooc_unique_container_insert_range(p,pos,value,value+this->type_info_->type_size_);
}

iterator yaooc_unique_container_insert_range(pointer p,const_iterator pos,const_iterator f,const_iterator l)
{
	WITHIN_BOUNDS(p,pos,"Insert position out of range in yaooc_unique_container_insert_range");
	PROPER_RANGE(f,l,"First > last for insert in yaooc_unique_container_insert_range");
	yaooc_unique_container_pointer this=p;
	yaooc_private_const_iterator ptr=pos;
	yaooc_private_const_iterator first=f;
	yaooc_private_const_iterator last=l;
	size_t ofs=INDEX(this,ptr);
	size_t element_size=this->type_info_->type_size_;
	size_t n=(last-first)/element_size;
	yaooc_container_increase_capacity(this,n);
	size_t first_insert_pos=(size_t)-1;
	for(;first!=last;first+=element_size) {
		yaooc_private_iterator position = yaooc_unique_container_find(this,first);
		if(first_insert_pos==(size_t)-1)
			first_insert_pos=position-this->array_;
		if(position == yaooc_unique_container_end(this)) {
			yaooc_container_insert_n_private(this,ofs++,1,first);
		}
	}
	if(first_insert_pos==(size_t)-1)
		first_insert_pos=this->size_;
	return AT(this,first_insert_pos);
}

void yaooc_container_erase_range_private(pointer p,iterator f,iterator l);
size_t yaooc_unique_container_erase_value(pointer p,const_pointer value)
{
	yaooc_unique_container_pointer this=p;
	size_t i,n_erased=0;
	for(i=0;i<this->size_;i++) {
		if(op_eq_static(AT(this,i),value,this->type_info_)) {
			/*
				Since this is a unique container, no other matches will be found
			*/
			yaooc_container_erase_range_private(this,AT(this,i),AT(this,i+1));
			n_erased=1;
			break;
		}
	}
	return n_erased;
}

void yaooc_unique_container_resize(pointer p,size_t new_size,const_pointer value)
{
//	size_t n;
	yaooc_container_pointer this=p;
//	const type_info_t* ti=this->type_info_;
	if(new_size > this->size_) {
		yaooc_unique_container_insert_n(this,yaooc_container_end(p),1,value);
	} else {
		yaooc_container_erase_range(this,AT(this,new_size),yaooc_container_end(p));
	}
}

ISA_IMPLEMENTATION(yaooc_unique_container,yaooc_container)

DEFINE_TYPE_INFO(yaooc_unique_container,NULL,NULL,NULL,NULL,NULL,
        NULL,yaooc_container)

