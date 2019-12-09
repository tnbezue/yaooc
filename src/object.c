#include <yaooc/object.h>
#include <stdio.h>
#include <string.h>


bool yaooc_object_isa(const_pointer __pthis__,const char* s)
{
yaooc_object_const_pointer this=__pthis__;(void)this;

      const yaooc_object_class_table_t* current_class_table=(yaooc_object_class_table_t*)(((yaooc_object_pointer)this)->class_table_);
      while(current_class_table != NULL) {
        if(strcmp(current_class_table->type_name_,s) == 0)
          return true;
        current_class_table=(const yaooc_object_class_table_t*)current_class_table->parent_class_table_;
      }
      return false;
    
}
void yaooc_object_swap(pointer __pthis__,pointer s)
{
yaooc_object_pointer this=__pthis__;(void)this;
#define super() yaooc_object_parent_class_table->swap(this,s)
#define PM(method,...) CTM((*yaooc_object_parent_class_table),this,method,## __VA_ARGS__)

 
#undef PM
#undef super
}
yaooc_object_class_table_t yaooc_object_class_table ={
.parent_class_table_ = (const class_table_t*)NULL,
.type_name_ = (const char*)"yaooc_object_t",
.swap = (void(*)(pointer,pointer)) yaooc_object_swap,
};
const type_info_t __yaooc_object_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_object_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=NULL,
.dtor_=NULL,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaooc_object_class_table,
.parent_=NULL
};
const type_info_t* const yaooc_object_ti=&__yaooc_object_ti;
void yaooc_pure_virtual(const char* method,const char* cls)
{
  fprintf(stderr,"Pure virtual method %s for class %s called.\n",method,cls);
  abort();
}

