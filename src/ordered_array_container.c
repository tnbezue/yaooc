#include <string.h>
#include <stdio.h>
#include <yaooc/ordered_array_container.h>
#ifdef __YAOOC_BOUNDS_CHECKING__
#include <assert.h>
#endif

yaooc_ordered_array_container_find_result_t yaooc_ordered_array_container_find_private(const_pointer p,const_pointer value)
{
	yaooc_ordered_array_container_const_pointer this=p;
	yaooc_ordered_array_container_find_result_t fr;
	fr.found_=false;
//	fr.position_=(iterator)yaooc_ordered_array_container_cend(p);
	yaooc_size_type element_size=this->type_info_->type_size_;
	yaooc_size_type lower=0;
	yaooc_size_type upper=this->size_-1;
	yaooc_size_type middle,position=0;
//	lt_compare lt_function=get_lt_cmp(this->type_info_);
	while(lower <= upper && upper != (yaooc_size_type)-1) {
		middle=(lower+upper)>>1;
		void* middle_ptr=this->array_+element_size*middle;
		debug(DEBUG_CONTAINER) {
			printf("lower: %d middle: %d upper: %d %p\n",lower,middle,upper,middle_ptr);
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
	fr.position_=(iterator)yaooc_ordered_array_container_at((pointer)p,position);
	return fr;
}

iterator yaooc_ordered_array_container_find(const_pointer p,const_pointer value)
{
	yaooc_ordered_array_container_find_result_t fr=yaooc_ordered_array_container_find_private(p,value);
	return fr.found_ ? fr.position_ : (iterator)CEND(p);
}

/*
const_iterator yaooc_ordered_array_container_cfind(const_pointer p,const_pointer value)
{
	yaooc_ordered_array_container_find_result_t fr=yaooc_ordered_array_container_find_private(p,value);
	return fr.found_ ? fr.position_ : CEND(p);
}
*/
iterator yaooc_ordered_array_container_insert_n(pointer p,const_iterator pos,yaooc_size_type n,const_pointer value)
{
	/*
		Note: argument pos should be begin <= pos <= end.  However, this may not be the position where value is inserted
	*/
	yaooc_ordered_array_container_pointer this=p;
#ifdef __YAOOC_BOUNDS_CHECKING__
	yaooc_private_const_iterator cbegin=CBEGIN(p);
	assert(cbegin <= (yaooc_private_const_iterator)(pos) && (yaooc_private_const_iterator)(pos) <= (yaooc_private_const_iterator)CEND(p) && "Insert position out of range");
#endif
	/*
		Do find after increase capacity because increase capacity (realloc) may move data array
	*/
	yaooc_ordered_array_container_increase_capacity(p,n);
	yaooc_ordered_array_container_find_result_t fr=yaooc_ordered_array_container_find_private(p,value);
	yaooc_array_container_insert_n_private(this,INDEX(this,fr.position_),n,value);
	return fr.position_;
}

iterator yaooc_ordered_array_container_insert(pointer p,const_iterator pos,const_pointer value)
{
	return yaooc_ordered_array_container_insert_n(p,pos,1,value);
}

iterator yaooc_ordered_array_container_insert_range(pointer p,const_iterator pos,const_iterator f,const_iterator l)
{
	yaooc_ordered_array_container_pointer this=p;
#ifdef __YAOOC_BOUNDS_CHECKING__
	yaooc_private_iterator ptr=(yaooc_private_iterator)pos;
  assert((yaooc_private_const_iterator)yaooc_ordered_array_container_begin(this) <= ptr && ptr <= (yaooc_private_const_iterator)yaooc_ordered_array_container_end(this) && "Insert position out of range");
#endif
	yaooc_private_const_iterator first=f;
	yaooc_private_const_iterator last=l;
#ifdef __YAOOC_BOUNDS_CHECKING__
	assert(first <= last && "First > last for insert");
#endif
//	yaooc_size_type ofs=ptr-(yaooc_private_const_iterator)yaooc_ordered_array_container_begin(this);
	yaooc_size_type element_size=this->type_info_->type_size_;
	yaooc_size_type n=(last-first)/element_size;
	yaooc_ordered_array_container_increase_capacity(this,n);
//	ptr=(yaooc_private_iterator)yaooc_ordered_array_container_begin(this)+ofs;
	iterator rpos=NULL;
	for(;first!=last;first+=element_size) {
		yaooc_ordered_array_container_find_result_t fr=yaooc_ordered_array_container_find_private(p,first);
		memmove(fr.position_+element_size,fr.position_,END(this)-fr.position_);
		real_newp_array_copy_static(fr.position_,this->type_info_,first,1);
		this->size_++;
	}
	return rpos;
}

void yaooc_ordered_array_container_resize(pointer p,yaooc_size_type n,const_pointer value)
{
	yaooc_ordered_array_container_pointer this=p;
	if(n>this->size_) {
		yaooc_ordered_array_container_insert_n(p,yaooc_ordered_array_container_end(this),n-this->size_,value);
	} else {
		yaooc_ordered_array_container_erase_range(this,(yaooc_private_iterator)yaooc_ordered_array_container_begin(this)+n*this->type_info_->type_size_,yaooc_ordered_array_container_end(this));
	}
}

yaooc_size_type yaooc_ordered_array_container_erase_value(pointer p,const_pointer value)
{
	yaooc_ordered_array_container_pointer this=p;
	yaooc_size_type n_erased=0;
	yaooc_ordered_array_container_find_result_t fr=yaooc_ordered_array_container_find_private(this,value);
	if(fr.found_) {
		yaooc_size_type j,i=INDEX(this,fr.position_);
		n_erased=1;
		for(j=i+1;j<this->size_;j++) {
			if(op_ne_static(AT(this,j),value,this->type_info_))
				break;
			n_erased++;
		}
		yaooc_array_container_erase_range(this,AT(this,i),AT(this,i+n_erased));
	}
	return n_erased;
}

ISA_IMPLEMENTATION(yaooc_ordered_array_container,yaooc_array_container)

DEFINE_TYPE_INFO(yaooc_ordered_array_container,NULL,NULL,NULL,NULL,NULL,
        NULL,yaooc_array_container)
