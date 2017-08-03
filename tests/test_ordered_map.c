#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include <yaooc/ordered_map.h>
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

class_table(student_info)
{
  yaooc_object_class_members_t;
};

class_instance(student_info)
{
  yaooc_string_t lname_;
  yaooc_string_t fname_;
  uint32_t score_;
};

class(student_info);

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
#define STUDENT_CLASS_MEMBERS \
( \
  YAOOC_OBJECT_CLASS_MEMBERS \
}

student_info_class_members_t student_info_class_members; // = { STUDENT_GLOBAL_MEMBERS };

DEFINE_TYPE_INFO(student_info,student_info_default_ctor,student_info_dtor
      ,student_info_copy_ctor,student_info_assign,NULL,&student_info_class_members,
      NULL)

void student_info_ctor(pointer p,va_list args)
{
  student_info_pointer this=p;
  newp_ctor(&this->lname_,yaooc_string,yaooc_string_ctor_ccs,va_arg(args,const char*));
  newp_ctor(&this->fname_,yaooc_string,yaooc_string_ctor_ccs,va_arg(args,const char*));
  this->score_=va_arg(args,uint32_t);
}

typedef uint32_t student_id_t;
#define student_id_ti uint32_ti

typedef struct {
  uint32_t student_id;
  const char* lname;
  const char* fname;
  uint32_t score;
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
	{ 44, "Long","Kathy", 79 },
	{ 0, 0, 0, 0 }
};


ORDERED_MAP_DEFINITION(student_id,student_info)
ORDERED_MAP_IMPLEMENTATION(student_id,student_info)

void test_basic()
{
  student_id_student_info_ordered_map_pointer student_info_ordered_map=new(student_id_student_info_ordered_map);
  student_data_t * isd=students;
  for(;isd->student_id!=0;isd++) {
    student_info_pointer sip=new_ctor(student_info,student_info_ctor,isd->lname,isd->fname,isd->score);
    M(student_info_ordered_map,insert,&isd->student_id,sip);
    delete(sip);
  }
  student_id_student_info_ordered_map_const_iterator i;
  for(i=M(student_info_ordered_map,cbegin);i!=M(student_info_ordered_map,cend);i++) {
    student_info_const_pointer p=&i->second;
    printf("%d %s %s %d\n",i->first,M(&p->lname_,c_str),M(&p->fname_,c_str),p->score_);
  }
  isd=student_updates;
  printf("\n");
  for(;isd->student_id!=0;isd++) {
    student_info_pointer sip=new_ctor(student_info,student_info_ctor,isd->lname,isd->fname,isd->score);
    M(student_info_ordered_map,insert,&isd->student_id,sip);
    delete(sip);
  }
  for(i=M(student_info_ordered_map,cbegin);i!=M(student_info_ordered_map,cend);i++) {
    student_info_const_pointer p=&i->second;
    printf("%d %s %s %d\n",i->first,M(&p->lname_,c_str),M(&p->fname_,c_str),p->score_);
  }
	delete(student_info_ordered_map);
}


ORDERED_MAP_DEFINITION(yaooc_string,int32);
ORDERED_MAP_IMPLEMENTATION(yaooc_string,int32);

const char* str1="rpkjeiuhvlocynwtqdagzmfbxs";
const char* str2="fzhcvtdkjpoxgyenluqrmawsib";
const char* str3="vgztaiqfsphnjkydbxruewmocl";
const char* str4="iufkyowzvmhljbsrxqgacnpted";

void test_big()
{
	int32_t counter=0;
  yaooc_string_t str;
  newp_ctor(&str,yaooc_string,yaooc_string_ctor_ccs,"    ");
	yaooc_string_iterator is=M(&str,begin);
	yaooc_string_int32_ordered_map_pointer mfls=new(yaooc_string_int32_ordered_map);
	clock_t start=clock();
	const char *i,*j,*k,*l;
	for(i=str1+20;*i!=0;i++) {
		is[0]=*i;
		for(j=str2;*j!=0;j++) {
			is[1]=*j;
			for(k=str3;*k!=0;k++) {
				is[2]=*k;
        for(l=str4;*l!=0;l++) {
          is[3]=*l;
          M(mfls,insert_kv,str,counter);
          counter++;
        }
			}
		}
	}
	printf("%ld clock cycles to insert %zu items\n",clock()-start,M(mfls,size));
//	printf("%5s %6d\n",M(&mfls->first,c_str),p.second);
	yaooc_string_int32_ordered_map_const_iterator isi;
	for(isi=M(mfls,cbegin);isi!=M(mfls,cend);isi++) {
		printf("%5s %6d\n",M(&isi->first,c_str),isi->second);
	}
	delete(mfls);
	deletep(&str,yaooc_string);
}

/*
  The following is the same as above but uses unique pointers for the key.
  It should execute in half the time as above.  Compare this to map.
*/
UNIQUE_PTR_DEFINITION(yaooc_string)
UNIQUE_PTR_IMPLEMENTATION(yaooc_string)
ORDERED_MAP_DEFINITION(yaooc_string_unique_ptr,int32)
ORDERED_MAP_IMPLEMENTATION(yaooc_string_unique_ptr,int32)

void test_big_unique_ptr()
{
	int32_t counter=0;
  char str[8];
	str[4]=0;
	yaooc_string_unique_ptr_int32_ordered_map_pointer mfls=new(yaooc_string_unique_ptr_int32_ordered_map);
	clock_t start=clock();
  STACK_PTR(yaooc_string_unique_ptr,s);
	const char *i,*j,*k,*l;
	for(i=str1+20;*i!=0;i++) {
		str[0]=*i;
		for(j=str2;*j!=0;j++) {
			str[1]=*j;
			for(k=str3;*k!=0;k++) {
				str[2]=*k;
        for(l=str4;*l!=0;l++) {
          str[3]=*l;
          M(s,set,new_ctor(yaooc_string,yaooc_string_ctor_ccs,str));
          M(mfls,insert_pv,s,counter);
          counter++;
        }
			}
		}
	}
	printf("%ld clock cycles to insert %zu items\n",clock()-start,M(mfls,size));
//	printf("%5s %6d\n",M(&mfls->first,c_str),p.second);
	yaooc_string_unique_ptr_int32_ordered_map_const_iterator isi;
	for(isi=M(mfls,cbegin);isi!=M(mfls,cend);isi++) {
    yaooc_string_const_pointer first=M(&isi->first,cget);
		printf("%5s %6d\n",M(first,c_str),isi->second);
	}
	delete(mfls);
}

test_function tests[]=
{
	test_basic,
	test_big,
  test_big_unique_ptr
};

STD_MAIN(tests)
