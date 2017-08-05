#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <yaooc/thread.h>
#include <yaooc/exception.h>
#include <sys/types.h>
#include "test_harness.h"

class_table(mythread)
{
  yaooc_thread_class_members_t;
};

class_instance(mythread)
{
  yaooc_thread_instance_members_t;
};

#define MYTHREAD_CLASS_MEMBERS \
  { \
    { YAOOC_OBJECT_CLASS_MEMBERS }, \
    (pthread_t(*) (const_pointer)) yaooc_thread_id, \
    (int(*) (pointer)) yaooc_thread_join, \
    (int(*) (pointer)) yaooc_thread_cancel, \
    (int(*) (pointer)) yaooc_thread_detach, \
    (yaooc_thread_state_t(*) (const_pointer)) yaooc_thread_state, \
    (bool(*) (const_pointer)) yaooc_thread_is_detached, \
    (bool (*) (pointer)) yaooc_thread_start, \
    (void*(*) (pointer)) mythread_run, \
  }

class(mythread);

#define USLEEP_MIN 10000
#define USLEEP_MAX 1000000
void* mythread_run(pointer p)
{
  mythread_pointer this=p;
  int i;
  for(i=0;i<5;i++) {
    printf("%d %ld\n",i,this->thread_id_);
    usleep(rand() % (USLEEP_MAX + 1 - USLEEP_MIN) + USLEEP_MIN);
//    sleep(1);
  }
  return NULL;
}

void mythread_default_ctor(pointer p)
{
//  mythread_pointer this=p;
  yaooc_thread_default_ctor(p);
}

mythread_class_members_t mythread_class_members = { MYTHREAD_CLASS_MEMBERS };

DEFINE_TYPE_INFO(mythread,mythread_default_ctor,NULL,NULL,NULL,NULL,&mythread_class_members,yaooc_thread)

void test_single_thread()
{
  srand(time(NULL));
  mythread_pointer mt=new(mythread);
  if(M(mt,start)) {
    sleep(1);
    M(mt,join);
  } else
    puts("Failed to start");
  delete(mt);
}

#define N_TEST_THREADS 5
void test_multiple_thread()
{
  srand(time(NULL));
  mythread_t threads[N_TEST_THREADS];
  int i;
  for(i=0;i<N_TEST_THREADS;i++) {
    newp(threads+i,mythread);
    TEST("Thread started",M(threads+i,start));
  }
  sleep(1);
  for(i=0;i<N_TEST_THREADS;i++) {
    M(threads+i,join);
    deletep(threads+i,mythread);
  }
}

yaooc_mutex_t mutex;
void* mythread_run_with_mutex(pointer p)
{
  mythread_pointer this=p;
  int i;
  for(i=0;i<5;i++) {
    M(&mutex,lock);
    printf("M %d %ld\n",i,this->thread_id_);
    M(&mutex,unlock);
    usleep(rand() % (USLEEP_MAX + 1 - USLEEP_MIN) + USLEEP_MIN);
  }
  return NULL;
}


void test_mutex()
{
  mythread_class_members.run=mythread_run_with_mutex;
  newp(&mutex,yaooc_mutex);
  test_multiple_thread();
  mythread_class_members.run=mythread_run;
}

class_table(custom_exception)
{
  yaooc_exception_class_members_t;
};

class_instance(custom_exception)
{
  yaooc_exception_instance_members_t;
  pthread_t id_;
};

class(custom_exception);

ISA_DEFINITION(custom_exception,yaooc_exception)
ISA_IMPLEMENTATION(custom_exception,yaooc_exception)

void custom_exception_default_ctor(pointer p)
{
  custom_exception_pointer this=p;
  puts("Creating exception");
  this->id_=pthread_self();
}

custom_exception_class_members_t custom_exception_class_members=
{{
  {
    custom_exception_isa,
    custom_exception_is_descendent,
    yaooc_object_swap
  },
  yaooc_exception_what
}};

DEFINE_TYPE_INFO(custom_exception,custom_exception_default_ctor,NULL,NULL,NULL,NULL,
      &custom_exception_class_members,yaooc_exception)


void* mythread_run_with_exception(pointer p)
{
  mythread_pointer this=p;
  int i;
  sleep(3);
  for(i=0;i<5;i++) {
    TRY {
      printf("E %d %ld\n",i,this->thread_id_);
      usleep(rand() % (USLEEP_MAX + 1 - USLEEP_MIN) + USLEEP_MIN);
      THROW(new(custom_exception));
    } CATCH(custom_exception,e) {
      printf("Caught exception %d %ld %d\n",i,this->thread_id_,e->id_==pthread_self());
    }
    ETRY
  }
  return NULL;
}

void test_exception()
{
  mythread_class_members.run=mythread_run_with_exception;
  test_multiple_thread();
  mythread_class_members.run=mythread_run;
}


test_function tests[]=
{
 	test_single_thread,
  test_multiple_thread,
  test_mutex,
  test_exception
};

STD_MAIN(tests)
