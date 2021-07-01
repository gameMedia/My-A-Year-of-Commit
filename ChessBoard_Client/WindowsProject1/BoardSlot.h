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
	int GetTop() { return top; }
	int GetBottom() { return bottom; }
	int GetLeft() { return left; }
	int GetRight() { return right; }
private:
	int top;
	int left;
	int bottom;
	int right;
};

