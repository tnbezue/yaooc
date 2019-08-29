/*
		Copyright (C) 2016-2018  by Terry N Bezue

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

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <yaooc/thread.h>
#include <yaooc/exception.h>
#include <yaooc/map.h>
#include <sys/types.h>
#include <sys/time.h>
#include "test_harness.h"

#define USLEEP_MIN 10000
#define USLEEP_MAX 1000000

void test_init()
{
  init_exceptions();
}

yaooc_thread_pointer create_threads(int n,yaooc_thread_method method)
{
  return new_array_ctor(yaooc_thread,n,yaooc_thread_ctor_method,method);
}

void* test_thread_method(pointer p,void* data)
{
  yaooc_thread_pointer this=p;
  int i;
  for(i=0;!this->request_exit_;i++) {
    printf("%" PRIINT " %" PRILONG "\n",i,this->thread_id_);
    sleep(1);
  }
  printf("Exit requested for %" PRIULONG "\n",this->thread_id_);
  return NULL;
}

/* Scramble order of threads */
void scramble(int* ary,int n)
{
  if(n>1) {
    int i;
    for(i=0;i<n;i++) {
      int j=rand() % n;
      int k=rand() % n;
      if(j!=k) {
        SWAP(int,ary[j],ary[k]);
      }
    }
  }

}

void test_thread(int n,yaooc_thread_method method)
{
  yaooc_thread_pointer threads=create_threads(n,method);
  int i;
  int *indexes = MALLOC(n*sizeof(int));
  for(i=0;i<n;i++) {
    M(threads+i,start,NULL);
    indexes[i]=i;
  }
  scramble(indexes,n);
  for(i=0;i<n;i++) {
    int sleep_time=rand() % 5 + 1;
    int it=indexes[i];
    printf("Waiting %" PRIINT " seconds for thread %" PRIINT " with id of %" PRIULONG "\n",sleep_time,it,M(threads+it,id));
    sleep(sleep_time);
    M(threads+it,cancel);
    M(threads+it,join);
  }
  delete(threads);
  FREE(indexes);
}

void test_single_thread()
{
  test_thread(1,test_thread_method);
}

#define N_TEST_THREADS 5
void test_multiple_thread_using_thread_function(yaooc_thread_method method)
{
  yaooc_thread_t threads[N_TEST_THREADS];
  int i;
  newp_array_ctor(threads,yaooc_thread,N_TEST_THREADS,yaooc_thread_ctor_method,method);
  for(i=0;i<N_TEST_THREADS;i++) {
    TEST("Thread started",M(threads+i,start,NULL));
  }
  sleep(1);
  for(i=0;i<N_TEST_THREADS;i++) {
    M(threads+i,join);
  }
  deletep_array(threads,yaooc_thread,N_TEST_THREADS);
}

void test_multiple_thread()
{
  test_thread(N_TEST_THREADS,test_thread_method);
}

yaooc_mutex_t mutex;
void* test_thread_with_mutex(pointer p,void* data)
{
  yaooc_thread_pointer this=p;
  int i;
  for(i=0;!this->request_exit_;i++) {
    printf("Thread %" PRIULONG " waiting for lock\n",M(this,id));
    M(&mutex,lock);
    printf("Thread %" PRIULONG " is holding lock\n",M(this,id));
    sleep(1);
    M(&mutex,unlock);
    sleep(1);
  }
  printf("Thread %" PRIULONG " is terminating\n",M(this,id));
  return NULL;
}

void test_mutex()
{
  newp(&mutex,yaooc_mutex);
  yaooc_thread_pointer threads=new_array_ctor(yaooc_thread,N_TEST_THREADS,yaooc_thread_ctor_method,test_thread_with_mutex);
  int i;
  for(i=0;i<N_TEST_THREADS;i++) {
    M(threads+i,start,NULL);
  }
  for(i=0;i<N_TEST_THREADS;i++) {
    int sleep_time=rand() % 5 + 1;
    printf("Sleeping %" PRIINT " seconds before requesting thread %" PRIULONG " to exit\n",sleep_time,M(threads+i,id));
    sleep(sleep_time);
    M(threads+i,cancel);
    M(threads+i,join);
  }

//  test_multiple_thread_using_thread_function(mythread_run_with_mutex);
//  test_thread(N_TEST_THREADS,test_thread_with_mutex);
}
#if 0
yaooc_condition_variable_t cond_var;
yaooc_condition_variable_t last_thread_finished;
int n_threads_remaining=N_TEST_THREADS;
double sleep_time;
void* test_thread_with_condition_variable(pointer p,void* data)
{
  yaooc_thread_pointer this=p;
  long thread_id=M(this,id);
  double* limit=data;
  double total_time=0;
  do {
    printf("Thread %" PRIULONG " waiting for signal\n",M(this,id));
    M(&cond_var,lock);
    M(&cond_var,wait);
    printf("Thread %" PRIULONG " has received signal\n",M(this,id));
    printf("Adding %lg to total time\n",sleep_time);
    total_time+=sleep_time;
    M(&cond_var,unlock);
  } while (total_time <= *limit);
  printf("Thread %" PRIULONG " has exceeded wait time limit of %lg by waiting %lg seconds and is now finished\n",thread_id,*limit,total_time);
  if(--n_threads_remaining == 0) {
    puts("last thread");
    M(&last_thread_finished,signal);
  }
  return NULL;
}

void test_condition_variable_signal()
{
  yaooc_thread_pointer threads=new_array_ctor(yaooc_thread,N_TEST_THREADS,yaooc_thread_ctor_method,test_thread_with_condition_variable);
  int i;
  newp(&cond_var,yaooc_condition_variable);
  newp(&last_thread_finished,yaooc_condition_variable);
  double time_limits[N_TEST_THREADS];
  for(i=0;i<N_TEST_THREADS;i++) {
    time_limits[i]=rand() % 20 + 5;
    M(threads+i,start,time_limits+i);
  }
  while(true) {
    sleep_time = rand() % 5 + 1.5;
    printf("Sleeping %lg seconds before signaling next\n",sleep_time);
    M(&last_thread_finished,lock);
    int rc = M(&last_thread_finished,timedwait,sleep_time);
    M(&last_thread_finished,unlock);
    if(rc == 0)
      break;
    M(&cond_var,signal);
  }
  for(i=0;i<N_TEST_THREADS;i++) {
    M(threads+i,join);
  }
  delete(threads);
}

void test_condition_variable_broadcast()
{
  yaooc_thread_pointer threads=new_array_ctor(yaooc_thread,N_TEST_THREADS,yaooc_thread_ctor_method,test_thread_with_condition_variable);
  int i;
  newp(&cond_var,yaooc_condition_variable);
  newp(&last_thread_finished,yaooc_condition_variable);
  double time_limits[N_TEST_THREADS];
  for(i=0;i<N_TEST_THREADS;i++) {
    time_limits[i]=rand() % 20 + 5;
    M(threads+i,start,time_limits+i);
  }
  while(true) {
    sleep_time = rand() % 5 + 1.5;
    printf("Sleeping %lg seconds before signaling next\n",sleep_time);
    M(&last_thread_finished,lock);
    int rc = M(&last_thread_finished,timedwait,sleep_time);
    M(&last_thread_finished,unlock);
    if(rc == 0)
      break;
    M(&cond_var,broadcast);
  }
  for(i=0;i<N_TEST_THREADS;i++) {
    M(threads+i,join);
  }
  delete(threads);
}
#endif
yaooc_class_table(custom_exception)
{
  yaooc_exception_class_table_t;
};

yaooc_class_instance(custom_exception)
{
  yaooc_exception_class_instance_t;
  yaooc_internal_thread_t id_;
};

yaooc_class(custom_exception);


void custom_exception_default_ctor(pointer p)
{
  custom_exception_pointer this=p;
  puts("Creating exception");
  this->id_=yaooc_current_thread_id();
}

custom_exception_class_table_t custom_exception_class_table=
{
  .parent_class_table_ = (const class_table_t*) &yaooc_exception_class_table,
  .type_name_ = (const char*) "custom_exception_t",
  .swap = (void (*) (pointer p,pointer)) yaooc_exception_swap,
  .what = (const char* (*) (const_pointer p)) yaooc_exception_what,
};

DEFINE_TYPE_INFO(custom_exception,Y,N,N,N,N,N,N,Y,yaooc_exception);


void* test_thread_exception(pointer p,void* data)
{
  yaooc_thread_pointer this=p;
  int i;
  sleep(3);
  for(i=0;i<5;i++) {
    TRY
    {
      printf("E %" PRIINT " %" PRIULONG "\n",i,this->thread_id_);
      fflush(stdout);
      usleep(rand() % (USLEEP_MAX + 1 - USLEEP_MIN) + USLEEP_MIN);
      THROW(new(custom_exception));
    } CATCH(custom_exception,e) {
      printf("Caught exception %" PRIINT " %" PRIULONG " %" PRIINT "\n",i,this->thread_id_,e->id_==yaooc_current_thread_id());
      fflush(stdout);
    }
    ETRY
  }
  return NULL;
}

void test_exception()
{
  test_multiple_thread_using_thread_function(test_thread_exception);
}

test_function tests[]=
{
 	test_single_thread,
  test_multiple_thread,
//  test_condition_variable_signal,
//  test_condition_variable_broadcast,
  test_mutex,
  test_exception
};

STD_MAIN(tests)
