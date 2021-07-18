#include "BoardSlot.h"

BoardSlot::BoardSlot()
	:top_x{ 0 }, top_y{ 0 }
{
}

BoardSlot::~BoardSlot()
{
}

void BoardSlot::SetPosition(int row, int column)
{
	top_x = 64 * column;
	top_y = 64 * row;
}
