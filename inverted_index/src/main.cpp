#include <cstdio>
#include <cstring>

unsigned char s[100];
int main()
{
	while (gets((char *)s))
	{
		for (int i = 0; s[i]; i++) printf("%d ", s[i]);
		puts("");
		puts((char *)s);
	}
	return 0;
}
