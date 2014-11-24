#include "StatisticInfo.h"
#include <cstdio>
#include <cstring>

#define BUFFER_SIZE 128
#define KET_SIZE 64
#define VALUE_SIZE (BUFFER_SIZE - KET_SIZE)
StatisticInfo::StatisticInfo(char *filename)
{
	strcpy(m_filename, filename);
}

bool StatisticInfo::write(void *key, int key_len, void *value, int value_len)
{
	static char buffer[BUFFER_SIZE];
	FILE *fp = fopen(m_filename, "rb+");
	if (fp == NULL) 
	{
		fp = fopen(m_filename, "wb+");
	}
	int cnt = 0;
	while (fread(buffer, BUFFER_SIZE, 1, fp))
	{
		cnt++;
		if (strncmp((char *)key, buffer, key_len) == 0)
		{
			fseek(fp, -BUFFER_SIZE, SEEK_CUR);
			strncpy(buffer, (char *)key, key_len);
			buffer[key_len] = '\0';
			strncpy(buffer+key_len+1, (char *)value, value_len);
			buffer[key_len+1+value_len] = '\0';
			fwrite(buffer, BUFFER_SIZE, 1, fp);
			fclose(fp);
			return 1;
		}
	}
	fseek(fp, cnt * BUFFER_SIZE, SEEK_SET);
	strncpy(buffer, (char *)key, key_len);
	buffer[key_len] = '\0';
	strncpy(buffer+key_len+1, (char *)value, value_len);
	buffer[key_len+1+value_len] = '\0';
	fwrite(buffer, BUFFER_SIZE, 1, fp);
	fclose(fp);
	return 1;
}

bool StatisticInfo::read(void *key, int key_len, void *value, int value_len)
{
	static char buffer[BUFFER_SIZE];
	FILE *fp = fopen(m_filename, "rb");
	if (fp == NULL) return 0;
	while (fread(buffer, BUFFER_SIZE, 1, fp))
	{
		if (strncmp((char *)key, buffer, key_len) == 0 && strlen(buffer) == key_len)
		{
			strncpy((char *)value, buffer+key_len + 1, value_len);
			fclose(fp);
			return 1;
		}
	}
	fclose(fp);
	return 0;
}

bool StatisticInfo::write(char *key, char *value)
{
	return this->write((void *)key, strlen(key), (void *)value, strlen(value));
}

bool StatisticInfo::read(char *key, char *value)
{
	return this->read((void *)key, strlen(key), (void *)value, sizeof(value));
}
