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
#include "IREngine.h"

unsigned char s[100];
int main(int argc, char *args[])
{
	system("mkdir -p "IR_RUNTIME_TMP);
	if (argc == 1)
	{
		puts("please use -h to see the help");
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
		makeIndex(INVERTED_INDEX_FILE, PRE_INDEX_FILE);
		L("合并倒排记录");
	}
	else if (strncmp(args[1], "-r", 2) == 0)
	{
		puts("测试搜索引擎");
		puts("正在启动.........");
		IREngine::initEngine(IR_RUNTIME_DATA);
		int n;
		char s[110][128];
		int tids[110];
		while (scanf("%d", &n) == 1)
		{
			for (int i = 0; i < n; i++)
				scanf("%s", s[i]);
			puts("开始查询");
			IREngine *engine = IREngine::sharedInstance();
			engine->getTids(&s[0], n, tids);
			for (int i = 0; i < n; i++)
				LOG("%s %d", s[i], tids[i]);

		}
	}
	else if (strncmp(args[1], "-h", 2) == 0)
	{
		puts("参数说明:");
		puts("-t 处理出<词项ID，docID>对");
		puts("-s 对<词项ID，docID>对排序");
		puts("-m 合并倒排记录表");
		puts("-r 运行引擎");
		puts("-h 帮助");
	}
	else 
	{
		puts("参数错误，使用./work -h查看参数说明");
	}
	return 0;
}
