#include <yaooc/memory.h>
void yaooc_dynamic_pointer_default_ctor(pointer __pthis__)
{
yaooc_dynamic_pointer_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_dynamic_pointer);


 this->ptr_=NULL; 
}
void yaooc_dynamic_pointer_dtor(pointer __pthis__)
{
yaooc_dynamic_pointer_pointer this=__pthis__;(void)this;

 if(this->ptr_!=NULL) delete(this->ptr_); 
}
void yaooc_dynamic_pointer_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaooc_dynamic_pointer_pointer this=__pthis__;(void)this;
yaooc_dynamic_pointer_const_pointer src=__psrc__;(void)src;

call_default_ctor_static(this,yaooc_dynamic_pointer);


      this->ptr_ = src->ptr_ ? new_copy(src->ptr_) : NULL;
    
}
void yaooc_dynamic_pointer_assign(pointer __pthis__,const_pointer __psrc__)
{
yaooc_dynamic_pointer_pointer this=__pthis__;(void)this;
yaooc_dynamic_pointer_const_pointer src=__psrc__;(void)src;


      yaooc_dynamic_pointer_dtor(this);
      yaooc_dynamic_pointer_copy_ctor(this,src);
    
}
int yaooc_dynamic_pointer_rich_compare(const_pointer __plhs__,const_pointer __prhs__)
{
yaooc_dynamic_pointer_const_pointer lhs=__plhs__;(void)lhs;
yaooc_dynamic_pointer_const_pointer rhs=__prhs__;(void)rhs;

      return op_rich_compare(lhs->ptr_,rhs->ptr_);
    
}
void yaooc_dynamic_pointer_to_stream(const_pointer __pthis__,ostream_pointer __pstrm__)
{
yaooc_dynamic_pointer_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer istrm=__pstrm__;(void)istrm;

      M(istrm,stream,this->ptr_,NULL);
    
}
void yaooc_dynamic_pointer_from_stream(pointer __pthis__,ostream_pointer __pstrm__)
{
yaooc_dynamic_pointer_pointer this=__pthis__;(void)this;
yaooc_istream_pointer ostrm=__pstrm__;(void)ostrm;

      M(ostrm,stream,this->ptr_,NULL);
    
}
void yaooc_dynamic_pointer_ctor_ptr(pointer __pthis,va_list __con_args__){
yaooc_dynamic_pointer_pointer this=__pthis;(void)this;
const_pointer p = va_arg(__con_args__,const_pointer);

call_default_ctor_static(this,yaooc_dynamic_pointer);

 yaooc_dynamic_pointer_copy_ctor(this,p);  
}
const type_info_t __yaooc_dynamic_pointer_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_dynamic_pointer_t),
.rich_compare_=yaooc_dynamic_pointer_rich_compare,
.to_stream_=yaooc_dynamic_pointer_to_stream,
.from_stream_=yaooc_dynamic_pointer_from_stream,
.default_ctor_=yaooc_dynamic_pointer_default_ctor,
.dtor_=yaooc_dynamic_pointer_dtor,
.copy_ctor_=yaooc_dynamic_pointer_copy_ctor,
.assign_=yaooc_dynamic_pointer_assign,
.class_table_=NULL,
.parent_=NULL
};
const type_info_t* const yaooc_dynamic_pointer_ti=(const type_info_t* const)&__yaooc_dynamic_pointer_ti;
void yaooc_unique_pointer_default_ctor(pointer __pthis__)
{
yaooc_unique_pointer_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_unique_pointer);



      this->ptr_=NULL;
    
}
void yaooc_unique_pointer_dtor(pointer __pthis__)
{
yaooc_unique_pointer_pointer this=__pthis__;(void)this;


      if(this->ptr_)
        delete(this->ptr_);
      this->ptr_=NULL;
    
}
void yaooc_unique_pointer_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaooc_unique_pointer_pointer this=__pthis__;(void)this;
yaooc_unique_pointer_const_pointer src=__psrc__;(void)src;

call_default_ctor_static(this,yaooc_unique_pointer);


      assign_static(this,src,yaooc_unique_pointer);
    
}
void yaooc_unique_pointer_assign(pointer __pthis__,const_pointer __psrc__)
{
yaooc_unique_pointer_pointer this=__pthis__;(void)this;
yaooc_unique_pointer_const_pointer src=__psrc__;(void)src;


      if(this->ptr_ != src->ptr_) {
        deletep(this,yaooc_unique_pointer);
        this->ptr_=src->ptr_;
        ((yaooc_unique_pointer_pointer)src)->ptr_=NULL;  
      }
    
}
int yaooc_unique_pointer_rich_compare(const_pointer __plhs__,const_pointer __prhs__)
{
yaooc_unique_pointer_const_pointer lhs=__plhs__;(void)lhs;
yaooc_unique_pointer_const_pointer rhs=__prhs__;(void)rhs;

      if(lhs->ptr_==rhs->ptr_)
        return 0;
      if(lhs->ptr_ != NULL) {
        if(rhs->ptr_ != NULL) {
          return op_rich_compare(lhs->ptr_,rhs->ptr_);
        } else {
          return 1;
        }
      }
      
      return -1;
    
}
void yaooc_unique_pointer_ctor_ptr(pointer __pthis,va_list __con_args__){
yaooc_unique_pointer_pointer this=__pthis;(void)this;
pointer value = va_arg(__con_args__,pointer);

call_default_ctor_static(this,yaooc_unique_pointer);


      M(this,reset,value);
    
}
void yaooc_unique_pointer_swap(pointer __pthis__,pointer o)
{
yaooc_unique_pointer_pointer this=__pthis__;(void)this;
#define super() yaooc_unique_pointer_parent_class_table->swap(this,o)
#define PM(method,...) CTM((*yaooc_unique_pointer_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_unique_pointer_t* other=o;
      SWAP(pointer,this->ptr_,other->ptr_);
    
#undef PM
#undef super
}
pointer yaooc_unique_pointer_get(const_pointer __pthis__)
{
yaooc_unique_pointer_const_pointer this=__pthis__;(void)this;
#define super() yaooc_unique_pointer_parent_class_table->get(this)
#define PM(method,...) CTM((*yaooc_unique_pointer_parent_class_table),this,method,## __VA_ARGS__)


      return this->ptr_;
    
#undef PM
#undef super
}
pointer yaooc_unique_pointer_release(pointer __pthis__)
{
yaooc_unique_pointer_pointer this=__pthis__;(void)this;
#define super() yaooc_unique_pointer_parent_class_table->release(this)
#define PM(method,...) CTM((*yaooc_unique_pointer_parent_class_table),this,method,## __VA_ARGS__)


      pointer ret = this->ptr_;
      this->ptr_=NULL;
      return ret;
    
#undef PM
#undef super
}
void yaooc_unique_pointer_reset(pointer __pthis__,pointer ptr)
{
yaooc_unique_pointer_pointer this=__pthis__;(void)this;
#define super() yaooc_unique_pointer_parent_class_table->reset(this,ptr)
#define PM(method,...) CTM((*yaooc_unique_pointer_parent_class_table),this,method,## __VA_ARGS__)


      deletep(this,yaooc_unique_pointer);
      this->ptr_=ptr;
    
#undef PM
#undef super
}
yaooc_unique_pointer_class_table_t yaooc_unique_pointer_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_object_class_table,
.type_name_ = (const char*)"yaooc_unique_pointer_t",
.swap = (void(*)(pointer,pointer)) yaooc_unique_pointer_swap,
.get = (pointer(*)(const_pointer)) yaooc_unique_pointer_get,
.release = (pointer(*)(pointer)) yaooc_unique_pointer_release,
.reset = (void(*)(pointer,pointer)) yaooc_unique_pointer_reset,
};
const type_info_t __yaooc_unique_pointer_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_unique_pointer_t),
.rich_compare_=yaooc_unique_pointer_rich_compare,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaooc_unique_pointer_default_ctor,
.dtor_=yaooc_unique_pointer_dtor,
.copy_ctor_=yaooc_unique_pointer_copy_ctor,
.assign_=yaooc_unique_pointer_assign,
.class_table_=(const class_table_t*) &yaooc_unique_pointer_class_table,
.parent_=&__yaooc_object_ti
};
const type_info_t* const yaooc_unique_pointer_ti=&__yaooc_unique_pointer_ti;
struct yaooc_counter_s {
	void* ptr_;
	size_t count_;
};

static void yaooc_counter_default_ctor(pointer p)
{
  yaooc_counter_t* this=p;
	this->ptr_=NULL;
	this->count_=1;
}

static void yaooc_counter_ctor_ptr(pointer p,va_list args)
{
  yaooc_counter_t* this=p;
	this->ptr_=va_arg(args,pointer);
	this->count_=1;
}

DEFINE_TYPE_INFO(yaooc_counter,Y,N,N,N,N,N,N,N,NULL);


void yaooc_shared_pointer_default_ctor(pointer __pthis__)
{
yaooc_shared_pointer_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_shared_pointer);



    this->counter_=NULL;
  
}
void yaooc_shared_pointer_dtor(pointer __pthis__)
{
yaooc_shared_pointer_pointer this=__pthis__;(void)this;


    M(this,release);
  
}
void yaooc_shared_pointer_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaooc_shared_pointer_pointer this=__pthis__;(void)this;
yaooc_shared_pointer_const_pointer src=__psrc__;(void)src;

call_default_ctor_static(this,yaooc_shared_pointer);


    call_default_ctor_static(this,yaooc_shared_pointer);
    assign_static(this,src,yaooc_shared_pointer);
  
}
void yaooc_shared_pointer_assign(pointer __pthis__,const_pointer __psrc__)
{
yaooc_shared_pointer_pointer this=__pthis__;(void)this;
yaooc_shared_pointer_const_pointer src=__psrc__;(void)src;


    if(this != src) {
      M(this,release);
      yaooc_shared_pointer_acquire(this,src->counter_);
    }
  
}
int yaooc_shared_pointer_rich_compare(const_pointer __plhs__,const_pointer __prhs__)
{
yaooc_shared_pointer_const_pointer lhs=__plhs__;(void)lhs;
yaooc_shared_pointer_const_pointer rhs=__prhs__;(void)rhs;

    return op_rich_compare(M(lhs,get),M(rhs,get));
  
}
void yaooc_shared_pointer_ctor_ptr(pointer __pthis,va_list __con_args__){
yaooc_shared_pointer_pointer this=__pthis;(void)this;
pointer value = va_arg(__con_args__,pointer);

call_default_ctor_static(this,yaooc_shared_pointer);


    call_default_ctor_static(this,yaooc_shared_pointer);
    M(this,reset,value);
  
}
void yaooc_shared_pointer_acquire(pointer __pthis__,yaooc_counter_t* c)
{
yaooc_shared_pointer_pointer this=__pthis__;(void)this;

    this->counter_=c;
    if(c)
      ++c->count_;
  
}
void yaooc_shared_pointer_swap(pointer __pthis__,pointer o)
{
yaooc_shared_pointer_pointer this=__pthis__;(void)this;
#define super() yaooc_shared_pointer_parent_class_table->swap(this,o)
#define PM(method,...) CTM((*yaooc_shared_pointer_parent_class_table),this,method,## __VA_ARGS__)


    yaooc_shared_pointer_t* other=o;
    SWAP(yaooc_counter_t*,this->counter_,other->counter_);
  
#undef PM
#undef super
}
pointer yaooc_shared_pointer_get(const_pointer __pthis__)
{
yaooc_shared_pointer_const_pointer this=__pthis__;(void)this;
#define super() yaooc_shared_pointer_parent_class_table->get(this)
#define PM(method,...) CTM((*yaooc_shared_pointer_parent_class_table),this,method,## __VA_ARGS__)


    return this->counter_ ? this->counter_->ptr_ : NULL;
  
#undef PM
#undef super
}
pointer yaooc_shared_pointer_release(pointer __pthis__)
{
yaooc_shared_pointer_pointer this=__pthis__;(void)this;
#define super() yaooc_shared_pointer_parent_class_table->release(this)
#define PM(method,...) CTM((*yaooc_shared_pointer_parent_class_table),this,method,## __VA_ARGS__)


    pointer ret=M(this,get);
    if(this->counter_) {
      if(--this->counter_->count_ == 0) {
        delete(this->counter_->ptr_);
        delete(this->counter_);
      }
      this->counter_=NULL;
    }
    return ret;
  
#undef PM
#undef super
}
void yaooc_shared_pointer_reset(pointer __pthis__,pointer ptr)
{
yaooc_shared_pointer_pointer this=__pthis__;(void)this;
#define super() yaooc_shared_pointer_parent_class_table->reset(this,ptr)
#define PM(method,...) CTM((*yaooc_shared_pointer_parent_class_table),this,method,## __VA_ARGS__)


    M(this,release);
    if(ptr != NULL)
      this->counter_=new_ctor(yaooc_counter,yaooc_counter_ctor_ptr,ptr);
  
#undef PM
#undef super
}
size_t yaooc_shared_pointer_count(const_pointer __pthis__)
{
yaooc_shared_pointer_const_pointer this=__pthis__;(void)this;
#define super() yaooc_shared_pointer_parent_class_table->count(this)
#define PM(method,...) CTM((*yaooc_shared_pointer_parent_class_table),this,method,## __VA_ARGS__)


    return this->counter_ ? this->counter_->count_  : 0;
  
#undef PM
#undef super
}
yaooc_shared_pointer_class_table_t yaooc_shared_pointer_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_object_class_table,
.type_name_ = (const char*)"yaooc_shared_pointer_t",
.swap = (void(*)(pointer,pointer)) yaooc_shared_pointer_swap,
.get = (pointer(*)(const_pointer)) yaooc_shared_pointer_get,
.release = (pointer(*)(pointer)) yaooc_shared_pointer_release,
.reset = (void(*)(pointer,pointer)) yaooc_shared_pointer_reset,
.count = (size_t(*)(const_pointer)) yaooc_shared_pointer_count,
};
const type_info_t __yaooc_shared_pointer_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_shared_pointer_t),
.rich_compare_=yaooc_shared_pointer_rich_compare,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaooc_shared_pointer_default_ctor,
.dtor_=yaooc_shared_pointer_dtor,
.copy_ctor_=yaooc_shared_pointer_copy_ctor,
.assign_=yaooc_shared_pointer_assign,
.class_table_=(const class_table_t*) &yaooc_shared_pointer_class_table,
.parent_=&__yaooc_object_ti
};
const type_info_t* const yaooc_shared_pointer_ti=&__yaooc_shared_pointer_ti;
