#include <iostream>
#include <WS2tcpip.h>
#pragma comment(lib, "WS2_32.lib")
using namespace std;

#define MAX_BUFFER 1024
#define PORT 9000

int main()
{
	WSADATA WSAdata;
	WSAStartup(MAKEWORD(2, 0), &WSAdata);

	SOCKET listen_sock = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, 0);

	SOCKADDR_IN Server_Address;
	ZeroMemory(&Server_Address, sizeof(Server_Address));
	Server_Address.sin_family = AF_INET;
	Server_Address.sin_port = htons(PORT);
	Server_Address.sin_addr.s_addr = htonl(INADDR_ANY);
	::bind(listen_sock, (sockaddr*)&Server_Address, sizeof(Server_Address));


	listen(listen_sock, SOMAXCONN);

	while (true)
	{
		SOCKADDR_IN client_Address;
		int Address_length = sizeof(client_Address);
		SOCKET client_sock = accept(listen_sock, (sockaddr*)&client_Address, &Address_length);

		char recvBuf[8] = {};
		char sendBuf[4] = {};
		int recvByte = 0;
		int sendByte = 0;
		short mouse_x = 0, mouse_y = 0;
		short row = 0, column = 0;
		short piece_row = 0, piece_column = 0;
		while (true)
		{


			recvByte = recv(client_sock, recvBuf, sizeof(recvBuf), 0);
			if (recvByte > 0)
			{

				cout << "----- recv -----\n";
				mouse_x = *((short*)&recvBuf[0]);
				mouse_y = *((short*)&recvBuf[2]);
				cout << "mouse_x - " << mouse_x << ", mouse_y - " << mouse_y << endl;

				column = (short)(mouse_x / 64);
				row = (short)(mouse_y / 64);
				piece_row = *((short*)&recvBuf[4]);
				piece_column = *((short*)&recvBuf[6]);

				if (piece_row == row && abs(column - piece_column) == 1)
				{ // x는 같고 y만 좌우 한칸
					*((short*)&sendBuf[0]) = row;
					*((short*)&sendBuf[2]) = column;
				}
				else if (piece_column == column && (abs(row - piece_row) == 1))
				{ // y는 같고 x만 좌우 한칸
					*((short*)&sendBuf[0]) = row;
					*((short*)&sendBuf[2]) = column;
				}
				else
				{ // 그외 말을 옮기면 안되는 상황
					*((short*)&sendBuf[0]) = -1;
					*((short*)&sendBuf[2]) = -1;
				}
			}
			else
				break;

			sendByte = send(client_sock, sendBuf, sizeof(sendBuf), 0);

		}
		closesocket(client_sock);
	}
	closesocket(listen_sock);
	WSACleanup();

}