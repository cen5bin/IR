#include <cstdio>
#include <cstring>
#include "Trie.h"
#include "SymbolJudger.h"
#include "IRDefine.h"
#include "FileScanner.h"
#include <cstdlib>

unsigned char s[100];
int main(int argc, char *args[])
{
	printf("%d\n", XXX);
	return 0;
	system("mkdir -p "DICT_PATH);
	if (argc == 1)
	{
		FileScanner fs;
		fs.scanFile(SPORTS_DOC_PATH"sport10.txt");
		fs.scanFile(SPORTS_DOC_PATH"sport11.txt");
		fs.scanFile(SPORTS_DOC_PATH"sport1.txt");
		fs.scanFile(SPORTS_DOC_PATH"sport2.txt");
		fs.scanFile(SPORTS_DOC_PATH"sport3.txt");
		fs.finish();

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
