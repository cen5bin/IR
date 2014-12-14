#include "SymbolJudger.h"
#include <cstdio>
#include <cstring>
#include "IRDefine.h"

const int LEN = 10;

SymbolJudger::SymbolJudger()
{
	m_loaded = 0;
	trie = new Trie(300);
	this->loadSymbols(SYMBOL_FILE);
}

bool SymbolJudger::loadSymbols(const char *filename)
{
	if (m_loaded) return 1;
	m_loaded = 1;
	if (trie == NULL) 
	{
		LE("trie is NULL. Failed to load symbal");
		return 0;
	}
	FILE *fp = fopen(filename, "r");
	if (!fp)
	{
		LERR("open file %s failed!", filename);
		return 0;
	}
	char s[LEN];
	while (fgets(s, LEN, fp))
	{
		int len = strlen(s);
		s[--len] = '\0';
		bool ret = trie->insert(s, len, 1);
		if (!ret) return 0;
	}
	return 1;
}

bool SymbolJudger::judge(char *s, int n)
{
	if (n > 10) return 1;
	if (!m_loaded)
	{
		LE("You haven't load symbols. Please call loadSymbols first");
		return 0;
	}
	int ret = trie->query(s, n);
	if (ret == 0 || ret == -1) return 0;
	return 1;
}
