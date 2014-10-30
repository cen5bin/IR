#pragma once
#include <cstdio>
#include <cstring>

class Trie
{
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
	}*p;
public:
	Trie(){}
	Trie(int size);

};


