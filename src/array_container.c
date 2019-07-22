/* Begin YAOOCPP output */

#include <yaooc/array_container.h>


#include <yaooc/algorithm.h>
#include <yaooc/stream.h>
#include <string.h>

/* Private variables implementation for yaooc_array_container */

/* Private methods prototypes for yaooc_array_container */
static void yaooc_array_container_destroy_elements(pointer p);

/* Type Info implemmentation for yaooc_array_container */
void yaooc_array_container_default_ctor(pointer p)
{
	THROW(new_ctor(yaooc_exception,yaooc_exception_ctor_v,"Cannot create an array without type info"));
}

void yaooc_array_container_dtor(pointer p)
{
  yaooc_array_container_pointer this=p;
	yaooc_array_container_destroy_elements(this);
/*	yaooc_array_container_clear(this);
//	M(this,clear);*/
  if(this->array_)
     FREE(this->array_);
  this->array_ = NULL;
  this->size_=0;
  this->capacity_=0;
}

void yaooc_array_container_copy_ctor(pointer p,const_pointer s)
{
  yaooc_array_container_const_pointer src=s;
  call_constructor(p,yaooc_array_container_ctor_ti,src->type_info_);
  yaooc_array_container_assign(p,s);
}

void yaooc_array_container_assign(pointer p,const_pointer s)
{
	yaooc_array_container_clear(p);
	yaooc_array_container_reserve(p,SIZE(s));
	yaooc_array_container_insert_range(p,BEGIN(p),BEGIN(s),END(s));
}

bool yaooc_array_container_less_than_compare(const_pointer p1,const_pointer p2)
{
  yaooc_array_container_const_pointer lhs=p1;
  yaooc_array_container_const_pointer rhs=p2;
  size_t n=M(lhs,size)<M(rhs,size) ? M(lhs,size) : M(rhs,size);
  size_t i;
  less_than_compare lt_cmp=get_lt_cmp(TYPE_INFO(lhs));
  for(i=0;i<n;i++) {
    if(lt_cmp(AT(lhs,i),AT(rhs,i)))
       return true;
    if(lt_cmp(AT(rhs,i),AT(lhs,i)))
      return false;
  }
  return M(lhs,size) < M(rhs,size);
}

void yaooc_array_container_to_stream(const_pointer p,ostream_pointer o){
  yaooc_array_container_const_pointer this=p;
  yaooc_ostream_pointer ostrm=o;
	yaooc_private_const_iterator i;
	size_t type_size=TYPE_SIZE(this);
	for(i=M(this,cbegin);i!=M(this,cend);i+=type_size) {
		STREAM(ostrm,__S_OBJ(TYPE_INFO(this)),i);
	}
}

/* Constructors implementation for yaooc_array_container */
void yaooc_array_container_ctor_ti(pointer p,va_list args)
{
  yaooc_array_container_pointer this=p;
  this->array_ = NULL;
  this->type_info_ = va_arg(args, const type_info_t*);
  this->size_=0;
  this->capacity_=0;
}


/* Private methods implementation for yaooc_array_container */
static void yaooc_array_container_destroy_elements(pointer p)
{
  yaooc_array_container_pointer this=p;
	if(!is_pod_type(this->type_info_) && this->size_ > 0) {
		__deletep_array(this->array_,this->type_info_,this->size_);
	}
	this->size_=0;
}
/* Protected implementation for yaooc_array_container */
iterator yaooc_array_container_insert_space(pointer p,const_iterator pos,size_t n)
{
  yaooc_array_container_pointer this=p;
  size_t index=INDEX(this,pos);  /* Save index because increase capacity may move array */
  debug(DEBUG_ARRAY_CONTAINER) {
    debug_printf("this: %p pos: index: %zu n: %zu  this_array: %p  this_size: %zu this_cap: %zu\n",
          p,index,n,BEGIN(p),SIZE(p),CAPACITY(p));
  }
  M(this,increase_capacity,n);
  yaooc_private_iterator ret = AT(p,index);
  memmove(ret+n*TYPE_SIZE(p),ret,(this->size_-index)*TYPE_SIZE(p));
  this->size_+=n;
  return ret;
}

iterator yaooc_array_container_erase_space(pointer p,const_iterator pos,size_t n)
{
  yaooc_array_container_pointer this=p;
  yaooc_private_iterator ret=(yaooc_private_iterator)pos;
  size_t index=INDEX(p,pos);
  memmove(ret,ret+n*TYPE_SIZE(p),(SIZE(p)-index-n)*TYPE_SIZE(p));
  this->size_-=n;
  return ret;
}

iterator yaooc_array_container_replace_space(pointer p,const_iterator f,const_iterator l,size_t count)
{
  yaooc_array_container_pointer this=p;
  size_t index=INDEX(p,f);
  size_t n = DISTANCE(TYPE_INFO(p),f,l);
  if(n < count ) {
    yaooc_array_container_insert_space(this,AT(p,index+n),count-n);
  } else if(n > count) {
    yaooc_array_container_erase_space(this,AT(p,index+count),n-count);
  }
  return AT(this,index);
}

iterator yaooc_array_container_find(pointer p,const_pointer value)
{
	return __yaooc_find(TYPE_INFO(p),BEGIN(p),END(p),value);
}

iterator yaooc_array_container_insert(pointer p,const_iterator pos,const_pointer value)
{
  return yaooc_array_container_insertn(p,pos,1,value);
}

iterator yaooc_array_container_insertn(pointer p,const_iterator pos,size_t n,const_pointer val)
{
  yaooc_private_iterator ret=yaooc_array_container_insert_space(p,pos,n);
  __newp_array_copy_static(ret,TYPE_INFO(p),val,n);
  return ret;
}

iterator yaooc_array_container_insert_range(pointer p,const_iterator pos,const_iterator f,const_iterator l)
{
  size_t n=DISTANCE(TYPE_INFO(p),f,l);
  yaooc_private_iterator dpos=yaooc_array_container_insert_space(p,pos,n);
  __newp_array_copy_range_static(dpos,TYPE_INFO(p),f,n);
  return dpos;
}

iterator yaooc_array_container_erase(pointer p,const_iterator pos)
{
	return yaooc_array_container_erase_range(p,pos,((yaooc_private_const_iterator)pos)+yaooc_sizeof(TYPE_INFO(p)));
}

iterator yaooc_array_container_erase_range(pointer p,const_iterator f,const_iterator l)
{
  iterator ret=(iterator)f;
  size_t n=DISTANCE(TYPE_INFO(p),f,l);
  __deletep_array(ret,TYPE_INFO(p),n);
  return yaooc_array_container_erase_space(p,f,n);
}

size_t yaooc_array_container_erase_value(pointer p,const_pointer value)
{
  yaooc_array_container_pointer this=p;
  size_t ret=0;
  yaooc_private_iterator pos=END(this)-TYPE_SIZE(this);
  less_than_compare lt_cmp = get_lt_cmp(this->type_info_);
  while(pos >= BEGIN(this) && SIZE(this)>0) {
    if(__op_eq__(pos,value,lt_cmp)) {
      __deletep_array(pos,this->type_info_,1);
      yaooc_array_container_erase_space(this,pos,1);
      ret++;
    }
    pos-=TYPE_SIZE(this);
  }
  return ret;
}

iterator yaooc_array_container_at(const_pointer p,size_t i)
{
  return AT(p,i);
}

void yaooc_array_container_shrink_to_fit(pointer p)
{
  yaooc_array_container_pointer this=p;
  // Don't shrink to less than INITIAL_CAPACITY
  if(this->capacity_ > YAOOC_ARRAY_CONTAINER_INITIAL_CAPACITY && this->size_ < this->capacity_) {
		size_t new_cap = YAOOC_ARRAY_CONTAINER_INITIAL_CAPACITY;
		while(new_cap < this->size_) new_cap <<= 1;
		if(new_cap != this->capacity_) {
			this->array_=REALLOC(this->array_,M(this,size_needed,this->capacity_=new_cap));
		}
  }
}

void yaooc_array_container_reserve(pointer p,size_t n)
{
  yaooc_array_container_pointer this=p;
  if(n > this->capacity_)
    M(this,increase_capacity,n-this->capacity_);
}

void yaooc_array_container_resize(pointer p,size_t n)
{
  pointer temp=__new_array(TYPE_INFO(p),1);
  yaooc_array_container_resize_value(p,n,temp);
  delete(temp);
}

void yaooc_array_container_resize_value(pointer p,size_t n,const_pointer value)
{
  if(n<SIZE(p)) {
    yaooc_array_container_erase_range(p,AT(p,n),END(p));
  } else if(n > SIZE(p)){
    yaooc_array_container_insertn(p,END(p),n-SIZE(p),value);
  }
}

void yaooc_array_container_clear(pointer p)
{
//  yaooc_array_container_pointer this=p;
	yaooc_array_container_destroy_elements(p);
}


/* Table implementation for yaooc_array_container */
void yaooc_array_container_swap(pointer p,pointer p2)
{
  yaooc_array_container_pointer this=p;
  yaooc_array_container_pointer other=p2;
  SWAP(char*,this->array_,other->array_);
  SWAP(size_t,this->size_,other->size_);
  SWAP(size_t,this->capacity_,other->capacity_);
}

bool yaooc_array_container_increase_capacity(pointer p,size_t n)
{
  yaooc_array_container_pointer this=p;
  size_t capacity_needed = this->size_+n;
  bool ret=false;
  if(capacity_needed > this->capacity_ || this->array_==NULL) {
    this->capacity_=YAOOC_ARRAY_CONTAINER_INITIAL_CAPACITY;
    while(capacity_needed > this->capacity_) this->capacity_ <<= 1;
    this->array_=REALLOC(this->array_,M(this,size_needed,this->capacity_));
    ret=true;
  }
  return ret;
}

size_t yaooc_array_container_size_needed(const_pointer p,size_t n)
{
  return n*TYPE_SIZE(p);
}

size_t yaooc_array_container_size(const_pointer p)
{
	return SIZE(p);
}

size_t yaooc_array_container_capacity(const_pointer p)
{
	return CAPACITY(p);
}

bool yaooc_array_container_empty(const_pointer p)
{
  return SIZE(p)==0;
}

iterator yaooc_array_container_begin(pointer p)
{
  return BEGIN(p);
}

iterator yaooc_array_container_end(pointer p)
{
	return END(p);
}

const_iterator yaooc_array_container_cbegin(const_pointer p)
{
	return (const_iterator)BEGIN(p);
}

const_iterator yaooc_array_container_cend(const_pointer p)
{
	return (const_iterator)END(p);
}


/* Class table definition for yaooc_array_container */
yaooc_array_container_class_table_t yaooc_array_container_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
  .type_name_ = (const char*) "yaooc_array_container_t",
  .swap = (void(*)(pointer, pointer)) yaooc_array_container_swap,
  .increase_capacity = (bool(*)(pointer, size_t)) yaooc_array_container_increase_capacity,
  .size_needed = (size_t(*)(const_pointer, size_t)) yaooc_array_container_size_needed,
  .size = (size_t(*)(const_pointer)) yaooc_array_container_size,
  .capacity = (size_t(*)(const_pointer)) yaooc_array_container_capacity,
  .empty = (bool(*)(const_pointer)) yaooc_array_container_empty,
  .begin = (iterator(*)(pointer)) yaooc_array_container_begin,
  .end = (iterator(*)(pointer)) yaooc_array_container_end,
  .cbegin = (const_iterator(*)(const_pointer)) yaooc_array_container_cbegin,
  .cend = (const_iterator(*)(const_pointer)) yaooc_array_container_cend,
};

/* Type info structure for yaooc_array_container */
DEFINE_TYPE_INFO(yaooc_array_container,Y,Y,Y,Y,Y,Y,N,Y,yaooc_object);

/* End YAOOCPP output */

