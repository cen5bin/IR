#include <cstdio>
#include "IRLog.h"

int main()
{
	LOG("%d", 1);
	L("asd");
//	FLOG("%d", 1);
//	FL("asd");
	LERR("%s", "aaaa");
	return 0;
}
