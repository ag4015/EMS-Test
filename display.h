#pragma once

#ifndef EMS_TEST_H_INCLUDED
#define EMS_TEST_H_INCLUDED
#include "EMS Test.h"
#endif // !EMS_TEST_H_INCLUDED

#ifndef WINDOWS_H_INCLUDED
#define	WINDOWS_H_INCLUDED
#include <windows.h>
#endif	// !WINDOWS_H_INCLUDED

#ifndef RESOURCE_H_INCLUDED
#define RESOURCE_H_INCLUDED
#include	"Resource.h"
#endif // !RESOURCE_H_INCLUDED

#ifndef STDIO_H_INCLUDED
#define STDIO_H_INCLUDED
#include <stdio.h>
#endif // !STDIO_H_INCLUDED

#ifndef ATLSTR_H_INCLUDED
#define	ATLSTR_H_INCLUDED
#include "atlstr.h"
#endif // !ATLSTR_H_INCLUDED

#define _OPEN_SYS_ITOA_EXT
#include <stdlib.h>
#include <locale>
#include <codecvt>

using namespace std;


void display_message(std::string boxText, std::string boxCaption = "Instruction", int button_type = MB_OK);
LPCWSTR to_lpcwstr(std::string a_string);
std::string int_to_string(unsigned long long number);
std::wstring get_utf16(const std::string &str, int codepage = CP_UTF8);
std::string wstring_to_string(std::wstring some_wstring);
std::string improve_path(std::string path);

void display_message(std::string boxText, std::string boxCaption, int button_type) {
	std::wstring box_text_wide = std::wstring(boxText.begin(), boxText.end());
	std::wstring box_caption_wide = std::wstring(boxCaption.begin(), boxCaption.end());
	const wchar_t* box_text_lpcwstr = box_text_wide.c_str();
	const wchar_t* box_caption_lpcwstr = box_caption_wide.c_str();
	int msgboxID = MessageBox(
		NULL,
		box_text_lpcwstr,
		box_caption_lpcwstr,
		MB_TOPMOST | MB_ICONEXCLAMATION | button_type
	);
	return;
}
LPCWSTR to_lpcwstr(std::string a_string) {
	std::wstring string_wide = std::wstring(a_string.begin(), a_string.end());
	const wchar_t* string_lpcwstr = string_wide.c_str();
	return string_lpcwstr;
}
std::string int_to_string(unsigned long long number) {
	std::stringstream ss;
	ss << number;
	return ss.str();
}
std::wstring get_utf16(const std::string &str, int codepage) {
	if (str.empty()) return std::wstring();
	int sz = MultiByteToWideChar(codepage, 0, &str[0], (int)str.size(), 0, 0);
	std::wstring res(sz, 0);
	MultiByteToWideChar(codepage, 0, &str[0], (int)str.size(), &res[0], sz);
	return res;
 }
std::string wstring_to_string(std::wstring some_wstring) {
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;
	std::string converted_str = converter.to_bytes(some_wstring);
	return converted_str;
}
std::string improve_path(std::string path) {
	int size = path.length();
	char ch;
	int i;
	for (i = size - 1; i > 3; i--) {
		if (path[i - 1] == 'S' && path[i - 2] == 'M' && path[i-3] == 'E') {
			break;
		}
	}
	path[i - 3] = 'P';
	path[i - 2] = 'r';
	path[i - 1] = 'o';
	path[i] = 'j';
	path[i + 1] = 'e';
	path[i + 2] = 'c';
	path[i + 3] = 't';
	path[i + 4] = 's';
	path[i + 5] = '\0';
	/*while (i + 4 < size) {
		path[i]
	}*/
	return path;
}
