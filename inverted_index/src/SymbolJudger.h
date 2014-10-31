#pragma once
#include "Trie.h"
class SymbolJudger
{
	public:
		SymbolJudger(int size){ m_loaded = 0; trie = new Trie(size); }
		~SymbolJudger(){ if (trie) delete trie; }
		bool loadSymbols(char *filename);
		bool judge(char *s, int n);
	private:
		Trie *trie;
		bool m_loaded;
};
