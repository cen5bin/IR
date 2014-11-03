#include <cstdio>
#include <cstring>
#include "Trie.h"
#include "SymbolJudger.h"

unsigned char s[100];
int main(int argc, char *args[])
{
	if (argc == 0)
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
	}
	else if (strncmp(args[1], "-t", 2) == 0)
	{
		L("处理<词项ID，docID>对");
	}
	else if (strncmp(args[1], "-s", 2) == 0)
	{
		L("排序");
	}
	else if (strncmp(args[1], "-m", 2) == 0)
	{
		L("合并到排记录");
	}
	else if (strncmp(args[1], "-h", 2) == 0)
	{
		puts("参数说明:");
		puts("-t 处理出<词项ID，docID>对");
		puts("-s 对<词项ID，docID>对排序");
		puts("-m 合并倒排记录表");
		puts("-h 帮助");
	}
	else 
	{
		puts("参数错误，使用./work -h查看参数说明");
	}
	return 0;
}
