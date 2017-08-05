#include <yaooc/thread.h>
#include <yaooc/exception.h>

void yaooc_exception_thread_list_remove_exception_thread(pthread_t tid);

/* Private members for yaooc_thread */
void* yaooc_thread_start_thread(void* arg)
{
  yaooc_thread_pointer this=arg;
  void* ret=NULL;
  this->thread_state_=THREAD_RUNNING;
//  this->thread_id_=pthread_self();
  ret=M(this,run);
  yaooc_exception_thread_list_remove_exception_thread(pthread_self());
  pthread_exit(ret);
  return ret;
}


/* Protected members for yaooc_thread */

/* Typeinfo for yaooc_thread */
void yaooc_thread_default_ctor(pointer p)
{
  yaooc_thread_pointer this=p;
  this->thread_id_=0;
  this->thread_state_=THREAD_READY;
  this->is_detached_=false;
}
void yaooc_thread_dtor(pointer p)
{
  yaooc_thread_pointer this=p;

  if(this->thread_state_ == THREAD_RUNNING) {
    yaooc_thread_cancel(this);
    yaooc_thread_join(this);
  }
}

void yaooc_thread_copy_ctor(pointer d,const_pointer s)
{

}

void yaooc_thread_assign(pointer d,const_pointer s)
{

}

/* Additional constructors for yaooc_thread */

/* Class table members for yaooc_thread */
pthread_t yaooc_thread_id(const_pointer p)
{
  yaooc_thread_const_pointer this=p;
  return this->thread_id_;
}

int yaooc_thread_join(pointer p)
{
  yaooc_thread_pointer this=p;
  int ret=0;
  if(this->thread_state_ != THREAD_READY && !this->is_detached_) {
    ret=pthread_join(this->thread_id_,NULL);
    this->thread_state_=THREAD_READY;
  }
  return ret;
}

int yaooc_thread_cancel(pointer p)
{
  yaooc_thread_pointer this=p;
  int ret=0;
  if(this->thread_state_ == THREAD_RUNNING) {
    ret=pthread_cancel(this->thread_id_);
    this->thread_state_=this->is_detached_ ? THREAD_READY : THREAD_TERMINATED;
  }
  return ret;
}

int yaooc_thread_detach(pointer p)
{
  yaooc_thread_pointer this=p;
  int ret=0;
  if(!this->is_detached_) {
    ret=pthread_detach(this->thread_id_);
    this->is_detached_=true;
  }
  return ret;
}

yaooc_thread_state_t yaooc_thread_state(const_pointer p)
{
  yaooc_thread_const_pointer this=p;
  return this->thread_state_;
}

bool yaooc_thread_is_detached(const_pointer p)
{
  yaooc_thread_const_pointer this=p;
  return this->is_detached_;
}

bool yaooc_thread_start(pointer p)
{
  yaooc_thread_pointer this=p;
  return pthread_create(&this->thread_id_,NULL,yaooc_thread_start_thread,this) == 0;
}

yaooc_thread_class_members_t yaooc_thread_class_members = { YAOOC_THREAD_CLASS_MEMBERS };

DEFINE_TYPE_INFO(yaooc_thread,yaooc_thread_default_ctor,yaooc_thread_dtor,yaooc_thread_copy_ctor,
        yaooc_thread_assign,NULL,&yaooc_thread_class_members,yaooc_object)

/*
void* yaooc_thread_run(pointer p)
{
  yaooc_thread_pointer this=p;
  return NULL;
}
*/

/* Instance members for yaooc_thread */
/* Private members for yaooc_mutex */

/* Protected members for yaooc_mutex */

/* Typeinfo for yaooc_mutex */
void yaooc_mutex_default_ctor(pointer p)
{
  yaooc_mutex_pointer this=p;
   pthread_mutex_init(&this->mutex_,NULL);
}

void yaooc_mutex_dtor(pointer p)
{
  yaooc_mutex_pointer this=p;
  pthread_mutex_destroy(&this->mutex_);
}

/* Class table members for yaooc_mutex */
bool yaooc_mutex_lock(pointer p)
{
  yaooc_mutex_pointer this=p;
  return pthread_mutex_lock(&this->mutex_) == 0;
}

bool yaooc_mutex_trylock(pointer p)
{
  yaooc_mutex_pointer this=p;
  return pthread_mutex_trylock(&this->mutex_) == 0;
}

bool yaooc_mutex_unlock(pointer p)
{
  yaooc_mutex_pointer this=p;
  return pthread_mutex_unlock(&this->mutex_) == 0;
}


/* Instance members for yaooc_mutex */

yaooc_mutex_class_members_t yaooc_mutex_class_members = { YAOOC_MUTEX_CLASS_MEMBERS };

DEFINE_TYPE_INFO(yaooc_mutex,yaooc_mutex_default_ctor,yaooc_mutex_dtor,NULL,NULL,NULL,&yaooc_mutex_class_members,yaooc_object)
