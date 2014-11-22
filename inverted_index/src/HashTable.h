#pragma once

class HashTable
{
	private:
		struct node
		{
			char *key;
			int flag;
			node *next;
			node()
			{
				key = NULL;
				next = NULL;
				flag = -1;
			}
		};
		inline int calID(char *s, int len);
		bool isPrime(int x);
		int m_mod;
		node *m_header;
	public:
		HashTable(int size);
		~HashTable(){}
		bool insert(char *s, int len, int flag);
		int query(char *s, int len);
};
