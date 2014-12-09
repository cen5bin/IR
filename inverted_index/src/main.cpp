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
		int ll;
		uint8 *bytes = VB::encode(7, ll);
		LOG("%d", ll);
		ll++;
		int xx = VB::decode(bytes, ll);
		LOG("%d", xx);
		FILE *fp = fopen("aa.dat", "wb");
		int len = 0;
		int size = sizeof(int);
		int cnt = 0;
		for (int i = 100; i <= 200; i++)
		{
			cnt++;
			uint8 *bytes = VB::encode(i, len);
			size+=len * sizeof(uint8);
		}
		LOG("size %d", size);
		fwrite((void*)&size, sizeof(int), 1, fp);
		fwrite((void*)&cnt, sizeof(int), 1, fp);
		for (int i = 100; i <= 200; i++)
		{
			uint8 *bytes = VB::encode(i, len);
			fwrite((void *)bytes, sizeof(uint8), len, fp);
		}
		fclose(fp);
		fp = fopen("aa.dat", "rb");
		fread((void*)&size, sizeof(int), 1, fp);
		fread((void*)&cnt, sizeof(int), 1, fp);
		uint8 *kk = new uint8[size-sizeof(int)];
		fread((void*)kk, sizeof(uint8), size - sizeof(int), fp);
		int offset = 0;
		for (int i = 0; i < cnt; i++)
		{
			int ret = VB::decode(kk+offset, len);
			offset += len;
			LOG("ret %d offset %d", ret, offset);
		}
		fclose(fp);
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
		char s[110][MAX_TERM_LEN];
		int tids[110];
		while (scanf("%d", &n) == 1)
		{
			for (int i = 0; i < n; i++)
				scanf("%s", s[i]);
			puts("开始查询");
			IREngine *engine = IREngine::sharedInstance();
			engine->getTids(s, n, tids);
			for (int i = 0; i < n; i++)
				LOG("%s %d", s[i], tids[i]);
			int docids[1000], size;
			engine->query(tids, n, docids, size);
			LOG("size %d", size);
			for (int i = 0; i < size; i++)
				LOG("%d", docids[i]);
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
