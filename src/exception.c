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

#include <yaooc/exception.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

/*  Begin YAOOC PreProcessor generated content */

/* Private items for yaooc_exception */

/* Protected items for yaooc_exception */

/* Typeinfo for yaooc_exception */
void yaooc_exception_default_ctor(pointer p)
{
	yaooc_exception_pointer this=p;
	this->what_=NULL;
}

void yaooc_exception_dtor(pointer p)
{
	yaooc_exception_pointer this=p;
	if(this->what_)
		free(this->what_);  // Don't use FREE since vasprintf may have allocated the memory
}

void yaooc_exception_copy_ctor(pointer p,const_pointer s)
{
	yaooc_exception_default_ctor(p);
	yaooc_exception_assign(p,s);
}

void yaooc_exception_assign(pointer p,const_pointer s)
{
	yaooc_exception_pointer this=p;
	yaooc_exception_const_pointer src=p;
	yaooc_exception_dtor(p);
	this->what_ = src->what_ ? strdup(src->what_) : NULL; // Don't use STRDUP
}

void yaooc_exception_ctor_v(pointer p,va_list args)
{
	yaooc_exception_pointer this=p;
	const char* fmt=va_arg(args,const char*);
	vasprintf(&this->what_,fmt,args);
}

/* Class table members for yaooc_exception */
void yaooc_exception_swap(pointer p,pointer o)
{
	yaooc_exception_pointer this=p;
	yaooc_exception_pointer other=o;
	SWAP(char *,this->what_,other->what_);
}

const char* yaooc_exception_what(const_pointer p)
{
  return ((yaooc_exception_const_pointer)p)->what_;
}

/* Class table for yaooc_exception */
yaooc_exception_class_table_t yaooc_exception_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
  .type_name_ = (const char*) "yaooc_exception_t",
  .swap = (void (*) (pointer p,pointer)) yaooc_exception_swap,
  .what = (const char* (*) (const_pointer p)) yaooc_exception_what,
};


DEFINE_TYPE_INFO(yaooc_exception,Y,Y,Y,Y,N,N,N,Y,yaooc_object)
/*  End YAOOC PreProcessor generated content */

typedef struct yaooc_jmpbuf_s yaooc_jmpbuf_t;
struct yaooc_jmpbuf_s {
  jmp_buf jb_;
  yaooc_exception_t* exception_thrown_;
  yaooc_pointer_bag_t* pb_;
  yaooc_jmpbuf_t* prev_;
};
typedef struct yaooc_exception_thread_jmpbuf_node_s yaooc_exception_thread_jmpbuf_node_t;
struct yaooc_exception_thread_jmpbuf_node_s {
  yaooc_exception_thread_jmpbuf_node_t* next_;
  pthread_t tid_;
  yaooc_jmpbuf_t* current_jmpbuf_;
};

static pthread_mutex_t exception_mutex = PTHREAD_MUTEX_INITIALIZER;
static void yaooc_exception_terminate(yaooc_exception_pointer e);
static void yaooc_jmpbuf_destroy(yaooc_jmpbuf_t*);
yaooc_exception_thread_jmpbuf_node_t* yaooc_exception_thread_jmpbuf_head=NULL;
yaooc_exception_thread_jmpbuf_node_t* yaooc_exception_thread_jmpbuf_tail=NULL;

yaooc_exception_thread_jmpbuf_node_t* yaooc_exception_thread_jmpbuf_list_find_jmpbuf(pthread_t tid)
{
  yaooc_exception_thread_jmpbuf_node_t* current=yaooc_exception_thread_jmpbuf_head;
  while(current != NULL) {
    if(tid==current->tid_)
      return current;
    current=current->next_;
  }
  return NULL;
}

/*
  Make sure to call find before calling this function.  It does not check if one exists
  before creating a new one.
*/
yaooc_exception_thread_jmpbuf_node_t* yaooc_exception_thread_node_create_thread_list(pthread_t tid)
{
  pthread_mutex_lock(&exception_mutex);
  yaooc_exception_thread_jmpbuf_node_t* current=MALLOC(sizeof(yaooc_exception_thread_jmpbuf_node_t));
  current->tid_=tid;
  current->next_=NULL;
  current->current_jmpbuf_=NULL;
//  current->exception_thread_=yaooc_exception_thread_create();
  if(yaooc_exception_thread_jmpbuf_head==NULL) {
    yaooc_exception_thread_jmpbuf_head=yaooc_exception_thread_jmpbuf_tail=current;
  } else {
    yaooc_exception_thread_jmpbuf_tail->next_=current;
    yaooc_exception_thread_jmpbuf_tail=current;
  }
  pthread_mutex_unlock(&exception_mutex);
  return current;
}

/*

*/
yaooc_exception_thread_jmpbuf_node_t* yaooc_exception_thread_jmpbuf_find_or_create_exception_thread(pthread_t tid)
{
  yaooc_exception_thread_jmpbuf_node_t* current=yaooc_exception_thread_jmpbuf_list_find_jmpbuf(tid);
  return current ? current : yaooc_exception_thread_node_create_thread_list(tid);
}

void yaooc_exception_thread_list_remove_all()
{
  yaooc_exception_thread_jmpbuf_node_t* current=yaooc_exception_thread_jmpbuf_head;
  yaooc_exception_thread_jmpbuf_node_t* temp;
  while(current != NULL) {
    temp=current->next_;
    yaooc_exception_thread_jmpbuf_head=yaooc_exception_thread_jmpbuf_tail=NULL;
    current=temp;
  }

}

void yaooc_exception_thread_list_remove_exception_thread(pthread_t tid)
{
  yaooc_exception_thread_jmpbuf_node_t* current=yaooc_exception_thread_jmpbuf_head;
  yaooc_exception_thread_jmpbuf_node_t* previous=NULL;
  while(current != NULL) {
    if(tid==current->tid_) {
      pthread_mutex_lock(&exception_mutex);
      if(previous) {
        previous->next_=current->next_;
        if(current->next_ ==NULL) { /* removing last item in list */
          yaooc_exception_thread_jmpbuf_tail=previous;
        }
      } else {
        /* Remove first item in list */
        yaooc_exception_thread_jmpbuf_head=current->next_;
        if(current->next_ == NULL) {
          /* only one item in list */
          yaooc_exception_thread_jmpbuf_head=yaooc_exception_thread_jmpbuf_tail=NULL;
        }
      }
      pthread_mutex_unlock(&exception_mutex);
//      yaooc_exception_thread_destroy(current->exception_thread_);
      FREE(current);
      break;
    }
    previous=current;
    current=current->next_;
  }
}

yaooc_jmpbuf_t* yaooc_current_jmpbuf();

/*
void yaooc_jmpbuf_dump(* et)
{
  printf("Current jmpbuf: %p\n",et->current_jmpbuf_);
  if(et->current_jmpbuf_) {
    printf("Exception: %p\n"
        "Pointer bag size: %zu\n"
        "Previous: %p\n",et->current_jmpbuf_->exception_thrown_,
        M(et->current_jmpbuf_->pb_,size),et->current_jmpbuf_->prev_);
  }
}
*/

jmp_buf* yaooc_jmpbuf_new()
{
  yaooc_exception_thread_jmpbuf_node_t* node=yaooc_exception_thread_jmpbuf_find_or_create_exception_thread(pthread_self());
  yaooc_jmpbuf_t* prev=node->current_jmpbuf_;
  node->current_jmpbuf_=(yaooc_jmpbuf_t*)MALLOC(sizeof(yaooc_jmpbuf_t));
  node->current_jmpbuf_->exception_thrown_=NULL;
  node->current_jmpbuf_->pb_=new(yaooc_pointer_bag);
  node->current_jmpbuf_->prev_=prev;
  return &(node->current_jmpbuf_->jb_);
}

/*
  Moves to previous jumbuf when no exception occurred or after successfully handling an exception
*/
void yaooc_exception_handled()
{
  yaooc_exception_thread_jmpbuf_node_t* node=yaooc_exception_thread_jmpbuf_list_find_jmpbuf(pthread_self());
  yaooc_jmpbuf_t* temp=node->current_jmpbuf_;
  node->current_jmpbuf_=temp->prev_;
  yaooc_jmpbuf_destroy(temp);
}

/*
  Called by ETRY macro.  The exception has not been handled.  Move to the level of exceptions.
  Copies file and line number information to next environment
*/

static void yaooc_jmpbuf_destroy(yaooc_jmpbuf_t* jb)
{

  if(jb) {
    delete(jb->pb_);
    if(jb->exception_thrown_)
      delete(jb->exception_thrown_);
    FREE(jb);
  }
}

static void yaooc_exception_terminate(yaooc_exception_pointer e)
{
  fprintf(stderr,"terminate called after throwing %s : %s\n",e->class_table_->type_name_,M(e,what) ? M(e,what) : "");
  delete(e);
  exit(0);
}

/*
  Throw and exception
*/
void __throw__(pointer e)
{
  yaooc_exception_thread_jmpbuf_node_t* node=yaooc_exception_thread_jmpbuf_list_find_jmpbuf(pthread_self());
  if(node != NULL) { // && node->current_jmpbuf_ != NULL) {
    /*
      Traverse upward until a jmpbuf found that has not had an exception thrown
    */
    while(node->current_jmpbuf_ != NULL && node->current_jmpbuf_->exception_thrown_ != NULL) {
      yaooc_jmpbuf_t* temp=node->current_jmpbuf_;
      node->current_jmpbuf_=temp->prev_;
      yaooc_jmpbuf_destroy(temp);
    }
  }
  if(node ==NULL || node->current_jmpbuf_ == NULL)
    yaooc_exception_terminate(e); /* Will not return */
  node->current_jmpbuf_->exception_thrown_=e;
  longjmp(node->current_jmpbuf_->jb_,1);
}

/*
  Reached an ETRY without an exception being handled.  Rethrow the last exception
*/
void __rethrow_last_exception__()
{
  yaooc_exception_thread_jmpbuf_node_t* node=yaooc_exception_thread_jmpbuf_list_find_jmpbuf(pthread_self());
  yaooc_jmpbuf_t* temp =node->current_jmpbuf_;
  pointer e = temp->exception_thrown_;
  temp->exception_thrown_ = NULL;
  node->current_jmpbuf_=temp->prev_;
  yaooc_jmpbuf_destroy(temp);
  __throw__(e);
}

bool __catch__(const char* etype)
{
  return yaooc_object_isa(yaooc_exception_current_exception_thrown(),etype);
}
/*
  Called from CATCH and ETRY macros -- node and node->current_jmpbuf_ should never be NULL
*/
yaooc_jmpbuf_t* yaooc_current_jmpbuf()
{
  yaooc_exception_thread_jmpbuf_node_t* node=yaooc_exception_thread_jmpbuf_list_find_jmpbuf(pthread_self());
  return node->current_jmpbuf_;
}

pointer yaooc_exception_pointer_bag_save(pointer p)
{
  yaooc_jmpbuf_t* cjb=yaooc_current_jmpbuf();
  if(cjb)
    M(cjb->pb_,push,p);
  return p;
}

void yaooc_exception_pointer_bag_clear(pointer p)
{
  yaooc_jmpbuf_t* cjb=yaooc_current_jmpbuf();
  if(cjb)
    M(cjb->pb_,clear);
}

void yaooc_exception_pointer_bag_delete(pointer p)
{
  yaooc_jmpbuf_t* cjb=yaooc_current_jmpbuf();
  if(cjb)
    M(cjb->pb_,delete_all);
}

/*
  Called from CATCH block so current jmpbuf and exception will not be NULL.
*/
yaooc_exception_pointer yaooc_exception_current_exception_thrown()
{
  return yaooc_current_jmpbuf()->exception_thrown_;
}
