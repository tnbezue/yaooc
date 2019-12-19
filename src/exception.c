#include <yaooc/exception.h>
#include <yaooc/garbage_bag.h>
#include <stdio.h>
#include <string.h>
#if defined(_WIN32) && !defined(__YAOOC_USE_PTRHEADS)
#include <windows.h>
typedef uintptr_t yaooc_exception_thread_t;
#define yaooc_current_thread_id() (uintptr_t)GetCurrentThread()
#else
#include <pthread.h>
typedef pthread_t yaooc_exception_thread_t;
#define yaooc_current_thread_id() pthread_self()
#endif


void yaooc_exception_default_ctor(pointer __pthis__)
{
yaooc_exception_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_exception);



      this->what_=NULL;
      this->error_code_=0;
    
}
void yaooc_exception_dtor(pointer __pthis__)
{
yaooc_exception_pointer this=__pthis__;(void)this;


      if(this->what_)
        FREE(this->what_);
    
}
void yaooc_exception_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaooc_exception_pointer this=__pthis__;(void)this;
yaooc_exception_const_pointer src=__psrc__;(void)src;

call_default_ctor_static(this,yaooc_exception);


      yaooc_exception_default_ctor(this);
      yaooc_exception_assign(this,src);
    
}
void yaooc_exception_assign(pointer __pthis__,const_pointer __psrc__)
{
yaooc_exception_pointer this=__pthis__;(void)this;
yaooc_exception_const_pointer src=__psrc__;(void)src;


      yaooc_exception_dtor(this);
      this->what_ = src->what_ ? STRDUP(src->what_) : NULL;
    
}
void yaooc_exception_ctor_v(pointer __pthis,va_list __con_args__){
yaooc_exception_pointer this=__pthis;(void)this;
int err_code = va_arg(__con_args__,int);
const char* fmt = va_arg(__con_args__,const char*);
#define args __con_args__
call_default_ctor_static(this,yaooc_exception);


      this->error_code_=err_code;
      if(fmt != NULL) {
        va_list args2;
        va_copy(args2,args);
        int size_needed=vsnprintf(NULL,0,fmt,args2);
        va_end(args2);
        if(size_needed > 0) {
          this->what_=MALLOC(++size_needed);
          vsnprintf(this->what_,size_needed,fmt,args);
        }
      }
    
}
const char* yaooc_exception_what(const_pointer __pthis__)
{
yaooc_exception_const_pointer this=__pthis__;(void)this;
#define super() yaooc_exception_parent_class_table->what(this)
#define PM(method,...) CTM((*yaooc_exception_parent_class_table),this,method,## __VA_ARGS__)


      return this->what_;
    
#undef PM
#undef super
}
int yaooc_exception_error_code(const_pointer __pthis__)
{
yaooc_exception_const_pointer this=__pthis__;(void)this;
#define super() yaooc_exception_parent_class_table->error_code(this)
#define PM(method,...) CTM((*yaooc_exception_parent_class_table),this,method,## __VA_ARGS__)


      return this->error_code_;
    
#undef PM
#undef super
}
yaooc_exception_class_table_t yaooc_exception_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_object_class_table,
.type_name_ = (const char*)"yaooc_exception_t",
.swap = (void(*)(pointer,pointer)) yaooc_exception_swap,
.what = (const char*(*)(const_pointer)) yaooc_exception_what,
.error_code = (int(*)(const_pointer)) yaooc_exception_error_code,
};
const type_info_t __yaooc_exception_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_exception_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaooc_exception_default_ctor,
.dtor_=yaooc_exception_dtor,
.copy_ctor_=yaooc_exception_copy_ctor,
.assign_=yaooc_exception_assign,
.class_table_=(const class_table_t*) &yaooc_exception_class_table,
.parent_=&__yaooc_object_ti
};
const type_info_t* const yaooc_exception_ti=&__yaooc_exception_ti;
typedef struct yaooc_jmpbuf_s yaooc_jmpbuf_t;
struct yaooc_jmpbuf_s {
  jmp_buf jb_;
  yaooc_exception_t* exception_thrown_;
  yaooc_garbage_bag_t* pb_;
  yaooc_jmpbuf_t* prev_;
};
typedef struct yaooc_exception_thread_jmpbuf_node_s yaooc_exception_thread_jmpbuf_node_t;
struct yaooc_exception_thread_jmpbuf_node_s {
  yaooc_exception_thread_jmpbuf_node_t* next_;
  yaooc_exception_thread_t tid_;
  yaooc_jmpbuf_t* current_jmpbuf_;
};


#if defined(_WIN32) && !defined(__YAOOC_USE_PTHREADS)
static CRITICAL_SECTION exception_mutex; 
void init_exceptions() { InitializeCriticalSection(&exception_mutex); }
#else
static pthread_mutex_t exception_mutex  = PTHREAD_MUTEX_INITIALIZER;
void init_exceptions() { }
#endif

void yaooc_exception_remove_jmpbuf(yaooc_exception_thread_t);
void yaooc_exception_thread_list_remove_exception_thread(yaooc_exception_thread_t);

static void yaooc_exception_terminate(yaooc_exception_pointer e);
static void yaooc_jmpbuf_destroy(yaooc_jmpbuf_t*);
yaooc_exception_thread_jmpbuf_node_t* yaooc_exception_thread_jmpbuf_head=NULL;
yaooc_exception_thread_jmpbuf_node_t* yaooc_exception_thread_jmpbuf_tail=NULL;

yaooc_exception_thread_jmpbuf_node_t* yaooc_exception_thread_jmpbuf_list_find_jmpbuf(yaooc_exception_thread_t tid)
{
  yaooc_exception_thread_jmpbuf_node_t* current=yaooc_exception_thread_jmpbuf_head;
  while(current != NULL) {
    if(tid==current->tid_)
      return current;
    current=current->next_;
  }
  return NULL;
}





yaooc_exception_thread_jmpbuf_node_t* yaooc_exception_thread_node_create_thread_list(yaooc_exception_thread_t tid)
{
#if defined(_WIN32) && !defined(_YAOOC_USE_PTHREADS)
  EnterCriticalSection(&exception_mutex);
#else
  pthread_mutex_lock(&exception_mutex);
#endif
  yaooc_exception_thread_jmpbuf_node_t* current=MALLOC(sizeof(yaooc_exception_thread_jmpbuf_node_t));
  current->tid_=tid;
  current->next_=NULL;
  current->current_jmpbuf_=NULL;

  if(yaooc_exception_thread_jmpbuf_head==NULL) {
    yaooc_exception_thread_jmpbuf_head=yaooc_exception_thread_jmpbuf_tail=current;
  } else {
    yaooc_exception_thread_jmpbuf_tail->next_=current;
    yaooc_exception_thread_jmpbuf_tail=current;
  }
#if defined(_WIN32) && !defined(_YAOOC_USE_PTHREADS)
  LeaveCriticalSection(&exception_mutex);
#else
  pthread_mutex_unlock(&exception_mutex);
#endif
  return current;
}




yaooc_exception_thread_jmpbuf_node_t* yaooc_exception_thread_jmpbuf_find_or_create_exception_thread(yaooc_exception_thread_t tid)
{
  yaooc_exception_thread_jmpbuf_node_t* current=yaooc_exception_thread_jmpbuf_list_find_jmpbuf(tid);
  return current ? current : yaooc_exception_thread_node_create_thread_list(tid);
}












void yaooc_exception_thread_list_remove_exception_thread(yaooc_exception_thread_t tid)
{
  yaooc_exception_thread_jmpbuf_node_t* current=yaooc_exception_thread_jmpbuf_head;
  yaooc_exception_thread_jmpbuf_node_t* previous=NULL;
  while(current != NULL) {
    if(tid==current->tid_) {
#if defined(_WIN32) && !defined(_YAOOC_USE_PTHREADS)
      EnterCriticalSection(&exception_mutex);
#else
      pthread_mutex_lock(&exception_mutex);
#endif
      if(previous) {
        previous->next_=current->next_;
        if(current->next_ ==NULL) { 
          yaooc_exception_thread_jmpbuf_tail=previous;
        }
      } else {
        
        yaooc_exception_thread_jmpbuf_head=current->next_;
        if(current->next_ == NULL) {
          
          yaooc_exception_thread_jmpbuf_head=yaooc_exception_thread_jmpbuf_tail=NULL;
        }
      }
#ifdef _WIN32
      LeaveCriticalSection(&exception_mutex);
#else
      pthread_mutex_unlock(&exception_mutex);
#endif

      FREE(current);
      break;
    }
    previous=current;
    current=current->next_;
  }
}

yaooc_jmpbuf_t* yaooc_current_jmpbuf();














jmp_buf* yaooc_jmpbuf_new()
{
  yaooc_exception_thread_jmpbuf_node_t* node=yaooc_exception_thread_jmpbuf_find_or_create_exception_thread(yaooc_current_thread_id());
  yaooc_jmpbuf_t* prev=node->current_jmpbuf_;
  node->current_jmpbuf_=(yaooc_jmpbuf_t*)MALLOC(sizeof(yaooc_jmpbuf_t));
  node->current_jmpbuf_->exception_thrown_=NULL;
  node->current_jmpbuf_->pb_=new(yaooc_garbage_bag);
  node->current_jmpbuf_->prev_=prev;
  return &(node->current_jmpbuf_->jb_);
}




void __yaooc_exception_handled__()
{
  yaooc_exception_thread_jmpbuf_node_t* node=yaooc_exception_thread_jmpbuf_list_find_jmpbuf(yaooc_current_thread_id());
  yaooc_jmpbuf_t* temp=node->current_jmpbuf_;
  node->current_jmpbuf_=temp->prev_;
  yaooc_jmpbuf_destroy(temp);
}






static void yaooc_jmpbuf_destroy(yaooc_jmpbuf_t* jb)
{

  if(jb) {
    delete(jb->pb_);
    if(jb->exception_thrown_)
      delete(jb->exception_thrown_);
    FREE(jb);
  }
}

static void yaooc_exception_terminate(yaooc_exception_pointer e)
{
  fprintf(stderr,"terminate called after throwing %s : %s\n",e->class_table_->type_name_,M(e,what) ? M(e,what) : "");
  delete(e);
  exit(0);
}




void __throw__(pointer e)
{
  yaooc_exception_thread_jmpbuf_node_t* node=yaooc_exception_thread_jmpbuf_list_find_jmpbuf(yaooc_current_thread_id());
  if(node != NULL) { 
    


    while(node->current_jmpbuf_ != NULL && node->current_jmpbuf_->exception_thrown_ != NULL) {
      yaooc_jmpbuf_t* temp=node->current_jmpbuf_;
      node->current_jmpbuf_=temp->prev_;
      yaooc_jmpbuf_destroy(temp);
    }
  }
  if(node ==NULL || node->current_jmpbuf_ == NULL)
    yaooc_exception_terminate(e); 
  node->current_jmpbuf_->exception_thrown_=e;
  longjmp(node->current_jmpbuf_->jb_,1);
}




void __rethrow_last_exception__()
{
  yaooc_exception_thread_jmpbuf_node_t* node=yaooc_exception_thread_jmpbuf_list_find_jmpbuf(yaooc_current_thread_id());
  yaooc_jmpbuf_t* temp =node->current_jmpbuf_;
  pointer e = temp->exception_thrown_;
  temp->exception_thrown_ = NULL;
  node->current_jmpbuf_=temp->prev_;
  yaooc_jmpbuf_destroy(temp);
  __throw__(e);
}

bool __catch__(const char* etype)
{
  return yaooc_object_isa(yaooc_exception_current_exception_thrown(),etype);
}



yaooc_jmpbuf_t* yaooc_current_jmpbuf()
{
  yaooc_exception_thread_jmpbuf_node_t* node=yaooc_exception_thread_jmpbuf_list_find_jmpbuf(yaooc_current_thread_id());
  return node->current_jmpbuf_;
}

pointer yaooc_exception_garbage_bag_save(pointer p)
{
  yaooc_jmpbuf_t* cjb=yaooc_current_jmpbuf();
  if(cjb)
    M(cjb->pb_,add,p);
  return p;
}

pointer yaooc_exception_garbage_bag_save_static_array(pointer p,const type_info_t* ti,size_t n)
{
  yaooc_jmpbuf_t* cjb=yaooc_current_jmpbuf();
  if(cjb)
    M(cjb->pb_,add_static,p,ti,n);
  return p;
}

void yaooc_exception_garbage_bag_clear(pointer p)
{
  yaooc_jmpbuf_t* cjb=yaooc_current_jmpbuf();
  if(cjb)
    M(cjb->pb_,clear);
}

void yaooc_exception_garbage_bag_delete(pointer p)
{
  yaooc_jmpbuf_t* cjb=yaooc_current_jmpbuf();
  if(cjb)
    M(cjb->pb_,del_all);
}




yaooc_exception_pointer yaooc_exception_current_exception_thrown()
{
  return yaooc_current_jmpbuf()->exception_thrown_;
}


yaooc_stream_exception_class_table_t yaooc_stream_exception_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_exception_class_table,
.type_name_ = (const char*)"yaooc_stream_exception_t",
.swap = (void(*)(pointer,pointer)) yaooc_stream_exception_swap,
.what = (const char*(*)(const_pointer)) yaooc_stream_exception_what,
.error_code = (int(*)(const_pointer)) yaooc_stream_exception_error_code,
};
const type_info_t __yaooc_stream_exception_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_stream_exception_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=NULL,
.dtor_=NULL,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaooc_stream_exception_class_table,
.parent_=&__yaooc_exception_ti
};
const type_info_t* const yaooc_stream_exception_ti=&__yaooc_stream_exception_ti;
void throw_stream_exception(pointer p,const char* what)
{
  THROW(new_ctor(yaooc_stream_exception,yaooc_stream_exception_ctor_v,21,"No %s method for %s type",
        what,((yaooc_object_class_table_t*)(((yaooc_object_pointer)p)->class_table_))->type_name_));
}


yaooc_array_container_exception_class_table_t yaooc_array_container_exception_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_exception_class_table,
.type_name_ = (const char*)"yaooc_array_container_exception_t",
.swap = (void(*)(pointer,pointer)) yaooc_array_container_exception_swap,
.what = (const char*(*)(const_pointer)) yaooc_array_container_exception_what,
.error_code = (int(*)(const_pointer)) yaooc_array_container_exception_error_code,
};
const type_info_t __yaooc_array_container_exception_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_array_container_exception_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=NULL,
.dtor_=NULL,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaooc_array_container_exception_class_table,
.parent_=&__yaooc_exception_ti
};
const type_info_t* const yaooc_array_container_exception_ti=&__yaooc_array_container_exception_ti;
void throw_yaooc_array_container_exception(pointer p,const char* what)
{
  THROW(new_ctor(yaooc_array_container_exception,yaooc_array_container_exception_ctor_v,32,"%s",
        what,((yaooc_object_class_table_t*)(((yaooc_object_pointer)p)->class_table_))->type_name_));
}


