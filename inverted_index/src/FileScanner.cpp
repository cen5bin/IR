#include "FileScanner.h"
#include "IRDefine.h"

#define MAX_LINE_LEN 10000
#define MAX_TERM_LEN 200

#define MAX_DICTIONARY_SIZE 500000

FileScanner::~FileScanner()
{ 
	if (m_sj) delete m_sj; 
	if (m_dict) delete m_dict;
}
FileScanner::FileScanner()
{ 
	FUNC_START;
	m_sj = new SymbolJudger();
	m_dict = new Dictionary(MAX_DICTIONARY_SIZE);
	FUNC_END;
}
bool FileScanner::scanFile(const char *filename)
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
						int termID = m_dict->getTermID(tmp, cnt);
						LOG("%d %s %d", pos, tmp, termID);
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

bool FileScanner::finish()
{
	return m_dict->writeToFile(DICT_FILENAME);
}
