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

#ifndef __THREAD_INCLUDED__
#define __THREAD_INCLUDED__

#include <yaooc/object.h>
#include <yaooc/exception.h>

#include <pthread.h>

typedef enum { THREAD_READY=0,THREAD_RUNNING,THREAD_TERMINATED } yaooc_thread_state_t;

#ifdef __cplusplus
extern "C" {
#endif

typedef void* (*yaooc_thread_method) (pointer,void*);
/*  Begin YAOOC PreProcessor generated content */


/*
  Class definition for yaooc_thread
*/
yaooc_class_table(yaooc_thread)
{
  yaooc_object_class_table_t;
  pthread_t (*id)(const_pointer);
  int (*join)(pointer);
  int (*cancel)(pointer);
  int (*detach)(pointer);
  yaooc_thread_state_t (*state)(const_pointer);
  bool (*is_detached)(const_pointer);
  bool (*start)(pointer,void*);
};

yaooc_class_instance(yaooc_thread)
{
  yaooc_object_class_instance_t;
  yaooc_thread_method method;
  pthread_t thread_id_;
  yaooc_thread_state_t state_;
  bool is_detached_;
  bool request_exit_;
};

yaooc_class(yaooc_thread);
/* Prototypes for yaooc_thread type info */
void yaooc_thread_default_ctor(pointer);
void yaooc_thread_dtor(pointer);

/* Constructors for yaooc_thread */
void yaooc_thread_ctor_method(pointer,va_list);

/* Prototypes for yaooc_thread class table*/
#define yaooc_thread_swap yaooc_object_swap
pthread_t yaooc_thread_id(const_pointer);
int yaooc_thread_join(pointer);
int yaooc_thread_cancel(pointer);
int yaooc_thread_detach(pointer);
yaooc_thread_state_t yaooc_thread_state(const_pointer);
bool yaooc_thread_is_detached(const_pointer);
bool yaooc_thread_start(pointer,void*);

/* Prototypes for yaooc_thread class instance*/

/* Prototypes for yaooc_thread class protected items*/


/*
  Class definition for yaooc_mutex
*/
yaooc_class_table(yaooc_mutex)
{
  yaooc_object_class_table_t;
  bool (*lock)(pointer);
  bool (*trylock)(pointer);
  bool (*unlock)(pointer);
};

yaooc_class_instance(yaooc_mutex)
{
  yaooc_object_class_instance_t;
  pthread_mutex_t mutex_;
};

yaooc_class(yaooc_mutex);
/* Prototypes for yaooc_mutex type info */
void yaooc_mutex_default_ctor(pointer);
void yaooc_mutex_dtor(pointer);

/* Constructors for yaooc_mutex */

/* Prototypes for yaooc_mutex class table*/
#define yaooc_mutex_swap yaooc_object_swap
bool yaooc_mutex_lock(pointer);
bool yaooc_mutex_trylock(pointer);
bool yaooc_mutex_unlock(pointer);

/* Prototypes for yaooc_mutex class instance*/

/* Prototypes for yaooc_mutex class protected items*/

/*  End YAOOC PreProcessor generated content */

/*
  Class definition for yaooc_condition_variable
*/
yaooc_class_table(yaooc_condition_variable)
{
  yaooc_mutex_class_table_t;
  bool (*signal)(pointer);
  bool (*broadcast)(pointer);
  int (*wait)(pointer);
  int (*timedwait)(pointer,double);
};

yaooc_class_instance(yaooc_condition_variable)
{
  yaooc_mutex_class_instance_t;
  pthread_cond_t condition_variable_;
};

yaooc_class(yaooc_condition_variable);
/* Prototypes for yaooc_condition_variable type info */
void yaooc_condition_variable_default_ctor(pointer);
void yaooc_condition_variable_dtor(pointer);

/* Constructors for yaooc_condition_variable */

/* Prototypes for yaooc_condition_variable class table*/
#define yaooc_condition_variable_swap yaooc_mutex_swap
#define yaooc_condition_variable_lock yaooc_mutex_lock
#define yaooc_condition_variable_trylock yaooc_mutex_trylock
#define yaooc_condition_variable_unlock yaooc_mutex_unlock
bool yaooc_condition_variable_signal(pointer);
bool yaooc_condition_variable_broadcast(pointer);
int yaooc_condition_variable_wait(pointer);
int yaooc_condition_variable_timedwait(pointer,double);

/* Prototypes for yaooc_condition_variable class instance*/

/* Prototypes for yaooc_condition_variable class protected items*/

#ifdef __cplusplus
}
#endif

#endif
