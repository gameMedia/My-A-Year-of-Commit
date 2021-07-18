#include "ChessBoard.h"
#include <iostream>
using namespace std;
#pragma comment(lib, "msimg32.lib")
ChessBoard::ChessBoard()
{
	m_Piece.Row_X = 4;
	m_Piece.Column_Y = 3;
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			slot[i][j].SetPosition(i, j);

}

ChessBoard::~ChessBoard()
{
}

void ChessBoard::Init(HINSTANCE& hInst)
{
	m_hInst = hInst;
	boardBit = LoadBitmap(m_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	m_Piece.Bit_Image = LoadBitmap(m_hInst, MAKEINTRESOURCE(IDB_BITMAP2));
}

void ChessBoard::DrawBoard(HDC& hdc, HDC& memDC)
{
	// Draw ChessBoard
	SelectObject(memDC, boardBit);
	BitBlt(hdc,
		0, 0,
		512, 512,
		memDC, 0, 0, SRCCOPY);

	// Draw ChessPiece
	//cout << "그림그려.." << endl;
	SelectObject(memDC, m_Piece.Bit_Image);
	TransparentBlt(hdc,
		slot[m_Piece.Row_X][m_Piece.Column_Y].GetTop_x(), slot[m_Piece.Row_X][m_Piece.Column_Y].GetTop_y(),
		64, 64,
		memDC, 0, 0, 64, 64, RGB(255, 255, 255));

}

void ChessBoard::SetPiecePosition(int _row, int _column)
{
	m_Piece.Row_X = _row;
	m_Piece.Column_Y = _column;
}
