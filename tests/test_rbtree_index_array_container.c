#include "test_rbtree_index_array_container.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include "test_harness.h"

unsigned int *rbtree_indexes;
unsigned int irb;

void get_index(yaooc_rbnode_t* node)
{
 if(node != NULL) {
  get_index(node->link_[0]);
  rbtree_indexes[irb++]=node->index_;
  get_index(node->link_[1]);
 };
}

void print_index(yaooc_rbnode_t* node)
{
 if(node != NULL) {
  print_index(node->link_[0]);
  optr+=sprintf(optr,"%u ",node->index_);
  print_index(node->link_[1]);
 }
}


void int_rbtree_index_array_container_default_ctor(pointer __pthis__)
{
int_rbtree_index_array_container_pointer this=__pthis__;(void)this;
call_constructor(this,yaooc_rbtree_index_array_container_ctor_ti,int_ti);



    
}
void int_rbtree_index_array_container_print_in_order(const_pointer __pthis__)
{
int_rbtree_index_array_container_const_pointer this=__pthis__;(void)this;

      rbtree_indexes = (unsigned int*)MALLOC(M(this,size)*sizeof(unsigned int));
      irb=0;
      get_index(this->root_);
      optr=output;
      *optr=0;
      int_rbtree_index_array_container_const_iterator array=M(this,cbegin);
      for(irb=0;irb<M(this,size);irb++)
        optr+=sprintf(optr,"%d ",array[rbtree_indexes[irb]]);
      puts(output);
      FREE(rbtree_indexes);
    
}
bool int_rbtree_index_array_container_index_ordered(const_pointer __pthis__)
{
int_rbtree_index_array_container_const_pointer this=__pthis__;(void)this;

      rbtree_indexes = (unsigned int*)MALLOC(M(this,size)*sizeof(unsigned int));
      irb=0;
      bool rc=true;
      get_index(this->root_);
      int_rbtree_index_array_container_const_iterator array=M(this,cbegin);
      for(irb=1;irb<M(this,size);irb++)
        if(array[rbtree_indexes[irb-1]] >= array[rbtree_indexes[irb]]) {
          rc=false;
          break;
        }
      FREE(rbtree_indexes);
      return rc;
    
}
void int_rbtree_index_array_container_print_indexes(const_pointer __pthis__)
{
int_rbtree_index_array_container_const_pointer this=__pthis__;(void)this;

      optr=output;
      *optr=0;
      print_index(this->root_);
      printf("M%sM\n",output);
    
}
void int_rbtree_index_array_container_print_value(const_pointer __pthis__)
{
int_rbtree_index_array_container_const_pointer this=__pthis__;(void)this;

      optr=output;
      *optr=0;
      size_t i;
      int_rbtree_index_array_container_const_iterator array=M(this,cbegin);
      for(i=0;i<M(this,size);i++)
        optr+=sprintf(optr,"%d ",array[i]);
    
}
int_rbtree_index_array_container_iterator int_rbtree_index_array_container_find(pointer __pthis__,int value)
{
int_rbtree_index_array_container_pointer this=__pthis__;(void)this;
#define super() int_rbtree_index_array_container_parent_class_table->find(this,value)
#define PM(method,...) CTM((*int_rbtree_index_array_container_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_rbtree_index_array_container_find(this,&value);
    
#undef PM
#undef super
}
int_rbtree_index_array_container_const_iterator int_rbtree_index_array_container_insert(pointer __pthis__,const int* pos,int value)
{
int_rbtree_index_array_container_pointer this=__pthis__;(void)this;
#define super() int_rbtree_index_array_container_parent_class_table->insert(this,pos,value)
#define PM(method,...) CTM((*int_rbtree_index_array_container_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_rbtree_index_array_container_insert(this,pos,&value);
    
#undef PM
#undef super
}
int_rbtree_index_array_container_const_iterator int_rbtree_index_array_container_insert_range(pointer __pthis__,const int* pos,const int* first,const int* last)
{
int_rbtree_index_array_container_pointer this=__pthis__;(void)this;
#define super() int_rbtree_index_array_container_parent_class_table->insert_range(this,pos,first,last)
#define PM(method,...) CTM((*int_rbtree_index_array_container_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_rbtree_index_array_container_insert_range(this,pos,first,last);
    
#undef PM
#undef super
}
int_rbtree_index_array_container_const_iterator int_rbtree_index_array_container_insertn(pointer __pthis__,const int* pos,size_t n,int value)
{
int_rbtree_index_array_container_pointer this=__pthis__;(void)this;
#define super() int_rbtree_index_array_container_parent_class_table->insertn(this,pos,n,value)
#define PM(method,...) CTM((*int_rbtree_index_array_container_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_rbtree_index_array_container_insertn(this,pos,n,&value);
    
#undef PM
#undef super
}
int_rbtree_index_array_container_iterator int_rbtree_index_array_container_erase(pointer __pthis__,const int* pos)
{
int_rbtree_index_array_container_pointer this=__pthis__;(void)this;
#define super() int_rbtree_index_array_container_parent_class_table->erase(this,pos)
#define PM(method,...) CTM((*int_rbtree_index_array_container_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_rbtree_index_array_container_erase(this,pos);
    
#undef PM
#undef super
}
int_rbtree_index_array_container_iterator int_rbtree_index_array_container_erase_range(pointer __pthis__,const int* first,const int* last)
{
int_rbtree_index_array_container_pointer this=__pthis__;(void)this;
#define super() int_rbtree_index_array_container_parent_class_table->erase_range(this,first,last)
#define PM(method,...) CTM((*int_rbtree_index_array_container_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_rbtree_index_array_container_erase_range(this,first,last);
    
#undef PM
#undef super
}
size_t int_rbtree_index_array_container_erase_value(pointer __pthis__,int value)
{
int_rbtree_index_array_container_pointer this=__pthis__;(void)this;
#define super() int_rbtree_index_array_container_parent_class_table->erase_value(this,value)
#define PM(method,...) CTM((*int_rbtree_index_array_container_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_rbtree_index_array_container_erase_value(this,&value);
    
#undef PM
#undef super
}
void int_rbtree_index_array_container_resize(pointer __pthis__,size_t n)
{
int_rbtree_index_array_container_pointer this=__pthis__;(void)this;
#define super() int_rbtree_index_array_container_parent_class_table->resize(this,n)
#define PM(method,...) CTM((*int_rbtree_index_array_container_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_rbtree_index_array_container_resize(this,n);
    
#undef PM
#undef super
}
void int_rbtree_index_array_container_resize_value(pointer __pthis__,size_t n,int value)
{
int_rbtree_index_array_container_pointer this=__pthis__;(void)this;
#define super() int_rbtree_index_array_container_parent_class_table->resize_value(this,n,value)
#define PM(method,...) CTM((*int_rbtree_index_array_container_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_rbtree_index_array_container_resize_value(this,n,&value);
    
#undef PM
#undef super
}
int_rbtree_index_array_container_class_table_t int_rbtree_index_array_container_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_rbtree_index_array_container_class_table,
.type_name_ = (const char*)"int_rbtree_index_array_container_t",
.swap = (void(*)(pointer,pointer)) int_rbtree_index_array_container_swap,
.increase_capacity = (bool(*)(pointer,size_t)) int_rbtree_index_array_container_increase_capacity,
.size_needed = (size_t(*)(const_pointer,size_t)) int_rbtree_index_array_container_size_needed,
.size = (size_t(*)(const_pointer)) int_rbtree_index_array_container_size,
.capacity = (size_t(*)(const_pointer)) int_rbtree_index_array_container_capacity,
.empty = (bool(*)(const_pointer)) int_rbtree_index_array_container_empty,
.begin = (iterator(*)(pointer)) int_rbtree_index_array_container_begin,
.end = (iterator(*)(pointer)) int_rbtree_index_array_container_end,
.cbegin = (const_iterator(*)(const_pointer)) int_rbtree_index_array_container_cbegin,
.cend = (const_iterator(*)(const_pointer)) int_rbtree_index_array_container_cend,
.find = (int_rbtree_index_array_container_iterator(*)(pointer,int)) int_rbtree_index_array_container_find,
.insert = (int_rbtree_index_array_container_const_iterator(*)(pointer,const int*,int)) int_rbtree_index_array_container_insert,
.insert_range = (int_rbtree_index_array_container_const_iterator(*)(pointer,const int*,const int*,const int*)) int_rbtree_index_array_container_insert_range,
.insertn = (int_rbtree_index_array_container_const_iterator(*)(pointer,const int*,size_t,int)) int_rbtree_index_array_container_insertn,
.erase = (int_rbtree_index_array_container_iterator(*)(pointer,const int*)) int_rbtree_index_array_container_erase,
.erase_range = (int_rbtree_index_array_container_iterator(*)(pointer,const int*,const int*)) int_rbtree_index_array_container_erase_range,
.erase_value = (size_t(*)(pointer,int)) int_rbtree_index_array_container_erase_value,
.resize = (void(*)(pointer,size_t)) int_rbtree_index_array_container_resize,
.resize_value = (void(*)(pointer,size_t,int)) int_rbtree_index_array_container_resize_value,
.shrink_to_fit = (void(*)(pointer)) int_rbtree_index_array_container_shrink_to_fit,
.clear = (void(*)(pointer)) int_rbtree_index_array_container_clear,
.at = (int_rbtree_index_array_container_iterator(*)(pointer,size_t)) int_rbtree_index_array_container_at,
};
const type_info_t __int_rbtree_index_array_container_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(int_rbtree_index_array_container_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=int_rbtree_index_array_container_default_ctor,
.dtor_=NULL,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &int_rbtree_index_array_container_class_table,
.parent_=&__yaooc_rbtree_index_array_container_ti
};
const type_info_t* const int_rbtree_index_array_container_ti=&__int_rbtree_index_array_container_ti;
void test_sizes()
{
 printf("%" PRIULONG " %" PRIULONG "\n",sizeof(yaooc_rbnode_t),sizeof(int_rbtree_index_array_container_t));
 TEST("SIZE yaooc_rbnode_t == 24",sizeof(yaooc_rbnode_t)== 24);
 TEST("SIZE index_array_container == 48",sizeof(int_rbtree_index_array_container_t)== 48);
}

void test_constructor()
{
 yaooc_rbtree_index_array_container_pointer bc=new_ctor(yaooc_rbtree_index_array_container,yaooc_rbtree_index_array_container_ctor_ti,int_ti);
 TEST("Array is NULL",bc->array_==NULL);
 TEST("Typeinfo is int_ti",bc->type_info_==int_ti);
 TEST("Root is NULL",bc->root_==NULL);
 TEST("Size is 0",bc->size_==0);
 TEST("Capacity is 0",bc->capacity_==0);

 delete(bc);
}

void test_insert()
{
 int_t values[] = { 14, 8, 6, 14 ,99, 17, 17, 17, 88, 21, 56, 31, 31, 8, 17, 24, 555, 24, 24, 18, 18, 21, 88, 102, 88, 99 , -8, 32, 57, 35 ,21 };
 int n=ARRAY_SIZE(values);
 int_rbtree_index_array_container_pointer bc=new(int_rbtree_index_array_container);
 int i;
  TESTCASE("Insert");
 int_rbtree_index_array_container_const_iterator pos;
 for(i=0;i<5;i++) {
  M(bc,insert,M(bc,cend),values[i]);
 }
 TEST("Array is not NULL",bc->array_!=NULL);
 printf("%" PRIULONG "\n",bc->size_);
 TEST("Size is 4",bc->size_==4);
 TEST("Capacity is 16",bc->capacity_==16);
  TEST("Index is ordered",int_rbtree_index_array_container_index_ordered(bc));
  int_rbtree_index_array_container_print_value(bc);
  TEST("Values are '14 8 6 99'",strcmp(output,"14 8 6 99 ")==0);
  int_rbtree_index_array_container_print_indexes(bc);
  TEST("Indexes are '2 1 0 3'",strcmp(output,"2 1 0 3 ")==0);
  int_rbtree_index_array_container_print_in_order(bc);
  TEST("Sorter order is '6 8 14 99'",strcmp(output,"6 8 14 99 ")==0);

 for(i=5;i<18;i++) {
  pos=M(bc,end);
  M(bc,insert,pos,values[i]);
 }
 TEST("Size is 18",bc->size_==11);
 TEST("Capacity is 32",bc->capacity_==16);
  TEST("Index is ordered",int_rbtree_index_array_container_index_ordered(bc));
  int_rbtree_index_array_container_print_value(bc);
  TEST("Values are '14 8 6 99 17 88 21 56 31 24 555'",strcmp(output,"14 8 6 99 17 88 21 56 31 24 555 ")==0);
  int_rbtree_index_array_container_print_indexes(bc);
  TEST("Indexes are '2 1 0 4 6 9 8 7 5 3 10'",strcmp(output,"2 1 0 4 6 9 8 7 5 3 10 ")==0);
  int_rbtree_index_array_container_print_in_order(bc);
  TEST("Sorter order is '6 8 14 17 21 24 31 56 88 99 555'",strcmp(output,"6 8 14 17 21 24 31 56 88 99 555 ")==0);

 for(i=18;i<n;i++) {
  pos=M(bc,at,8);
  M(bc,insert,pos,values[i]);
 }
 TEST("Size is 17",bc->size_==17);
 TEST("Capacity is 32",bc->capacity_==32);
  TEST("Index is ordered",int_rbtree_index_array_container_index_ordered(bc));
  int_rbtree_index_array_container_print_value(bc);
  TEST("Values are '14 8 6 99 17 88 21 56 31 24 555 18 102 -8 32 57 35'",strcmp(output,"14 8 6 99 17 88 21 56 31 24 555 18 102 -8 32 57 35 ")==0);
  int_rbtree_index_array_container_print_indexes(bc);
  TEST("Indexes are '13 2 1 0 4 11 6 9 8 14 16 7 15 5 3 12 10'",strcmp(output,"13 2 1 0 4 11 6 9 8 14 16 7 15 5 3 12 10 ")==0);
  int_rbtree_index_array_container_print_in_order(bc);
  TEST("Sorter order is '-8 6 8 14 17 18 21 24 31 32 35 56 57 88 99 102 555'",strcmp(output,"-8 6 8 14 17 18 21 24 31 32 35 56 57 88 99 102 555 ")==0);

 optr=output;


  TESTCASE("Insert Range");
  M(bc,clear);
  pos=M(bc,begin);
  M(bc,insert_range,pos,values,values+n);
 TEST("Size is 17",bc->size_==17);
 TEST("Capacity is 32",bc->capacity_==32);
  TEST("Index is ordered",int_rbtree_index_array_container_index_ordered(bc));
  int_rbtree_index_array_container_print_value(bc);
  TEST("Values are '14 8 6 99 17 88 21 56 31 24 555 18 102 -8 32 57 35'",strcmp(output,"14 8 6 99 17 88 21 56 31 24 555 18 102 -8 32 57 35 ")==0);
  int_rbtree_index_array_container_print_indexes(bc);
  puts(output);
  TEST("Indexes are '13 2 1 0 4 11 6 9 8 14 16 7 15 5 3 12 10'",strcmp(output,"13 2 1 0 4 11 6 9 8 14 16 7 15 5 3 12 10 ")==0);
  int_rbtree_index_array_container_print_in_order(bc);
  TEST("Sorter order is '-8 6 8 14 17 18 21 24 31 32 35 56 57 88 99 102 555'",strcmp(output,"-8 6 8 14 17 18 21 24 31 32 35 56 57 88 99 102 555 ")==0);

  TESTCASE("Insert N")

  M(bc,clear);
  pos=M(bc,begin);
  M(bc,insertn,pos,20,values[10]);
 TEST("Size is 1",bc->size_==1);
 TEST("Capacity is 32",bc->capacity_==32);
  TEST("Index is ordered",int_rbtree_index_array_container_index_ordered(bc));
  int_rbtree_index_array_container_print_value(bc);
  TEST("Values are '56'",strcmp(output,"56 ")==0);
  int_rbtree_index_array_container_print_indexes(bc);
  puts(output);
  TEST("Indexes are '0'",strcmp(output,"0 ")==0);
  int_rbtree_index_array_container_print_in_order(bc);
  TEST("Sorter order is '56'",strcmp(output,"56 ")==0);
  delete(bc);
}

#define MAX_RANDOMS 409600
void test_insert_big()
{
 int_rbtree_index_array_container_pointer bc=new(int_rbtree_index_array_container);
 srand((unsigned) time(NULL));
 int i;
 for(i=0;i<MAX_RANDOMS;i++) {
  int numb = rand();
  M(bc,insert,M(bc,cend),numb);
 }
 TEST("Index ordered and unique",int_rbtree_index_array_container_index_ordered(bc));
  if(0) {
 int_rbtree_index_array_container_const_iterator ibc = M(bc,cbegin);
 M(bc,erase_range,ibc+200,ibc+500);
 TEST("Index ordered and unique",int_rbtree_index_array_container_index_ordered(bc));
  }
  delete(bc);
}

void test_erase()
{
 int_t values[] = { 14, 8, 6, 2 ,99, 17, 21, 56, 31, 8, 17, 24, 18, 18, 21, 88, 99 , -8, 32, 57, 35 };
 int n=ARRAY_SIZE(values);
 int_rbtree_index_array_container_pointer bc=new(int_rbtree_index_array_container);
 int_rbtree_index_array_container_const_iterator pos=M(bc,begin);
 M(bc,insert_range,pos,values,values+n);
 TESTCASE("Erase");
 TEST("Size is 16",bc->size_==16);
 TEST("Capacity is 16",bc->capacity_==16);
  TEST("Index is ordered",int_rbtree_index_array_container_index_ordered(bc));
  int_rbtree_index_array_container_print_value(bc);
  TEST("Values are '14 8 6 2 99 17 21 56 31 24 18 88 -8 32 57 35'",strcmp(output,"14 8 6 2 99 17 21 56 31 24 18 88 -8 32 57 35 ")==0);
  int_rbtree_index_array_container_print_indexes(bc);
  TEST("Indexes are '12 3 2 1 0 5 10 6 9 8 13 15 7 14 11 4'",strcmp(output,"12 3 2 1 0 5 10 6 9 8 13 15 7 14 11 4 ")==0);
  int_rbtree_index_array_container_print_in_order(bc);
  TEST("Sorter order is '-8 2 6 8 14 17 18 21 24 31 32 35 56 57 88 99'",strcmp(output,"-8 2 6 8 14 17 18 21 24 31 32 35 56 57 88 99 ")==0);

  TESTCASE("Erase pos");
 pos=M(bc,at,10);
 M(bc,erase,pos);
 TEST("Erase item 10. Size is 15",M(bc,size)==15);
 TEST("Capacity is 16",bc->capacity_==16);
  TEST("Index is ordered",int_rbtree_index_array_container_index_ordered(bc));
  int_rbtree_index_array_container_print_value(bc);
  TEST("Values are '14 8 6 2 99 17 21 56 31 24 88 -8 32 57 35'",strcmp(output,"14 8 6 2 99 17 21 56 31 24 88 -8 32 57 35 ")==0);
  int_rbtree_index_array_container_print_indexes(bc);
  TEST("Indexes are '11 3 2 1 0 5 6 9 8 12 14 7 13 10 4'",strcmp(output,"11 3 2 1 0 5 6 9 8 12 14 7 13 10 4 ")==0);
  int_rbtree_index_array_container_print_in_order(bc);
  TEST("Sorter order is '-8 2 6 8 14 17 21 24 31 32 35 56 57 88 99'",strcmp(output,"-8 2 6 8 14 17 21 24 31 32 35 56 57 88 99 ")==0);

 pos=M(bc,at,7);
  TESTCASE("Erase range");
  M(bc,erase_range,pos,pos+5);
 TEST("Erase 5 items starting at position 7. Size is 8",M(bc,size)==10);
 TEST("Capacity is 16",bc->capacity_==16);
  TEST("Index is ordered",int_rbtree_index_array_container_index_ordered(bc));
  int_rbtree_index_array_container_print_value(bc);
  TEST("Values are '14 8 6 2 99 17 21 32 57 35'",strcmp(output,"14 8 6 2 99 17 21 32 57 35 ")==0);
  int_rbtree_index_array_container_print_indexes(bc);
  TEST("Indexes are '3 2 1 0 5 6 7 9 8 4'",strcmp(output,"3 2 1 0 5 6 7 9 8 4 ")==0);
  int_rbtree_index_array_container_print_in_order(bc);
  TEST("Sorter order is '2 6 8 14 17 21 32 35 57 99'",strcmp(output,"2 6 8 14 17 21 32 35 57 99 ")==0);

 TESTCASE("Erase Value");
 TEST("Erasing 1 99's from '2 6 8 14 17 21 32 35 57 99'",M(bc,erase_value,99)==1);
 TEST("Size is 16",bc->size_==9);
  TEST("Index is ordered",int_rbtree_index_array_container_index_ordered(bc));
 TEST("Capacity is 16",bc->capacity_==16);
  TEST("Index is ordered",int_rbtree_index_array_container_index_ordered(bc));
  int_rbtree_index_array_container_print_value(bc);
  TEST("Values are '14 8 6 2 17 21 32 57 35'",strcmp(output,"14 8 6 2 17 21 32 57 35 ")==0);
  int_rbtree_index_array_container_print_indexes(bc);
  TEST("Indexes are '3 2 1 0 4 5 6 8 7'",strcmp(output,"3 2 1 0 4 5 6 8 7 ")==0);
  int_rbtree_index_array_container_print_in_order(bc);
  TEST("Sorter order is '2 6 8 14 17 21 32 35 57'",strcmp(output,"2 6 8 14 17 21 32 35 57 ")==0);

 delete(bc);
}


void test_copy()
{
 int_t values[] = { 14, 8, 6, 2 ,99 , 2 , 8, 21, 32, 21 ,21 , 14, -8 };
 int_rbtree_index_array_container_pointer c1=new(int_rbtree_index_array_container);
 int n=ARRAY_SIZE(values);
  int_rbtree_index_array_container_const_iterator pos=M(c1,begin);

  M(c1,insert_range,pos,values,values+n);
  TESTCASE("Copy");
 TEST("Size is 8",M(c1,size)==8);
 TEST("Capacity is 16",c1->capacity_==16);
  TEST("Index is ordered",int_rbtree_index_array_container_index_ordered(c1));
  int_rbtree_index_array_container_print_value(c1);
  puts(output);
  TEST("Values are '14 8 6 2 99 21 32 -8'",strcmp(output,"14 8 6 2 99 21 32 -8 ")==0);
  int_rbtree_index_array_container_print_indexes(c1);
  puts(output);
  TEST("Indexes are '7 3 2 1 0 5 6 4'",strcmp(output,"7 3 2 1 0 5 6 4 ")==0);
  int_rbtree_index_array_container_print_in_order(c1);
  puts(output);
  TEST("Sorter order is '-8 2 6 8 14 21 32 99'",strcmp(output,"-8 2 6 8 14 21 32 99 ")==0);

  int_rbtree_index_array_container_pointer c2=new_copy(c1);
 TEST("Size is 8",M(c2,size)==8);
 TEST("Capacity is 16",c2->capacity_==16);
  TEST("Index is ordered",int_rbtree_index_array_container_index_ordered(c2));
  int_rbtree_index_array_container_print_value(c2);
  puts(output);
  TEST("Values are '14 8 6 2 99 21 32 -8'",strcmp(output,"14 8 6 2 99 21 32 -8 ")==0);
  int_rbtree_index_array_container_print_indexes(c2);
  puts(output);
  TEST("Indexes are '7 3 2 1 0 5 6 4'",strcmp(output,"7 3 2 1 0 5 6 4 ")==0);
  int_rbtree_index_array_container_print_in_order(c2);
  puts(output);
  TEST("Sorter order is '-8 2 6 8 14 21 32 99'",strcmp(output,"-8 2 6 8 14 21 32 99 ")==0);

 delete(c2);
 delete(c1);
}
void test_assign()
{
 int_t values[] = { 14, 8, 6, 2 ,99 , 2 , 8, 21, 32, 21 ,21 , 14, -8 };
 int_rbtree_index_array_container_pointer c1=new(int_rbtree_index_array_container);
 int n=ARRAY_SIZE(values);
  int_rbtree_index_array_container_const_iterator pos=M(c1,begin);

  M(c1,insert_range,pos,values,values+n);
  TESTCASE("Assign");
 TEST("Size is 8",M(c1,size)==8);
 TEST("Capacity is 16",c1->capacity_==16);
  TEST("Index is ordered",int_rbtree_index_array_container_index_ordered(c1));
  int_rbtree_index_array_container_print_value(c1);
  puts(output);
  TEST("Values are '14 8 6 2 99 21 32 -8'",strcmp(output,"14 8 6 2 99 21 32 -8 ")==0);
  int_rbtree_index_array_container_print_indexes(c1);
  puts(output);
  TEST("Indexes are '7 3 2 1 0 5 6 4'",strcmp(output,"7 3 2 1 0 5 6 4 ")==0);
  int_rbtree_index_array_container_print_in_order(c1);
  puts(output);
  TEST("Sorter order is '-8 2 6 8 14 21 32 99'",strcmp(output,"-8 2 6 8 14 21 32 99 ")==0);

  int_rbtree_index_array_container_pointer c2=new(int_rbtree_index_array_container);
  assign(c2,c1);
 TEST("Size is 8",M(c2,size)==8);
 TEST("Capacity is 16",c2->capacity_==16);
  TEST("Index is ordered",int_rbtree_index_array_container_index_ordered(c2));
  int_rbtree_index_array_container_print_value(c2);
  puts(output);
  TEST("Values are '14 8 6 2 99 21 32 -8'",strcmp(output,"14 8 6 2 99 21 32 -8 ")==0);
  int_rbtree_index_array_container_print_indexes(c2);
  puts(output);
  TEST("Indexes are '7 3 2 1 0 5 6 4'",strcmp(output,"7 3 2 1 0 5 6 4 ")==0);
  int_rbtree_index_array_container_print_in_order(c2);
  puts(output);
  TEST("Sorter order is '-8 2 6 8 14 21 32 99'",strcmp(output,"-8 2 6 8 14 21 32 99 ")==0);

 delete(c2);
 delete(c1);

}

void test_resize_shrink()
{
 int_rbtree_index_array_container_pointer rs=new(int_rbtree_index_array_container);
 TESTCASE("Creation");
 TEST("Container array is NULL",rs->array_==NULL);
 TEST("Size is 0",M(rs,size)==0);
 TEST("Capacity is 0",M(rs,capacity)==0);

 int_t value=24;

 M(rs,resize_value,5,value);
 TESTCASE("Resize to 5 with value of 24");
 TEST("Size is 1",M(rs,size)==1);
 TEST("Capacity is 16",M(rs,capacity)==16);
  TEST("Index is ordered",int_rbtree_index_array_container_index_ordered(rs));
  int_rbtree_index_array_container_print_value(rs);
  TEST("Values are '24'",strcmp(output,"24 ")==0);
  int_rbtree_index_array_container_print_indexes(rs);
  TEST("Indexes are '0'",strcmp(output,"0 ")==0);
  int_rbtree_index_array_container_print_in_order(rs);
  TEST("Sorter order is '24'",strcmp(output,"24 ")==0);

 M(rs,resize_value,5,value);
 TESTCASE("Resize to current size.  No changes");
 TEST("Size is 1",M(rs,size)==1);
 TEST("Capacity is 16",M(rs,capacity)==16);
  TEST("Index is ordered",int_rbtree_index_array_container_index_ordered(rs));
  int_rbtree_index_array_container_print_value(rs);
  TEST("Values are '24'",strcmp(output,"24 ")==0);
  int_rbtree_index_array_container_print_indexes(rs);
  TEST("Indexes are '0'",strcmp(output,"0 ")==0);
  int_rbtree_index_array_container_print_in_order(rs);
  TEST("Sorter order is '24'",strcmp(output,"24 ")==0);

  value = 15;
 M(rs,resize_value,10,value);
 TESTCASE("Resize to 10 with value of 15");
 TEST("Size is 2",M(rs,size)==2);
 TEST("Capacity is 16",M(rs,capacity)==16);
  TEST("Index is ordered",int_rbtree_index_array_container_index_ordered(rs));
  int_rbtree_index_array_container_print_value(rs);
  TEST("Values are '24 15'",strcmp(output,"24 15 ")==0);
  int_rbtree_index_array_container_print_indexes(rs);
  TEST("Indexes are '1 0'",strcmp(output,"1 0 ")==0);
  int_rbtree_index_array_container_print_in_order(rs);
  TEST("Sorter order is '15 24'",strcmp(output,"15 24 ")==0);

  value=20;
 M(rs,resize_value,20,value);
 TESTCASE("Resize to 20 with value of 20");
 TEST("Size is 3",M(rs,size)==3);
 TEST("Capacity is 16",M(rs,capacity)==16);
  TEST("Index is ordered",int_rbtree_index_array_container_index_ordered(rs));
  int_rbtree_index_array_container_print_value(rs);
  TEST("Values are '24 15 20'",strcmp(output,"24 15 20 ")==0);
  int_rbtree_index_array_container_print_indexes(rs);
  TEST("Indexes are '1 2 0'",strcmp(output,"1 2 0 ")==0);
  int_rbtree_index_array_container_print_in_order(rs);
  TEST("Sorter order is '15 20 24'",strcmp(output,"15 20 24 ")==0);

  M(rs,shrink_to_fit);
 TESTCASE("Shrink to fit");
 TEST("Size is 3",M(rs,size)==3);
 TEST("Capacity is 16",M(rs,capacity)==16);
  TEST("Index is ordered",int_rbtree_index_array_container_index_ordered(rs));
  int_rbtree_index_array_container_print_value(rs);
  TEST("Values are '24 15 20'",strcmp(output,"24 15 20 ")==0);
  int_rbtree_index_array_container_print_indexes(rs);
  TEST("Indexes are '1 2 0'",strcmp(output,"1 2 0 ")==0);
  int_rbtree_index_array_container_print_in_order(rs);
  TEST("Sorter order is '15 20 24'",strcmp(output,"15 20 24 ")==0);

 M(rs,resize_value,2,value);
 TESTCASE("Resize to 2");
 TEST("Size is 3",M(rs,size)==2);
 TEST("Capacity is 16",M(rs,capacity)==16);
  TEST("Index is ordered",int_rbtree_index_array_container_index_ordered(rs));
  int_rbtree_index_array_container_print_value(rs);
  TEST("Values are '24 15'",strcmp(output,"24 15 ")==0);
  int_rbtree_index_array_container_print_indexes(rs);
  TEST("Indexes are '1 0'",strcmp(output,"1 0 ")==0);
  int_rbtree_index_array_container_print_in_order(rs);
  TEST("Sorter order is '15 24'",strcmp(output,"15 24 ")==0);

 M(rs,shrink_to_fit);
 TESTCASE("Shrink to fit");
 TEST("Size is 3",M(rs,size)==2);
 TEST("Capacity is 16",M(rs,capacity)==16);
  TEST("Index is ordered",int_rbtree_index_array_container_index_ordered(rs));
  int_rbtree_index_array_container_print_value(rs);
  TEST("Values are '24 15'",strcmp(output,"24 15 ")==0);
  int_rbtree_index_array_container_print_indexes(rs);
  TEST("Indexes are '1 0'",strcmp(output,"1 0 ")==0);
  int_rbtree_index_array_container_print_in_order(rs);
  TEST("Sorter order is '15 24'",strcmp(output,"15 24 ")==0);

 M(rs,resize_value,0,value);
 TESTCASE("Resize to 0");
 TEST("Size is 0",M(rs,size)==0);
 TEST("Capacity is 16",M(rs,capacity)==16);
  TEST("Index is ordered",int_rbtree_index_array_container_index_ordered(rs));
  int_rbtree_index_array_container_print_value(rs);
  TEST("Values are ''",strcmp(output,"")==0);
  int_rbtree_index_array_container_print_indexes(rs);
  TEST("Indexes are ''",strcmp(output,"")==0);
  int_rbtree_index_array_container_print_in_order(rs);
  TEST("Sorter order is ''",strcmp(output,"")==0);

 M(rs,shrink_to_fit);
 TESTCASE("Shrink to fit");
 TEST("Size is 0",M(rs,size)==0);
 TEST("Capacity is 16",M(rs,capacity)==16);
  TEST("Index is ordered",int_rbtree_index_array_container_index_ordered(rs));
  int_rbtree_index_array_container_print_value(rs);
  TEST("Values are ''",strcmp(output,"")==0);
  int_rbtree_index_array_container_print_indexes(rs);
  TEST("Indexes are ''",strcmp(output,"")==0);
  int_rbtree_index_array_container_print_in_order(rs);
  TEST("Sorter order is ''",strcmp(output,"")==0);

 delete(rs);
}

test_function tests[]=
{
 test_sizes,
 test_constructor,
  test_insert,
 test_insert_big,
 test_erase,
 test_copy,
 test_assign,
 test_resize_shrink
};

STD_MAIN(tests)

