#include "Network.h"
#include "ChessBoard.h"

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

void Network::Set_ChessBoard(ChessBoard* chessboard)
{
	cout << "��Ʈ��ũ�� ü�����带 �˷���" << endl;
	m_ChessBoard = chessboard;
}

void Network::MoveChessPiece(short mouse_x, short mouse_y)
{
	int sendByte = 0;
	int recvByte = 0;
	char recvBuf[4] = {};

	// make SendBuf
	*((short*)&m_SendBuf[0]) = mouse_x;
	*((short*)&m_SendBuf[2]) = mouse_y;
	*((short*)&m_SendBuf[4]) = m_ChessBoard->GetPiecePos_row();
	*((short*)&m_SendBuf[6]) = m_ChessBoard->GetPiecePos_column();

	sendByte = send(m_client_sock, m_SendBuf, sizeof(m_SendBuf), 0);
	recvByte = recv(m_client_sock, recvBuf, sizeof(recvBuf), 0);

	if (recvByte > 0)
	{ // recvData
		short row = *((short*)&recvBuf[0]);
		short column = *((short*)&recvBuf[2]);

		if (row >= 0 && column >= 0)
		{ // �� �ű� ��� -1�� �Ѿ��
			//cout << "���Ű�" << endl;
			m_ChessBoard->SetPiecePosition(row, column);
		}
	}
}
