#include "IRDict.h"
#include <cstdio>
#include <cstring>
#include "IRDefine.h"
#include "StatisticInfo.h"


IRDict::~IRDict()
{ 
	if (m_hashtable) delete m_hashtable; 
	if (m_offset) delete m_offset;
}

IRDict::IRDict(char *datapath)
{
	char filename[MAX_FILENAME_LEN];
	sprintf(filename, "%s%s", datapath, STATISTIC_FILE_NAME);
	StatisticInfo info(filename);
	char value[128];
	info.read(STATISTIC_KEY_TERMNUM, value, 128);
	int size;
	sscanf(value, "%d", &size);
	LOG("%d", size);
	m_hashtable = new HashTable((int)(size * 1.2));
	m_offset = new int[size+1];
	sprintf(filename, "%s%s", datapath, DICT_FILE_NAME);
	FILE *fp = fopen(filename, "r");
	if (!fp) return;
	char term[1280];
	int tid, offset;
	while (fscanf(fp, "%s%d%d", term, &tid, &offset) == 3)
	{
//		LOG("term %s tid %d", term, tid);
		m_hashtable->insert(term, strlen(term), tid);
		m_offset[tid] = offset;
	}
	fclose(fp);
	LOG("yes");
}

bool IRDict::insert(char *s, int len, int flag)
{
	if (m_hashtable == NULL) return 0;
	return m_hashtable->insert(s, len, flag);
}

int IRDict::query(char *s, int len)
{
	if (m_hashtable == NULL) return ERROR;
	return m_hashtable->query(s, len);
} 
