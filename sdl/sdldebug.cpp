/*
* $Logfile: /DescentIII/Main/linux/sdldebug.cpp $
* $Revision: 1.1.1.1 $
* $Date: 2000/04/18 00:00:39 $
* $Author: icculus $
*
* Linux SDL debugging routines
*
* $Log: sdldebug.cpp,v $
* Revision 1.1.1.1  2000/04/18 00:00:39  icculus
* initial checkin
*
 *
 * 8     7/22/99 1:21p Jeff
 * added 3rd debugging window
 *
 * 7     7/14/99 9:09p Jeff
 * added comment header
*
* $NoKeywords: $
*/

#include "debug.h"
#include "mono.h"
#include "logfile.h"
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////

static logfile AppLogFile;

void Debug_ConsolePrintf(int n, char *format, ...)
{
    va_list args;
    va_start(args, format);
    
    char msg[1024];
    vsnprintf(msg, sizeof(msg), format, args);
    va_end(args);

    // Print window badge if applicable, then write to stdout/stderr
    if (n == 1) { // Window 1 is "Warnings" in Debug_Init
        fprintf(stderr, "[WARN] %s", msg);
        fflush(stderr);
    } else {
        printf("[DEBUG %d] %s", n, msg);
        fflush(stdout);
    }

    AppLogFile.puts(msg);
    AppLogFile.update();
}

// Positioned console print: mprintf_at((window, row, col, "format", ...))
void Debug_ConsolePrintf(int n, int row, int col, char *format, ...)
{
    va_list args;
    va_start(args, format);

    char msg[1024];
    vsnprintf(msg, sizeof(msg), format, args);
    va_end(args);

    printf("[DEBUG %d @ %d,%d] %s", n, row, col, msg);
    fflush(stdout);

    AppLogFile.puts(msg);
    AppLogFile.update();
}

bool Debug_Logfile(const char *filename) 
{ 
    if (filename && filename[0] != '\0') {
        AppLogFile.start(filename, "Descent 3 Log");
        return true;
    }
    return false;
}

void Debug_LogWrite(const char *str) { fprintf(stdout, "%s\n", str); fflush(stdout); }
bool Debug_ConsoleInit() { return true; }
void Debug_ConsoleOpen(int n, int row, int col, int width, int height, char *title) {}
void Debug_ConsoleClose(int n) {}
void Debug_ConsoleRedirectMessages(int virtual_window, int physical_window) {}
bool Debug_break=false;
bool Debug_mono=false;

void nw_InitTCPLogging(char *ip, unsigned short port)
{
    // TCP logging stub for Linux/SDL targets
}

void nw_TCPPrintf(int n, char *format, ...)
{
    // TCP logging printf stub
}

char *Debug_DumpInfo();

//	if we are running under a debugger, then pass true
bool Debug_Init(bool debugger, bool mono_debug)
{
#ifndef RELEASE
	Debug_break = debugger;

	if (mono_debug) {
		Debug_ConsoleInit();
		Debug_ConsoleOpen( 0, 9, 1, 78, 15, "Debug Spew");
		Debug_ConsoleOpen( 1, 1, 1, 58,  6, "Warnings");
		Debug_ConsoleOpen( 2, 1,61, 18,  6, "Stats");

		mprintf((0, "Linux system.\n"));
	}

	if (Debug_break)
		mprintf((0, "Debug Break enabled.\n"));

#endif	//ifndef RELEASE

	return true;
}

//Does a messagebox with a stack dump
//Messagebox shows topstring, then stack dump, then bottomstring
//Return types are the same as the Windows return values
int Debug_ErrorBox(int type,const char *topstring, const char *title,const char *bottomstring)
{
	int answer = 0;
	char *dumptext = Debug_DumpInfo();

	fprintf(stderr,"\r\n%s(%s)\r\n\n%s\r\n\n%s\r\n",title,topstring,dumptext,bottomstring);

	debug_break();

	return answer;
}

// displays an message box
// Returns the same values as the Win32 MessageBox() function
int Debug_MessageBox(int type, const char *title, const char *str)
{
	return Debug_ErrorBox(type,str,"Descent 3 Message","");
}

///////////////////////////////////////////////////////////////////////////////

char *Debug_DumpInfo(void)
{
	static char e[]= "System Error";
	return e;
}
