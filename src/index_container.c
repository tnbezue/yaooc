#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <yaooc/index_container.h>

static container_private_class_methods_t index_container_private_class_methods=
{
  yaooc_container_size_needed,
  yaooc_index_container_increase_capacity
};

bool yaooc_index_container_increase_capacity(pointer p,size_t n)
{
  debug(DEBUG_CONTAINER) {
    puts("Index container increase capacity");
  }
	bool rc;
	if((rc=yaooc_container_increase_capacity(p,n))) {
		yaooc_index_container_pointer this=p;
		this->index_=(size_t*)REALLOC(this->index_,this->capacity_*sizeof(size_t));
    debug(DEBUG_CONTAINER) {
      printf("Increasing index capacity %zu\n",this->capacity_);
      printf("Index address %p\n",this->index_);
    }
	}
	return rc;
}

void yaooc_index_container_reserve(pointer p,size_t n)
{
	yaooc_index_container_pointer this=p;
	if(n > this->capacity_)
		yaooc_index_container_increase_capacity(this,n-this->size_);
}

void yaooc_index_container_resize(pointer p,size_t new_size,const_pointer value)
{
	yaooc_index_container_pointer this=p;
	if(new_size > this->size_) {
		yaooc_index_container_insert_n(this,yaooc_container_end(this),new_size-this->size_,value);
	} else {
		yaooc_index_container_erase_range(this,AT(this,new_size),AT(this,this->size_));
	}
}

void yaooc_index_container_ctor(pointer p,va_list args)
{
  yaooc_index_container_pointer this=p;
  call_constructor(this,yaooc_container_ctor,va_arg(args,const type_info_t*));
  this->private_class_table_=&index_container_private_class_methods;
	this->index_=NULL;
}

#ifndef __YAOOC_USE_GC__
void yaooc_index_container_dtor(pointer p)
{
	yaooc_index_container_pointer this=p;
  debug(DEBUG_CONTAINER) {
    printf("Deleting index at address %p\n",this->index_);
  }
	if(this->index_) FREE(this->index_);
}
#else
#define yaooc_index_container_dtor NULL
#endif

void yaooc_index_container_assign(pointer d,const_pointer s)
{
	yaooc_index_container_pointer dst=d;
  /*
    Note: yaooc_container_assign calls class method increase capacity (which is
    yaooc_index_container_increase_capacity) so index is properly sized.
  */
	yaooc_container_assign(d,s);
	yaooc_index_container_const_pointer src=s;
	memcpy(dst->index_,src->index_,dst->size_*sizeof(size_t));
}

void yaooc_index_container_copy_ctor(pointer d,const_pointer s)
{
	yaooc_index_container_const_pointer src=s;
	call_constructor(d,yaooc_index_container_ctor,src->type_info_);
	yaooc_index_container_assign(d,s);
}

DEFINE_TYPE_INFO(yaooc_index_container,yaooc_container_default_ctor,
        yaooc_index_container_dtor,yaooc_index_container_copy_ctor,yaooc_index_container_assign,
        NULL,NULL,yaooc_container)

yaooc_index_container_find_result_t
yaooc_index_container_private_find(yaooc_index_container_const_pointer this,const_pointer value)
{
	yaooc_index_container_find_result_t fr = { 0,false};
	if(this->size_ > 0) {
		size_t lower=0,upper=this->size_-1,middle;
		while(lower <= upper && upper != (size_t)-1) {
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

iterator yaooc_index_container_find(const_pointer p,const_pointer value)
{
	yaooc_index_container_const_pointer this=p;
	yaooc_index_container_find_result_t fr=yaooc_index_container_private_find(this,value);
	if(fr.found_)
		return this->array_+this->index_[fr.index_]*this->type_info_->type_size_;
	return yaooc_container_end((pointer)this);
}

const_iterator yaooc_index_container_cfind(const_pointer p,const_pointer value)
{
	return yaooc_index_container_find(p,value);
}

void yaooc_insert_index(pointer p,size_t pos,size_t n,size_t size,size_t value)
{
  yaooc_index_container_pointer this=p;
	/*
		Add n to every index that is greater or equal to value
	*/
  debug(DEBUG_CONTAINER) {
    puts("inserting index");
  }
	size_t i;
	size_t n_gt_value=size-value;
	for(i=0;i<size && n_gt_value>0;i++) {
		if(this->index_[i] >= value) {
			this->index_[i]+=n;
			n_gt_value--;
		}
	}
	memmove(this->index_+pos+n,this->index_+pos,(size-pos)*sizeof(size_t));
	for(i=0;i<n;i++)
		this->index_[pos++]=value++;
}

/*
	All checks have been perform, array and ordered index have sufficient capacity, just do insert
*/
void yaooc_index_container_private_insert(pointer p,yaooc_private_const_iterator pos,size_t n,const_pointer value)
{
	yaooc_index_container_pointer this=p;
	yaooc_container_insert_n(this,pos,n,value);
}

iterator yaooc_index_container_insert_n(pointer p,const_iterator pos,size_t n,const_pointer value)
{
	yaooc_index_container_pointer this=p;
	yaooc_private_const_iterator ypos=pos;
	assert(CBEGIN(this) <= ypos && ypos <= CEND(this) && "Container insert position out of range");
	yaooc_index_container_find_result_t fr=yaooc_index_container_private_find(p,value);
	size_t index=(ypos-(char*)BEGIN(this))/this->type_info_->type_size_;
	yaooc_index_container_increase_capacity(this,n);
	yaooc_insert_index(this,fr.index_,1,this->size_,index);
	yaooc_container_insert_n_private(this,index,n,value);
	return AT(this,index);
}

iterator yaooc_index_container_insert(pointer p,const_iterator pos,const_pointer value)
{
	return yaooc_index_container_insert_n(p,pos,1,value);
}

iterator yaooc_index_container_insert_range(pointer p,const_iterator pos,const_iterator f,const_iterator l)
{
	yaooc_index_container_pointer this=p;
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
	for(;first!=last;first+=this->type_info_->type_size_,ipos+=this->type_info_->type_size_) {
		yaooc_index_container_insert_n(this,ipos,1,first);
	}
	return rpos;
}

void yaooc_index_container_erase_index(pointer p,size_t index,size_t oi_size)
{
	yaooc_index_container_pointer this=p;
	assert(index < oi_size && "Index out of range in yaooc_index_container_erase_index");
	size_t i,pos=-1;
	for(i=0;i<oi_size;i++)
		if(this->index_[i]==index) {
			pos=i;
			break;
		}
	assert(pos != (size_t)-1 && "Index not found in yaooc_index_container_erase_index");
	// decrement all indexes greater than index
	size_t n_gt_index=oi_size-index;
	for(i=0;i<oi_size && n_gt_index>0;i++) {
		if(this->index_[i]>index) {
			this->index_[i]--;
			n_gt_index--;
		}
	}
	memmove(this->index_+pos,this->index_+pos+1,(oi_size-pos-1)*sizeof(size_t));
}

iterator yaooc_index_container_erase(pointer p,iterator pos)
{
	yaooc_index_container_pointer this=p;
	assert((pointer)BEGIN(this) <= pos && pos < (pointer)END(this) && "Pos out of range in yaooc_index_container_erase");
	size_t index=((char*)pos - this->array_)/this->type_info_->type_size_;
	yaooc_container_erase(p,pos);
	yaooc_index_container_erase_index(this,index,this->size_+1);
	return pos;
}

iterator yaooc_index_container_erase_range(pointer p,iterator first,iterator last)
{
/*
	Have to erase one at a time because index array may not have consecutive items
*/
	yaooc_index_container_pointer this=p;
	assert(first <= last && "First greater than last in yaooc_index_container_erase_range");
	assert(BEGIN(this) <= (char*)first && (char*)last < END(this) && "Container erase position out of range");
	size_t n=((char*)last - (char*)first)/this->type_info_->type_size_;
	size_t i;
	for(i=0;i<n;i++)
		yaooc_index_container_erase(this,first);
	return first;
}

void yaooc_index_container_shrink_to_fit(pointer p)
{
	yaooc_index_container_pointer this=p;
	size_t old_cap=this->capacity_;
	yaooc_container_shrink_to_fit(p);
	if(old_cap != this->capacity_) {
		this->index_=(size_t*)REALLOC(this->index_,this->capacity_*sizeof(size_t));
	}
}

void yaooc_index_container_swap(pointer p,pointer o)
{
  yaooc_index_container_pointer this=p;
  yaooc_index_container_pointer other=o;
  yaooc_container_swap(p,o);
  SWAP(size_t*,this->index_,other->index_);
}

void yaooc_index_container_print_indexes(pointer p,FILE* out)
{
  yaooc_index_container_pointer this=p;
  size_t i;
  for(i=0;i<this->size_;i++)
    fprintf(out,"%zu ",this->index_[i]);
  fprintf(out,"\n");
}

ISA_IMPLEMENTATION(yaooc_index_container,yaooc_container)
