#pragma once
#include <vector>
#include <string>

class IndexMaker
{
	private:
		int m_N;
		struct point
		{
			int docid, tf;
			point(){}
			point(int _docid, int _tf):docid(_docid), tf(_tf){}
			bool operator < (const point &p1) const
			{
				if (this->tf == p1.tf) return this->docid < p1.docid;
				return this->tf > p1.tf;
			}
		};
		std::vector<point> m_postlist; //当前词项的倒排记录表
		std::vector<std::string> m_dict;
		std::vector<std::string> m_docs;
		int *m_df; //文档频率数组，下标表示词项id 
		FILE *m_fp; //倒排记录文件指针
		FILE *m_fp1; //词典文件指针
		FILE *m_fp2; //词项ID docid 排序文件指针
		int m_offset; //文件偏移量
		int m_cnt; //当前在处理第几个词项，从0开始
		void writePostListToFile(int tid);
		void loadDict();
		void loadDocs();
		inline double calidf(int df);
		void normalize(std::vector<double> &tfidf);
	public:
		IndexMaker(){}
		~IndexMaker(){}
		void makePostIndex(const char *filename);
		void makePreIndex(const char *filename);
};
