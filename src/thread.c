/*
		Copyright (C) 2016-2019  by Terry N Bezue

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <yaooc/thread.h>
#include <sys/time.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct yaooc_exception_thread_jmpbuf_node_s yaooc_exception_thread_jmpbuf_node_t;

typedef struct {
  void* object_;
  void* data_;
} thread_start_info_t;
void yaooc_exception_thread_list_remove_exception_thread(yaooc_internal_thread_t tid);

/*  Begin YAOOC PreProcessor generated content */

/* Private items for yaooc_thread */
#if defined(_WIN32) && !defined(__YAOOC_USE_PTHREADS)
static unsigned int __stdcall yaooc_thread_thread_entry(void *arg)
{
  thread_start_info_t* start_arg=arg;
  yaooc_thread_pointer this=start_arg->object_;
  this->state_=THREAD_RUNNING;
  this->method(this,start_arg->data_);
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
  thread_start_info_t* start_arg=arg;
  yaooc_thread_pointer this=start_arg->object_;
  void* ret=NULL;
  this->state_=THREAD_RUNNING;
  this->thread_id_=pthread_self();
  ret=this->method(this,start_arg->data_);
  FREE(arg);
  yaooc_exception_thread_list_remove_exception_thread(pthread_self());
  this->state_=THREAD_READY;
  this->is_detached_=false;
  this->request_exit_=false;
  pthread_exit(ret);
  return ret;
}
#endif
/* Protected items for yaooc_thread */


/* Typeinfo for yaooc_thread */
void yaooc_thread_default_ctor(pointer p)
{
  yaooc_thread_pointer this=p;
  this->thread_id_=0;
  this->state_=THREAD_READY;
  this->is_detached_=false;
  this->request_exit_=false;
}

void yaooc_thread_dtor(pointer p)
{
  yaooc_thread_pointer this=p;
  if(this->state_ == THREAD_RUNNING) {
    yaooc_thread_cancel(this);
    yaooc_thread_join(this);
#ifdef _WIN32
    CloseHandle((HANDLE)this->thread_id_);
#endif
  }
}

/* Constructors for yaooc_thread */
void yaooc_thread_ctor_method(pointer p,va_list args)
{
  yaooc_thread_default_ctor(p);
  ((yaooc_thread_pointer)p)->method=va_arg(args,yaooc_thread_method);
}

/* Class table methods for yaooc_thread */
yaooc_internal_thread_t yaooc_thread_id(const_pointer p)
{
  yaooc_thread_const_pointer this=p;
  return this->thread_id_;
}

int yaooc_thread_join(pointer p)
{
  yaooc_thread_pointer this=p;
  int ret=0;
//  printf("%d %d\n",this->state_,this->is_detached_);
  if(this->state_ != THREAD_READY && !this->is_detached_) {
#ifdef _WIN32
    ret = WaitForSingleObject((HANDLE)this->thread_id_,INFINITE);
#else
    ret=pthread_join(this->thread_id_,NULL);
#endif
    this->state_=THREAD_READY;
  }
  return ret;
}

int yaooc_thread_cancel(pointer p)
{
  yaooc_thread_pointer this=p;
  int ret=0;
  if(this->state_ == THREAD_RUNNING) {
    this->request_exit_=true;
  }
  return ret;
}

int yaooc_thread_detach(pointer p)
{
  yaooc_thread_pointer this=p;
  int ret=0;
  if(!this->is_detached_) {
#ifdef _WIN32
    ret=CloseHandle((HANDLE)this->thread_id_);
//    this->thread_id_=0;
#else
    ret=pthread_detach(this->thread_id_);
#endif
    this->is_detached_=true;
  }
  return ret;
}

yaooc_thread_state_t yaooc_thread_state(const_pointer p)
{
  yaooc_thread_const_pointer this=p;
  return this->state_;
}

bool yaooc_thread_is_detached(const_pointer p)
{
  yaooc_thread_const_pointer this=p;
  return this->is_detached_;
}

bool yaooc_thread_start(pointer p,void* data)
{
  yaooc_thread_pointer this=p;
  thread_start_info_t* ti=MALLOC(sizeof(thread_start_info_t));
  ti->object_=p;
  ti->data_=data;
//  pthread_t id;
#ifdef _WIN32
  return (this->thread_id_=_beginthreadex(NULL,0,yaooc_thread_thread_entry,ti,0,NULL))!=0L;
#else
  return pthread_create(&this->thread_id_,NULL,yaooc_thread_thread_entry,ti) == 0;
#endif
}

/*
void* yaooc_thread_method(pointer p)
{
  return NULL;
}
*/

/* Class table for yaooc_thread */
yaooc_thread_class_table_t yaooc_thread_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
  .type_name_ = (const char*) "yaooc_thread_t",
  .swap = (void (*) (pointer,pointer)) yaooc_thread_swap,
  .id = (yaooc_internal_thread_t (*) (const_pointer)) yaooc_thread_id,
  .join = (int (*) (pointer)) yaooc_thread_join,
  .cancel = (int (*) (pointer)) yaooc_thread_cancel,
  .detach = (int (*) (pointer)) yaooc_thread_detach,
  .state = (yaooc_thread_state_t (*) (const_pointer p)) yaooc_thread_state,
  .is_detached = (bool (*) (const_pointer)) yaooc_thread_is_detached,
  .start = (bool (*) (pointer,void*)) yaooc_thread_start,
};


DEFINE_TYPE_INFO(yaooc_thread,Y,Y,N,N,N,N,N,Y,yaooc_object);
/* Private items for yaooc_mutex */

/* Protected items for yaooc_mutex */


/* Typeinfo for yaooc_mutex */
void yaooc_mutex_default_ctor(pointer p)
{
  yaooc_mutex_pointer this=p;
//  this->mutex_=(pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
#ifdef _WIN32
  this->mutex_=CreateMutex(NULL,FALSE,NULL);
#else
  pthread_mutex_init(&this->mutex_,NULL);
#endif
}

void yaooc_mutex_dtor(pointer p)
{
  yaooc_mutex_pointer this=p;
  yaooc_mutex_unlock(this);
#ifdef _WIN32
  CloseHandle((HANDLE)this->mutex_);
#else
  pthread_mutex_destroy(&this->mutex_);
#endif
}

/* Constructors for yaooc_mutex */

/* Class table methods for yaooc_mutex */
bool yaooc_mutex_lock(pointer p)
{
  yaooc_mutex_pointer this=p;
#ifdef _WIN32
  return WaitForSingleObject(this->mutex_,INFINITE) == WAIT_OBJECT_0;
#else
  return pthread_mutex_lock(&this->mutex_) == 0;
#endif
}

bool yaooc_mutex_trylock(pointer p)
{
#if defined(_WIN32) && !defined(__YAOOC_USE_PTHREADS)
  return yaooc_mutex_lock(p);
#else
  return pthread_mutex_trylock(&((yaooc_mutex_pointer)p)->mutex_) == 0;
#endif
}

bool yaooc_mutex_unlock(pointer p)
{
  yaooc_mutex_pointer this=p;
#ifdef _WIN32
  return ReleaseMutex(this->mutex_);
#else
  return pthread_mutex_unlock(&this->mutex_) == 0;
#endif
}

/* Class table for yaooc_mutex */
yaooc_mutex_class_table_t yaooc_mutex_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
  .type_name_ = (const char*) "yaooc_mutex_t",
  .swap = (void (*) (pointer p,pointer)) yaooc_mutex_swap,
  .lock = (bool (*) (pointer p)) yaooc_mutex_lock,
  .trylock = (bool (*) (pointer p)) yaooc_mutex_trylock,
  .unlock = (bool (*) (pointer p)) yaooc_mutex_unlock,
};


DEFINE_TYPE_INFO(yaooc_mutex,Y,Y,N,N,N,N,N,Y,yaooc_object);
/*  End YAOOC PreProcessor generated content */
#if 0
/* Private items for yaooc_condition_variable */

/* Protected items for yaooc_condition_variable */


/* Typeinfo for yaooc_condition_variable */
void yaooc_condition_variable_default_ctor(pointer p)
{
  yaooc_condition_variable_pointer this=p;
  yaooc_mutex_default_ctor(&this->mutex_);
//  this->condition_variable_= (pthread_cond_t)PTHREAD_COND_INITIALIZER;
  pthread_cond_init(&this->condition_variable_,NULL);
}

void yaooc_condition_variable_dtor(pointer p)
{
  yaooc_condition_variable_pointer this=p;
  pthread_cond_destroy(&this->condition_variable_);
}

/* Constructors for yaooc_condition_variable */

/* Class table methods for yaooc_condition_variable */
bool yaooc_condition_variable_signal(pointer p)
{
  yaooc_condition_variable_pointer this=p;
  return pthread_cond_signal(&this->condition_variable_);
}

bool yaooc_condition_variable_broadcast(pointer p)
{
  yaooc_condition_variable_pointer this=p;
  return pthread_cond_broadcast(&this->condition_variable_);
}

int yaooc_condition_variable_wait(pointer p)
{
  yaooc_condition_variable_pointer this=p;
  return pthread_cond_wait(&this->condition_variable_, &this->mutex_);
}

int yaooc_condition_variable_timedwait(pointer p,double delay)
{
  yaooc_condition_variable_pointer this=p;
  long long tv_sec=delay;
  long long tv_nsec=(delay-tv_sec)*1000000000;
  struct timeval tv;
  gettimeofday(&tv,NULL);
  struct timespec ts;
  ts.tv_nsec=tv.tv_usec*1000 + tv_nsec;
  if(ts.tv_nsec>=1000000000) {
    ts.tv_nsec-=1000000000;
    tv_sec++;
  }
  ts.tv_sec=tv.tv_sec+tv_sec;
  int rc= pthread_cond_timedwait(&this->condition_variable_, &this->mutex_,&ts);
  return rc;
}


/* Class table for yaooc_condition_variable */
yaooc_condition_variable_class_table_t yaooc_condition_variable_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_mutex_class_table,
  .type_name_ = (const char*) "yaooc_condition_variable_t",
  .swap = (void (*) (pointer p,pointer)) yaooc_condition_variable_swap,
  .lock = (bool (*) (pointer p)) yaooc_condition_variable_lock,
  .trylock = (bool (*) (pointer p)) yaooc_condition_variable_trylock,
  .unlock = (bool (*) (pointer p)) yaooc_condition_variable_unlock,
  .signal = (bool (*) (pointer p)) yaooc_condition_variable_signal,
  .broadcast = (bool (*) (pointer p)) yaooc_condition_variable_broadcast,
  .wait = (int (*) (pointer p)) yaooc_condition_variable_wait,
  .timedwait = (int (*) (pointer p,double)) yaooc_condition_variable_timedwait,
};

DEFINE_TYPE_INFO(yaooc_condition_variable,Y,Y,N,N,N,N,N,Y,yaooc_mutex);
#endif
#ifdef __cplusplus
}
#endif
