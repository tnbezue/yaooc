#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaooc/vector.h>
#include <yaooc/map.h>
#include <libgen.h>
#include <ctype.h>
#include "yaooc_definition_parser.h"
#include <yaooc/garbage_bag.h>

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

int main(int argc,char* argv[])
{
  GB_INIT;
	setbuf(stdout,NULL);
	setbuf(stderr,NULL);
  yaooc_definition_parser_pointer ydp=GB_SAVE(new(yaooc_definition_parser));
  int i;
  item_definition_shared_ptr_vector_pointer classes; //=new(class_definition_vector_ti);
  for(i=1;i<argc;i++) {
    classes=GB_SAVE(M(ydp,parse_file,argv[i]));
    if(classes != NULL && M(classes,size) > 0) {
/*      item_definition_shared_ptr_vector_const_iterator j;
      CFOR_EACH(j,classes) {
        M(M(j,cget),dump,stdout,0);
      }*/
      char* root=GB_SAVE(root_name(argv[i]));
      write_header(root,classes);
      write_source(root,classes);
    }
  }
  GB_EXIT;
}
