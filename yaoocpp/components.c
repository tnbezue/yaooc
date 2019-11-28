#include "components.h"

void yaoocpp_item_set_line_no(pointer __pthis__,int n)
{
yaoocpp_item_pointer this=__pthis__;(void)this;
#define super() yaoocpp_item_parent_class_table->set_line_no(this,n)
#define PM(method,...) CTM((*yaoocpp_item_parent_class_table),this,method,## __VA_ARGS__)


      this->line_no_=n;
    
#undef PM
#undef super
}
yaoocpp_item_class_table_t yaoocpp_item_class_table ={
.parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
.type_name_ = (const char*) "yaoocpp_item_t",
.swap = (void(*)(pointer,pointer)) yaoocpp_item_swap,
.set_line_no = (void(*)(pointer,int)) yaoocpp_item_set_line_no,
};
void yaoocpp_item_default_ctor(pointer __pthis__)
{
yaoocpp_item_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaoocpp_item);


newp(&this->name_,yaooc_string);
this->line_no_=(int)0;

}
void yaoocpp_item_dtor(pointer __pthis__)
{
yaoocpp_item_pointer this=__pthis__;(void)this;

deletep(&this->name_,yaooc_string);

}
void yaoocpp_item_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaoocpp_item_pointer this=__pthis__;(void)this;
yaoocpp_item_const_pointer src=__psrc__;(void)src;

call_default_ctor_static(this,yaoocpp_item);
assign_static(this,src,yaoocpp_item);


}
void yaoocpp_item_assign(pointer __pthis__,const_pointer __psrc__)
{
yaoocpp_item_pointer this=__pthis__;(void)this;
yaoocpp_item_const_pointer src=__psrc__;(void)src;

assign_static(this,src,yaooc_object);
assign_static(&this->name_,&src->name_,yaooc_string);
this->line_no_=src->line_no_;

}
int yaoocpp_item_rich_compare(const_pointer __plhs__,const_pointer __prhs__)
{
yaoocpp_item_const_pointer lhs=__plhs__;(void)lhs;
yaoocpp_item_const_pointer rhs=__prhs__;(void)rhs;

      return yaooc_string_rich_compare(&lhs->name_,&rhs->name_);
    
}
const type_info_t __yaoocpp_item_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaoocpp_item_t),
.rich_compare_=yaoocpp_item_rich_compare,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaoocpp_item_default_ctor,
.dtor_=yaoocpp_item_dtor,
.copy_ctor_=yaoocpp_item_copy_ctor,
.assign_=yaoocpp_item_assign,
.class_table_=(const class_table_t*) &yaoocpp_item_class_table,
.parent_=&__yaooc_object_ti
};
const type_info_t* const yaoocpp_item_ti=&__yaoocpp_item_ti;

VECTOR_IMPLEMENTATION(yaooc_dynamic_pointer,yaoocpp_item_pointer_vector);





yaoocpp_argument_class_table_t yaoocpp_argument_class_table ={
.parent_class_table_ = (const class_table_t*) &yaoocpp_item_class_table,
.type_name_ = (const char*) "yaoocpp_argument_t",
.swap = (void(*)(pointer,pointer)) yaoocpp_argument_swap,
.set_line_no = (void(*)(pointer,int)) yaoocpp_argument_set_line_no,
};
void yaoocpp_argument_default_ctor(pointer __pthis__)
{
yaoocpp_argument_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaoocpp_argument);


newp(&this->type_,yaooc_string);
newp(&this->array_def_,yaooc_string);

}
void yaoocpp_argument_dtor(pointer __pthis__)
{
yaoocpp_argument_pointer this=__pthis__;(void)this;

deletep(&this->type_,yaooc_string);
deletep(&this->array_def_,yaooc_string);

}
void yaoocpp_argument_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaoocpp_argument_pointer this=__pthis__;(void)this;
yaoocpp_argument_const_pointer src=__psrc__;(void)src;

call_default_ctor_static(this,yaoocpp_argument);
assign_static(this,src,yaoocpp_argument);


}
void yaoocpp_argument_assign(pointer __pthis__,const_pointer __psrc__)
{
yaoocpp_argument_pointer this=__pthis__;(void)this;
yaoocpp_argument_const_pointer src=__psrc__;(void)src;

assign_static(this,src,yaoocpp_item);
assign_static(&this->type_,&src->type_,yaooc_string);
assign_static(&this->array_def_,&src->array_def_,yaooc_string);

}
const type_info_t __yaoocpp_argument_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaoocpp_argument_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaoocpp_argument_default_ctor,
.dtor_=yaoocpp_argument_dtor,
.copy_ctor_=yaoocpp_argument_copy_ctor,
.assign_=yaoocpp_argument_assign,
.class_table_=(const class_table_t*) &yaoocpp_argument_class_table,
.parent_=&__yaoocpp_item_ti
};
const type_info_t* const yaoocpp_argument_ti=&__yaoocpp_argument_ti;
void yaoocpp_member_item_print_instance_prototype(const_pointer __pthis__,ostream_pointer __postrm,const char* class_name,const char* parent)
{
yaoocpp_member_item_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_member_item_parent_class_table->print_instance_prototype(this,ostrm,class_name,parent)
#define PM(method,...) CTM((*yaoocpp_member_item_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


    
#undef PM
#undef super
}
void yaoocpp_member_item_print_table_definition(const_pointer __pthis__,ostream_pointer __postrm,const char* class_name,const char* parent)
{
yaoocpp_member_item_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;

yaooc_pure_virtual("print_table_definition","yaoocpp_member_item");
}
void yaoocpp_member_item_print_table_implementation(const_pointer __pthis__,ostream_pointer __postrm,const char* class_name,const char* parent)
{
yaoocpp_member_item_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;

yaooc_pure_virtual("print_table_implementation","yaoocpp_member_item");
}
void yaoocpp_member_item_print_adjunct_prototype(const_pointer __pthis__,ostream_pointer __postrm,const char* class_name,const char* parent)
{
yaoocpp_member_item_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;

yaooc_pure_virtual("print_adjunct_prototype","yaoocpp_member_item");
}
void yaoocpp_member_item_print_adjunct_implementation(const_pointer __pthis__,ostream_pointer __postrm,const char* class_name,const char* parent)
{
yaoocpp_member_item_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;

yaooc_pure_virtual("print_adjunct_implementation","yaoocpp_member_item");
}
void yaoocpp_member_item_print_private_prototype(const_pointer __pthis__,ostream_pointer __postrm,const char* class_name,const char* parent)
{
yaoocpp_member_item_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;

yaooc_pure_virtual("print_private_prototype","yaoocpp_member_item");
}
void yaoocpp_member_item_print_private_implementation(const_pointer __pthis__,ostream_pointer __postrm,const char* class_name,const char* parent)
{
yaoocpp_member_item_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;

yaooc_pure_virtual("print_private_implementation","yaoocpp_member_item");
}
void yaoocpp_member_item_print_class_table_entry(const_pointer __pthis__,ostream_pointer __postrm,const char* class_name,const char* parent)
{
yaoocpp_member_item_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;

yaooc_pure_virtual("print_class_table_entry","yaoocpp_member_item");
}
void yaoocpp_member_item_print_yod_definition(const_pointer __pthis__,ostream_pointer __postrm,bool include_implementation)
{
yaoocpp_member_item_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;

yaooc_pure_virtual("print_yod_definition","yaoocpp_member_item");
}
yaoocpp_member_item_class_table_t yaoocpp_member_item_class_table ={
.parent_class_table_ = (const class_table_t*) &yaoocpp_argument_class_table,
.type_name_ = (const char*) "yaoocpp_member_item_t",
.swap = (void(*)(pointer,pointer)) yaoocpp_member_item_swap,
.set_line_no = (void(*)(pointer,int)) yaoocpp_member_item_set_line_no,
.print_instance_prototype = (void(*)(const_pointer,ostream_pointer,const char*,const char*)) yaoocpp_member_item_print_instance_prototype,
.print_table_definition = (void(*)(const_pointer,ostream_pointer,const char*,const char*)) yaoocpp_member_item_print_table_definition,
.print_table_implementation = (void(*)(const_pointer,ostream_pointer,const char*,const char*)) yaoocpp_member_item_print_table_implementation,
.print_adjunct_prototype = (void(*)(const_pointer,ostream_pointer,const char*,const char*)) yaoocpp_member_item_print_adjunct_prototype,
.print_adjunct_implementation = (void(*)(const_pointer,ostream_pointer,const char*,const char*)) yaoocpp_member_item_print_adjunct_implementation,
.print_private_prototype = (void(*)(const_pointer,ostream_pointer,const char*,const char*)) yaoocpp_member_item_print_private_prototype,
.print_private_implementation = (void(*)(const_pointer,ostream_pointer,const char*,const char*)) yaoocpp_member_item_print_private_implementation,
.print_class_table_entry = (void(*)(const_pointer,ostream_pointer,const char*,const char*)) yaoocpp_member_item_print_class_table_entry,
.print_yod_definition = (void(*)(const_pointer,ostream_pointer,bool)) yaoocpp_member_item_print_yod_definition,
};
void yaoocpp_member_item_default_ctor(pointer __pthis__)
{
yaoocpp_member_item_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaoocpp_member_item);
this->generation_=INITIAL;



    
}
void yaoocpp_member_item_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaoocpp_member_item_pointer this=__pthis__;(void)this;
yaoocpp_member_item_const_pointer src=__psrc__;(void)src;

call_default_ctor_static(this,yaoocpp_member_item);
assign_static(this,src,yaoocpp_member_item);


}
void yaoocpp_member_item_assign(pointer __pthis__,const_pointer __psrc__)
{
yaoocpp_member_item_pointer this=__pthis__;(void)this;
yaoocpp_member_item_const_pointer src=__psrc__;(void)src;


      yaoocpp_argument_assign(this,src);
      this->generation_=src->generation_;
    
}
const type_info_t __yaoocpp_member_item_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaoocpp_member_item_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaoocpp_member_item_default_ctor,
.dtor_=NULL,
.copy_ctor_=yaoocpp_member_item_copy_ctor,
.assign_=yaoocpp_member_item_assign,
.class_table_=(const class_table_t*) &yaoocpp_member_item_class_table,
.parent_=&__yaoocpp_argument_ti
};
const type_info_t* const yaoocpp_member_item_ti=&__yaoocpp_member_item_ti;
void yaoocpp_variable_print(const_pointer __pthis__,ostream_pointer __postrm,const char* class_name,const char* parent,const char* storage_class,bool include_value)
{
yaoocpp_variable_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      M(ostrm,printf,"%s %s %s_%s%s",storage_class,M(&this->type_,c_str),class_name,
              M(&this->name_,c_str),M(&this->array_def_,c_str));
      if(include_value)
        M(ostrm,printf,"=%s",M(&this->value_,c_str));
      M(ostrm,printf,";\n");
    
}
void yaoocpp_variable_print_instance_prototype(const_pointer __pthis__,ostream_pointer __postrm,const char* class_name,const char* parent)
{
yaoocpp_variable_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_variable_parent_class_table->print_instance_prototype(this,ostrm,class_name,parent)
#define PM(method,...) CTM((*yaoocpp_variable_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_variable_print(this,ostrm,class_name,parent,"extern",false);
    
#undef PM
#undef super
}
void yaoocpp_variable_print_table_definition(const_pointer __pthis__,ostream_pointer __postrm,const char* class_name,const char* parent)
{
yaoocpp_variable_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_variable_parent_class_table->print_table_definition(this,ostrm,class_name,parent)
#define PM(method,...) CTM((*yaoocpp_variable_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      M(ostrm,printf,"%s %s%s;\n",M(&this->type_,c_str),M(&this->name_,c_str),M(&this->array_def_,c_str));
    
#undef PM
#undef super
}
void yaoocpp_variable_print_table_implementation(const_pointer __pthis__,ostream_pointer __postrm,const char* class_name,const char* parent)
{
yaoocpp_variable_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_variable_parent_class_table->print_table_implementation(this,ostrm,class_name,parent)
#define PM(method,...) CTM((*yaoocpp_variable_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      M(ostrm,printf,".%s = (%s%s)%s,\n",M(&this->name_,c_str),M(&this->type_,c_str),
            M(&this->array_def_,c_str),M(&this->value_,c_str));
    
#undef PM
#undef super
}
void yaoocpp_variable_print_adjunct_prototype(const_pointer __pthis__,ostream_pointer __postrm,const char* class_name,const char* parent)
{
yaoocpp_variable_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_variable_parent_class_table->print_adjunct_prototype(this,ostrm,class_name,parent)
#define PM(method,...) CTM((*yaoocpp_variable_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_variable_print(this,ostrm,class_name,parent,"extern ",false);
    
#undef PM
#undef super
}
void yaoocpp_variable_print_adjunct_implementation(const_pointer __pthis__,ostream_pointer __postrm,const char* class_name,const char* parent)
{
yaoocpp_variable_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_variable_parent_class_table->print_adjunct_implementation(this,ostrm,class_name,parent)
#define PM(method,...) CTM((*yaoocpp_variable_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_variable_print(this,ostrm,class_name,parent,"extern ",false);
    
#undef PM
#undef super
}
void yaoocpp_variable_print_private_prototype(const_pointer __pthis__,ostream_pointer __postrm,const char* class_name,const char* parent)
{
yaoocpp_variable_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_variable_parent_class_table->print_private_prototype(this,ostrm,class_name,parent)
#define PM(method,...) CTM((*yaoocpp_variable_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;



    
#undef PM
#undef super
}
void yaoocpp_variable_print_private_implementation(const_pointer __pthis__,ostream_pointer __postrm,const char* class_name,const char* parent)
{
yaoocpp_variable_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_variable_parent_class_table->print_private_implementation(this,ostrm,class_name,parent)
#define PM(method,...) CTM((*yaoocpp_variable_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_variable_print(this,ostrm,class_name,parent,"static ",true);
    
#undef PM
#undef super
}
void yaoocpp_variable_print_class_table_entry(const_pointer __pthis__,ostream_pointer __postrm,const char* class_name,const char* parent)
{
yaoocpp_variable_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_variable_parent_class_table->print_class_table_entry(this,ostrm,class_name,parent)
#define PM(method,...) CTM((*yaoocpp_variable_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      M(ostrm,printf,".%s = (%s%s)%s,\n",M(&this->name_,c_str),M(&this->type_,c_str),
            M(&this->array_def_,c_str),M(&this->value_,c_str));
    
#undef PM
#undef super
}
void yaoocpp_variable_print_yod_definition(const_pointer __pthis__,ostream_pointer __postrm,bool include_default_value)
{
yaoocpp_variable_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_variable_parent_class_table->print_yod_definition(this,ostrm,include_default_value)
#define PM(method,...) CTM((*yaoocpp_variable_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      M(ostrm,printf,"%s %s%s",M(&this->type_,c_str),M(&this->name_,c_str),M(&this->array_def_,c_str));
      if(include_default_value)
        M(ostrm,printf,"=%s",M(&this->value_,c_str));
      M(ostrm,printf,";\n");
    
#undef PM
#undef super
}
yaoocpp_variable_class_table_t yaoocpp_variable_class_table ={
.parent_class_table_ = (const class_table_t*) &yaoocpp_member_item_class_table,
.type_name_ = (const char*) "yaoocpp_variable_t",
.swap = (void(*)(pointer,pointer)) yaoocpp_variable_swap,
.set_line_no = (void(*)(pointer,int)) yaoocpp_variable_set_line_no,
.print_instance_prototype = (void(*)(const_pointer,ostream_pointer,const char*,const char*)) yaoocpp_variable_print_instance_prototype,
.print_table_definition = (void(*)(const_pointer,ostream_pointer,const char*,const char*)) yaoocpp_variable_print_table_definition,
.print_table_implementation = (void(*)(const_pointer,ostream_pointer,const char*,const char*)) yaoocpp_variable_print_table_implementation,
.print_adjunct_prototype = (void(*)(const_pointer,ostream_pointer,const char*,const char*)) yaoocpp_variable_print_adjunct_prototype,
.print_adjunct_implementation = (void(*)(const_pointer,ostream_pointer,const char*,const char*)) yaoocpp_variable_print_adjunct_implementation,
.print_private_prototype = (void(*)(const_pointer,ostream_pointer,const char*,const char*)) yaoocpp_variable_print_private_prototype,
.print_private_implementation = (void(*)(const_pointer,ostream_pointer,const char*,const char*)) yaoocpp_variable_print_private_implementation,
.print_class_table_entry = (void(*)(const_pointer,ostream_pointer,const char*,const char*)) yaoocpp_variable_print_class_table_entry,
.print_yod_definition = (void(*)(const_pointer,ostream_pointer,bool)) yaoocpp_variable_print_yod_definition,
};
void yaoocpp_variable_default_ctor(pointer __pthis__)
{
yaoocpp_variable_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaoocpp_variable);


newp(&this->value_,yaooc_string);

}
void yaoocpp_variable_dtor(pointer __pthis__)
{
yaoocpp_variable_pointer this=__pthis__;(void)this;

deletep(&this->value_,yaooc_string);

}
void yaoocpp_variable_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaoocpp_variable_pointer this=__pthis__;(void)this;
yaoocpp_variable_const_pointer src=__psrc__;(void)src;

call_default_ctor_static(this,yaoocpp_variable);
assign_static(this,src,yaoocpp_variable);


}
void yaoocpp_variable_assign(pointer __pthis__,const_pointer __psrc__)
{
yaoocpp_variable_pointer this=__pthis__;(void)this;
yaoocpp_variable_const_pointer src=__psrc__;(void)src;

assign_static(this,src,yaoocpp_member_item);
assign_static(&this->value_,&src->value_,yaooc_string);

}
const type_info_t __yaoocpp_variable_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaoocpp_variable_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaoocpp_variable_default_ctor,
.dtor_=yaoocpp_variable_dtor,
.copy_ctor_=yaoocpp_variable_copy_ctor,
.assign_=yaoocpp_variable_assign,
.class_table_=(const class_table_t*) &yaoocpp_variable_class_table,
.parent_=&__yaoocpp_member_item_ti
};
const type_info_t* const yaoocpp_variable_ti=&__yaoocpp_variable_ti;
static void yaoocpp_method_print_prototype(const_pointer,ostream_pointer,const char*,const char*,const char*);
static void yaoocpp_method_print_implementation(const_pointer,ostream_pointer,const char*,const char*,const char*,bool);
static void yaoocpp_method_print_prototype(const_pointer __pthis__,ostream_pointer __postrm,const char* class_name,const char* parent_class_name,const char* storage_class)
{
yaoocpp_method_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      if(this->form_==IMPLEMENTATION_TEXT || (this->form_ == IMPLEMENTED_AS && strcmp(M(&this->implementation_,c_str),"0") == 0)) {
        M(ostrm,printf,"%s %s %s_%s(%spointer",storage_class,M(&this->type_,c_str),class_name,M(&this->name_,c_str),
              (this->is_const_ ? "const_" : "" ));
        yaoocpp_method_print_args_type(this,ostrm);
        M(ostrm,printf,");\n");
      } else if(this->form_==IMPLEMENTED_AS) {
        M(ostrm,printf,"#define %s_%s %s\n",class_name,M(&this->name_,c_str),M(&this->implementation_,c_str));
      }
    
}
static void yaoocpp_method_print_implementation(const_pointer __pthis__,ostream_pointer __postrm,const char* class_name,const char* parent,const char* storage_class,bool is_table_method)
{
yaoocpp_method_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      gb_init();
      bool pure_virtual=false;
      if(is_table_method && this->form_ == IMPLEMENTED_AS && strcmp(M(&this->implementation_,c_str),"0") == 0) {

        pure_virtual=true;
        is_table_method=false;
      }
      if(pure_virtual || this->form_ == IMPLEMENTATION_TEXT) {
        yaooc_string_t super_definition;
        yaooc_string_t pm_definition;
        yaooc_string_t stream_args;
        gb_newp(&stream_args,yaooc_string);
        gb_newp(&pm_definition,yaooc_string);
        gb_newp(&super_definition,yaooc_string);
        M(&super_definition,append,"#define super() ");
        M(&super_definition,append,class_name);
        M(&super_definition,append,"_parent_class_table->");
        M(&super_definition,append,M(&this->name_,c_str));
        M(&super_definition,append,"(this");

        M(&pm_definition,append,"#define PM(method,...) CTM((*");
        M(&pm_definition,append,class_name);
        M(&pm_definition,append,"_parent_class_table),this,method,## __VA_ARGS__)\n");

        M(ostrm,printf,"%s%s %s_%s(%spointer __pthis__",storage_class,M(&this->type_,c_str),
                class_name,M(&this->name_,c_str),(this->is_const_ ? "const_" : ""));
        yaoocpp_item_pointer_vector_const_iterator i;
        bool has_va_arg=false;
        const char* va_arg_name=NULL;
        const char* prev_arg="__pthis__";
        CFOR_EACH(i,&this->arguments_) {
          yaoocpp_argument_const_pointer iarg = i->ptr_;
          if(strcmp(M(&iarg->type_,c_str),"...") == 0) {
            has_va_arg=true;
            M(ostrm,printf,",...");
            va_arg_name=M(&iarg->name_,c_str);
          } else {
            const char* arg_name;
            char* temp_arg_name;
            if(strcmp(M(&iarg->type_,c_str),"ostream_pointer") == 0 || strcmp(M(&iarg->type_,c_str),"istream_pointer") == 0) {
              temp_arg_name=gb_new_array(char,M(&iarg->name_,size)+4);
              strcpy(temp_arg_name,"__p");
              strcat(temp_arg_name,M(&iarg->name_,c_str));
              if(strcmp(M(&iarg->type_,c_str),"ostream_pointer")==0)
                M(&stream_args,append,"yaooc_ostream_pointer ");
              else
                M(&stream_args,append,"yaooc_istream_pointer ");
              M(&stream_args,append,M(&iarg->name_,c_str));
              M(&stream_args,append,"=");
              M(&stream_args,append,temp_arg_name);
              M(&stream_args,append,";(void)");
              M(&stream_args,append,M(&iarg->name_,c_str));
              M(&stream_args,append,";\n");
              arg_name=temp_arg_name;
            } else {
              arg_name=M(&iarg->name_,c_str);
            }
            M(ostrm,printf,",%s %s",M(&iarg->type_,c_str),arg_name);
            prev_arg=M(&iarg->name_,c_str);
          }
          M(&super_definition,append,",");
          M(&super_definition,append,M(&iarg->name_,c_str));
        }
        M(&super_definition,append,")");
        M(ostrm,printf,")\n{\n");
        if(pure_virtual) {
          M(ostrm,printf,"yaooc_pure_virtual(\"%s\",\"%s\");exit(0);",M(&this->name_,c_str),class_name);
        } else {
          M(ostrm,printf,"%s_%spointer this=__pthis__;(void)this;\n",class_name,(this->is_const_ ? "const_" : ""));
          if(has_va_arg)
            M(ostrm,printf,"va_list %s; va_start(%s,%s);\n",va_arg_name,va_arg_name,prev_arg);
          if(is_table_method)
            M(ostrm,printf,"%s\n%s\n",M(&super_definition,c_str),M(&pm_definition,c_str));
          if(M(&stream_args,size)>0)
            M(ostrm,printf,"%s\n",M(&stream_args,c_str));
          M(ostrm,printf,"%s\n",M(&this->implementation_,c_str));
          if(is_table_method)
            M(ostrm,printf,"#undef PM\n#undef super\n");
        }
        M(ostrm,printf,"}\n");
      }
      gb_exit();
    
}
void yaoocpp_method_print_args_type(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_method_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_item_pointer_vector_const_iterator i;
      CFOR_EACH(i,&this->arguments_) {
        yaoocpp_argument_const_pointer iarg=i->ptr_;
        M(ostrm,printf,",%s",M(&iarg->type_,c_str));
      }
    
}
void yaoocpp_method_print_args_type_name(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_method_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_item_pointer_vector_const_iterator i;
      CFOR_EACH(i,&this->arguments_) {
        yaoocpp_argument_const_pointer iarg=i->ptr_;
        M(ostrm,printf,",%s %s",M(&iarg->type_,c_str),M(&iarg->name_,c_str));
      }
    
}
void yaoocpp_method_print_table_definition(const_pointer __pthis__,ostream_pointer __postrm,const char* class_name,const char* parent_name)
{
yaoocpp_method_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_method_parent_class_table->print_table_definition(this,ostrm,class_name,parent_name)
#define PM(method,...) CTM((*yaoocpp_method_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      M(ostrm,printf,"%s (*%s)(%spointer",M(&this->type_,c_str),M(&this->name_,c_str),
            (this->is_const_ ? "const_" : "" ));
      yaoocpp_method_print_args_type(this,ostrm);
      M(ostrm,printf,");\n");
    
#undef PM
#undef super
}
void yaoocpp_method_print_table_implementation(const_pointer __pthis__,ostream_pointer __postrm,const char* class_name,const char* parent)
{
yaoocpp_method_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_method_parent_class_table->print_table_implementation(this,ostrm,class_name,parent)
#define PM(method,...) CTM((*yaoocpp_method_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_method_print_implementation(this,ostrm,class_name,parent,"",true);
    
#undef PM
#undef super
}
void yaoocpp_method_print_adjunct_prototype(const_pointer __pthis__,ostream_pointer __postrm,const char* class_name,const char* parent)
{
yaoocpp_method_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_method_parent_class_table->print_adjunct_prototype(this,ostrm,class_name,parent)
#define PM(method,...) CTM((*yaoocpp_method_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_method_print_prototype(this,ostrm,class_name,parent,"");
    
#undef PM
#undef super
}
void yaoocpp_method_print_adjunct_implementation(const_pointer __pthis__,ostream_pointer __postrm,const char* class_name,const char* parent)
{
yaoocpp_method_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_method_parent_class_table->print_adjunct_implementation(this,ostrm,class_name,parent)
#define PM(method,...) CTM((*yaoocpp_method_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_method_print_implementation(this,ostrm,class_name,parent,"",false);
    
#undef PM
#undef super
}
void yaoocpp_method_print_private_prototype(const_pointer __pthis__,ostream_pointer __postrm,const char* class_name,const char* parent)
{
yaoocpp_method_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_method_parent_class_table->print_private_prototype(this,ostrm,class_name,parent)
#define PM(method,...) CTM((*yaoocpp_method_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_method_print_prototype(this,ostrm,class_name,parent,"static");
    
#undef PM
#undef super
}
void yaoocpp_method_print_private_implementation(const_pointer __pthis__,ostream_pointer __postrm,const char* class_name,const char* parent)
{
yaoocpp_method_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_method_parent_class_table->print_private_implementation(this,ostrm,class_name,parent)
#define PM(method,...) CTM((*yaoocpp_method_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_method_print_implementation(this,ostrm,class_name,parent,"static ",true);
    
#undef PM
#undef super
}
void yaoocpp_method_print_class_table_entry(const_pointer __pthis__,ostream_pointer __postrm,const char* class_name,const char* parent)
{
yaoocpp_method_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_method_parent_class_table->print_class_table_entry(this,ostrm,class_name,parent)
#define PM(method,...) CTM((*yaoocpp_method_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      M(ostrm,printf,".%s = (%s(*)(%spointer",M(&this->name_,c_str),M(&this->type_,c_str),
            (this->is_const_ ? "const_" : ""));
      yaoocpp_method_print_args_type(this,ostrm);
      M(ostrm,printf,")) %s_%s,\n",class_name,M(&this->name_,c_str));
    
#undef PM
#undef super
}
void yaoocpp_method_print_yod_definition(const_pointer __pthis__,ostream_pointer __postrm,bool include_implementation)
{
yaoocpp_method_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_method_parent_class_table->print_yod_definition(this,ostrm,include_implementation)
#define PM(method,...) CTM((*yaoocpp_method_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      if(this->form_==IMPLEMENTATION_TEXT || this->form_==IMPLEMENTED_AS) {
        M(ostrm,printf,"%s %s(",M(&this->type_,c_str),M(&this->name_,c_str));
        yaoocpp_item_pointer_vector_const_iterator i=M(&this->arguments_,cbegin);
        if(i != M(&this->arguments_,cend)) {
          const yaoocpp_argument_t* iarg=i->ptr_;
          M(ostrm,printf,"%s %s",M(&iarg->type_,c_str),M(&iarg->name_,c_str));
          for(i++;i!=M(&this->arguments_,cend);i++) {
            iarg=i->ptr_;
            M(ostrm,printf,",%s %s",M(&iarg->type_,c_str),M(&iarg->name_,c_str));
          }
        }
        M(ostrm,printf,") %s",(this->is_const_ ? "const" : "" ));
        if(this->form_==IMPLEMENTATION_TEXT) {
          if(include_implementation)
            M(ostrm,printf,"{\n%s}\n",M(&this->implementation_,c_str));
          else
            M(ostrm,printf,"{ }\n");
        } else {
          M(ostrm,printf,"=%s;\n",M(&this->implementation_,c_str));
        }
      }
    
#undef PM
#undef super
}
size_t yaoocpp_method_argument_count(const_pointer __pthis__)
{
yaoocpp_method_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_method_parent_class_table->argument_count(this)
#define PM(method,...) CTM((*yaoocpp_method_parent_class_table),this,method,## __VA_ARGS__)


      return M(&this->arguments_,size);
    
#undef PM
#undef super
}
void yaoocpp_method_set_implementation(pointer __pthis__,const char* str,size_t len)
{
yaoocpp_method_pointer this=__pthis__;(void)this;
#define super() yaoocpp_method_parent_class_table->set_implementation(this,str,len)
#define PM(method,...) CTM((*yaoocpp_method_parent_class_table),this,method,## __VA_ARGS__)


    M(&this->implementation_,setn,str,len);
    this->form_=IMPLEMENTATION_TEXT;
  
#undef PM
#undef super
}
void yaoocpp_method_set_implemented_as(pointer __pthis__,const char* str,size_t len)
{
yaoocpp_method_pointer this=__pthis__;(void)this;
#define super() yaoocpp_method_parent_class_table->set_implemented_as(this,str,len)
#define PM(method,...) CTM((*yaoocpp_method_parent_class_table),this,method,## __VA_ARGS__)


    M(&this->implementation_,setn,str,len);
    this->form_=IMPLEMENTED_AS;
  
#undef PM
#undef super
}
bool yaoocpp_method_is_implemented(const_pointer __pthis__)
{
yaoocpp_method_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_method_parent_class_table->is_implemented(this)
#define PM(method,...) CTM((*yaoocpp_method_parent_class_table),this,method,## __VA_ARGS__)


    return this->form_ == IMPLEMENTED_AS || this->form_ == IMPLEMENTATION_TEXT;
  
#undef PM
#undef super
}
yaoocpp_method_class_table_t yaoocpp_method_class_table ={
.parent_class_table_ = (const class_table_t*) &yaoocpp_member_item_class_table,
.type_name_ = (const char*) "yaoocpp_method_t",
.swap = (void(*)(pointer,pointer)) yaoocpp_method_swap,
.set_line_no = (void(*)(pointer,int)) yaoocpp_method_set_line_no,
.print_instance_prototype = (void(*)(const_pointer,ostream_pointer,const char*,const char*)) yaoocpp_method_print_instance_prototype,
.print_table_definition = (void(*)(const_pointer,ostream_pointer,const char*,const char*)) yaoocpp_method_print_table_definition,
.print_table_implementation = (void(*)(const_pointer,ostream_pointer,const char*,const char*)) yaoocpp_method_print_table_implementation,
.print_adjunct_prototype = (void(*)(const_pointer,ostream_pointer,const char*,const char*)) yaoocpp_method_print_adjunct_prototype,
.print_adjunct_implementation = (void(*)(const_pointer,ostream_pointer,const char*,const char*)) yaoocpp_method_print_adjunct_implementation,
.print_private_prototype = (void(*)(const_pointer,ostream_pointer,const char*,const char*)) yaoocpp_method_print_private_prototype,
.print_private_implementation = (void(*)(const_pointer,ostream_pointer,const char*,const char*)) yaoocpp_method_print_private_implementation,
.print_class_table_entry = (void(*)(const_pointer,ostream_pointer,const char*,const char*)) yaoocpp_method_print_class_table_entry,
.print_yod_definition = (void(*)(const_pointer,ostream_pointer,bool)) yaoocpp_method_print_yod_definition,
.argument_count = (size_t(*)(const_pointer)) yaoocpp_method_argument_count,
.set_implementation = (void(*)(pointer,const char*,size_t)) yaoocpp_method_set_implementation,
.set_implemented_as = (void(*)(pointer,const char*,size_t)) yaoocpp_method_set_implemented_as,
.is_implemented = (bool(*)(const_pointer)) yaoocpp_method_is_implemented,
};
void yaoocpp_method_default_ctor(pointer __pthis__)
{
yaoocpp_method_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaoocpp_method);
this->is_const_=false;



    newp(&this->arguments_,yaoocpp_item_pointer_vector);
  

    newp(&this->implementation_,yaooc_string);
    this->form_=DEFAULT;
  
 
}
void yaoocpp_method_dtor(pointer __pthis__)
{
yaoocpp_method_pointer this=__pthis__;(void)this;


    deletep(&this->arguments_,yaoocpp_item_pointer_vector);
  

    deletep(&this->implementation_,yaooc_string);
  

}
void yaoocpp_method_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaoocpp_method_pointer this=__pthis__;(void)this;
yaoocpp_method_const_pointer src=__psrc__;(void)src;



call_default_ctor_static(this,yaoocpp_method);
assign_static(this,src,yaoocpp_method);


}
void yaoocpp_method_assign(pointer __pthis__,const_pointer __psrc__)
{
yaoocpp_method_pointer this=__pthis__;(void)this;
yaoocpp_method_const_pointer src=__psrc__;(void)src;


    assign_static(&this->arguments_,&src->arguments_,yaoocpp_item_pointer_vector);
  

    assign_static(&this->implementation_,&src->implementation_,yaooc_string);
    this->form_=src->form_;
  
assign_static(this,src,yaoocpp_member_item);
this->is_const_=src->is_const_;

}
const type_info_t __yaoocpp_method_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaoocpp_method_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaoocpp_method_default_ctor,
.dtor_=yaoocpp_method_dtor,
.copy_ctor_=yaoocpp_method_copy_ctor,
.assign_=yaoocpp_method_assign,
.class_table_=(const class_table_t*) &yaoocpp_method_class_table,
.parent_=&__yaoocpp_member_item_ti
};
const type_info_t* const yaoocpp_method_ti=&__yaoocpp_method_ti;
void yaoocpp_constructor_initializer_ctor_id_value(pointer __pthis__,va_list __con_args__)
{
yaoocpp_constructor_initializer_pointer this=__pthis__;
const char* id_text = va_arg(__con_args__,const char*);
const char* value_text = va_arg(__con_args__,const char*);

call_default_ctor_static(this,yaoocpp_constructor_initializer);


    M(&this->name_,set,id_text);
    M(&this->value_,set,value_text);
    M(&this->value_,trim_);
  
}
yaoocpp_constructor_initializer_class_table_t yaoocpp_constructor_initializer_class_table ={
.parent_class_table_ = (const class_table_t*) &yaoocpp_item_class_table,
.type_name_ = (const char*) "yaoocpp_constructor_initializer_t",
.swap = (void(*)(pointer,pointer)) yaoocpp_constructor_initializer_swap,
.set_line_no = (void(*)(pointer,int)) yaoocpp_constructor_initializer_set_line_no,
};
void yaoocpp_constructor_initializer_default_ctor(pointer __pthis__)
{
yaoocpp_constructor_initializer_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaoocpp_constructor_initializer);


newp(&this->value_,yaooc_string);

}
void yaoocpp_constructor_initializer_dtor(pointer __pthis__)
{
yaoocpp_constructor_initializer_pointer this=__pthis__;(void)this;

deletep(&this->value_,yaooc_string);

}
void yaoocpp_constructor_initializer_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaoocpp_constructor_initializer_pointer this=__pthis__;(void)this;
yaoocpp_constructor_initializer_const_pointer src=__psrc__;(void)src;

call_default_ctor_static(this,yaoocpp_constructor_initializer);
assign_static(this,src,yaoocpp_constructor_initializer);


}
void yaoocpp_constructor_initializer_assign(pointer __pthis__,const_pointer __psrc__)
{
yaoocpp_constructor_initializer_pointer this=__pthis__;(void)this;
yaoocpp_constructor_initializer_const_pointer src=__psrc__;(void)src;

assign_static(this,src,yaoocpp_item);
assign_static(&this->value_,&src->value_,yaooc_string);

}
const type_info_t __yaoocpp_constructor_initializer_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaoocpp_constructor_initializer_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaoocpp_constructor_initializer_default_ctor,
.dtor_=yaoocpp_constructor_initializer_dtor,
.copy_ctor_=yaoocpp_constructor_initializer_copy_ctor,
.assign_=yaoocpp_constructor_initializer_assign,
.class_table_=(const class_table_t*) &yaoocpp_constructor_initializer_class_table,
.parent_=&__yaoocpp_item_ti
};
const type_info_t* const yaoocpp_constructor_initializer_ti=&__yaoocpp_constructor_initializer_ti;
void yaoocpp_type_info_print_entry(const_pointer __pthis__,ostream_pointer __postrm,const char* type_info_name)
{
yaoocpp_type_info_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      M(ostrm,printf,".%s_=",type_info_name);
      if(this->form_==IMPLEMENTATION_TEXT)
        M(ostrm,printf,"%s_%s,\n",M(&this->name_,c_str),type_info_name);
      else if(this->form_==IMPLEMENTED_AS)
        M(ostrm,printf,"%s,\n",M(&this->implementation_,c_str));
      else
        M(ostrm,printf,"NULL,\n");
    
}
void yaoocpp_type_info_print_prototype(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_type_info_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_type_info_parent_class_table->print_prototype(this,ostrm)
#define PM(method,...) CTM((*yaoocpp_type_info_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


    
#undef PM
#undef super
}
void yaoocpp_type_info_set_implementation(pointer __pthis__,const char* str,size_t len)
{
yaoocpp_type_info_pointer this=__pthis__;(void)this;
#define super() yaoocpp_type_info_parent_class_table->set_implementation(this,str,len)
#define PM(method,...) CTM((*yaoocpp_type_info_parent_class_table),this,method,## __VA_ARGS__)


    M(&this->implementation_,setn,str,len);
    this->form_=IMPLEMENTATION_TEXT;
  
#undef PM
#undef super
}
void yaoocpp_type_info_set_implemented_as(pointer __pthis__,const char* str,size_t len)
{
yaoocpp_type_info_pointer this=__pthis__;(void)this;
#define super() yaoocpp_type_info_parent_class_table->set_implemented_as(this,str,len)
#define PM(method,...) CTM((*yaoocpp_type_info_parent_class_table),this,method,## __VA_ARGS__)


    M(&this->implementation_,setn,str,len);
    this->form_=IMPLEMENTED_AS;
  
#undef PM
#undef super
}
bool yaoocpp_type_info_is_implemented(const_pointer __pthis__)
{
yaoocpp_type_info_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_type_info_parent_class_table->is_implemented(this)
#define PM(method,...) CTM((*yaoocpp_type_info_parent_class_table),this,method,## __VA_ARGS__)


    return this->form_ == IMPLEMENTED_AS || this->form_ == IMPLEMENTATION_TEXT;
  
#undef PM
#undef super
}
yaoocpp_type_info_class_table_t yaoocpp_type_info_class_table ={
.parent_class_table_ = (const class_table_t*) &yaoocpp_item_class_table,
.type_name_ = (const char*) "yaoocpp_type_info_t",
.swap = (void(*)(pointer,pointer)) yaoocpp_type_info_swap,
.set_line_no = (void(*)(pointer,int)) yaoocpp_type_info_set_line_no,
.print_prototype = (void(*)(const_pointer,ostream_pointer)) yaoocpp_type_info_print_prototype,
.set_implementation = (void(*)(pointer,const char*,size_t)) yaoocpp_type_info_set_implementation,
.set_implemented_as = (void(*)(pointer,const char*,size_t)) yaoocpp_type_info_set_implemented_as,
.is_implemented = (bool(*)(const_pointer)) yaoocpp_type_info_is_implemented,
};
void yaoocpp_type_info_default_ctor(pointer __pthis__)
{
yaoocpp_type_info_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaoocpp_type_info);



    newp(&this->implementation_,yaooc_string);
    this->form_=DEFAULT;
  
newp(&this->mixin_text_,yaooc_string);

}
void yaoocpp_type_info_dtor(pointer __pthis__)
{
yaoocpp_type_info_pointer this=__pthis__;(void)this;


    deletep(&this->implementation_,yaooc_string);
  
deletep(&this->mixin_text_,yaooc_string);

}
void yaoocpp_type_info_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaoocpp_type_info_pointer this=__pthis__;(void)this;
yaoocpp_type_info_const_pointer src=__psrc__;(void)src;


call_default_ctor_static(this,yaoocpp_type_info);
assign_static(this,src,yaoocpp_type_info);


}
void yaoocpp_type_info_assign(pointer __pthis__,const_pointer __psrc__)
{
yaoocpp_type_info_pointer this=__pthis__;(void)this;
yaoocpp_type_info_const_pointer src=__psrc__;(void)src;


    assign_static(&this->implementation_,&src->implementation_,yaooc_string);
    this->form_=src->form_;
  
assign_static(this,src,yaoocpp_item);
assign_static(&this->mixin_text_,&src->mixin_text_,yaooc_string);

}
const type_info_t __yaoocpp_type_info_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaoocpp_type_info_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaoocpp_type_info_default_ctor,
.dtor_=yaoocpp_type_info_dtor,
.copy_ctor_=yaoocpp_type_info_copy_ctor,
.assign_=yaoocpp_type_info_assign,
.class_table_=(const class_table_t*) &yaoocpp_type_info_class_table,
.parent_=&__yaoocpp_item_ti
};
const type_info_t* const yaoocpp_type_info_ti=&__yaoocpp_type_info_ti;
void yaoocpp_constructor_base_gen_initializers_text(pointer __pthis__,const char* class_name,const char* parent_class_name,yaoocpp_item_pointer_vector_const_pointer new_items,bool is_default_ctor)
{
yaoocpp_constructor_base_pointer this=__pthis__;(void)this;

      char* buffer = new_array(char,1024);




      if(M(&this->initializers_,size)>0) {


        yaoocpp_item_pointer_vector_const_iterator i=M(&this->initializers_,cbegin);
        const yaoocpp_constructor_initializer_t* init=i->ptr_;

        if((strcmp(M(&init->name_,c_str),class_name) == 0 ||
            ( parent_class_name && strcmp(M(&init->name_,c_str),parent_class_name)) == 0) && M(&init->value_,size)>0) {
          M(cerr,printf,"Can not specify copy constructor as initializer for class \"%s\"\n",class_name);
          exit(44);
        }
        if(is_default_ctor) {


          if(strcmp(M(&init->name_,c_str),class_name) == 0 && M(&init->value_,size)==0) {
            M(cerr,printf,"Can not specify default constructor \"%s\" for class \"%s\"\n",class_name,class_name);
            exit(33);
          }
          if(parent_class_name) {
            if(strcmp(parent_class_name,M(&init->name_,c_str))==0) {
              sprintf(buffer,"call_parent_default_ctor_static(this,%s);\n",class_name);
              i++;
            } else if(strncmp(parent_class_name,M(&init->name_,c_str),strlen(parent_class_name))==0) {
              sprintf(buffer,"call_constructor(this,%s,%s);\n",M(&init->name_,c_str),M(&init->value_,c_str));
              i++;
            } else {

              sprintf(buffer,"call_parent_default_ctor_static(this,%s);\n",class_name);
            }
          }
        } else {

          if(strcmp(class_name,M(&init->name_,c_str))==0) {
            sprintf(buffer,"call_default_ctor_static(this,%s);\n",class_name);
            i++;
          } else if(strncmp(class_name,M(&init->name_,c_str),strlen(class_name))==0) {
              sprintf(buffer,"call_constructor(this,%s,%s);\n",M(&init->name_,c_str),M(&init->value_,c_str));
              i++;
          } else if(parent_class_name) {
            if(strcmp(parent_class_name,M(&init->name_,c_str))==0) {
              sprintf(buffer,"call_parent_default_ctor_static(this,%s);\n",class_name);
              i++;
            } else if(strncmp(parent_class_name,M(&init->name_,c_str),strlen(parent_class_name))==0) {
              sprintf(buffer,"call_constructor(this,%s,%s);\n",M(&init->name_,c_str),M(&init->value_,c_str));
              i++;
            } else {
              sprintf(buffer,"call_parent_default_ctor_static(this,%s);\n",class_name);
            }
          } else {
            sprintf(buffer,"call_default_ctor_static(this,%s);\n",class_name);
          }
        }
        M(&this->initializer_text_,append,buffer);

        yaoocpp_item_t* temp=new(yaoocpp_item);
        for(;i!=M(&this->initializers_,cend);i++) {
          init=i->ptr_;

          assign_static(&temp->name_,&init->name_,yaooc_string);
          if(yaooc_find(yaooc_dynamic_pointer,M(new_items,cbegin),M(new_items,cend),make_dynamic_pointer(temp)) == M(new_items,cend)) {

            printf("Initializer specified '%s' is not a new instance member.\n",M(&init->name_,c_str));
            exit(27);
          }
          sprintf(buffer,"this->%s=%s;\n",M(&init->name_,c_str),M(&init->value_,c_str));
          M(&this->initializer_text_,append,buffer);
        }
        delete(temp);
      } else {



        if(is_default_ctor)
          snprintf(buffer,1023,"call_parent_default_ctor_static(this,%s);\n",class_name);
        else
          snprintf(buffer,1023,"call_default_ctor_static(this,%s);\n",class_name);
        M(&this->initializer_text_,append,buffer);
      }
      delete(buffer);
    
}
void yaoocpp_constructor_base_print_prototype(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_constructor_base_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_constructor_base_parent_class_table->print_prototype(this,ostrm)
#define PM(method,...) CTM((*yaoocpp_constructor_base_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      if(this->form_==IMPLEMENTED_AS) {
        M(ostrm,printf,"#define %s_default_ctor %s\n",M(&this->name_,c_str),M(&this->implementation_,c_str));
      } else if(this->form_==IMPLEMENTATION_TEXT) {
        M(ostrm,printf,"void %s_default_ctor(pointer);\n",M(&this->name_,c_str));
      }
    
#undef PM
#undef super
}
yaoocpp_constructor_base_class_table_t yaoocpp_constructor_base_class_table ={
.parent_class_table_ = (const class_table_t*) &yaoocpp_type_info_class_table,
.type_name_ = (const char*) "yaoocpp_constructor_base_t",
.swap = (void(*)(pointer,pointer)) yaoocpp_constructor_base_swap,
.set_line_no = (void(*)(pointer,int)) yaoocpp_constructor_base_set_line_no,
.print_prototype = (void(*)(const_pointer,ostream_pointer)) yaoocpp_constructor_base_print_prototype,
.set_implementation = (void(*)(pointer,const char*,size_t)) yaoocpp_constructor_base_set_implementation,
.set_implemented_as = (void(*)(pointer,const char*,size_t)) yaoocpp_constructor_base_set_implemented_as,
.is_implemented = (bool(*)(const_pointer)) yaoocpp_constructor_base_is_implemented,
};
void yaoocpp_constructor_base_default_ctor(pointer __pthis__)
{
yaoocpp_constructor_base_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaoocpp_constructor_base);


newp(&this->initializers_,yaoocpp_item_pointer_vector);
newp(&this->initializer_text_,yaooc_string);

}
void yaoocpp_constructor_base_dtor(pointer __pthis__)
{
yaoocpp_constructor_base_pointer this=__pthis__;(void)this;

deletep(&this->initializers_,yaoocpp_item_pointer_vector);
deletep(&this->initializer_text_,yaooc_string);

}
void yaoocpp_constructor_base_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaoocpp_constructor_base_pointer this=__pthis__;(void)this;
yaoocpp_constructor_base_const_pointer src=__psrc__;(void)src;

call_default_ctor_static(this,yaoocpp_constructor_base);
assign_static(this,src,yaoocpp_constructor_base);


}
void yaoocpp_constructor_base_assign(pointer __pthis__,const_pointer __psrc__)
{
yaoocpp_constructor_base_pointer this=__pthis__;(void)this;
yaoocpp_constructor_base_const_pointer src=__psrc__;(void)src;

assign_static(this,src,yaoocpp_type_info);
assign_static(&this->initializers_,&src->initializers_,yaoocpp_item_pointer_vector);
assign_static(&this->initializer_text_,&src->initializer_text_,yaooc_string);

}
const type_info_t __yaoocpp_constructor_base_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaoocpp_constructor_base_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaoocpp_constructor_base_default_ctor,
.dtor_=yaoocpp_constructor_base_dtor,
.copy_ctor_=yaoocpp_constructor_base_copy_ctor,
.assign_=yaoocpp_constructor_base_assign,
.class_table_=(const class_table_t*) &yaoocpp_constructor_base_class_table,
.parent_=&__yaoocpp_type_info_ti
};
const type_info_t* const yaoocpp_constructor_base_ti=&__yaoocpp_constructor_base_ti;
void yaoocpp_default_constructor_resolve(pointer __pthis__,const char* class_name,const char* parent_class_name,yaoocpp_item_pointer_vector_const_pointer new_items)
{
yaoocpp_default_constructor_pointer this=__pthis__;(void)this;

      if(this->form_==DEFAULT) {

        if(M(new_items,size)>0)
          yaoocpp_default_constructor_create(this,class_name,parent_class_name,new_items);
      } else if(this->form_==IMPLEMENTATION_TEXT)
        yaoocpp_constructor_base_gen_initializers_text(this,class_name,parent_class_name,new_items,true);
    
}
void yaoocpp_default_constructor_create(pointer __pthis__,const char* class_name,const char* parent_class_name,yaoocpp_item_pointer_vector_const_pointer new_items)
{
yaoocpp_default_constructor_pointer this=__pthis__;(void)this;

      char *buffer = new_array(char,1024);
      M(&this->name_,set,class_name);
      this->form_=IMPLEMENTATION_TEXT;

      if(parent_class_name != NULL) {
        sprintf(buffer,"call_parent_default_ctor_static(this,%s);\n",class_name);
        M(&this->initializer_text_,append,buffer);
      }
      if(new_items) {
        yaoocpp_item_pointer_vector_const_iterator i;
        CFOR_EACH(i,new_items) {
          yaoocpp_variable_const_pointer var=i->ptr_;
          if(M(&var->type_,ends_with,"*")) {
            sprintf(buffer,"this->%s=NULL;\n",M(&var->name_,c_str));
          } else if(M(&var->type_,ends_with,"_t")) {
            sprintf(buffer,"newp(&this->%s,%.*s);\n",M(&var->name_,c_str),(int)(M(&var->type_,size)-2),M(&var->type_,c_str));
          } else {
            sprintf(buffer,"this->%s=(%s)0;\n",M(&var->name_,c_str),M(&var->type_,c_str));
          }
          M(&this->implementation_,append,buffer);
        }
      }
      delete(buffer);
    
}
void yaoocpp_default_constructor_add_mixin_text(pointer __pthis__,yaoocpp_mixin_const_pointer mixin,const char* class_name,const char* parent_class_name)
{
yaoocpp_default_constructor_pointer this=__pthis__;(void)this;

      if(mixin->default_ctor_.form_ == IMPLEMENTATION_TEXT) {
        if(this->form_ == DEFAULT)
          yaoocpp_default_constructor_create(this,class_name,parent_class_name,NULL);
        if(this->form_==IMPLEMENTATION_TEXT) {
          M(&this->mixin_text_,append,"\n");
          M(&this->mixin_text_,append,M(&mixin->default_ctor_.implementation_,c_str));
          M(&this->mixin_text_,gsub_,"@CLASS@",class_name);
        }
      }
    
}
void yaoocpp_default_constructor_print_implementation(const_pointer __pthis__,ostream_pointer __postrm,const char* namespace)
{
yaoocpp_default_constructor_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      if(this->form_==IMPLEMENTATION_TEXT) {
        M(ostrm,printf,"void %s_default_ctor(pointer __pthis__)\n"
        "{\n%s_pointer this=__pthis__;(void)this;\n"
        "%s\n"
        "%s\n"
        "%s\n"
        "}\n",M(&this->name_,c_str),M(&this->name_,c_str),M(&this->initializer_text_,c_str),
              M(&this->mixin_text_,c_str),M(&this->implementation_,c_str));
      }
    
}
void yaoocpp_default_constructor_print_type_info_entry(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_default_constructor_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_type_info_print_entry(this,ostrm,"default_ctor");
    
}
void yaoocpp_default_constructor_print_yod_definition(const_pointer __pthis__,ostream_pointer __postrm,bool include_implementation)
{
yaoocpp_default_constructor_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      if(this->form_==IMPLEMENTATION_TEXT) {
        M(ostrm,printf,"%s(){",M(&this->name_,c_str));
        if(include_implementation)
          M(ostrm,printf,"\n%s",M(&this->implementation_,c_str));
        M(ostrm,printf,"}\n");
      } else if(this->form_==IMPLEMENTED_AS) {
        M(ostrm,printf,"%s() = %s;\n",M(&this->name_,c_str),M(&this->implementation_,c_str));
      } else if(this->form_==DELETE) {
        M(ostrm,printf,"%s() = delete;\n",M(&this->name_,c_str));
      }
    
}
yaoocpp_default_constructor_class_table_t yaoocpp_default_constructor_class_table ={
.parent_class_table_ = (const class_table_t*) &yaoocpp_constructor_base_class_table,
.type_name_ = (const char*) "yaoocpp_default_constructor_t",
.swap = (void(*)(pointer,pointer)) yaoocpp_default_constructor_swap,
.set_line_no = (void(*)(pointer,int)) yaoocpp_default_constructor_set_line_no,
.print_prototype = (void(*)(const_pointer,ostream_pointer)) yaoocpp_default_constructor_print_prototype,
.set_implementation = (void(*)(pointer,const char*,size_t)) yaoocpp_default_constructor_set_implementation,
.set_implemented_as = (void(*)(pointer,const char*,size_t)) yaoocpp_default_constructor_set_implemented_as,
.is_implemented = (bool(*)(const_pointer)) yaoocpp_default_constructor_is_implemented,
};
const type_info_t __yaoocpp_default_constructor_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaoocpp_default_constructor_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=NULL,
.dtor_=NULL,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaoocpp_default_constructor_class_table,
.parent_=&__yaoocpp_constructor_base_ti
};
const type_info_t* const yaoocpp_default_constructor_ti=&__yaoocpp_default_constructor_ti;
void yaoocpp_destructor_resolve(pointer __pthis__,const char* class_name,const char* parent_class_name,yaoocpp_item_pointer_vector_const_pointer new_items)
{
yaoocpp_destructor_pointer this=__pthis__;(void)this;

      if(this->form_==DEFAULT) {

        if(M(new_items,size)>0)
          yaoocpp_destructor_create(this,class_name,parent_class_name,new_items);


      }
    
}
void yaoocpp_destructor_create(pointer __pthis__,const char* class_name,const char* parent_class_name,yaoocpp_item_pointer_vector_const_pointer new_items)
{
yaoocpp_destructor_pointer this=__pthis__;(void)this;

      char *buffer = new_array(char,1024);
      M(&this->name_,set,class_name);
      this->form_=IMPLEMENTATION_TEXT;
      if(new_items) {
        yaoocpp_item_pointer_vector_const_iterator i;
        CFOR_EACH(i,new_items) {
          yaoocpp_variable_const_pointer var=i->ptr_;
          *buffer=0;
          if(M(&var->type_,ends_with,"*") && !M(&var->type_,starts_with,"const")) {
            sprintf(buffer,"if(this->%s!=NULL) delete(this->%s);\n",M(&var->name_,c_str),M(&var->name_,c_str));
          } else if(M(&var->type_,ends_with,"_t")) {
            sprintf(buffer,"deletep(&this->%s,%.*s);\n",M(&var->name_,c_str),(int)(M(&var->type_,size)-2),M(&var->type_,c_str));
          }
          if(*buffer != 0)
            M(&this->implementation_,append,buffer);
        }
      }
      delete(buffer);
    
}
void yaoocpp_destructor_add_mixin_text(pointer __pthis__,yaoocpp_mixin_const_pointer mixin,const char* class_name,const char* parent_class_name)
{
yaoocpp_destructor_pointer this=__pthis__;(void)this;

      if(M(&mixin->dtor_.implementation_,size)>0) {
        if(this->form_ == DEFAULT)
          yaoocpp_destructor_create(this,class_name,parent_class_name,NULL);
        if(this->form_==IMPLEMENTATION_TEXT) {
          M(&this->mixin_text_,append,"\n");
          M(&this->mixin_text_,append,M(&mixin->dtor_.implementation_,c_str));
          M(&this->mixin_text_,gsub_,"@CLASS@",class_name);
        }
      }
    
}
void yaoocpp_destructor_print_implementation(const_pointer __pthis__,ostream_pointer __postrm,const char* namespace)
{
yaoocpp_destructor_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      if(this->form_==IMPLEMENTATION_TEXT) {
        M(ostrm,printf,"void %s_dtor(pointer __pthis__)\n"
        "{\n%s_pointer this=__pthis__;(void)this;\n"
        "%s\n"
        "%s\n"
        "}\n",M(&this->name_,c_str),M(&this->name_,c_str),
            M(&this->mixin_text_,c_str),M(&this->implementation_,c_str));
      }
    
}
void yaoocpp_destructor_print_type_info_entry(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_destructor_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_type_info_print_entry(this,ostrm,"dtor");
    
}
void yaoocpp_destructor_print_yod_definition(const_pointer __pthis__,ostream_pointer __postrm,bool include_implementation)
{
yaoocpp_destructor_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      if(this->form_==IMPLEMENTATION_TEXT) {
        M(ostrm,printf,"~%s(){\n"
        "%s\n"
        "}\n",M(&this->name_,c_str),(include_implementation ? M(&this->implementation_,c_str) : ""));
      } else if(this->form_==IMPLEMENTED_AS) {
        M(ostrm,printf,"~%s() = %s;\n",M(&this->name_,c_str),M(&this->implementation_,c_str));
      } else if(this->form_==DELETE) {
        M(ostrm,printf,"~%s() = delete;\n",M(&this->name_,c_str));
      }
    
}
void yaoocpp_destructor_print_prototype(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_destructor_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_destructor_parent_class_table->print_prototype(this,ostrm)
#define PM(method,...) CTM((*yaoocpp_destructor_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      if(this->form_==IMPLEMENTED_AS) {
        M(ostrm,printf,"#define %s_dtor %s\n",M(&this->name_,c_str),M(&this->implementation_,c_str));
      } else if(this->form_==IMPLEMENTATION_TEXT) {
        M(ostrm,printf,"void %s_dtor(pointer);\n",M(&this->name_,c_str));
      }
    
#undef PM
#undef super
}
yaoocpp_destructor_class_table_t yaoocpp_destructor_class_table ={
.parent_class_table_ = (const class_table_t*) &yaoocpp_type_info_class_table,
.type_name_ = (const char*) "yaoocpp_destructor_t",
.swap = (void(*)(pointer,pointer)) yaoocpp_destructor_swap,
.set_line_no = (void(*)(pointer,int)) yaoocpp_destructor_set_line_no,
.print_prototype = (void(*)(const_pointer,ostream_pointer)) yaoocpp_destructor_print_prototype,
.set_implementation = (void(*)(pointer,const char*,size_t)) yaoocpp_destructor_set_implementation,
.set_implemented_as = (void(*)(pointer,const char*,size_t)) yaoocpp_destructor_set_implemented_as,
.is_implemented = (bool(*)(const_pointer)) yaoocpp_destructor_is_implemented,
};
const type_info_t __yaoocpp_destructor_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaoocpp_destructor_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=NULL,
.dtor_=NULL,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaoocpp_destructor_class_table,
.parent_=&__yaoocpp_type_info_ti
};
const type_info_t* const yaoocpp_destructor_ti=&__yaoocpp_destructor_ti;
void yaoocpp_copy_constructor_resolve(pointer __pthis__,const char* class_name,const char* parent_class_name,yaoocpp_item_pointer_vector_const_pointer new_items)
{
yaoocpp_copy_constructor_pointer this=__pthis__;(void)this;

      if(this->form_==DEFAULT) {

        if(M(new_items,size)>0)
          yaoocpp_copy_constructor_create(this,class_name,parent_class_name,new_items);


      } else if(this->form_==IMPLEMENTATION_TEXT) {
        yaoocpp_constructor_base_gen_initializers_text(this,class_name,parent_class_name,new_items,false);
      }
    
}
void yaoocpp_copy_constructor_create(pointer __pthis__,const char* class_name,const char* parent_class_name,yaoocpp_item_pointer_vector_const_pointer new_items)
{
yaoocpp_copy_constructor_pointer this=__pthis__;(void)this;

      char *buffer = new_array(char,1024);
      M(&this->name_,set,class_name);
      M(&this->src_name_,set,"src");
      this->form_=IMPLEMENTATION_TEXT;
      sprintf(buffer,"call_default_ctor_static(this,%s);\n"
      "assign_static(this,src,%s);\n",class_name,class_name);
      M(&this->implementation_,set,buffer);
      delete(buffer);
    
}
void yaoocpp_copy_constructor_add_mixin_text(pointer __pthis__,yaoocpp_mixin_const_pointer mixin,const char* class_name,const char* parent_class_name)
{
yaoocpp_copy_constructor_pointer this=__pthis__;(void)this;







      if(this->form_ == DEFAULT)
        yaoocpp_copy_constructor_create(this,class_name,parent_class_name,NULL);

      if(M(&mixin->copy_ctor_.implementation_,size)>0 && this->form_==IMPLEMENTATION_TEXT) {
        M(&this->mixin_text_,append,"\n");
        M(&this->mixin_text_,append,M(&mixin->copy_ctor_.implementation_,c_str));
        M(&this->mixin_text_,gsub_,"@CLASS@",class_name);
      }
    
}
void yaoocpp_copy_constructor_print_implementation(const_pointer __pthis__,ostream_pointer __postrm,const char* namespace)
{
yaoocpp_copy_constructor_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      if(this->form_==IMPLEMENTATION_TEXT) {
        M(ostrm,printf,"void %s_copy_ctor(pointer __pthis__,const_pointer __psrc__)\n"
        "{\n%s_pointer this=__pthis__;(void)this;\n"
        "%s_const_pointer %s=__psrc__;(void)%s;\n"
        "%s\n"
        "%s\n"
        "%s\n"
        "}\n",M(&this->name_,c_str),M(&this->name_,c_str),M(&this->name_,c_str),M(&this->src_name_,c_str),
            M(&this->src_name_,c_str),M(&this->mixin_text_,c_str),M(&this->initializer_text_,c_str),
            M(&this->implementation_,c_str));
      }
    
}
void yaoocpp_copy_constructor_print_type_info_entry(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_copy_constructor_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_type_info_print_entry(this,ostrm,"copy_ctor");
    
}
void yaoocpp_copy_constructor_print_yod_definition(const_pointer __pthis__,ostream_pointer __postrm,bool include_implementation)
{
yaoocpp_copy_constructor_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      if(this->form_==IMPLEMENTATION_TEXT) {
            M(ostrm,printf,"%s(%s){\n"
            "%s\n"
            "}\n",M(&this->name_,c_str),M(&this->src_name_,c_str),
            (include_implementation ? M(&this->implementation_,c_str) : ""));
      } else if(this->form_==IMPLEMENTED_AS) {
        M(ostrm,printf,"%s(%s) = %s;\n",M(&this->name_,c_str),M(&this->src_name_,c_str),
              M(&this->implementation_,c_str));
      } else if(this->form_==DELETE) {
        M(ostrm,printf,"%s(%s) = delete;\n",M(&this->name_,c_str),M(&this->src_name_,c_str));
      }
    
}
void yaoocpp_copy_constructor_print_prototype(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_copy_constructor_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_copy_constructor_parent_class_table->print_prototype(this,ostrm)
#define PM(method,...) CTM((*yaoocpp_copy_constructor_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      if(this->form_==IMPLEMENTED_AS) {
        M(ostrm,printf,"#define %s_copy_ctor %s\n",M(&this->name_,c_str),M(&this->implementation_,c_str));
      } else if(this->form_==IMPLEMENTATION_TEXT) {
        M(ostrm,printf,"void %s_copy_ctor(pointer,const_pointer);\n",M(&this->name_,c_str));
      }
    
#undef PM
#undef super
}
void yaoocpp_copy_constructor_set_source_name(pointer __pthis__,const char* str,size_t len)
{
yaoocpp_copy_constructor_pointer this=__pthis__;(void)this;
#define super() yaoocpp_copy_constructor_parent_class_table->set_source_name(this,str,len)
#define PM(method,...) CTM((*yaoocpp_copy_constructor_parent_class_table),this,method,## __VA_ARGS__)


      M(&this->src_name_,setn,str,len);
    
#undef PM
#undef super
}
yaoocpp_copy_constructor_class_table_t yaoocpp_copy_constructor_class_table ={
.parent_class_table_ = (const class_table_t*) &yaoocpp_constructor_base_class_table,
.type_name_ = (const char*) "yaoocpp_copy_constructor_t",
.swap = (void(*)(pointer,pointer)) yaoocpp_copy_constructor_swap,
.set_line_no = (void(*)(pointer,int)) yaoocpp_copy_constructor_set_line_no,
.print_prototype = (void(*)(const_pointer,ostream_pointer)) yaoocpp_copy_constructor_print_prototype,
.set_implementation = (void(*)(pointer,const char*,size_t)) yaoocpp_copy_constructor_set_implementation,
.set_implemented_as = (void(*)(pointer,const char*,size_t)) yaoocpp_copy_constructor_set_implemented_as,
.is_implemented = (bool(*)(const_pointer)) yaoocpp_copy_constructor_is_implemented,
.set_source_name = (void(*)(pointer,const char*,size_t)) yaoocpp_copy_constructor_set_source_name,
};
void yaoocpp_copy_constructor_default_ctor(pointer __pthis__)
{
yaoocpp_copy_constructor_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaoocpp_copy_constructor);


newp(&this->src_name_,yaooc_string);

}
void yaoocpp_copy_constructor_dtor(pointer __pthis__)
{
yaoocpp_copy_constructor_pointer this=__pthis__;(void)this;

deletep(&this->src_name_,yaooc_string);

}
void yaoocpp_copy_constructor_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaoocpp_copy_constructor_pointer this=__pthis__;(void)this;
yaoocpp_copy_constructor_const_pointer src=__psrc__;(void)src;

call_default_ctor_static(this,yaoocpp_copy_constructor);
assign_static(this,src,yaoocpp_copy_constructor);


}
void yaoocpp_copy_constructor_assign(pointer __pthis__,const_pointer __psrc__)
{
yaoocpp_copy_constructor_pointer this=__pthis__;(void)this;
yaoocpp_copy_constructor_const_pointer src=__psrc__;(void)src;

assign_static(this,src,yaoocpp_constructor_base);
assign_static(&this->src_name_,&src->src_name_,yaooc_string);

}
const type_info_t __yaoocpp_copy_constructor_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaoocpp_copy_constructor_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaoocpp_copy_constructor_default_ctor,
.dtor_=yaoocpp_copy_constructor_dtor,
.copy_ctor_=yaoocpp_copy_constructor_copy_ctor,
.assign_=yaoocpp_copy_constructor_assign,
.class_table_=(const class_table_t*) &yaoocpp_copy_constructor_class_table,
.parent_=&__yaoocpp_constructor_base_ti
};
const type_info_t* const yaoocpp_copy_constructor_ti=&__yaoocpp_copy_constructor_ti;
void yaoocpp_assignment_resolve(pointer __pthis__,const char* class_name,const char* parent_class_name,yaoocpp_item_pointer_vector_const_pointer new_items)
{
yaoocpp_assignment_pointer this=__pthis__;(void)this;


      if(this->form_==DEFAULT) {

        if(M(new_items,size)>0)
          yaoocpp_assignment_create(this,class_name,parent_class_name,new_items);


      }
    
}
void yaoocpp_assignment_create(pointer __pthis__,const char* class_name,const char* parent_class_name,yaoocpp_item_pointer_vector_const_pointer new_items)
{
yaoocpp_assignment_pointer this=__pthis__;(void)this;

      char *buffer = new_array(char,1024);
      M(&this->name_,set,class_name);
      M(&this->src_name_,set,"src");
      this->form_=IMPLEMENTATION_TEXT;

      if(parent_class_name) {
        sprintf(buffer,"assign_static(this,src,%s);\n",parent_class_name);
        M(&this->implementation_,append,buffer);
      }
      if(new_items) {
        yaoocpp_item_pointer_vector_const_iterator i;
        CFOR_EACH(i,new_items) {
          yaoocpp_variable_const_pointer var=i->ptr_;
          if(M(&var->type_,starts_with,"const")) {
            sprintf(buffer,"this->%s=src->%s;\n",M(&var->name_,c_str),M(&var->name_,c_str));
          } else if(M(&var->type_,ends_with,"_t")) {
            sprintf(buffer,"assign_static(&this->%s,&src->%s,%.*s);\n",M(&var->name_,c_str),
                  M(&var->name_,c_str),(int)(M(&var->type_,size)-2),M(&var->type_,c_str));
          } else if(M(&var->type_,ends_with,"_t*")) {
            sprintf(buffer,"assign(this->%s,src->%s);\n",M(&var->name_,c_str),M(&var->name_,c_str));
          } else
            sprintf(buffer,"this->%s=src->%s;\n",M(&var->name_,c_str),M(&var->name_,c_str));
          M(&this->implementation_,append,buffer);
        }
      }
      delete(buffer);
    
}
void yaoocpp_assignment_add_mixin_text(pointer __pthis__,yaoocpp_mixin_const_pointer mixin,const char* class_name,const char* parent_class_name)
{
yaoocpp_assignment_pointer this=__pthis__;(void)this;

      if(M(&mixin->assign_.implementation_,size)>0) {
        if(this->form_ == DEFAULT)
          yaoocpp_assignment_create(this,class_name,parent_class_name,NULL);
        if(this->form_==IMPLEMENTATION_TEXT) {
          M(&this->mixin_text_,append,"\n");
          M(&this->mixin_text_,append,M(&mixin->assign_.implementation_,c_str));
          M(&this->mixin_text_,gsub_,"@CLASS@",class_name);
        }
      }
    
}
void yaoocpp_assignment_print_implementation(const_pointer __pthis__,ostream_pointer __postrm,const char* namespace)
{
yaoocpp_assignment_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      if(this->form_==IMPLEMENTATION_TEXT) {
        M(ostrm,printf,"void %s_assign(pointer __pthis__,const_pointer __psrc__)\n"
        "{\n%s_pointer this=__pthis__;(void)this;\n"
        "%s_const_pointer %s=__psrc__;(void)%s;\n"
        "%s\n"
        "%s\n"
        "}\n",M(&this->name_,c_str),M(&this->name_,c_str),M(&this->name_,c_str),M(&this->src_name_,c_str),
              M(&this->src_name_,c_str),M(&this->mixin_text_,c_str),M(&this->implementation_,c_str));
      }
    
}
void yaoocpp_assignment_print_type_info_entry(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_assignment_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_type_info_print_entry(this,ostrm,"assign");
    
}
void yaoocpp_assignment_print_yod_definition(const_pointer __pthis__,ostream_pointer __postrm,bool include_implementation)
{
yaoocpp_assignment_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      if(this->form_==IMPLEMENTATION_TEXT) {
            M(ostrm,printf,"operator=(%s){\n"
            "%s\n"
            "}\n",M(&this->src_name_,c_str),
            (include_implementation ? M(&this->implementation_,c_str) : ""));
      } else if(this->form_==IMPLEMENTED_AS) {
        M(ostrm,printf,"operator=(%s) = %s;\n",M(&this->src_name_,c_str),
              M(&this->implementation_,c_str));
      } else if(this->form_==DELETE) {
        M(ostrm,printf,"operator=(%s) = delete;\n",M(&this->src_name_,c_str));
      }
    
}
void yaoocpp_assignment_print_prototype(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_assignment_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_assignment_parent_class_table->print_prototype(this,ostrm)
#define PM(method,...) CTM((*yaoocpp_assignment_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      if(this->form_==IMPLEMENTED_AS) {
        M(ostrm,printf,"#define %s_assign %s\n",M(&this->name_,c_str),M(&this->implementation_,c_str));
      } else if(this->form_==IMPLEMENTATION_TEXT) {
        M(ostrm,printf,"void %s_assign(pointer,const_pointer);\n",M(&this->name_,c_str));
      }
    
#undef PM
#undef super
}
yaoocpp_assignment_class_table_t yaoocpp_assignment_class_table ={
.parent_class_table_ = (const class_table_t*) &yaoocpp_copy_constructor_class_table,
.type_name_ = (const char*) "yaoocpp_assignment_t",
.swap = (void(*)(pointer,pointer)) yaoocpp_assignment_swap,
.set_line_no = (void(*)(pointer,int)) yaoocpp_assignment_set_line_no,
.print_prototype = (void(*)(const_pointer,ostream_pointer)) yaoocpp_assignment_print_prototype,
.set_implementation = (void(*)(pointer,const char*,size_t)) yaoocpp_assignment_set_implementation,
.set_implemented_as = (void(*)(pointer,const char*,size_t)) yaoocpp_assignment_set_implemented_as,
.is_implemented = (bool(*)(const_pointer)) yaoocpp_assignment_is_implemented,
.set_source_name = (void(*)(pointer,const char*,size_t)) yaoocpp_assignment_set_source_name,
};
const type_info_t __yaoocpp_assignment_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaoocpp_assignment_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=NULL,
.dtor_=NULL,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaoocpp_assignment_class_table,
.parent_=&__yaoocpp_copy_constructor_ti
};
const type_info_t* const yaoocpp_assignment_ti=&__yaoocpp_assignment_ti;
void yaoocpp_rich_compare_resolve(pointer __pthis__,const char* class_name,const char* parent_class_name,yaoocpp_item_pointer_vector_const_pointer new_items)
{
yaoocpp_rich_compare_pointer this=__pthis__;(void)this;


      if(this->form_==DEFAULT) {
        this->form_=DELETE;
      }
    
}
void yaoocpp_rich_compare_print_implementation(const_pointer __pthis__,ostream_pointer __postrm,const char* namespace)
{
yaoocpp_rich_compare_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      if(this->form_==IMPLEMENTATION_TEXT) {
        M(ostrm,printf,"int %s_rich_compare(const_pointer __plhs__,const_pointer __prhs__)\n"
        "{\n%s_const_pointer %s=__plhs__;(void)%s;\n"
        "%s_const_pointer %s=__prhs__;(void)%s;\n"
        "%s\n"
        "}\n",M(&this->name_,c_str),M(&this->name_,c_str),M(&this->lhs_name_,c_str),M(&this->lhs_name_,c_str),
        M(&this->name_,c_str),M(&this->rhs_name_,c_str),M(&this->rhs_name_,c_str),M(&this->implementation_,c_str));
      }
    
}
void yaoocpp_rich_compare_print_type_info_entry(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_rich_compare_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_type_info_print_entry(this,ostrm,"rich_compare");
    
}
void yaoocpp_rich_compare_print_prototype(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_rich_compare_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_rich_compare_parent_class_table->print_prototype(this,ostrm)
#define PM(method,...) CTM((*yaoocpp_rich_compare_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      if(this->form_==IMPLEMENTED_AS) {
        M(ostrm,printf,"#define %s_rich_compare %s\n",M(&this->name_,c_str),M(&this->implementation_,c_str));
      } else if(this->form_==IMPLEMENTATION_TEXT) {
        M(ostrm,printf,"int %s_rich_compare(const_pointer,const_pointer);\n",M(&this->name_,c_str));
      }
    
#undef PM
#undef super
}
void yaoocpp_rich_compare_set_lhs_name(pointer __pthis__,const char* str,size_t len)
{
yaoocpp_rich_compare_pointer this=__pthis__;(void)this;
#define super() yaoocpp_rich_compare_parent_class_table->set_lhs_name(this,str,len)
#define PM(method,...) CTM((*yaoocpp_rich_compare_parent_class_table),this,method,## __VA_ARGS__)


      M(&this->lhs_name_,setn,str,len);
    
#undef PM
#undef super
}
void yaoocpp_rich_compare_set_rhs_name(pointer __pthis__,const char* str,size_t len)
{
yaoocpp_rich_compare_pointer this=__pthis__;(void)this;
#define super() yaoocpp_rich_compare_parent_class_table->set_rhs_name(this,str,len)
#define PM(method,...) CTM((*yaoocpp_rich_compare_parent_class_table),this,method,## __VA_ARGS__)


      M(&this->rhs_name_,setn,str,len);
    
#undef PM
#undef super
}
yaoocpp_rich_compare_class_table_t yaoocpp_rich_compare_class_table ={
.parent_class_table_ = (const class_table_t*) &yaoocpp_type_info_class_table,
.type_name_ = (const char*) "yaoocpp_rich_compare_t",
.swap = (void(*)(pointer,pointer)) yaoocpp_rich_compare_swap,
.set_line_no = (void(*)(pointer,int)) yaoocpp_rich_compare_set_line_no,
.print_prototype = (void(*)(const_pointer,ostream_pointer)) yaoocpp_rich_compare_print_prototype,
.set_implementation = (void(*)(pointer,const char*,size_t)) yaoocpp_rich_compare_set_implementation,
.set_implemented_as = (void(*)(pointer,const char*,size_t)) yaoocpp_rich_compare_set_implemented_as,
.is_implemented = (bool(*)(const_pointer)) yaoocpp_rich_compare_is_implemented,
.set_lhs_name = (void(*)(pointer,const char*,size_t)) yaoocpp_rich_compare_set_lhs_name,
.set_rhs_name = (void(*)(pointer,const char*,size_t)) yaoocpp_rich_compare_set_rhs_name,
};
void yaoocpp_rich_compare_default_ctor(pointer __pthis__)
{
yaoocpp_rich_compare_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaoocpp_rich_compare);


newp(&this->lhs_name_,yaooc_string);
newp(&this->rhs_name_,yaooc_string);

}
void yaoocpp_rich_compare_dtor(pointer __pthis__)
{
yaoocpp_rich_compare_pointer this=__pthis__;(void)this;

deletep(&this->lhs_name_,yaooc_string);
deletep(&this->rhs_name_,yaooc_string);

}
void yaoocpp_rich_compare_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaoocpp_rich_compare_pointer this=__pthis__;(void)this;
yaoocpp_rich_compare_const_pointer src=__psrc__;(void)src;

call_default_ctor_static(this,yaoocpp_rich_compare);
assign_static(this,src,yaoocpp_rich_compare);


}
void yaoocpp_rich_compare_assign(pointer __pthis__,const_pointer __psrc__)
{
yaoocpp_rich_compare_pointer this=__pthis__;(void)this;
yaoocpp_rich_compare_const_pointer src=__psrc__;(void)src;

assign_static(this,src,yaoocpp_type_info);
assign_static(&this->lhs_name_,&src->lhs_name_,yaooc_string);
assign_static(&this->rhs_name_,&src->rhs_name_,yaooc_string);

}
const type_info_t __yaoocpp_rich_compare_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaoocpp_rich_compare_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaoocpp_rich_compare_default_ctor,
.dtor_=yaoocpp_rich_compare_dtor,
.copy_ctor_=yaoocpp_rich_compare_copy_ctor,
.assign_=yaoocpp_rich_compare_assign,
.class_table_=(const class_table_t*) &yaoocpp_rich_compare_class_table,
.parent_=&__yaoocpp_type_info_ti
};
const type_info_t* const yaoocpp_rich_compare_ti=&__yaoocpp_rich_compare_ti;
void yaoocpp_to_stream_resolve(pointer __pthis__,const char* class_name,const char* parent_class_name,yaoocpp_item_pointer_vector_const_pointer new_items)
{
yaoocpp_to_stream_pointer this=__pthis__;(void)this;





    
}
void yaoocpp_to_stream_print_implementation(const_pointer __pthis__,ostream_pointer __postrm,const char* namespace)
{
yaoocpp_to_stream_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      if(this->form_==IMPLEMENTATION_TEXT) {
        M(ostrm,printf,"void %s_to_stream(const_pointer __pthis__,ostream_pointer __pstrm__)\n"
        "{\n%s_const_pointer this=__pthis__;(void)this;\n"
        "yaooc_ostream_pointer %s=__pstrm__;(void)%s;\n"
        "%s\n"
        "}\n",M(&this->name_,c_str),M(&this->name_,c_str),M(&this->strm_name_,c_str),M(&this->strm_name_,c_str),
        M(&this->implementation_,c_str));
      }
    
}
void yaoocpp_to_stream_print_type_info_entry(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_to_stream_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_type_info_print_entry(this,ostrm,"to_stream");
    
}
void yaoocpp_to_stream_print_prototype(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_to_stream_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_to_stream_parent_class_table->print_prototype(this,ostrm)
#define PM(method,...) CTM((*yaoocpp_to_stream_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      if(this->form_==IMPLEMENTED_AS) {
        M(ostrm,printf,"#define %s_to_stream %s\n",M(&this->name_,c_str),M(&this->implementation_,c_str));
      } else if(this->form_==IMPLEMENTATION_TEXT) {
        M(ostrm,printf,"void %s_to_stream(const_pointer,ostream_pointer);\n",M(&this->name_,c_str));
      }
    
#undef PM
#undef super
}
void yaoocpp_to_stream_set_stream_name(pointer __pthis__,const char* str,size_t len)
{
yaoocpp_to_stream_pointer this=__pthis__;(void)this;
#define super() yaoocpp_to_stream_parent_class_table->set_stream_name(this,str,len)
#define PM(method,...) CTM((*yaoocpp_to_stream_parent_class_table),this,method,## __VA_ARGS__)


      M(&this->strm_name_,setn,str,len);
    
#undef PM
#undef super
}
yaoocpp_to_stream_class_table_t yaoocpp_to_stream_class_table ={
.parent_class_table_ = (const class_table_t*) &yaoocpp_type_info_class_table,
.type_name_ = (const char*) "yaoocpp_to_stream_t",
.swap = (void(*)(pointer,pointer)) yaoocpp_to_stream_swap,
.set_line_no = (void(*)(pointer,int)) yaoocpp_to_stream_set_line_no,
.print_prototype = (void(*)(const_pointer,ostream_pointer)) yaoocpp_to_stream_print_prototype,
.set_implementation = (void(*)(pointer,const char*,size_t)) yaoocpp_to_stream_set_implementation,
.set_implemented_as = (void(*)(pointer,const char*,size_t)) yaoocpp_to_stream_set_implemented_as,
.is_implemented = (bool(*)(const_pointer)) yaoocpp_to_stream_is_implemented,
.set_stream_name = (void(*)(pointer,const char*,size_t)) yaoocpp_to_stream_set_stream_name,
};
void yaoocpp_to_stream_default_ctor(pointer __pthis__)
{
yaoocpp_to_stream_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaoocpp_to_stream);


newp(&this->strm_name_,yaooc_string);

}
void yaoocpp_to_stream_dtor(pointer __pthis__)
{
yaoocpp_to_stream_pointer this=__pthis__;(void)this;

deletep(&this->strm_name_,yaooc_string);

}
void yaoocpp_to_stream_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaoocpp_to_stream_pointer this=__pthis__;(void)this;
yaoocpp_to_stream_const_pointer src=__psrc__;(void)src;

call_default_ctor_static(this,yaoocpp_to_stream);
assign_static(this,src,yaoocpp_to_stream);


}
void yaoocpp_to_stream_assign(pointer __pthis__,const_pointer __psrc__)
{
yaoocpp_to_stream_pointer this=__pthis__;(void)this;
yaoocpp_to_stream_const_pointer src=__psrc__;(void)src;

assign_static(this,src,yaoocpp_type_info);
assign_static(&this->strm_name_,&src->strm_name_,yaooc_string);

}
const type_info_t __yaoocpp_to_stream_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaoocpp_to_stream_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaoocpp_to_stream_default_ctor,
.dtor_=yaoocpp_to_stream_dtor,
.copy_ctor_=yaoocpp_to_stream_copy_ctor,
.assign_=yaoocpp_to_stream_assign,
.class_table_=(const class_table_t*) &yaoocpp_to_stream_class_table,
.parent_=&__yaoocpp_type_info_ti
};
const type_info_t* const yaoocpp_to_stream_ti=&__yaoocpp_to_stream_ti;
void yaoocpp_from_stream_resolve(pointer __pthis__,const char* class_name,const char* parent_class_name,yaoocpp_item_pointer_vector_const_pointer new_items)
{
yaoocpp_from_stream_pointer this=__pthis__;(void)this;

      if(this->form_==DEFAULT) {

        this->form_=DELETE;
      }
    
}
void yaoocpp_from_stream_print_implementation(const_pointer __pthis__,ostream_pointer __postrm,const char* namespace)
{
yaoocpp_from_stream_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      if(this->form_==IMPLEMENTATION_TEXT) {
        M(ostrm,printf,"void %s_from_stream(pointer __pthis__,ostream_pointer __pstrm__)\n"
        "{\n%s_pointer this=__pthis__;(void)this;\n"
        "yaooc_istream_pointer %s=__pstrm__;(void)%s;\n"
        "%s\n"
        "}\n",M(&this->name_,c_str),M(&this->name_,c_str),M(&this->strm_name_,c_str),M(&this->strm_name_,c_str),
        M(&this->implementation_,c_str));
      }
    
}
void yaoocpp_from_stream_print_type_info_entry(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_from_stream_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_type_info_print_entry(this,ostrm,"from_stream");
    
}
void yaoocpp_from_stream_print_prototype(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_from_stream_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_from_stream_parent_class_table->print_prototype(this,ostrm)
#define PM(method,...) CTM((*yaoocpp_from_stream_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      if(this->form_==IMPLEMENTED_AS) {
        M(ostrm,printf,"#define %s_from_stream %s\n",M(&this->name_,c_str),M(&this->implementation_,c_str));
      } else if(this->form_==IMPLEMENTATION_TEXT) {
        M(ostrm,printf,"void %s_from_stream(pointer,ostream_pointer);\n",M(&this->name_,c_str));
      }
    
#undef PM
#undef super
}
yaoocpp_from_stream_class_table_t yaoocpp_from_stream_class_table ={
.parent_class_table_ = (const class_table_t*) &yaoocpp_to_stream_class_table,
.type_name_ = (const char*) "yaoocpp_from_stream_t",
.swap = (void(*)(pointer,pointer)) yaoocpp_from_stream_swap,
.set_line_no = (void(*)(pointer,int)) yaoocpp_from_stream_set_line_no,
.print_prototype = (void(*)(const_pointer,ostream_pointer)) yaoocpp_from_stream_print_prototype,
.set_implementation = (void(*)(pointer,const char*,size_t)) yaoocpp_from_stream_set_implementation,
.set_implemented_as = (void(*)(pointer,const char*,size_t)) yaoocpp_from_stream_set_implemented_as,
.is_implemented = (bool(*)(const_pointer)) yaoocpp_from_stream_is_implemented,
.set_stream_name = (void(*)(pointer,const char*,size_t)) yaoocpp_from_stream_set_stream_name,
};
const type_info_t __yaoocpp_from_stream_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaoocpp_from_stream_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=NULL,
.dtor_=NULL,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaoocpp_from_stream_class_table,
.parent_=&__yaoocpp_to_stream_ti
};
const type_info_t* const yaoocpp_from_stream_ti=&__yaoocpp_from_stream_ti;
void yaoocpp_constructor_resolve(pointer __pthis__,const char* class_name,const char* parent_class_name,yaoocpp_item_pointer_vector_const_pointer new_items)
{
yaoocpp_constructor_pointer this=__pthis__;(void)this;

      yaoocpp_constructor_base_gen_initializers_text(this,class_name,parent_class_name,new_items,false);
    
}
void yaoocpp_constructor_print_args_type(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_constructor_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_item_pointer_vector_const_iterator i;
      CFOR_EACH(i,&this->arguments_) {
        yaoocpp_argument_const_pointer iarg=i->ptr_;
        M(ostrm,printf,",%s",M(&iarg->type_,c_str));
      }
    
}
void yaoocpp_constructor_print_args_type_name(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_constructor_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_item_pointer_vector_const_iterator i;
      CFOR_EACH(i,&this->arguments_) {
        yaoocpp_argument_const_pointer iarg=i->ptr_;
        M(ostrm,printf,",%s %s",M(&iarg->type_,c_str),M(&iarg->name_,c_str));
      }
    
}
void yaoocpp_constructor_print_prototype(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_constructor_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_constructor_parent_class_table->print_prototype(this,ostrm)
#define PM(method,...) CTM((*yaoocpp_constructor_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      if(this->form_==IMPLEMENTED_AS)
        M(ostrm,printf,"#define %s %s\n",M(&this->name_,c_str),M(&this->implementation_,c_str));
      else
        M(ostrm,printf,"void %s(pointer,va_list);\n",M(&this->name_,c_str));
    
#undef PM
#undef super
}
void yaoocpp_constructor_print_implementation(const_pointer __pthis__,ostream_pointer __postrm,const char* class_name)
{
yaoocpp_constructor_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_constructor_parent_class_table->print_implementation(this,ostrm,class_name)
#define PM(method,...) CTM((*yaoocpp_constructor_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      if(this->form_==IMPLEMENTATION_TEXT) {
        M(ostrm,printf,"void %s(pointer __pthis,va_list __con_args__){\n"
              "%s_pointer this=__pthis;(void)this;\n",M(&this->name_,c_str),class_name);
        yaoocpp_item_pointer_vector_const_iterator i;
        CFOR_EACH(i,&this->arguments_) {
          yaoocpp_argument_const_pointer iarg=i->ptr_;
          if(strcmp(M(&iarg->type_,c_str),"...")==0) {
            M(ostrm,printf,"#define %s __con_args__",M(&iarg->name_,c_str));
          } else {

            const char* arg_type=M(&iarg->type_,c_str);
            if(strcmp(M(&iarg->type_,c_str),"ostream_pointer") == 0)
              arg_type="yaooc_ostream_pointer";
            else if(strcmp(M(&iarg->type_,c_str),"istream_pointer") == 0)
              arg_type="yaooc_istream_pointer";
            M(ostrm,printf,"%s %s = va_arg(__con_args__,%s);\n",arg_type,
                  M(&iarg->name_,c_str),arg_type);
          }
        }
        M(ostrm,printf,"\n%s\n%s\n",M(&this->initializer_text_,c_str),M(&this->implementation_,c_str));
        M(ostrm,printf,"}\n");
      }
    
#undef PM
#undef super
}
size_t yaoocpp_constructor_argument_count(const_pointer __pthis__)
{
yaoocpp_constructor_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_constructor_parent_class_table->argument_count(this)
#define PM(method,...) CTM((*yaoocpp_constructor_parent_class_table),this,method,## __VA_ARGS__)


      return M(&this->arguments_,size);
    
#undef PM
#undef super
}
yaoocpp_constructor_class_table_t yaoocpp_constructor_class_table ={
.parent_class_table_ = (const class_table_t*) &yaoocpp_constructor_base_class_table,
.type_name_ = (const char*) "yaoocpp_constructor_t",
.swap = (void(*)(pointer,pointer)) yaoocpp_constructor_swap,
.set_line_no = (void(*)(pointer,int)) yaoocpp_constructor_set_line_no,
.print_prototype = (void(*)(const_pointer,ostream_pointer)) yaoocpp_constructor_print_prototype,
.set_implementation = (void(*)(pointer,const char*,size_t)) yaoocpp_constructor_set_implementation,
.set_implemented_as = (void(*)(pointer,const char*,size_t)) yaoocpp_constructor_set_implemented_as,
.is_implemented = (bool(*)(const_pointer)) yaoocpp_constructor_is_implemented,
.print_implementation = (void(*)(const_pointer,ostream_pointer,const char*)) yaoocpp_constructor_print_implementation,
.argument_count = (size_t(*)(const_pointer)) yaoocpp_constructor_argument_count,
};
void yaoocpp_constructor_default_ctor(pointer __pthis__)
{
yaoocpp_constructor_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaoocpp_constructor);



    newp(&this->arguments_,yaoocpp_item_pointer_vector);
  

}
void yaoocpp_constructor_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaoocpp_constructor_pointer this=__pthis__;(void)this;
yaoocpp_constructor_const_pointer src=__psrc__;(void)src;


call_default_ctor_static(this,yaoocpp_constructor);
assign_static(this,src,yaoocpp_constructor);


}
void yaoocpp_constructor_assign(pointer __pthis__,const_pointer __psrc__)
{
yaoocpp_constructor_pointer this=__pthis__;(void)this;
yaoocpp_constructor_const_pointer src=__psrc__;(void)src;


    assign_static(&this->arguments_,&src->arguments_,yaoocpp_item_pointer_vector);
  
assign_static(this,src,yaoocpp_constructor_base);

}
const type_info_t __yaoocpp_constructor_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaoocpp_constructor_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaoocpp_constructor_default_ctor,
.dtor_=NULL,
.copy_ctor_=yaoocpp_constructor_copy_ctor,
.assign_=yaoocpp_constructor_assign,
.class_table_=(const class_table_t*) &yaoocpp_constructor_class_table,
.parent_=&__yaoocpp_constructor_base_ti
};
const type_info_t* const yaoocpp_constructor_ti=&__yaoocpp_constructor_ti;
void yaoocpp_section_print_to_header(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_section_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_section_parent_class_table->print_to_header(this,ostrm)
#define PM(method,...) CTM((*yaoocpp_section_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


    
#undef PM
#undef super
}
void yaoocpp_section_print_to_source(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_section_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_section_parent_class_table->print_to_source(this,ostrm)
#define PM(method,...) CTM((*yaoocpp_section_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


    
#undef PM
#undef super
}
void yaoocpp_section_print_to_yod(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_section_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_section_parent_class_table->print_to_yod(this,ostrm)
#define PM(method,...) CTM((*yaoocpp_section_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


    
#undef PM
#undef super
}
void yaoocpp_section_resolve(pointer __pthis__,const char* class_name,const char* parent_class_name,yaoocpp_item_pointer_vector_const_pointer new_items)
{
yaoocpp_section_pointer this=__pthis__;(void)this;
#define super() yaoocpp_section_parent_class_table->resolve(this,class_name,parent_class_name,new_items)
#define PM(method,...) CTM((*yaoocpp_section_parent_class_table),this,method,## __VA_ARGS__)



    
#undef PM
#undef super
}
void yaoocpp_section_add_mixins(pointer __pthis__,yaoocpp_item_pointer_vector_const_pointer mixins)
{
yaoocpp_section_pointer this=__pthis__;(void)this;
#define super() yaoocpp_section_parent_class_table->add_mixins(this,mixins)
#define PM(method,...) CTM((*yaoocpp_section_parent_class_table),this,method,## __VA_ARGS__)


    
#undef PM
#undef super
}
yaoocpp_section_class_table_t yaoocpp_section_class_table ={
.parent_class_table_ = (const class_table_t*) &yaoocpp_item_class_table,
.type_name_ = (const char*) "yaoocpp_section_t",
.swap = (void(*)(pointer,pointer)) yaoocpp_section_swap,
.set_line_no = (void(*)(pointer,int)) yaoocpp_section_set_line_no,
.print_to_header = (void(*)(const_pointer,ostream_pointer)) yaoocpp_section_print_to_header,
.print_to_source = (void(*)(const_pointer,ostream_pointer)) yaoocpp_section_print_to_source,
.print_to_yod = (void(*)(const_pointer,ostream_pointer)) yaoocpp_section_print_to_yod,
.resolve = (void(*)(pointer,const char*,const char*,yaoocpp_item_pointer_vector_const_pointer)) yaoocpp_section_resolve,
.add_mixins = (void(*)(pointer,yaoocpp_item_pointer_vector_const_pointer)) yaoocpp_section_add_mixins,
};
void yaoocpp_section_default_ctor(pointer __pthis__)
{
yaoocpp_section_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaoocpp_section);



      this->defined_in_top_level_file_=false;
    
}
void yaoocpp_section_dtor(pointer __pthis__)
{
yaoocpp_section_pointer this=__pthis__;(void)this;


}
void yaoocpp_section_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaoocpp_section_pointer this=__pthis__;(void)this;
yaoocpp_section_const_pointer src=__psrc__;(void)src;

call_default_ctor_static(this,yaoocpp_section);
assign_static(this,src,yaoocpp_section);


}
void yaoocpp_section_assign(pointer __pthis__,const_pointer __psrc__)
{
yaoocpp_section_pointer this=__pthis__;(void)this;
yaoocpp_section_const_pointer src=__psrc__;(void)src;

assign_static(this,src,yaoocpp_item);
this->defined_in_top_level_file_=src->defined_in_top_level_file_;

}
const type_info_t __yaoocpp_section_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaoocpp_section_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaoocpp_section_default_ctor,
.dtor_=yaoocpp_section_dtor,
.copy_ctor_=yaoocpp_section_copy_ctor,
.assign_=yaoocpp_section_assign,
.class_table_=(const class_table_t*) &yaoocpp_section_class_table,
.parent_=&__yaoocpp_item_ti
};
const type_info_t* const yaoocpp_section_ti=&__yaoocpp_section_ti;
void yaoocpp_header_print_to_header(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_header_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_header_parent_class_table->print_to_header(this,ostrm)
#define PM(method,...) CTM((*yaoocpp_header_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      M(ostrm,printf,"%s\n",M(&this->content_,c_str));
    
#undef PM
#undef super
}
yaoocpp_header_class_table_t yaoocpp_header_class_table ={
.parent_class_table_ = (const class_table_t*) &yaoocpp_section_class_table,
.type_name_ = (const char*) "yaoocpp_header_t",
.swap = (void(*)(pointer,pointer)) yaoocpp_header_swap,
.set_line_no = (void(*)(pointer,int)) yaoocpp_header_set_line_no,
.print_to_header = (void(*)(const_pointer,ostream_pointer)) yaoocpp_header_print_to_header,
.print_to_source = (void(*)(const_pointer,ostream_pointer)) yaoocpp_header_print_to_source,
.print_to_yod = (void(*)(const_pointer,ostream_pointer)) yaoocpp_header_print_to_yod,
.resolve = (void(*)(pointer,const char*,const char*,yaoocpp_item_pointer_vector_const_pointer)) yaoocpp_header_resolve,
.add_mixins = (void(*)(pointer,yaoocpp_item_pointer_vector_const_pointer)) yaoocpp_header_add_mixins,
};
void yaoocpp_header_default_ctor(pointer __pthis__)
{
yaoocpp_header_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaoocpp_header);


newp(&this->content_,yaooc_string);

}
void yaoocpp_header_dtor(pointer __pthis__)
{
yaoocpp_header_pointer this=__pthis__;(void)this;

deletep(&this->content_,yaooc_string);

}
void yaoocpp_header_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaoocpp_header_pointer this=__pthis__;(void)this;
yaoocpp_header_const_pointer src=__psrc__;(void)src;

call_default_ctor_static(this,yaoocpp_header);
assign_static(this,src,yaoocpp_header);


}
void yaoocpp_header_assign(pointer __pthis__,const_pointer __psrc__)
{
yaoocpp_header_pointer this=__pthis__;(void)this;
yaoocpp_header_const_pointer src=__psrc__;(void)src;

assign_static(this,src,yaoocpp_section);
assign_static(&this->content_,&src->content_,yaooc_string);

}
const type_info_t __yaoocpp_header_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaoocpp_header_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaoocpp_header_default_ctor,
.dtor_=yaoocpp_header_dtor,
.copy_ctor_=yaoocpp_header_copy_ctor,
.assign_=yaoocpp_header_assign,
.class_table_=(const class_table_t*) &yaoocpp_header_class_table,
.parent_=&__yaoocpp_section_ti
};
const type_info_t* const yaoocpp_header_ti=&__yaoocpp_header_ti;
void yaoocpp_source_print_to_header(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_source_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_source_parent_class_table->print_to_header(this,ostrm)
#define PM(method,...) CTM((*yaoocpp_source_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


    
#undef PM
#undef super
}
void yaoocpp_source_print_to_source(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_source_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_source_parent_class_table->print_to_source(this,ostrm)
#define PM(method,...) CTM((*yaoocpp_source_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      M(ostrm,printf,"%s\n",M(&this->content_,c_str));
    
#undef PM
#undef super
}
yaoocpp_source_class_table_t yaoocpp_source_class_table ={
.parent_class_table_ = (const class_table_t*) &yaoocpp_header_class_table,
.type_name_ = (const char*) "yaoocpp_source_t",
.swap = (void(*)(pointer,pointer)) yaoocpp_source_swap,
.set_line_no = (void(*)(pointer,int)) yaoocpp_source_set_line_no,
.print_to_header = (void(*)(const_pointer,ostream_pointer)) yaoocpp_source_print_to_header,
.print_to_source = (void(*)(const_pointer,ostream_pointer)) yaoocpp_source_print_to_source,
.print_to_yod = (void(*)(const_pointer,ostream_pointer)) yaoocpp_source_print_to_yod,
.resolve = (void(*)(pointer,const char*,const char*,yaoocpp_item_pointer_vector_const_pointer)) yaoocpp_source_resolve,
.add_mixins = (void(*)(pointer,yaoocpp_item_pointer_vector_const_pointer)) yaoocpp_source_add_mixins,
};
const type_info_t __yaoocpp_source_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaoocpp_source_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=NULL,
.dtor_=NULL,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaoocpp_source_class_table,
.parent_=&__yaoocpp_header_ti
};
const type_info_t* const yaoocpp_source_ti=&__yaoocpp_source_ti;
void yaoocpp_struct_print_struct_definition(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_struct_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      const char* struct_type="yaooc_struct";
      if(M(this,is_min_pod))
        struct_type="yaooc_min_struct";
      else if(M(this,is_pod))
        struct_type="yaooc_pod_struct";
      M(ostrm,printf,"%s(%s) {\n",struct_type,M(&this->name_,c_str));
      if(this->parent_)
        M(ostrm,printf,"  %s_t;\n",M(&this->parent_->name_,c_str));
      yaoocpp_item_pointer_vector_const_iterator iter;
      CFOR_EACH(iter,&this->instance_) {
        yaoocpp_member_item_t* mitem = iter->ptr_;
        if(mitem->generation_==INITIAL) {
          M(mitem,print_table_definition,ostrm,M(&this->name_,c_str),(this->parent_ ? M(&this->parent_->name_,c_str) : NULL ));
        }
      }
      M(ostrm,printf,"};\n");
    
}
void yaoocpp_struct_print_type_info_definition(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_struct_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      M(&this->default_ctor_,print_prototype,ostrm);
      M(&this->dtor_,print_prototype,ostrm);
      M(&this->copy_ctor_,print_prototype,ostrm);
      M(&this->assign_,print_prototype,ostrm);
      M(&this->rich_compare_,print_prototype,ostrm);
      M(&this->to_stream_,print_prototype,ostrm);
      M(&this->from_stream_,print_prototype,ostrm);
    
}
void yaoocpp_struct_print_type_info_implementation(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_struct_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_default_constructor_print_implementation(&this->default_ctor_,ostrm,M(&this->name_,c_str));
      yaoocpp_destructor_print_implementation(&this->dtor_,ostrm,M(&this->name_,c_str));
      yaoocpp_copy_constructor_print_implementation(&this->copy_ctor_,ostrm,M(&this->name_,c_str));
      yaoocpp_assignment_print_implementation(&this->assign_,ostrm,M(&this->name_,c_str));
      yaoocpp_rich_compare_print_implementation(&this->rich_compare_,ostrm,M(&this->name_,c_str));
      yaoocpp_to_stream_print_implementation(&this->to_stream_,ostrm,M(&this->name_,c_str));
      yaoocpp_from_stream_print_implementation(&this->from_stream_,ostrm,M(&this->name_,c_str));
    
}
void yaoocpp_struct_print_constructor_prototypes(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_struct_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_item_pointer_vector_const_iterator i;

      CFOR_EACH(i,&this->constructors_) {
        M((yaoocpp_constructor_const_pointer)i->ptr_,print_prototype,ostrm);
      }
    
}
void yaoocpp_struct_print_constructor_implementation(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_struct_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_item_pointer_vector_const_iterator i;

      CFOR_EACH(i,&this->constructors_) {
        M((yaoocpp_constructor_const_pointer)i->ptr_,print_implementation,ostrm,M(&this->name_,c_str));
      }
    
}
void yaoocpp_struct_print_adjunct_prototypes(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_struct_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_item_pointer_vector_const_iterator i;

      CFOR_EACH(i,&this->adjunct_){
        yaoocpp_member_item_const_pointer item=(yaoocpp_member_item_const_pointer)i->ptr_;
        M(item,print_adjunct_prototype,ostrm,M(&this->name_,c_str),(this->parent_ ? M(&this->parent_->name_,c_str) : NULL ));
      }
    
}
void yaoocpp_struct_print_adjunct_implementation(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_struct_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_item_pointer_vector_const_iterator i;
      CFOR_EACH(i,&this->adjunct_){
        yaoocpp_member_item_const_pointer item=(yaoocpp_member_item_const_pointer)i->ptr_;
        M(item,print_adjunct_implementation,ostrm,M(&this->name_,c_str),(this->parent_ ? M(&this->parent_->name_,c_str) : NULL ));
      }
    
}
void yaoocpp_struct_print_private_variable_implementation(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_struct_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_item_pointer_vector_const_iterator iter;
      CFOR_EACH(iter,&this->private_) {
        yaoocpp_member_item_t* mitem = (yaoocpp_member_item_t*)iter->ptr_;
        if(ISA(mitem,yaoocpp_variable))
          M(mitem,print_private_implementation,ostrm,M(&this->name_,c_str),(this->parent_ ? M(&this->parent_->name_,c_str) : NULL ));
      }
    
}
void yaoocpp_struct_print_private_method_prototypes(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_struct_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_item_pointer_vector_const_iterator iter;

      CFOR_EACH(iter,&this->private_) {
        yaoocpp_member_item_t* mitem = (yaoocpp_member_item_t*)iter->ptr_;
        if(ISA(mitem,yaoocpp_method))
          M(mitem,print_private_prototype,ostrm,M(&this->name_,c_str),(this->parent_ ? M(&this->parent_->name_,c_str) : NULL ));
      }
    
}
void yaoocpp_struct_print_private_method_implementation(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_struct_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_item_pointer_vector_const_iterator iter;
      CFOR_EACH(iter,&this->private_) {
        yaoocpp_member_item_t* mitem = (yaoocpp_member_item_t*)iter->ptr_;
        if(ISA(mitem,yaoocpp_method))
          M(mitem,print_private_implementation,ostrm,M(&this->name_,c_str),(this->parent_ ? M(&this->parent_->name_,c_str) : NULL ));
      }
    
}
void yaoocpp_struct_add_mixin_members(pointer __pthis__,yaoocpp_item_pointer_vector_pointer target,yaoocpp_item_pointer_vector_const_pointer src,bool error_if_dup)
{
yaoocpp_struct_pointer this=__pthis__;(void)this;

      gb_init();
      yaoocpp_item_pointer_vector_const_iterator iter;
      CFOR_EACH(iter,src) {
        yaooc_dynamic_pointer_t* item=yaooc_find(yaooc_dynamic_pointer,M(target,cbegin),M(target,cend),iter);
        if(item != M(target,cend)) {
          if(error_if_dup) {
            printf("Mixin caused duplicate entry\n");
            exit(44);
          } else {
            assign_static(item,iter,yaooc_dynamic_pointer);
          }
        } else {
          M(target,push_back,iter);
        }
      }
      gb_exit();
    
}
void yaoocpp_struct_print_type_info_declaration(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_struct_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      const char* class_name=M(&this->name_,c_str);
      const char* parent_class_name = this->parent_ ? M(&this->parent_->name_,c_str) : NULL;
      bool is_min_pod=M(this,is_min_pod);
      bool is_pod=M(this,is_pod);
      M(ostrm,printf,"const ");
      if(is_min_pod)
        M(ostrm,printf,"min_type_info_t ");
      else if(is_pod)
        M(ostrm,printf,"pod_type_info_t ");
      else
        M(ostrm,printf,"type_info_t ");
      M(ostrm,printf,"__%s_ti = {\n",class_name);
      M(ostrm,printf,".min_flag_=%d,\n",(is_min_pod ? 1 : 0));
      M(ostrm,printf,".pod_flag_=%d,\n",(!is_min_pod && is_pod ? 1 : 0));
      M(ostrm,printf,".type_size_=sizeof(%s_t),\n",class_name,class_name);
      if(!is_min_pod) {
        yaoocpp_rich_compare_print_type_info_entry(&this->rich_compare_,ostrm);
        yaoocpp_to_stream_print_type_info_entry(&this->to_stream_,ostrm);
        yaoocpp_from_stream_print_type_info_entry(&this->from_stream_,ostrm);
      }
      if(!is_min_pod && !is_pod){
        yaoocpp_default_constructor_print_type_info_entry(&this->default_ctor_,ostrm);
        yaoocpp_destructor_print_type_info_entry(&this->dtor_,ostrm);
        yaoocpp_copy_constructor_print_type_info_entry(&this->copy_ctor_,ostrm);
        yaoocpp_assignment_print_type_info_entry(&this->assign_,ostrm);
        M(ostrm,printf,".class_table_=NULL,\n");
        M(ostrm,printf,".parent_=");
        if(parent_class_name)
          M(ostrm,printf,"&__%s_ti",parent_class_name);
        else
          M(ostrm,printf,"NULL\n");
      }
      M(ostrm,printf,"};\n");
      M(ostrm,printf,"const type_info_t* const %s_ti=(const type_info_t* const)&__%s_ti;\n",class_name,class_name);
    
}
void yaoocpp_struct_print_to_header(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_struct_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_struct_parent_class_table->print_to_header(this,ostrm)
#define PM(method,...) CTM((*yaoocpp_struct_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_struct_print_struct_definition(this,ostrm);
      yaoocpp_struct_print_type_info_definition(this,ostrm);
      yaoocpp_struct_print_constructor_prototypes(this,ostrm);
      yaoocpp_struct_print_adjunct_prototypes(this,ostrm);
    
#undef PM
#undef super
}
void yaoocpp_struct_print_to_source(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_struct_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_struct_parent_class_table->print_to_source(this,ostrm)
#define PM(method,...) CTM((*yaoocpp_struct_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_struct_print_private_variable_implementation(this,ostrm);
      yaoocpp_struct_print_private_method_prototypes(this,ostrm);
      yaoocpp_struct_print_private_method_implementation(this,ostrm);
      yaoocpp_struct_print_type_info_implementation(this,ostrm);
      yaoocpp_struct_print_constructor_implementation(this,ostrm);
      yaoocpp_struct_print_adjunct_implementation(this,ostrm);
      yaoocpp_struct_print_type_info_declaration(this,ostrm);
    
#undef PM
#undef super
}
void yaoocpp_struct_print_to_yod(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_struct_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_struct_parent_class_table->print_to_yod(this,ostrm)
#define PM(method,...) CTM((*yaoocpp_struct_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      M(ostrm,printf,"%%struct %s {\n",M(&this->name_,c_str));
      yaoocpp_default_constructor_print_yod_definition(&this->default_ctor_,ostrm,false);
      yaoocpp_destructor_print_yod_definition(&this->dtor_,ostrm,false);
      yaoocpp_copy_constructor_print_yod_definition(&this->copy_ctor_,ostrm,false);
      yaoocpp_assignment_print_yod_definition(&this->assign_,ostrm,false);
      M(ostrm,printf,"instance:\n");
      const yaoocpp_member_item_t* const* i;
      CFOR_EACH(i,&this->instance_) {
        M(*i,print_yod_definition,ostrm,false);
      }
      M(ostrm,printf,"};");
    
#undef PM
#undef super
}
void yaoocpp_struct_add_mixins(pointer __pthis__,yaoocpp_item_pointer_vector_const_pointer mixins)
{
yaoocpp_struct_pointer this=__pthis__;(void)this;
#define super() yaoocpp_struct_parent_class_table->add_mixins(this,mixins)
#define PM(method,...) CTM((*yaoocpp_struct_parent_class_table),this,method,## __VA_ARGS__)


      gb_init();
      yaooc_string_vector_const_iterator imix;
      const char* class_name=M(&this->name_,c_str);
      const char* parent_class_name= this->parent_ ? M(&this->parent_->name_,c_str) : NULL;
      CFOR_EACH(imix,&this->mixins_) {
        yaoocpp_item_t* temp = gb_new(yaoocpp_item);
        M(&temp->name_,set,M(imix,c_str));
        yaooc_dynamic_pointer_t* dp = yaooc_find(yaooc_dynamic_pointer,M(mixins,cbegin),M(mixins,cend),make_dynamic_pointer(temp));
        if(dp == M(mixins,cend)) {
          printf("Mixin %s not defined\n",M(&temp->name_,c_str));
          exit(33);
        }
        yaoocpp_mixin_const_pointer mixin=dp->ptr_;
        yaoocpp_default_constructor_add_mixin_text(&this->default_ctor_,mixin,class_name,parent_class_name);
        yaoocpp_destructor_add_mixin_text(&this->dtor_,mixin,class_name,parent_class_name);
        yaoocpp_copy_constructor_add_mixin_text(&this->copy_ctor_,mixin,class_name,parent_class_name);
        yaoocpp_assignment_add_mixin_text(&this->assign_,mixin,class_name,parent_class_name);

        yaoocpp_struct_add_mixin_members(this,&this->instance_,&mixin->instance_,false);
        yaoocpp_struct_add_mixin_members(this,&this->adjunct_,&mixin->adjunct_,false);
        yaoocpp_struct_add_mixin_members(this,&this->private_,&mixin->private_,false);
      }
      gb_exit();
    
#undef PM
#undef super
}
void yaoocpp_struct_inherit(pointer __pthis__)
{
yaoocpp_struct_pointer this=__pthis__;(void)this;
#define super() yaoocpp_struct_parent_class_table->inherit(this)
#define PM(method,...) CTM((*yaoocpp_struct_parent_class_table),this,method,## __VA_ARGS__)


      if(this->parent_) {
        assign_static(&this->instance_,&((yaoocpp_struct_t*)this->parent_)->instance_,yaoocpp_item_pointer_vector);
        yaoocpp_item_pointer_vector_iterator i;
        FOR_EACH(i,&this->instance_)
          ((yaoocpp_member_item_pointer)i->ptr_)->generation_=INHERITED;
      }
    
#undef PM
#undef super
}
void yaoocpp_struct_resolve_outstanding_components(pointer __pthis__)
{
yaoocpp_struct_pointer this=__pthis__;(void)this;
#define super() yaoocpp_struct_parent_class_table->resolve_outstanding_components(this)
#define PM(method,...) CTM((*yaoocpp_struct_parent_class_table),this,method,## __VA_ARGS__)


      yaoocpp_item_pointer_vector_t* new_items=yaoocpp_struct_get_new_instance_variables(this);
      const char* class_name=M(&this->name_,c_str);
      const char* parent_class_name=this->parent_ ? M(&this->parent_->name_,c_str) : NULL;
      yaoocpp_default_constructor_resolve(&this->default_ctor_,class_name,parent_class_name,new_items);
      yaoocpp_destructor_resolve(&this->dtor_,class_name,parent_class_name,new_items);
      yaoocpp_copy_constructor_resolve(&this->copy_ctor_,class_name,parent_class_name,new_items);
      yaoocpp_assignment_resolve(&this->assign_,class_name,parent_class_name,new_items);
      yaoocpp_rich_compare_resolve(&this->rich_compare_,class_name,parent_class_name,new_items);
      yaoocpp_to_stream_resolve(&this->to_stream_,class_name,parent_class_name,new_items);
      yaoocpp_from_stream_resolve(&this->from_stream_,class_name,parent_class_name,new_items);
      yaoocpp_item_pointer_vector_iterator i;
      FOR_EACH(i,&this->constructors_) {
        yaoocpp_constructor_resolve(i->ptr_,class_name,parent_class_name,new_items);
      }
      delete(new_items);
    
#undef PM
#undef super
}
yaoocpp_item_pointer_vector_t* yaoocpp_struct_get_new_instance_variables(const_pointer __pthis__)
{
yaoocpp_struct_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_struct_parent_class_table->get_new_instance_variables(this)
#define PM(method,...) CTM((*yaoocpp_struct_parent_class_table),this,method,## __VA_ARGS__)


      yaoocpp_item_pointer_vector_t* new_items = new(yaoocpp_item_pointer_vector);
      yaoocpp_item_pointer_vector_const_iterator iter;
      CFOR_EACH(iter,&this->instance_) {
        yaoocpp_member_item_pointer item=iter->ptr_;
        if(ISA(item,yaoocpp_variable) && item->generation_==INITIAL)
          M(new_items,push_back,iter);
      }
      return new_items;
    
#undef PM
#undef super
}
bool yaoocpp_struct_is_pod(const_pointer __pthis__)
{
yaoocpp_struct_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_struct_parent_class_table->is_pod(this)
#define PM(method,...) CTM((*yaoocpp_struct_parent_class_table),this,method,## __VA_ARGS__)


      bool ret = this->parent_ ? M(this->parent_,is_pod) : true;
      return ret && !M(&this->default_ctor_,is_implemented)
              && !M(&this->dtor_,is_implemented)
              && !M(&this->copy_ctor_,is_implemented)
              && !M(&this->assign_,is_implemented);
    
#undef PM
#undef super
}
bool yaoocpp_struct_is_min_pod(const_pointer __pthis__)
{
yaoocpp_struct_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_struct_parent_class_table->is_min_pod(this)
#define PM(method,...) CTM((*yaoocpp_struct_parent_class_table),this,method,## __VA_ARGS__)


      bool ret = this->parent_ ? M(this->parent_,is_min_pod) : true;
      return ret && !M(&this->default_ctor_,is_implemented)
              && !M(&this->dtor_,is_implemented)
              && !M(&this->copy_ctor_,is_implemented)
              && !M(&this->assign_,is_implemented)
              && !M(&this->rich_compare_,is_implemented)
              && !M(&this->to_stream_,is_implemented)
              && !M(&this->from_stream_,is_implemented);
    
#undef PM
#undef super
}
yaoocpp_struct_class_table_t yaoocpp_struct_class_table ={
.parent_class_table_ = (const class_table_t*) &yaoocpp_section_class_table,
.type_name_ = (const char*) "yaoocpp_struct_t",
.swap = (void(*)(pointer,pointer)) yaoocpp_struct_swap,
.set_line_no = (void(*)(pointer,int)) yaoocpp_struct_set_line_no,
.print_to_header = (void(*)(const_pointer,ostream_pointer)) yaoocpp_struct_print_to_header,
.print_to_source = (void(*)(const_pointer,ostream_pointer)) yaoocpp_struct_print_to_source,
.print_to_yod = (void(*)(const_pointer,ostream_pointer)) yaoocpp_struct_print_to_yod,
.resolve = (void(*)(pointer,const char*,const char*,yaoocpp_item_pointer_vector_const_pointer)) yaoocpp_struct_resolve,
.add_mixins = (void(*)(pointer,yaoocpp_item_pointer_vector_const_pointer)) yaoocpp_struct_add_mixins,
.inherit = (void(*)(pointer)) yaoocpp_struct_inherit,
.resolve_outstanding_components = (void(*)(pointer)) yaoocpp_struct_resolve_outstanding_components,
.get_new_instance_variables = (yaoocpp_item_pointer_vector_t*(*)(const_pointer)) yaoocpp_struct_get_new_instance_variables,
.is_pod = (bool(*)(const_pointer)) yaoocpp_struct_is_pod,
.is_min_pod = (bool(*)(const_pointer)) yaoocpp_struct_is_min_pod,
};
void yaoocpp_struct_default_ctor(pointer __pthis__)
{
yaoocpp_struct_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaoocpp_struct);


this->parent_=NULL;
newp(&this->default_ctor_,yaoocpp_default_constructor);
newp(&this->dtor_,yaoocpp_destructor);
newp(&this->copy_ctor_,yaoocpp_copy_constructor);
newp(&this->assign_,yaoocpp_assignment);
newp(&this->rich_compare_,yaoocpp_rich_compare);
newp(&this->to_stream_,yaoocpp_to_stream);
newp(&this->from_stream_,yaoocpp_from_stream);
newp(&this->constructors_,yaoocpp_item_pointer_vector);
newp(&this->instance_,yaoocpp_item_pointer_vector);
newp(&this->adjunct_,yaoocpp_item_pointer_vector);
newp(&this->private_,yaoocpp_item_pointer_vector);
newp(&this->mixins_,yaooc_string_vector);

}
void yaoocpp_struct_dtor(pointer __pthis__)
{
yaoocpp_struct_pointer this=__pthis__;(void)this;

deletep(&this->default_ctor_,yaoocpp_default_constructor);
deletep(&this->dtor_,yaoocpp_destructor);
deletep(&this->copy_ctor_,yaoocpp_copy_constructor);
deletep(&this->assign_,yaoocpp_assignment);
deletep(&this->rich_compare_,yaoocpp_rich_compare);
deletep(&this->to_stream_,yaoocpp_to_stream);
deletep(&this->from_stream_,yaoocpp_from_stream);
deletep(&this->constructors_,yaoocpp_item_pointer_vector);
deletep(&this->instance_,yaoocpp_item_pointer_vector);
deletep(&this->adjunct_,yaoocpp_item_pointer_vector);
deletep(&this->private_,yaoocpp_item_pointer_vector);
deletep(&this->mixins_,yaooc_string_vector);

}
void yaoocpp_struct_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaoocpp_struct_pointer this=__pthis__;(void)this;
yaoocpp_struct_const_pointer src=__psrc__;(void)src;

call_default_ctor_static(this,yaoocpp_struct);
assign_static(this,src,yaoocpp_struct);


}
void yaoocpp_struct_assign(pointer __pthis__,const_pointer __psrc__)
{
yaoocpp_struct_pointer this=__pthis__;(void)this;
yaoocpp_struct_const_pointer src=__psrc__;(void)src;

assign_static(this,src,yaoocpp_section);
this->parent_=src->parent_;
assign_static(&this->default_ctor_,&src->default_ctor_,yaoocpp_default_constructor);
assign_static(&this->dtor_,&src->dtor_,yaoocpp_destructor);
assign_static(&this->copy_ctor_,&src->copy_ctor_,yaoocpp_copy_constructor);
assign_static(&this->assign_,&src->assign_,yaoocpp_assignment);
assign_static(&this->rich_compare_,&src->rich_compare_,yaoocpp_rich_compare);
assign_static(&this->to_stream_,&src->to_stream_,yaoocpp_to_stream);
assign_static(&this->from_stream_,&src->from_stream_,yaoocpp_from_stream);
assign_static(&this->constructors_,&src->constructors_,yaoocpp_item_pointer_vector);
assign_static(&this->instance_,&src->instance_,yaoocpp_item_pointer_vector);
assign_static(&this->adjunct_,&src->adjunct_,yaoocpp_item_pointer_vector);
assign_static(&this->private_,&src->private_,yaoocpp_item_pointer_vector);
assign_static(&this->mixins_,&src->mixins_,yaooc_string_vector);

}
const type_info_t __yaoocpp_struct_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaoocpp_struct_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaoocpp_struct_default_ctor,
.dtor_=yaoocpp_struct_dtor,
.copy_ctor_=yaoocpp_struct_copy_ctor,
.assign_=yaoocpp_struct_assign,
.class_table_=(const class_table_t*) &yaoocpp_struct_class_table,
.parent_=&__yaoocpp_section_ti
};
const type_info_t* const yaoocpp_struct_ti=&__yaoocpp_struct_ti;
void yaoocpp_class_print_class_definition(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_class_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;



      M(ostrm,printf,"yaooc_class_table(%s) {\n",M(&this->name_,c_str));
      if(this->parent_)
        M(ostrm,printf,"  %s_class_table_t;\n",M(&this->parent_->name_,c_str));
      yaoocpp_item_pointer_vector_const_iterator iter;
      CFOR_EACH(iter,&this->table_) {
        yaoocpp_member_item_t* mitem = (yaoocpp_member_item_t*)iter->ptr_;
        if(mitem->generation_==INITIAL) {
          M(mitem,print_table_definition,ostrm,M(&this->name_,c_str),(this->parent_ ? M(&this->parent_->name_,c_str) : NULL ));
        }
      }


      M(ostrm,printf,"};\n");
      if(this->parent_)
        M(ostrm,printf,"#define %s_parent_class_table ((%s_class_table_t*)(%s_class_table.parent_class_table_))\n",
              M(&this->name_,c_str),M(&(((yaoocpp_class_t*)(this->parent_))->name_),c_str),M(&this->name_,c_str));


      if(M(&this->instance_,size)>0) {
        M(ostrm,printf,"\nyaooc_class_instance(%s) {\n",M(&this->name_,c_str));
        if(this->parent_ && M(&((yaoocpp_class_t*)(this->parent_))->instance_,size) > 0)
          M(ostrm,printf,"  %s_class_instance_t;\n",M(&this->parent_->name_,c_str));
        CFOR_EACH(iter,&this->instance_) {
          yaoocpp_member_item_t* mitem = (yaoocpp_member_item_t*)iter->ptr_;
          if((mitem)->generation_==INITIAL)
            M(mitem,print_table_definition,ostrm,M(&this->name_,c_str),(this->parent_ ? M(&this->parent_->name_,c_str) : NULL ));
        }
        M(ostrm,printf,"};\n\n");
        M(ostrm,printf,"yaooc_class(%s);\n",M(&this->name_,c_str));
      } else {
        M(ostrm,printf,"yaooc_class_without_instance(%s);\n",M(&this->name_,c_str));
      }
    
}
void yaoocpp_class_print_class_table_prototypes(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_class_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_item_pointer_vector_const_iterator i;
      CFOR_EACH(i,&this->table_){
        yaoocpp_member_item_const_pointer item=(yaoocpp_member_item_const_pointer)i->ptr_;
        if(ISA(item,yaoocpp_method))
          M(item,print_adjunct_prototype,ostrm,M(&this->name_,c_str),(this->parent_ ? M(&this->parent_->name_,c_str) : NULL ));
      }
    
}
void yaoocpp_class_print_table_method_implementation(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_class_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_item_pointer_vector_const_iterator iter;

      CFOR_EACH(iter,&this->table_) {
        yaoocpp_member_item_t* mitem = (yaoocpp_member_item_t*)iter->ptr_;
        if(ISA(mitem,yaoocpp_method) && mitem->generation_!=INHERITED)
          M(mitem,print_table_implementation,ostrm,M(&this->name_,c_str),this->parent_ ? M(&this->parent_->name_,c_str):NULL );
      }
    
}
void yaoocpp_class_print_class_table_implementation(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_class_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      M(ostrm,printf,"%s_class_table_t %s_class_table ={\n",M(&this->name_,c_str),M(&this->name_,c_str));
      yaoocpp_item_pointer_vector_const_iterator i;
      CFOR_EACH(i,&this->table_) {
        yaoocpp_member_item_const_pointer mitem=(yaoocpp_member_item_const_pointer)i->ptr_;
        M(mitem,print_class_table_entry,ostrm,M(&this->name_,c_str),NULL);
      }
      M(ostrm,printf,"};\n");
    
}
void yaoocpp_class_print_type_info_declaration(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_class_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      const char* class_name=M(&this->name_,c_str);
      const char* parent_class_name = this->parent_ ? M(&this->parent_->name_,c_str) : NULL;
      M(ostrm,printf,"const type_info_t __%s_ti = {\n"
          ".min_flag_=0,\n"
          ".pod_flag_=0,\n"
          ".type_size_=sizeof(%s_t),\n",class_name,class_name);
      yaoocpp_rich_compare_print_type_info_entry(&this->rich_compare_,ostrm);
      yaoocpp_to_stream_print_type_info_entry(&this->to_stream_,ostrm);
      yaoocpp_from_stream_print_type_info_entry(&this->from_stream_,ostrm);
      yaoocpp_default_constructor_print_type_info_entry(&this->default_ctor_,ostrm);
      yaoocpp_destructor_print_type_info_entry(&this->dtor_,ostrm);
      yaoocpp_copy_constructor_print_type_info_entry(&this->copy_ctor_,ostrm);
      yaoocpp_assignment_print_type_info_entry(&this->assign_,ostrm);
      M(ostrm,printf,".class_table_=(const class_table_t*) &%s_class_table,\n",class_name);
      M(ostrm,printf,".parent_=");
      if(parent_class_name)
        M(ostrm,printf,"&__%s_ti\n",parent_class_name);
      else
        M(ostrm,printf,"NULL\n");
      M(ostrm,printf,"};\nconst type_info_t* const %s_ti=&__%s_ti;\n",class_name,class_name);
    
}
void yaoocpp_class_print_to_header(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_class_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_class_parent_class_table->print_to_header(this,ostrm)
#define PM(method,...) CTM((*yaoocpp_class_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_class_print_class_definition(this,ostrm);
      yaoocpp_struct_print_type_info_definition(this,ostrm);
      yaoocpp_struct_print_constructor_prototypes(this,ostrm);
      yaoocpp_class_print_class_table_prototypes(this,ostrm);
      yaoocpp_struct_print_adjunct_prototypes(this,ostrm);
    
#undef PM
#undef super
}
void yaoocpp_class_print_to_source(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_class_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_class_parent_class_table->print_to_source(this,ostrm)
#define PM(method,...) CTM((*yaoocpp_class_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_struct_print_private_variable_implementation(this,ostrm);
      yaoocpp_struct_print_private_method_prototypes(this,ostrm);
      yaoocpp_struct_print_private_method_implementation(this,ostrm);
      yaoocpp_struct_print_type_info_implementation(this,ostrm);
      yaoocpp_struct_print_constructor_implementation(this,ostrm);
      yaoocpp_struct_print_adjunct_implementation(this,ostrm);
      yaoocpp_class_print_table_method_implementation(this,ostrm);
      yaoocpp_class_print_class_table_implementation(this,ostrm);
      yaoocpp_class_print_type_info_declaration(this,ostrm);
    
#undef PM
#undef super
}
void yaoocpp_class_print_to_yod(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_class_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_class_parent_class_table->print_to_yod(this,ostrm)
#define PM(method,...) CTM((*yaoocpp_class_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      M(ostrm,printf,"%%class %s {\n",M(&this->name_,c_str));
      yaoocpp_default_constructor_print_yod_definition(&this->default_ctor_,ostrm,false);
      yaoocpp_destructor_print_yod_definition(&this->dtor_,ostrm,false);
      yaoocpp_copy_constructor_print_yod_definition(&this->copy_ctor_,ostrm,false);
      yaoocpp_assignment_print_yod_definition(&this->assign_,ostrm,false);
      M(ostrm,printf,"instance:\n");
      const yaoocpp_member_item_t* const* i;
      CFOR_EACH(i,&this->instance_) {
        M(*i,print_yod_definition,ostrm,false);
      }
      M(ostrm,printf,"table:\n");
      CFOR_EACH(i,&this->table_) {
        M(*i,print_yod_definition,ostrm,false);
      }
      M(ostrm,printf,"};\n");
    
#undef PM
#undef super
}
void yaoocpp_class_add_mixins(pointer __pthis__,yaoocpp_item_pointer_vector_const_pointer mixins)
{
yaoocpp_class_pointer this=__pthis__;(void)this;
#define super() yaoocpp_class_parent_class_table->add_mixins(this,mixins)
#define PM(method,...) CTM((*yaoocpp_class_parent_class_table),this,method,## __VA_ARGS__)


      yaoocpp_struct_add_mixins(this,mixins);
      gb_init();
      yaooc_string_vector_const_iterator imix;
      CFOR_EACH(imix,&this->mixins_) {
        yaoocpp_item_t* temp = gb_new(yaoocpp_item);
        M(&temp->name_,set,M(imix,c_str));
        yaoocpp_mixin_const_pointer* mixin = yaooc_find(yaooc_dynamic_pointer,M(mixins,cbegin),M(mixins,cend),make_dynamic_pointer(temp));
        if(mixin == M(mixins,cend)) {
          printf("Mixin %s not defined\n",M(&temp->name_,c_str));
          exit(33);
        }
        yaoocpp_struct_add_mixin_members(this,&this->table_,&(*mixin)->table_,false);
      }
      gb_exit();
    
#undef PM
#undef super
}
void yaoocpp_class_inherit(pointer __pthis__)
{
yaoocpp_class_pointer this=__pthis__;(void)this;
#define super() yaoocpp_class_parent_class_table->inherit(this)
#define PM(method,...) CTM((*yaoocpp_class_parent_class_table),this,method,## __VA_ARGS__)


      if(this->parent_) {
        super();
        yaoocpp_class_t* p=(yaoocpp_class_pointer)this->parent_;
        assign_static(&this->table_,&p->table_,yaoocpp_item_pointer_vector);
        const char* parent_name=M(&p->name_,c_str);
        yaoocpp_item_pointer_vector_iterator i;
        FOR_EACH(i,&this->table_) {
          ((yaoocpp_member_item_pointer)i->ptr_)->generation_=INHERITED;
          if(ISA(i->ptr_,yaoocpp_method)) {
            yaoocpp_method_pointer method=(yaoocpp_method_pointer)i->ptr_;
            if(strcmp(M(&method->implementation_,c_str),"0")!=0) {
              char temp[256];
              sprintf(temp,"%s_%s",parent_name,M(&method->name_,c_str));
              M(method,set_implemented_as,temp,strlen(temp));
            }
          } else {
            yaoocpp_variable_pointer var=(yaoocpp_variable_pointer)i->ptr_;
            if(strcmp(M(&var->name_,c_str),"parent_class_table_")==0) {
              M(&var->value_,set,"&");
              M(&var->value_,append,M(&p->name_,c_str));
              M(&var->value_,append,"_class_table");
            } else if(strcmp(M(&var->name_,c_str),"type_name_")==0) {
              M(&var->value_,set,"\"");
              M(&var->value_,append,M(&this->name_,c_str));
              M(&var->value_,append,"_t\"");
            }
          }
        }
      }
    
#undef PM
#undef super
}
yaoocpp_class_class_table_t yaoocpp_class_class_table ={
.parent_class_table_ = (const class_table_t*) &yaoocpp_struct_class_table,
.type_name_ = (const char*) "yaoocpp_class_t",
.swap = (void(*)(pointer,pointer)) yaoocpp_class_swap,
.set_line_no = (void(*)(pointer,int)) yaoocpp_class_set_line_no,
.print_to_header = (void(*)(const_pointer,ostream_pointer)) yaoocpp_class_print_to_header,
.print_to_source = (void(*)(const_pointer,ostream_pointer)) yaoocpp_class_print_to_source,
.print_to_yod = (void(*)(const_pointer,ostream_pointer)) yaoocpp_class_print_to_yod,
.resolve = (void(*)(pointer,const char*,const char*,yaoocpp_item_pointer_vector_const_pointer)) yaoocpp_class_resolve,
.add_mixins = (void(*)(pointer,yaoocpp_item_pointer_vector_const_pointer)) yaoocpp_class_add_mixins,
.inherit = (void(*)(pointer)) yaoocpp_class_inherit,
.resolve_outstanding_components = (void(*)(pointer)) yaoocpp_class_resolve_outstanding_components,
.get_new_instance_variables = (yaoocpp_item_pointer_vector_t*(*)(const_pointer)) yaoocpp_class_get_new_instance_variables,
.is_pod = (bool(*)(const_pointer)) yaoocpp_class_is_pod,
.is_min_pod = (bool(*)(const_pointer)) yaoocpp_class_is_min_pod,
};
void yaoocpp_class_default_ctor(pointer __pthis__)
{
yaoocpp_class_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaoocpp_class);


newp(&this->table_,yaoocpp_item_pointer_vector);

}
void yaoocpp_class_dtor(pointer __pthis__)
{
yaoocpp_class_pointer this=__pthis__;(void)this;

deletep(&this->table_,yaoocpp_item_pointer_vector);

}
void yaoocpp_class_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaoocpp_class_pointer this=__pthis__;(void)this;
yaoocpp_class_const_pointer src=__psrc__;(void)src;

call_default_ctor_static(this,yaoocpp_class);
assign_static(this,src,yaoocpp_class);


}
void yaoocpp_class_assign(pointer __pthis__,const_pointer __psrc__)
{
yaoocpp_class_pointer this=__pthis__;(void)this;
yaoocpp_class_const_pointer src=__psrc__;(void)src;

assign_static(this,src,yaoocpp_struct);
assign_static(&this->table_,&src->table_,yaoocpp_item_pointer_vector);

}
const type_info_t __yaoocpp_class_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaoocpp_class_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaoocpp_class_default_ctor,
.dtor_=yaoocpp_class_dtor,
.copy_ctor_=yaoocpp_class_copy_ctor,
.assign_=yaoocpp_class_assign,
.class_table_=(const class_table_t*) &yaoocpp_class_class_table,
.parent_=&__yaoocpp_struct_ti
};
const type_info_t* const yaoocpp_class_ti=&__yaoocpp_class_ti;
void yaoocpp_union_print_to_header(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_union_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_union_parent_class_table->print_to_header(this,ostrm)
#define PM(method,...) CTM((*yaoocpp_union_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      yaoocpp_union_print_class_definition(this,ostrm);
      yaoocpp_struct_print_type_info_definition(this,ostrm);
      yaoocpp_struct_print_constructor_prototypes(this,ostrm);
      yaoocpp_class_print_class_table_prototypes(this,ostrm);
      yaoocpp_struct_print_adjunct_prototypes(this,ostrm);
    
#undef PM
#undef super
}
void yaoocpp_union_print_class_definition(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_union_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_union_parent_class_table->print_class_definition(this,ostrm)
#define PM(method,...) CTM((*yaoocpp_union_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;



      M(ostrm,printf,"yaooc_union_table(%s) {\n",M(&this->name_,c_str));
      if(this->parent_)
        M(ostrm,printf,"  %s_class_table_t;\n",M(&this->parent_->name_,c_str));
      yaoocpp_item_pointer_vector_const_iterator iter;
      CFOR_EACH(iter,&this->table_) {
        yaoocpp_member_item_t* mitem = (yaoocpp_member_item_t*)iter->ptr_;
        if(mitem->generation_==INITIAL) {
          M(mitem,print_table_definition,ostrm,M(&this->name_,c_str),(this->parent_ ? M(&this->parent_->name_,c_str) : NULL ));
        }
      }


      M(ostrm,printf,"};\n");
      if(this->parent_)
        M(ostrm,printf,"#define %s_parent_class_table ((%s_class_table_t*)(%s_class_table.parent_class_table_))\n",
              M(&this->name_,c_str),M(&(((yaoocpp_class_t*)(this->parent_))->name_),c_str),M(&this->name_,c_str));


      if(M(&this->instance_,size)>0) {
        M(ostrm,printf,"\nyaooc_union_instance(%s) {\n",M(&this->name_,c_str));
        if(this->parent_ && M(&((yaoocpp_class_t*)(this->parent_))->instance_,size) > 0)
          M(ostrm,printf,"  %s_class_instance_t;\n",M(&this->parent_->name_,c_str));
        CFOR_EACH(iter,&this->instance_) {
          yaoocpp_member_item_t* mitem = (yaoocpp_member_item_t*)iter->ptr_;
          if((mitem)->generation_==INITIAL)
            M(mitem,print_table_definition,ostrm,M(&this->name_,c_str),(this->parent_ ? M(&this->parent_->name_,c_str) : NULL ));
        }
        M(ostrm,printf,"};\n");
        M(ostrm,printf,"yaooc_union(%s);\n",M(&this->name_,c_str));
      } else {

        M(ostrm,printf,"yaooc_union_without_instance(%s);\n\n",M(&this->name_,c_str));
      }
    
#undef PM
#undef super
}
yaoocpp_union_class_table_t yaoocpp_union_class_table ={
.parent_class_table_ = (const class_table_t*) &yaoocpp_class_class_table,
.type_name_ = (const char*) "yaoocpp_union_t",
.swap = (void(*)(pointer,pointer)) yaoocpp_union_swap,
.set_line_no = (void(*)(pointer,int)) yaoocpp_union_set_line_no,
.print_to_header = (void(*)(const_pointer,ostream_pointer)) yaoocpp_union_print_to_header,
.print_to_source = (void(*)(const_pointer,ostream_pointer)) yaoocpp_union_print_to_source,
.print_to_yod = (void(*)(const_pointer,ostream_pointer)) yaoocpp_union_print_to_yod,
.resolve = (void(*)(pointer,const char*,const char*,yaoocpp_item_pointer_vector_const_pointer)) yaoocpp_union_resolve,
.add_mixins = (void(*)(pointer,yaoocpp_item_pointer_vector_const_pointer)) yaoocpp_union_add_mixins,
.inherit = (void(*)(pointer)) yaoocpp_union_inherit,
.resolve_outstanding_components = (void(*)(pointer)) yaoocpp_union_resolve_outstanding_components,
.get_new_instance_variables = (yaoocpp_item_pointer_vector_t*(*)(const_pointer)) yaoocpp_union_get_new_instance_variables,
.is_pod = (bool(*)(const_pointer)) yaoocpp_union_is_pod,
.is_min_pod = (bool(*)(const_pointer)) yaoocpp_union_is_min_pod,
.print_class_definition = (void(*)(const_pointer,ostream_pointer)) yaoocpp_union_print_class_definition,
};
const type_info_t __yaoocpp_union_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaoocpp_union_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=NULL,
.dtor_=NULL,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaoocpp_union_class_table,
.parent_=&__yaoocpp_class_ti
};
const type_info_t* const yaoocpp_union_ti=&__yaoocpp_union_ti;
void yaoocpp_mixin_print_to_header(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_mixin_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_mixin_parent_class_table->print_to_header(this,ostrm)
#define PM(method,...) CTM((*yaoocpp_mixin_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


    
#undef PM
#undef super
}
void yaoocpp_mixin_print_to_source(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_mixin_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_mixin_parent_class_table->print_to_source(this,ostrm)
#define PM(method,...) CTM((*yaoocpp_mixin_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


    
#undef PM
#undef super
}
void yaoocpp_mixin_print_to_yod(const_pointer __pthis__,ostream_pointer __postrm)
{
yaoocpp_mixin_const_pointer this=__pthis__;(void)this;
#define super() yaoocpp_mixin_parent_class_table->print_to_yod(this,ostrm)
#define PM(method,...) CTM((*yaoocpp_mixin_parent_class_table),this,method,## __VA_ARGS__)

yaooc_ostream_pointer ostrm=__postrm;(void)ostrm;


      M(ostrm,printf,"%%mixin %s {\n",M(&this->name_,c_str));
      yaoocpp_default_constructor_print_yod_definition(&this->default_ctor_,ostrm,true);
      yaoocpp_destructor_print_yod_definition(&this->dtor_,ostrm,true);
      yaoocpp_copy_constructor_print_yod_definition(&this->copy_ctor_,ostrm,true);
      yaoocpp_assignment_print_yod_definition(&this->assign_,ostrm,true);
      M(ostrm,printf,"instance:\n");
      const yaoocpp_member_item_t* const* i;
      CFOR_EACH(i,&this->instance_) {
        M(*i,print_yod_definition,ostrm,false);
      }
      M(ostrm,printf,"table:\n");
      CFOR_EACH(i,&this->table_) {
        M(*i,print_yod_definition,ostrm,true);
      }
      M(ostrm,printf,"};\n");
    
#undef PM
#undef super
}
yaoocpp_mixin_class_table_t yaoocpp_mixin_class_table ={
.parent_class_table_ = (const class_table_t*) &yaoocpp_class_class_table,
.type_name_ = (const char*) "yaoocpp_mixin_t",
.swap = (void(*)(pointer,pointer)) yaoocpp_mixin_swap,
.set_line_no = (void(*)(pointer,int)) yaoocpp_mixin_set_line_no,
.print_to_header = (void(*)(const_pointer,ostream_pointer)) yaoocpp_mixin_print_to_header,
.print_to_source = (void(*)(const_pointer,ostream_pointer)) yaoocpp_mixin_print_to_source,
.print_to_yod = (void(*)(const_pointer,ostream_pointer)) yaoocpp_mixin_print_to_yod,
.resolve = (void(*)(pointer,const char*,const char*,yaoocpp_item_pointer_vector_const_pointer)) yaoocpp_mixin_resolve,
.add_mixins = (void(*)(pointer,yaoocpp_item_pointer_vector_const_pointer)) yaoocpp_mixin_add_mixins,
.inherit = (void(*)(pointer)) yaoocpp_mixin_inherit,
.resolve_outstanding_components = (void(*)(pointer)) yaoocpp_mixin_resolve_outstanding_components,
.get_new_instance_variables = (yaoocpp_item_pointer_vector_t*(*)(const_pointer)) yaoocpp_mixin_get_new_instance_variables,
.is_pod = (bool(*)(const_pointer)) yaoocpp_mixin_is_pod,
.is_min_pod = (bool(*)(const_pointer)) yaoocpp_mixin_is_min_pod,
};
const type_info_t __yaoocpp_mixin_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaoocpp_mixin_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=NULL,
.dtor_=NULL,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaoocpp_mixin_class_table,
.parent_=&__yaoocpp_class_ti
};
const type_info_t* const yaoocpp_mixin_ti=&__yaoocpp_mixin_ti;
