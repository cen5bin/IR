#pragma once
#include "IRDefine.h"
class StatisticInfo
{
	private:
		char m_filename[MAX_FILENAME_LEN];
	public:
		StatisticInfo();
		StatisticInfo(char *filename);
		~StatisticInfo(){}
		bool write(void *key, int key_len, void *value, int value_len);
		bool write(const char *key, char *value);
		bool read(void *key, int key_len, void *value, int value_len);
		bool read(const char *key, char *value, int len=64);
};
