#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <yaooc/exception.h>
#include "test_harness.h"
#include "demo_def.inc"
#include <pthread.h>

class_table(demo_exception)
{
  yaooc_exception_class_members_t;
};
class_instance(demo_exception)
{
  char* msg_;
};
class(demo_exception);

ISA_IMPLEMENTATION(demo_exception,yaooc_exception)

void demo_exception_default_ctor(pointer p)
{
  ((demo_exception_pointer)p)->msg_=NULL;
}

void demo_exception_dtor(pointer p)
{
  demo_exception_pointer this=p;
  if(this->msg_!=NULL)
    FREE(this->msg_);
}

const char* demo_exception_what(const_pointer p)
{
  return ((demo_exception_const_pointer)p)->msg_;
}

demo_exception_class_members_t demo_exception_class_members =
{
  {
    {
      demo_exception_isa,
      demo_exception_is_descendent,
      yaooc_object_swap
    },
    demo_exception_what
  }
};

DEFINE_TYPE_INFO(demo_exception,demo_exception_default_ctor,demo_exception_dtor,NULL,NULL,NULL,&demo_exception_class_members,yaooc_exception)

void demo_exception_ctor_ccs(pointer p,va_list args)
{
  const char* str=va_arg(args,const char*);
  ((demo_exception_pointer)p)->msg_=str?STRDUP(str):NULL;
}

/*  *** */

class_table(demo2_exception)
{
  yaooc_exception_class_members_t;
};
class_instance(demo2_exception)
{
  char* msg_;
};
class(demo2_exception);

ISA_IMPLEMENTATION(demo2_exception,yaooc_exception)

void demo2_exception_default_ctor(pointer p)
{
  ((demo2_exception_pointer)p)->msg_=NULL;
}

void demo2_exception_dtor(pointer p)
{
  demo2_exception_pointer this=p;
  if(this->msg_!=NULL)
    FREE(this->msg_);
}

const char* demo2_exception_what(const_pointer p)
{
  return ((demo2_exception_const_pointer)p)->msg_;
}

demo2_exception_class_members_t demo2_exception_class_members =
{
  {
    {
      demo2_exception_isa,
      demo2_exception_is_descendent,
      yaooc_object_swap
    },
    demo2_exception_what
  }
};

DEFINE_TYPE_INFO(demo2_exception,demo2_exception_default_ctor,demo2_exception_dtor,NULL,NULL,NULL,&demo2_exception_class_members,yaooc_exception)

void demo2_exception_ctor_ccs(pointer p,va_list args)
{
  const char* str=va_arg(args,const char*);
  ((demo2_exception_pointer)p)->msg_=str?STRDUP(str):NULL;
}


/* **** */

class_table(uncaught_exception)
{
  yaooc_exception_class_members_t;
};
class_instance(uncaught_exception)
{
  char* msg_;
};
class(uncaught_exception);

ISA_IMPLEMENTATION(uncaught_exception,yaooc_exception)

void uncaught_exception_default_ctor(pointer p)
{
  ((uncaught_exception_pointer)p)->msg_=NULL;
}

void uncaught_exception_dtor(pointer p)
{
  uncaught_exception_pointer this=p;
  if(this->msg_!=NULL)
    FREE(this->msg_);
}

const char* uncaught_exception_what(const_pointer p)
{
  return ((uncaught_exception_const_pointer)p)->msg_;
}

uncaught_exception_class_members_t uncaught_exception_class_members =
{
  {
    {
      uncaught_exception_isa,
      uncaught_exception_is_descendent,
      yaooc_object_swap
    },
    uncaught_exception_what
  }
};

DEFINE_TYPE_INFO(uncaught_exception,uncaught_exception_default_ctor,uncaught_exception_dtor,NULL,NULL,NULL,&uncaught_exception_class_members,yaooc_exception)

void uncaught_exception_ctor_ccs(pointer p,va_list args)
{
  const char* str=va_arg(args,const char*);
  ((uncaught_exception_pointer)p)->msg_=str?STRDUP(str):NULL;
}

/*  ****  */
int result=-10;

typedef struct {
  int x;
  int catch_block;
} test_data_t;

void sub(int x)
{
  TRY
  {
    printf("X is %d\n",x);
    if(x==10) {
      result=10;
    } else if(x==11) {
      THROW(new_ctor(demo_exception,demo_exception_ctor_ccs,"Inner Catch Block 1"));
    } else if(x==12) {
      THROW(new_ctor(demo2_exception,demo2_exception_ctor_ccs,"Catch Block 2"))
    }
  }
  CATCH(demo_exception,e)
  {
    result=11;
    TEST("Exception caught in block 1",strcmp(M(e,what),"Inner Catch Block 1")==0);
  }
  ETRY
}

yaooc_exception_thread_t* yaooc_exception_thread_list_find_or_create_exception_thread(pthread_t tid,bool create_flag);
void test_exception()
{
  test_data_t tries[] =
  {
    { 0, 0 },
    { 1, 0 },
    { 2, 1 },
    { 3, 2 },
    { 5, 0 },
    { 10, 0 },  /* no exception occurs in sub */
    { 11, 0 },  /* exception is handled in sub and it returns normally */
    { 12, 2 },  /* exception is not handled in sub */
    { 4, -1 },
  };
  TESTCASE("Basic Exception");
  yaooc_exception_thread_t* et=yaooc_exception_thread_list_find_or_create_exception_thread(pthread_self(),true);
  TEST("Jump buffer stack top is NULL",et->current_jmpbuf_==NULL);
  int n=ARRAY_SIZE(tries);
  int i;
  for(i=0; i<n;i++) {
    int x=tries[i].x;
    if(x==4) {
      FINAL_SUMMARY;
      puts("*****\nThis next test throws an uncaught exception which terminates this program\n*****");
    }
    TRY
    {
      /* Intentionally did not use a switch statement */
      if(x==0) {
        result=0;
      } else if(x==1) {
        result=0;
        break; // breaks out of TRY/CATCH block
      } else if(x==2) {
        THROW(new_ctor(demo_exception,demo_exception_ctor_ccs,"Catch Block 1"))
      } else if(x==3) {
        THROW(new_ctor(demo2_exception,demo2_exception_ctor_ccs,"Catch Block 2"))
      } else if(x == 4 ) {
        THROW(new_ctor(uncaught_exception,uncaught_exception_ctor_ccs,"Uncaught"))
      }
      sub(x);
      result=0;
    }
    CATCH(demo_exception,e)
    {
      result=1;
      TEST("Exception caught in block 1",strcmp(M(e,what),"Catch Block 1")==0);
    }
    CATCH(demo2_exception,e)
    {
      result=2;
      TEST("Exception caught in block 2",strcmp(M(e,what),"Catch Block 2")==0);
    }
    ETRY
    char result_msg[128];
    sprintf(result_msg,"Result = %d for x = %d",tries[i].catch_block,tries[i].x);
    TEST(result_msg,result==tries[i].catch_block);
  }
}

test_function tests[]=
{
 	test_exception,
};

STD_MAIN(tests)
