#include <iostream>
#include <WS2tcpip.h>
#include <MSWSock.h>
#pragma comment (lib,"WS2_32.lib")
#pragma comment (lib, "mswsock.lib")
#include "protocol.h"


constexpr unsigned char MAX_PACKET_SIZE = 255;
constexpr unsigned int MAX_BUFFER_SIZE = 4096;
constexpr unsigned char MAX_USER = 10;
using namespace std;


enum ENUMOP { OP_RECV, OP_SEND, OP_ACCEPT };

struct EXOVER {
	WSAOVERLAPPED over;
	ENUMOP opType;
	char iocp_buf[MAX_BUFFER_SIZE]; // �ѹ��� ������ ū 
	WSABUF wsa_buf;
};

struct client_info { // Ŭ���̾�Ʈ ������ �����ϴ� ����ü
	SOCKET m_s;
	int m_id;
	EXOVER m_recv_over;
	int m_prev_size; // ��Ŷ�� ���� ������
	char m_packet_buffer[MAX_PACKET_SIZE]; // ��Ŷ �󸶳� ���� �� �ֳ�.

	bool m_connected;
	short x, y;
	char name[MAX_ID_LEN + 1];
};

client_info g_clients[MAX_USER]; // ������ŭ �����ؾ���
int g_current_userID = 0;		 // ID �߱� ��Ȳ
HANDLE g_IOCP;					 // IOCP �ڵ�


void send_pakcet(int user_id, void* packet)
{
	char* buf = reinterpret_cast<char*>(packet);

	client_info& user = g_clients[user_id];

	EXOVER* exover = new EXOVER;
	exover->opType = OP_SEND;
	ZeroMemory(&exover->over, sizeof(exover->over));
	exover->wsa_buf.buf = exover->iocp_buf;
	exover->wsa_buf.len = buf[0];
	memcpy(exover->iocp_buf, buf, buf[0]);
	WSASend(user.m_s, &exover->wsa_buf, 1, 0, 0, &exover->over, 0);
}

void send_move_packet(int user_id, int mover)
{
	sc_packet_move packet;
	packet.id = mover;
	packet.size = sizeof(packet);
	packet.type = SC_MOVE;
	packet.x = g_clients[mover].x;
	packet.y = g_clients[mover].y;

	send_pakcet(user_id, &packet);
}

void send_login_ok_packet(int user_id)
{
	sc_packet_login_ok packet;
	packet.exp = 0;
	packet.hp = 0;
	packet.id = user_id;
	packet.level = 0;
	packet.size = sizeof(packet);
	packet.type = SC_PACKET_LOGIN_OK;
	packet.x = g_clients[user_id].x;
	packet.y = g_clients[user_id].y;

	send_pakcet(user_id, &packet);
}

void send_enter_packet(int user_id, int o_id) // user_id ���� o_id�� ������ ������.
{
	sc_packet_enter packet;
	packet.id = o_id;
	strcpy_s(packet.name, g_clients[o_id].name);
	packet.size = sizeof(packet);
	packet.type = SC_PACKET_ENTER;
	packet.x = g_clients[o_id].x;
	packet.y = g_clients[o_id].y;
	packet.o_type = O_PLAYER; // ������Ʈ�� Ÿ�� ( player�� NPC�� )
	send_pakcet(user_id, &packet);
}

void send_leave_packet(int user_id, int o_id)
{
	sc_packet_leave p;
	p.id = o_id;
	p.size = sizeof(p);
	p.type = SC_PACKET_LEAVE;

	send_pakcet(user_id, &p);
}

void do_move(int user_id, int direction)
{
	client_info& user = g_clients[user_id];
	short x = user.x;
	short y = user.y;
	switch (direction) {
	case D_UP: if (y > 0)y--; break;
	case D_DOWN:if (y < 100)y++; break;
	case D_LEFT: if (x > 0)x--; break;
	case D_RIGHT: if (x < 100)x++; break;
	default:
		cout << "�̵��Ҽ����� ��Ŷ" << endl;
	}
	for (auto& cl : g_clients) {
		if (true == cl.m_connected) {
			send_move_packet(cl.m_id, user_id);
		}
	}
}

void enter_game(int user_id)
{ // ������ �ִ� �÷��̾ ���� ������ ��������Ѵ�.
	g_clients[user_id].m_connected = true; // �ش� ������ ������
	for (int i = 0; i < MAX_USER; ++i) {
		if (true == g_clients[i].m_connected) {
			if (user_id != i) { // �� �ڽ��� ������ ������ ���� �ʿ�� ����
				send_enter_packet(user_id, i); // ���� ������ ������ ���ݱ��� ������ �÷��̾���� ������ ���������.
				send_enter_packet(i, user_id);
			}
		}
	}


}

void recvpacket_construct(int user_id, int io_byte)
{
	EXOVER& recv_over = g_clients[user_id].m_recv_over;
	client_info& client = g_clients[user_id];

	int rest_byte = io_byte; // io_byte�� ��ü ������
	char* packet_start_ptr = recv_over.iocp_buf;
	int packet_size = 0;
	if (0 != client.m_prev_size) packet_size = client.m_packet_buffer[0];
	while (rest_byte > 0) { // ó���� �����Ͱ� �����ִ�.
		if (packet_size == 0)
			packet_size = *packet_start_ptr;
		if (packet_size <= rest_byte + client.m_prev_size) { // ��Ŷ �ϼ� ����
			memcpy(client.m_packet_buffer + client.m_prev_size, packet_start_ptr, packet_size - client.m_prev_size);
			
			packet_start_ptr += packet_size - client.m_prev_size;
			rest_byte -= (packet_size - client.m_prev_size);
			packet_size = 0;
			process_packet(user_id, client.m_packet_buffer);
			client.m_prev_size = 0;

		}
		else { // ��Ŷ �ϼ��ϱ⿡�� ���� byte�� ������
			memcpy(client.m_packet_buffer + client.m_prev_size, packet_start_ptr, rest_byte);
			client.m_prev_size += rest_byte;
			rest_byte = 0;
			packet_start_ptr += rest_byte; // rest��ŭ ó�������� ó���� ��ġ �����
		}
	}

}

void process_packet(int user_id, char* buf)
{
	switch (buf[1]) {
	case CS_LOGIN:
	{
		cs_packet_login* packet = reinterpret_cast<cs_packet_login*>(buf);
		strcpy_s(g_clients[user_id].name, packet->name);
		g_clients[user_id].name[MAX_ID_LEN] = NULL;
		send_login_ok_packet(user_id);
		enter_game(user_id); // ���ӿ� ������ �� ó���� ��
	}
	break;
	case CS_MOVE:
	{
		cs_packet_move* packet = reinterpret_cast<cs_packet_move*>(buf);
		do_move(packet->id, packet->direction);
	}
	break;
	default:cout << "Unknown Packet Type Error!\n";
	}
}

void initialize_clients()
{
	for (int i = 0; i < MAX_USER; ++i) {
		g_clients[i].m_connected = false; // �ʱ⿡ ��� Ŭ���̾�Ʈ ������ �����ӻ����̴ϱ�.
	}
}

void disconnect(int user_id)
{
	g_clients[user_id].m_connected = false;
	for (auto& cl : g_clients)
		if (true == g_clients[cl.m_id].m_connected)
			send_leave_packet(cl.m_id, user_id); // �ٸ� Ŭ���̾�Ʈ���� user_id�� ������ �˷������
}

int main()
{
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 2), &WSAData);

	SOCKET l_Socket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);

	SOCKADDR_IN s_address;
	memset(&s_address, 0, sizeof(s_address));
	s_address.sin_family = AF_INET;
	s_address.sin_port = htons(SERVER_PORT);
	s_address.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	::bind(l_Socket, reinterpret_cast<SOCKADDR*>(&s_address), sizeof(s_address)); // c++ 11�� bind�� �ٸ� bind

	listen(l_Socket, SOMAXCONN);

	g_IOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);

	initialize_clients();

	CreateIoCompletionPort(reinterpret_cast<HANDLE>(l_Socket), g_IOCP, 999, 0); // socket, iocp, key(������ ��), 0
	SOCKET c_socket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	EXOVER accept_over;
	ZeroMemory(&accept_over.over, sizeof(accept_over.over));
	accept_over.opType = OP_ACCEPT;
	AcceptEx(l_Socket, c_socket, accept_over.iocp_buf,
		NULL, sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, NULL, &accept_over.over); // AcceptEx�� �Ϸ��� Ŭ���̾�Ʈ ���ӿ� ����Ϸ��� ������ �̸� �������� 

																												// ����� ���� ������ Ŭ���̾�Ʈ�� �������ִ°��̴�.


	while (true) {
		DWORD io_byte;
		ULONG_PTR key;
		WSAOVERLAPPED* over;

		// blocking����ε� Ŭ���̾�Ʈ�� �����͸� ���������� accept�� ���� ���� ����
		GetQueuedCompletionStatus(g_IOCP, &io_byte, &key, &over, INFINITE);

		EXOVER* exover = reinterpret_cast<EXOVER*>(over);
		int user_id = static_cast<int>(key);
		client_info& cl = g_clients[user_id];



		switch (exover->opType) {
		case OP_RECV:
		{
			if (0 == io_byte) { // GetQueuedCompletionStatus���� io_byte�� 0�̸� �ְ�޴°� ����.
								// accept������ io_byte�� 0���� ���� ��찡 �ִ�.
				disconnect(user_id);
			}
			else {
				recvpacket_construct(user_id, io_byte);

				ZeroMemory(&cl.m_recv_over.over, sizeof(cl.m_recv_over.over));
				DWORD flags = 0;
				WSARecv(cl.m_s, &cl.m_recv_over.wsa_buf, 1, NULL, &flags, &cl.m_recv_over.over, NULL);
			}
		}
		break;
		case OP_SEND:
			if (0 == io_byte) { // GetQueuedCompletionStatus���� io_byte�� 0�̸� �ְ�޴°� ����.
					// accept������ io_byte�� 0���� ���� ��찡 �ִ�.
				disconnect(user_id);
			}
			delete exover;
			break;
		case OP_ACCEPT:
		{
			int user_id = g_current_userID++;

			CreateIoCompletionPort(reinterpret_cast<HANDLE>(c_socket), g_IOCP, user_id, 0); // iocp�� ���
			g_current_userID = g_current_userID % MAX_USER;
			client_info& nc = g_clients[user_id];
			nc.m_id = user_id = 0;
			nc.m_prev_size = 0;
			nc.m_recv_over.opType = OP_RECV;
			ZeroMemory(&nc.m_recv_over.over, sizeof(nc.m_recv_over.over));
			nc.m_recv_over.wsa_buf.buf = nc.m_recv_over.iocp_buf;
			nc.m_recv_over.wsa_buf.len = MAX_BUFFER_SIZE;
			nc.m_s = c_socket;
			nc.x = rand(); // �ʱ���ǥ
			nc.y = rand(); // �ʱ� ��ǥ

			DWORD flags = 0;
			WSARecv(c_socket, &nc.m_recv_over.wsa_buf, 1, NULL, &flags, &nc.m_recv_over.over, NULL); // recv ������ �ݹ� �޾ƾ���

			c_socket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
			ZeroMemory(&accept_over.over, sizeof(accept_over.over));
			AcceptEx(l_Socket, c_socket, accept_over.iocp_buf,
				NULL, sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, NULL, &accept_over.over);
		}
		break;
		}
	}
}
