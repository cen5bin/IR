#pragma once
#include "Trie.h"
#include <vector>
#include <string>

class Dictionary
{
	private:
		Trie *m_trie;
		int m_cnt;
		std::vector<std::string> m_termVec;
	public:
		//Dictionary(){ m_cnt = 0; }
		Dictionary(int size){ m_cnt = 0; m_trie = new Trie(size);}
		~Dictionary(){ if (m_trie) delete m_trie; }

		int getTermID(char *s, int n); //查询词项ID，如果不存在，这为这个词项生成一个新的ID
		int queryTermID(char *s, int n); //单纯的查询词项ID，如果不存在则直接返回-1
		bool writeToFile(const char *filename); //将整个词典写到文件中去
};
