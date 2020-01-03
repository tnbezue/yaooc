/*
		Copyright (C) 2016-2020  by Terry N Bezue

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
