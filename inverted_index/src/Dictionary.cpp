#include "Dictionary.h"
#include "IRDefine.h"

int Dictionary::getTermID(char *s, int n)
{
	if (!m_trie)
	{
		LE("m_trie is not initialized");
		return ERROR;
	}
	int ret = m_trie->query(s, n);
	if (ret != ERROR && ret) return ret;
	m_cnt++;
	m_trie->insert(s, n, m_cnt);
	m_termVec.push_back(std::string(s, n));
	return m_cnt;
}

int Dictionary::queryTermID(char *s, int n)
{
	if (!m_trie)
	{
		LE("m_trie is not initialized");
		return ERROR;
	}
	return m_trie->query(s, n); 
}

bool Dictionary::writeToFile(const char *filename)
{
	FILE *fp = fopen(filename, "w");
	if (fp == NULL)
	{
		LERR("open file %s failed", filename);
		return 0;
	}
	int size = m_termVec.size();
	for (int i = 0; i < size; i++)
		fprintf(fp, "%s %d\n", m_termVec[i].c_str(), i+1);
	fclose(fp);
	return 1;
}

int Dictionary::getTermCount()
{
	return m_cnt;
}
