#include <yaooc/utils.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

bool mkstemp_in_tmpdir(char* fname,size_t n)
{
	const char* tmpdir=getenv("TMPDIR");
	if(tmpdir == NULL) {
		tmpdir=getenv("TEMP");
		if(tmpdir == NULL) {
			tmpdir=getenv("TMP");
		}
	}
	if(tmpdir == NULL)
		tmpdir="/tmp";
	size_t l=strlen(tmpdir);
	int handle=-1;
	if((l+strlen(fname)+7) < n) {
		memmove(fname+(l=strlen(tmpdir))+1,fname,strlen(fname)+1);
		memcpy(fname,tmpdir,l);
		fname[l] =  '/';
		strcat(fname,"XXXXXX");
		handle=mkstemp(fname);
		if(handle >= 0)
			close(handle);
	}
	return handle >= 0;
}
