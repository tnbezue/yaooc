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

#ifndef __YAOOC_EXCEPTION_INCLUDED__
#define __YAOOC_EXCEPTION_INCLUDED__
#include <setjmp.h>
#include <pthread.h>
#include <yaooc/object.h>
#include <yaooc/pointer_bag.h>

/*  Begin YAOOC PreProcessor generated content */

/*
  Class definition for yaooc_exception
*/
yaooc_class_table(yaooc_exception)
{
  yaooc_object_class_table_t;
  const char* (*what)(const_pointer);
};

yaooc_class_instance(yaooc_exception)
{
  yaooc_object_class_instance_t;
};

yaooc_class(yaooc_exception);

/* Prototypes for yaooc_exception type info */

/* Constructors for yaooc_exception */
#define yaooc_exception_default_ctor yaooc_object_default_ctor
#define yaooc_exception_dtor yaooc_object_dtor
#define yaooc_exception_copy_ctor yaooc_object_copy_ctor
#define yaooc_exception_assign yaooc_object_assign

/* Prototypes for yaooc_exception class table*/
const char* yaooc_exception_isa(const_pointer);
#define yaooc_exception_is_descendant yaooc_object_is_descendant
#define yaooc_exception_swap yaooc_object_swap
const char* yaooc_exception_what(const_pointer);

/* Prototypes for yaooc_exception class instance*/

/* Prototypes for yaooc_exception class protected items*/


/*  End YAOOC PreProcessor generated content */


yaooc_exception_pointer yaooc_exception_current_exception_thrown();

void yaooc_exception_remove_jmpbuf(pthread_t);
void yaooc_exception_thread_list_remove_exception_thread(pthread_t);
#define YAOOC_THREAD_CLEANUP yaooc_exception_thread_list_remove_exception_thread(pthread_self());

/*
  Macros/routines to implement TRY/CATCH
*/
void yaooc_exception_handled();

jmp_buf* yaooc_jmpbuf_new(void);

void __throw__(pointer);
bool __catch__(const char*);
void __rethrow_last_exception__();
pointer yaooc_exception_pointer_bag_save(pointer);
void yaooc_exception_pointer_bag_clear();
void yaooc_exception_pointer_bag_delete();

typedef struct yaooc_exception_thread_jmpbuf_node_s yaooc_exception_thread_jmpbuf_node_t;
yaooc_exception_thread_jmpbuf_node_t* yaooc_exception_thread_jmpbuf_list_find_jmpbuf(pthread_t);

#define EPB_SAVE(ptr) yaooc_exception_pointer_bag_save(ptr)
#define EPB_CLEAR  yaooc_exception_pointer_bag_clear(ptr)
#define EPB_DELETE yaooc_exception_pointer_bag_delete(ptr)

/*
  throw an exception
*/
#define THROW(e) \
    __throw__(e);

#define TRY if(setjmp(*yaooc_jmpbuf_new()) == 0) { \
    do {

#define CATCH(exception_type,e) \
    /* No exception thrown or exception was caught in preceding block */ \
    } while(0); \
    yaooc_exception_handled(); \
  } else  \
      /* Exception thrown not caught by preceding block. Check if it should be caught here */ \
  if(__catch__(# exception_type "_t")) {  do { \
    exception_type ## _const_pointer e=(exception_type ## _const_pointer)yaooc_exception_current_exception_thrown();

#define ETRY \
    } while(0); \
    /* No exception thrown or exception was caught in preceding block */ \
    yaooc_exception_handled(); \
} else  {\
    /* Exception not caught by any catch block in the TRY/ETRY section -- rethrow */ \
    __rethrow_last_exception__(); \
}

#endif
