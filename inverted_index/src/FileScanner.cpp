#include "FileScanner.h"
#include "IRDefine.h"
#include "StatisticInfo.h"

#define MAX_LINE_LEN 10000
#define MAX_TERM_LEN 200

#define MAX_DICTIONARY_SIZE 500000


FileScanner::~FileScanner()
{ 
	if (m_sj) delete m_sj; 
	if (m_dict) delete m_dict;
}

void FileScanner::openTmpFile()
{
	static char tmp[MAX_FILENAME_LEN];
	m_cnt = 0;
	if (m_fp) fclose(m_fp);
	snprintf(tmp, sizeof(tmp), "%s%d.tmp", IR_RUNTIME_TMP, ++m_flag);
	m_fp = fopen(tmp, "w");
}

void FileScanner::openTmpFile1()
{
	static char tmp[MAX_FILENAME_LEN];
	m_cnt1 = 0;
	if (m_fp1) fclose(m_fp1);
	snprintf(tmp, sizeof(tmp), "%svec_%d.tmp", IR_RUNTIME_TMP, ++m_flag1);
	m_fp1 = fopen(tmp, "w");
}

FileScanner::FileScanner()
{ 
	m_docID = m_cnt = m_flag = 0;
	m_cnt1 = m_flag1 = 0;
	m_fp = m_fp1 = NULL;
	m_fp0 = fopen(DOCIDMAP_FILE, "w");
	this->openTmpFile();
	this->openTmpFile1();
	m_sj = new SymbolJudger();
	m_dict = new Dictionary(MAX_DICTIONARY_SIZE);
}
bool FileScanner::scanFile(const char *filename)
{
	fprintf(m_fp0, "%s %d\n", filename, ++m_docID);
	fprintf(m_fp1, "%d", m_docID);
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
					if (!m_sj->judge(tmp, cnt) && tmp[0] != ' ' && tmp[0] != '\n' && tmp[0] != '\r')
					{
						pos++;
						int termID = m_dict->getTermID(tmp, cnt);
						m_cnt++;
						this->write(termID, m_docID);
						fprintf(m_fp1, " %d", termID);
						//LOG("%d %s %d", pos, tmp, termID);
						if (m_cnt == MAX_ITEM_COUNT)
							this->openTmpFile();
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
	fprintf(m_fp1, "\n");
	m_cnt1++;
	if (m_cnt1 == MAX_VEC_COUNT)
		this->openTmpFile1();
	fclose(fp);
	return 1;
}

bool FileScanner::write(int tid, int docID)
{
	fprintf(m_fp, "%d %d\n", tid, docID);	
	return 1;
}


bool FileScanner::finish()
{
	StatisticInfo si((char *)STATISTIC_FILE_PATH);
	char value[128];
	sprintf(value, "%d", m_docID);
	si.write((void*)STATISTIC_KEY_DOCNUM, strlen(STATISTIC_KEY_DOCNUM), (void*)value, strlen(value));
	sprintf(value, "%d", m_dict->getTermCount());
	si.write((char *)STATISTIC_KET_TERMNUM, value);
	fclose(m_fp0);
	fclose(m_fp);
	fclose(m_fp1);
	return m_dict->writeToFile(DICT_FILENAME);
}
