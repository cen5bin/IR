#pragma once
#include "IRDefine.h"
class FileMerge
{
	private:
		void getFilename(const char *prefix, int id);
		void writeSortedData(int id);
		void secondMergeRealWork(FILE *fp[], int kk, FILE *fp0);
		char m_dataRoot[MAX_FILENAME_LEN];
		char m_filename[MAX_FILENAME_LEN];
	public:
		FileMerge(char *dataRoot);
		~FileMerge(){}
		bool firstMerge();
		bool secondMerge();
};
