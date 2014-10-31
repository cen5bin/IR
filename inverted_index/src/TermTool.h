#pragma once
#include "Trie.h"
class TermTool
{
public:
	TermTool(int size){ trie = new Trie(size); }
	~TermTool(){ if (trie) delete trie; }
	void processFile(char *filename);
private:
	Trie *trie;
	void writeToDictionary(char *term, int id);
};
