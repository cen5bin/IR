#pragma once
class IRDocVector
{
	private:
		int m_docNum;
		struct vecNode
		{
			int tid;
			double tfidf;
		};
		vecNode **m_docVec;
		int *m_docVecLen;
	public:
		IRDocVector(char *datapath);
		~IRDocVector();
		void getDocVector(int docid, int *tid, double *tfidf, int &size);
};
