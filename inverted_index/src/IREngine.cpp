#include "IREngine.h"
#include <cstring>
#include <cstdio>

IREngine * IREngine::_sharedInstance = NULL;
char IREngine::_datapath[MAX_FILENAME_LEN];

void IREngine::initEngine(char *datapath)
{
	if (_sharedInstance) return;
	strcpy(_datapath, datapath);
	_sharedInstance = new IREngine(datapath);
}

IREngine * IREngine::sharedInstance()
{
	return _sharedInstance;
}

IREngine::IREngine(char *datapath)
{
	m_postindex = new IRPostIndex(datapath);
	L("load postindex success");
	m_dict = new IRDict(datapath);
	L("load dict success");
	m_docVec = new IRDocVector(datapath);
	L("load docvector success");
}

IREngine::~IREngine()
{
	if (m_dict) delete m_dict;
	if (m_postindex) delete m_postindex;
	if (m_docVec) delete m_docVec;
}

int IREngine::getTid(char *term)
{
	return m_dict->query(term, strlen(term));
}

void IREngine::getTids(char terms[][128], int n, int *tids)
{
	for (int i = 0; i < n; i++)
		tids[i] = m_dict->query(terms[i], strlen(terms[i]));
}
