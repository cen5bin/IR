#pragma once
#include "SymbolJudger.h"

class FileScanner
{
	private:
		SymbolJudger *m_sj;
	public:
		~FileScanner(){ if (m_sj) delete m_sj; }
		FileScanner(){ m_sj = new SymbolJudger(); }
		bool scanFile(char *filename);
};
