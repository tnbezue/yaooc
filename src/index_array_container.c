#include <yaooc/index_array_container.h>
#include <string.h>
#include <stdio.h>

int cmp_size_t(const void* a,const void* b)
{
  if(*(size_t*)a < *(size_t*)b)
    return -1;
  if(*(size_t*)a > *(size_t*)b)
    return 1;
  return 0;
}



void yaooc_index_array_container_dtor(pointer __pthis__)
{
yaooc_index_array_container_pointer this=__pthis__;(void)this;


      if(this->indexes_ != NULL)
        FREE(this->indexes_);
    
}
void yaooc_index_array_container_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaooc_index_array_container_pointer this=__pthis__;(void)this;
yaooc_index_array_container_const_pointer src=__psrc__;(void)src;

call_constructor(this,yaooc_index_array_container_ctor_ti,TYPE_INFO(src));


      yaooc_index_array_container_assign(this,src);
    
}
void yaooc_index_array_container_assign(pointer __pthis__,const_pointer __psrc__)
{
yaooc_index_array_container_pointer this=__pthis__;(void)this;
yaooc_index_array_container_const_pointer src=__psrc__;(void)src;


      yaooc_array_container_assign(this,src);
      memcpy(this->indexes_,src->indexes_,this->size_*sizeof(yaooc_index_array_container_index_t));
    
}
void yaooc_index_array_container_ctor_ti(pointer __pthis,va_list __con_args__){
yaooc_index_array_container_pointer this=__pthis;(void)this;
const type_info_t* ti = va_arg(__con_args__,const type_info_t*);

call_constructor(this,yaooc_array_container_ctor_ti,ti);


      this->indexes_=NULL;
    
}
yaooc_index_array_container_find_result_t yaooc_index_array_container_find_protected(const_pointer __pthis__,const_pointer value)
{
yaooc_index_array_container_const_pointer this=__pthis__;(void)this;

      yaooc_index_array_container_find_result_t ret = { 0, 0, false };
      size_t lower=0,upper=this->size_-1,middle;
      rich_compare rich_cmp=get_rich_compare(this->type_info_);
      while(lower <= upper && upper != (size_t)-1) {
        middle=(lower+upper)>>1;
        const_pointer middle_value=AT_I(this,middle);
        int rc = rich_cmp(middle_value,value);
        if(rc < 0) {
          lower=middle+1;
          ret.lower_index_=lower;
        } else if(rc > 0) {
          upper=middle-1;
          ret.lower_index_=middle;
        } else {
          


          size_t idx=middle-1;
          for(;idx>=0 && idx != (size_t)-1;idx--) {
            if(rich_cmp(AT_I(this,idx),value)<0)
              break;
          }
          ret.lower_index_=idx+1;
          for(idx=middle+1;idx<SIZE(this);idx++) {
            if(rich_cmp(value,AT_I(this,idx))<0)
              break;
          }
          ret.upper_index_=idx-1;
          ret.found_=true;
          break;
        }
      }
      return ret;
    
}
void yaooc_index_array_container_insert_index(pointer __pthis__,size_t pos,size_t n,size_t value,size_t size)
{
yaooc_index_array_container_pointer this=__pthis__;(void)this;

      size_t i;
      size_t n_ge_value=size-value;
      for(i=0;i<size && n_ge_value>0;i++) {
        uint32_t temp=yaooc_uint24_to_uint32(this->indexes_+i);
        if(temp >= value) {
          yaooc_uint24_from_uint32(this->indexes_+i,temp+n);
          n_ge_value--;
        }
      }
      memmove(this->indexes_+pos+n,this->indexes_+pos,(size -pos)*sizeof(yaooc_index_array_container_index_t));
      for(i=0;i<n;i++,pos++)
        yaooc_uint24_from_uint32(this->indexes_+pos,value++);
    
}
void yaooc_index_array_container_remove_index(pointer __pthis__,size_t pos,size_t n)
{
yaooc_index_array_container_pointer this=__pthis__;(void)this;

      size_t i,j;
      size_t lower=pos;
      size_t upper=pos+n;
      size_t new_size=SIZE(this)-1;
      for(j=lower;j<upper;j++) {
        size_t n_gt_index=new_size-yaooc_uint24_to_uint32(this->indexes_+j);
        for(i=0; i<lower && n_gt_index > 0;i++) {
          uint32_t temp=yaooc_uint24_to_uint32(this->indexes_+i);
          if(temp > yaooc_uint24_to_uint32(this->indexes_+j)) {
            yaooc_uint24_from_uint32(this->indexes_+i,--temp);
            n_gt_index--;
          }
        }
        for(i=j+1; i<SIZE(this) && n_gt_index > 0;i++) {
          uint32_t temp=yaooc_uint24_to_uint32(this->indexes_+i);
          if(temp > yaooc_uint24_to_uint32(this->indexes_+j)) {
            yaooc_uint24_from_uint32(this->indexes_+i,--temp);
            n_gt_index--;
          }
        }
        new_size--;
      }
      memmove(this->indexes_+pos,this->indexes_+pos+n,(SIZE(this)-pos-n)*sizeof(yaooc_index_array_container_index_t));
    
}
void yaooc_index_array_container_remove_fixed_index(pointer __pthis__,size_t value,size_t n)
{
yaooc_index_array_container_pointer this=__pthis__;(void)this;

      size_t i,j;
      size_t save_size=SIZE(this);
      for(j=0;j<n;j++) {
        for(i=0;i<SIZE(this);i++) {
          if(value == yaooc_uint24_to_uint32(this->indexes_+i))
            break;
        }
        yaooc_index_array_container_remove_index(this,i,1);
        this->size_--;
      }
      this->size_=save_size;
    
}
iterator yaooc_index_array_container_insert(pointer __pthis__,const_iterator pos,const_pointer value)
{
yaooc_index_array_container_pointer this=__pthis__;(void)this;

      return yaooc_index_array_container_insertn(this,pos,1,value);
    
}
iterator yaooc_index_array_container_insertn(pointer __pthis__,const_iterator pos,size_t n,const_pointer val)
{
yaooc_index_array_container_pointer this=__pthis__;(void)this;

      size_t cur_size=SIZE(this);
      size_t idx=INDEX(this,pos);
      yaooc_index_array_container_find_result_t fr=yaooc_index_array_container_find_protected(this,val);
      iterator ret=yaooc_array_container_insertn(this,pos,n,val);
      yaooc_index_array_container_insert_index(this,fr.lower_index_,n,idx,cur_size);
      return ret;
    
}
iterator yaooc_index_array_container_insert_range(pointer __pthis__,const_iterator pos,const_iterator f,const_iterator l)
{
yaooc_index_array_container_pointer this=__pthis__;(void)this;

      size_t idx=INDEX(this,pos);
      yaooc_private_const_iterator first=f;
      yaooc_private_const_iterator last=l;
      for(;first < last;first+=TYPE_SIZE(this),idx++) {
        yaooc_index_array_container_find_result_t fr=yaooc_index_array_container_find_protected(this,first);
        size_t cur_size=SIZE(this);
        yaooc_array_container_insert(this,AT(this,idx),first);
        yaooc_index_array_container_insert_index(this,fr.lower_index_,1,idx,cur_size);
      }
      return AT(this,idx);
    
}
iterator yaooc_index_array_container_find(const_pointer __pthis__,const_pointer value)
{
yaooc_index_array_container_const_pointer this=__pthis__;(void)this;

      yaooc_index_array_container_find_result_t fr=yaooc_index_array_container_find_protected(this,value);
      return fr.found_ ? AT_I(this,fr.lower_index_) : END(this);
    
}
iterator yaooc_index_array_container_erase(pointer __pthis__,const_iterator pos)
{
yaooc_index_array_container_pointer this=__pthis__;(void)this;

      return yaooc_index_array_container_erase_range(this,pos,((yaooc_private_const_iterator)pos)+TYPE_SIZE(this));
    
}
size_t yaooc_index_array_container_erase_value(pointer __pthis__,const_pointer value)
{
yaooc_index_array_container_pointer this=__pthis__;(void)this;

      size_t n_del=0;
      yaooc_index_array_container_find_result_t fr=yaooc_index_array_container_find_protected(this,value);
      if(fr.found_) {
        size_t i,j;
        n_del = fr.upper_index_-fr.lower_index_+1;
        size_t * indexes=__new_array(size_ti,n_del);
        for(j=0,i=fr.lower_index_;i<=fr.upper_index_;j++,i++) {
          indexes[j]=yaooc_uint24_to_uint32(this->indexes_+i);
        }
        qsort(indexes,n_del,sizeof(size_t),cmp_size_t);
        yaooc_index_array_container_remove_index(this,fr.lower_index_,n_del);
        for(j=n_del-1;j>=0 && j!=(size_t)-1;j--)
          yaooc_array_container_erase_range(this,AT(this,indexes[j]),AT(this,indexes[j]+1));
        delete(indexes);
      }
      return n_del;
    
}
iterator yaooc_index_array_container_erase_range(pointer __pthis__,const_iterator f,const_iterator l)
{
yaooc_index_array_container_pointer this=__pthis__;(void)this;

      size_t n=DISTANCE(TYPE_INFO(this),f,l);
      size_t idx=INDEX(this,f);
      yaooc_index_array_container_remove_fixed_index(this,idx,n);
      return yaooc_array_container_erase_range(this,f,l);
    
}
void yaooc_index_array_container_resize_value(pointer __pthis__,size_t n,const_pointer value)
{
yaooc_index_array_container_pointer this=__pthis__;(void)this;

      if(n<SIZE(this)) {
        yaooc_index_array_container_erase_range(this,AT(this,n),END(this));
      } else {
        yaooc_index_array_container_insertn(this,END(this),n-SIZE(this),value);
      }
    
}
void yaooc_index_array_container_resize(pointer __pthis__,size_t n)
{
yaooc_index_array_container_pointer this=__pthis__;(void)this;

      pointer temp=__new_array(TYPE_INFO(this),1);
      yaooc_index_array_container_resize_value(this,n,temp);
      delete(temp);
    
}
void yaooc_index_array_container_shrink_to_fit(pointer __pthis__)
{
yaooc_index_array_container_pointer this=__pthis__;(void)this;

      size_t old_capacity=this->capacity_;
      yaooc_array_container_shrink_to_fit(this);
      if(this->capacity_ != old_capacity)
        this->indexes_=REALLOC(this->indexes_,this->capacity_*sizeof(yaooc_index_array_container_index_t));
    
}
void yaooc_index_array_container_reserve(pointer __pthis__,size_t n)
{
yaooc_index_array_container_pointer this=__pthis__;(void)this;

      size_t old_capacity=this->capacity_;
      yaooc_array_container_reserve(this,n);
      if(this->capacity_ != old_capacity)
        this->indexes_=REALLOC(this->indexes_,this->capacity_*sizeof(yaooc_index_array_container_index_t));
    
}
iterator yaooc_index_array_container_yaooc_index_array_container_at_i(pointer __pthis__,const_pointer p,size_t i)
{
yaooc_index_array_container_pointer this=__pthis__;(void)this;

      return AT_I(this,i);
    
}
bool yaooc_index_array_container_increase_capacity(pointer __pthis__,size_t n)
{
yaooc_index_array_container_pointer this=__pthis__;(void)this;
#define super() yaooc_index_array_container_parent_class_table->increase_capacity(this,n)
#define PM(method,...) CTM((*yaooc_index_array_container_parent_class_table),this,method,## __VA_ARGS__)


      bool ret=super();
      if(ret) {
        this->indexes_=REALLOC(this->indexes_,CAPACITY(this)*sizeof(yaooc_index_array_container_index_t));
      }
      return ret;
    
#undef PM
#undef super
}
yaooc_index_array_container_class_table_t yaooc_index_array_container_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_array_container_class_table,
.type_name_ = (const char*)"yaooc_index_array_container_t",
.swap = (void(*)(pointer,pointer)) yaooc_index_array_container_swap,
.increase_capacity = (bool(*)(pointer,size_t)) yaooc_index_array_container_increase_capacity,
.size_needed = (size_t(*)(const_pointer,size_t)) yaooc_index_array_container_size_needed,
.size = (size_t(*)(const_pointer)) yaooc_index_array_container_size,
.capacity = (size_t(*)(const_pointer)) yaooc_index_array_container_capacity,
.empty = (bool(*)(const_pointer)) yaooc_index_array_container_empty,
.begin = (iterator(*)(pointer)) yaooc_index_array_container_begin,
.end = (iterator(*)(pointer)) yaooc_index_array_container_end,
.cbegin = (const_iterator(*)(const_pointer)) yaooc_index_array_container_cbegin,
.cend = (const_iterator(*)(const_pointer)) yaooc_index_array_container_cend,
};
const type_info_t __yaooc_index_array_container_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_index_array_container_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=NULL,
.dtor_=yaooc_index_array_container_dtor,
.copy_ctor_=yaooc_index_array_container_copy_ctor,
.assign_=yaooc_index_array_container_assign,
.class_table_=(const class_table_t*) &yaooc_index_array_container_class_table,
.parent_=&__yaooc_array_container_ti
};
const type_info_t* const yaooc_index_array_container_ti=&__yaooc_index_array_container_ti;
