#pragma once

#define XXX 2

#define DATA_PATH "./data/" //数据的根目录
#define IR_RUNTIME_DATA DATA_PATH"runtime/" //运行时相关的文件所在目录
#define IR_RUNTIME_TMP IR_RUNTIME_DATA"tmp/" //临时目录

#define DOCIDMAP_TMP_FILE IR_RUNTIME_TMP"map.tmp" //docID 和文件名的映射 临时文件
#define DOCIDMAP_FILE IR_RUNTIME_DATA"map.txt" //docID 和文件名的映射 正式文件

#define SORTED_FILE IR_RUNTIME_TMP"sorted.tmp" //docID tid最终排序文件

#define INVERTED_INDEX_FILE_NAME "inverted_index.dat"
#define INVERTED_INDEX_FILE IR_RUNTIME_DATA INVERTED_INDEX_FILE_NAME //倒排索引文件

#define PRE_INDEX_TMP_FILE IR_RUNTIME_TMP"pre_index.tmp"
#define PRE_INDEX_FILE_NAME "pre_index.dat"
#define PRE_INDEX_FILE IR_RUNTIME_DATA PRE_INDEX_FILE_NAME

//#define DICT_PATH IR_RUNTIME_DATA"dict/" //词典路径
#define DICT_TMP_FILE IR_RUNTIME_TMP"dict.tmp" //词典文件名 临时
#define DICT_FILE_NAME "dict.txt"
#define DICT_FILE IR_RUNTIME_DATA DICT_FILE_NAME //词典文件名 正式


#define SPORTS_DOC_PATH DATA_PATH"contents/fenci/" //体育新闻文档路径

#define STATISTIC_FILE_NAME "statistic.dat"
//#define STATISTIC_FILE_PATH DATA_PATH STATISTIC_FILE_NAME //系统数据的统计信息
#define STATISTIC_FILE_PATH IR_RUNTIME_DATA STATISTIC_FILE_NAME //系统数据的统计信息
#define STATISTIC_KEY_DOCNUM "docnum"  //文档总数量
#define STATISTIC_KEY_TERMNUM "termnum" //词项数量

#define SYMBOL_FILE DATA_PATH"symbols" //标点符号文件
#define TERM_SPLIT_SYMBOL '|' // 分词的分割符



///////////各种常量/////////
#define ERROR -1
#define MAX_ITEM_COUNT 1000000 //每个临时文件中tid，docid的对数
#define MAX_VEC_COUNT 0x7fffffff //每个临时文件中的正排记录的个数
#define MAX_FILENAME_LEN 256 //文件名最长长度
#define WINNER_SIZE 100 //胜者表的大小
#define MAX_TERM_LEN 128 //词项最大长度
