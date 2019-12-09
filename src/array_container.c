#include <yaooc/array_container.h>
#include <string.h>


static void yaooc_array_container_destroy_elements(pointer);
static void yaooc_array_container_destroy_elements(pointer __pthis__)
{
yaooc_array_container_pointer this=__pthis__;(void)this;
#define super() yaooc_array_container_parent_class_table->destroy_elements(this)
#define PM(method,...) CTM((*yaooc_array_container_parent_class_table),this,method,## __VA_ARGS__)


      __deletep_array(this->array_,this->type_info_,this->size_);
      this->size_=0;
    
#undef PM
#undef super
}
void yaooc_array_container_default_ctor(pointer __pthis__)
{
yaooc_array_container_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_array_container);



      throw_yaooc_array_container_exception(this,"Default constructor for yaooc_array_container called.\n"
        "Object type contained in array must be specified");
    
}
void yaooc_array_container_dtor(pointer __pthis__)
{
yaooc_array_container_pointer this=__pthis__;(void)this;


      yaooc_array_container_destroy_elements(this);
      if(this->array_)
         FREE(this->array_);
      this->array_ = NULL;
      this->size_=0;
      this->capacity_=0;
    
}
void yaooc_array_container_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaooc_array_container_pointer this=__pthis__;(void)this;
yaooc_array_container_const_pointer src=__psrc__;(void)src;

call_constructor(this,yaooc_array_container_ctor_ti,src->type_info_);


      yaooc_array_container_assign(this,src);
    
}
void yaooc_array_container_assign(pointer __pthis__,const_pointer __psrc__)
{
yaooc_array_container_pointer this=__pthis__;(void)this;
yaooc_array_container_const_pointer src=__psrc__;(void)src;


      yaooc_array_container_clear(this);
      yaooc_array_container_reserve(this,SIZE(src));
      yaooc_array_container_insert_range(this,BEGIN(this),BEGIN(src),END(src));

    
}
int yaooc_array_container_rich_compare(const_pointer __plhs__,const_pointer __prhs__)
{
yaooc_array_container_const_pointer lhs=__plhs__;(void)lhs;
yaooc_array_container_const_pointer rhs=__prhs__;(void)rhs;

      size_t n=M(lhs,size)<M(rhs,size) ? M(lhs,size) : M(rhs,size);
      size_t i;
      rich_compare rich_cmp=get_rich_compare(TYPE_INFO(lhs));
      if(rich_cmp) {
        for(i=0;i<n;i++) {
          int rc = rich_cmp(AT(lhs,i),AT(rhs,i));
          if(rc < 0)
             return -1;
          if(rc > 0)
            return 1;
        }
      }
      
      return (int)(M(lhs,size) - M(rhs,size));
    
}
void yaooc_array_container_to_stream(const_pointer __pthis__,ostream_pointer __pstrm__)
{
yaooc_array_container_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__pstrm__;(void)ostrm;

      yaooc_private_const_iterator i;
      to_stream to_stream_method=get_to_stream(TYPE_INFO(this));
      if(to_stream_method != NULL) {
        size_t type_size=TYPE_SIZE(this);
        for(i=M(this,cbegin);i!=M(this,cend);i+=type_size)
          to_stream_method(i,ostrm);
      }
    
}
void yaooc_array_container_ctor_ti(pointer __pthis,va_list __con_args__){
yaooc_array_container_pointer this=__pthis;(void)this;
const type_info_t* ti = va_arg(__con_args__,const type_info_t*);

call_parent_default_ctor_static(this,yaooc_array_container);


      this->array_ = NULL;
      this->type_info_ = ti;
      this->size_=0;
      this->capacity_=0;
    
}
iterator yaooc_array_container_insert_space(pointer __pthis__,const_iterator pos,size_t n)
{
yaooc_array_container_pointer this=__pthis__;(void)this;

      size_t index=INDEX(this,pos);  
      debug(DEBUG_ARRAY_CONTAINER) {
        debug_printf("this: %p pos: index: %zu n: %zu  this_array: %p  this_size: %zu this_cap: %zu\n",
              this,index,n,BEGIN(this),SIZE(this),CAPACITY(this));
      }
      M(this,increase_capacity,n);
      yaooc_private_iterator ret = AT(this,index);
      memmove(ret+n*TYPE_SIZE(this),ret,(this->size_-index)*TYPE_SIZE(this));
      this->size_+=n;
      return ret;
    
}
iterator yaooc_array_container_erase_space(pointer __pthis__,const_iterator pos,size_t n)
{
yaooc_array_container_pointer this=__pthis__;(void)this;

      yaooc_private_iterator ret=(yaooc_private_iterator)pos;
      size_t index=INDEX(this,pos);
      memmove(ret,ret+n*TYPE_SIZE(this),(SIZE(this)-index-n)*TYPE_SIZE(this));
      this->size_-=n;
      return ret;
    
}
iterator yaooc_array_container_replace_space(pointer __pthis__,const_iterator first,const_iterator last,size_t count)
{
yaooc_array_container_pointer this=__pthis__;(void)this;

      size_t index=INDEX(this,first);
      size_t n = DISTANCE(TYPE_INFO(this),first,last);
      if(n < count) {
        yaooc_array_container_insert_space(this,AT(this,index+n),count-n);
      } else if(n > count) {
        yaooc_array_container_erase_space(this,AT(this,index+count),n-count);
      }
      return AT(this,index);
    
}
iterator yaooc_array_container_find(pointer __pthis__,const_pointer value)
{
yaooc_array_container_pointer this=__pthis__;(void)this;

      return __yaooc_find(TYPE_INFO(this),BEGIN(this),END(this),value);
    
}
iterator yaooc_array_container_insert(pointer __pthis__,const_iterator pos,const_pointer value)
{
yaooc_array_container_pointer this=__pthis__;(void)this;

      return yaooc_array_container_insertn(this,pos,1,value);
    
}
iterator yaooc_array_container_insertn(pointer __pthis__,const_iterator pos,size_t n,const_pointer val)
{
yaooc_array_container_pointer this=__pthis__;(void)this;

      yaooc_private_iterator ret=yaooc_array_container_insert_space(this,pos,n);
      __newp_array_copy_static(ret,TYPE_INFO(this),val,n);
      return ret;
    
}
iterator yaooc_array_container_insert_range(pointer __pthis__,const_iterator pos,const_iterator f,const_iterator l)
{
yaooc_array_container_pointer this=__pthis__;(void)this;

      size_t n=DISTANCE(TYPE_INFO(this),f,l);
      yaooc_private_iterator dpos=yaooc_array_container_insert_space(this,pos,n);
      __newp_array_copy_range_static(dpos,TYPE_INFO(this),f,n);
      return dpos;
    
}
iterator yaooc_array_container_erase(pointer __pthis__,const_iterator pos)
{
yaooc_array_container_pointer this=__pthis__;(void)this;

      return yaooc_array_container_erase_range(this,pos,((yaooc_private_const_iterator)pos)+yaooc_sizeof(TYPE_INFO(this)));
    
}
iterator yaooc_array_container_erase_range(pointer __pthis__,const_iterator f,const_iterator l)
{
yaooc_array_container_pointer this=__pthis__;(void)this;

      iterator ret=(iterator)f;
      size_t n=DISTANCE(TYPE_INFO(this),f,l);
      __deletep_array(ret,TYPE_INFO(this),n);
      return yaooc_array_container_erase_space(this,f,n);
    
}
size_t yaooc_array_container_erase_value(pointer __pthis__,const_pointer value)
{
yaooc_array_container_pointer this=__pthis__;(void)this;

      size_t ret=0;
      yaooc_private_iterator pos=END(this)-TYPE_SIZE(this);
      rich_compare rich_cmp = get_rich_compare(this->type_info_);
      while(pos >= BEGIN(this) && SIZE(this)>0) {
        if(__op_eq__(pos,value,rich_cmp)) {
          __deletep_array(pos,this->type_info_,1);
          yaooc_array_container_erase_space(this,pos,1);
          ret++;
        }
        pos-=TYPE_SIZE(this);
      }
      return ret;
    
}
iterator yaooc_array_container_at(const_pointer __pthis__,size_t i)
{
yaooc_array_container_const_pointer this=__pthis__;(void)this;

      return AT(this,i);
    
}
void yaooc_array_container_shrink_to_fit(pointer __pthis__)
{
yaooc_array_container_pointer this=__pthis__;(void)this;

      
      if(this->capacity_ > YAOOC_ARRAY_CONTAINER_INITIAL_CAPACITY && this->size_ < this->capacity_) {
        size_t new_cap = YAOOC_ARRAY_CONTAINER_INITIAL_CAPACITY;
        while(new_cap < this->size_) new_cap <<= 1;
        if(new_cap != this->capacity_) {
          this->array_=REALLOC(this->array_,M(this,size_needed,this->capacity_=new_cap));
        }
      }
    
}
void yaooc_array_container_reserve(pointer __pthis__,size_t n)
{
yaooc_array_container_pointer this=__pthis__;(void)this;

      if(n > this->capacity_)
        M(this,increase_capacity,n-this->capacity_);
    
}
void yaooc_array_container_resize(pointer __pthis__,size_t n)
{
yaooc_array_container_pointer this=__pthis__;(void)this;

      pointer temp=__new_array(TYPE_INFO(this),1);
      yaooc_array_container_resize_value(this,n,temp);
      delete(temp);
    
}
void yaooc_array_container_resize_value(pointer __pthis__,size_t n,const_pointer value)
{
yaooc_array_container_pointer this=__pthis__;(void)this;

      if(n<SIZE(this)) {
        yaooc_array_container_erase_range(this,AT(this,n),END(this));
      } else if(n > SIZE(this)){
        yaooc_array_container_insertn(this,END(this),n-SIZE(this),value);
      }
    
}
void yaooc_array_container_clear(pointer __pthis__)
{
yaooc_array_container_pointer this=__pthis__;(void)this;

      yaooc_array_container_destroy_elements(this);
    
}
void yaooc_array_container_swap(pointer __pthis__,pointer s)
{
yaooc_array_container_pointer this=__pthis__;(void)this;
#define super() yaooc_array_container_parent_class_table->swap(this,s)
#define PM(method,...) CTM((*yaooc_array_container_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_array_container_pointer other=s;
      SWAP(char*,this->array_,other->array_);
      SWAP(size_t,this->size_,other->size_);
      SWAP(size_t,this->capacity_,other->capacity_);
    
#undef PM
#undef super
}
bool yaooc_array_container_increase_capacity(pointer __pthis__,size_t n)
{
yaooc_array_container_pointer this=__pthis__;(void)this;
#define super() yaooc_array_container_parent_class_table->increase_capacity(this,n)
#define PM(method,...) CTM((*yaooc_array_container_parent_class_table),this,method,## __VA_ARGS__)


      size_t capacity_needed = this->size_+n;
      bool ret=false;
      if(capacity_needed > this->capacity_ || this->array_==NULL) {
        this->capacity_=YAOOC_ARRAY_CONTAINER_INITIAL_CAPACITY;
        while(capacity_needed > this->capacity_) this->capacity_ <<= 1;
        this->array_=REALLOC(this->array_,M(this,size_needed,this->capacity_));
        ret=true;
      }
      return ret;
    
#undef PM
#undef super
}
size_t yaooc_array_container_size_needed(const_pointer __pthis__,size_t n)
{
yaooc_array_container_const_pointer this=__pthis__;(void)this;
#define super() yaooc_array_container_parent_class_table->size_needed(this,n)
#define PM(method,...) CTM((*yaooc_array_container_parent_class_table),this,method,## __VA_ARGS__)


      return n*TYPE_SIZE(this);
    
#undef PM
#undef super
}
size_t yaooc_array_container_size(const_pointer __pthis__)
{
yaooc_array_container_const_pointer this=__pthis__;(void)this;
#define super() yaooc_array_container_parent_class_table->size(this)
#define PM(method,...) CTM((*yaooc_array_container_parent_class_table),this,method,## __VA_ARGS__)


      return SIZE(this);
    
#undef PM
#undef super
}
size_t yaooc_array_container_capacity(const_pointer __pthis__)
{
yaooc_array_container_const_pointer this=__pthis__;(void)this;
#define super() yaooc_array_container_parent_class_table->capacity(this)
#define PM(method,...) CTM((*yaooc_array_container_parent_class_table),this,method,## __VA_ARGS__)


      return CAPACITY(this);
    
#undef PM
#undef super
}
bool yaooc_array_container_empty(const_pointer __pthis__)
{
yaooc_array_container_const_pointer this=__pthis__;(void)this;
#define super() yaooc_array_container_parent_class_table->empty(this)
#define PM(method,...) CTM((*yaooc_array_container_parent_class_table),this,method,## __VA_ARGS__)


      return SIZE(this)==0;
    
#undef PM
#undef super
}
iterator yaooc_array_container_begin(pointer __pthis__)
{
yaooc_array_container_pointer this=__pthis__;(void)this;
#define super() yaooc_array_container_parent_class_table->begin(this)
#define PM(method,...) CTM((*yaooc_array_container_parent_class_table),this,method,## __VA_ARGS__)


      return BEGIN(this);
    
#undef PM
#undef super
}
iterator yaooc_array_container_end(pointer __pthis__)
{
yaooc_array_container_pointer this=__pthis__;(void)this;
#define super() yaooc_array_container_parent_class_table->end(this)
#define PM(method,...) CTM((*yaooc_array_container_parent_class_table),this,method,## __VA_ARGS__)


      return END(this);
    
#undef PM
#undef super
}
yaooc_array_container_class_table_t yaooc_array_container_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_object_class_table,
.type_name_ = (const char*)"yaooc_array_container_t",
.swap = (void(*)(pointer,pointer)) yaooc_array_container_swap,
.increase_capacity = (bool(*)(pointer,size_t)) yaooc_array_container_increase_capacity,
.size_needed = (size_t(*)(const_pointer,size_t)) yaooc_array_container_size_needed,
.size = (size_t(*)(const_pointer)) yaooc_array_container_size,
.capacity = (size_t(*)(const_pointer)) yaooc_array_container_capacity,
.empty = (bool(*)(const_pointer)) yaooc_array_container_empty,
.begin = (iterator(*)(pointer)) yaooc_array_container_begin,
.end = (iterator(*)(pointer)) yaooc_array_container_end,
.cbegin = (const_iterator(*)(const_pointer)) yaooc_array_container_cbegin,
.cend = (const_iterator(*)(const_pointer)) yaooc_array_container_cend,
};
const type_info_t __yaooc_array_container_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_array_container_t),
.rich_compare_=yaooc_array_container_rich_compare,
.to_stream_=yaooc_array_container_to_stream,
.from_stream_=NULL,
.default_ctor_=yaooc_array_container_default_ctor,
.dtor_=yaooc_array_container_dtor,
.copy_ctor_=yaooc_array_container_copy_ctor,
.assign_=yaooc_array_container_assign,
.class_table_=(const class_table_t*) &yaooc_array_container_class_table,
.parent_=&__yaooc_object_ti
};
const type_info_t* const yaooc_array_container_ti=&__yaooc_array_container_ti;
