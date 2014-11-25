#include "VB.h"
#define X ((1<<7)-1)
#define W (1<<7)

uint8 *VB::encode(int n, int &len)
{
	static uint8 bytes[5];
	len = 0;
	while (n > X)
		bytes[len++] = n & X, n >>= 7;
	n |= W;
	bytes[len++] = n;
	return bytes;
}

int VB::decode(uint8 *bytes, int &len)
{
	int ret = 0;
	len = 0;
	int move = 0;
	while (!(bytes[len] & W))
	{
		ret |= bytes[len++] << move;
		move+=7;
	}
	ret |= (bytes[len++] ^ W) << move;
	return ret;
}
