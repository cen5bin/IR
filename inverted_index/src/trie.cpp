#include "trie.h"

Trie::Trie(int size)
{
	p = new node[size];
	LOG("创建字典树，消耗内存 %d MB", sizeof(node) * size >> 20);
}
