#include "test_exception.h"

demo_exception_class_table_t demo_exception_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_exception_class_table,
.type_name_ = (const char*)"demo_exception_t",
.swap = (void(*)(pointer,pointer)) demo_exception_swap,
.what = (const char*(*)(const_pointer)) demo_exception_what,
.error_code = (int(*)(const_pointer)) demo_exception_error_code,
};
const type_info_t __demo_exception_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(demo_exception_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=NULL,
.dtor_=NULL,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &demo_exception_class_table,
.parent_=&__yaooc_exception_ti
};
const type_info_t* const demo_exception_ti=&__demo_exception_ti;
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <yaooc/exception.h>
#include <yaooc/pointer_bag.h>

#include "test_harness.h"
#include "demo_def.h"





demo2_exception_class_table_t demo2_exception_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_exception_class_table,
.type_name_ = (const char*)"demo2_exception_t",
.swap = (void(*)(pointer,pointer)) demo2_exception_swap,
.what = (const char*(*)(const_pointer)) demo2_exception_what,
.error_code = (int(*)(const_pointer)) demo2_exception_error_code,
};
const type_info_t __demo2_exception_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(demo2_exception_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=NULL,
.dtor_=NULL,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &demo2_exception_class_table,
.parent_=&__yaooc_exception_ti
};
const type_info_t* const demo2_exception_ti=&__demo2_exception_ti;
#if 0
yaooc_class_table(uncaught_exception)
{
  yaooc_exception_class_table_t;
};
yaooc_class_instance(uncaught_exception)
{
  yaooc_exception_class_instance_t;
};
yaooc_class(uncaught_exception);


uncaught_exception_class_table_t uncaught_exception_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_exception_class_table,
  .type_name_ = (const char*) "uncaught_exception_t",
  .swap = (void(*) (pointer,pointer)) yaooc_object_swap,
  .what = (const char*(*) (const_pointer)) yaooc_exception_what,
};

DEFINE_TYPE_INFO(uncaught_exception,N,N,N,N,N,N,N,Y,yaooc_exception);

#define uncaugh_exception_ctor_v yaooc_exception_ctor_v
#endif

char *path=output;
void sub(int x)
{
  TRY
  {
    strcat(path,":TRY_SUB");
    if(x==1) {
      strcat(path,":THROW1_SUB");
      THROW(new_ctor(demo_exception,demo_exception_ctor_v,x,"Inner Catch Level 1"));
    } else if(x==2) {
      strcat(path,":THROW2_SUB");
      THROW(new_ctor(demo2_exception,demo2_exception_ctor_v,x,"Catch Level 2"));
    }
  }
  CATCH(demo_exception,e)
  {
    strcat(path,":CATCH1_SUB");
  }
  ETRY
}

typedef struct {
  const char* desc;
  const char* path;
} test_result_t;

test_result_t results1[]=
  {
    { "Normal Flow -- no throw or catch","TRY_L1" },
    { "Throwing demo1 exception caught by yaooc exception" , "TRY_L1:THROW_1:CATCH_YE"},
    { "Throwing demo2 exception caught by yaooc exception" , "TRY_L1:THROW_2:CATCH_YE"},
    { "Throwing yaooc exception caught by yaooc exception" , "TRY_L1:THROW_YE:CATCH_YE"},
  };
void test_basic()
{
  TESTCASE("Single TRY/CATCH");
  int n=ARRAY_SIZE(results1);
  int i;
  for(i=0;i<n;i++) {
    TRY {
      strcpy(path,"TRY_L1");
      if(i==1) {
        strcat(path,":THROW_1");
        THROW(new(demo_exception));
      } else if(i==2) {
        strcat(path,":THROW_2");
        THROW(new(demo2_exception));
      } else if(i==3) {
        strcat(path,":THROW_YE");
        THROW(new(yaooc_exception));
      }
    } CATCH(yaooc_exception,ye) {
      strcat(path,":CATCH_YE");
    } ETRY

    TEST(results1[i].desc,strcmp(results1[i].path,path)==0);
  }

}

test_result_t results2[]=
  {
    { "Normal Flow -- no throw or catch","TRY_L1:TRY_SUB:END_TRY_L1" },
    { "Throw demo 1 exception caught by demo 1 exception" , "TRY_L1:THROW_1:CATCH_1"},
    { "Throw demo 2 exception caught by demo 2 exception" , "TRY_L1:THROW_2:CATCH_2"},
    { "Throw yaooc exception caught by yaooc exception" , "TRY_L1:THROW_YE:CATCH_YE"},
    { "Throw demo 1 exception from sub caught by demo 1 exception in sub" , "TRY_L1:TRY_SUB:THROW1_SUB:CATCH1_SUB:TRY_SUB:END_TRY_L1"},
    { "Throw demo 1 exception from sub caught by demo 1 exception outside sub" , "TRY_L1:TRY_SUB:THROW2_SUB:CATCH_2"},
  };


void test_multi_catch()
{
  TESTCASE("Multiple catches");
  int n=ARRAY_SIZE(results2);
  int i;
  for(i=0; i< n;i++) {
    TRY
    {
      strcpy(path,"TRY_L1");
      
      if(i==1) {
        strcat(path,":THROW_1");
        THROW(new(demo_exception));
      } else if(i==2) {
        strcat(path,":THROW_2");
        THROW(new_ctor(demo2_exception,demo2_exception_ctor_v,i,"Catch Level 2"));
      } else if(i==3) {
        strcat(path,":THROW_YE");
        THROW(new_ctor(yaooc_exception,yaooc_exception_ctor_v,i,"Catch Level 2"));
      } else if(i==4) {
        sub(1);
      } else if(i==5)
        sub(2);
      sub(0);
      strcat(path,":END_TRY_L1");
    }
    CATCH(demo_exception,e)
    {
      strcat(path,":CATCH_1");
    }
    CATCH(demo2_exception,e)
    {
      strcat(path,":CATCH_2");
    }
    CATCH(yaooc_exception,e)
    {
      strcat(path,":CATCH_YE");
    }
    ETRY

    TEST(results2[i].desc,strcmp(results2[i].path,path)==0);
  }
}


test_result_t results3[]=
  {
    { "Normal Flow -- no throw or catch","TRY_L1:END_TRY_L1" },
    { "Level 1 throw demo 1 exception caught by level 1 demo 1 exception" , "TRY_L1:THROW_L1_1:CATCH_L1_1"},
    { "Level 1 throw demo 2 exception caught by level 1 demo 2 exception" , "TRY_L1:THROW_L1_2:CATCH_L1_2"},
    { "Level 1 throw yaooc exception caught by level 1 yaooc exception" , "TRY_L1:THROW_L1_YE:CATCH_L1_YE"},
    { "Normal flow -- no throw or catch through level 2" , "TRY_L1:TRY_L2:END_TRY_L2:END_TRY_L1"},
    { "Level 2 throw demo 1 exception caught by level 2 demo 1 exception" ,
            "TRY_L1:TRY_L2:THROW_L2_1:CATCH_L2_1:END_TRY_L1"},
    { "Level 2 throw demo 2 exception caught by level 2 demo 2 exception and process in level 3" ,
            "TRY_L1:TRY_L2:THROW_L2_2:CATCH_L2_2:TRY_L3:END_TRY_L3:END_CATCH_L2_2:END_TRY_L1"},
    { "Level 2 throw demo 2 exception caught by level 2 demo2 exception and  throw yaooc exception and caught in level 1" ,
            "TRY_L1:TRY_L2:THROW_L2_2:CATCH_L2_2:TRY_L3:THROW_L3:CATCH_L3_1:END_CATCH_L3_1:END_CATCH_L2_2:END_TRY_L1"},
    { "Level 2 throw demo 2 exception caught by level 2 demo2 exception and " ,
          "TRY_L1:TRY_L2:THROW_L2_2:CATCH_L2_2:TRY_L3:THROW_L3:CATCH_L3_1:THROW_L3_YE:CATCH_L1_YE"},
    { "Throw demo 1 exception from sub caught by demo 1 exception in sub" ,
          "TRY_L1:TRY_L2:THROW_L2_YE:CATCH_L2_YE:END_TRY_L1"},
  };

void test_nested()
{
  TESTCASE("Nested TRY/CATCH");
  int i;
  int n = ARRAY_SIZE(results3);
  for(i=0;i<n;i++) {
    TRY { 
      strcpy(path,"TRY_L1");
      if(i==1) {
        strcat(path,":THROW_L1_1");
        THROW(new(demo_exception));
      } else if(i==2) {
        strcat(path,":THROW_L1_2");
        THROW(new(demo2_exception));
      } else if(i==3) {
        strcat(path,":THROW_L1_YE");
        THROW(new(yaooc_exception));
      } else if(i>3) {
        TRY {
          
          strcat(path,":TRY_L2");
          if(i==5) {
            strcat(path,":THROW_L2_1");
            THROW(new(demo_exception));
          } else  if(i>=6 && i<=8) {
            strcat(path,":THROW_L2_2");
            THROW(new(demo2_exception));
          } else  if(i==9) {
            strcat(path,":THROW_L2_YE");
            THROW(new(yaooc_exception));
          }
          strcat(path,":END_TRY_L2");
        } CATCH(demo_exception,ed) {
          strcat(path,":CATCH_L2_1");
        } CATCH(demo2_exception,ed2) {
          strcat(path,":CATCH_L2_2");
          TRY { 
            strcat(path,":TRY_L3");
            
            if(i>=7) {
              strcat(path,":THROW_L3");
              THROW(new(demo_exception));
            }
            strcat(path,":END_TRY_L3");
          } CATCH(demo_exception,aed) {
            strcat(path,":CATCH_L3_1");
            if(i==8) {
              strcat(path,":THROW_L3_YE");
              THROW(new(yaooc_exception));
            }
            strcat(path,":END_CATCH_L3_1");
          }
          ETRY
          strcat(path,":END_CATCH_L2_2");
        } CATCH(yaooc_exception,yye) {
          strcat(path,":CATCH_L2_YE");
        }
        ETRY
      }
      strcat(path,":END_TRY_L1");
    } CATCH(demo_exception,ed) {
      strcat(path,":CATCH_L1_1");
    } CATCH(demo2_exception,ed2) {
      strcat(path,":CATCH_L1_2");
    } CATCH(yaooc_exception,yye) {
      strcat(path,":CATCH_L1_YE");
    }
    ETRY

    TEST(results3[i].desc,strcmp(results3[i].path,path)==0);
  }
}

void test_throw_without_catch()
{
  printf("Throwing uncaught exeption. Program will terminate\n");
  TRY {
    THROW(new_ctor(yaooc_exception,yaooc_exception_ctor_v,0,"This exception is not caught"));
  }
  CATCH(demo2_exception,e) {
  }
  CATCH(demo_exception,e) {
  } ETRY
}

test_function tests[]=
{
  test_basic,
 	test_multi_catch,
  test_nested,
  test_throw_without_catch,
};

STD_MAIN(tests)

