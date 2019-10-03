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

#ifndef __YAOOC_EXCEPTION_INCLUDED__
#define __YAOOC_EXCEPTION_INCLUDED__

#include <setjmp.h>
#include <yaooc/object.h>
#include <yaooc/thread.h>

void init_exceptions();

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
	char* what_;
};

yaooc_class(yaooc_exception);

/* Prototypes for yaooc_exception type info */
void yaooc_exception_default_ctor(pointer);
void yaooc_exception_dtor(pointer);
void yaooc_exception_copy_ctor(pointer,const_pointer);
void yaooc_exception_assign(pointer,const_pointer);

/* Constructors for yaooc_exception */
void yaooc_exception_ctor_v(pointer,va_list);

/* Prototypes for yaooc_exception class table*/
void yaooc_exception_swap(pointer,pointer);
const char* yaooc_exception_what(const_pointer);

/* Prototypes for yaooc_exception class instance*/

/* Prototypes for yaooc_exception class protected items*/


/*  End YAOOC PreProcessor generated content */


//#define YAOOC_THREAD_CLEANUP yaooc_exception_thread_list_remove_exception_thread(yaooc_current_thread_id());

/*
  Macros/routines to implement TRY/CATCH
*/
void __yaooc_exception_handled__();

jmp_buf* yaooc_jmpbuf_new();
yaooc_exception_pointer yaooc_exception_current_exception_thrown();
void __throw__(pointer);
bool __catch__(const char*);
void __rethrow_last_exception__();

pointer yaooc_exception_pointer_bag_save(pointer);
pointer yaooc_exception_pointer_bag_save_static_array(pointer,const type_info_t*,size_t);
void yaooc_exception_pointer_bag_clear();
void yaooc_exception_pointer_bag_delete();

/*
  throw an exception
*/
#define THROW(e) \
    __throw__(e)

#define TRY if(setjmp(*yaooc_jmpbuf_new()) == 0) { \
     {

#define CATCH(exception_type,e) \
    /* No exception thrown or exception was caught in preceding block */ \
    }  \
    __yaooc_exception_handled__(); \
  } else  \
      /* Exception thrown not caught by preceding block. Check if it should be caught here */ \
  if(__catch__(# exception_type "_t")) {   { \
    exception_type ## _const_pointer e=(exception_type ## _const_pointer)yaooc_exception_current_exception_thrown(); \
    (void) e;

#define ETRY \
    }  \
    /* No exception thrown or exception was caught in preceding block */ \
    __yaooc_exception_handled__(); \
} else  {\
    /* Exception not caught by any catch block in the TRY/ETRY section -- rethrow */ \
    __rethrow_last_exception__(); \
}

#define epb_save(ptr) yaooc_exception_pointer_bag_save(ptr)

#define epb_new(T)         epb_save(new(T))
#define epb_new_array(T,N) epb_save(new_array(T,N))
#define epb_new_copy(P)    epb_save(new_copy(P))
#define epb_new_array_copy(P,N)    epb_save(new_array_copy(P,N))
#define epb_new_ctor(T,CON,...)     epb_save(new_ctor(T,CON,## __VA_ARGS__))
#define epb_new_array_ctor(T,N,...)     epb_save(new_array_ctor(T,N,CON,## __VA_ARGS__))

#define epb_save_static(P,T)       yaooc_exception_pointer_bag_save_static_array(P,T ## _ti,1)
#define epb_save_static_array(P,T,N)       yaooc_exception_pointer_bag_save_static_array(P,T ## _ti,N)
#define epb_newp(P,T)      epb_save_static(newp(P,T),T ## _ti,1)
#define epb_newp_array(P,T,N)      epb_save_static_array(newp_array(P,T,N),T ## _ti,N)
#define epb_newp_copy_static(P,T,CP)      epb_save_static(newp_copy_static(P,T,CP),T ## _ti,1)
#define epb_newp_array_copy_static(P,T,CP,N)      epb_save_static_array(newp_array_copy_static(P,T,CP,N),T ## _ti,N)
#define epb_newp_ctor(P,T,CON,...)      epb_save_static(newp_ctor(P,T,CON,## __VA_ARGG__),T ## _ti,1)
#define epb_newp_array_ctor(P,T,N,CON,...)      epb_save_static_array(newp_array_ctor(P,T,N,CON,## __VA_ARGG__),T ## _ti,1)


#define epb_clear()  yaooc_exception_pointer_bag_clear(ptr)
#define epb_delete() yaooc_exception_pointer_bag_delete(ptr)

#endif
