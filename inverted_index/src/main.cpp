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
#include "VB.h"

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
		char *s1 = (char *)"岑武斌";
		hashtable.insert(s1, strlen(s1), 1);
		LOG("hash %d", hashtable.query(s1, strlen(s1)));
		

		trie.insert(s1, strlen(s1), 1);
		char *s2 = (char *)"asdadas";
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
		int len = 0;
		uint8 *bytes = VB::encode(128347775, len);
		for (int i = 0; i < len; i++) printf("%d ", bytes[i]);
		puts("");
		printf("len = %d\n", len);
		printf("decode %d\n", VB::decode(bytes, len));
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
		makeIndex(INVERTED_INDEX_FILE);
		L("合并倒排记录");
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
