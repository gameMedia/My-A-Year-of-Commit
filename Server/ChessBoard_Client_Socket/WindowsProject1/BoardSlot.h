#pragma once
class BoardSlot
{
public:
	BoardSlot();
	~BoardSlot();

public:
	// Set
	void SetPosition(int row, int column);

	// Get
	const int& GetTop_x() { return top_x; }
	const int& GetTop_y() { return top_y; }

private:
	int top_x;
	int top_y;
};

