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
		Dictionary(){ m_cnt = 0; }
		Dictionary(int size){ m_cnt = 0; m_trie = new Trie(size);}
		~Dictionary(){ if (m_trie) delete m_trie; }

		int getTermID(char *s, int n);
		int queryTermID(char *s, int n);
		bool writeToFile(const char *filename);
};
