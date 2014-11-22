#include "HashTable.h"
#include "MurmurHash2.h"
#include <cstring>


bool HashTable::insert(char *s, int len, int flag)
{
	int id = this->calID(s, len);
	node *p = m_header + id;
	node *tmp = new node;
	tmp->key = new char[len+1];
	strncpy(tmp->key, s, len);
	tmp->key[len] = '\0';
	tmp->flag = flag;
	tmp->next = p->next;
	p->next = tmp;
	return 1;
}

int HashTable::query(char *s, int len)
{
	int id = this->calID(s, len);
	node *p = m_header + id;
	while (p->next)
	{
		p = p->next;
		if (strncmp(p->key, s, len) == 0) return p->flag;
	}
	return -1;
}

int HashTable::calID(char *s, int len)
{
	return MurmurHash2(s, len) % m_mod;
}

bool HashTable::isPrime(int x)
{
	for (int i = 2; i * i <= x; i++)
		if (x % i == 0) return 0;
	return 1;
}

HashTable::HashTable(int size)
{
	m_mod = 0;
	for (int i = (size-1)/2*2+1; i > 0; i--)
	if (this->isPrime(i))
	{
		m_mod = i;
		break;
	}
	if (m_mod == 0) 
	{
		LE("hashtable的size设置太小");
		return;
	}
	LOG("m_mod=%d", m_mod);
	m_header = new node[m_mod];
}
