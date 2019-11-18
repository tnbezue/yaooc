#ifndef __THREAD_INCLUDED__
#define __THREAD_INCLUDED__


#include <yaooc/object.h>


#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
typedef uintptr_t yaooc_internal_thread_t;
typedef HANDLE yaooc_internal_mutex_t;
#define yaooc_current_thread_id() (uintptr_t)GetCurrentThread()
#else
#include <pthread.h>
typedef pthread_t yaooc_internal_thread_t;
typedef pthread_mutex_t yaooc_internal_mutex_t;
#define yaooc_current_thread_id() pthread_self()
#endif
typedef enum { THREAD_READY=0,THREAD_RUNNING,THREAD_TERMINATED } yaooc_thread_state_t;

#ifdef __cplusplus
extern "C" {
#endif

typedef void* (*yaooc_thread_method) (pointer,void*);


typedef struct yaooc_exception_thread_jmpbuf_node_s yaooc_exception_thread_jmpbuf_node_t;

yaooc_min_struct(yaooc_thread_start_info) {
  void* object_;
  void* data_;
};
yaooc_class_table(yaooc_thread) {
  yaooc_object_class_table_t;
  yaooc_internal_thread_t (*id)(const_pointer);
  void (*cancel)(pointer);
  int (*join)(pointer);
  int (*detach)(pointer);
  yaooc_thread_state_t (*state)(const_pointer);
  bool (*is_detached)(const_pointer);
  bool (*start)(pointer,void*);
};
#define yaooc_thread_parent_class_table ((yaooc_object_class_table_t*)(yaooc_thread_class_table.parent_class_table_))

yaooc_class_instance(yaooc_thread) {
  yaooc_thread_method method_;
  yaooc_internal_thread_t thread_id_;
  yaooc_thread_state_t state_;
  bool is_detached_;
  bool request_exit_;
};

yaooc_class(yaooc_thread);

void yaooc_thread_default_ctor(pointer);
void yaooc_thread_dtor(pointer);
void yaooc_thread_ctor_method(pointer,va_list);
#define yaooc_thread_swap yaooc_object_swap
yaooc_internal_thread_t yaooc_thread_id(const_pointer);
void yaooc_thread_cancel(pointer);
int yaooc_thread_join(pointer);
int yaooc_thread_detach(pointer);
yaooc_thread_state_t yaooc_thread_state(const_pointer);
bool yaooc_thread_is_detached(const_pointer);
bool yaooc_thread_start(pointer,void*);
yaooc_class_table(yaooc_mutex) {
  yaooc_object_class_table_t;
  bool (*lock)(pointer);
  bool (*trylock)(pointer);
  bool (*unlock)(pointer);
};
#define yaooc_mutex_parent_class_table ((yaooc_object_class_table_t*)(yaooc_mutex_class_table.parent_class_table_))

yaooc_class_instance(yaooc_mutex) {
  yaooc_internal_mutex_t mutex_;
};

yaooc_class(yaooc_mutex);

void yaooc_mutex_default_ctor(pointer);
void yaooc_mutex_dtor(pointer);
#define yaooc_mutex_swap yaooc_object_swap
bool yaooc_mutex_lock(pointer);
bool yaooc_mutex_trylock(pointer);
bool yaooc_mutex_unlock(pointer);

#include <yaooc/string.h>
int command_pipe(const char* command,const yaooc_string_t* std_in,yaooc_string_t* std_out,yaooc_string_t* std_err);


#endif
