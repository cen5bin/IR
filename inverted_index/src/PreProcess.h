#pragma once

extern bool getTidAndDocID(char *dataRoot); //从分词的结果中分离出tid，docid对
extern bool mergeTidAndDocID(char *dataRoot); //将分离出的tid，docid对归并成有序的状态
extern bool makeIndex(char *postIndexPath, char *preIndexPath); //建立索引
