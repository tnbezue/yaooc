#ifndef __EXCEPTION_INCLUDED__
#define __EXCEPTION_INCLUDED__
#include <yaooc/new.h>
#include <yaooc/object.h>
#include <setjmp.h>

yaooc_class_table(yaooc_exception) {
  yaooc_object_class_table_t;
const char* (*what)(const_pointer);
int (*error_code)(const_pointer);
};
#define yaooc_exception_parent_class_table ((yaooc_object_class_table_t*)(yaooc_exception_class_table.parent_class_table_))

yaooc_class_instance(yaooc_exception) {
char* what_;
int error_code_;
};

yaooc_class(yaooc_exception);
void yaooc_exception_default_ctor(pointer);
void yaooc_exception_dtor(pointer);
void yaooc_exception_copy_ctor(pointer,const_pointer);
void yaooc_exception_assign(pointer,const_pointer);
void yaooc_exception_ctor_v(pointer,va_list);
#define yaooc_exception_swap yaooc_object_swap
 const char* yaooc_exception_what(const_pointer);
 int yaooc_exception_error_code(const_pointer);
void __yaooc_exception_handled__();

jmp_buf* yaooc_jmpbuf_new();
yaooc_exception_pointer yaooc_exception_current_exception_thrown();
void __throw__(pointer);
bool __catch__(const char*);
void __rethrow_last_exception__();

pointer yaooc_exception_garbage_bag_save(pointer);
pointer yaooc_exception_garbage_bag_save_static_array(pointer,const type_info_t*,size_t);
void yaooc_exception_garbage_bag_clear();
void yaooc_exception_garbage_bag_delete();




#define THROW(e) \
    __throw__(e)

#define TRY if(setjmp(*yaooc_jmpbuf_new()) == 0) { \
     {

#define CATCH(exception_type,e) \
     \
    }  \
    __yaooc_exception_handled__(); \
  } else  \
       \
  if(__catch__(# exception_type "_t")) {   { \
    exception_type ## _const_pointer e=(exception_type ## _const_pointer)yaooc_exception_current_exception_thrown(); \
    (void) e;

#define ETRY \
    }  \
     \
    __yaooc_exception_handled__(); \
} else  {\
     \
    __rethrow_last_exception__(); \
}


#define egb_save(ptr) yaooc_exception_garbage_bag_save(ptr)

#define egb_new(T)         egb_save(new(T))
#define egb_new_array(T,N) egb_save(new_array(T,N))
#define egb_new_copy(P)    egb_save(new_copy(P))
#define egb_new_array_copy(P,N)    egb_save(new_array_copy(P,N))
#define egb_new_ctor(T,CON,...)     egb_save(new_ctor(T,CON,## __VA_ARGS__))
#define egb_new_array_ctor(T,N,...)     egb_save(new_array_ctor(T,N,CON,## __VA_ARGS__))

#define egb_save_static(P,T)       yaooc_exception_garbage_bag_save_static_array(P,T ## _ti,1)
#define egb_save_static_array(P,T,N)       yaooc_exception_garbage_bag_save_static_array(P,T ## _ti,N)
#define egb_newp(P,T)      egb_save_static(newp(P,T),T ## _ti,1)
#define egb_newp_array(P,T,N)      egb_save_static_array(newp_array(P,T,N),T ## _ti,N)
#define egb_newp_copy_static(P,T,CP)      egb_save_static(newp_copy_static(P,T,CP),T ## _ti,1)
#define egb_newp_array_copy_static(P,T,CP,N)      egb_save_static_array(newp_array_copy_static(P,T,CP,N),T ## _ti,N)
#define egb_newp_ctor(P,T,CON,...)      egb_save_static(newp_ctor(P,T,CON,## __VA_ARGG__),T ## _ti,1)
#define egb_newp_array_ctor(P,T,N,CON,...)      egb_save_static_array(newp_array_ctor(P,T,N,CON,## __VA_ARGG__),T ## _ti,1)


#define egb_clear()  yaooc_exception_garbage_bag_clear(ptr)
#define egb_delete() yaooc_exception_garbage_bag_delete(ptr)


yaooc_class_table(yaooc_stream_exception) {
  yaooc_exception_class_table_t;
};
#define yaooc_stream_exception_parent_class_table ((yaooc_exception_class_table_t*)(yaooc_stream_exception_class_table.parent_class_table_))

yaooc_class_instance(yaooc_stream_exception) {
  yaooc_exception_class_instance_t;
};

yaooc_class(yaooc_stream_exception);
#define yaooc_stream_exception_ctor_v yaooc_exception_ctor_v
#define yaooc_stream_exception_swap yaooc_exception_swap
#define yaooc_stream_exception_what yaooc_exception_what
#define yaooc_stream_exception_error_code yaooc_exception_error_code
yaooc_class_table(yaooc_array_container_exception) {
  yaooc_exception_class_table_t;
};
#define yaooc_array_container_exception_parent_class_table ((yaooc_exception_class_table_t*)(yaooc_array_container_exception_class_table.parent_class_table_))

yaooc_class_instance(yaooc_array_container_exception) {
  yaooc_exception_class_instance_t;
};

yaooc_class(yaooc_array_container_exception);
#define yaooc_array_container_exception_ctor_v yaooc_exception_ctor_v
#define yaooc_array_container_exception_swap yaooc_exception_swap
#define yaooc_array_container_exception_what yaooc_exception_what
#define yaooc_array_container_exception_error_code yaooc_exception_error_code

#endif
