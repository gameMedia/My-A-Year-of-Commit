#pragma once
#pragma once

constexpr int SERVER_PORT = 3500;
constexpr int MAX_ID_LEN = 10;


#pragma pack (push, 1)

constexpr char SC_PACKET_LOGIN_OK = 0;
constexpr char SC_PACKET_MOVE = 1;
constexpr char SC_PACKET_ENTER = 2;
constexpr char SC_PACKET_LEAVE = 3;

constexpr char CS_LOGIN = 0;
constexpr char CS_MOVE = 1;

constexpr char D_UP = 1;
constexpr char D_DOWN = 2;
constexpr char D_LEFT = 3;
constexpr char D_RIGHT = 4;

constexpr unsigned char O_PLAYER = 0;

struct sc_packet_login_ok {
	char size;
	char type;
	int  id;
	short x, y;
	short hp;
	short level;
	int   exp;
};

struct sc_packet_move {
	char size;
	char type;
	int id;
	short x, y;
};

struct sc_packet_enter {
	char size;
	char type;
	int  id;
	char name[MAX_ID_LEN];
	char o_type;
	short x, y;
};

struct sc_packet_leave {
	char size;
	char type;
	int  id;
};

struct cs_packet_login {
	char  size;
	char  type;
	char  name[MAX_ID_LEN];
};

struct cs_packet_move {
	char  size;
	char  type;
	char  direction;
	int id;
};

#pragma pack (pop)

