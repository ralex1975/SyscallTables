/*******************************************************************************
*
*  (C) COPYRIGHT AUTHORS, 2016 - 2018
*
*  TITLE:       CUI.C
*
*  VERSION:     1.12
*
*  DATE:        10 Jan 2018
*
*  Console output.
*
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
* TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
*******************************************************************************/
#include "main.h"

/*
* cuiPrintText
*
* Purpose:
*
* Output text to the console or file.
*
*/
VOID cuiPrintText(
	_In_ HANDLE hOutConsole,
	_In_ LPWSTR lpText,
	_In_ BOOL ConsoleOutputEnabled,
	_In_ BOOL UseReturn
	)
{
	SIZE_T consoleIO;
	DWORD bytesIO;
	LPWSTR Buffer;

	if (lpText == NULL)
		return;

	consoleIO = _strlen(lpText);
	if ((consoleIO == 0) || (consoleIO > MAX_PATH * 4))
		return;

	consoleIO = consoleIO * sizeof(WCHAR) + 4 + sizeof(UNICODE_NULL);
	Buffer = (LPWSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, consoleIO);
	if (Buffer) {

		_strcpy(Buffer, lpText);
		if (UseReturn) _strcat(Buffer, TEXT("\r\n"));

		consoleIO = _strlen(Buffer);

		if (ConsoleOutputEnabled != FALSE) {
			WriteConsole(hOutConsole, Buffer, (DWORD)consoleIO, &bytesIO, NULL);
		}
		else {
			WriteFile(hOutConsole, Buffer, (DWORD)(consoleIO * sizeof(WCHAR)), &bytesIO, NULL);
		}
		HeapFree(GetProcessHeap(), 0, Buffer);
	}
}

/*
* cuiPrintTextLastError
*
* Purpose:
*
* Output LastError translated code to the console or file.
*
*/
VOID cuiPrintTextLastError(
    _In_ HANDLE hOutConsole,
    _In_ BOOL ConsoleOutputEnabled,
    _In_ BOOL UseReturn
    )
{
    WCHAR szTextBuffer[512];
    DWORD dwLastError = GetLastError();
    
    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastError, LANG_USER_DEFAULT, (LPWSTR)&szTextBuffer, 512, NULL);
    cuiPrintText(hOutConsole, szTextBuffer, ConsoleOutputEnabled, UseReturn);
}
