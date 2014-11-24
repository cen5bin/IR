#include "FileMerge.h"
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>
#include <cstdlib>

struct point
{
	int tid, docid;
	point(){}
	point(int _tid, int _docid):tid(_tid), docid(_docid){}
};
int cmp(const point &p1, const point &p2)
{
	if (p1.tid == p2.tid) return p1.docid < p2.docid;
	return p1.tid < p2.tid;
}
struct point1
{
	point p0;
	int id;
	point1(){}
	point1(point _p0, int _id):p0(_p0), id(_id){}
	bool operator > (const point1 &p1) const 
	{
		return !cmp(this->p0, p1.p0);
	}
};
std::priority_queue<point1, std::vector<point1>, std::greater<point1> > q;
std::vector<point> p;
std::vector<point1> p2[10];
char filename[MAX_FILENAME_LEN];
char command[MAX_FILENAME_LEN * 2 + 10];

bool FileMerge::firstMerge()
{
	int now = 1;
	int cnt = 0;
	while (1)
	{
		cnt++;
		bool yes = 0;
		for (int i = now; i < now + 10; i++)
		{
			this->getFilename("", i);	
			//L(m_filename);
			FILE *fp = fopen(m_filename, "r");
			if (fp == NULL) break;
			yes = 1;
			int tid, docid;
			while (fscanf(fp, "%d%d", &tid, &docid) == 2)
				p.push_back(point(tid, docid));
			fclose(fp);
		}
		this->writeSortedData(cnt);
		now += 10;
		if (!yes) break;
	}
	this->writeSortedData(cnt);
	return 1;
}


bool FileMerge::secondMerge()
{
	char prefix[MAX_FILENAME_LEN];
	memset(prefix, '\0', sizeof(prefix));
	prefix[0] = '#';
	int cnt = 0, id = 0;
	FILE *fp[10];
	while (1)
	{
		bool yes = 0;
		cnt++;
		id = 0;
		int now = 1;
		while (1)
		{
			int kk = 0;
			for (int i = now; i < now + 10; i++)
			{
				this->getFilename(prefix, i);
				fp[kk++] = fopen(m_filename, "r");
				if (fp[kk-1] == NULL)
				{
					kk--;
					break;
				}
	//			LOG("%d %s", cnt, m_filename);
			}
			if (kk == 0) break;
			if (kk == 1 && now == 1) break;
			yes = 1;
			prefix[cnt] = '#';
			this->getFilename(prefix, ++id);
			prefix[cnt] = '\0';
			FILE *fp0 = fopen(m_filename, "w");
			this->secondMergeRealWork(fp, kk, fp0);
			fclose(fp0);
			for (int i = 0; i < kk; i++)
				fclose(fp[i]);
			now += 10;
		}
		prefix[cnt] = '#';
	//	L(prefix);
	//	LOG("%d", cnt);
		if (!yes) break;
	}
	prefix[cnt] = '\0';
	this->getFilename(prefix, 1);
	L(m_filename);
	sprintf(command, "cp %s %s", m_filename, SORTED_FILE);
	system(command);
	return 1;
}

void FileMerge::secondMergeRealWork(FILE *fp[], int kk, FILE *fp0)
{
	for (int i = 0; i < 10; i++) p2[i].clear();
	while (!q.empty()) q.pop();
	int cnt[10];
	bool end[10];
	memset(cnt, 0, sizeof(cnt));
	memset(end, 0, sizeof(end));
	for (int i = 0; i < kk; i++)
	{
		for (int j = 0; j < 10000; j++)
		{
			int tid, docid;
			int ret = fscanf(fp[i], "%d %d", &tid, &docid);
			if (ret != 2)
			{
				end[i] = 1;
				break;
			}
			p2[i].push_back(point1(point(tid, docid), i));
		}
	}
	for (int i = 0; i < kk; i++)
	if (cnt[i] < p2[i].size())
	{
		q.push(p2[i][cnt[i]++]);
	}
	while (!q.empty())
	{
		point1 p1 = q.top();
		q.pop();
		fprintf(fp0, "%d %d\n", p1.p0.tid, p1.p0.docid);
		if (cnt[p1.id] < p2[p1.id].size())
			q.push(p2[p1.id][cnt[p1.id]++]);
		else if(!end[p1.id])
		{
			p2[p1.id].clear();
			cnt[p1.id] = 0;
			for (int i = 0; i < 10000; i++)
			{
				int tid, docid;
				int ret = fscanf(fp[p1.id], "%d %d", &tid, &docid);
				if (ret == 0)
				{
					end[p1.id] = 1;
					break;
				}
				p2[p1.id].push_back(point1(point(tid, docid), p1.id));
			}
		}
	}
}

FileMerge::FileMerge(char *dataRoot)
{
	m_dataRoot[0] = '\0';
	strcpy(m_dataRoot, dataRoot);
}

void FileMerge::getFilename(const char *prefix, int id)
{
	sprintf(m_filename, "%s%s%d.tmp", m_dataRoot, prefix, id);
}

void FileMerge::writeSortedData(int id)
{
	if (p.size() == 0) return;
	sort(p.begin(), p.end(), cmp);
	this->getFilename("#", id);
	FILE *fp = fopen(m_filename, "w");
	for (int i = 0; i < p.size(); i++)
		fprintf(fp, "%d %d\n", p[i].tid, p[i].docid);
	fclose(fp);
	p.clear();
}
