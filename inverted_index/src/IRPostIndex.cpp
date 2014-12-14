#include "IRPostIndex.h"
#include <cstdio>
#include <cstring>
#include "StatisticInfo.h"
#include "IRDefine.h"
#include "VB.h"
#include <cmath>

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
	m_idf = new double[m_termNum+1];
	info.read(STATISTIC_KEY_DOCNUM, value, 128);
	sscanf(value, "%d", &m_N);
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
		m_idf[tid] = log(m_N * 1.0 / m_df[tid]);
		size -= 2 * sizeof(int);
		m_postlists[tid] = new uint8[size];
		fread((void*)m_postlists[tid], sizeof(uint8), size, fp);
	}
	fclose(fp);
}

void IRPostIndex::query(int *tids, int n, int *ret, int &size)
{
	//LOG("%d", m_df[tids[0]]);
	size = 0;
	int tmp0[10000];
	for (int i = 0; i < n; i++)
	{
		int cnt = 0;
		int offset = 0, now = 0;
		//for (int j = m_df[tids[i]], k = 0; j >= 0 && k < WINNER_SIZE; k++, j-- )
		for (int j = 0;  j < m_df[tids[i]]; j++)
		{
			int len;
			now += VB::decode(m_postlists[tids[i]]+offset, len);
			//LOG("now %d", now);
			offset += len;
		//	ret[size++] = now;
			tmp0[cnt++] = now;
		}
		for (int j = 0; j < cnt / 2; j++)
			tmp0[j] = tmp0[j] ^ tmp0[cnt-1-j],
			tmp0[cnt-1-j] = tmp0[j] ^ tmp0[cnt-1-j],
			tmp0[j] = tmp0[j] ^ tmp0[cnt-1-j];
		for (int j = 0; j < WINNER_SIZE && j < m_df[tids[i]]; j++)
			ret[size++] = tmp0[j];
	}
	
}

void IRPostIndex::getidfs(int *tids, int n, double *ret, int &size)
{
	size = 0;
	for (int i = 0; i < n; i++)
		ret[size++] = m_idf[tids[i]];
}
