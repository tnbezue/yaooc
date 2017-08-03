#ifndef __YAOOC_EXCEPTION_INCLUDED__
#define __YAOOC_EXCEPTION_INCLUDED__
#include <setjmp.h>
#include <yaooc/object.h>
#include <yaooc/garbage_bag.h>

/*
  Base exception class.  All exception classes should be derived for it.
*/
class_table(yaooc_exception)
{
  yaooc_object_class_members_t;
  const char * (*what) (const_pointer);
};

class_instance(yaooc_exception)
{
  yaooc_object_instance_members_t;
};
class(yaooc_exception);
ISA_DEFINITION(yaooc_exception,yaooc_object)

const char* yaooc_exception_what(const_pointer);

/*
  Exception stack
*/
typedef struct yaooc_jmpbuf_s yaooc_jmpbuf_t;
struct yaooc_jmpbuf_s {
  jmp_buf jb_;
  yaooc_exception_pointer exception_thrown_;
  char* file_;
  size_t line_no_;
  yaooc_garbage_bag_pointer pb_;
  yaooc_jmpbuf_t* prev_;
};

typedef struct yaooc_exception_thread_s yaooc_exception_thread_t;
struct yaooc_exception_thread_s {
  yaooc_jmpbuf_t* current_jmpbuf_;
  yaooc_jmpbuf_t* unhandled_jmpbuf_;
};
yaooc_jmpbuf_t* yaooc_current_jmpbuf(void);
void yaooc_exception_handled(void);
void yaooc_exception_unhandled(void);

yaooc_exception_thread_t* yaooc_exception_thread_create(void);
void yaooc_exception_thread_destroy(yaooc_exception_thread_t*);

yaooc_jmpbuf_t* yaooc_jmpbuf_new(void);
//void yaooc_jmpbuf_pop(yaooc_exception_thread_t*);

void yaooc_jmpbuf_destroy(yaooc_jmpbuf_t*);
yaooc_jmpbuf_t* yaooc_jmpbuf_top(void);
void yaooc_uncaught_exception(const char*,size_t,yaooc_exception_pointer);
void yaooc_jmpbuf_dump(yaooc_exception_thread_t* et);

/*
  Macros/routines to implement TRY/CATCH
*/
yaooc_jmpbuf_t* setup_jmpbuf_for_exeception(void *,const char*,size_t);
pointer yaooc_exception_garbage_bag_save(pointer);

#define EGB_SAVE(ptr) yaooc_exception_garbage_bag_save(ptr)

#define TRY if(setjmp(yaooc_jmpbuf_new()->jb_) == 0) { \
    do {

/*
  setup the exception and throw (long jump)
*/
#define THROW(e) \
    longjmp(setup_jmpbuf_for_exeception(e,__FILE__,__LINE__)->jb_,1); \

/*
  Before "else if", no exception thrown or exception handled.
  adjust exception stack.
  After "else if", exception just thrown or not handled
    * if preceeding section was a try, an exception was thrown
    * if preceeding section was a catch, exception was unhandled
*/
#define CATCH(exception_type,e) \
    } while(0); \
    yaooc_exception_handled(); \
  } else if(M(yaooc_current_jmpbuf()->exception_thrown_,is_descendent,# exception_type "_t")) {  do { \
    exception_type ## _const_pointer e=(exception_type ## _const_pointer)yaooc_current_jmpbuf()->exception_thrown_;\

/*
  Before "else if":
    Same as CATCH
  After "else if";
    Exception not handled.  Throw same exception to next level
*/
#define ETRY \
    } while(0); \
    yaooc_exception_handled(); \
} else  {\
    yaooc_exception_unhandled(); \
    setup_jmpbuf_for_exeception(NULL,NULL,0); \
    longjmp(yaooc_current_jmpbuf()->jb_,1); \
}

#define YAOOC_EXCEPTION_CLASS_MEMBERS \
  { \
    yaooc_exception_isa, \
    yaooc_exception_is_descendent, \
    yaooc_object_swap \
  }, \
  yaooc_exception_what \

#endif
