#pragma once
#include "ConnectObject.h"
#include <vector>

class CConnectManager {
public:
	CConnectManager();
	~CConnectManager();
	unsigned int GetNewConnectId();
	ConnectObject& GetConnect(unsigned int index);
	void CreateNewConnect(HANDLE hPipe, unsigned int id, IO_STATUS status = IOST_RECV);
	void RemoveConnect(unsigned int id);
private:
	std::vector<ConnectObject> m_con;
};