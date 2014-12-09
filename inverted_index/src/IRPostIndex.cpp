#include "IRPostIndex.h"
#include <cstdio>
#include <cstring>
#include "StatisticInfo.h"
#include "IRDefine.h"
#include "VB.h"

IRPostIndex::IRPostIndex(char *datapath)
{
	char filename[MAX_FILENAME_LEN];
	sprintf(filename, "%s%s", datapath, STATISTIC_FILE_NAME);
	StatisticInfo info(filename);
	char value[128];
	info.read(STATISTIC_KEY_TERMNUM, value, 128);
	sscanf(value, "%d", &m_termNum);
	m_postlists = new uint8 *[m_termNum+1];
	m_df = new int[m_termNum+1];
	sprintf(filename, "%s%s", datapath, INVERTED_INDEX_FILE_NAME);
	this->loadPostLists(filename);
}

void IRPostIndex::loadPostLists(char *filename)
{
	FILE *fp = fopen(filename, "rb");
	if (fp == NULL) return;
	int size, tid;
	for (int i = 0; i < m_termNum; i++)
	{
		fread((void*)&size, sizeof(size), 1, fp);
		fread((void*)&tid, sizeof(tid), 1, fp);
		fread((void*)&m_df[tid], sizeof(int), 1, fp);
		size -= 2 * sizeof(int);
		m_postlists[tid] = new uint8[size];
		fread((void*)m_postlists, sizeof(uint8), size, fp);
	}
	fclose(fp);
}

void IRPostIndex::query(int *tids, int n, int *ret, int &size)
{
	size = 0;
	for (int i = 0; i < n; i++)
	{
		int offset = 0, now = 0;
		for (int j = 0; j < WINNER_SIZE && j < m_df[tids[i]]; j++)
		{
			int len;
			now += VB::decode(m_postlists[tids[i]]+offset, len);
			offset += len;
			ret[size++] = now;
		}
	}
}
