#include "mono.h"
#include <stdio.h>
#include <stdarg.h>

// Undefine preprocessor macros so we can define the actual function signatures
#ifdef mprintf
#undef mprintf
#endif

#ifdef mprintf_at
#undef mprintf_at
#endif

void mono_Init(void)
{
    printf("SDL Mono Debug Output Initialized.\n");
    fflush(stdout);
}

void DebugBuildPrint(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    fflush(stdout);
}

void mprintf(int window, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    fflush(stdout);
}

void mprintf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    fflush(stdout);
}
