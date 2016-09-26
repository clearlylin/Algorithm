#include "log.h"
#include "config.h"

static void doErr(int level, const char* msg, va_list ap) {
	int errorno = errno, n;
	char buf[MAXLine + 1];
	vsnprintf(buf, MAXLine + 1, msg, ap);

	n = strlen(buf);
	snprintf(buf + n, MAXLine - n, ":%s", strerror(errorno));

	#ifdef SYSLOG
		syslog(level, "%s", buf);
	#else
		fputs(buf, stderr);
		fflush(stderr);
	#endif
}

void err_msg(const char* msg, ...) {
	va_list vp;
	va_start(vp, msg);
	doErr(LOG_INFO, msg, vp);
	va_end(vp);
}

void err_quit(const char* msg, ...) {
	va_list vp;
	va_start(vp, msg);
	doErr(LOG_ERR, msg, vp);
	va_end(vp);
	abort();
	exit(1);
}
