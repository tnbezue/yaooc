#ifndef __FILE_INCLUDED__
#define __FILE_INCLUDED__

#include <yaooc/object.h>
#include <yaooc/stream.h>
#include <fcntl.h>
#ifdef _WIN32
typedef short nlink_t;
#endif

yaooc_class_table(yaooc_file) {
  yaooc_object_class_table_t;
bool (*exists)(const_pointer);
dev_t (*dev)(const_pointer);
mode_t (*mode)(const_pointer);
time_t (*atime)(const_pointer);
time_t (*mtime)(const_pointer);
time_t (*ctime)(const_pointer);
uid_t (*uid)(const_pointer);
gid_t (*gid)(const_pointer);
nlink_t (*nlink)(const_pointer);
size_t (*size)(const_pointer);
bool (*isdir)(const_pointer);
bool (*ischr)(const_pointer);
bool (*isblk)(const_pointer);
bool (*isreg)(const_pointer);
bool (*isfile)(const_pointer);
bool (*islink)(const_pointer);
bool (*issock)(const_pointer);
};
#define yaooc_file_parent_class_table ((yaooc_object_class_table_t*)(yaooc_file_class_table.parent_class_table_))

yaooc_class_instance(yaooc_file) {
char* file_;
};

yaooc_class(yaooc_file);
void yaooc_file_default_ctor(pointer);
void yaooc_file_dtor(pointer);
void yaooc_file_copy_ctor(pointer,const_pointer);
void yaooc_file_assign(pointer,const_pointer);
void yaooc_file_ctor_name(pointer,va_list);
 void yaooc_file_swap(pointer,pointer);
 bool yaooc_file_exists(const_pointer);
 dev_t yaooc_file_dev(const_pointer);
 mode_t yaooc_file_mode(const_pointer);
 time_t yaooc_file_atime(const_pointer);
 time_t yaooc_file_mtime(const_pointer);
 time_t yaooc_file_ctime(const_pointer);
 uid_t yaooc_file_uid(const_pointer);
 gid_t yaooc_file_gid(const_pointer);
 nlink_t yaooc_file_nlink(const_pointer);
 size_t yaooc_file_size(const_pointer);
 bool yaooc_file_isdir(const_pointer);
 bool yaooc_file_ischr(const_pointer);
 bool yaooc_file_isblk(const_pointer);
 bool yaooc_file_isreg(const_pointer);
 bool yaooc_file_isfile(const_pointer);
 bool yaooc_file_islink(const_pointer);
 bool yaooc_file_issock(const_pointer);

#endif
