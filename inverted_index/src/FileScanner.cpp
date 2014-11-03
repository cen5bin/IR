#include "FileScanner.h"
#include "IRDefine.h"

#define MAX_LINE_LEN 10000
#define MAX_TERM_LEN 200

bool FileScanner::scanFile(char *filename)
{
	char s[MAX_LINE_LEN];
	FILE *fp = fopen(filename, "r");
	if (!fp)
	{
		LERR("打开文件 %s 失败", filename);
		return 0;
	}
	char tmp[MAX_TERM_LEN];
	int pos = 0;
	int cnt = 0;
	while (fgets(s, MAX_LINE_LEN, fp))
	{
		for (int i = 0; i < MAX_LINE_LEN && s[i]; i++)
		{
			if (s[i] == TERM_SPLIT_SYMBOL) 
			{
				if (cnt)
				{
					tmp[cnt] = '\0';
					if (!m_sj->judge(tmp, cnt) && tmp[0] != ' ')
					{
						pos++;
						LOG("%d %s", pos, tmp);
					}
				}
				cnt = 0;
				tmp[0] = '\0';
				continue;
			}
			else
			{
				tmp[cnt++] = s[i];
				//pos++;
			}
		}	
	}
	fclose(fp);
	return 0;
}
