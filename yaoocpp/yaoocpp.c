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
#include <yaooc/string.h>
#include <yaooc/pointer_bag.h>
#include <yaooc/exception.h>
#include <yaooc/fstream.h>
#include <string.h>
#include <libgen.h>
#include "parser.h"

yaooc_string_t include_directories = YAOOC_STRING_STATIC_DEFAULT_CTOR;
yaooc_string_t cpp = YAOOC_STRING_STATIC_DEFAULT_CTOR;
yaooc_string_t defines = YAOOC_STRING_STATIC_DEFAULT_CTOR;
yaooc_string_t output_file = YAOOC_STRING_STATIC_DEFAULT_CTOR;
yaooc_string_t header_extra = YAOOC_STRING_STATIC_DEFAULT_CTOR;
yaooc_string_t source_extra = YAOOC_STRING_STATIC_DEFAULT_CTOR;
yaooc_string_vector_t include_files;

#define YAOOCPP_MAJOR 1
#define YAOOCPP_MINOR 3

void print_info()
{
  M(cout,printf,"YAOOCPP -- Yet Another Object Oriented C PreProcessor\n");
}

void print_help(const char* pgm)
{
  print_info();
  M(cout,printf,"Syntax: %s [ -h | --help ]\n",pgm);
  M(cout,printf,"        %s [ -v | --version ]\n",pgm);
  M(cout,printf,"        %s [ -I | --include path ] [ -Dmacro<=value> ] [ -o | --output prefix ] file.yaooc\n",pgm);
  M(cout,printf,"Where:\n");
  M(cout,printf,"  -h|--help -- prints this help\n");
  M(cout,printf,"  -v|--version -- prints version information\n");
  M(cout,printf,"  -I|--include -- Include path for C preprocessor (multiple -I directives may be specified)\n");
  M(cout,printf,"  -D|--define  -- Define macro (multiple -D directives may be specified)\n");
  M(cout,printf,"  -o|--output  -- Specifies output file prefix.  Appended with \".h.template\" and \".c.template\"\n");
//  M(cout,printf,"  -p|--cpp -- C preprocessor to use.  \n");
  M(cout,printf,"  file.yaooc -- File to preprocesses.  If output prefix not specified, then \"file\" is used as output prefix\n");
}

void print_version()
{
  print_info();
  M(cout,printf,"Version: %d.%d\n",YAOOCPP_MAJOR,YAOOCPP_MINOR);
}

void parse_options(int argc,char* argv[])
{
  struct option options[] =
  {
    {"help", no_argument, 0, 'h' },
    {"version", no_argument, 0, 'v'},
    {"include", required_argument, 0, 'I'},
//    {"cpp",required_argument, 0, 'p'},
    {"define", required_argument, 0, 'D' },
    {"output",required_argument, 0, 'o' },
    { 0,0,0,0 }
  };
  int c;
  int option_index=0;
  while((c=getopt_long(argc,argv,"hvI:p:D:",options,&option_index)) > 0) {
    switch(c) {
      case 'I':
        M(&include_directories,append," -I");
        M(&include_directories,append,optarg);
        break;

      case 'D':
        M(&defines,append, " -D");
        M(&defines,append,optarg);
        break;

      case 'p':
        M(&cpp,set,optarg);
        break;

      case 'v':
        print_version();
        exit(0);

      case 'o':
        M(&output_file,set,optarg);
        break;

      case 'h':
      default:
        print_help(argv[0]);
        exit(0);

    }
  }
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
	PB_INIT;
	newp(&include_files,yaooc_string_vector);
	newp(&header_extra,yaooc_string);
	newp(&source_extra,yaooc_string);
	M(&cpp,set,"cpp -nostdinc");
  parse_options(argc,argv);
  yaooc_ofstream_t h_strm,c_strm;
  newp(&h_strm,yaooc_ofstream);
  newp(&c_strm,yaooc_ofstream);
  yaoocpp_parser_t class_parser;
  newp(&class_parser,yaoocpp_parser);
  if(optind < argc) {
		TRY {
			int i;
			for(i=optind;i<argc;i++) {
				M(&header_extra,clear);
				M(&source_extra,clear);
				M(&include_files,clear);
				M(&class_parser,parse_file,argv[i]);
        if(M(class_parser.classes_,size) > 0) {
          char* root;
          if(M(&output_file,size) > 0)
            root=yaooc_strdup(M(&output_file,c_str));
          else
            root=PB_SAVE(root_name(argv[i]));
          size_t l=strlen(root)+12; // root + ".[ch].template"
          char* header_fname=PB_SAVE(new_array(char,l));
          strcpy(header_fname,root);
          strcat(header_fname,".h.template");
          M(&h_strm,open,header_fname,"w");
          char* uc_root=PB_SAVE(yaooc_upcase(root));
          M(&h_strm,printf,"#ifndef __%s_INCLUDED__\n"
                           "#define __%s_INCLUDED__\n\n",uc_root,uc_root);
          M(&h_strm,printf,"/* Begin YAOOCPP output */\n\n");
/*          M(&h_strm,printf,"#include <yaooc/object.h>\n"
                           "#include <yaooc/stream.h>\n"
                           "\n");*/
					if(M(&include_files,size)>0) {
						yaooc_string_vector_const_iterator ifile;
						FOR_EACH(ifile,&include_files)
							M(&h_strm,printf,"#include <%s.h>\n",M(ifile,c_str));
						M(&h_strm,printf,"\n");
					}
					if(M(&header_extra,size)>0)
						M(&h_strm,printf,"\n%s\n",M(&header_extra,c_str));

          char* source_fname=PB_SAVE(new_array(char,l));
          strcpy(source_fname,root);
          strcat(source_fname,".c.template");
          M(&c_strm,open,source_fname,"w");
          M(&c_strm,printf,"/* Begin YAOOCPP output */\n\n");
          M(&c_strm,printf,"#include \"%s.h\"\n\n",root);
					if(M(&source_extra,size)>0)
						M(&c_strm,printf,"\n%s\n",M(&source_extra,c_str));

          yaoocpp_container_pointer_vector_const_iterator k;

  //				M(cout,printf,"%zu classes defined\n",M(classes,size));
          FOR_EACH(k,class_parser.classes_) {
            if((*k)->defined_in_top_level_file_) {
              M(*k,print_to_header,&h_strm);
              M(*k,print_to_source,&c_strm);
            }
  //          M(cout,printf,"%s %d\n",M(&((yaoocpp_class_pointer)(*k))->name_,c_str),((yaoocpp_class_pointer)(*k))->defined_in_top_level_file_);
          }
          M(&h_strm,printf,"/* End YAOOCPP output */\n\n");
          M(&h_strm,printf,"\n#endif\n");
          M(&c_strm,printf,"/* End YAOOCPP output */\n\n");

          M(&h_strm,close);
          M(&c_strm,close);
        }
      }
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
  deletep(&class_parser,yaoocpp_parser);
  deletep(&cpp,yaooc_string);
  deletep(&include_directories,yaooc_string);
  deletep(&output_file,yaooc_string);
	deletep(&header_extra,yaooc_string);
	deletep(&source_extra,yaooc_string);
	deletep(&include_files,yaooc_string_vector);
  PB_EXIT;
	return 0;
}
