#pragma once
#include <cstdio>
#include <cstring>
#include "IRType.h"

class Trie
{
private:
	static const int N = 256;
	struct node
	{
		int next[N];
		int val;
		void init()
		{
			memset(next, 0, sizeof(next));
			val = 0;
		}
	}*pool, *root;
	inline int idx(uint8 x) {return x;}
	int size;
	int cnt;
	bool m_isDynamic;
	bool insert1(char *s, int n, int val);
	bool insert2(char *s, int n, int val);
public:
	Trie(){ m_isDynamic = 1; root = new node; root->init(); }
	~Trie(){ delete pool; }
	Trie(int size);
	bool insert(char *s, int n, int val);
	int query(char *s, int n);
};


