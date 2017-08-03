
typedef void (*yaooc_callback)(void*,FILE*);
iterator yaooc_container_at(pointer,size_t pos);
void yaooc_container_dump(pointer p,FILE* out,yaooc_callback cb)
{
	yaooc_unique_index_container_const_pointer this=p;
	fprintf(out,"Dump\n");
	fprintf(out,"Base: %p  Size: %zu  Capacity: %zu\n",this->array_,this->size_,this->capacity_);
	size_t i;
	int count=0;
	fprintf(out,"Insert order:\n");
	char* ptr=this->array_;
	for(i=0;i<this->size_;i++) {
		if(cb) {
			cb(ptr,out);
		} else {
			fprintf(out,"%p ",ptr);
		}
		if(++count > 10) {
			fprintf(out,"\n");
			count=0;
		}
		ptr+=this->type_info_->type_size_;
	}
	if(this->index_) {
		fprintf(out,"\n\nIndex array:\n");
		count=0;
		size_t* st_ptr=this->index_;
		for(i=0;i<this->size_;i++,st_ptr++) {
			fprintf(out,"%zu  ",*st_ptr);
			if(++count > 10) {
				fprintf(out,"\n");
				count=0;
			}
		}
		count=0;
		fprintf(out,"\n\nSorted order\n");
		for(i=0;i<this->size_;i++) {
			ptr=yaooc_container_at(p,this->index_[i]);
			if(cb) {
				cb(ptr,out);
			} else {
				fprintf(out,"%p ",ptr);
			}
			if(++count > 10) {
				fprintf(out,"\n");
				count=0;
			}
			ptr+=this->type_info_->type_size_;
		}
	}
	fprintf(out,"\n");
}
