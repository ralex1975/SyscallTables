/*******************************************************************************
*
*  (C) COPYRIGHT AUTHORS, 2016 - 2018
*
*  TITLE:       MAIN.H
*
*  VERSION:     1.12
*
*  DATE:        10 Jan 2018
*
*  Common header file.
*
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
* TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
*******************************************************************************/

#pragma once

#if !defined UNICODE
#error ANSI build is not supported
#endif

#if (_MSC_VER >= 1900) 
#ifdef _DEBUG
#pragma comment(lib, "vcruntimed.lib")
#pragma comment(lib, "ucrtd.lib")
#else
#pragma comment(lib, "libvcruntime.lib")
#endif
#endif

#pragma warning(disable: 4054)  // from function pointer to data pointer
#pragma warning(disable: 4091)  // 'typedef ': ignored on left of '' when no variable is declared
#pragma warning(disable: 6320)  // exception-filter expression is the constant EXCEPTION_EXECUTE_HANDLER  

#include <windows.h>
#include <DbgHelp.h>
#include "minirtl\minirtl.h"
#include "minirtl\_filename.h"
#include "cui.h"
#include "hde\hde64.h"

#pragma comment(lib, "Version.lib")

#define W32SYSCALLSTART 0x1000

typedef struct _SYMBOL_ENTRY {
    struct _SYMBOL_ENTRY *Next;
    LPWSTR   Name;
    SIZE_T   NameLen;
    DWORD64  Address;
} SYMBOL_ENTRY, *PSYMBOL_ENTRY;

typedef struct _SERVICE_ENTRY {
    struct _SERVICE_ENTRY *Next;
    LPWSTR Name;
    ULONG  Index;
} SERVICE_ENTRY, *PSERVICE_ENTRY;

typedef  DWORD(WINAPI *pfnSymSetOptions)(
    _In_ DWORD   SymOptions
    );

typedef BOOL(WINAPI *pfnSymInitializeW)(
    _In_ HANDLE hProcess,
    _In_opt_ PCWSTR UserSearchPath,
    _In_ BOOL fInvadeProcess
    );

typedef DWORD64(WINAPI *pfnSymLoadModuleExW)(
    _In_ HANDLE hProcess,
    _In_opt_ HANDLE hFile,
    _In_opt_ PCWSTR ImageName,
    _In_opt_ PCWSTR ModuleName,
    _In_ DWORD64 BaseOfDll,
    _In_ DWORD DllSize,
    _In_opt_ PMODLOAD_DATA Data,
    _In_opt_ DWORD Flags
    );

typedef BOOL(WINAPI *pfnSymEnumSymbolsW)(
    _In_ HANDLE hProcess,
    _In_ ULONG64 BaseOfDll,
    _In_opt_ PCWSTR Mask,
    _In_ PSYM_ENUMERATESYMBOLS_CALLBACKW EnumSymbolsCallback,
    _In_opt_ PVOID UserContext
    );

typedef BOOL(WINAPI *pfnSymUnloadModule64)(
    _In_ HANDLE hProcess,
    _In_ DWORD64 BaseOfDll
    );

typedef BOOL(WINAPI *pfnSymCleanup)(
    _In_ HANDLE hProcess
    );

typedef BOOL(WINAPI *pfnSymFromAddrW)(
    _In_ HANDLE hProcess,
    _In_ DWORD64 Address,
    _Out_opt_ PDWORD64 Displacement,
    _Inout_ PSYMBOL_INFOW Symbol
    );

#define PathFileExists(lpszPath) (GetFileAttributes(lpszPath) != (DWORD)-1)
