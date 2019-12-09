#include <yaooc/thread.h>
const min_type_info_t __yaooc_thread_start_info_ti = {
.min_flag_=1,
.pod_flag_=0,
.type_size_=sizeof(yaooc_thread_start_info_t),
};
const type_info_t* const yaooc_thread_start_info_ti=(const type_info_t* const)&__yaooc_thread_start_info_ti;
void yaooc_exception_thread_list_remove_exception_thread(yaooc_internal_thread_t tid);

#if defined(_WIN32) && !defined(__YAOOC_USE_PTHREADS)
static unsigned int __stdcall yaooc_thread_thread_entry(void *arg)
{
  yaooc_thread_start_info_t* start_arg=arg;
  yaooc_thread_pointer this=start_arg->object_;
  this->state_=THREAD_RUNNING;
  this->method_(this,start_arg->data_);
  FREE(arg);
  yaooc_exception_thread_list_remove_exception_thread(this->thread_id_);
  this->state_=THREAD_READY;
  this->is_detached_=false;
  this->request_exit_=false;
  _endthreadex(0);
}
#else
static void* yaooc_thread_thread_entry(void* arg)
{
  yaooc_thread_start_info_t* start_arg=arg;
  yaooc_thread_pointer this=start_arg->object_;
  void* ret=NULL;
  this->state_=THREAD_RUNNING;
  this->thread_id_=pthread_self();
  ret=this->method_(this,start_arg->data_);
  FREE(arg);
  yaooc_exception_thread_list_remove_exception_thread(pthread_self());
  this->state_=THREAD_READY;
  this->is_detached_=false;
  this->request_exit_=false;
  pthread_exit(ret);
  return ret;
}
#endif


void yaooc_thread_default_ctor(pointer __pthis__)
{
yaooc_thread_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_thread);



      this->thread_id_=0;
      this->state_=THREAD_READY;
      this->is_detached_=false;
      this->request_exit_=false;
    
}
void yaooc_thread_dtor(pointer __pthis__)
{
yaooc_thread_pointer this=__pthis__;(void)this;


      if(this->state_ == THREAD_RUNNING) {
        yaooc_thread_cancel(this);
        yaooc_thread_join(this);
#ifdef _WIN32
        CloseHandle((HANDLE)this->thread_id_);
#endif
      }
    
}
void yaooc_thread_ctor_method(pointer __pthis,va_list __con_args__){
yaooc_thread_pointer this=__pthis;(void)this;
yaooc_thread_method method = va_arg(__con_args__,yaooc_thread_method);

call_default_ctor_static(this,yaooc_thread);


      yaooc_thread_default_ctor(this);
      ((yaooc_thread_pointer)this)->method_=method;
    
}
yaooc_internal_thread_t yaooc_thread_id(const_pointer __pthis__)
{
yaooc_thread_const_pointer this=__pthis__;(void)this;
#define super() yaooc_thread_parent_class_table->id(this)
#define PM(method,...) CTM((*yaooc_thread_parent_class_table),this,method,## __VA_ARGS__)


      return this->thread_id_;
    
#undef PM
#undef super
}
void yaooc_thread_cancel(pointer __pthis__)
{
yaooc_thread_pointer this=__pthis__;(void)this;
#define super() yaooc_thread_parent_class_table->cancel(this)
#define PM(method,...) CTM((*yaooc_thread_parent_class_table),this,method,## __VA_ARGS__)


      this->request_exit_=true;
    
#undef PM
#undef super
}
int yaooc_thread_join(pointer __pthis__)
{
yaooc_thread_pointer this=__pthis__;(void)this;
#define super() yaooc_thread_parent_class_table->join(this)
#define PM(method,...) CTM((*yaooc_thread_parent_class_table),this,method,## __VA_ARGS__)


      int ret=0;
    

      if(this->thread_id_ != 0) {
#ifdef _WIN32
        ret = WaitForSingleObject((HANDLE)this->thread_id_,INFINITE);
#else
        ret=pthread_join(this->thread_id_,NULL);
#endif
        this->state_=THREAD_READY;
        this->thread_id_=0;
      }
      return ret;
    
#undef PM
#undef super
}
int yaooc_thread_detach(pointer __pthis__)
{
yaooc_thread_pointer this=__pthis__;(void)this;
#define super() yaooc_thread_parent_class_table->detach(this)
#define PM(method,...) CTM((*yaooc_thread_parent_class_table),this,method,## __VA_ARGS__)


      int ret=0;
      if(!this->is_detached_) {
#ifdef _WIN32
        ret=CloseHandle((HANDLE)this->thread_id_);
    
#else
        ret=pthread_detach(this->thread_id_);
#endif
        this->is_detached_=true;
      }
      return ret;
    
#undef PM
#undef super
}
yaooc_thread_state_t yaooc_thread_state(const_pointer __pthis__)
{
yaooc_thread_const_pointer this=__pthis__;(void)this;
#define super() yaooc_thread_parent_class_table->state(this)
#define PM(method,...) CTM((*yaooc_thread_parent_class_table),this,method,## __VA_ARGS__)


      return this->state_;
    
#undef PM
#undef super
}
bool yaooc_thread_is_detached(const_pointer __pthis__)
{
yaooc_thread_const_pointer this=__pthis__;(void)this;
#define super() yaooc_thread_parent_class_table->is_detached(this)
#define PM(method,...) CTM((*yaooc_thread_parent_class_table),this,method,## __VA_ARGS__)


      return this->is_detached_;
    
#undef PM
#undef super
}
bool yaooc_thread_start(pointer __pthis__,void* data)
{
yaooc_thread_pointer this=__pthis__;(void)this;
#define super() yaooc_thread_parent_class_table->start(this,data)
#define PM(method,...) CTM((*yaooc_thread_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_thread_start_info_t* ti=MALLOC(sizeof(yaooc_thread_start_info_t));
      ti->object_=this;
      ti->data_=data;
    
#ifdef _WIN32
      return (this->thread_id_=_beginthreadex(NULL,0,yaooc_thread_thread_entry,ti,0,NULL))!=0L;
#else
      return pthread_create(&this->thread_id_,NULL,yaooc_thread_thread_entry,ti) == 0;
#endif
    
#undef PM
#undef super
}
yaooc_thread_class_table_t yaooc_thread_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_object_class_table,
.type_name_ = (const char*)"yaooc_thread_t",
.swap = (void(*)(pointer,pointer)) yaooc_thread_swap,
.id = (yaooc_internal_thread_t(*)(const_pointer)) yaooc_thread_id,
.cancel = (void(*)(pointer)) yaooc_thread_cancel,
.join = (int(*)(pointer)) yaooc_thread_join,
.detach = (int(*)(pointer)) yaooc_thread_detach,
.state = (yaooc_thread_state_t(*)(const_pointer)) yaooc_thread_state,
.is_detached = (bool(*)(const_pointer)) yaooc_thread_is_detached,
.start = (bool(*)(pointer,void*)) yaooc_thread_start,
};
const type_info_t __yaooc_thread_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_thread_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaooc_thread_default_ctor,
.dtor_=yaooc_thread_dtor,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaooc_thread_class_table,
.parent_=&__yaooc_object_ti
};
const type_info_t* const yaooc_thread_ti=&__yaooc_thread_ti;
void yaooc_mutex_default_ctor(pointer __pthis__)
{
yaooc_mutex_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_mutex);



#ifdef _WIN32
      this->mutex_=CreateMutex(NULL,FALSE,NULL);
#else
      pthread_mutex_init(&this->mutex_,NULL);
#endif
    
}
void yaooc_mutex_dtor(pointer __pthis__)
{
yaooc_mutex_pointer this=__pthis__;(void)this;


      yaooc_mutex_unlock(this);
#ifdef _WIN32
      CloseHandle((HANDLE)this->mutex_);
#else
      pthread_mutex_destroy(&this->mutex_);
#endif
    
}
bool yaooc_mutex_lock(pointer __pthis__)
{
yaooc_mutex_pointer this=__pthis__;(void)this;
#define super() yaooc_mutex_parent_class_table->lock(this)
#define PM(method,...) CTM((*yaooc_mutex_parent_class_table),this,method,## __VA_ARGS__)


#ifdef _WIN32
      return WaitForSingleObject(this->mutex_,INFINITE) == WAIT_OBJECT_0;
#else
      return pthread_mutex_lock(&this->mutex_) == 0;
#endif
    
#undef PM
#undef super
}
bool yaooc_mutex_trylock(pointer __pthis__)
{
yaooc_mutex_pointer this=__pthis__;(void)this;
#define super() yaooc_mutex_parent_class_table->trylock(this)
#define PM(method,...) CTM((*yaooc_mutex_parent_class_table),this,method,## __VA_ARGS__)


#if defined(_WIN32) && !defined(__YAOOC_USE_PTHREADS)
      return yaooc_mutex_lock(this);
#else
      return pthread_mutex_trylock(&((yaooc_mutex_pointer)this)->mutex_) == 0;
#endif
    
#undef PM
#undef super
}
bool yaooc_mutex_unlock(pointer __pthis__)
{
yaooc_mutex_pointer this=__pthis__;(void)this;
#define super() yaooc_mutex_parent_class_table->unlock(this)
#define PM(method,...) CTM((*yaooc_mutex_parent_class_table),this,method,## __VA_ARGS__)


#ifdef _WIN32
      return ReleaseMutex(this->mutex_);
#else
      return pthread_mutex_unlock(&this->mutex_) == 0;
#endif
    
#undef PM
#undef super
}
yaooc_mutex_class_table_t yaooc_mutex_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_object_class_table,
.type_name_ = (const char*)"yaooc_mutex_t",
.swap = (void(*)(pointer,pointer)) yaooc_mutex_swap,
.lock = (bool(*)(pointer)) yaooc_mutex_lock,
.trylock = (bool(*)(pointer)) yaooc_mutex_trylock,
.unlock = (bool(*)(pointer)) yaooc_mutex_unlock,
};
const type_info_t __yaooc_mutex_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_mutex_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaooc_mutex_default_ctor,
.dtor_=yaooc_mutex_dtor,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaooc_mutex_class_table,
.parent_=&__yaooc_object_ti
};
const type_info_t* const yaooc_mutex_ti=&__yaooc_mutex_ti;
#include <sys/stat.h>
#include <string.h>

typedef struct {
#ifdef _WIN32
  HANDLE pipe_handle;
#else
  const char* pipename;
#endif
  const yaooc_string_t *buffer;
} thread_data_input;

typedef struct {
#ifdef _WIN32
  HANDLE pipe_handle;
#else
  const char* pipename;
#endif
  yaooc_string_t *buffer;
} thread_data_output;

void* thread_writer(pointer p,void* data)
{
  thread_data_input* wd=data;
#ifdef _WIN32
  if(ConnectNamedPipe(wd->pipe_handle, NULL) != FALSE) {
    DWORD dwWritten;
    WriteFile(wd->pipe_handle,M(wd->buffer,c_str),M(wd->buffer,size),&dwWritten,NULL);
  }
  CloseHandle(wd->pipe_handle);
#else
  FILE* fh = fopen(wd->pipename,"w");
  if(fh) {
    fwrite(M(wd->buffer,c_str),1,M(wd->buffer,size),fh);
    fclose(fh);
  }
#endif
  return NULL;
}

#define TEMP_BUF_SIZE 1024
void* thread_reader(pointer p,void* data)
{
  thread_data_output *rd = data;
  char* temp_buffer=MALLOC(TEMP_BUF_SIZE);
#ifdef _WIN32
  if(ConnectNamedPipe(rd->pipe_handle, NULL) != FALSE) {
    DWORD dwRead;
    while(ReadFile(rd->pipe_handle, temp_buffer, TEMP_BUF_SIZE, &dwRead, NULL) != FALSE) {
      M(rd->buffer,appendn,temp_buffer,dwRead);
    }
    CloseHandle(rd->pipe_handle);
  }
#else
  FILE* fh = fopen(rd->pipename,"r");
  M(rd->buffer,clear);
  if(fh) {
    while(!feof(fh)) {
      int nb = fread(temp_buffer,1,TEMP_BUF_SIZE,fh);
      M(rd->buffer,appendn,temp_buffer,nb);
    }
    fclose(fh);
  }
#endif
  FREE(temp_buffer);
  return NULL;
}




int command_pipe(const char* command,const yaooc_string_t* std_in,yaooc_string_t* std_out,yaooc_string_t* std_err)
{
  yaooc_thread_t* writer=new_ctor(yaooc_thread,yaooc_thread_ctor_method,thread_writer);
  yaooc_thread_t* reader=new_ctor(yaooc_thread,yaooc_thread_ctor_method,thread_reader);
  yaooc_thread_t* errreader=new_ctor(yaooc_thread,yaooc_thread_ctor_method,thread_reader);

  thread_data_input wd;
#ifdef _WIN32
  const char* pipein=TEXT("\\\\.\\pipe\\Pipein");
  wd.pipe_handle=CreateNamedPipe(pipein,PIPE_ACCESS_DUPLEX,PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,1,1024 * 16,1024 * 16,NMPWAIT_USE_DEFAULT_WAIT,NULL);
#else
  const char* pipein="/tmp/pipein";
  wd.pipename = pipein;
  mkfifo(wd.pipename, 0600);
#endif
  wd.buffer = std_in;

  thread_data_output rd;

#ifdef _WIN32
  const char* pipeout=TEXT("\\\\.\\pipe\\Pipeout");
  wd.pipe_handle=CreateNamedPipe(pipeout,PIPE_ACCESS_DUPLEX,PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,1,1024 * 16,1024 * 16,NMPWAIT_USE_DEFAULT_WAIT,NULL);
#else
  const char* pipeout="/tmp/pipeout";
  rd.pipename = pipeout;
  mkfifo(rd.pipename, 0600);
#endif
  rd.buffer = std_out;

  thread_data_output err;
#ifdef _WIN32
  const char* pipeerr=TEXT("\\\\.\\pipe\\Pipeerr");
  wd.pipe_handle=CreateNamedPipe(pipeerr,PIPE_ACCESS_DUPLEX,PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,1,1024 * 16,1024 * 16,NMPWAIT_USE_DEFAULT_WAIT,NULL);
#else
  const char* pipeerr = "/tmp/pipeerr";
  err.pipename = pipeerr;
  mkfifo(err.pipename, 0600);
#endif
  err.buffer = std_err;

  M(writer,start,&wd);
  M(reader,start,&rd);
  M(errreader,start,&err);

  char* temp_cmd = malloc(strlen(command)+64);
  sprintf(temp_cmd,"%s < %s > %s 2> %s",command,pipein,pipeout,pipeerr);
  int rc = system(temp_cmd);
  free(temp_cmd);
  M(writer,join);
  M(reader,join);
  M(errreader,join);

  unlink(pipein);
  unlink(pipeout);
  unlink(pipeerr);
  delete(writer);
  delete(reader);
  delete(errreader);
  return rc;
}

