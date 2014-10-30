#include <cstdio>
#include <cstring>
#include "Trie.h"

unsigned char s[100];
int main()
{
	FUNC_START;
	Trie trie(10000);
	char *s1 = "岑武斌";
	trie.insert(s1, strlen(s1), 1);
	char *s2 = "asdadas";
	trie.insert(s2, strlen(s2), 2);

	LOG("%d %d %d", trie.query("asd", 3), trie.query(s1, strlen(s1)), trie.query(s2, strlen(s2)));
	FUNC_END;
	//while (gets((char *)s))
	//{
	//	for (int i = 0; s[i]; i++) printf("%d ", s[i]);
	//	puts("");
	//	puts((char *)s);
	//}
	return 0;
}
