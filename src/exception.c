#include <yaooc/exception.h>
#include <string.h>
#include <pthread.h>

static pthread_mutex_t emut = PTHREAD_MUTEX_INITIALIZER;
yaooc_exception_thread_t* yaooc_exception_thread_create()
{
  yaooc_exception_thread_t* et=MALLOC(sizeof(yaooc_exception_thread_t));
  et->current_jmpbuf_=NULL;
  et->unhandled_jmpbuf_=NULL;
  return et;
}

void yaooc_exception_thread_destroy(yaooc_exception_thread_t* et)
{
  while(et->current_jmpbuf_)
    yaooc_exception_handled();
  FREE(et);
}

typedef struct yaooc_exception_thread_list_s yaooc_exception_thread_list_t;
struct yaooc_exception_thread_list_s {
  pthread_t tid_;
  yaooc_exception_thread_t* exception_thread_;
  yaooc_exception_thread_list_t* next_;
};
yaooc_exception_thread_list_t* exception_thread_head=NULL;
yaooc_exception_thread_list_t* exception_thread_tail=NULL;

yaooc_exception_thread_t* yaooc_exception_thread_list_find_exception_thread(pthread_t tid)
{
  yaooc_exception_thread_list_t* current=exception_thread_head;
  while(current != NULL) {
    if(tid==current->tid_)
      return current->exception_thread_;
    current=current->next_;
  }
  return NULL;
}

/*
  Make sure to call find before calling this function.  It does not check if one exists
  before creating a new one.
*/
yaooc_exception_thread_t* yaooc_exception_thread_list_create_exception_thread(pthread_t tid)
{
  printf("Creating thread exception for %ld\n",tid);
  pthread_mutex_lock(&emut);
  yaooc_exception_thread_list_t* current=MALLOC(sizeof(yaooc_exception_thread_list_t));
  current->tid_=tid;
  current->next_=NULL;
  current->exception_thread_=yaooc_exception_thread_create();
  if(exception_thread_head==NULL) {
    exception_thread_head=exception_thread_tail=current;
  } else {
    exception_thread_tail->next_=current;
    exception_thread_tail=current;
  }
  pthread_mutex_unlock(&emut);
  return current->exception_thread_;
}

/*
  Combine find with create.  If not found and create_flag is true, then new exception thread created
*/
yaooc_exception_thread_t* yaooc_exception_thread_list_find_or_create_exception_thread(pthread_t tid,bool create_flag)
{
  yaooc_exception_thread_t* current=yaooc_exception_thread_list_find_exception_thread(tid);
  if(current)
    return current;
  if(create_flag)
    return yaooc_exception_thread_list_create_exception_thread(tid);
  return NULL;
}

void yaooc_exception_thread_list_remove_exception_thread(pthread_t tid)
{
  yaooc_exception_thread_list_t* current=exception_thread_head;
  yaooc_exception_thread_list_t* previous=NULL;
  while(current != NULL) {
    if(tid==current->tid_) {
      pthread_mutex_lock(&emut);
      printf("Removing %ld thread from exception list\n",tid);
      if(previous) {
        previous->next_=current->next_;
        if(current->next_ ==NULL) { /* removing last item in list */
          exception_thread_tail=previous;
        }
      } else {
        /* Remove first item in list */
        exception_thread_head=current->next_;
        if(current->next_ == NULL) {
          /* only one item in list */
          exception_thread_head=exception_thread_tail=NULL;
        } else {
          /* Remove head of list */
        }
      }
      pthread_mutex_unlock(&emut);
      yaooc_exception_thread_destroy(current->exception_thread_);
      FREE(current);
      break;
    }
    previous=current;
    current=current->next_;
  }
}

/*
  Base exception
*/
ISA_IMPLEMENTATION(yaooc_exception,yaooc_object)

const char* yaooc_exception_what(const_pointer p)
{
  return NULL;
}

yaooc_exception_class_members_t yaooc_exception_class_members =
{
  YAOOC_EXCEPTION_CLASS_MEMBERS
};

DEFINE_TYPE_INFO(yaooc_exception,NULL,NULL,NULL,NULL,NULL,&yaooc_exception_class_members,yaooc_object)

/*
  Exception handling
*/

void yaooc_jmpbuf_dump(yaooc_exception_thread_t* et)
{
  printf("Current jmpbuf: %p\n",et->current_jmpbuf_);
  if(et->current_jmpbuf_) {
    printf("Exception: %p\n"
        "File: %s\n"
        "Line number: %d\n"
        "Pointer bag size: %d\n"
        "Previous: %p\n",et->current_jmpbuf_->exception_thrown_,et->current_jmpbuf_->file_,
        et->current_jmpbuf_->line_no_,M(et->current_jmpbuf_->pb_,size),et->current_jmpbuf_->prev_);
  }
}
/*
  Create a new stack item.
*/
yaooc_jmpbuf_t* yaooc_jmpbuf_new(void)
{
  yaooc_exception_thread_t* et=yaooc_exception_thread_list_find_or_create_exception_thread(pthread_self(),true);
  yaooc_jmpbuf_t* prev=et->current_jmpbuf_;
  et->current_jmpbuf_=(yaooc_jmpbuf_t*)MALLOC(sizeof(yaooc_jmpbuf_t));
  et->current_jmpbuf_->exception_thrown_=NULL;
  et->current_jmpbuf_->file_=NULL;
  et->current_jmpbuf_->line_no_=0;
  et->current_jmpbuf_->pb_=new(yaooc_garbage_bag);
  et->current_jmpbuf_->prev_=prev;
  return et->current_jmpbuf_;
}

/*
  Moves to previous jumbuf when no exception occurred or after successfully handling an exception
*/
void yaooc_exception_handled()
{
  yaooc_exception_thread_t* et=yaooc_exception_thread_list_find_or_create_exception_thread(pthread_self(),false);
  if(et->current_jmpbuf_) {
    yaooc_jmpbuf_t* prev=et->current_jmpbuf_;
    et->current_jmpbuf_=et->current_jmpbuf_->prev_;
    yaooc_jmpbuf_destroy(prev);
  }
}

/*
  Moves to previous jumbuf when exception is unhandled.  Copies file and line number
  information to previous environment
*/
void yaooc_exception_unhandled()
{
  yaooc_exception_thread_t* et=yaooc_exception_thread_list_find_or_create_exception_thread(pthread_self(),false);
  if(et->current_jmpbuf_) {
    yaooc_jmpbuf_t* prev=et->current_jmpbuf_->prev_;
    if(prev) {
      prev->file_=et->current_jmpbuf_->file_;
      et->current_jmpbuf_->file_=NULL;
      prev->exception_thrown_=et->current_jmpbuf_->exception_thrown_;
      et->current_jmpbuf_->exception_thrown_=NULL;
      prev->line_no_=et->current_jmpbuf_->line_no_;
    } else {
      et->unhandled_jmpbuf_=et->current_jmpbuf_;
      et->current_jmpbuf_=NULL;
    }
    yaooc_exception_handled();
  }
}

void yaooc_jmpbuf_destroy(yaooc_jmpbuf_t* jb)
{

  if(jb) {
    delete(jb->pb_);
    if(jb->exception_thrown_)
      delete(jb->exception_thrown_);
    if(jb->file_)
      FREE(jb->file_);
    FREE(jb);
  }
}

void yaooc_exception_terminate(const char* fname,yaooc_size_type line,yaooc_exception_pointer e)
{
  fprintf(stderr,"Uncaught %s exception in file %s at line number %d: %s\n",M(e,isa),fname,line,M(e,what));
  abort();
}

yaooc_jmpbuf_t* setup_jmpbuf_for_exeception(void *e,const char* f,yaooc_size_type l)
{
  yaooc_exception_thread_t* et=yaooc_exception_thread_list_find_or_create_exception_thread(pthread_self(),false);
  if(et->current_jmpbuf_ == NULL) {
    if(et->unhandled_jmpbuf_) {
      /* Got here because exception not handled by any CATCH -- from ETRY */
      yaooc_exception_terminate(et->unhandled_jmpbuf_->file_,et->unhandled_jmpbuf_->line_no_,et->unhandled_jmpbuf_->exception_thrown_);
      yaooc_jmpbuf_destroy(et->unhandled_jmpbuf_);
    } else {
      /* Got here because THROW executed without a TRY -- first THROW */
      yaooc_exception_terminate(f,l,e);
    }
    exit(9); /* abort(); */
  } else {
    yaooc_exception_pointer temp=(yaooc_exception_pointer)(e?e:et->current_jmpbuf_->exception_thrown_);
    if(et->current_jmpbuf_->exception_thrown_ !=NULL && temp != et->current_jmpbuf_->exception_thrown_)
      delete(et->current_jmpbuf_->exception_thrown_);
    if(et->current_jmpbuf_->file_==NULL) { /* If not null, info already copied from prev exception */
      et->current_jmpbuf_->file_=STRDUP(f);
      et->current_jmpbuf_->line_no_=l;
    }
    et->current_jmpbuf_->exception_thrown_=temp;
  }
  return et->current_jmpbuf_;
}

yaooc_jmpbuf_t* yaooc_current_jmpbuf()
{
  yaooc_exception_thread_t* et=yaooc_exception_thread_list_find_or_create_exception_thread(pthread_self(),false);
  return et ? et->current_jmpbuf_ : NULL;
}

pointer yaooc_exception_garbage_bag_save(pointer p)
{
  yaooc_jmpbuf_t* cjb=yaooc_current_jmpbuf();
  if(cjb)
    M(cjb->pb_,push,p);
  return p;
}
