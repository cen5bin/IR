#pragma once
#include "IRType.h"
class IRPostIndex
{
	private:
		uint8 **m_postlists; //记录每个tid的倒排记录表,VB编码
		int *m_df; //记录每个tid的dfs值
		int m_termNum; //词项数
		void loadPostLists(char *filename); //从文件中读入倒排记录
	public:
		IRPostIndex(char *datapath); //参数为倒排记录文件所在路径	
		~IRPostIndex() {if (m_postlists) delete m_postlists; }
		void query(int *tids, int n, int *ret, int &size); //根据查询的tid，获取这些tid的倒排记录中的docid的并集，ret为返回的并集，size表示集合的大小
};
