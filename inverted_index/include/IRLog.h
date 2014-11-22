#pragma once
#include <cstdio>
#include <stdarg.h>
#include <time.h>

//#define _DEBUG_ //在控制台输出log信息
//#define _DEBUG_ERR_ //在控制台输出err信息
//#define _LOG_ //在文件输出log信息
//#define _ERR_ //在文件输出err信息


//对外建议使用：
//LOG(fmt, args...) 用法同printf，输出log
//L(fmt, args...) 同法同puts，输出log
//LERR(fmt, args...) 用法同printf，输出err
//LE(fmt, args...) 用法同puts，输出err
//FUNC_START 函数刚开始
//FUNC_END 函数结束



#if defined(_DEBUG_) || defined(_LOG_)
	#define LOG(fmt, args...) _REAL_LOG_("[%s:%d %s] "fmt"\n", __FILE__, __LINE__, __FUNCTION__, ##args)
	#define L(s) LOG("%s", s)
#else
	#define LOG(fmt, args...) NULL
	#define L(s) NULL
#endif

#if defined(_ERR_) || defined(_DEBUG_ERR_)
	#define LERR(fmt, args...) _REAL_LERR_("[%s:%d %s] "fmt"\n", __FILE__, __LINE__, __FUNCTION__, ##args)
	#define LE(s) LERR("%s", s)
#else
	#define LERR(fmt, args...) NULL
	#define LE(s) NULL
#endif

#define FUNC_START L("start")
#define FUNC_END L("end")

extern void _REAL_LOG_(const char *fmt,  ...);
extern void _REAL_LERR_(const char *fmt, ...);
