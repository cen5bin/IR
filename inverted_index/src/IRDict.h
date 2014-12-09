#pragma once
#include "HashTable.h"
class IRDict
{
	private:
		HashTable *m_hashtable;
		int *m_offset;
	public:
		IRDict(char *datapath);
		~IRDict();
		bool insert(char *s, int len, int flag);
		int query(char *s, int len);	
};
