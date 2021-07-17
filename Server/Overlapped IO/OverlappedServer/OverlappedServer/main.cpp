#include <iostream>
#include <map>
using namespace std;
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

#define MAX_BUFFER		1024
#define SERVER_PORT		3500

struct SOCKETINFO
{
	WSAOVERLAPPED overlapped;
	WSABUF dataBuffer;
	SOCKET socket;
	char messageBuffer[MAX_BUFFER];
};

map <SOCKET, SOCKETINFO> clients;

void CALLBACK send_callback(DWORD Error, DWORD dataBytes, LPWSAOVERLAPPED overlapped, DWORD InFlags);
void CALLBACK recv_callback(DWORD Error, DWORD dataBytes, LPWSAOVERLAPPED overlapped, DWORD InFlags);


int main()
{
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 2), &WSAData);
	SOCKET listenSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	SOCKADDR_IN serverAddr;
	memset(&serverAddr, 0, sizeof(SOCKADDR_IN));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	::bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(SOCKADDR_IN));
	listen(listenSocket, 5);
	SOCKADDR_IN clientAddr;
	int addrLen = sizeof(SOCKADDR_IN);
	memset(&clientAddr, 0, addrLen);

	while (true) {
		SOCKET clientSocket = accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen);
		clients[clientSocket] = SOCKETINFO{};
		clients[clientSocket].socket = clientSocket;
		clients[clientSocket].dataBuffer.len = MAX_BUFFER;
		clients[clientSocket].dataBuffer.buf = clients[clientSocket].messageBuffer;
		memset(&clients[clientSocket].overlapped, 0, sizeof(WSAOVERLAPPED));
		clients[clientSocket].overlapped.hEvent = (HANDLE)clients[clientSocket].socket;
		DWORD flags = 0;
		WSARecv(clients[clientSocket].socket, &clients[clientSocket].dataBuffer, 1, NULL,
			&flags, &(clients[clientSocket].overlapped), recv_callback);

	}
	closesocket(listenSocket);
	WSACleanup();
}

void CALLBACK send_callback(DWORD Error, DWORD dataBytes, LPWSAOVERLAPPED overlapped, DWORD InFlags)
{
	DWORD receiveBytes = 0;
	DWORD flags = 0;

	SOCKET client_socket = reinterpret_cast<int>(overlapped->hEvent);

	if (dataBytes == 0) { // 클라이언트가 closesocket를 했을 경우
		closesocket(clients[client_socket].socket);
		clients.erase(client_socket);
		return;
	} 

	// WSASend에 대한 콜백일 경우
	clients[client_socket].dataBuffer.len = MAX_BUFFER;

	cout << "TRACE - Send message : " << clients[client_socket].messageBuffer << " ( " << dataBytes << " bytes)\n";
	memset(&(clients[client_socket].overlapped), 0, sizeof(WSAOVERLAPPED));
	clients[client_socket].overlapped.hEvent = (HANDLE)client_socket;
	WSARecv(client_socket, &clients[client_socket].dataBuffer, 1, 0, &flags, &(clients[client_socket].overlapped), recv_callback);
}

void CALLBACK recv_callback(DWORD Error, DWORD dataBytes, LPWSAOVERLAPPED overlapped, DWORD InFlags)
{
	SOCKET client_socket = reinterpret_cast<int>(overlapped->hEvent);

	if (dataBytes == 0)
	{
		closesocket(clients[client_socket].socket);
		clients.erase(client_socket);
		return;
	}

	clients[client_socket].messageBuffer[dataBytes] = 0;
	cout << "From client : " << clients[client_socket].messageBuffer << " ( " << dataBytes << " bytes)\n";
	clients[client_socket].dataBuffer.len = dataBytes;
	memset(&(clients[client_socket].overlapped), 0, sizeof(WSAOVERLAPPED));
	clients[client_socket].overlapped.hEvent = (HANDLE)client_socket;
	WSASend(client_socket, &clients[client_socket].dataBuffer, 1, NULL, 0, &(clients[client_socket].overlapped), recv_callback);
	

}
