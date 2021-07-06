#include <iostream>
using namespace std;

#define MAZE_SIZE 6

typedef struct element
{
	int row;
	int col;
}Element;

typedef struct StackType
{
	element* data;
	int capacity;
	int top;

}STACK;

char maze[MAZE_SIZE][MAZE_SIZE] = {
	{'1','1','1','1','1','1'},
	{'e','0','1','0','0','1'},
	{'1','0','0','0','1','1'},
	{'1','0','1','0','1','1'},
	{'1','0','1','0','0','x'},
	{'1','1','1','1','1','1'}
};

void initStack(STACK* s);
int is_emptycheck(STACK* s);
int is_fullcheck(STACK* s);
void push_loc(STACK* s, int r, int c);
void maze_print(char maze[MAZE_SIZE][MAZE_SIZE]);



void push(STACK* s, element item)
{
	if (is_fullcheck(s)) {
		s->capacity *= 2;
		s->data = (element*)realloc(s->data, s->capacity * sizeof(element));
	}
	s->data[++(s->top)] = item;
}
element pop(STACK* s)
{
	if (is_emptycheck(s)) {
		cout << "스택이 비어있다.\n";
	}
	return s->data[(s->top)--];
}


int main()
{
	element here = { 1,0 };
	element entry = { 1,0 };



	int r, c;
	StackType s;
	StackType rc;
	initStack(&s);
	initStack(&rc);
	here = entry;
	push(&rc, here);
	cout << "---------- 주어진 미로 ------------" << endl;
	maze_print(maze);

	while (maze[here.row][here.col] != 'x') {
		r = here.row;
		c = here.col;
		maze[r][c] = '.';
		push_loc(&s, r - 1, c);
		push_loc(&s, r + 1, c);
		push_loc(&s, r, c - 1);
		push_loc(&s, r, c + 1);

		if (is_emptycheck(&s)) {
			cout << "실패\n";
			cout << "---------- 미로 ------------" << endl;
			maze_print(maze);
			return 0;
		}
		else {
			here = pop(&s);
			push(&rc, here);
		}
	}
	cout << "\n";
	cout << "---------- 미로 ------------" << endl;
	cout << "성공\n";
	maze_print(maze);

	cout << "---------- 미로 ------------" << endl;
	cout << "경로 : \n";
	cout << "(row col)\n";

	for (int i = 0; i <= rc.top; ++i)
	{
		cout << "(" << rc.data[i].row << " " << rc.data[i].col << ")" << endl;
	}




	return 0;
}

void initStack(STACK* s)
{
	s->top = -1;
	s->capacity = 10;
	s->data = (element*)malloc(sizeof(element) * s->capacity);
}

int is_emptycheck(STACK* s)
{
	return (s->top == -1);
}

int is_fullcheck(STACK* s)
{
	return (s->top == (s->capacity - 1));
}

void push_loc(STACK* s, int r, int c)
{
	if (r < 0 || c < 0) return;
	if (maze[r][c] != '1' && maze[r][c] != '.') {
		element tmp;
		tmp.row = r;
		tmp.col = c;
		push(s, tmp);
	}
}

void maze_print(char maze[MAZE_SIZE][MAZE_SIZE])
{
	cout << "\n";
	for (int r = 0; r < MAZE_SIZE; ++r) {
		for (int c = 0; c < MAZE_SIZE; ++c) {
			cout << maze[r][c];
		}
		cout << '\n';
	}
}
