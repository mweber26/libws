
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#ifdef WIN32
#include <io.h>
#endif
#include "libws_test_helpers.h"

int libws_test_parse_cmdline(int argc, char **argv)
{
	return 0;
}

enum libws_test_color_e
{
	NORMAL,
	GREEN,
	RED,
	BRIGHT,
	STATUS
};

void libws_test_vprintf(FILE *target, enum libws_test_color_e test_color, const char *fmt, va_list args)
{
	#ifdef WIN32
	WORD color = 0;
	
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);

	switch (test_color)
	{
		default:
		case NORMAL: break;
		case GREEN: color = (FOREGROUND_GREEN | FOREGROUND_INTENSITY); break;
		case RED: color = (FOREGROUND_RED | FOREGROUND_INTENSITY); break;
		case BRIGHT: color = (FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED); break;
		case STATUS: color = FOREGROUND_INTENSITY; break;
	}

	// Set color.
	if (color) SetConsoleTextAttribute(hstdout, color);

	vfprintf(target, fmt, args);

	// Reset color.
	SetConsoleTextAttribute(hstdout, csbi.wAttributes);

	#else // end WIN32

	#define ANSI_COLOR_BLACK		"\x1b[22;30m"
	#define ANSI_COLOR_RED			"\x1b[22;31m"
	#define ANSI_COLOR_GREEN		"\x1b[22;32m"
	#define ANSI_COLOR_YELLOW		"\x1b[22;33m"
	#define ANSI_COLOR_BLUE			"\x1b[22;34m"
	#define ANSI_COLOR_MAGENTA		"\x1b[22;35m"
	#define ANSI_COLOR_CYAN			"\x1b[22;36m"
	#define ANSI_COLOR_GRAY			"\x1b[22;37m"
	#define ANSI_COLOR_DARK_GRAY	"\x1b[01;30m"
	#define ANSI_COLOR_LIGHT_RED	"\x1b[01;31m"
	#define ANSI_COLOR_LIGHT_GREEN	"\x1b[01;32m"
	#define ANSI_COLOR_LIGHT_BLUE	"\x1b[01;34m"
	#define ANSI_COLOR_LIGHT_MAGNETA "\x1b[01;35m"
	#define ANSI_COLOR_LIGHT_CYAN	"\x1b[01;36m"
	#define ANSI_COLOR_WHITE		"\x1b[01;37m"
	#define ANSI_COLOR_RESET		"\x1b[0m"

	switch (test_color)
	{
		default:
		case NORMAL: break;
		case GREEN: fprintf(target, ANSI_COLOR_LIGHT_GREEN);  break;
		case RED:	fprintf(target, ANSI_COLOR_LIGHT_RED); break;
		case BRIGHT: fprintf(target, ANSI_COLOR_WHITE); break;
		case STATUS: fprintf(target, ANSI_COLOR_DARK_GRAY); break;
	}

	vfprintf(target, fmt, args);

	fprintf(target, ANSI_COLOR_RESET);
	
	#endif
}

void libws_test_printf(FILE *target, enum libws_test_color_e test_color, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	libws_test_vprintf(target, test_color, fmt, args);

	va_end(args);
}

void libws_test_SUCCESS(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	
	libws_test_printf(stdout, BRIGHT, "[");
	libws_test_printf(stdout, GREEN, "SUCCESS");
	libws_test_printf(stdout, BRIGHT, "] ");
	vfprintf(stdout, fmt, args);
	printf("\n");

	va_end(args);
}

void libws_test_FAILURE(const char *fmt, ...)
{
	// TODO: Make a version of this that saves the output to a buffer instead. 
	// And queues all log messages, so that we can present all failure at the end
	// of a long test!
	va_list args;
	va_start(args, fmt);
	
	libws_test_printf(stderr, BRIGHT, "[");
	libws_test_printf(stderr, RED, "FAILURE");
	libws_test_printf(stderr, BRIGHT, "] ");
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");

	va_end(args);
}

void libws_test_STATUS_ex(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	
	libws_test_vprintf(stdout, STATUS, fmt, args);

	va_end(args);
}

void libws_test_STATUS(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	
	libws_test_vprintf(stdout, STATUS, fmt, args);
	printf("\n");

	va_end(args);
}


