/*
 * Copyright (C) 2010-2012 Strawberry-Pr0jcts <http://strawberry-pr0jcts.com/>
 * Copyright (C) 2005-2011 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef STRAWBERRY_DEFINE_H
#define STRAWBERRY_DEFINE_H

#include <sys/types.h>

#include <ace/Basic_Types.h>
#include <ace/Default_Constants.h>
#include <ace/OS_NS_dlfcn.h>
#include <ace/ACE_export.h>

#include "Platform/CompilerDefs.h"

#define STRAWBERRY_LITTLEENDIAN 0
#define STRAWBERRY_BIGENDIAN    1

#if !defined(STRAWBERRY_ENDIAN)
#  if defined (ACE_BIG_ENDIAN)
#    define STRAWBERRY_ENDIAN STRAWBERRY_BIGENDIAN
#  else //ACE_BYTE_ORDER != ACE_BIG_ENDIAN
#    define STRAWBERRY_ENDIAN STRAWBERRY_LITTLEENDIAN
#  endif //ACE_BYTE_ORDER
#endif //STRAWBERRY_ENDIAN

typedef ACE_SHLIB_HANDLE STRAWBERRY_LIBRARY_HANDLE;

#define STRAWBERRY_SCRIPT_NAME "StrawberryScripts"
#define STRAWBERRY_SCRIPT_SUFFIX ACE_DLL_SUFFIX
#define STRAWBERRY_SCRIPT_PREFIX ACE_DLL_PREFIX
#define STRAWBERRY_LOAD_LIBRARY(libname)    ACE_OS::dlopen(libname)
#define STRAWBERRY_CLOSE_LIBRARY(hlib)      ACE_OS::dlclose(hlib)
#define STRAWBERRY_GET_PROC_ADDR(hlib,name) ACE_OS::dlsym(hlib,name)

#define STRAWBERRY_PATH_MAX PATH_MAX                            // ace/os_include/os_limits.h -> ace/Basic_Types.h

#if PLATFORM == PLATFORM_WINDOWS
#  define STRAWBERRY_EXPORT __declspec(dllexport)
#  define STRAWBERRY_IMPORT __cdecl
#else //PLATFORM != PLATFORM_WINDOWS
#  define STRAWBERRY_EXPORT export
#  if defined(__APPLE_CC__) && defined(BIG_ENDIAN)
#    define STRAWBERRY_IMPORT __attribute__ ((longcall))
#  elif defined(__x86_64__)
#    define STRAWBERRY_IMPORT
#  else
#    define STRAWBERRY_IMPORT __attribute__ ((cdecl))
#  endif //__APPLE_CC__ && BIG_ENDIAN
#endif //PLATFORM

#if !defined(DEBUG)
#  define STRAWBERRY_INLINE inline
#else //DEBUG
#  if !defined(STRAWBERRY_DEBUG)
#    define STRAWBERRY_DEBUG
#  endif //STRAWBERRY_DEBUG
#  define STRAWBERRY_INLINE
#endif //!DEBUG

#if COMPILER == COMPILER_GNU
#  define ATTR_NORETURN __attribute__((noreturn))
#  define ATTR_PRINTF(F,V) __attribute__ ((format (printf, F, V)))
#else //COMPILER != COMPILER_GNU
#  define ATTR_NORETURN
#  define ATTR_PRINTF(F,V)
#endif //COMPILER == COMPILER_GNU

typedef ACE_INT64 int64;
typedef ACE_INT32 int32;
typedef ACE_INT16 int16;
typedef ACE_INT8 int8;
typedef ACE_UINT64 uint64;
typedef ACE_UINT32 uint32;
typedef ACE_UINT16 uint16;
typedef ACE_UINT8 uint8;

#if COMPILER != COMPILER_MICROSOFT
typedef uint16      WORD;
typedef uint32      DWORD;
#endif //COMPILER

#if COMPILER == COMPILER_GNU
#  if !defined(__GXX_EXPERIMENTAL_CXX0X__) || (__GNUC__ < 4) || (__GNUC__ == 4) && (__GNUC_MINOR__ < 7)
#    define override
#  endif
#endif

typedef uint64 OBJECT_HANDLE;

#endif //STRAWBERRY_DEFINE_H