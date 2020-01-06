#include "pch.h"
#include "Common.h"
#include "StringTool.h"

IServer::IServer()
{
	m_type = LOAD_NONE;
	m_iocp = INVALID_HANDLE_VALUE;
	SYSTEM_INFO sys_info;
	memset(&sys_info, 0, sizeof(sys_info));
	GetSystemInfo(&sys_info);
	m_hThreadCount = sys_info.dwNumberOfProcessors;
	m_run = false;
}

IServer::~IServer()
{

}

void IServer::SetType(LOAD_TYPE type)
{
	m_type = type;
}

bool IServer::Startup()
{
	switch(m_type)
	{
	case LOAD_PIPE:
	{
		if(!InitIOCP()) {
			return false;
		}
		m_run = true;
		InitThreadPool();
		InitListenThread();

	}break;
	case LOAD_SOCKET:
		break;
	default:
		break;
	}
	return true;
}

bool IServer::IsRun()
{
	return m_run;
}

HANDLE IServer::GetNamedPipe()
{
	return m_hPipe;
}

bool IServer::InitNamedPipe()
{
	wchar_t* pszPipeName = StringTool::A2W(m_pszPipeName);
	m_hPipe = CreateNamedPipeW(pszPipeName, PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED, PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT, PIPE_UNLIMITED_INSTANCES, NULL, NULL, 5000, NULL);
	if(m_hPipe == INVALID_HANDLE_VALUE)
		return false;

	return true;
}

bool IServer::InitIOCP()
{
	m_iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, m_hThreadCount);
	if(m_iocp == INVALID_HANDLE_VALUE)
		return false;

	return true;
}

DWORD WINAPI IServer::WorkerThread(LPVOID lpParam)
{
	IServer* pServer = (IServer*)lpParam;
	if(pServer) {
		while(pServer->IsRun()) {
			
		}
	}
	return 0;
}

DWORD WINAPI IServer::ListenThread(LPVOID lpParam)
{
	IServer* pServer = (IServer*)lpParam;
	if(pServer) {
		while(pServer->IsRun()) {
			wchar_t* pszPipeName = StringTool::A2W(pServer->m_pszPipeName);
			HANDLE hPipe = CreateNamedPipeW(pszPipeName, PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED, PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT, PIPE_UNLIMITED_INSTANCES, NULL, NULL, 5000, NULL);
			OVERLAPPED op;
			op.Offset = 0;
			op.OffsetHigh = 0;
			op.hEvent = NULL;
			memset(&op, 0, sizeof(op));
			if(ConnectNamedPipe(hPipe, &op)) {
				//create new connect
				unsigned int id = pServer->m_ConManager.GetNewConnectId();
				pServer->m_ConManager.CreateNewConnect(hPipe, id);
				IOContext* ctx = new IOContext;
				ctx->hEvent = NULL;
				ctx->Offset = 0;
				ctx->OffsetHigh = 0;
				ctx->m_hPipe = hPipe;
				ctx->m_status = IOST_RECV;
				DWORD dwReadByte = 0;
				if(!ReadFile(hPipe, ctx->m_buff, MAX_BUF, &dwReadByte, ctx)) {
					DWORD dwError = GetLastError();
					if(dwError != ERROR_IO_PENDING) {
						delete ctx;
						ctx = NULL;
						pServer->m_ConManager.RemoveConnect(id);
					}
				}
			}

		}
	}
	return 0;
}

void IServer::InitThreadPool()
{
	for(unsigned int n = 0; n < m_hThreadCount; ++n) {
		HANDLE hThread = CreateThread(NULL, 0, WorkerThread, this, 0, NULL);
		if(hThread) CloseHandle(hThread);
	}
}

void IServer::InitListenThread()
{
	HANDLE hThread = CreateThread(NULL, 0, ListenThread, this, 0, NULL);
	if(hThread) CloseHandle(hThread);
}

bool IServer::InitSocket()
{
	return true;
}

void IServer::SetIP(const char* pszIP, const short nPort)
{
	memset(&m_pszIP, 0, MAX_PATH);
	memcpy(&m_pszIP, pszIP, strlen(pszIP));
	m_nPort = nPort;
}

void IServer::SetPipeName(const char* pszPipeName)
{
	memset(&m_pszPipeName, 0, MAX_PATH);
	memcpy(&m_pszPipeName, pszPipeName, strlen(pszPipeName));
}

//client
bool IClient::ConnectSocketServer(char* pszIP, short nPort)
{
	return true;
}

bool IClient::ConnectNamedPipeServer(char* pszPipeName)
{
	return true;
}