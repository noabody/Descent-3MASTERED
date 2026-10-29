#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#ifndef _WIN32
#include <unistd.h>
#endif

void con_Printf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    fflush(stdout);
}

int con_Input(char *buf, int maxlen)
{
    if (fgets(buf, maxlen, stdin) != NULL) {
        return 1;
    }
    return 0;
}

void con_defer() {}
void con_init() {}

#ifndef WIN32
void Sleep(int millis)
{
    usleep(millis * 1000);
}

void* GlobalAlloc(int flags, int size)
{
    return malloc(size);
}

void GlobalFree(void* ptr)
{
    free(ptr);
}

void* GlobalLock(void* hMem)
{
    return hMem;
}

char* itoa(int value, char* string, int radix)
{
    sprintf(string, "%d", value);
    return string;
}
#endif
