/*
    SDL - Simple DirectMedia Layer
    Copyright (C) 1997-2009 Sam Lantinga

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    Sam Lantinga
    slouken@libsdl.org
*/

#ifndef _SDL_config_android_h
#define _SDL_config_android_h

#include "SDL_platform.h"

/* This is the android configuration that can be used to build SDL */

#include <stdarg.h>

/*
// these are already defined in android include files
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int16_t;
typedef unsigned short uint16_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;
typedef unsigned int size_t;
typedef unsigned long uintptr_t; 
*/

/* Enable the dummy audio driver (src/audio/dummy/\*.c) */
//#define SDL_AUDIO_DRIVER_DUMMY	1
#define SDL_AUDIO_DRIVER_OSS	1 

/* Enable the stub cdrom driver (src/cdrom/dummy/\*.c) */
#define SDL_CDROM_DISABLED	1

/* Enable the stub joystick driver (src/joystick/dummy/\*.c) */
#define SDL_JOYSTICK_DISABLED	1

/* Enable the stub shared object loader (src/loadso/dummy/\*.c) */
//#define SDL_LOADSO_DISABLED	1
#define SDL_LOADSO_DLOPEN 1

/* Enable the stub thread support (src/thread/generic/\*.c) */
//#define SDL_THREADS_DISABLED	1
#define SDL_THREAD_PTHREAD 1
#define SDL_THREAD_PTHREAD_RECURSIVE_MUTEX 1

/* Enable the stub timer support (src/timer/dummy/\*.c) */
//SDL_TIMERS_DISABLED
#define SDL_TIMER_UNIX		1

/* Enable the dummy video driver (src/video/dummy/\*.c) */
//SDL_VIDEO_DRIVER_DUMMY
#define SDL_VIDEO_DRIVER_FBCON	1

//#define HAVE_STDIO_H 1 
#define HAVE_LIBC 1

#ifdef  HAVE_LIBC

#define HAVE_ALLOCA_H  1
#define HAVE_SYS_TYPES_H 1
#define HAVE_STDIO_H  1
#define STDC_HEADERS  1
#define HAVE_STDLIB_H  1
#define HAVE_STDARG_H  1
// defined in android includes, so undef it
#undef HAVE_MALLOC_H
#define HAVE_MALLOC_H  1
#define HAVE_MEMORY_H  1
//#define HAVE_STRING_H  1
//#define HAVE_STRINGS_H  1
#define HAVE_INTTYPES_H  1
#define HAVE_STDINT_H  1
#define HAVE_CTYPE_H  1
#define HAVE_MATH_H   1
//#define HAVE_ICONV_H  1
#define HAVE_SIGNAL_H  1
#define HAVE_ALTIVEC_H  1
#define HAVE_MALLOC   1
#define HAVE_CALLOC   1
#define HAVE_REALLOC  1
#define HAVE_FREE   1
#define HAVE_ALLOCA   1
#define HAVE_GETENV   1
#define HAVE_PUTENV   1
#define HAVE_UNSETENV  1
#define HAVE_QSORT  1
#define HAVE_ABS  1
#define HAVE_BCOPY  1
#define HAVE_MEMSET  1
#define HAVE_MEMCPY  1
#define HAVE_MEMMOVE  1
#define HAVE_MEMCMP  1
#define HAVE_STRLEN  1
//#define HAVE_STRLCPY  1
//#define HAVE_STRLCAT  1
#define HAVE_STRDUP  1
#define HAVE__STRREV  1
#define HAVE__STRUPR  1
#define HAVE__STRLWR  1
#define HAVE_INDEX  1
#define HAVE_RINDEX  1
#define HAVE_STRCHR  1
#define HAVE_STRRCHR  1
#define HAVE_STRSTR  1
#define HAVE_ITOA  1
#define HAVE__LTOA  1
#define HAVE__UITOA  1
#define HAVE__ULTOA  1
#define HAVE_STRTOL  1
#define HAVE_STRTOUL  1
#define HAVE__I64TOA  1
#define HAVE__UI64TOA  1
#define HAVE_STRTOLL  1
#define HAVE_STRTOULL  1
#define HAVE_STRTOD  1
#define HAVE_ATOI  1
#define HAVE_ATOF  1
#define HAVE_STRCMP  1
#define HAVE_STRNCMP  1
#define HAVE__STRICMP  1
#define HAVE_STRCASECMP  1
#define HAVE__STRNICMP  1
#define HAVE_STRNCASECMP  1
#define HAVE_SSCANF  1
#define HAVE_SNPRINTF  1
#define HAVE_VSNPRINTF  1
//#define HAVE_ICONV
#define HAVE_SIGACTION  1
#define HAVE_SETJMP  1
#define HAVE_NANOSLEEP  1
//#define HAVE_CLOCK_GETTIME  1
#define HAVE_DLVSYM  1
#define HAVE_GETPAGESIZE  1
#define HAVE_MPROTECT  1
#else
    #include <stdarg.h>
#endif

#endif /* _SDL_config_minimal_h */
