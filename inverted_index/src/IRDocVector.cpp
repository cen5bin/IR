#include <cstdio>
#include <cstring>
#include "IRDocVector.h"
#include "IRDefine.h"
#include "StatisticInfo.h"

IRDocVector::IRDocVector(char *datapath)
{
	char filename[MAX_FILENAME_LEN];
	sprintf(filename, "%s%s", datapath, STATISTIC_FILE_NAME);
	StatisticInfo info(filename);
	char value[128];
	info.read(STATISTIC_KEY_DOCNUM, value, 128);
	sscanf(value, "%d", &m_docNum);	
	m_docVec = new vecNode*[m_docNum + 1];
	m_docVecLen = new int[m_docNum + 1];
	sprintf(filename, "%s%s", datapath, PRE_INDEX_FILE_NAME);
	FILE *fp = fopen(filename, "rb");
	if (!fp) return;
	for (int i = 0; i < m_docNum; i++)
	{
		int size, docid;			
		fread((void*)&size, sizeof(int), 1, fp);
		fread((void*)&docid, sizeof(int), 1, fp);
	//	LOG("size %d, docid %d", size, docid);
		int count = (size-sizeof(int))/sizeof(vecNode);
	//	LOG("count %d", count);
		m_docVec[docid] = new vecNode[count];
		m_docVecLen[docid] = count;
		int ret = fread((void*)m_docVec[docid], sizeof(vecNode), count, fp);
	//	LOG("ret %d", ret);
		//for (int j = 0; j < count; j++)
		//	LOG("tid %d, tfidf %.3f", m_docVec[docid][j].tid, m_docVec[docid][j].tfidf);
	}
	fclose(fp);
}

IRDocVector::~IRDocVector()
{
	if (m_docVec) delete m_docVec;
	if (m_docVecLen) delete m_docVecLen;
}

void IRDocVector::getDocVector(int docid, int *tid, double *tfidf, int &size)
{
	size = 0;
	for (int i = 0; i < m_docVecLen[docid]; i++)
	{
		tid[size] = m_docVec[docid][i].tid;
		tfidf[size++] = m_docVec[docid][i].tfidf;
	}
}
