#ifndef __THREAD_INCLUDED__
#define __THREAD_INCLUDED__

#include <yaooc/object.h>
#include <pthread.h>

typedef enum { THREAD_READY=0,THREAD_RUNNING,THREAD_TERMINATED } yaooc_thread_state_t;

class_table(yaooc_thread)
{
  yaooc_object_class_members_t;
  pthread_t (*id)(const_pointer);
  int (*join)(pointer);
  int (*cancel)(pointer);
  int (*detach)(pointer);
  yaooc_thread_state_t (*state)(const_pointer);
  bool (*is_detached)(const_pointer);
  bool (*start) (pointer);
  void* (*run)(pointer);
};

class_instance(yaooc_thread)
{
  yaooc_object_instance_members_t;
  pthread_t thread_id_;
  yaooc_thread_state_t thread_state_;
  bool is_detached_;
};

class(yaooc_thread);

/* Prototypes for type info */
void yaooc_thread_default_ctor(pointer);
void yaooc_thread_dtor(pointer);
void yaooc_thread_copy_ctor(pointer,const_pointer);

/* Prototypes for Constructors */

/* Prototypes for class table members */
pthread_t yaooc_thread_id(const_pointer);
int yaooc_thread_join(pointer);
int yaooc_thread_cancel(pointer);
int yaooc_thread_detach(pointer);
yaooc_thread_state_t yaooc_thread_state(const_pointer);
bool yaooc_thread_is_detached(const_pointer);
bool yaooc_thread_start(pointer);
#define yaooc_thread_run  NULL

/* Prototypes for class instance members */

/* Prototypes for class protected members */

/* New class table members for yaooc_thread */
#define YAOOC_THREAD_NEW_CLASS_MEMBERS \
  (pthread_t(*) (const_pointer)) yaooc_thread_id, \
  (int(*) (pointer)) yaooc_thread_join, \
  (int(*) (pointer)) yaooc_thread_cancel, \
  (int(*) (pointer)) yaooc_thread_detach, \
  (yaooc_thread_state_t(*) (const_pointer)) yaooc_thread_state, \
  (bool (*) (const_pointer)) yaooc_thread_is_detached, \
  (bool (*) (pointer)) yaooc_thread_start, \
  (void* (*) (pointer)) yaooc_thread_run, \

/* New plus parent members for yaooc_thread */
#define YAOOC_THREAD_CLASS_MEMBERS \
  { YAOOC_OBJECT_CLASS_MEMBERS }, \
  YAOOC_THREAD_NEW_CLASS_MEMBERS

class_table(yaooc_mutex)
{
  yaooc_object_class_members_t;
  bool (*lock)(pointer);
  bool (*trylock)(pointer);
  bool (*unlock)(pointer);
};

class_instance(yaooc_mutex)
{
  yaooc_object_instance_members_t;
  pthread_mutex_t mutex_;
};

class(yaooc_mutex);

/* Prototypes for type info */
void yaooc_mutex_default_ctor(pointer);
void yaooc_mutex_dtor(pointer);

/* Prototypes for Constructors */

/* Prototypes for class table members */
bool yaooc_mutex_lock(pointer);
bool yaooc_mutex_trylock(pointer);
bool yaooc_mutex_unlock(pointer);

/* Prototypes for class instance members */

/* Prototypes for class protected members */

/* New class table members for yaooc_mutex */
#define YAOOC_MUTEX_NEW_CLASS_MEMBERS \
  (bool(*) (pointer)) yaooc_mutex_lock, \
  (bool(*) (pointer)) yaooc_mutex_trylock, \
  (bool(*) (pointer)) yaooc_mutex_unlock, \

/* New plus parent members for yaooc_mutex */
#define YAOOC_MUTEX_CLASS_MEMBERS \
  { YAOOC_OBJECT_CLASS_MEMBERS }, \
  YAOOC_MUTEX_NEW_CLASS_MEMBERS

#endif
