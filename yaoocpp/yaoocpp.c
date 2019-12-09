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
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>
#include <yaooc/string.h>
#include <yaooc/garbage_bag.h>
#include <yaooc/exception.h>
#include <yaooc/fstream.h>
#include <string.h>
#include <libgen.h>
#include "components.h"
#include "parser.h"


#define YAOOCPP_MAJOR 2
#define YAOOCPP_MINOR 0

//yaooc_string_t include_directories = YAOOC_STRING_STATIC_DEFAULT_CTOR;
yaooc_string_vector_t include_directories;

//yaooc_string_t cpp = YAOOC_STRING_STATIC_DEFAULT_CTOR;
yaooc_string_t defines = YAOOC_STRING_STATIC_DEFAULT_CTOR;
yaooc_string_t output_file = YAOOC_STRING_STATIC_DEFAULT_CTOR;
yaooc_string_t header_directory  = YAOOC_STRING_STATIC_DEFAULT_CTOR;
yaooc_string_t definition_directory = YAOOC_STRING_STATIC_DEFAULT_CTOR;
extern yaooc_string_t yaoocpp_header_prefix;
//extern yaooc_string_t yaoocpp_definition_prefix;

void print_info()
{
  M(cout,printf,"YAOOCPP -- Yet Another Object Oriented C PreProcessor\n");
}

void print_help(const char* pgm)
{
  print_info();
  M(cout,printf,"Syntax: %s [ -h | --help ]\n",pgm);
  M(cout,printf,"        %s [ -v | --version ]\n",pgm);
  M(cout,printf,"        %s [ [ -I | --include ] path ] [ -Dmacro[=value] ] [ [ -hd | --header-directory ] path ]"
                " [ [ -dd | --definition-directory ] path ] file.yoc\n",pgm);
  M(cout,printf,"Where:\n");
  M(cout,printf,"  -h|--help -- prints this help\n");
  M(cout,printf,"  -v|--version -- prints version information\n");
  M(cout,printf,"  -I|--include-directory -- Adds directory to include path.\n");
  M(cout,printf,"  -D|--define  -- Define macro (multiple -D directives may be specified)\n");
  M(cout,printf,"  -hd|--header-directory  -- Specifies directory to which generated header is written."
                " Default is current directory.\n");
  M(cout,printf,"  -dd|--definition-directory -- Specified directory to which stripped definition file is written."
                " Default is same directory as header directory.\n");
  M(cout,printf,"  file.yoc -- File to preprocesses.\n");
}

void print_version()
{
  print_info();
  M(cout,printf,"Version: %d.%d\n",YAOOCPP_MAJOR,YAOOCPP_MINOR);
}

#ifdef _WIN32
char path_sep = ';';
char dir_sep='\\';
#else
char path_sep = ':';
char dir_sep='/';
#endif
void include_dirs(const char* str)
{
  const char* beg=str;
  const char* end;
  yaooc_string_t temp = YAOOC_STRING_STATIC_DEFAULT_CTOR;
  while(1) {
    end = strchr(beg,path_sep);
    if(end==NULL)
      end = beg+strlen(beg);
    for(;beg < end && isspace(*beg);beg++);
    if(beg < end) {
      M(&temp,setn,beg,end-beg);
#ifdef _WIN32
      // "/" as seperators works in Windows as well
      M(&temp,gsub_,"\\","/");
#endif
      // Make sure a "/" at end
      if(!M(&temp,ends_with,"/"))
        M(&temp,append,"/");
      M(&include_directories,push_back,&temp);
    }
    if(*end ==0)
      break;
    beg=end+1;
  }
/*
  for(;*beg != 0 && isspace(*beg);beg++);
  if(*beg != 0) {
    M(&temp,set,beg);
    // Make sure a dir_seperator at the end;
    M(&include_directories,push_back,&temp);
  }
*/
  deletep(&temp,yaooc_string);
}

/*
  Parser options.  Returns the index of the first argument that is not an options
*/
int parse_options(int argc,char* argv[])
{
  int iarg=0;
//  const char* valptr;
  for(iarg=1;iarg<argc;iarg++) {
    if(argv[iarg][0] != '-')  // not an option, stop processing
      break;
    if(strcmp(argv[iarg],"-h")==0 || strcmp(argv[iarg],"--help")==0) {
      print_help(argv[0]);
      exit(0);
    } else if(strcmp(argv[iarg],"-v")==0 || strcmp(argv[iarg],"--version")==0) {
      print_version(argv[0]);
      exit(0);
    } else if(strcmp(argv[iarg],"-I") == 0 || strcmp(argv[iarg],"--include") == 0) {
      if((iarg+1) >= argc) {
        printf("Expecting value following option %s\n",argv[iarg]);
        print_help(argv[0]);
        exit(3);
      }
      iarg++;
      include_dirs(argv[iarg]);
    } else if(strcmp(argv[iarg],"-D") == 0 || strcmp(argv[iarg],"--define") == 0) {
      if((iarg+1) >= argc) {
        printf("Expecting value following option %s\n",argv[iarg]);
        print_help(argv[0]);
        exit(3);
      }
      iarg++;
      M(&defines,append, " -D");
      M(&defines,append,argv[iarg]);
    } else if(strcmp(argv[iarg],"-hd") == 0 || strcmp(argv[iarg],"--header-directory") == 0) {
      if((iarg+1) >= argc) {
        printf("Expecting value following option %s\n",argv[iarg]);
        print_help(argv[0]);
        exit(3);
      }
      iarg++;
      M(&header_directory,set,argv[iarg]);
    } else if(strcmp(argv[iarg],"-dd") == 0 || strcmp(argv[iarg],"--definition-directory") == 0) {
      if((iarg+1) >= argc) {
        printf("Expecting value following option %s\n",argv[iarg]);
        print_help(argv[0]);
        exit(3);
      }
      iarg++;
      M(&definition_directory,set,argv[iarg]);
    } else {
      printf("Invalid option %s\n",argv[iarg]);
      print_help(argv[0]);
      exit(20);
    }
  }
  return iarg;
}

char* root_name(const char* fname)
{
  char* temp=yaooc_strdup(fname);
  char *base=basename(temp);
  char *ptr=strchr(base,'.');
  size_t l = ptr-base;
  char* ret=new_array(char,l+1);
  strncpy(ret,base,l);
  ret[l]=0;
  delete(temp);
  return ret;
}

int main(int argc,char* argv[])
{
  yaooc_init();
	gb_init();
  gb_newp(&include_directories,yaooc_string_vector);
//  M(&include_directories,push_back,gb_new_ctor(yaooc_string,yaooc_string_ctor_ccs,""));
//	newp(&include_files,yaooc_string_vector);
//	M(&cpp,set,"cpp -nostdinc");
  int iarg = parse_options(argc,argv);
  if(M(&definition_directory,size)==0)
    assign_static(&definition_directory,&header_directory,yaooc_string);
/*  printf("Defines -- %s\n"
         "Header directory -- %s\n"
         "Definition directory -- %s\n",
         M(&defines,c_str),M(&header_directory,c_str),M(&definition_directory,c_str));
  printf("Include directories\n");
  yaooc_string_vector_const_iterator id;
  CFOR_EACH(id,&include_directories) {
    printf("  X%sX\n",M(id,c_str));
  }*/
  yaooc_ofstream_t h_strm,c_strm,yod_strm;
  newp(&h_strm,yaooc_ofstream);
  newp(&c_strm,yaooc_ofstream);
  newp(&yod_strm,yaooc_ofstream);
  if(iarg < argc) {
		TRY {
//			for(i=optind;i<argc;i++) {
        yaoocpp_parser_t parser;
        newp(&parser,yaoocpp_parser);
        M(&parser,parse_file,argv[iarg]);
        if(M(&parser.sections_,size)>0) {
          char* root;
          if(M(&output_file,size) > 0)
            root=yaooc_strdup(M(&output_file,c_str));
          else
            root=gb_save(root_name(argv[iarg]));
          size_t l=M(&header_directory,size)+strlen(root)+5; // header_directory + "/" + root + ".h"
          char* header_fname=gb_new_array(char,l);
          *header_fname=0;
          if(M(&header_directory,size)>0) {
            strcpy(header_fname,M(&header_directory,c_str));
            strcat(header_fname,"/");
          }
          strcat(header_fname,root);
          strcat(header_fname,".h");
          M(&h_strm,open,header_fname,"w");
          char* uc_root=gb_save(yaooc_upcase(root));
          M(&h_strm,printf,"#ifndef __%s_INCLUDED__\n"
                          "#define __%s_INCLUDED__\n\n",uc_root,uc_root);
          l = M(&definition_directory,size)+strlen(root)+7; // definition_directory + "/" + root + ".yod"
          char* yod_fname=gb_new_array(char,l);
          *yod_fname=0;
          if(M(&definition_directory,size)>0) {
            strcpy(yod_fname,M(&definition_directory,c_str));
            strcat(yod_fname,"/");
          }
          strcat(yod_fname,root);
          strcat(yod_fname,".yod");
          M(&yod_strm,open,yod_fname,"w");
          M(&yod_strm,printf,"%%ifndef __%s_YOD_INCLUDED__\n"
                          "%%define __%s_YOD_INCLUDED__\n\n",uc_root,uc_root);

          if(strcmp(root,"object")!=0)
            M(&yod_strm,printf,"%%include <yaooc/object.yod>\n");
          char* source_fname=gb_new_array(char,strlen(root)+3);
          strcpy(source_fname,root);
          strcat(source_fname,".c");
          M(&c_strm,open,source_fname,"w");
          if(M(&yaoocpp_header_prefix,size)==0) {
            M(&c_strm,printf,"#include \"%s.h\"\n\n",root);
          } else {
            M(&c_strm,printf,"#include <%s/%s.h>\n",M(&yaoocpp_header_prefix,c_str),root);
          }

          yaoocpp_item_pointer_vector_const_iterator k;

//  				M(cout,printf,"%zu sections defined\n",M(&parser.sections_,size));
          CFOR_EACH(k,&parser.sections_) {
            yaoocpp_section_const_pointer section=(yaoocpp_section_const_pointer)k->ptr_;
            if(section->defined_in_top_level_file_) {
//              printf("Section %s of type %s\n",M(&section->name_,c_str),section->class_table_->type_name_);
              M(section,print_to_header,&h_strm);
              M(section,print_to_source,&c_strm);
              M(section,print_to_yod,&yod_strm);
            }
//            M(cout,printf,"%s %d\n",M(&section->name_,c_str),section->defined_in_top_level_file_);
          }
//          M(cout,printf,"%zu mixins defined\n",M(&parser.mixins_,size));
          CFOR_EACH(k,&parser.mixins_) {
            yaoocpp_mixin_const_pointer mixin=(yaoocpp_mixin_const_pointer)k->ptr_;
            if(mixin->defined_in_top_level_file_) {
              M(mixin,print_to_yod,&yod_strm);
            }
          }
          M(&h_strm,printf,"\n#endif\n");
          M(&yod_strm,printf,"\n%%endif\n");

          M(&h_strm,close);
          M(&c_strm,close);
          M(&yod_strm,close);
//          delete(&parser.sections_);
        }
        deletep(&parser,yaoocpp_parser);
//      }
		} CATCH(yaoocpp_parser_exception,e) {
			M(cerr,printf,"%s\n",M(e,what));
//			exit(0);
		} CATCH(yaooc_exception,e) {
			M(e,what); // To avoid compiler warnings
			M(cerr,printf,"Unknow exception occured\n");
//			exit(0);
		} ETRY
	}
  deletep(&h_strm,yaooc_ofstream);
  deletep(&c_strm,yaooc_ofstream);
  deletep(&yod_strm,yaooc_ofstream);
  deletep(&header_directory,yaooc_string);
  deletep(&definition_directory,yaooc_string);
//  deletep(&cpp,yaooc_string);
//  deletep(&include_directories,yaooc_string);
  deletep(&output_file,yaooc_string);
  gb_exit();
	return 0;
}
