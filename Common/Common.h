#pragma once
#include "CConnectManager.h"

#ifdef COMMON_EXPORTS
#define COMMON_API __declspec(dllexport)
#else
#define COMMON_API __declspec(dllimport)
#endif

typedef enum  {
	LOAD_NONE,
	LOAD_PIPE,
	LOAD_SOCKET
}LOAD_TYPE;

class COMMON_API IBase
{
public:
	virtual void SendData(char* pszData, int nLen) = 0;
	virtual void OnDataArrive(char* pszData, int nLen) = 0;
};

class COMMON_API IServer : public IBase
{
public:
	IServer();
	~IServer();
	
public:
	virtual void SetType(LOAD_TYPE type);
	virtual void SetIP(const char* pszIP, const short nPort);
	virtual void SetPipeName(const char* pszPipeName);
	virtual bool Startup();
	
private:
	bool IsRun();
	HANDLE GetNamedPipe();
	bool InitNamedPipe();
	bool InitIOCP();
	void InitThreadPool();
	void InitListenThread();
	static DWORD WINAPI WorkerThread(LPVOID lpParam);
	static DWORD WINAPI ListenThread(LPVOID lpParam);
	bool InitSocket();
	
private:
	LOAD_TYPE m_type;
	char m_pszIP[MAX_PATH];
	short m_nPort;
	char m_pszPipeName[MAX_PATH];
	HANDLE m_iocp;
	HANDLE m_hPipe;
	unsigned int m_hThreadCount;
	bool m_run;
	CConnectManager m_ConManager;
};

class COMMON_API IClient : public IBase
{
public:
	virtual bool ConnectSocketServer(char* pszIP, short nPort);
	virtual bool ConnectNamedPipeServer(char* pszPipeName);
};
