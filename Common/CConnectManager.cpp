#include "pch.h"
#include "CConnectManager.h"

CConnectManager::CConnectManager()
{
	m_con.clear();
}

CConnectManager::~CConnectManager()
{

}

unsigned int CConnectManager::GetNewConnectId()
{
	return m_con.size() + 1;
}

ConnectObject& CConnectManager::GetConnect(unsigned int index)
{
	return m_con.at(index);
}

void CConnectManager::CreateNewConnect(HANDLE hPipe, unsigned int id, IO_STATUS status)
{
	ConnectObject con(hPipe, id);
	m_con.push_back(con);
}

void CConnectManager::RemoveConnect(unsigned int id)
{
	std::vector<ConnectObject>::iterator iter = m_con.begin();
	for(; iter != m_con.end(); ++iter) {
		if(iter->m_connect_id == id) {
			m_con.erase(iter);
			break;
		}
	}

}