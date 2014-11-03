/**
  用来判断标点符号
*/
#pragma once
#include "Trie.h"
class SymbolJudger
{
	public:
		SymbolJudger();//{ m_loaded = 0; trie = new Trie(300); }
		SymbolJudger(int size){ m_loaded = 0; trie = new Trie(size); }
		~SymbolJudger(){ if (trie) delete trie; }
		bool judge(char *s, int n);
	private:
		bool loadSymbols(const char *filename);
		Trie *trie;
		bool m_loaded;
};
