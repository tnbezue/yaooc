#include <yaooc/file.h>
#include <string.h>
#include <sys/stat.h>


void yaooc_file_default_ctor(pointer __pthis__)
{
yaooc_file_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_file);


this->file_=NULL;

}
void yaooc_file_dtor(pointer __pthis__)
{
yaooc_file_pointer this=__pthis__;(void)this;

if(this->file_!=NULL) delete(this->file_);

}
void yaooc_file_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaooc_file_pointer this=__pthis__;(void)this;
yaooc_file_const_pointer src=__psrc__;(void)src;


call_default_ctor_static(this,yaooc_file);
assign_static(this,src,yaooc_file);

}
void yaooc_file_assign(pointer __pthis__,const_pointer __psrc__)
{
yaooc_file_pointer this=__pthis__;(void)this;
yaooc_file_const_pointer src=__psrc__;(void)src;


      yaooc_file_dtor(this);
      this->file_ = src->file_ ? STRDUP(src->file_) : NULL;
    
}
void yaooc_file_ctor_name(pointer __pthis,va_list __con_args__){
yaooc_file_pointer this=__pthis;(void)this;
const char* fname = va_arg(__con_args__,const char*);

call_parent_default_ctor_static(this,yaooc_file);
this->file_=STRDUP(fname);


    
}
void yaooc_file_swap(pointer __pthis__,pointer o)
{
yaooc_file_pointer this=__pthis__;(void)this;
#define super() yaooc_file_parent_class_table->swap(this,o)
#define PM(method,...) CTM((*yaooc_file_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_file_pointer other=o;
      SWAP(char*,this->file_,other->file_);
    
#undef PM
#undef super
}
bool yaooc_file_exists(const_pointer __pthis__)
{
yaooc_file_const_pointer this=__pthis__;(void)this;
#define super() yaooc_file_parent_class_table->exists(this)
#define PM(method,...) CTM((*yaooc_file_parent_class_table),this,method,## __VA_ARGS__)


      if(this->file_)
        return access(this->file_,0);
      return false;
    
#undef PM
#undef super
}
dev_t yaooc_file_dev(const_pointer __pthis__)
{
yaooc_file_const_pointer this=__pthis__;(void)this;
#define super() yaooc_file_parent_class_table->dev(this)
#define PM(method,...) CTM((*yaooc_file_parent_class_table),this,method,## __VA_ARGS__)


      if(this->file_) {
        struct stat st;
        if(stat(this->file_,&st) == 0)
          return st.st_dev;
      }
      return 0;
    
#undef PM
#undef super
}
mode_t yaooc_file_mode(const_pointer __pthis__)
{
yaooc_file_const_pointer this=__pthis__;(void)this;
#define super() yaooc_file_parent_class_table->mode(this)
#define PM(method,...) CTM((*yaooc_file_parent_class_table),this,method,## __VA_ARGS__)


      if(this->file_) {
        struct stat st;
        if(stat(this->file_,&st) == 0)
          return st.st_mode;
      }
      return 0;
    
#undef PM
#undef super
}
time_t yaooc_file_atime(const_pointer __pthis__)
{
yaooc_file_const_pointer this=__pthis__;(void)this;
#define super() yaooc_file_parent_class_table->atime(this)
#define PM(method,...) CTM((*yaooc_file_parent_class_table),this,method,## __VA_ARGS__)


      if(this->file_) {
        struct stat st;
        if(stat(this->file_,&st) == 0)
          return st.st_atime;
      }
      return 0;
    
#undef PM
#undef super
}
time_t yaooc_file_mtime(const_pointer __pthis__)
{
yaooc_file_const_pointer this=__pthis__;(void)this;
#define super() yaooc_file_parent_class_table->mtime(this)
#define PM(method,...) CTM((*yaooc_file_parent_class_table),this,method,## __VA_ARGS__)


      if(this->file_) {
        struct stat st;
        if(stat(this->file_,&st) == 0)
          return st.st_mtime;
      }
      return 0;
    
#undef PM
#undef super
}
time_t yaooc_file_ctime(const_pointer __pthis__)
{
yaooc_file_const_pointer this=__pthis__;(void)this;
#define super() yaooc_file_parent_class_table->ctime(this)
#define PM(method,...) CTM((*yaooc_file_parent_class_table),this,method,## __VA_ARGS__)


      if(this->file_) {
        struct stat st;
        if(stat(this->file_,&st) == 0)
          return st.st_ctime;
      }
      return 0;
    
#undef PM
#undef super
}
uid_t yaooc_file_uid(const_pointer __pthis__)
{
yaooc_file_const_pointer this=__pthis__;(void)this;
#define super() yaooc_file_parent_class_table->uid(this)
#define PM(method,...) CTM((*yaooc_file_parent_class_table),this,method,## __VA_ARGS__)


      if(this->file_) {
        struct stat st;
        if(stat(this->file_,&st) == 0)
          return st.st_uid;
      }
      return 0;
    
#undef PM
#undef super
}
gid_t yaooc_file_gid(const_pointer __pthis__)
{
yaooc_file_const_pointer this=__pthis__;(void)this;
#define super() yaooc_file_parent_class_table->gid(this)
#define PM(method,...) CTM((*yaooc_file_parent_class_table),this,method,## __VA_ARGS__)


      if(this->file_) {
        struct stat st;
        if(stat(this->file_,&st) == 0)
          return st.st_gid;
      }
      return 0;
    
#undef PM
#undef super
}
nlink_t yaooc_file_nlink(const_pointer __pthis__)
{
yaooc_file_const_pointer this=__pthis__;(void)this;
#define super() yaooc_file_parent_class_table->nlink(this)
#define PM(method,...) CTM((*yaooc_file_parent_class_table),this,method,## __VA_ARGS__)


      if(this->file_) {
        struct stat st;
        if(stat(this->file_,&st) == 0)
          return st.st_nlink;
      }
      return 0;
    
#undef PM
#undef super
}
size_t yaooc_file_size(const_pointer __pthis__)
{
yaooc_file_const_pointer this=__pthis__;(void)this;
#define super() yaooc_file_parent_class_table->size(this)
#define PM(method,...) CTM((*yaooc_file_parent_class_table),this,method,## __VA_ARGS__)


      if(this->file_) {
        struct stat st;
        if(stat(this->file_,&st) == 0)
          return st.st_size;
      }
      return 0;
    
#undef PM
#undef super
}
bool yaooc_file_isdir(const_pointer __pthis__)
{
yaooc_file_const_pointer this=__pthis__;(void)this;
#define super() yaooc_file_parent_class_table->isdir(this)
#define PM(method,...) CTM((*yaooc_file_parent_class_table),this,method,## __VA_ARGS__)


      if(this->file_) {
        struct stat st;
        if(stat(this->file_,&st) == 0)
          return S_ISDIR(st.st_mode);
      }
      return false;
    
#undef PM
#undef super
}
bool yaooc_file_ischr(const_pointer __pthis__)
{
yaooc_file_const_pointer this=__pthis__;(void)this;
#define super() yaooc_file_parent_class_table->ischr(this)
#define PM(method,...) CTM((*yaooc_file_parent_class_table),this,method,## __VA_ARGS__)


      if(this->file_) {
        struct stat st;
        if(stat(this->file_,&st) == 0)
          return S_ISCHR(st.st_mode);
      }
      return false;
    
#undef PM
#undef super
}
bool yaooc_file_isblk(const_pointer __pthis__)
{
yaooc_file_const_pointer this=__pthis__;(void)this;
#define super() yaooc_file_parent_class_table->isblk(this)
#define PM(method,...) CTM((*yaooc_file_parent_class_table),this,method,## __VA_ARGS__)


      if(this->file_) {
        struct stat st;
        if(stat(this->file_,&st) == 0)
          return S_ISBLK(st.st_mode);
      }
      return false;
    
#undef PM
#undef super
}
bool yaooc_file_isreg(const_pointer __pthis__)
{
yaooc_file_const_pointer this=__pthis__;(void)this;
#define super() yaooc_file_parent_class_table->isreg(this)
#define PM(method,...) CTM((*yaooc_file_parent_class_table),this,method,## __VA_ARGS__)


      if(this->file_) {
        struct stat st;
        if(stat(this->file_,&st) == 0)
          return S_ISREG(st.st_mode);
      }
      return false;
    
#undef PM
#undef super
}
bool yaooc_file_isfile(const_pointer __pthis__)
{
yaooc_file_const_pointer this=__pthis__;(void)this;
#define super() yaooc_file_parent_class_table->isfile(this)
#define PM(method,...) CTM((*yaooc_file_parent_class_table),this,method,## __VA_ARGS__)


      if(this->file_) {
        struct stat st;
        if(stat(this->file_,&st) == 0)
          return S_ISFIFO(st.st_mode);
      }
      return false;
    
#undef PM
#undef super
}
bool yaooc_file_islink(const_pointer __pthis__)
{
yaooc_file_const_pointer this=__pthis__;(void)this;
#define super() yaooc_file_parent_class_table->islink(this)
#define PM(method,...) CTM((*yaooc_file_parent_class_table),this,method,## __VA_ARGS__)


#ifdef WIN32_
      return false;
#else
      if(this->file_) {
        struct stat st;
        if(stat(this->file_,&st) == 0)
          return S_ISLNK(st.st_mode);
      }
      return false;
#endif
    
#undef PM
#undef super
}
bool yaooc_file_issock(const_pointer __pthis__)
{
yaooc_file_const_pointer this=__pthis__;(void)this;
#define super() yaooc_file_parent_class_table->issock(this)
#define PM(method,...) CTM((*yaooc_file_parent_class_table),this,method,## __VA_ARGS__)


#ifdef WIN32_
      return false;
#else
      if(this->file_) {
        struct stat st;
        if(stat(this->file_,&st) == 0)
          return st.st_mode & __S_IFSOCK;
      }
      return false;
#endif
    
#undef PM
#undef super
}
yaooc_file_class_table_t yaooc_file_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_object_class_table,
.type_name_ = (const char*)"yaooc_file_t",
.swap = (void(*)(pointer,pointer)) yaooc_file_swap,
.exists = (bool(*)(const_pointer)) yaooc_file_exists,
.dev = (dev_t(*)(const_pointer)) yaooc_file_dev,
.mode = (mode_t(*)(const_pointer)) yaooc_file_mode,
.atime = (time_t(*)(const_pointer)) yaooc_file_atime,
.mtime = (time_t(*)(const_pointer)) yaooc_file_mtime,
.ctime = (time_t(*)(const_pointer)) yaooc_file_ctime,
.uid = (uid_t(*)(const_pointer)) yaooc_file_uid,
.gid = (gid_t(*)(const_pointer)) yaooc_file_gid,
.nlink = (nlink_t(*)(const_pointer)) yaooc_file_nlink,
.size = (size_t(*)(const_pointer)) yaooc_file_size,
.isdir = (bool(*)(const_pointer)) yaooc_file_isdir,
.ischr = (bool(*)(const_pointer)) yaooc_file_ischr,
.isblk = (bool(*)(const_pointer)) yaooc_file_isblk,
.isreg = (bool(*)(const_pointer)) yaooc_file_isreg,
.isfile = (bool(*)(const_pointer)) yaooc_file_isfile,
.islink = (bool(*)(const_pointer)) yaooc_file_islink,
.issock = (bool(*)(const_pointer)) yaooc_file_issock,
};
const type_info_t __yaooc_file_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_file_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaooc_file_default_ctor,
.dtor_=yaooc_file_dtor,
.copy_ctor_=yaooc_file_copy_ctor,
.assign_=yaooc_file_assign,
.class_table_=(const class_table_t*) &yaooc_file_class_table,
.parent_=&__yaooc_object_ti
};
const type_info_t* const yaooc_file_ti=&__yaooc_file_ti;
