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
	public:
		IRDocVector(char *datapath);
		~IRDocVector();
};
