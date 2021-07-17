#include <iostream>
#include <WS2tcpip.h>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
#define MAX_BUFFER		1024
#define SERVER_IP		"127.0.0.1"
#define SERVER_PORT		3500


// AF_INET == IPv4인터넷 프로토콜
// htons == 호스트 바이트 순서를 네트워크 바이트 순서로
// inet_pton ( 1, 2, 3 ) IP주소를 binary 형태로 바꿔서 3번 파라미터에 넣는다.

// 순서 : 타이핑 받고 서버에게 보내고 서버에서 처리하고 다시 클라이언트로 보냄
// Client는 단순한 Blocking 동기화 IO 로 구현되어있음
int main()
{
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 0), &WSAData);
	
	SOCKET serverSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, 0);
	SOCKADDR_IN serverAddr;
	memset(&serverAddr, 0, sizeof(SOCKADDR_IN));
	
	serverAddr.sin_family = AF_INET; 
	serverAddr.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr);
	connect(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	
	while (true) {
		char messageBuffer[MAX_BUFFER];
		cout << "Enter Message : ";
		cin >> messageBuffer;
		int bufferLen = static_cast<int> (strlen(messageBuffer));
		int sendBytes = send(serverSocket, messageBuffer, bufferLen, 0);
		cout << "Sent : " << messageBuffer << " ( " << sendBytes << " bytes)\n";
		int receiveBytes = recv(serverSocket, messageBuffer, MAX_BUFFER, 0);
		if (receiveBytes == 0)break;
		messageBuffer[receiveBytes] = 0;
		cout << "Received : " << messageBuffer << " ( " << receiveBytes << " bytes)\n";
	}

	closesocket(serverSocket);
	WSACleanup();
}