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
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <yaooc/exception.h>
#include <yaooc/pointer_bag.h>
#include "test_harness.h"
#include "demo_def.inc"
#include <pthread.h>

yaooc_class_table(demo_exception)
{
  yaooc_exception_class_table_t;
};

yaooc_class_instance(demo_exception)
{
  yaooc_exception_class_instance_t;
  char* msg_;
};

yaooc_class(demo_exception);

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

demo_exception_class_table_t demo_exception_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_exception_class_table,
  .type_name_ = (const char*) "demo_exception_t",
  .swap = (void(*) (pointer,pointer)) yaooc_object_swap,
  .what = (const char*(*) (const_pointer)) demo_exception_what,

};

DEFINE_TYPE_INFO(demo_exception,Y,Y,N,N,N,N,N,Y,yaooc_exception)

void demo_exception_ctor_ccs(pointer p,va_list args)
{
  const char* str=va_arg(args,const char*);
  ((demo_exception_pointer)p)->msg_=str?STRDUP(str):NULL;
}

/*  *** */

yaooc_class_table(demo2_exception)
{
  yaooc_exception_class_table_t;
};

yaooc_class_instance(demo2_exception)
{
  yaooc_exception_class_instance_t;
  char* msg_;
};

yaooc_class(demo2_exception);

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

demo2_exception_class_table_t demo2_exception_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_exception_class_table,
  .type_name_ = (const char*) "demo2_exception_t",
  .swap = (void(*) (pointer,pointer)) yaooc_object_swap,
  .what = (const char*(*) (const_pointer)) demo2_exception_what,
};

DEFINE_TYPE_INFO(demo2_exception,Y,Y,N,N,N,N,N,Y,yaooc_exception)

void demo2_exception_ctor_ccs(pointer p,va_list args)
{
  const char* str=va_arg(args,const char*);
  ((demo2_exception_pointer)p)->msg_=str?STRDUP(str):NULL;
}


/* **** */

yaooc_class_table(uncaught_exception)
{
  yaooc_exception_class_table_t;
};
yaooc_class_instance(uncaught_exception)
{
  yaooc_exception_class_instance_t;
  char* msg_;
};
yaooc_class(uncaught_exception);


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

uncaught_exception_class_table_t uncaught_exception_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_exception_class_table,
  .type_name_ = (const char*) "uncaught_exception_t",
  .swap = (void(*) (pointer,pointer)) yaooc_object_swap,
  .what = (const char*(*) (const_pointer)) uncaught_exception_what,
};

DEFINE_TYPE_INFO(uncaught_exception,Y,Y,N,N,N,N,N,Y,yaooc_exception)

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
  int n=ARRAY_SIZE(tries);
  int i;
  yaooc_exception_thread_jmpbuf_node_t* tl=yaooc_exception_thread_jmpbuf_list_find_jmpbuf(pthread_self());
  for(i=0; i<n;i++) {
    int x=tries[i].x;
    if(x==4) {
      FINAL_SUMMARY;
      puts("*****\nThe next test throws an uncaught exception which terminates this program\n*****");
    }
    TRY
    {
      tl=yaooc_exception_thread_jmpbuf_list_find_jmpbuf(pthread_self());
      TEST("Thread list is not NULL",tl!=NULL);
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
        puts("Throwing uncaught");
        THROW(new_ctor(uncaught_exception,uncaught_exception_ctor_ccs,"Uncaught"))
      }
      sub(x);
      result=0;
    }
    CATCH(demo_exception,e)
    {
      printf("Caught %s in block 1\n",TYPE(e));
      result=1;
      TEST("Exception caught in block 1",strcmp(M(e,what),"Catch Block 1")==0);
    }
    CATCH(demo2_exception,e)
    {
      printf("Caught %s in block 2\n",TYPE(e));
      result=2;
      printf(" ZZZZ %s\n",M(e,what));
      TEST("Exception caught in block 2",strcmp(M(e,what),"Catch Block 2")==0);
    }
    ETRY
    char result_msg[128];
    sprintf(result_msg,"Result = %d for x = %d",tries[i].catch_block,tries[i].x);
    printf("*** %d\n",tries[i].catch_block);
    TEST(result_msg,result==tries[i].catch_block);
  }
}

void test_nested()
{
  PB_INIT;
  int i;
//  yaooc_exeception_pointer ptr;
  char* path=PB_SAVE(new_array(char,1024));
  for(i=0;i<10;i++) {
    path[0]=0;
//    et[0]=0;
    TRY { /* TB1 */
        strcat(path,"TB1");
      if(i==1) {
        THROW(new(demo_exception));
      }
      if(i==2) {
        THROW(new(demo2_exception));
      }
      if(i==3) {
        THROW(new(yaooc_exception));
      }
      if(i>3) {
        TRY { /* TB2 */
          strcat(path,"TB2");
          if(i==4) {
            THROW(new(demo_exception));
          } else  if(i==5) {
            THROW(new(demo2_exception));
          }
        } CATCH(demo_exception,ed) {  /* CB2_1 */
          strcat(path,"CB2_1");
          strcat(path,TYPE(ed));
        } CATCH(demo2_exception,ed2) { /* CB2_2 */
          strcat(path,"CB_2");
          strcat(path,TYPE(ed2));
          if(i==6) {
            TRY { /* CB2_T1 */
              THROW(new(demo_exception));
            } CATCH(demo_exception,aed) { /* CB2_CB1 */
              M(aed,what);  // just to avoid warning of unused variable
              THROW(new(yaooc_exception));
            }
            ETRY
          }
        } CATCH(yaooc_exception,ye) { /* CB2_3 */
          M(ye,what);
        }
        ETRY
      }
    } CATCH(yaooc_exception,yye) { /* CB1 */
			M(yye,what);
    }
    ETRY
    printf("%d %s\n",i,path);
    switch(i) {
      case 0:
        TEST("i==0: 'TB1'",strcmp(path,"TB1")==0);
        break;

      case 1:
        TEST("Exception what is 'L1:DE1'",strcmp(path,"L1:DE1")==0);
        break;

      case 2:
        TEST("Exception what is 'L1:DE2'",strcmp(path,"L1:DE2")==0);
        break;

      case 3:
        TEST("Exception what is empty",path[0]==0);
        break;

      case 4:
          TEST("Exception what is 'L1:DE1'",strcmp(path,"L2:DE1")==0);
          break;

      case 5:
        TEST("Exception what is 'L2:DE2'",strcmp(path,"L2:DE2")==0);
        break;

    }
  }
  PB_EXIT;
}

void test_throw_without_catch()
{
  THROW(new(yaooc_exception));
}
test_function tests[]=
{
 	test_exception,
  test_nested,
  test_throw_without_catch,
};

STD_MAIN(tests)
