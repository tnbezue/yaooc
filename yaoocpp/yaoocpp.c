#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaooc/vector.h>
#include <yaooc/map.h>
#include <libgen.h>
#include <ctype.h>
#include "yaooc_definition_parser.h"
#include <yaooc/garbage_bag.h>
#include <getopt.h>

#define YAOOCPP_MAJOR 1
#define YAOOCPP_MINOR 0
void print_info()
{
  printf("YAOOCPP -- Yet Another Object Oriented C PreProcessor\n");
}

void print_version()
{
  print_info();
  printf("Version: %d.%d",YAOOCPP_MAJOR,YAOOCPP_MINOR);
}

void print_help()
{
  print_info();
  printf("Syntax: yaoocpp [ -h | --help ]\n");
  printf("        yaoocpp [ -v | --version ]\n");
  printf("        yaoocpp file.yaooc\n");
  printf("Where:\n");
  printf("  -h|--help -- prints this help\n");
  printf("  -v|--version -- prints version information\n");
  printf("  file.yaooc -- preprocesses file.yaooc into file.h.template and file.c.template\n");
}

char *root_name(const char* fname_in)
{
  char* fname_out=new_array(char,1024);
  strcpy(fname_out,fname_in);
  char *ptr=basename(fname_out);
  memmove(fname_out,ptr,strlen(ptr)+1);
  ptr=strchr(fname_out,'.');
  if(ptr) *ptr=0;
  return fname_out;
}

void write_header(const char* root,item_definition_shared_ptr_vector_const_pointer classes)
{
  GB_INIT;
  yaooc_string_pointer header=GB_SAVE(new_ctor(yaooc_string,yaooc_string_ctor_ccs,root));
  yaooc_string_pointer header_block=GB_SAVE(M(header,upcase));
  M(header,append,".h.template");
  FILE* out=fopen(M(header,c_str),"w");
  if(out) {
    fprintf(out,"#ifndef __%s_INCLUDED__\n"
                "#define __%s_INCLUDED__\n\n"
                "#include <yaooc/object.h>\n\n",M(header_block,c_str),M(header_block,c_str));
    item_definition_shared_ptr_vector_const_iterator ci;
    for(ci=M(classes,cbegin);ci!=M(classes,cend);ci++) {
      M(M(ci,cget),print_to_header_class,out);
      M(M(ci,cget),print_to_header_prototype,out);
      M(M(ci,cget),print_to_header_define,out);
      fprintf(out,"\n");
    }
    fprintf(out,"#endif\n");
    fclose(out);
  }
  GB_EXIT;
}

void write_source(const char* root,item_definition_shared_ptr_vector_const_pointer classes)
{
  GB_INIT;
  yaooc_string_pointer source=GB_SAVE(new_ctor(yaooc_string,yaooc_string_ctor_ccs,root));
  yaooc_string_pointer header=GB_SAVE(new_ctor(yaooc_string,yaooc_string_ctor_ccs,root));
  M(source,append,".c.template");
  FILE* out=fopen(M(source,c_str),"w");
  if(out) {
    fprintf(out,"#include \"%s.h\"\n\n",M(header,c_str));
    item_definition_shared_ptr_vector_const_iterator ci;
    for(ci=M(classes,cbegin);ci!=M(classes,cend);ci++) {
      M(M(ci,cget),print_to_source,out);
    }
    fprintf(out,"\n");
    fclose(out);
  }
  GB_EXIT;
}

static struct option long_options[] =
  {
    {"version", no_argument,       0, 'v'},
    {"help",   no_argument,      0, 'h'},
    {0, 0, 0, 0}
  };

void parse_options(int argc,char* argv[])
{
  int c;
  int option_index = 0;
  c = getopt_long (argc, argv, "vh",long_options, &option_index);
  switch(c) {
    case -1:
      break;

    case 'v':
      print_version();
      exit(0);

    case 'h':
    default:
      print_help();
      exit(0);

  }
}

int main(int argc,char* argv[])
{
  GB_INIT;
  parse_options(argc,argv);
  if(optind == argc) {
    print_help();
    return 0;
  }
  yaooc_definition_parser_pointer ydp=GB_SAVE(new(yaooc_definition_parser));
  int i;
  item_definition_shared_ptr_vector_pointer classes;
  for(i=1;i<argc;i++) {
    classes=GB_SAVE(M(ydp,parse_file,argv[i]));
    if(classes != NULL && M(classes,size) > 0) {
      char* root=GB_SAVE(root_name(argv[i]));
      write_header(root,classes);
      write_source(root,classes);
    }
  }
  GB_EXIT;
}
