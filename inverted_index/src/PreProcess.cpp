#include "PreProcess.h"
#include <dirent.h>
#include <sys/stat.h>
#include "FileScanner.h"
#include <cstdio>
#include <cstring>


bool dfs_path(char *pathname, FileScanner *fs)
{
	L(pathname);
	bool ret = 1;
	struct stat st;
	if (lstat(pathname, &st) == -1) return 0;
	if (!S_ISDIR(st.st_mode)) return fs->scanFile(pathname);
	else
	{
		DIR *dir = opendir(pathname);
		struct dirent *dd;
		while (dd = readdir(dir))
		{
			if (strcmp(dd->d_name, ".") == 0 || strcmp(dd->d_name, "..") == 0) continue;
			static char tmp[256];
			strcpy(tmp, pathname);
			int l = strlen(tmp);
			if (tmp[l-1] != '/')
				tmp[l++] = '/';
			strcpy(tmp+l, dd->d_name);
			ret = dfs_path(tmp, fs);
			if (!ret) return 0;
		}
		closedir(dir);
	}
	return 1;
}


bool getTidAndDocID(char *dataRoot)
{
	FileScanner fs;
	bool ret = dfs_path(dataRoot, &fs);
	fs.finish();
	return ret;
}
