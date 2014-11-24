#pragma once
#include "SymbolJudger.h"
#include "Dictionary.h"

class FileScanner
{
	private:
		SymbolJudger *m_sj;
		Dictionary *m_dict;

		//关于词项id和docid对的临时文件
		int m_cnt;  //当前文件中已经写了几个记录
		int m_flag; //当前是第几个词项id和docid的临时文件
		FILE *m_fp;  //当前正在写数据的文件指针
		void openTmpFile(); //打开一个新的临时文件，在上一个文件写满的时候


		FILE *m_fp0; //docID和文件名的映射文件指针
		
		//关于正排索引
		FILE *m_fp1; //正排索引的文件指针
		int m_cnt1;  //当前正排索引文件中记录的个数
		int m_flag1; //当前时第几个正排索引文件
		void openTmpFile1(); //打开一个新的正排索引临时文件


		int m_docID; //当前正在扫描的docID
		bool write(int tid, int docID); //将词项id和docID组写到文件中
	public:
		~FileScanner();
		FileScanner();
		bool scanFile(const char *filename); //扫描一个文件
		bool finish(); //扫描完所有文件后调用这个函数
};
