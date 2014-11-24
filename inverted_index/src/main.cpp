#include <cstdio>
#include <cstring>
#include "Trie.h"
#include "SymbolJudger.h"
#include "IRDefine.h"
#include "FileScanner.h"
#include <cstdlib>
#include "HashTable.h"
#include "PreProcess.h"
#include "StatisticInfo.h"

unsigned char s[100];
int main(int argc, char *args[])
{
	system("mkdir -p "DICT_PATH);
	system("mkdir -p "IR_RUNTIME_TMP);
	if (argc == 1)
	{
		HashTable hashtable(1000000);
		FileScanner fs;
		fs.scanFile(SPORTS_DOC_PATH"sport10.txt");
		fs.scanFile(SPORTS_DOC_PATH"sport11.txt");
		fs.scanFile(SPORTS_DOC_PATH"sport1.txt");
		fs.scanFile(SPORTS_DOC_PATH"sport2.txt");
		fs.scanFile(SPORTS_DOC_PATH"sport3.txt");
		fs.finish();

		Trie trie(10000);
		char *s1 = "岑武斌";
		hashtable.insert(s1, strlen(s1), 1);
		LOG("hash %d", hashtable.query(s1, strlen(s1)));
		

		trie.insert(s1, strlen(s1), 1);
		char *s2 = "asdadas";
		trie.insert(s2, strlen(s2), 2);
		hashtable.insert(s2, strlen(s2), 2);
		LOG("hash %d", hashtable.query(s2, strlen(s2)));


		LOG("%d %d %d", trie.query("asd", 3), trie.query(s1, strlen(s1)), trie.query(s2, strlen(s2)));
		while (gets((char *)s))
		{
			for (int i = 0; s[i]; i++) printf("%d ", s[i]);
			puts("");
			puts((char *)s);
		}
	}
	else if (strncmp(args[1], "-x", 2) == 0)
	{
		StatisticInfo si(STATISTIC_FILE_PATH);
		//si.write((void *)"asd0", 4, (void *)"arrsa2", 6);
		char value[100];
		if (si.read(STATISTIC_KEY_DOCNUM, value))
		//if (si.read((void *)STATISTIC_KEY_DOCNUM, strlen(STATISTIC_KEY_DOCNUM), (void *)value, 100) )
		puts(value);
		else puts("no");
	}
	else if (strncmp(args[1], "-t", 2) == 0)
	{
		getTidAndDocID(SPORTS_DOC_PATH);
		L("处理<词项ID，docID>对");
	}
	else if (strncmp(args[1], "-s", 2) == 0)
	{
		mergeTidAndDocID(IR_RUNTIME_TMP);
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
