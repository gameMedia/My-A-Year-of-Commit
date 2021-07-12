#pragma once

#include "Protocol.h"

class Network
{
private:
	Network() {}
	~Network() {}
private:
	static Network* m_pInstance;
public:
	static Network* Get_Instance()
	{
		if (m_pInstance == nullptr) {
			m_pInstance = new Network();
		}
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		if (m_pInstance != nullptr)
		{
			delete m_pInstance;
		}
		m_pInstance = nullptr;
	}
public:
	bool Init(const string& strServerIP);


private:
	char m_DataBuf[8];
	string m_serverIP;
	WSADATA m_WSAdata;
	SOCKET m_client_sock;
	SOCKADDR_IN m_serverAddr;
};

