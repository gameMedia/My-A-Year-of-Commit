#pragma once

#include "Protocol.h"

class ChessBoard;

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
	void Set_ChessBoard(ChessBoard* chessboard);
	void MoveChessPiece(short mouse_x, short mouse_y);
	void Close_Server() { closesocket(m_client_sock); }

private:
	char m_SendBuf[8]; 
	string m_serverIP;
	WSADATA m_WSAdata;
	SOCKET m_client_sock;
	SOCKADDR_IN m_serverAddr;

	ChessBoard* m_ChessBoard;

};

