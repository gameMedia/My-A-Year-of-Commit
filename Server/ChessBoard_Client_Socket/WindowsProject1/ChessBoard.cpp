#include "ChessBoard.h"

ChessBoard::ChessBoard(HINSTANCE& hInst)
{
	m_Piece.Row_X = 4;
	m_Piece.Column_Y = 4;
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			slot[i][j].SetPosition(i, j);
	m_hInst = hInst;
	boardBit = LoadBitmap(m_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	m_Piece.Bit_Image = LoadBitmap(m_hInst, MAKEINTRESOURCE(IDB_BITMAP2));
}

ChessBoard::~ChessBoard()
{
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
	SelectObject(memDC, m_Piece.Bit_Image);
	BitBlt(hdc,
		slot[m_Piece.Row_X][m_Piece.Column_Y].GetTop(), slot[m_Piece.Row_X][m_Piece.Column_Y].GetLeft(),
		slot[m_Piece.Row_X][m_Piece.Column_Y].GetBottom(), slot[m_Piece.Row_X][m_Piece.Column_Y].GetRight(),
		memDC, 0, 0, SRCCOPY);

}

void ChessBoard::SetPiecePosition(int _row, int _column)
{
	if (abs(m_Piece.Row_X - _row) == 1)
		m_Piece.Row_X = _row;
	else if (abs(m_Piece.Column_Y - _column) == 1)
		m_Piece.Column_Y = _column;
	
}
