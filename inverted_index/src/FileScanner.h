#pragma once
#include "SymbolJudger.h"
#include "Dictionary.h"

class FileScanner
{
	private:
		SymbolJudger *m_sj;
		Dictionary *m_dict;
	public:
		~FileScanner();
		FileScanner();
		bool scanFile(const char *filename);
		bool finish();
};
