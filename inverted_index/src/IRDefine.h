#pragma once

#define XXX 2

#define DATA_PATH "./data/" //数据的根目录
#define IR_RUNTIME_DATA DATA_PATH"runtime/" //运行时相关的文件所在目录
#define IR_RUNTIME_TMP IR_RUNTIME_DATA"tmp/" //临时目录
#define DOCIDMAP_FILE IR_RUNTIME_DATA"map" //docID 和文件名的映射
#define SORTED_FILE IR_RUNTIME_DATA"sorted.tmp" //docID tid最终排序文件

#define DICT_PATH IR_RUNTIME_DATA"dict/" //词典路径
#define DICT_FILENAME DICT_PATH"IR.dict" //词典文件名

#define SPORTS_DOC_PATH DATA_PATH"sport/" //体育新闻文档路径

#define STATISTIC_FILE_PATH DATA_PATH"statistic.txt" //系统数据的统计信息
#define STATISTIC_KEY_DOCNUM "docnum"  //文档总数量
#define STATISTIC_KET_TERMNUM "termnum" //词项数量

#define SYMBOL_FILE DATA_PATH"symbol.txt" //标点符号文件
#define TERM_SPLIT_SYMBOL '|' // 分词的分割符



///////////各种常量/////////
#define ERROR -1
#define MAX_ITEM_COUNT 1000 //每个临时文件中tid，docid的对数
#define MAX_VEC_COUNT 1000 //每个临时文件中的正排记录的个数
#define MAX_FILENAME_LEN 256 //文件名最长长度
