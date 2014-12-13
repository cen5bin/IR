#include "IndexMaker.h"
#include <cstdio>
#include <cstring>
#include "IRDefine.h"
#include "StatisticInfo.h"
#include <algorithm>
#include "VB.h"
#include <cmath>

void IndexMaker::makePostIndex(const char *filename)
{
	this->loadDict();
	StatisticInfo si;
	char value[128];
	m_offset = 0;
	si.read(STATISTIC_KEY_TERMNUM, value, 128);
	int size = 0;
	sscanf(value, "%d", &size);
	LOG("size %d", size);
	m_df = new int[size+1];
	m_fp = fopen(filename, "w");
	L(filename);
	m_fp1 = fopen(DICT_FILE, "w");
	m_fp2 = fopen(SORTED_FILE, "r");
	if (!m_fp || !m_fp1 || !m_fp2) return;
	int tid, docid;
	int lasttid = -1, lastdocid = -1;
	point p;
	m_cnt = 0;
	while (fscanf(m_fp2, "%d%d", &tid, &docid) == 2)
	{
		if (lasttid != tid)
		{
			if (lasttid != -1)
			{
				m_postlist.push_back(p);
				m_df[lasttid] = m_postlist.size();
				this->writePostListToFile(lasttid);
			}
			lasttid = tid;
			p = point(docid, 1);
			lastdocid = -1;
		}
		if (lastdocid != docid)
		{
			if (lastdocid != -1)
			m_postlist.push_back(p);
			lastdocid = docid;
			p = point(docid, 1);
			continue;
		}
		p.tf++;
	}
	m_df[lasttid] = m_postlist.size();
	this->writePostListToFile(lasttid);
	fclose(m_fp);
	fclose(m_fp1);
	fclose(m_fp2);
	m_dict.clear();
	L("make postindex success");
}

//#define TF

void IndexMaker::writePostListToFile(int tid)
{
//	LOG("%d", m_postlist.size());
	fprintf(m_fp1, "%s %d\n", m_dict[m_cnt++].c_str(), m_offset);
//	if (m_postlist.size() == 0) return;
	int size = 0;
	size += sizeof(int) * 2;
//	std::sort(m_postlist.begin(), m_postlist.end());
	int last = 0;
	for (int i = 0; i < m_postlist.size(); i++)
	{
		point p = m_postlist[i];
		int len;
		uint8 *bytes = VB::encode(p.docid - last, len);
		last = p.docid;
		size += len * sizeof(uint8);
#ifdef TF
		bytes = VB::encode(p.tf, len);
		size += len * sizeof(uint8); 
#endif
	}
	m_offset += sizeof(int) + size;
	fwrite((void *)&size, sizeof(int), 1, m_fp);
	fwrite((void *)&tid, sizeof(int), 1, m_fp);
	fwrite((void *)&m_df[tid], sizeof(int), 1, m_fp);
	//m_offset += sizeof(int) * 2;
	last = 0;
	for (int i = 0; i < m_postlist.size(); i++)
	{
		point p = m_postlist[i];
		int len;
		uint8 *bytes = VB::encode(p.docid - last, len);
		last = p.docid;
		fwrite((void *)bytes, sizeof(uint8) * len, 1, m_fp);
	//	m_offset += len * sizeof(uint8);
#ifdef TF
		bytes = VB::encode(p.tf, len);
		fwrite((void *)bytes, sizeof(uint8) * len, 1, m_fp);
#endif
	//	m_offset += len * sizeof(uint8); 
	}
	m_postlist.clear();
}

void IndexMaker::loadDict()
{
	FILE *fp = fopen(DICT_TMP_FILE, "r");
	if (!fp) return;
	char buffer[1024];
	while (fgets(buffer, 1024, fp))
	{
		buffer[strlen(buffer) - 1] = '\0';
		m_dict.push_back(buffer);
	}
	fclose(fp);
}

void IndexMaker::loadDocs()
{
	FILE *fp = fopen(DOCIDMAP_TMP_FILE, "r");
	if (!fp) return;
	char buffer[1024];
	while (fgets(buffer, 1024, fp))
	{
		buffer[strlen(buffer) - 1] = '\0';
		m_docs.push_back(buffer);
	}
	fclose(fp);
}

void IndexMaker::normalize(std::vector<double> &tfidf)
{
	double len = 0;
	for (int i = 0; i < tfidf.size(); i++)
		len += tfidf[i] * tfidf[i];
	len = sqrt(len);
	for (int i = 0; i < tfidf.size(); i++)
		tfidf[i] /= len;
}

void IndexMaker::makePreIndex(const char *filename)
{	
	this->loadDocs();
	StatisticInfo si;
	char value[128];
	si.read(STATISTIC_KEY_DOCNUM, value, 128);
	sscanf(value, "%d", &m_N);
	FILE *fp = fopen(PRE_INDEX_TMP_FILE, "r");
	FILE *fp1 = fopen(filename, "wb");
	FILE *fp2 = fopen(DOCIDMAP_FILE, "w");
	if (!fp || !fp1) return;
	std::vector<int> a;
	std::vector<double> tfidf;
	std::vector<int>tids;
	int offset = 0;
	for (int i = 0; i < m_N; i++)
	{
		fprintf(fp2, "%s %d\n", m_docs[i].c_str(), offset);
		a.clear();
		tfidf.clear();
		tids.clear();
		int docid;
		fscanf(fp, "%d", &docid);
		int tid;
		while (fscanf(fp, "%d", &tid) && tid)
			a.push_back(tid);
		if (a.size() == 0) continue;
		sort(a.begin(), a.end());
		int last = a[0];
		int cnt = 0;
		a.push_back(-1);
		for (int j = 0; j < a.size(); j++)
		{
			if (last != a[j])
			{
				double tmp = cnt * this->calidf(m_df[last]);
				tids.push_back(last);
				tfidf.push_back(tmp);
				last = a[j];
				cnt = 0;
			}	
			cnt++;
		}
		this->normalize(tfidf);
		int size = sizeof(int) + tfidf.size() * (sizeof(int) + sizeof(double));
		offset += sizeof(int) + size;
		fwrite((void *)&size, sizeof(int), 1, fp1);
		fwrite((void *)&docid, sizeof(int), 1, fp1);
		for (int j = 0; j < tfidf.size(); j++)
		{
			fwrite((void *)&tids[j], sizeof(int), 1, fp1);
			fwrite((void *)&tfidf[j], sizeof(double), 1, fp1);
		}
	}
	fclose(fp);
	fclose(fp1);
	fclose(fp2);
}

inline double IndexMaker::calidf(int df)
{
	return log(1.0 * m_N / df);
}
