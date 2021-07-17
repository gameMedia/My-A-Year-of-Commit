#include <iostream>
#include <WS2tcpip.h>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
#define MAX_BUFFER		1024
#define SERVER_IP		"127.0.0.1"
#define SERVER_PORT		3500


// AF_INET == IPv4���ͳ� ��������
// htons == ȣ��Ʈ ����Ʈ ������ ��Ʈ��ũ ����Ʈ ������
// inet_pton ( 1, 2, 3 ) IP�ּҸ� binary ���·� �ٲ㼭 3�� �Ķ���Ϳ� �ִ´�.

// ���� : Ÿ���� �ް� �������� ������ �������� ó���ϰ� �ٽ� Ŭ���̾�Ʈ�� ����
// Client�� �ܼ��� Blocking ����ȭ IO �� �����Ǿ�����
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