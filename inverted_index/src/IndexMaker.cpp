#include "IndexMaker.h"
#include <cstdio>
#include <cstring>
#include "IRDefine.h"
#include "StatisticInfo.h"
#include <algorithm>
#include "VB.h"

void IndexMaker::makePostIndex(const char *filename)
{
	this->loadDict();
	StatisticInfo si;
	char value[128];
	m_offset = 0;
	si.read(STATISTIC_KET_TERMNUM, value, 128);
	int size = 0;
	sscanf(value, "%d", &size);
	LOG("size %d", size);
	m_df = new int[size+1];
	m_fp = fopen(filename, "w");
	L(filename);
	m_fp1 = fopen("aaaa.txt", "w");
	m_fp2 = fopen(SORTED_FILE, "r");
	if (!m_fp || !m_fp1 || !m_fp2) return;
	int tid, docid;
	int lasttid = 1, lastdocid = -1;
	point p;
	m_cnt = 0;
	while (fscanf(m_fp2, "%d%d", &tid, &docid) == 2)
	{
		if (lasttid != tid)
		{
			m_df[lasttid] = m_postlist.size();
			this->writePostListToFile(lasttid);
			lasttid = tid;
			p = point(docid, 1);
			lastdocid = -1;
			//continue;
		}
		if (lastdocid != docid)
		{
			lastdocid = docid;
			m_postlist.push_back(p);
			p = point(docid, 1);
			continue;
		}
		p.tf++;
	}
//	L("zzz");
	fclose(m_fp);
	fclose(m_fp1);
	fclose(m_fp2);
}


void IndexMaker::writePostListToFile(int tid)
{
	fprintf(m_fp1, "%s %d\n", m_dict[m_cnt++].c_str(), m_offset);
	fwrite((void *)&tid, sizeof(int), 1, m_fp);
	fwrite((void *)&m_df[tid], sizeof(int), 1, m_fp);
	m_offset += sizeof(int) * 2;
	std::sort(m_postlist.begin(), m_postlist.end());
	int last = 0;
	if (m_postlist.size() == 0) L("zz");
	for (int i = 0; i < m_postlist.size(); i++)
	{
		point p = m_postlist[i];
		int len;
		uint8 *bytes = VB::encode(p.docid - last, len);
		last = p.docid;
		fwrite((void *)bytes, sizeof(uint8) * len, 1, m_fp);
		m_offset += len * sizeof(uint8);
		bytes = VB::encode(p.tf, len);
		fwrite((void *)bytes, sizeof(uint8) * len, 1, m_fp);
		//fwrite((void *)&p.tf, sizeof(int), 1, m_fp);
		m_offset += len * sizeof(uint8); // + sizeof(int);
	}
	m_postlist.clear();
}

void IndexMaker::loadDict()
{
	FILE *fp = fopen(DICT_FILENAME, "r");
	char buffer[1024];
	while (fgets(buffer, 1024, fp))
	{
		buffer[strlen(buffer) - 1] = '\0';
		m_dict.push_back(buffer);
	}
	fclose(fp);
}

void IndexMaker::makePreIndex(const char *filename)
{
	
}
