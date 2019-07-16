/*
		Copyright (C) 2016-2019  by Terry N Bezue

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
#ifndef __YAOOC_FILE_INCLUDED__
#define __YAOOC_FILE_INCLUDED__

/* Begin YAOOCPP output */

#include <yaooc/object.h>
#include <yaooc/stream.h>
#include <fcntl.h>
#ifdef _WIN32
typedef short nlink_t;
#endif

/*
  Class Definition for yaooc_file
*/
yaooc_class_table(yaooc_file) {
  yaooc_object_class_table_t;
	bool (*exists)(const_pointer);
  dev_t (*dev)(const_pointer);
  mode_t (*mode)(const_pointer);
  time_t (*atime)(const_pointer);
  time_t (*mtime)(const_pointer);
  time_t (*ctime)(const_pointer);
  uid_t (*uid)(const_pointer);
  const char* (*name)(const_pointer);
  gid_t (*gid)(const_pointer);
  nlink_t (*nlink)(const_pointer);
  off_t (*size)(const_pointer);
  bool (*isdir)(const_pointer);
  bool (*ischr)(const_pointer);
  bool (*isblk)(const_pointer);
  bool (*isreg)(const_pointer);
  bool (*isfifo)(const_pointer);
	bool (*islink)(const_pointer);
	bool (*issock)(const_pointer);
};
#define yaooc_file_parent_class_table ((yaooc_object_class_table_t*)(yaooc_file_class_table.parent_class_table_))

yaooc_class_instance(yaooc_file) {
  yaooc_object_class_instance_t;
  struct stat* stat_;
  char* name_;
	int stat_result_;
};

yaooc_class(yaooc_file);

/* Type Info Prototypes for yaooc_file */
void yaooc_file_default_ctor(pointer);
void yaooc_file_dtor(pointer);
void yaooc_file_copy_ctor(pointer,const_pointer);
void yaooc_file_assign(pointer,const_pointer);

/* Constructors prototypes for yaooc_file */
void yaooc_file_ctor_name(pointer,va_list);

/* Table prototypes for yaooc_file */
void yaooc_file_swap(pointer,pointer);
bool yaooc_file_exists(const_pointer);
dev_t yaooc_file_dev(const_pointer);
mode_t yaooc_file_mode(const_pointer);
time_t yaooc_file_atime(const_pointer);
time_t yaooc_file_mtime(const_pointer);
time_t yaooc_file_ctime(const_pointer);
uid_t yaooc_file_uid(const_pointer);
const char* yaooc_file_name(const_pointer);
gid_t yaooc_file_gid(const_pointer);
nlink_t yaooc_file_nlink(const_pointer);
off_t yaooc_file_size(const_pointer);
bool yaooc_file_isdir(const_pointer);
bool yaooc_file_ischr(const_pointer);
bool yaooc_file_isblk(const_pointer);
bool yaooc_file_isreg(const_pointer);
bool yaooc_file_isfifo(const_pointer);
bool yaooc_file_islink(const_pointer);
bool yaooc_file_issock(const_pointer);

/* Protected prototypes for yaooc_file */

/* End YAOOCPP output */

bool yaooc_file_cp(const char*,const char*);
bool yaooc_file_mv(const char*,const char*);
bool yaooc_file_chmod(const char*,uint32_t);
bool yaooc_file_unlink(const char*);
#define yaooc_file_rm yaooc_file_unlink
#define yaooc_file_rename yaooc_file_mv

#endif
