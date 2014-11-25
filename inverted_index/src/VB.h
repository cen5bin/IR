#pragma once
#include "IRType.h"
class VB
{
	public:
		static uint8 *encode(int n, int &len);
		static int decode(uint8 *bytes, int &len);
};
