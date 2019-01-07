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
