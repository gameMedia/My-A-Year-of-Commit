#include "BoardSlot.h"

BoardSlot::BoardSlot()
	:top{ 0 }, bottom{ 0 }, left{ 0 }, right{ 0 }
{
}

BoardSlot::~BoardSlot()
{
}

void BoardSlot::SetPosition(int row, int column)
{
	top = 64 * row;
	bottom = 64 * (row + 1);
	left = 64 * column;
	right = 64 * (column + 1);
}
