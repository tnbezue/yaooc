#include <string.h>
#include <stdio.h>
#include <yaooc/index_array_container.h>
#ifdef __YAOOC_BOUNDS_CHECKING__
#include <assert.h>
#endif

static container_private_class_methods_t index_container_private_class_methods=
{
  yaooc_array_container_size_needed,
  yaooc_index_array_container_increase_capacity
};

bool yaooc_index_array_container_increase_capacity(pointer p,yaooc_size_type n)
{
  debug(DEBUG_CONTAINER) {
    puts("Index container increase capacity");
  }
	bool rc;
	if((rc=yaooc_array_container_increase_capacity(p,n))) {
		yaooc_index_array_container_pointer this=p;
		this->index_=(yaooc_size_type*)REALLOC(this->index_,this->capacity_*sizeof(yaooc_size_type));
    debug(DEBUG_CONTAINER) {
      printf("Increasing index capacity %d\n",this->capacity_);
      printf("Index address %p\n",this->index_);
    }
	}
	return rc;
}

void yaooc_index_array_container_reserve(pointer p,yaooc_size_type n)
{
	yaooc_index_array_container_pointer this=p;
	if(n > this->capacity_)
		yaooc_index_array_container_increase_capacity(this,n-this->size_);
}

void yaooc_index_array_container_resize(pointer p,yaooc_size_type new_size,const_pointer value)
{
	yaooc_index_array_container_pointer this=p;
	if(new_size > this->size_) {
		yaooc_index_array_container_insert_n(this,yaooc_array_container_end(this),new_size-this->size_,value);
	} else {
		yaooc_index_array_container_erase_range(this,AT(this,new_size),AT(this,this->size_));
	}
}

void yaooc_index_array_container_ctor(pointer p,va_list args)
{
  yaooc_index_array_container_pointer this=p;
  call_constructor(this,yaooc_array_container_ctor,va_arg(args,const type_info_t*));
  this->private_class_table_=&index_container_private_class_methods;
	this->index_=NULL;
}

#ifndef __YAOOC_USE_GC__
void yaooc_index_array_container_dtor(pointer p)
{
	yaooc_index_array_container_pointer this=p;
  debug(DEBUG_CONTAINER) {
    printf("Deleting index at address %p\n",this->index_);
  }
	if(this->index_) FREE(this->index_);
}
#else
#define yaooc_index_array_container_dtor NULL
#endif

void yaooc_index_array_container_assign(pointer d,const_pointer s)
{
	yaooc_index_array_container_pointer dst=d;
  /*
    Note: yaooc_array_container_assign calls class method increase capacity (which is
    yaooc_index_array_container_increase_capacity) so index is properly sized.
  */
	yaooc_array_container_assign(d,s);
	yaooc_index_array_container_const_pointer src=s;
	memcpy(dst->index_,src->index_,dst->size_*sizeof(yaooc_size_type));
}

void yaooc_index_array_container_copy_ctor(pointer d,const_pointer s)
{
	yaooc_index_array_container_const_pointer src=s;
	call_constructor(d,yaooc_index_array_container_ctor,src->type_info_);
	yaooc_index_array_container_assign(d,s);
}

DEFINE_TYPE_INFO(yaooc_index_array_container,yaooc_array_container_default_ctor,
        yaooc_index_array_container_dtor,yaooc_index_array_container_copy_ctor,yaooc_index_array_container_assign,
        NULL,NULL,yaooc_array_container)

yaooc_index_array_container_find_result_t
yaooc_index_array_container_private_find(yaooc_index_array_container_const_pointer this,const_pointer value)
{
	yaooc_index_array_container_find_result_t fr = { 0,false};
	if(this->size_ > 0) {
		yaooc_size_type lower=0,upper=this->size_-1,middle;
		while(lower <= upper && upper != (yaooc_size_type)-1) {
			middle=(lower+upper)>>1;
			const_pointer middle_value=(const_pointer)I_AT(this,middle);
			if(op_lt_static(middle_value,value,this->type_info_)) {
				lower=middle+1;
				fr.index_=lower;
			} else if (op_lt_static(value,middle_value,this->type_info_)) {
				upper=middle-1;
				fr.index_=middle;
			} else {
				fr.found_=true;
				/* Make sure to return the first one */
				while(middle > 0) {
          middle--;
					if(op_lt_static(I_AT(this,middle),value,this->type_info_)) {
						middle++;
						break;
					}
				}
				fr.index_=middle;
				break;
			}
		}
	}
	return fr;
}

iterator yaooc_index_array_container_find(const_pointer p,const_pointer value)
{
	yaooc_index_array_container_const_pointer this=p;
	yaooc_index_array_container_find_result_t fr=yaooc_index_array_container_private_find(this,value);
	if(fr.found_)
		return this->array_+this->index_[fr.index_]*this->type_info_->type_size_;
	return yaooc_array_container_end((pointer)this);
}

const_iterator yaooc_index_array_container_cfind(const_pointer p,const_pointer value)
{
	return yaooc_index_array_container_find(p,value);
}

void yaooc_insert_index(pointer p,yaooc_size_type pos,yaooc_size_type n,yaooc_size_type size,yaooc_size_type value)
{
  yaooc_index_array_container_pointer this=p;
	/*
		Add n to every index that is greater or equal to value
	*/
  debug(DEBUG_CONTAINER) {
    puts("inserting index");
  }
	yaooc_size_type i;
	yaooc_size_type n_gt_value=size-value;
	for(i=0;i<size && n_gt_value>0;i++) {
		if(this->index_[i] >= value) {
			this->index_[i]+=n;
			n_gt_value--;
		}
	}
	memmove(this->index_+pos+n,this->index_+pos,(size-pos)*sizeof(yaooc_size_type));
	for(i=0;i<n;i++)
		this->index_[pos++]=value++;
}

/*
	All checks have been perform, array and ordered index have sufficient capacity, just do insert
*/
void yaooc_index_array_container_private_insert(pointer p,yaooc_private_const_iterator pos,yaooc_size_type n,const_pointer value)
{
	yaooc_index_array_container_pointer this=p;
	yaooc_array_container_insert_n(this,pos,n,value);
}

iterator yaooc_index_array_container_insert_n(pointer p,const_iterator pos,yaooc_size_type n,const_pointer value)
{
	yaooc_index_array_container_pointer this=p;
	yaooc_private_const_iterator ypos=pos;
#ifdef __YAOOC_BOUNDS_CHECKING__
	assert(CBEGIN(this) <= ypos && ypos <= CEND(this) && "Container insert position out of range");
#endif
	yaooc_index_array_container_find_result_t fr=yaooc_index_array_container_private_find(p,value);
	yaooc_size_type index=(ypos-(char*)BEGIN(this))/this->type_info_->type_size_;
	yaooc_index_array_container_increase_capacity(this,n);
	yaooc_insert_index(this,fr.index_,1,this->size_,index);
	yaooc_array_container_insert_n_private(this,index,n,value);
	return AT(this,index);
}

iterator yaooc_index_array_container_insert(pointer p,const_iterator pos,const_pointer value)
{
	return yaooc_index_array_container_insert_n(p,pos,1,value);
}

iterator yaooc_index_array_container_insert_range(pointer p,const_iterator pos,const_iterator f,const_iterator l)
{
	yaooc_index_array_container_pointer this=p;
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
	for(;first!=last;first+=this->type_info_->type_size_,ipos+=this->type_info_->type_size_) {
		yaooc_index_array_container_insert_n(this,ipos,1,first);
	}
	return rpos;
}

void yaooc_index_array_container_erase_index(pointer p,yaooc_size_type index,yaooc_size_type oi_size)
{
	yaooc_index_array_container_pointer this=p;
#ifdef __YAOOC_BOUNDS_CHECKING__
	assert(index < oi_size && "Index out of range in yaooc_index_array_container_erase_index");
#endif
	yaooc_size_type i,pos=-1;
	for(i=0;i<oi_size;i++)
		if(this->index_[i]==index) {
			pos=i;
			break;
		}
#ifdef __YAOOC_BOUNDS_CHECKING__
	assert(pos != (yaooc_size_type)-1 && "Index not found in yaooc_index_array_container_erase_index");
#endif
	// decrement all indexes greater than index
	yaooc_size_type n_gt_index=oi_size-index;
	for(i=0;i<oi_size && n_gt_index>0;i++) {
		if(this->index_[i]>index) {
			this->index_[i]--;
			n_gt_index--;
		}
	}
	memmove(this->index_+pos,this->index_+pos+1,(oi_size-pos-1)*sizeof(yaooc_size_type));
}

iterator yaooc_index_array_container_erase(pointer p,iterator pos)
{
	yaooc_index_array_container_pointer this=p;
#ifdef __YAOOC_BOUNDS_CHECKING__
	assert((pointer)BEGIN(this) <= pos && pos < (pointer)END(this) && "Pos out of range in yaooc_index_array_container_erase");
#endif
	yaooc_size_type index=((char*)pos - this->array_)/this->type_info_->type_size_;
	yaooc_array_container_erase(p,pos);
	yaooc_index_array_container_erase_index(this,index,this->size_+1);
	return pos;
}

iterator yaooc_index_array_container_erase_range(pointer p,iterator first,iterator last)
{
/*
	Have to erase one at a time because index array may not have consecutive items
*/
	yaooc_index_array_container_pointer this=p;
#ifdef __YAOOC_BOUNDS_CHECKING__
	assert(first <= last && "First greater than last in yaooc_index_array_container_erase_range");
	assert(BEGIN(this) <= (char*)first && (char*)last < END(this) && "Container erase position out of range");
#endif
	yaooc_size_type n=((char*)last - (char*)first)/this->type_info_->type_size_;
	yaooc_size_type i;
	for(i=0;i<n;i++)
		yaooc_index_array_container_erase(this,first);
	return first;
}

void yaooc_index_array_container_shrink_to_fit(pointer p)
{
	yaooc_index_array_container_pointer this=p;
	yaooc_size_type old_cap=this->capacity_;
	yaooc_array_container_shrink_to_fit(p);
	if(old_cap != this->capacity_) {
		this->index_=(yaooc_size_type*)REALLOC(this->index_,this->capacity_*sizeof(yaooc_size_type));
	}
}

void yaooc_index_array_container_swap(pointer p,pointer o)
{
  yaooc_index_array_container_pointer this=p;
  yaooc_index_array_container_pointer other=o;
  yaooc_array_container_swap(p,o);
  SWAP(yaooc_size_type*,this->index_,other->index_);
}

void yaooc_index_array_container_print_indexes(pointer p,FILE* out)
{
  yaooc_index_array_container_pointer this=p;
  yaooc_size_type i;
  for(i=0;i<this->size_;i++)
    fprintf(out,"%d ",this->index_[i]);
  fprintf(out,"\n");
}

ISA_IMPLEMENTATION(yaooc_index_array_container,yaooc_array_container)
