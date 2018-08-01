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

#ifndef __REGEX_INCLUDED__
#define __REGEX_INCLUDED__

#include <yaooc/string.h>
#include <yaooc/exception.h>
#ifdef __YAOOC_USE_TRE__
#include <tre/regex.h>
#else
#include <regex.h>
#endif
/*  Begin YAOOC PreProcessor generated content */

/*
  Class definition for yaooc_regex_exception
*/
yaooc_class_table(yaooc_regex_exception)
{
  yaooc_exception_class_table_t;
};
#define yaooc_regex_exception_parent_class_table ((yaooc_exception_class_table_t*)(yaooc_regex_exception_class_table.parent_class_table_))

yaooc_class_instance(yaooc_regex_exception)
{
  yaooc_exception_class_instance_t;
  char* what_;
};

yaooc_class(yaooc_regex_exception);

/* Prototypes for yaooc_regex_exception type info */
void yaooc_regex_exception_default_ctor(pointer);
void yaooc_regex_exception_dtor(pointer);
void yaooc_regex_exception_copy_ctor(pointer,const_pointer);
void yaooc_regex_exception_assign(pointer,const_pointer);

/* Prototypes for yaooc_regex_exception constructors */
void yaooc_regex_exception_ctor_ccs(pointer,va_list);

/* Prototypes for yaooc_regex_exception class table */
const char* yaooc_regex_exception_isa(const_pointer);
#define yaooc_regex_exception_is_descendant yaooc_exception_is_descendant
void yaooc_regex_exception_swap(pointer,pointer);
const char* yaooc_regex_exception_what(const_pointer);

/* Prototypes for yaooc_regex_exception protected members */


/*
  Class definition for yaooc_matchdata
*/
yaooc_class_table(yaooc_matchdata)
{
  yaooc_object_class_table_t;
  yaooc_string_pointer (*at)(const_pointer,size_t);
  yaooc_string_pointer (*exec)(pointer,const char*);
  const char* (*subject)(const_pointer);
  bool (*bool)(const_pointer);
  size_t (*size)(const_pointer);
};

yaooc_class_instance(yaooc_matchdata)
{
  yaooc_object_class_instance_t;
  regmatch_t* ovector_;
  char* subject_;
  int match_result_;
  int n_captures_;
};

yaooc_class(yaooc_matchdata);
/* Prototypes for yaooc_matchdata type info */
void yaooc_matchdata_default_ctor(pointer);
void yaooc_matchdata_dtor(pointer);
void yaooc_matchdata_copy_ctor(pointer,const_pointer);
void yaooc_matchdata_assign(pointer,const_pointer);

/* Constructors for yaooc_matchdata */

/* Prototypes for yaooc_matchdata class table*/
const char* yaooc_matchdata_isa(const_pointer);
#define yaooc_matchdata_is_descendant yaooc_object_is_descendant
void yaooc_matchdata_swap(pointer,pointer);
yaooc_string_pointer yaooc_matchdata_at(const_pointer,size_t);
yaooc_string_pointer yaooc_matchdata_exec(pointer,const char*);
const char* yaooc_matchdata_subject(const_pointer);
bool yaooc_matchdata_bool(const_pointer);
size_t yaooc_matchdata_size(const_pointer);

/* Prototypes for yaooc_matchdata class instance*/

/* Prototypes for yaooc_matchdata class protected items*/


/*
  Class definition for yaooc_regex
*/
yaooc_class_table(yaooc_regex)
{
  yaooc_object_class_table_t;
  void (*set_pattern_flags)(pointer,const char*,int);
  const char* (*get_pattern)(const_pointer);
  int (*get_flags)(const_pointer);
  yaooc_matchdata_pointer (*match)(pointer,const char*,int);
  bool (*match_next)(pointer,yaooc_matchdata_pointer);
  bool (*bool)(const_pointer);
};

yaooc_class_instance(yaooc_regex)
{
  yaooc_object_class_instance_t;
  regex_t* re_;
  char* pattern_;
  int compile_flags_;
  int compile_result_;
};

yaooc_class(yaooc_regex);
/* Prototypes for yaooc_regex type info */
void yaooc_regex_default_ctor(pointer);
void yaooc_regex_dtor(pointer);
void yaooc_regex_copy_ctor(pointer,const_pointer);
void yaooc_regex_assign(pointer,const_pointer);

/* Constructors for yaooc_regex */
void yaooc_regex_ctor_ccs_int(pointer,va_list);

/* Prototypes for yaooc_regex class table*/
#define yaooc_regex_isa yaooc_object_isa
#define yaooc_regex_is_descendant yaooc_object_is_descendant
#define yaooc_regex_swap yaooc_object_swap
void yaooc_regex_set_pattern_flags(pointer,const char*,int);
const char* yaooc_regex_get_pattern(const_pointer);
int yaooc_regex_get_flags(const_pointer);
yaooc_matchdata_pointer yaooc_regex_match(pointer,const char*,int);
bool yaooc_regex_match_next(pointer,yaooc_matchdata_pointer);
bool yaooc_regex_bool(const_pointer);

/* Prototypes for yaooc_regex class instance*/

/* Prototypes for yaooc_regex class protected items*/

/*  End YAOOC PreProcessor generated content */

#endif
