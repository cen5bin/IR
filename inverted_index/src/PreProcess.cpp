#include "PreProcess.h"
#include <dirent.h>
#include <sys/stat.h>
#include "FileScanner.h"
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>
#include "FileMerge.h"

std::vector<std::string> filenames;

bool dfs_path(char *pathname, FileScanner *fs) //递归数据文件路径，将所有的分词结果的文件名放进vecotr中
{
	bool ret = 1;
	struct stat st;
	if (lstat(pathname, &st) == -1) return 0;
	if (!S_ISDIR(st.st_mode)) //return fs->scanFile(pathname);
	{
		filenames.push_back(pathname);
		return 1;
	}
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
	if (!ret) return 0;
	std::sort(filenames.begin(), filenames.end());
	for (int i = 0; i < filenames.size(); i++)
		ret &= fs.scanFile(filenames[i].c_str());
	fs.finish();
	filenames.clear();
	return ret;
}


bool mergeTidAndDocID(char *dataRoot)
{
	FileMerge fm(dataRoot);	
	fm.firstMerge();
	fm.secondMerge();
	return 1;
}
