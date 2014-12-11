#pragma once
#include "IRDefine.h"
#include "IRPostIndex.h"
#include "IRDict.h"
#include "IRDocVector.h"

class IREngine
{
	private:
		static char _datapath[MAX_FILENAME_LEN];
	   	static IREngine *_sharedInstance;
		IRDict *m_dict; //词典
		IRPostIndex *m_postindex; //到排索引
		IRDocVector *m_docVec; //文档向量
	public:
	   	static IREngine *sharedInstance(); //只有初始化以后调用这个函数才有意义,得到一个本类的单例
		static void initEngine(char *datapath); //初始化搜索引擎，datapath表示系统运行需要的各个文件存储的路径
		IREngine(char *datapath);
		~IREngine();
		int getTid(char *term);
		void getTids(char terms[][MAX_TERM_LEN], int n, int *tids);
		void query(char terms[][MAX_TERM_LEN], int n, int *docids, int &size);
		void query(int *tids, int n, int *docids, int &size);
		void getDocVector(int docid, int *tid, double *tfidf, int &size);
};
