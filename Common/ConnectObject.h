#pragma once
#include "pch.h"

#define MAX_BUF 0x1000

typedef enum {IOST_RECV,IOST_SEND}IO_STATUS;

class IOContext : public OVERLAPPED
{
public:
	IO_STATUS m_status;
	char m_buff[MAX_BUF];
	HANDLE m_hPipe;
};

class CompleteKey {
public:
};

class ConnectObject {
public:
	ConnectObject(HANDLE hPipe, unsigned int id, IO_STATUS status = IOST_RECV);
public:
	unsigned int m_connect_id;
	IOContext* m_ctx;
};