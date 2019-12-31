#include <yaooc/variant.h>
#include <string.h>


void yaooc_variant_default_ctor(pointer __pthis__)
{
yaooc_variant_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_variant);



    this->type_=VAR_NONE;
    this->chr_ptr_=NULL;
  
}
void yaooc_variant_dtor(pointer __pthis__)
{
yaooc_variant_pointer this=__pthis__;(void)this;


    switch(this->type_) {

      case VAR_NONE:
      case VAR_CHAR:
      case VAR_UCHAR:
      case VAR_SHORT:
      case VAR_USHORT:
      case VAR_INT:
      case VAR_UINT:
      case VAR_LONG:
      case VAR_ULONG:
      case VAR_DOUBLE:
        break;

      case VAR_CHAR_PTR:
      case VAR_VOID_PTR:
        FREE(this->chr_ptr_);
        break;

      case VAR_OBJECT_PTR:
        delete(this->obj_ptr_);
        break;
    }
    this->type_=VAR_NONE;
    this->chr_ptr_=NULL;
  
}
void yaooc_variant_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaooc_variant_pointer this=__pthis__;(void)this;
yaooc_variant_const_pointer src=__psrc__;(void)src;


call_default_ctor_static(this,yaooc_variant);
assign_static(this,src,yaooc_variant);

}
void yaooc_variant_assign(pointer __pthis__,const_pointer __psrc__)
{
yaooc_variant_pointer this=__pthis__;(void)this;
yaooc_variant_const_pointer src=__psrc__;(void)src;


    M(this,set,src->type_,M(src,value));
  
}
void yaooc_variant_swap(pointer __pthis__,pointer o)
{
yaooc_variant_pointer this=__pthis__;(void)this;
#define super() yaooc_variant_parent_class_table->swap(this,o)
#define PM(method,...) CTM((*yaooc_variant_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_variant_t* other=o;
      SWAP(yaooc_variant_type_t,this->type_,this->type_);
      SWAP(double,this->dbl_,other->dbl_);
    
#undef PM
#undef super
}
void yaooc_variant_set(pointer __pthis__,yaooc_variant_type_t t,const void* value)
{
yaooc_variant_pointer this=__pthis__;(void)this;
#define super() yaooc_variant_parent_class_table->set(this,t,value)
#define PM(method,...) CTM((*yaooc_variant_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_variant_dtor(this);
      switch(t) {
        case VAR_NONE:
          break;

        case VAR_CHAR:
        case VAR_UCHAR:
          this->ch_=*(const char*)value;
          break;

        case VAR_SHORT:
        case VAR_USHORT:
          this->sh_=*(const short*)value;
          break;

        case VAR_INT:
        case VAR_UINT:
          this->int_=*(const int*)value;
          break;

        case VAR_LONG:
        case VAR_ULONG:
          this->long_=*(const long long*)value;
          break;

        case VAR_DOUBLE:
          this->dbl_=*(const double*)value;
          break;

        case VAR_CHAR_PTR:
          this->chr_ptr_=STRDUP(value);
          break;

        case VAR_VOID_PTR:
          this->void_ptr_=(void*)value;
          break;

        case VAR_OBJECT_PTR:
          this->obj_ptr_=new_copy(value);
          break;
      }
      this->type_=t;
    
#undef PM
#undef super
}
const void* yaooc_variant_value(const_pointer __pthis__)
{
yaooc_variant_const_pointer this=__pthis__;(void)this;
#define super() yaooc_variant_parent_class_table->value(this)
#define PM(method,...) CTM((*yaooc_variant_parent_class_table),this,method,## __VA_ARGS__)


      return this->chr_ptr_;
    
#undef PM
#undef super
}
yaooc_variant_class_table_t yaooc_variant_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_object_class_table,
.type_name_ = (const char*)"yaooc_variant_t",
.swap = (void(*)(pointer,pointer)) yaooc_variant_swap,
.set = (void(*)(pointer,yaooc_variant_type_t,const void*)) yaooc_variant_set,
.value = (const void*(*)(const_pointer)) yaooc_variant_value,
};
const type_info_t __yaooc_variant_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_variant_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaooc_variant_default_ctor,
.dtor_=yaooc_variant_dtor,
.copy_ctor_=yaooc_variant_copy_ctor,
.assign_=yaooc_variant_assign,
.class_table_=(const class_table_t*) &yaooc_variant_class_table,
.parent_=&__yaooc_object_ti
};
const type_info_t* const yaooc_variant_ti=&__yaooc_variant_ti;
