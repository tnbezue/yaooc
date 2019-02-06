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
#include <yaooc/dir.h>
#include <dirent.h>
#include <string.h>
#include <glob.h>

VECTOR_IMPLEMENTATION(yaooc_file,yaooc_file_vector)

yaooc_file_vector_t* yaooc_dir_entries(const char* dir)
{
	yaooc_file_vector_t* files = new(yaooc_file_vector);
	struct dirent *entry;
	DIR *dp;

	dp = opendir(dir);
	if(dp != NULL) {
		yaooc_file_t temp; // Note, intentionally not initialized
		while((entry = readdir(dp))) {
			if(strcmp(entry->d_name,".") !=0 && strcmp(entry->d_name,"..") !=0)
				temp.name_=entry->d_name; // Copy constructor for yaooc_file only copies this entry
				M(files,push_back,&temp);
		}
		closedir(dp);
	}

	return files;
}

yaooc_file_vector_t* yaooc_dir_glob(const char* pat)
{
	yaooc_file_vector_t* files = new(yaooc_file_vector);
	yaooc_file_t temp; // Note, intentionally not initialized
#ifndef _WIN32
	glob_t glob_result;
	glob(pat,GLOB_TILDE,NULL,&glob_result);
	for(unsigned int i=0;i<glob_result.gl_pathc;++i){
		temp.name_=glob_result.gl_pathv[i];
		M(files,push_back,&temp);
	}
	globfree(&glob_result);
#else
	HANDLE hFind;
	BOOL bContinue = TRUE;
	WIN32_FIND_DATA data;

	hFind = FindFirstFile(pat, &data);
	while (hFind && bContinue) {
		el->push_back(data.cFileName);
		bContinue = FindNextFile(hFind, &data);
	}
	FindClose(hFind); // Free the dir structure
#endif
	return files;
}
