#include "Trie.h"
#include "IRDefine.h"

Trie::Trie(int size)
{
	m_isDynamic = 0;
	pool = new node[size];
	pool[0].init();
	this->size = size;
	cnt = 1;
	LOG("创建字典树，消耗内存 %d MB", sizeof(node) * size >> 20);
}

bool Trie::insert(char *s, int n, int val=1)
{
	if (m_isDynamic) return this->insert2(s, n, val);
	return this->insert1(s, n, val);
}

int Trie::query(char *s, int n)
{
	int now = 0;
	uint8 *tmp = (uint8 *) s;
	for (int i = 0; i < n; i++)
	{
		int index = idx(tmp[i]);
		if (pool[now].next[index] == 0) return ERROR;
		now = pool[now].next[index];
	}
	return pool[now].val;
}

bool Trie::insert1(char *s, int n, int val=1)
{
	int now = 0;
	uint8 *tmp = (uint8 *)s;
	for (int i = 0; i < n; i++)
	{
		int index = idx(tmp[i]);
		if (pool[now].next[index] == 0)
		{
			if (cnt == size) 
			{
				LE("字典树节点已经用完");
				return 0;
			}
			pool[now].next[index] = cnt;
			pool[cnt++].init();
		}
		now = pool[now].next[index];
	}
	pool[now].val = val;
	return 1;
}

bool Trie::insert2(char *s, int n, int val=1)
{
	return 1;
}
