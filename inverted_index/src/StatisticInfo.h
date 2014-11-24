#pragma once
#include "IRDefine.h"
class StatisticInfo
{
	private:
		char m_filename[MAX_FILENAME_LEN];
	public:
		StatisticInfo(char *filename);
		~StatisticInfo(){}
		bool write(void *key, int key_len, void *value, int value_len);
		bool write(char *key, char *value);
		bool read(void *key, int key_len, void *value, int value_len);
		bool read(char *key, char *value);
};
