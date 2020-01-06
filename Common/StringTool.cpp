#include "pch.h"
#include "StringTool.h"

wchar_t* StringTool::A2W(const char* pszSrc)
{
	int nSize = ::MultiByteToWideChar(CP_ACP, 0, pszSrc, strlen(pszSrc), NULL, 0);
	if(nSize <= 0) return NULL;

	wchar_t* pszRet = new wchar_t[nSize + 2];
	memset(pszRet, 0, nSize + 2);
	nSize = ::MultiByteToWideChar(CP_ACP, 0, pszSrc, strlen(pszSrc), pszRet, nSize);
	
	return pszRet;
}

char* StringTool::W2A(const wchar_t* pszSrc)
{
	char* pszRet = NULL;
	int nSize = ::WideCharToMultiByte(CP_ACP, 0, pszSrc, wcslen(pszSrc), NULL, -1, NULL, NULL);
	if(nSize <= 0) return NULL;

	pszRet = new char[nSize + 1];
	memset(&pszRet, 0, nSize + 1);
	::WideCharToMultiByte(CP_ACP, 0, pszSrc, wcslen(pszSrc), pszRet, nSize, NULL, NULL);

	return pszRet;
}