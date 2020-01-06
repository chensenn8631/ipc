#include "pch.h"
#include "ConnectObject.h"

ConnectObject::ConnectObject(HANDLE hPipe, unsigned int id, IO_STATUS status)
{
	IOContext* ctx = new IOContext;
	ctx->Internal = 0;
	ctx->InternalHigh = 0;
	ctx->hEvent = NULL;
	ctx->m_status = status;
	ctx->m_hPipe = hPipe;
	m_connect_id = id;
}