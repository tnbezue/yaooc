#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <yaooc/unique_array_container.h>

iterator yaooc_unique_array_container_insert_n(pointer p,const_iterator pos,yaooc_size_type n,const_pointer value)
{
	yaooc_unique_array_container_pointer this=p;
	return yaooc_unique_array_container_insert_range(p,pos,value,value+this->type_info_->type_size_);
}

iterator yaooc_unique_array_container_insert(pointer p,const_iterator pos,const_pointer value)
{
	yaooc_unique_array_container_pointer this=p;
	return yaooc_unique_array_container_insert_range(p,pos,value,value+this->type_info_->type_size_);
}

iterator yaooc_unique_array_container_insert_range(pointer p,const_iterator pos,const_iterator f,const_iterator l)
{
	WITHIN_BOUNDS(p,pos,"Insert position out of range in yaooc_unique_array_container_insert_range");
	PROPER_RANGE(f,l,"First > last for insert in yaooc_unique_array_container_insert_range");
	yaooc_unique_array_container_pointer this=p;
	yaooc_private_const_iterator ptr=pos;
	yaooc_private_const_iterator first=f;
	yaooc_private_const_iterator last=l;
	yaooc_size_type ofs=INDEX(this,ptr);
	yaooc_size_type element_size=this->type_info_->type_size_;
	yaooc_size_type n=(last-first)/element_size;
	yaooc_array_container_increase_capacity(this,n);
	yaooc_size_type first_insert_pos=(yaooc_size_type)-1;
	for(;first!=last;first+=element_size) {
		yaooc_private_iterator position = yaooc_unique_array_container_find(this,first);
		if(first_insert_pos==(yaooc_size_type)-1)
			first_insert_pos=position-this->array_;
		if(position == yaooc_unique_array_container_end(this)) {
			yaooc_array_container_insert_n_private(this,ofs++,1,first);
		}
	}
	if(first_insert_pos==(yaooc_size_type)-1)
		first_insert_pos=this->size_;
	return AT(this,first_insert_pos);
}

void yaooc_array_container_erase_range_private(pointer p,iterator f,iterator l);
yaooc_size_type yaooc_unique_array_container_erase_value(pointer p,const_pointer value)
{
	yaooc_unique_array_container_pointer this=p;
	yaooc_size_type i,n_erased=0;
	for(i=0;i<this->size_;i++) {
		if(op_eq_static(AT(this,i),value,this->type_info_)) {
			/*
				Since this is a unique container, no other matches will be found
			*/
			yaooc_array_container_erase_range_private(this,AT(this,i),AT(this,i+1));
			n_erased=1;
			break;
		}
	}
	return n_erased;
}

void yaooc_unique_array_container_resize(pointer p,yaooc_size_type new_size,const_pointer value)
{
//	yaooc_size_type n;
	yaooc_array_container_pointer this=p;
//	const type_info_t* ti=this->type_info_;
	if(new_size > this->size_) {
		yaooc_unique_array_container_insert_n(this,yaooc_array_container_end(p),1,value);
	} else {
		yaooc_array_container_erase_range(this,AT(this,new_size),yaooc_array_container_end(p));
	}
}

ISA_IMPLEMENTATION(yaooc_unique_array_container,yaooc_array_container)

DEFINE_TYPE_INFO(yaooc_unique_array_container,NULL,NULL,NULL,NULL,NULL,
        NULL,yaooc_array_container)

