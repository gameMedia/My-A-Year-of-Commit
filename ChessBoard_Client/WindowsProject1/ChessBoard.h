#pragma once

#include <Windows.h>
#include "resource.h"
#include "BoardSlot.h"

typedef struct Chesspiece
{
	int Row_X;
	int Column_Y;
	HBITMAP Bit_Image;
}PIECE;
// 클래스의 전방 선언은 포인터만 허용된다.

class ChessBoard
{
public:
	ChessBoard(HINSTANCE& hInst);
	~ChessBoard();

public:
	void DrawBoard(HDC& hdc, HDC& memDC);
	void SetPiecePosition(int _row, int _column);
	
private:
	HINSTANCE m_hInst;

	BoardSlot slot[8][8];
	PIECE m_Piece;
	HBITMAP boardBit;

};

