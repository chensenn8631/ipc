#pragma once
class StringTool {
public:
	static wchar_t* A2W(const char* pszSrc);
	static char* W2A(const wchar_t* pszSrc);
};