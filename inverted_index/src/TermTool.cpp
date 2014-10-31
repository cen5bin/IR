#include "TermTool.h"
#include <cstdio>
#include <cstring>

void TermTool::processFile(char *filename)
{
	FILE *fp = fopen(filename, "r");
	if (!fp)
	{
		LERR("打开文档%s失败", filename);
		return;
	}

}

void TermTool::writeToDictionary(char *term, int id)
{

}
