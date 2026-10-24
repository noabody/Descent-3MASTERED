#ifndef __LINUX_FIX_H_
#define __LINUX_FIX_H_

#include <sys/stat.h>

// Undefine macro min/max to prevent breaking C++ std::min/std::max templates in Macros.h
#ifdef min
  #undef min
#endif
#ifdef max
  #undef max
#endif

// Handle stdbool / bool definitions across C and C++ modes
#ifdef __cplusplus
  #include <cctype>
  #include <thread>
  #include <cstring>
  #include <algorithm>

  #ifndef register
    #define register
  #endif
#else
  #include <stdbool.h>
#endif

#include <unistd.h>
#include <signal.h>
#include <strings.h>
#include <utime.h>

// Undefine conflicting legacy platform macros
#undef device_type
#undef buttons

// POSIX System / Win32 Compatibility Definitions
#define dd_SplitPath ddio_SplitPath
#define dd_MakePath  ddio_MakePath

#define _open        open
#define _close       close
#define _read        read
#define _lseek       lseek
#define closesocket  close
#define _stat        stat

#ifndef _MAX_DIR
#define _MAX_DIR 256
#endif

#ifndef BOOL
typedef bool BOOL;
#endif

#ifndef TRUE
#define TRUE true
#endif

#ifndef FALSE
#define FALSE false
#endif

#define LOKI_VERSION ""
#define HGLOBAL void*

void GlobalFree(void *);
void *GlobalAlloc(int flags,int size);
void *GlobalLock(HGLOBAL hMem);
void Sleep(int millis);
char *itoa(int value,char *string,int radix);
char *strupr(char *string);

// Replace missing defines from stdlib.h
#define _MAX_PATH    260    /* max. length of full pathname*/
#define _MAX_FNAME   256    /* max. length of path component*/
#define _MAX_EXT     256    /* max. length of extension component*/
#if !defined(MAX_PATH)
#define MAX_PATH _MAX_PATH
#endif
#define HANDLE int

// _cdecl / _stdcall replacements
#ifndef STDCALL
  #define STDCALL __attribute__((stdcall))
#endif
#ifndef _stdcall
  #define _stdcall __attribute__((stdcall))
#endif
#ifndef __stdcall
  #define __stdcall __attribute__((stdcall))
#endif
#ifndef _cdecl
  #define _cdecl __attribute__((cdecl))
#endif
#ifndef __cdecl
  #define __cdecl __attribute__((cdecl))
#endif

inline int _filelength(int fd)
{
    struct stat statbuf;
    if(fstat(fd,&statbuf)!=0)
    {
        return -1;
    }
    return statbuf.st_size;
}

// Case-insensitive string comparisons
#ifndef stricmp
  #define stricmp(a,b) strcasecmp(a,b)
#endif
#ifndef strnicmp
  #define strnicmp(a,b,c) strncasecmp(a,b,c)
#endif

#define _fstat(a,b) fstat(a,b)
#define _fileno(a) fileno(a)
#define strcmpi(a,b) strcasecmp(a,b)
#define strcmpni(a,b,c) strncasecmp(a,b,c)
#define _chmod(a,b) chmod(a,b)
#define _finite(a) finite(a)

// Min/Max macro aliases
#ifndef _min
  #define _min(a,b) (((a) < (b)) ? (a) : (b))
#endif
#ifndef _max
  #define _max(a,b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef __min
  #define __min(a,b) (((a) < (b)) ? (a) : (b))
#endif
#ifndef __max
  #define __max(a,b) (((a) > (b)) ? (a) : (b))
#endif

#endif // __LINUX_FIX_H_
