#include "parser.h"


#define CLASS(term) YAOOC_PARSER_TRY_RULE(this,M(this,chr,'%',&term) && M(this,str,"class",&term))
#define STRUCT(term) YAOOC_PARSER_TRY_RULE(this,M(this,chr,'%',&term) && M(this,str,"struct",&term))
#define UNION(term) YAOOC_PARSER_TRY_RULE(this,M(this,chr,'%',&term) && M(this,str,"union",&term))
#define MIXIN(term) YAOOC_PARSER_TRY_RULE(this,M(this,chr,'%',&term) && M(this,str,"mixin",&term))
#define TABLE(term) (M(this,str,"table",&term) && M(this,chr,':',&term))
#define INSTANCE(term) (M(this,str,"instance",&term) && M(this,chr,':',&term))
#define ADJUNCT(term) (M(this,str,"adjunct",&term) && M(this,chr,':',&term))
#define PRIVATE(term) (M(this,str,"private",&term) && M(this,chr,':',&term))

#define __CONST__(term) M(this,str,"const",&term)
#define OPERATOR(term) M(this,str,"operator",&term)
#define COMMA(term) M(this,chr,',',&term)
#define COLON(term) M(this,chr,':',&term)
#define SEMICOLON(term) M(this,chr,';',&term)
#define EQUAL(term) M(this,chr,'=',&term)
#define LPAREN(term) M(this,chr,'(',&term)
#define RPAREN(term) M(this,chr,')',&term)
#define LBRACE(term) M(this,chr,'{',&term)
#define RBRACE(term) M(this,chr,'}',&term)
#define LBRACKET(term) M(this,chr,'[',&term)
#define RBRACKET(term) M(this,chr,']',&term)
#define STAR(term) M(this,chr,'*',&term)

#define IS_DELETE(t) (strncmp(t.beg_,"delete",6)==0)
#define IS_DEFAULT(t) (strncmp(t.beg_,"default",7)==0)

char yaoocpp_parser_current_file[PATH_MAX];
char yaoocpp_parser_file_being_parsed[PATH_MAX];
bool yaoocpp_parser_is_top_level=false;
yaooc_string_t yaoocpp_header_prefix = YAOOC_STRING_STATIC_DEFAULT_CTOR;
extern yaooc_string_t defines;
extern yaooc_string_vector_t include_directories;



static int header_count=0;
static int source_count=0;





#define LINE_LENGTH 1024
static yaooc_string_t* preprocess(const char* file)
{
  gb_init();
  yaooc_string_t* contents=new(yaooc_string);
  regex_t re_cpp_line,re_yaoocpp_line,re_yaoocpp_include;
  if(regcomp(&re_cpp_line,"^\\s*#\\s*(.)",REG_EXTENDED) == 0 &&
        regcomp(&re_yaoocpp_line,"^\\s*%\\s*(if|define|endif)\\s+",REG_EXTENDED) == 0 &&
        regcomp(&re_yaoocpp_include,"^\\s*%\\s*(include)\\s+([<\"])([^\\.]+)\\.(yod|yoc)([>\"])",REG_EXTENDED) == 0) {
    regmatch_t ov[7];
    yaooc_ifstream_t input;
    newp(&input,yaooc_ifstream);
    M(&input,open,file,"r");
    if(M(&input,good)) {

      yaooc_string_t output;
      newp(&output,yaooc_string);
      M(&output,append,"# 1 \"");
      M(&output,append,file);
      M(&output,append,"\"\n");
      char* line = gb_new_array(char,LINE_LENGTH);
      while(!M(&input,eof)) {
        *line=0;
        M(&input,getstr,line,LINE_LENGTH);
        if(regexec(&re_cpp_line,line,7,ov,0) == 0) {
          M(&output,append,"%X#");
          M(&output,append,line+ov[1].rm_so);
        } else if(regexec(&re_yaoocpp_line,line,7,ov,0) == 0) {
          M(&output,append,"#");
          M(&output,append,line+ov[1].rm_so);
        } else if(regexec(&re_yaoocpp_include,line,7,ov,0) == 0) {
          M(&output,append,"#");
          M(&output,append,line+ov[1].rm_so);
          M(&output,append,"%header\n%X#include ");
          M(&output,appendn,line+ov[2].rm_so,ov[2].rm_eo-ov[2].rm_so);
          M(&output,appendn,line+ov[3].rm_so,ov[3].rm_eo-ov[3].rm_so);
          M(&output,append,".h");
          M(&output,appendn,line+ov[5].rm_so,ov[5].rm_eo-ov[5].rm_so);
          M(&output,append,"\n%%\n");
        } else
          M(&output,append,line);
      }
      M(&input,close);


      yaooc_string_t cpp_command;
      gb_newp(&cpp_command,yaooc_string);
      M(&cpp_command,set,"cpp  -nostdinc -fdirectives-only");
      if(M(&defines,size)>0) {
        M(&cpp_command,append," ");
        M(&cpp_command,append,M(&defines,c_str));
      }
      yaooc_string_vector_const_iterator id;
      CFOR_EACH(id,&include_directories) {
        M(&cpp_command,append," -I");
        M(&cpp_command,append,M(id,c_str));
      }
      yaooc_string_t* se=new(yaooc_string);
      int rc = command_pipe(M(&cpp_command,c_str),&output,contents,se);
      deletep(&cpp_command,yaooc_string);
      M(&output,set,M(contents,c_str));
      if(rc == 0) {
        rc = command_pipe("cpp -nostdinc -fpreprocessed",&output,contents,se);

      } else {
        puts("Error in 1st pass of CPP");
        puts(M(se,c_str));
        exit(99);
      }
      deletep(&output,yaooc_string);
      delete(se);
      M(contents,gsub_,"\n%X#","\n#");
    } else {
      puts("File not found");
    }
    deletep(&input,yaooc_ifstream);
    regfree(&re_yaoocpp_line);
    regfree(&re_cpp_line);
    regfree(&re_yaoocpp_include);
  } else {
    printf("Failed compiling CPP line\n");
    exit(3);
  }
  gb_exit();
  return contents;
}


bool yaoocpp_parser_line_directive(pointer __pthis__)
{
yaoocpp_parser_pointer this=__pthis__;(void)this;

      RULE_START(this);
      if(*this->current_pos_ == '#') {
        this->current_pos_+=2;
        yaooc_token_t temp;
        if(M(this,digits,&temp)) {
          this->line_no_=atoi(temp.beg_)-1;
          this->current_pos_++;
          if(*this->current_pos_ == '"') {
            this->current_pos_++;
            const char* pos=this->current_pos_;
            for(;*this->current_pos_!='"' && *this->current_pos_!=0;this->current_pos_++);
            if(*this->current_pos_ != 0) {
              strncpy(yaoocpp_parser_file_being_parsed,pos,this->current_pos_-pos);
              yaoocpp_parser_file_being_parsed[this->current_pos_-pos]=0;
              yaoocpp_parser_is_top_level=strcmp(yaoocpp_parser_current_file,yaoocpp_parser_file_being_parsed) == 0;
              for(;*this->current_pos_!='\n' && *this->current_pos_!=0;this->current_pos_++);
              yaooc_base_parser_whitespace(this,&temp);
              return RULE_SUCCESS(this);
            }
          }
        }
      }
      return RULE_FAIL(this);
    
}
bool yaoocpp_parser_header_directory(pointer __pthis__)
{
yaoocpp_parser_pointer this=__pthis__;(void)this;

      RULE_START(this);
      yaooc_token_t temp,dirname;
      if(M(this,chr,'%',&temp)) {


        int saved_line_no=this->line_no_;
        if(M(this,str,"header_directory",&temp)) {
          if(saved_line_no == this->line_no_) {
            if(M(this,double_quoted_string,&dirname) || M(this,bare_string,&dirname)) {
              M(&yaoocpp_header_prefix,setn,dirname.beg_,dirname.end_-dirname.beg_);
              M(&yaoocpp_header_prefix,rtrim_);
              return RULE_SUCCESS(this);
            }
          } else {
            printf("No directory specifed for header directory at line number %d\n",saved_line_no);
          }
        }
      }
      return RULE_FAIL(this);
    
}
bool yaoocpp_parser_header(pointer __pthis__,yaoocpp_section_t** section)
{
yaoocpp_parser_pointer this=__pthis__;(void)this;

      RULE_START(this);
      yaooc_token_t temp;
      if(M(this,chr,'%',&temp) && M(this,str,"header",&temp)) {
        int saved_line_no = this->line_no_;
        const char* start_pos=yaooc_base_parser_current_pos(this);
        while(!M(this,str,"%%",&temp) && *this->current_pos_ != 0) {
          M(this,string_until_eol,&temp);
        }
        if(temp.end_ == NULL) {
          printf("Unterminated header declaration starting near %d\n",saved_line_no);
          exit(5);
        }

          yaoocpp_header_t* hs= new(yaoocpp_header);
          char name[16];
          sprintf(name,"header_%03d",header_count++);
          M(&hs->name_,set,name);
          M(&hs->content_,setn,start_pos,temp.beg_-start_pos);
          hs->defined_in_top_level_file_=true;
          *section = (yaoocpp_section_t*)hs;

        return RULE_SUCCESS(this);
      }
      return RULE_FAIL(this);
    
}
bool yaoocpp_parser_source(pointer __pthis__,yaoocpp_section_t** section)
{
yaoocpp_parser_pointer this=__pthis__;(void)this;

      regex_t re;

      if(regcomp(&re,"%\\s*(class|struct|union|header|mixin|header_directory)\\s+",REG_EXTENDED)==0) {
        regmatch_t ov[3];
        const char* ptr;
        if(regexec(&re,this->current_pos_,3,ov,0)==0) {
          ptr=this->current_pos_+ov[0].rm_so;
        } else {
          ptr=this->current_pos_+strlen(this->current_pos_);
        }
        yaoocpp_source_t* ss = new(yaoocpp_source);
        char name[16];
        sprintf(name,"source_%03d",source_count++);
        M(&ss->name_,set,name);
        size_t n = ptr-this->current_pos_;
        M(&ss->content_,setn,this->current_pos_,n);
        ss->defined_in_top_level_file_=true;
        *section = (yaoocpp_section_t*)ss;
        yaooc_base_parser_skip(this,n);
        regfree(&re);
      } else {
        printf("Regex compilation failed failed");
        exit(-1);
      }
      return true;
    
}
bool yaoocpp_parser_class_forward(pointer __pthis__,yaoocpp_section_t** section)
{
yaoocpp_parser_pointer this=__pthis__;(void)this;

      RULE_START(this);
      yaooc_token_t t,name;
      if((CLASS(t) || STRUCT(t) || UNION(t)) && M(this,ident,&name) && SEMICOLON(t)) {
        yaoocpp_header_t* hs= new(yaoocpp_header);
        char hname[16];
        sprintf(hname,"header_%03d",header_count++);
        M(&hs->name_,set,hname);
        M(&hs->content_,set,"yaooc_class_forward(");
        M(&hs->content_,appendn,name.beg_,name.end_-name.beg_);
        M(&hs->content_,append,");\n");
        hs->defined_in_top_level_file_=true;
        *section = (yaoocpp_section_t*)hs;
        return RULE_SUCCESS(this);
      }
      return RULE_FAIL(this);
    
}
bool yaoocpp_parser_class_definition(pointer __pthis__,yaoocpp_section_t** section)
{
yaoocpp_parser_pointer this=__pthis__;(void)this;

      yaooc_token_t temp;
      RULE_START(this);
      *section = NULL;
      bool is_struct = false;
      if(CLASS(temp))
        *section=(yaoocpp_section_t*)new(yaoocpp_class);
      else if(UNION(temp))
        *section=(yaoocpp_section_t*)new(yaoocpp_union);
      else if(STRUCT(temp)) {
        *section=(yaoocpp_section_t*)new(yaoocpp_struct);
        is_struct = true;
      }
      if(*section != NULL) {
        ((yaoocpp_struct_t*)*section)->defined_in_top_level_file_=yaoocpp_parser_is_top_level;
        yaooc_token_t class_name;
        M(this,ident,&class_name);
        M(&(*section)->name_,setn,class_name.beg_,class_name.end_-class_name.beg_);
        if(strncmp(class_name.beg_,"yaooc_object",class_name.end_-class_name.beg_) != 0) {

          char* parent_name=NULL;
          if(!yaoocpp_parser_get_parent_name(this,&parent_name) && !is_struct)
            parent_name=yaooc_strdup("yaooc_object");
          if(parent_name != NULL ) {
            if(!yaoocpp_parser_set_parent(this,parent_name,&((yaoocpp_struct_t*)*section)->parent_)) {
              printf("Parent class '%s' for '%.*s' not defined\n",parent_name,(int)(class_name.end_-class_name.beg_),class_name.beg_);
              exit(6);
            }
          if(is_struct)
            yaoocpp_struct_inherit(*section);
          else
            yaoocpp_class_inherit(*section);
          }
        }
        if(LBRACE(temp)) {
          while(true) {
            if(!yaoocpp_parser_type_info(this,(yaoocpp_struct_t*)*section))
              if(!yaoocpp_parser_constructor(this,(yaoocpp_struct_t*)*section))
                break;
          }
          while(true) {
            if(TABLE(temp)) {
              if(is_struct) {
                printf("Table not allowed for struct %.*s",(int)(class_name.end_-class_name.beg_),class_name.beg_);
                exit(7);
              }
              yaoocpp_parser_sub_section(this,&((yaoocpp_class_t*)*section)->table_,true);
            } else if(INSTANCE(temp)) {
              yaoocpp_parser_sub_section(this,&((yaoocpp_struct_t*)*section)->instance_,false);
            } else if(ADJUNCT(temp)) {
              yaoocpp_parser_sub_section(this,&((yaoocpp_struct_t*)*section)->adjunct_,true);
            } else if(PRIVATE(temp)) {
              yaoocpp_parser_sub_section(this,&((yaoocpp_struct_t*)*section)->private_,true);
            } else
              break;
          }
        }
        if(RBRACE(temp) && SEMICOLON(temp)) {
          if(((yaoocpp_struct_t*)*section)->defined_in_top_level_file_) {
            M(((yaoocpp_struct_t*)*section),resolve_outstanding_components);
            M(*section,add_mixins,&this->mixins_);
          }
          return RULE_SUCCESS(this);
        }
        else {
          printf("Error processing %s near line number %d\n",yaoocpp_parser_file_being_parsed,this->line_no_);
          exit(7);
        }
      }
      return RULE_FAIL(this);
    
}
bool yaoocpp_parser_sub_section(pointer __pthis__,yaoocpp_item_pointer_vector_t* list,bool include_value)
{
yaoocpp_parser_pointer this=__pthis__;(void)this;

      yaoocpp_variable_t* var;
      yaoocpp_method_t* method;
      while(true) {
        if(yaoocpp_parser_variable(this,&var,include_value)) {
          yaoocpp_variable_pointer* existing_var = yaooc_find(yaoocpp_item_pointer,M(list,cbegin),M(list,cend),(pointer)&var);
          if(existing_var == M(list,cend)) {
            M(list,push_back,(pointer)&var);
            existing_var=M(list,begin);
          } else {
            if((*existing_var)->generation_!=INHERITED) {

              printf("Duplicate variable specified on or before line number %d\n",this->line_no_);
              printf("X%sX X%sX\n",M(&(*existing_var)->name_,c_str),M(&var->name_,c_str));
              exit(3);
            }
            (*existing_var)->generation_=OVERRIDDEN;
            assign_static(&((*existing_var)->value_),&var->value_,yaooc_string);
          }
          delete(var);
        } else if(yaoocpp_parser_method(this,&method)) {
          yaoocpp_method_t** existing_method = yaooc_find(yaoocpp_item_pointer,M(list,begin),M(list,end),(pointer)&var);
          if(existing_method == M(list,cend))
            M(list,push_back,(pointer)&method);
          else {
            if((*existing_method)->generation_!=INHERITED) {

              printf("Duplicate method specified on or before line number %d\n",this->line_no_);
              exit(3);
            }
            assign_static(*existing_method,method,yaoocpp_method);
            (*existing_method)->generation_=OVERRIDDEN;

          }
          delete(method);
        } else
          break;
      }
      return true;
    
}
bool yaoocpp_parser_variable(pointer __pthis__,yaoocpp_variable_t** var,bool include_value)
{
yaoocpp_parser_pointer this=__pthis__;(void)this;

      RULE_START(this);
      yaooc_token_t t,val;
      yaoocpp_argument_t* arg;
      *var=NULL;
      if(yaoocpp_parser_argument(this,&arg)) {
        *var = new(yaoocpp_variable);
        assign_static(*var,arg,yaoocpp_argument);
        delete(arg);
        int saved_line_no=this->line_no_;
        if(YAOOC_PARSER_TRY_RULE(this,EQUAL(t) && M(this,string_until_chrs,";",&val) && SEMICOLON(t))) {
          if(!include_value) {
            printf("Unexpected default value near line number %d\n",saved_line_no);
            exit(17);
          }
          M(&(*var)->value_,setn,val.beg_,val.end_-val.beg_);
          return RULE_SUCCESS(this);
        } else if(SEMICOLON(t)) {

          M(&(*var)->value_,set,"0");
          return RULE_SUCCESS(this);
        }
      }
      return RULE_FAIL(this);
    
}
bool yaoocpp_parser_method(pointer __pthis__,yaoocpp_method_t** method)
{
yaoocpp_parser_pointer this=__pthis__;(void)this;

      RULE_START(this);
      yaooc_token_t t,implementation;
      yaoocpp_argument_t* arg;
      if(yaoocpp_parser_argument(this,&arg) && LPAREN(t)) {
        *method = new(yaoocpp_method);
        M(&(*method)->type_,set,M(&arg->type_,c_str));
        M(&(*method)->name_,set,M(&arg->name_,c_str));
        delete(arg);
        yaoocpp_parser_arguments(this,&(*method)->arguments_);
        if(RPAREN(t)) {
          if(__CONST__(t))
            (*method)->is_const_=true;
          if(M(this,string_within_matching_chr,'{','}',&implementation)) {
            M((*method),set_implementation,implementation.beg_,implementation.end_-implementation.beg_);
            return RULE_SUCCESS(this);
          } else if (EQUAL(t) && (M(this,ident,&implementation) || M(this,str,"0",&implementation)) && SEMICOLON(t)) {
            M((*method),set_implemented_as,implementation.beg_,implementation.end_-implementation.beg_);
            return RULE_SUCCESS(this);
          } else {
            printf("Error processing implementation for method %s\n",M(&(*method)->name_,c_str));
          }
        }
      }
      return RULE_FAIL(this);
    
}
bool yaoocpp_parser_get_parent_name(pointer __pthis__,char** name)
{
yaoocpp_parser_pointer this=__pthis__;(void)this;

      yaooc_token_t temp;
      if(COLON(temp)) {
        if(!M(this,ident,&temp)) {
          printf("Expecting parent name after ':' near line %d",this->line_no_);
          exit(8);
        }
        *name=yaooc_token_raw_text(&temp);
        return true;
      }
      return false;
    
}
bool yaoocpp_parser_set_parent(pointer __pthis__,const char* parent_name,const yaoocpp_struct_t** parent)
{
yaoocpp_parser_pointer this=__pthis__;(void)this;


      yaoocpp_item_pointer_vector_const_iterator i;
      CFOR_EACH(i,&this->sections_) {
        if(strcmp(M(&(*i)->name_,c_str),parent_name)==0) {
          *parent=(yaoocpp_struct_t*)*i;
          return true;
        }
      }
      return false;
    
}
bool yaoocpp_parser_type_info(pointer __pthis__,yaoocpp_struct_t* section)
{
yaoocpp_parser_pointer this=__pthis__;(void)this;

      bool ret=true;
      if(!yaoocpp_parser_default_constructor(this,section,true))
        if(!yaoocpp_parser_destructor(this,section))
          if(!yaoocpp_parser_copy_constructor(this,section,true))
            if(!yaoocpp_parser_assignment(this,section))
              if(!yaoocpp_parser_rich_compare(this,section))
                if(!yaoocpp_parser_to_stream(this,section))
                  if(!yaoocpp_parser_from_stream(this,section))
                    if(!yaoocpp_parser_include(this,section))
                      ret=false;
      return ret;
    
}
bool yaoocpp_parser_constructor_initializers(pointer __pthis__,yaoocpp_item_pointer_vector_t* list)
{
yaoocpp_parser_pointer this=__pthis__;(void)this;

      yaooc_token_t t,id,value;
      gb_init();
      do {
        int saved_line_no = this->line_no_;
        if(M(this,ident,&id)) {
          saved_line_no = this->line_no_;
          if(M(this,string_within_matching_chr,'(',')',&value)) {
            char* id_text=gb_save(yaooc_token_raw_text(&id));
            char* value_text=gb_save(yaooc_token_raw_text(&value));
            yaoocpp_constructor_initializer_t* temp=gb_new_ctor(yaoocpp_constructor_initializer,
                  yaoocpp_constructor_initializer_ctor_id_value,id_text,value_text);
            M(list,push_back,(pointer)&temp);
          } else {
            printf("Error processing constructor initializers near line %d\n",saved_line_no);
            exit(9);
          }
        } else {
          printf("Error processing constructor initializers near line %d\n",saved_line_no);
          exit(10);
        }
      } while(COMMA(t));
      gb_exit();
      return true;
    
}
bool yaoocpp_parser_default_constructor(pointer __pthis__,yaoocpp_struct_t* section,bool allow_initializers)
{
yaoocpp_parser_pointer this=__pthis__;(void)this;

      yaooc_token_t t,implementation;
      const char* class_name=M(&section->name_,c_str);
      RULE_START(this);
      bool has_initializers=false;
      if(M(this,str,class_name,&t) && LPAREN(t) && RPAREN(t)) {
        M(&section->default_ctor_.name_,set,class_name);

        if(COLON(t)) {
          has_initializers=true;
          yaoocpp_parser_constructor_initializers(this,&section->default_ctor_.initializers_);
        }
        if(has_initializers && !allow_initializers) {
          printf("Constructor initializers not allowed here.  Near line %d\n",this->line_no_);
          exit(77);
        }
        if(YAOOC_PARSER_TRY_RULE(this,M(this,string_within_matching_chr,'{','}',&implementation))) {

          M(&section->default_ctor_,set_implementation,implementation.beg_,implementation.end_-implementation.beg_);
          return RULE_SUCCESS(this);
        } else if(EQUAL(t) && M(this,ident,&implementation) && SEMICOLON(t)) {
          if(has_initializers) {
            printf("Error processing default constructor for class %s\n"
                   "Cannot specify construction initializers and implementation method",class_name);
            exit(1);
          }
          if(IS_DELETE(implementation)) {
            section->default_ctor_.form_=DELETE;
          } else if(IS_DEFAULT(implementation)) {
            section->default_ctor_.form_=DEFAULT;
          } else {
            M(&section->default_ctor_,set_implemented_as,implementation.beg_,implementation.end_-implementation.beg_);
          }
          return RULE_SUCCESS(this);
        } else {
          printf("Error processing file %s at line number %d\n",yaoocpp_parser_file_being_parsed,this->line_no_);
          exit(1);
        }
      }
      return RULE_FAIL(this);
    
}
bool yaoocpp_parser_destructor(pointer __pthis__,yaoocpp_struct_t* section)
{
yaoocpp_parser_pointer this=__pthis__;(void)this;

      yaooc_token_t t,implementation;
      const char* class_name=M(&section->name_,c_str);
      RULE_START(this);
      if(M(this,chr,'~',&t) && M(this,str,class_name,&t) && LPAREN(t) && RPAREN(t)) {
        M(&section->dtor_.name_,set,class_name);

        if(YAOOC_PARSER_TRY_RULE(this,M(this,string_within_matching_chr,'{','}',&implementation))) {

          M(&section->dtor_,set_implementation,implementation.beg_,implementation.end_-implementation.beg_);
          return RULE_SUCCESS(this);
        } else if(EQUAL(t) && M(this,ident,&implementation) && SEMICOLON(t)) {

          if(IS_DELETE(implementation)) {
            section->dtor_.form_=DELETE;
          } else if(IS_DEFAULT(implementation)) {
            section->dtor_.form_=DEFAULT;
          } else {
            M(&section->dtor_,set_implemented_as,implementation.beg_,implementation.end_-implementation.beg_);
          }
          return RULE_SUCCESS(this);
        } else {
          printf("Error processing file %s at line number %d\n",yaoocpp_parser_file_being_parsed,this->line_no_);
          exit(1);
        }
      }
      return RULE_FAIL(this);
    
}
bool yaoocpp_parser_copy_constructor(pointer __pthis__,yaoocpp_struct_t* section,bool allow_initializers)
{
yaoocpp_parser_pointer this=__pthis__;(void)this;

      yaooc_token_t t,src_name,implementation;
      const char* class_name=M(&section->name_,c_str);
      RULE_START(this);
      bool has_initializers=false;
      if(M(this,str,class_name,&t) && LPAREN(t) && M(this,ident,&src_name) && RPAREN(t)) {
        M(&section->copy_ctor_.name_,set,class_name);

        M(&section->copy_ctor_,set_source_name,src_name.beg_,src_name.end_-src_name.beg_);
        if(COLON(t)) {
          has_initializers=true;
          yaoocpp_parser_constructor_initializers(this,&section->copy_ctor_.initializers_);
        }
        if(has_initializers && !allow_initializers) {
          printf("Constructor initializers not allowed here.  Near line %d\n",this->line_no_);
          exit(77);
        }
        if(YAOOC_PARSER_TRY_RULE(this,M(this,string_within_matching_chr,'{','}',&implementation))) {

          M(&section->copy_ctor_,set_implementation,implementation.beg_,implementation.end_-implementation.beg_);
          return RULE_SUCCESS(this);
        } else if(EQUAL(t) && M(this,ident,&implementation) && SEMICOLON(t)) {
          if(has_initializers) {
            printf("Error processing copy constructor for class %s\n"
                   "Cannot specify construction initializers and implementation method",class_name);
            exit(1);
          }

          if(IS_DELETE(implementation)) {
            section->copy_ctor_.form_=DELETE;
          } else if(IS_DEFAULT(implementation)) {
            section->copy_ctor_.form_=DEFAULT;
          } else {
            M(&section->copy_ctor_,set_implemented_as,implementation.beg_,implementation.end_-implementation.beg_);
          }
          return RULE_SUCCESS(this);
        } else {
          printf("Error processing file %s at line number %d\n",yaoocpp_parser_file_being_parsed,this->line_no_);
          exit(1);
        }
      }
      return RULE_FAIL(this);
    
}
bool yaoocpp_parser_assignment(pointer __pthis__,yaoocpp_struct_t* section)
{
yaoocpp_parser_pointer this=__pthis__;(void)this;

      yaooc_token_t t,src_name,implementation;
      RULE_START(this);
      if(M(this,str,"operator",&t) && EQUAL(t) && LPAREN(t) && M(this,ident,&src_name) && RPAREN(t)) {
        M(&section->assign_.name_,set,M(&section->name_,c_str));
        M(&section->assign_,set_source_name,src_name.beg_,src_name.end_-src_name.beg_);
        if(YAOOC_PARSER_TRY_RULE(this,M(this,string_within_matching_chr,'{','}',&implementation))) {

          M(&section->assign_,set_implementation,implementation.beg_,implementation.end_-implementation.beg_);
          return RULE_SUCCESS(this);
        } else if(EQUAL(t) && M(this,ident,&implementation) && SEMICOLON(t)) {

          if(IS_DELETE(implementation)) {
            section->assign_.form_=DELETE;
          } else if(IS_DEFAULT(implementation)) {
            section->assign_.form_=DEFAULT;
          } else {
            M(&section->assign_,set_implemented_as,implementation.beg_,implementation.end_-implementation.beg_);
          }
          return RULE_SUCCESS(this);
        } else {
          printf("Error processing file %s at line number %d\n",yaoocpp_parser_file_being_parsed,this->line_no_);
          exit(1);
        }
      }
      return RULE_FAIL(this);
    
}
bool yaoocpp_parser_rich_compare(pointer __pthis__,yaoocpp_struct_t* section)
{
yaoocpp_parser_pointer this=__pthis__;(void)this;

      yaooc_token_t t,lhs_name,rhs_name,implementation;
      RULE_START(this);
      if(M(this,str,"int",&t) && OPERATOR(t) && M(this,str,"<=>",&t) && LPAREN(t) &&
            M(this,ident,&lhs_name) && COMMA(t) && M(this,ident,&rhs_name) && RPAREN(t)) {
        M(&section->rich_compare_.name_,set,M(&section->name_,c_str));
        M(&section->rich_compare_,set_lhs_name,lhs_name.beg_,lhs_name.end_-lhs_name.beg_);
        M(&section->rich_compare_,set_rhs_name,rhs_name.beg_,rhs_name.end_-rhs_name.beg_);
        if(YAOOC_PARSER_TRY_RULE(this,M(this,string_within_matching_chr,'{','}',&implementation))) {

          M(&section->rich_compare_,set_implementation,implementation.beg_,implementation.end_-implementation.beg_);
          return RULE_SUCCESS(this);
        } else if(EQUAL(t) && M(this,ident,&implementation) && SEMICOLON(t)) {
          if(IS_DELETE(implementation)) {
            section->rich_compare_.form_=DELETE;
          } else if(IS_DEFAULT(implementation)) {
            section->rich_compare_.form_=DEFAULT;
          } else {
            M(&section->rich_compare_,set_implemented_as,implementation.beg_,implementation.end_-implementation.beg_);
          }
          return RULE_SUCCESS(this);
        } else {
          printf("Error processing file %s at line number %d\n",yaoocpp_parser_file_being_parsed,this->line_no_);
          exit(1);
        }
      }
      return RULE_FAIL(this);
    
}
bool yaoocpp_parser_to_stream(pointer __pthis__,yaoocpp_struct_t* section)
{
yaoocpp_parser_pointer this=__pthis__;(void)this;

      yaooc_token_t t,strm_name,implementation;
      RULE_START(this);
      if(M(this,str,"operator",&t) && M(this,str,"<<",&t) && LPAREN(t) && M(this,ident,&strm_name) && RPAREN(t)) {
        M(&section->to_stream_.name_,set,M(&section->name_,c_str));

        M(&section->to_stream_,set_stream_name,strm_name.beg_,strm_name.end_-strm_name.beg_);
        if(YAOOC_PARSER_TRY_RULE(this,M(this,string_within_matching_chr,'{','}',&implementation))) {

          M(&section->to_stream_,set_implementation,implementation.beg_,implementation.end_-implementation.beg_);
          return RULE_SUCCESS(this);
        } else if(EQUAL(t) && M(this,ident,&implementation) && SEMICOLON(t)) {

          return RULE_SUCCESS(this);
        } else {
          printf("Error processing file %s at line number %d\n",yaoocpp_parser_file_being_parsed,this->line_no_);
          exit(1);
        }
      }
      return RULE_FAIL(this);
    
}
bool yaoocpp_parser_from_stream(pointer __pthis__,yaoocpp_struct_t* section)
{
yaoocpp_parser_pointer this=__pthis__;(void)this;

      yaooc_token_t t,strm_name,implementation;
      RULE_START(this);
      if(M(this,str,"operator",&t) && M(this,str,">>",&t) && LPAREN(t) && M(this,ident,&strm_name) && RPAREN(t)) {
        M(&section->from_stream_.name_,set,M(&section->name_,c_str));

        M(&section->from_stream_,set_stream_name,strm_name.beg_,strm_name.end_-strm_name.beg_);
        if(YAOOC_PARSER_TRY_RULE(this,M(this,string_within_matching_chr,'{','}',&implementation))) {

          M(&section->from_stream_,set_implementation,implementation.beg_,implementation.end_-implementation.beg_);
          return RULE_SUCCESS(this);
        } else if(EQUAL(t) && M(this,ident,&implementation) && SEMICOLON(t)) {

          return RULE_SUCCESS(this);
        } else {
          printf("Error processing file %s at line number %d\n",yaoocpp_parser_file_being_parsed,this->line_no_);
          exit(1);
        }
      }
      return RULE_FAIL(this);
    
}
bool yaoocpp_parser_include(pointer __pthis__,yaoocpp_struct_t* section)
{
yaoocpp_parser_pointer this=__pthis__;(void)this;

      RULE_START(this);
      yaooc_token_t t,id;
      if(M(this,str,"include",&t)) {
#define mixin_vector &((yaoocpp_struct_pointer)section)->mixins_
        do {
          int saved_line_no=this->line_no_;
          if(M(this,ident,&id)) {
            yaooc_string_t temp = YAOOC_STRING_STATIC_DEFAULT_CTOR;
            M(&temp,setn,id.beg_,id.end_-id.beg_);
            if(yaooc_find(yaooc_string,M(mixin_vector,begin),M(mixin_vector,end),&temp) != M(mixin_vector,end))
            {
              printf("Duplicate mixin specified on or before line %d\n",saved_line_no);
              exit(30);
            }
            M(mixin_vector,push_back,&temp);
            deletep(&temp,yaooc_string);
          } else {
            printf("Error including mixins on or before line %d\n",saved_line_no);
            exit(31);
          }
        } while(COMMA(t));
        if(SEMICOLON(t)) {
          return RULE_SUCCESS(this);
        }
#undef mixin_vector
      }
      return RULE_FAIL(this);
    
}
bool yaoocpp_parser_va_argument(pointer __pthis__,yaoocpp_argument_t** arg)
{
yaoocpp_parser_pointer this=__pthis__;(void)this;

      RULE_START(this);
      yaooc_token_t t;
      if(M(this,str,"...",&t)) {
        *arg=new(yaoocpp_argument);
        M(&(*arg)->type_,setn,t.beg_,t.end_-t.beg_);
        if(M(this,ident,&t)) {
          M(&(*arg)->name_,setn,t.beg_,t.end_-t.beg_);
        } else {
          M(&(*arg)->name_,set,"args");
        }
        return RULE_SUCCESS(this);
      }
      return RULE_FAIL(this);
    
}
bool yaoocpp_parser_argument(pointer __pthis__,yaoocpp_argument_t** arg)
{
yaoocpp_parser_pointer this=__pthis__;(void)this;

      RULE_START(this);
      yaooc_token_t t;
      *arg = NULL;
      if(M(this,ident,&t)) {
        *arg = new(yaoocpp_argument);
        M(&(*arg)->type_,setn,t.beg_,t.end_-t.beg_);
        while(true) {
          if(M(this,ident,&t)) {
            if(M(&(*arg)->name_,size)>0) {
              M(&(*arg)->type_,append," ");
              M(&(*arg)->type_,append,M(&(*arg)->name_,c_str));
            }
            M(&(*arg)->name_,setn,t.beg_,t.end_-t.beg_);
          } else if(STAR(t)) {
            if(M(&(*arg)->name_,size)>0) {
              M(&(*arg)->type_,append," ");
              M(&(*arg)->type_,append,M(&(*arg)->name_,c_str));
              M(&(*arg)->name_,clear);
            }
            M(&(*arg)->type_,append,"*");
          } else
            break;
        }
        if(M(&(*arg)->name_,size) > 0) {

          while(M(this,string_within_matching_chr,'[',']',&t)) {
            M(&(*arg)->array_def_,append,"[");
            M(&(*arg)->array_def_,appendn,t.beg_,t.end_-t.beg_);
            M(&(*arg)->array_def_,append,"]");
          }
          return M(&(*arg)->name_,size) > 0 ? RULE_SUCCESS(this) : RULE_FAIL(this);
        }
      }
      if(*arg != NULL)
        delete(*arg);
      return RULE_FAIL(this);
    
}
bool yaoocpp_parser_arguments(pointer __pthis__,yaoocpp_item_pointer_vector_t* args)
{
yaoocpp_parser_pointer this=__pthis__;(void)this;

      yaooc_token_t t;
      bool ret=false;
      do {
        yaoocpp_argument_t* arg;
        if(yaoocpp_parser_argument(this,&arg)) {
          M(args,push_back,(pointer)&arg);
          delete(arg);
        } else if(yaoocpp_parser_va_argument(this,&arg)) {
          M(args,push_back,(pointer)&arg);
          delete(arg);
        } else
          break;
        ret=true;
      } while(COMMA(t));
      return ret;
    
}
bool yaoocpp_parser_constructor(pointer __pthis__,yaoocpp_struct_t* section)
{
yaoocpp_parser_pointer this=__pthis__;(void)this;

      gb_init();
      RULE_START(this);
      bool has_initializers=false;
      yaooc_token_t t,con_name,implementation;
      int saved_line_no=this->line_no_;
      if(M(this,ident,&con_name) && LPAREN(t)) {
        size_t l = yaooc_token_len(con_name);
        if(l > M(&section->name_,size) && strncmp(con_name.beg_,M(&section->name_,c_str),M(&section->name_,size))==0) {

          yaoocpp_constructor_t* con=gb_new(yaoocpp_constructor);
          M(&con->name_,setn,con_name.beg_,l);
          if(yaooc_find(yaoocpp_item_pointer,M(&section->constructors_,cbegin),M(&section->constructors_,cend),(pointer)&con)
                != M(&section->constructors_,cend)) {
            printf("Duplicate constructor %s specified on line number %d\n",M(&con->name_,c_str),saved_line_no);
            exit(12);
          }
          if(yaoocpp_parser_arguments(this,&con->arguments_)) {
            if(RPAREN(t)) {
              if(COLON(t)) {
                has_initializers=true;
                yaoocpp_parser_constructor_initializers(this,&con->initializers_);
              }
              if(M(this,string_within_matching_chr,'{','}',&implementation)) {
                M(con,set_implementation,implementation.beg_,implementation.end_-implementation.beg_);
              } else if (EQUAL(t) && M(this,ident,&implementation) && SEMICOLON(t)) {
                if(has_initializers) {
                  printf("Error processing constructor %.*s\n"
                         "Cannot specify construction initializers and implementation method.",
                         (int)(con_name.end_-con_name.beg_),con_name.beg_);
                  exit(1);
                }
                M(con,set_implemented_as,implementation.beg_,implementation.end_-implementation.beg_);
              } else {
                printf("Error processing imlementation for constructor %.*s\n",(int)l,con_name.beg_);
                exit(3);
              }
              M(&section->constructors_,push_back,(pointer)&con);
              delete(con);
              return RULE_SUCCESS(this);
            }
            printf("Error parsing constructor at line number %d\n",saved_line_no);
            exit(33);
          } else {

            printf("Constructors must have at least 1 argument.\n"
                  "Constructor %.*s has zero arguments.\n",(int)l,con_name.beg_);
            exit(22);
          }
        }
      }
      gb_exit();
      return RULE_FAIL(this);
    
}
bool yaoocpp_parser_mixin(pointer __pthis__,yaoocpp_mixin_t** mixin)
{
yaoocpp_parser_pointer this=__pthis__;(void)this;

      RULE_START(this);
      yaooc_token_t t,mixin_name;
      if(MIXIN(t)) {
        M(this,ident,&mixin_name);
        *mixin = new(yaoocpp_mixin);
        (*mixin)->defined_in_top_level_file_=yaoocpp_parser_is_top_level;
        M(&(*mixin)->name_,setn,mixin_name.beg_,mixin_name.end_-mixin_name.beg_);
        if(LBRACE(t)) {
          while(true) {
            if(!yaoocpp_parser_default_constructor(this,(yaoocpp_struct_t*)*mixin,false))
              if(!yaoocpp_parser_destructor(this,(yaoocpp_struct_t*)*mixin))
                if(!yaoocpp_parser_copy_constructor(this,(yaoocpp_struct_t*)*mixin,false))
                  if(!yaoocpp_parser_assignment(this,(yaoocpp_struct_t*)*mixin))
                    break;
          }
          while(true) {
            if(TABLE(t)) {
              yaoocpp_parser_sub_section(this,&(*mixin)->table_,true);
            } else if(INSTANCE(t)) {
              yaoocpp_parser_sub_section(this,&(*mixin)->instance_,false);
            } else if(ADJUNCT(t)) {
              yaoocpp_parser_sub_section(this,&(*mixin)->adjunct_,true);
            } else if(PRIVATE(t)) {
              yaoocpp_parser_sub_section(this,&(*mixin)->private_,true);
            } else
              break;
          }
        }
        if(RBRACE(t) && SEMICOLON(t)) {
          return RULE_SUCCESS(this);
        }
        else {
          printf("Error processing %s near line number %d\n",yaoocpp_parser_file_being_parsed,this->line_no_);
          exit(7);
        }
      }
      return RULE_FAIL(this);
    
}
bool yaoocpp_parser_whitespace(pointer __pthis__,yaooc_token_t* r)
{
yaoocpp_parser_pointer this=__pthis__;(void)this;
#define super() yaoocpp_parser_parent_class_table->whitespace(this,r)
#define PM(method,...) CTM((*yaoocpp_parser_parent_class_table),this,method,## __VA_ARGS__)


      *r = yaooc_default_token(this);
      yaooc_token_t temp;
      bool rc=false;
      while(true) {
        rc = yaooc_base_parser_whitespace(this,&temp);
        if(!rc) {
          rc=yaoocpp_parser_line_directive(this);
          if(!rc)
            break;
        }
      }
      r->end_=yaooc_base_parser_current_pos(this);
      return r->beg_ != r->end_;
    
#undef PM
#undef super
}
void yaoocpp_parser_parse_file(pointer __pthis__,const char* fname)
{
yaoocpp_parser_pointer this=__pthis__;(void)this;
#define super() yaoocpp_parser_parent_class_table->parse_file(this,fname)
#define PM(method,...) CTM((*yaoocpp_parser_parent_class_table),this,method,## __VA_ARGS__)


      strcpy(yaoocpp_parser_current_file,fname);
      yaooc_string_t* result = preprocess(fname);

      M(this,set_parse_string,M(result,c_str));
      yaooc_token_t r;
      M(this,whitespace,&r);
      yaoocpp_section_t* current_section;
      yaoocpp_mixin_t* mixin;
      while(true) {
        if(yaoocpp_parser_class_forward(this,&current_section)) {
          M(&this->sections_,push_back,(pointer)&current_section);
          delete(current_section);
        } else if(yaoocpp_parser_class_definition(this,&current_section)) {
          M(&this->sections_,push_back,(pointer)&current_section);
          delete(current_section);
        } else if(yaoocpp_parser_header_directory(this)) {


        } else if(yaoocpp_parser_header(this,(pointer)&current_section)) {
          M(&this->sections_,push_back,(pointer)&current_section);
          delete(current_section);
        } else if(yaoocpp_parser_mixin(this,&mixin)) {
          M(&this->mixins_,push_back,(pointer)&mixin);
          delete(mixin);


        } else if(*this->current_pos_ != 0) {
          yaoocpp_parser_source(this,&current_section);
          M(&this->sections_,push_back,(pointer)&current_section);
          delete(current_section);
        } else {
          break;
        }
      }
      delete(result);
    
#undef PM
#undef super
}
yaoocpp_parser_class_table_t yaoocpp_parser_class_table ={
.parent_class_table_ = (const class_table_t*) &yaooc_base_parser_class_table,
.type_name_ = (const char*) "yaoocpp_parser_t",
.swap = (void(*)(pointer,pointer)) yaoocpp_parser_swap,
.set_parse_string = (void(*)(pointer,const char*)) yaoocpp_parser_set_parse_string,
.rule_start = (void(*)(pointer)) yaoocpp_parser_rule_start,
.rule_success = (bool(*)(pointer)) yaoocpp_parser_rule_success,
.rule_fail = (bool(*)(pointer)) yaoocpp_parser_rule_fail,
.eos = (bool(*)(pointer)) yaoocpp_parser_eos,
.chr = (bool(*)(pointer,char,yaooc_token_t*)) yaoocpp_parser_chr,
.chr_choices = (int(*)(pointer,const char*,yaooc_token_t*)) yaoocpp_parser_chr_choices,
.str = (bool(*)(pointer,const char*,yaooc_token_t*)) yaoocpp_parser_str,
.str_choices = (int(*)(pointer,yaooc_token_t*,...)) yaoocpp_parser_str_choices,
.digits = (bool(*)(pointer,yaooc_token_t*)) yaoocpp_parser_digits,
.hexdigits = (bool(*)(pointer,yaooc_token_t*)) yaoocpp_parser_hexdigits,
.integer = (bool(*)(pointer,yaooc_token_t*)) yaoocpp_parser_integer,
.hexinteger = (bool(*)(pointer,yaooc_token_t*)) yaoocpp_parser_hexinteger,
.real = (bool(*)(pointer,yaooc_token_t*)) yaoocpp_parser_real,
.ident = (bool(*)(pointer,yaooc_token_t*)) yaoocpp_parser_ident,
.regex = (bool(*)(pointer,regex_t*,uint32_t,size_t,regmatch_t*,yaooc_token_t*)) yaoocpp_parser_regex,
.quoted_string = (bool(*)(pointer,char,yaooc_token_t*)) yaoocpp_parser_quoted_string,
.single_quoted_string = (bool(*)(pointer,yaooc_token_t*)) yaoocpp_parser_single_quoted_string,
.double_quoted_string = (bool(*)(pointer,yaooc_token_t*)) yaoocpp_parser_double_quoted_string,
.bare_string = (bool(*)(pointer,yaooc_token_t*)) yaoocpp_parser_bare_string,
.string_until_chrs = (bool(*)(pointer,const char*,yaooc_token_t*)) yaoocpp_parser_string_until_chrs,
.string_while_chrs = (bool(*)(pointer,const char*,yaooc_token_t*)) yaoocpp_parser_string_while_chrs,
.string_until_eol = (bool(*)(pointer,yaooc_token_t*)) yaoocpp_parser_string_until_eol,
.whitespace = (bool(*)(pointer,yaooc_token_t*)) yaoocpp_parser_whitespace,
.string_within_matching_chr = (bool(*)(pointer,char,char,yaooc_token_t*)) yaoocpp_parser_string_within_matching_chr,
.result = (bool(*)(const_pointer)) yaoocpp_parser_result,
.parse_file = (void(*)(pointer,const char*)) yaoocpp_parser_parse_file,
};
void yaoocpp_parser_default_ctor(pointer __pthis__)
{
yaoocpp_parser_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaoocpp_parser);



      yaooc_base_parser_default_ctor(this);
      newp(&this->sections_,yaoocpp_item_pointer_vector);
      newp(&this->mixins_,yaoocpp_item_pointer_vector);
    
}
void yaoocpp_parser_dtor(pointer __pthis__)
{
yaoocpp_parser_pointer this=__pthis__;(void)this;


      deletep(&this->sections_,yaoocpp_item_pointer_vector);
      deletep(&this->mixins_,yaoocpp_item_pointer_vector);
    
}
void yaoocpp_parser_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaoocpp_parser_pointer this=__pthis__;(void)this;
yaoocpp_parser_const_pointer src=__psrc__;(void)src;


call_default_ctor_static(this,yaoocpp_parser);
assign_static(this,src,yaoocpp_parser);

}
void yaoocpp_parser_assign(pointer __pthis__,const_pointer __psrc__)
{
yaoocpp_parser_pointer this=__pthis__;(void)this;
yaoocpp_parser_const_pointer src=__psrc__;(void)src;

assign_static(this,src,yaooc_base_parser);
assign_static(&this->sections_,&src->sections_,yaoocpp_item_pointer_vector);
assign_static(&this->mixins_,&src->mixins_,yaoocpp_item_pointer_vector);

}
const type_info_t __yaoocpp_parser_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaoocpp_parser_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaoocpp_parser_default_ctor,
.dtor_=yaoocpp_parser_dtor,
.copy_ctor_=yaoocpp_parser_copy_ctor,
.assign_=yaoocpp_parser_assign,
.class_table_=(const class_table_t*) &yaoocpp_parser_class_table,
.parent_=&__yaooc_base_parser_ti
};
const type_info_t* const yaoocpp_parser_ti=&__yaoocpp_parser_ti;
yaoocpp_parser_exception_class_table_t yaoocpp_parser_exception_class_table ={
.parent_class_table_ = (const class_table_t*) &yaooc_exception_class_table,
.type_name_ = (const char*) "yaoocpp_parser_exception_t",
.swap = (void(*)(pointer,pointer)) yaoocpp_parser_exception_swap,
.what = (const char*(*)(const_pointer)) yaoocpp_parser_exception_what,
};
const type_info_t __yaoocpp_parser_exception_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaoocpp_parser_exception_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=NULL,
.dtor_=NULL,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaoocpp_parser_exception_class_table,
.parent_=&__yaooc_exception_ti
};
const type_info_t* const yaoocpp_parser_exception_ti=&__yaoocpp_parser_exception_ti;
