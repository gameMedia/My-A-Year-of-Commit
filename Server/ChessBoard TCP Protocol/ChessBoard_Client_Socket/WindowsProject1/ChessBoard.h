#pragma once

#include <Windows.h>
#include "resource.h"
#include "BoardSlot.h"

typedef struct Chesspiece
{
	short Row_X;
	short Column_Y;
	HBITMAP Bit_Image;
}PIECE;
// Ŭ������ ���� ������ �����͸� ���ȴ�.

class ChessBoard
{
public:
	ChessBoard();
	~ChessBoard();

public:
	void Init(HINSTANCE& hInst);
	void DrawBoard(HDC& hdc, HDC& memDC);
	void SetPiecePosition(int _row, int _column);

public:
	// Get
	short& GetPiecePos_row() { return m_Piece.Row_X; }
	short& GetPiecePos_column() { return m_Piece.Column_Y; }
	
private:
	HINSTANCE m_hInst;

	BoardSlot slot[8][8];
	PIECE m_Piece;
	HBITMAP boardBit;

};

