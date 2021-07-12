#include "Network.h"


Network* Network::m_pInstance = nullptr;

bool Network::Init(const string& strServerIP)
{
	int retval = 0;
	m_serverIP = strServerIP;

	WSAStartup(MAKEWORD(2, 0), &m_WSAdata);
	
	m_client_sock = WSASocket(AF_INET, SOCK_STREAM, 0, 0, 0, 0);
	
	memset(&m_serverAddr, 0, sizeof(SOCKADDR_IN));
	m_serverAddr.sin_family = AF_INET;
	m_serverAddr.sin_port = htons(PORT);
	//m_serverAddr.sin_addr.S_un.S_addr = inet_addr(m_serverIP.c_str());
	inet_pton(AF_INET, (PCSTR)m_serverIP.c_str(), &m_serverAddr.sin_addr);
	retval = connect(m_client_sock, (SOCKADDR*)&m_serverAddr, sizeof(m_serverAddr));

	if (retval == SOCKET_ERROR) {
		return false;
	}

	

	return true;
}
