#pragma once
#include "SymbolJudger.h"
#include "Dictionary.h"

class FileScanner
{
	private:
		SymbolJudger *m_sj;
		Dictionary *m_dict;
		int m_cnt;  //当前文件中已经写了几个记录
		int m_flag; //当前是第几个临时文件
		FILE *m_fp;  //当前正在写数据的文件指针
		FILE *m_fp0; //docID和文件名的映射文件指针
		int m_docID; //当前正在扫描的docID
		bool write(int tid, int docID); //将词项id和docID组写到文件中
		void openTmpFile(); //打开一个新的临时文件，在上一个文件写满的时候
	public:
		~FileScanner();
		FileScanner();
		bool scanFile(const char *filename); //扫描一个文件
		bool finish(); //扫描完所有文件后调用这个函数
};
