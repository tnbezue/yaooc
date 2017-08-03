#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <yaooc/ordered_container.h>

yaooc_ordered_container_find_result_t yaooc_ordered_container_find_private(const_pointer p,const_pointer value)
{
	yaooc_ordered_container_const_pointer this=p;
	yaooc_ordered_container_find_result_t fr;
	fr.found_=false;
//	fr.position_=(iterator)yaooc_ordered_container_cend(p);
	size_t element_size=this->type_info_->type_size_;
	size_t lower=0;
	size_t upper=this->size_-1;
	size_t middle,position=0;
//	lt_compare lt_function=get_lt_cmp(this->type_info_);
	while(lower <= upper && upper != -1) {
		middle=(lower+upper)>>1;
		void* middle_ptr=this->array_+element_size*middle;
		debug(DEBUG_CONTAINER) {
			printf("lower: %zu middle: %zu upper: %zu %p\n",lower,middle,upper,middle_ptr);
			fflush(stdout);
		}
		if(op_lt_static(middle_ptr,value,this->type_info_)) {
			lower=middle+1;
			position=lower;
		} else if(op_lt_static(value,middle_ptr,this->type_info_)) {
			upper=middle-1;
			position=middle;
		} else {
			fr.found_=true;
			/*
				Make sure first value in container returned
			*/
			while(middle > 0) {
        middle--;
				middle_ptr=this->array_+element_size*middle;
				if(op_lt_static(middle_ptr,value,this->type_info_)) {
          middle++;
					break;
        }
			}
			position=middle;
			break;
		}
	}
	fr.position_=(iterator)yaooc_ordered_container_at((pointer)p,position);
	return fr;
}

iterator yaooc_ordered_container_find(const_pointer p,const_pointer value)
{
	yaooc_ordered_container_find_result_t fr=yaooc_ordered_container_find_private(p,value);
	return fr.found_ ? fr.position_ : (iterator)CEND(p);
}

/*
const_iterator yaooc_ordered_container_cfind(const_pointer p,const_pointer value)
{
	yaooc_ordered_container_find_result_t fr=yaooc_ordered_container_find_private(p,value);
	return fr.found_ ? fr.position_ : CEND(p);
}
*/
iterator yaooc_ordered_container_insert_n(pointer p,const_iterator pos,size_t n,const_pointer value)
{
	/*
		Note: argument pos should be begin <= pos <= end.  However, this may not be the position where value is inserted
	*/
	yaooc_ordered_container_pointer this=p;
	yaooc_private_const_iterator cbegin=CBEGIN(p);
	assert(cbegin <= (yaooc_private_const_iterator)(pos) && (yaooc_private_const_iterator)(pos) <= (yaooc_private_const_iterator)CEND(p) && "Insert position out of range");
	/*
		Do find after increase capacity because increase capacity (realloc) may move data array
	*/
	yaooc_ordered_container_increase_capacity(p,n);
	yaooc_ordered_container_find_result_t fr=yaooc_ordered_container_find_private(p,value);
	yaooc_container_insert_n_private(this,INDEX(this,fr.position_),n,value);
	return fr.position_;
}

iterator yaooc_ordered_container_insert(pointer p,const_iterator pos,const_pointer value)
{
	return yaooc_ordered_container_insert_n(p,pos,1,value);
}

iterator yaooc_ordered_container_insert_range(pointer p,const_iterator pos,const_iterator f,const_iterator l)
{
	yaooc_ordered_container_pointer this=p;
	yaooc_private_iterator ptr=(yaooc_private_iterator)pos;
	assert((yaooc_private_const_iterator)yaooc_ordered_container_begin(this) <= ptr && ptr <= (yaooc_private_const_iterator)yaooc_ordered_container_end(this) && "Insert position out of range");
	yaooc_private_const_iterator first=f;
	yaooc_private_const_iterator last=l;
	assert(first <= last && "First > last for insert");
//	size_t ofs=ptr-(yaooc_private_const_iterator)yaooc_ordered_container_begin(this);
	size_t element_size=this->type_info_->type_size_;
	size_t n=(last-first)/element_size;
	yaooc_ordered_container_increase_capacity(this,n);
//	ptr=(yaooc_private_iterator)yaooc_ordered_container_begin(this)+ofs;
	iterator rpos=NULL;
	for(;first!=last;first+=element_size) {
		yaooc_ordered_container_find_result_t fr=yaooc_ordered_container_find_private(p,first);
		memmove(fr.position_+element_size,fr.position_,END(this)-fr.position_);
		real_newp_array_copy_static(fr.position_,this->type_info_,first,1);
		this->size_++;
	}
	return rpos;
}

void yaooc_ordered_container_resize(pointer p,size_t n,const_pointer value)
{
	yaooc_ordered_container_pointer this=p;
	if(n>this->size_) {
		yaooc_ordered_container_insert_n(p,yaooc_ordered_container_end(this),n-this->size_,value);
	} else {
		yaooc_ordered_container_erase_range(this,(yaooc_private_iterator)yaooc_ordered_container_begin(this)+n*this->type_info_->type_size_,yaooc_ordered_container_end(this));
	}
}

size_t yaooc_ordered_container_erase_value(pointer p,const_pointer value)
{
	yaooc_ordered_container_pointer this=p;
	size_t n_erased=0;
	yaooc_ordered_container_find_result_t fr=yaooc_ordered_container_find_private(this,value);
	if(fr.found_) {
		size_t j,i=INDEX(this,fr.position_);
		n_erased=1;
		for(j=i+1;j<this->size_;j++) {
			if(op_ne_static(AT(this,j),value,this->type_info_))
				break;
			n_erased++;
		}
		yaooc_container_erase_range(this,AT(this,i),AT(this,i+n_erased));
	}
	return n_erased;
}

ISA_IMPLEMENTATION(yaooc_ordered_container,yaooc_container)

DEFINE_TYPE_INFO(yaooc_ordered_container,NULL,NULL,NULL,NULL,NULL,
        NULL,yaooc_container)
