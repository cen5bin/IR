#include <cstdio>
#include <cstring>
#include "Trie.h"
#include "SymbolJudger.h"

unsigned char s[100];
int main()
{
	SymbolJudger sj(300);
	if (!sj.loadSymbols("./data/symbol.txt"))
	{
		LE("loadSymbols error");
		return 0;
	}
	char *s0 = ",";
	if (sj.judge(s0, strlen(s0))) L("yes");
	else L("no");
	s0 = ".";
	if (sj.judge(s0, strlen(s0))) L("yes");
	else L("no");
	s0 = "。";
	if (sj.judge(s0, strlen(s0))) L("yes");
	else L("no");

	Trie trie(10000);
	char *s1 = "岑武斌";
	trie.insert(s1, strlen(s1), 1);
	char *s2 = "asdadas";
	trie.insert(s2, strlen(s2), 2);

	LOG("%d %d %d", trie.query("asd", 3), trie.query(s1, strlen(s1)), trie.query(s2, strlen(s2)));
	while (gets((char *)s))
	{
		for (int i = 0; s[i]; i++) printf("%d ", s[i]);
		puts("");
		puts((char *)s);
	}
	return 0;
}
