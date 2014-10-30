#include "Trie.h"

Trie::Trie(int size)
{
	pool = new node[size];
	pool[0].init();
	this->size = size;
	cnt = 1;
	LOG("创建字典树，消耗内存 %d MB", sizeof(node) * size >> 20);
}

bool Trie::insert(char *s, int n, int val=3)
{
	int now = 0;
	uint8 *tmp = (uint8 *)s;
	for (int i = 0; i < n; i++)
	{
		int index = idx(tmp[i]);
		if (pool[now].child[index] == 0)
		{
			if (cnt == size) 
			{
				LE("字典树节点已经用完");
				return 0;
			}
			pool[now].child[index] = cnt;
			pool[cnt++].init();
		}
		now = pool[now].child[index];
	}
	pool[now].val = val;
	return 1;
}

int Trie::query(char *s, int n)
{
	int now = 0;
	uint8 *tmp = (uint8 *) s;
	for (int i = 0; i < n; i++)
	{
		int index = idx(tmp[i]);
		if (pool[now].child[index] == 0) return -1;
		now = pool[now].child[index];
	}
	return pool[now].val;
}
