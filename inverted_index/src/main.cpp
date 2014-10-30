#include <cstdio>
#include <cstring>

unsigned char s[100];
int main()
{
	LOG("%s", "岑武斌");
	LERR("%s", "err");
	while (gets((char *)s))
	{
		for (int i = 0; s[i]; i++) printf("%d ", s[i]);
		puts("");
		puts((char *)s);
	}
	return 0;
}
