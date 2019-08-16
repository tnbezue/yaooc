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
#include <time.h>
#include <yaooc/object.h>
#include <yaooc/map.h>
#include <yaooc/string.h>
#include <yaooc/memory.h>

#include "demo_def.inc"
#include "test_harness.h"

/*
void dump_map(student_info_const_pointer this,FILE* out)
{
	fprintf(out,"id: %04d  lname: %-10.10s fname: %-10.10s score: %d\n",this->id,this->lname,this->fname,this->score);
}
*/

yaooc_class_table(student_info)
{
  yaooc_object_class_table_t;
  uint_t (*score)(const_pointer);
};

yaooc_class_instance(student_info)
{
  yaooc_string_t lname_;
  yaooc_string_t fname_;
  uint_t score_;
};

yaooc_class(student_info);

void student_info_default_ctor(pointer p)
{
  student_info_pointer this=p;
  newp(&this->lname_,yaooc_string);
  newp(&this->fname_,yaooc_string);
  this->score_=0;
}

void student_info_dtor(pointer p)
{
  student_info_pointer this=p;
  deletep(&this->lname_,yaooc_string);
  deletep(&this->fname_,yaooc_string);
}

void student_info_assign(pointer d,const_pointer s)
{
  student_info_pointer dst=d;
  student_info_const_pointer src=s;
  assign_static(&dst->lname_,&src->lname_,yaooc_string);
  assign_static(&dst->fname_,&src->fname_,yaooc_string);
  dst->score_=src->score_;
}

void student_info_copy_ctor(pointer d,const_pointer s)
{
  student_info_default_ctor(d);
  student_info_assign(d,s);
}

uint_t student_info_score(const_pointer p)
{
  return 0;
}

student_info_class_table_t student_info_class_table = {
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
  .type_name_ = (const char*) "student_info_t",
  .swap = yaooc_object_swap,
  .score = student_info_score
};

DEFINE_TYPE_INFO(student_info,Y,Y,Y,Y,N,N,N,Y,yaooc_object)

void student_info_ctor(pointer p,va_list args)
{
  student_info_pointer this=p;
  newp_ctor(&this->lname_,yaooc_string,yaooc_string_ctor_ccs,va_arg(args,const char*));
  newp_ctor(&this->fname_,yaooc_string,yaooc_string_ctor_ccs,va_arg(args,const char*));
  this->score_=va_arg(args,uint_t);
}

typedef uint_t student_id_t;
#define student_id_ti uint_ti

typedef struct {
  uint_t student_id;
  const char* lname;
  const char* fname;
  uint_t score;
} student_data_t;

student_data_t students []=
	{
		{ 134, "Baker","Joan",93 },
		{ 66, "Smith","Lisa", 88 },
		{ 121, "Bell","John", 90 },
		{ 1010, "Lester","Ming", 82 },
		{ 0, 0, 0, 0 }
	};

student_data_t student_updates []=
{
  { 66, "Smith","Lisa", 91 },
	{ 121, "Bell","John", 79 },
	{ 44, "Long","Kathy", 66 },
	{ 0, 0, 0, 0 }
};

MINI_MAP_DEFINITION(student_id,student_info,student_id_student_info_map)
MINI_MAP_IMPLEMENTATION(student_id,student_info,student_id_student_info_map)

void test_basic()
{
  printf("Test map size %zu\n",sizeof(student_id_student_info_map_t));
  student_id_student_info_map_pointer student_info_map=new(student_id_student_info_map);
  student_data_t * isd=students;
  for(;isd->student_id!=0;isd++) {
    student_info_pointer sip=new_ctor(student_info,student_info_ctor,isd->lname,isd->fname,isd->score);
    M(student_info_map,insert,&isd->student_id,sip);
    delete(sip);
  }
  student_id_student_info_map_const_iterator i;
  for(i=M(student_info_map,begin);i!=M(student_info_map,end);i++) {
    student_info_const_pointer p=&i->second;
    printf("%d %s %s %d\n",i->first,M(&p->lname_,c_str),M(&p->fname_,c_str),p->score_);
  }
//  yaooc_index_container_print_indexes(student_info_map,stdout);
  isd=student_updates;
  printf("\n");
  for(;isd->student_id!=0;isd++) {
    student_info_pointer sip=new_ctor(student_info,student_info_ctor,isd->lname,isd->fname,isd->score);
    M(student_info_map,insert,&isd->student_id,sip);
    delete(sip);
  }
  for(i=M(student_info_map,begin);i!=M(student_info_map,end);i++) {
    student_info_const_pointer p=&i->second;
    printf("%d %s %s %d\n",i->first,M(&p->lname_,c_str),M(&p->fname_,c_str),p->score_);
  }
//  yaooc_index_container_print_indexes(student_info_map,stdout);
	delete(student_info_map);

}

MINI_MAP_DEFINITION(yaooc_string,int,yaooc_string_int_map);
MINI_MAP_IMPLEMENTATION(yaooc_string,int,yaooc_string_int_map);

unsigned int *rbtree_indexes;
unsigned int irb;
void get_index(yaooc_rbnode_t* node)
{
	if(node != yaooc_rbnode_rbnil) {
		get_index(node->left_);
		rbtree_indexes[irb++]=node->index_;
		get_index(node->right_);
	};
}
/*
const yaooc_string_t* prev_str=NULL;
bool is_ordered(yaooc_string_int_map_pointer this)
{
  bool ret=true;
  rbtree_indexes = (unsigned int*)MALLOC(M(this,size)*sizeof(unsigned int));
  irb=0;
  get_index(yaooc_rbtree_index_array_container_rbfirst(this));
  unsigned int i;
  printf("Size: %u\n",irb);
  yaooc_string_int_map_const_iterator array=M(this,cbegin);
  less_than_compare lt_cmp=get_lt_cmp(TYPE_INFO(this));
  for(i=1;i<irb;i++) {
    if(!lt_cmp(array+rbtree_indexes[i-1],array+rbtree_indexes[i])) {
//      printf("Failed at index %u %s %s\n",i,M(array+rbtree_indexes[i-1],c_str),M(array+rbtree_indexes[i],c_str));
      ret=false;
      break;
    }
  }
  return ret;
}
*/
const char* str1="rpkjeiuhvlocynwtqdagzmfbxs";
const char* str2="fzhcvtdkjpoxgyenluqrmawsib";
const char* str3="vgztaiqfsphnjkydbxruewmocl";
const char* str4="iufkyowzvmhljbsrxqgacnpted";

void test_big()
{
	int_t counter=0;
  yaooc_string_t str;
  newp_ctor(&str,yaooc_string,yaooc_string_ctor_ccs,"    ");
	yaooc_string_iterator is=M(&str,begin);
	yaooc_string_int_map_pointer mfls=new(yaooc_string_int_map);
	clock_t start=clock();
//  M(mfls,reserve,456976);
	const char *i,*j,*k,*l;
	for(i=str1+25;*i!=0;i++) {
		is[0]=*i;
		for(j=str2+22;*j!=0;j++) {
			is[1]=*j;
			for(k=str3;*k!=0;k++) {
				is[2]=*k;
        for(l=str4;*l!=0;l++) {
          is[3]=*l;
          M(mfls,insert,&str,&counter);
          counter++;
        }
			}
		}
	}

	printf("%lg seconds to insert %zu items\n",((double)(clock()-start))/CLOCKS_PER_SEC,M(mfls,size));
//	printf("%5s %6d\n",M(&mfls->first,c_str),p.second);
/*	yaooc_string_int_map_const_iterator isi;
	for(isi=M(mfls,begin);isi!=M(mfls,end);isi++) {
		printf("%5s %6d\n",M(&isi->first,c_str),isi->second);
	}*/
//  TEST("Ordered",is_ordered(mfls));
	delete(mfls);
	deletep(&str,yaooc_string);
}

/*
  The following is the same as above but uses unique pointers for the key.
  There should not be any performance difference.  Compare this to ordered map.
*/
UNIQUE_PTR_DEFINITION(yaooc_string,yaooc_string_unique_ptr)
UNIQUE_PTR_IMPLEMENTATION(yaooc_string,yaooc_string_unique_ptr)
MINI_MAP_DEFINITION(yaooc_string_unique_ptr,int,yaooc_string_unique_ptr_int_map)
MINI_MAP_IMPLEMENTATION(yaooc_string_unique_ptr,int,yaooc_string_unique_ptr_int_map)

void test_big_unique_ptr()
{
	int_t counter=0;
  char str[8];
	str[4]=0;
	yaooc_string_unique_ptr_int_map_pointer mfls=new(yaooc_string_unique_ptr_int_map);
	clock_t start=clock();
  STACK_VAR(yaooc_string_unique_ptr,s);
	const char *i,*j,*k,*l;
	for(i=str1+25;*i!=0;i++) {
		str[0]=*i;
		for(j=str2+22;*j!=0;j++) {
			str[1]=*j;
			for(k=str3;*k!=0;k++) {
				str[2]=*k;
        for(l=str4;*l!=0;l++) {
          str[3]=*l;
          M(&s,reset,new_ctor(yaooc_string,yaooc_string_ctor_ccs,str));
          M(mfls,insert,&s,&counter);
          counter++;
        }
			}
		}
	}
	printf("%lg seconds to insert %zu items\n",((double)(clock()-start))/CLOCKS_PER_SEC,M(mfls,size));
//	printf("%5s %6d\n",M(&mfls->first,c_str),p.second);
/*	yaooc_string_unique_ptr_int_map_const_iterator isi;
	for(isi=M(mfls,begin);isi!=M(mfls,end);isi++) {
    yaooc_string_const_pointer first=M(&isi->first,get);
		printf("%5s %6d\n",M(first,c_str),isi->second);
	}*/
	delete(mfls);

}
yaooc_pod_struct(temp_data) {
	char temp[16];
};

bool temp_data_less_than_compare(const_pointer p1,const_pointer p2)
{
	const temp_data_t* lhs=p1;
	const temp_data_t* rhs=p2;
	return strcmp(lhs->temp,rhs->temp) < 0;
};

DEFINE_POD_TYPE_INFO(temp_data,Y,N,N);

MAP_DEFINITION(temp_data,int,temp_int_map);
MAP_IMPLEMENTATION(temp_data,int,temp_int_map);

void test_pod()
{
	int_t counter=0;
  temp_data_t temp;
  memset(temp.temp,0,16);
  temp_int_map_pointer mfls=new(temp_int_map);
  char*ptr = temp.temp;
	clock_t start=clock();
//  M(mfls,reserve,456976);
	const char *i,*j,*k,*l;
	for(i=str1;*i!=0;i++) {
		ptr[0]=*i;
		for(j=str2;*j!=0;j++) {
			ptr[1]=*j;
			for(k=str3;*k!=0;k++) {
				ptr[2]=*k;
        for(l=str4;*l!=0;l++) {
          ptr[3]=*l;
          M(mfls,insert,&temp,&counter);
          counter++;
        }
			}
		}
	}

	printf("%lg seconds to insert %zu items\n",((double)(clock()-start))/CLOCKS_PER_SEC,M(mfls,size));
//	printf("%5s %6d\n",M(&mfls->first,c_str),p.second);
/*	yaooc_string_int_map_const_iterator isi;
	for(isi=M(mfls,begin);isi!=M(mfls,end);isi++) {
		printf("%5s %6d\n",M(&isi->first,c_str),isi->second);
	}*/
	delete(mfls);
}

test_function tests[]=
{
	test_basic,
	test_big,
  test_big_unique_ptr,
  test_pod,
};

STD_MAIN(tests)
