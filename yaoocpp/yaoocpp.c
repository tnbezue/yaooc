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
#include <string.h>
#include <getopt.h>
#include <libgen.h>
#include <ctype.h>
#include <yaooc/string.h>
#include <yaooc/pointer_bag.h>
#include "class_parser.h"

yaooc_string_t* includes;
yaooc_string_t* cpp;
//yaooc_string_pointer defines;

#define YAOOCPP_MAJOR 1
#define YAOOCPP_MINOR 4
void print_info()
{
  printf("YAOOCPP -- Yet Another Object Oriented C PreProcessor\n");
}

void print_help(const char* pgm)
{
  print_info();
  printf("Syntax: %s [ -h | --help ]\n",pgm);
  printf("        %s [ -v | --version ]\n",pgm);
  printf("        %s [ -I | --include <path> ] [ -Dmacro<=value> ] file.yaooc\n",pgm);
  printf("Where:\n");
  printf("  -h|--help -- prints this help\n");
  printf("  -v|--version -- prints version information\n");
  printf("  -I|--include -- Include path for C preprocessor\n");
  printf("  -D|--define  -- Define macro\n");
  printf("  file.yaooc -- preprocesses file.yaooc into file.h.template and file.c.template\n");
}

void print_version()
{
  print_info();
  printf("Version: %d.%d\n",YAOOCPP_MAJOR,YAOOCPP_MINOR);
}

void parse_options(int argc,char* argv[])
{
  struct option options[] =
  {
    {"help", no_argument, 0, 'h' },
    {"version", no_argument, 0, 'v'},
    {"include", required_argument, 0, 'I'},
    {"preprocessor",required_argument, 0, 'p'},
//    {"define", required_argument, 0, 'D' },
    { 0,0,0,0 }
  };
  int c;
  int option_index=0;
  while((c=getopt_long(argc,argv,"hvI:p:D:",options,&option_index)) > 0) {
    switch(c) {
      case 'I':
        M(includes,append," -I");
        M(includes,append,optarg);
        break;

/*      case 'D':
        M(defines,append, " -D");
        M(defines,append,optarg);
        break;
*/
      case 'p':
        M(cpp,set,optarg);
        break;

      case 'v':
        print_version();
        exit(0);

      case 'h':
      default:
        print_help(argv[0]);
        exit(0);

    }
  }
}

yaooc_string_pointer root_name(const char* fname)
{
  char* temp=yaooc_strdup(fname);
  yaooc_string_pointer ret=new(yaooc_string);
  char *base=basename(temp);
  char *ptr=strchr(base,'.');
  M(ret,setn,base,ptr-base);
  delete(temp);
  return ret;
}

void write_header(yaooc_string_const_pointer root,yaoocpp_item_ptr_vector_const_pointer classes)
{
  PB_INIT;
  yaooc_string_pointer header=PB_SAVE(new_ctor(yaooc_string,yaooc_string_ctor_ccs,M(root,c_str)));
  yaooc_string_pointer header_block=PB_SAVE(M(header,upcase));
  M(header,append,".h.template");
  yaooc_ofstream_pointer out=PB_SAVE(new_ctor(yaooc_ofstream,yaooc_ofstream_ctor_fname_mode,M(header,c_str),"w"));
  if(out) {
    M(out,printf,"#ifndef __%s_INCLUDED__\n"
                "#define __%s_INCLUDED__\n\n"
                "#include <yaooc/object.h>\n\n",M(header_block,c_str),M(header_block,c_str));
    M(out,printf,"/*  Begin YAOOC PreProcessor generated content */\n\n");
    yaoocpp_item_ptr_vector_const_iterator ci;
    FOR_EACH(ci,classes)  {
      if(((yaoocpp_class_const_pointer)*ci)->defined_in_top_level_file_)
        M(((yaoocpp_class_const_pointer)*ci),print_to_header,out);
    }
    M(out,printf,"/*  End YAOOC PreProcessor generated content */\n\n#endif\n");
  }
  PB_EXIT;
}

void write_source(yaooc_string_const_pointer root,yaoocpp_item_ptr_vector_const_pointer classes)
{
  PB_INIT;
  yaooc_string_pointer source=PB_SAVE(new_ctor(yaooc_string,yaooc_string_ctor_ccs,M(root,c_str)));
//  yaooc_string_pointer header=PB_SAVE(new_ctor(yaooc_string,yaooc_string_ctor_ccs,M(root,c_str))));
  M(source,append,".c.template");
  yaooc_ofstream_pointer out=PB_SAVE(new_ctor(yaooc_ofstream,yaooc_ofstream_ctor_fname_mode,M(source,c_str),"w"));
  if(out) {
    M(out,printf,"#include \"%s.h\"\n\n",M(root,c_str));
    M(out,printf,"/*  Begin YAOOC PreProcessor generated content */\n\n");
    yaoocpp_item_ptr_vector_const_iterator ci;
    FOR_EACH(ci,classes)  {
      if(((yaoocpp_class_const_pointer)*ci)->defined_in_top_level_file_)
        M(((yaoocpp_class_const_pointer)*ci),print_to_source,out);
    }
    M(out,printf,"/*  End YAOOC PreProcessor generated content */\n");
  }
  PB_EXIT;
}

int main(int argc,char* argv[])
{
	setbuf(stdout,NULL);
	setbuf(stderr,NULL);
	PB_INIT;
  includes=PB_SAVE(new(yaooc_string));
//  defines=PB_SAVE(new(yaooc_string));
  cpp=PB_SAVE(new_ctor(yaooc_string,yaooc_string_ctor_ccs,"cpp -nostdinc"));
  parse_options(argc,argv);
  if(optind < argc) {
    yaoocpp_class_parser_pointer yaoocpp_parser = PB_SAVE(new(yaoocpp_class_parser));
    int j;
    for(j=optind;j<argc;j++) {
      if(M(yaoocpp_parser,parse_file,argv[j])) {
        if(M(yaoocpp_parser->classes_,size)> 0) {
          yaoocpp_item_ptr_vector_const_iterator i;
          FOR_EACH(i,yaoocpp_parser->classes_) {
//            M(*i,dump,stdout);
            yaooc_string_pointer root=PB_SAVE(root_name(argv[j]));
            write_header(root,yaoocpp_parser->classes_);
            write_source(root,yaoocpp_parser->classes_);
          }
        }
      } else {
        printf("Error processing file %s near %.30s\n",argv[j],yaoocpp_parser->current_pos_);
      }
    }
  } else {
    print_help(argv[0]);
  }
  PB_EXIT;
  return 0;
}
