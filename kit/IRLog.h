#pragma once
#include <time.h>
#define LOG_PATH "./log/" //日志文件相对可执行文件的目录
#define ERR_PATH "./err/" //错误文件相对可执行文件的目录

#define IR_DEBUG //输出到控制台,注释掉后控制台不会打印普通信息
#define IR_DEBUG_ERR //控制台错误输出，注释掉后控制台不会输出错误信息
#define IR_LOG // 输出到log文件。如果IR_DEBUG和本行均被注释掉，则不会输出信息到日志文件

//建议在外部使用的是:
//LOG(fmt, args...)  同printf 
//L(s) 同puts
//LERR(fmt, args...) 同printf 输出错误


#define LEN 30
#define FILENAME_LEN 100

#define PRE_FLOG \
	time_t t; \
	struct tm* newtime; \
	char timebuf[LEN]; \
	char logfilename[LEN]; \
	time(&t);  \
	newtime = localtime(&t); \
	strftime(timebuf, LEN, "%F %T", newtime); \
	strftime(logfilename, FILENAME_LEN, LOG_PATH"%Y%m%d%H.log", newtime); \

#define PRE_FERR \
	PRE_FLOG; \
	char errfilename[FILENAME_LEN]; \
	strftime(errfilename, FILENAME_LEN, ERR_PATH"%Y%m%d%H.err", newtime); \

#if defined(IR_DEBUG) || defined(IR_LOG)
	#define FLOG(fmt, args...) { \
		PRE_FLOG \
		FILE *fp = fopen(logfilename, "a"); \
		fprintf(fp, "%s [%s:%d %s] "fmt"\n", timebuf, __FILE__, __LINE__, __FUNCTION__, ##args); \
		fclose(fp); \
	}
	#define FL(s) FLOG("%s", s)
#else
	#define FLOG(fmt, args...) NULL
	#define FL(s) NULL
#endif

#ifdef IR_LOG
#define FERR(fmt, args...) { \
	PRE_FERR \
	FILE *fp = fopen(errfilename, "a"); \
	fprintf(fp, "%s [%s:%d %s] "fmt"\n", timebuf, __FILE__, __LINE__, __FUNCTION__, ##args); \
	fclose(fp); \
	fp = fopen(logfilename, "a"); \
	fprintf(fp, "%s ERR!!! [%s:%d %s] "fmt"\n", timebuf, __FILE__, __LINE__, __FUNCTION__, ##args); \
	fclose(fp); \
}
#else
	#define FERR(fmt, args...) { \
		PRE_FERR \
		FILE *fp = fopen(errfilename, "a"); \
		fprintf(fp, "%s [%s:%d %s] "fmt"\n", timebuf, __FILE__, __LINE__, __FUNCTION__, ##args); \
		fclose(fp); \
	}
#endif

#if defined(IR_DEBUG)
	#define LOG(fmt, args...) { \
		printf("[%s:%d %s] "fmt"\n", __FILE__, __LINE__, __FUNCTION__, ##args); \
		FLOG(fmt, ##args); \
	}
	#define L(s) LOG("%s", s)
#elif defined(IR_LOG)
	#define LOG(fmt, args...) FLOG(fmt, ##args)
	#define L(s) FL(s)
#else
	#define LOG(fmt, args...) NULL
	#define L(s) NULL
#endif

#if defined(IR_DEBUG_ERR) || defined(IR_DEBUG)
	#define LERR(fmt, args...) {\
		printf("ERR!!! [%s:%d %s] "fmt"\n", __FILE__, __LINE__, __FUNCTION__, ##args); \
		FERR(fmt, ##args); \
	}
#else
	#define LERR(fmt, args...) FERR(fmt, ##args)
#endif

