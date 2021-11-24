#ifndef _LOGS_H_
#define _LOGS_H_

extern "C" {

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void ALOG(const char *fmt, ...) {
    va_list arg_list;
    va_start(arg_list, fmt);

    time_t times = time(NULL);
    struct tm *utcTime = gmtime(&times);
    printf("%04d-%02d-%02d\t%02d:%02d:%02d\t", utcTime->tm_year + 1900,
            utcTime->tm_mon + 1, utcTime->tm_mday, utcTime->tm_hour,
            utcTime->tm_min, utcTime->tm_sec);
    vprintf(fmt, arg_list);
    printf("\n");
    va_end(arg_list);
    return;
}
}

#endif