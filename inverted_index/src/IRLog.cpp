#include "IRLog.h"

//#define LOG_PATH "./log/"
//#define ERR_PATH "./err/"
#define LOG_PATH "."
#define ERR_PATH "."

static const int FILENAME_LEN = 50;
static const int TIME_LEN = 30;
static va_list ap;
static time_t t;
static struct tm *newtime;
static char logfilename[FILENAME_LEN];
static char errfilename[FILENAME_LEN];
static char timebuf[TIME_LEN];

void _VLOG_(const char *prefix, char *filename, const char *fmt, va_list &ap)
{
	FILE *fp = fopen(filename, "a");
	if (prefix)
		fprintf(fp, "%s ", prefix);
	fprintf(fp, "%s ", timebuf);
	vfprintf(fp, fmt, ap);
	fclose(fp);
}

inline void _PRE_F_()
{
	time(&t);
	newtime = localtime(&t);
	strftime(timebuf, TIME_LEN, "%F %T", newtime);
	strftime(logfilename, FILENAME_LEN, LOG_PATH"%Y%m%d%H.log", newtime); 
	strftime(errfilename, FILENAME_LEN, ERR_PATH"%Y%m%d%H.err", newtime); 
}

void _REAL_LOG_(const char *fmt,  ...)
{
	va_start(ap, fmt);
#ifdef _DEBUG_
	vfprintf(stdout, fmt, ap);
#endif
#ifdef _LOG_
	_PRE_F_();
	_VLOG_(NULL, logfilename, fmt, ap);
#endif
	va_end(ap);
}

void _REAL_LERR_(const char *fmt, ...)
{
	va_start(ap, fmt);
#ifdef _DEBUG_ERR_
	printf("ERR! ");
	vfprintf(stdout, fmt, ap);
#endif
#ifdef _ERR_
	_PRE_F_();
	_VLOG_(NULL, errfilename, fmt, ap);
#endif
#if defined(_ERR_) && defined(_LOG_)
	_VLOG_("#ERR!", logfilename, fmt, ap);
#endif
	va_end(ap);
}

