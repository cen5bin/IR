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
		int child[N];
		int val;
		void init()
		{
			memset(child, 0, sizeof(child));
			val = 0;
		}
	}*pool;
	inline int idx(uint8 x) {return x;}
	int size;
	int cnt;
public:
	Trie(){}
	~Trie(){ delete pool; }
	Trie(int size);
	bool insert(char *s, int n, int val);
	int query(char *s, int n);
};


