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
/* Begin YAOOCPP output */

#include <yaooc/file.h>
#include <string.h>
#include <sys/stat.h>

/* Private variables implementation for yaooc_file */

/* Private methods prototypes for yaooc_file */
static void yaooc_file_stat(const_pointer);

/* Type Info implemmentation for yaooc_file */
void yaooc_file_default_ctor(pointer p)
{
  yaooc_file_pointer this=p;
  this->stat_ = NULL;
  this->name_ = NULL;
	this->stat_result_=-2;
}

void yaooc_file_dtor(pointer p)
{
  yaooc_file_pointer this=p;
  if(this->name_) {
		FREE(this->name_);
		this->name_ = NULL;
	}
	if(this->stat_) {
		FREE(this->stat_);
		this->stat_=NULL;
		this->stat_result_=-2;
	}
}

void yaooc_file_copy_ctor(pointer p,const_pointer s)
{
  yaooc_file_default_ctor(p);
  yaooc_file_assign(p,s);
}

void yaooc_file_assign(pointer p,const_pointer s)
{
  yaooc_file_pointer this=p;
  yaooc_file_const_pointer src=s;
  this->name_=src->name_ ? strdup(src->name_) : NULL;
}

/* Constructors implementation for yaooc_file */
void yaooc_file_ctor_name(pointer p,va_list args)
{
  yaooc_file_pointer this=p;
	this->name_=strdup(va_arg(args, const char*));
	this->stat_=NULL;
	this->stat_result_=-2;
}


/* Private methods implementation for yaooc_file */
static void yaooc_file_stat(const_pointer p)
{
  yaooc_file_pointer this=(pointer)p;
	if(this->stat_result_ == -2 && this->name_ != NULL) {
		this->stat_=malloc(sizeof(struct stat));
		this->stat_result_ = stat(this->name_,this->stat_);
	}
}
/* Protected implementation for yaooc_file */

/* Table implementation for yaooc_file */

void yaooc_file_swap(pointer p,pointer o)
{
  yaooc_file_pointer this=p;
  yaooc_file_pointer other=o;
	SWAP(struct stat*,this->stat_,other->stat_);
	SWAP(char*,this->name_,other->name_);
	SWAP(int,this->stat_result_,other->stat_result_);
}

bool yaooc_file_exists(const_pointer p)
{
  yaooc_file_const_pointer this=p;
	yaooc_file_stat(this);
	return this->stat_result_==0;
}

dev_t yaooc_file_dev(const_pointer p)
{
  yaooc_file_const_pointer this=p;
	yaooc_file_stat(this);
  return this->stat_result_ == 0 ? this->stat_->st_dev : 0;
}

mode_t yaooc_file_mode(const_pointer p)
{
  yaooc_file_const_pointer this=p;
	yaooc_file_stat(this);
  return this->stat_result_ == 0 ? this->stat_->st_mode : 0;
}

time_t yaooc_file_atime(const_pointer p)
{
  yaooc_file_const_pointer this=p;
	yaooc_file_stat(this);
  return this->stat_result_ == 0 ? this->stat_->st_atime : 0;
}

time_t yaooc_file_mtime(const_pointer p)
{
  yaooc_file_const_pointer this=p;
	yaooc_file_stat(this);
  return this->stat_result_ == 0 ? this->stat_->st_mtime : 0;
}

time_t yaooc_file_ctime(const_pointer p)
{
  yaooc_file_const_pointer this=p;
	yaooc_file_stat(this);
  return this->stat_result_ == 0 ? this->stat_->st_ctime : 0;
}

uid_t yaooc_file_uid(const_pointer p)
{
  yaooc_file_const_pointer this=p;
	yaooc_file_stat(this);
  return this->stat_result_ == 0 ? this->stat_->st_uid : 0;
}

const char* yaooc_file_name(const_pointer p)
{
  yaooc_file_const_pointer this=p;
  return this->name_;
}

gid_t yaooc_file_gid(const_pointer p)
{
  yaooc_file_const_pointer this=p;
	yaooc_file_stat(this);
  return this->stat_result_ == 0 ? this->stat_->st_gid : 0;
}

nlink_t yaooc_file_nlink(const_pointer p)
{
  yaooc_file_const_pointer this=p;
	yaooc_file_stat(this);
  return this->stat_result_ == 0 ? this->stat_->st_nlink : 0;
}

off_t yaooc_file_size(const_pointer p)
{
  yaooc_file_const_pointer this=p;
	yaooc_file_stat(this);
  return this->stat_result_ == 0 ? this->stat_->st_size : 0;
}

bool yaooc_file_isdir(const_pointer p)
{
  yaooc_file_const_pointer this=p;
	yaooc_file_stat(this);
	return this->stat_result_ == 0 ? S_ISDIR(this->stat_->st_mode) : false;
}

bool yaooc_file_ischr(const_pointer p)
{
  yaooc_file_const_pointer this=p;
	yaooc_file_stat(this);
	return this->stat_result_ == 0 ? S_ISCHR(this->stat_->st_mode) : false;
}

bool yaooc_file_isblk(const_pointer p)
{
  yaooc_file_const_pointer this=p;
	yaooc_file_stat(this);
	return this->stat_result_ == 0 ? S_ISBLK(this->stat_->st_mode) : false;
}

bool yaooc_file_isreg(const_pointer p)
{
  yaooc_file_const_pointer this=p;
	yaooc_file_stat(this);
	return this->stat_result_ == 0 ? S_ISREG(this->stat_->st_mode) : false;
}

bool yaooc_file_isfifo(const_pointer p)
{
  yaooc_file_const_pointer this=p;
	yaooc_file_stat(this);
	return this->stat_result_ == 0 ? S_ISFIFO(this->stat_->st_mode) : false;
}

bool yaooc_file_islink(const_pointer p)
{
  yaooc_file_const_pointer this=p;
	yaooc_file_stat(this);
	return this->stat_result_ == 0 ? S_ISLNK(this->stat_->st_mode) : false;
}

bool yaooc_file_issock(const_pointer p)
{
  yaooc_file_const_pointer this=p;
	yaooc_file_stat(this);
	return this->stat_result_ == 0 ? this->stat_->st_mode & __S_IFSOCK : false;
}


/* Class table definition for yaooc_file */
yaooc_file_class_table_t yaooc_file_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
  .type_name_ = (const char*) "yaooc_file_t",
  .swap = (void(*)(pointer, pointer)) yaooc_file_swap,
	.exists = (bool(*)(const_pointer)) yaooc_file_exists,
  .dev = (dev_t(*)(const_pointer)) yaooc_file_dev,
  .mode = (mode_t(*)(const_pointer)) yaooc_file_mode,
  .atime = (time_t(*)(const_pointer)) yaooc_file_atime,
  .mtime = (time_t(*)(const_pointer)) yaooc_file_mtime,
  .ctime = (time_t(*)(const_pointer)) yaooc_file_ctime,
  .uid = (uid_t(*)(const_pointer)) yaooc_file_uid,
  .name = (const char*(*)(const_pointer)) yaooc_file_name,
  .gid = (gid_t(*)(const_pointer)) yaooc_file_gid,
  .nlink = (nlink_t(*)(const_pointer)) yaooc_file_nlink,
  .size = (off_t(*)(const_pointer)) yaooc_file_size,
  .isdir = (bool(*)(const_pointer)) yaooc_file_isdir,
  .ischr = (bool(*)(const_pointer)) yaooc_file_ischr,
  .isblk = (bool(*)(const_pointer)) yaooc_file_isblk,
  .isreg = (bool(*)(const_pointer)) yaooc_file_isreg,
  .isfifo = (bool(*)(const_pointer)) yaooc_file_isfifo,
  .islink = (bool(*)(const_pointer)) yaooc_file_islink,
  .issock = (bool(*)(const_pointer)) yaooc_file_issock,
};

/* Type info structure for yaooc_file */
DEFINE_TYPE_INFO(yaooc_file,Y,Y,Y,Y,N,N,N,Y,yaooc_object);

/* End YAOOCPP output */

