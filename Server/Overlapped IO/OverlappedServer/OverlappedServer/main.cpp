#include <iostream>
#include <map>
using namespace std;
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

#define MAX_BUFFER		1024
#define SERVER_PORT		3500


struct SOCKETINFO
{
	WSAOVERLAPPED overlapped; // 1개의 클라이언트마다 적어도 1개 있어야 함
	WSABUF dataBuffer; // 버퍼를 묶어서 관리하는 배열
	SOCKET socket; // 소켓
	char messageBuffer[MAX_BUFFER]; // 실제 사용하는 버퍼
};

// map
// 여러개의 클라이언트가 동시접속을 하고 관리를 해야하니까
// 그러한 정보를 컨테이너에 넣어서 관리하고
// 클라이언트가 동시다발적으로 접속 & 접속해제를 하기 때문에

// map < playerID, SOCKETINFO> clients 소켓은 플레이어의 ID로 관리하는게 직관적이다.
map <SOCKET, SOCKETINFO> clients;

void CALLBACK send_callback(DWORD Error, DWORD dataBytes, LPWSAOVERLAPPED overlapped, DWORD InFlags);
void CALLBACK recv_callback(DWORD Error, DWORD dataBytes, LPWSAOVERLAPPED overlapped, DWORD InFlags); // callback에서는 어떤 소켓의 recv가 완료되었는가를 알아야함. == 이를 알려면 overlapped구조체를 통하는 수 밖에 없다.


int main()
{
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 2), &WSAData);
	SOCKET listenSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED); // WSA_FLAG_OVERLAPPED == socket Overlapped 설정 해주기
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
		clients[clientSocket].overlapped.hEvent = (HANDLE)clients[clientSocket].socket; // 소켓을 넣어서 무슨 소켓이 보낸 recv인가를 구분할 수 있도록 함, 운영체제가 건들지 않으니까 가능한 일
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
