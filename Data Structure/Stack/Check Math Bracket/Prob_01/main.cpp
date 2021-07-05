#include <iostream>
using namespace std;

#define STACK_SIZE 10
#define EXPR_SIZE 200
typedef struct element
{
	int index;
	char ch;
};
typedef struct StackType
{
	element* data;
	int capacity;
	int top;
}STACK;

void init_stack(STACK* s);
int is_full(STACK* s);
bool myis_empty(STACK* s);
void push(STACK* s, element _data);
element pop(STACK* s);
int check_matching(STACK* s, char* expr, int& _s, int& _e);
int main()
{
	STACK* stack = new STACK;
	init_stack(stack);


	char expr1[EXPR_SIZE] = "24.5 * ( x + func(x, y)) * ( r * r * 3.14) / [ 7%10* sqrt(25)];";
	char expr2[EXPR_SIZE] = "24.5 * ( x + func(x, y)) * ( r * r * 3.14 / [ 7%10* sqrt(25)];";
	char expr3[EXPR_SIZE] = "24.5 * ( x + func(x, y] * ( r * r * 3.14) / [ 7%10* sqrt(25)];";
	char expr4[EXPR_SIZE] = "24.5 * ( x + func(x, y))) * ( r * r * 3.14) / [ 7%10* sqrt(25)];";
	//cout << "수식 A(x)의 입력\n";
	cout << "A(x) = " << expr1 << endl;
	int s = 0, e = 0;
	int check = check_matching(stack, expr1, s, e);
	if (check == 1)
	{
		cout << "괄호 검사 성공\n";
	}
	else if (check == 2)
	{
		cout << "괄호 검사 실패 " << e << "위치\n";
	}
	else {
		cout << "괄호 검사 실패 " << s << ' ' << e << "위치\n";
	}

	// 2번
	cout << "\n";
	cout << "A(x) = " << expr2 << endl;
	s = 0, e = 0;
	check = check_matching(stack, expr2, s, e);
	if (check == 1)
	{
		cout << "괄호 검사 성공\n";
	}
	else if (check == 2)
	{
		cout << "괄호 검사 실패 " << e << "위치\n";
	}
	else {
		cout << "괄호 검사 실패 " << s << ' ' << e << "위치\n";
	}

	// 3번
	cout << "\n";
	cout << "A(x) = " << expr3 << endl;
	s = 0, e = 0;
	check = check_matching(stack, expr3, s, e);
	if (check == 1)
	{
		cout << "괄호 검사 성공\n";
	}
	else if (check == 2)
	{
		cout << "괄호 검사 실패 " << e << "위치\n";
	}
	else {
		cout << "괄호 검사 실패 " << s << ' ' << e << "위치\n";
	}

	// 4번
	cout << "\n";
	cout << "A(x) = " << expr4 << endl;
	//cin >> expr;
	s = 0, e = 0;
	check = check_matching(stack, expr4, s, e);
	if (check == 1)
	{
		cout << "괄호 검사 성공\n";
	}
	else if (check == 2)
	{
		cout << "괄호 검사 실패 " << e << "위치\n";
	}
	else {
		cout << "괄호 검사 실패 " << s << ' ' << e << "위치\n";
	}

	delete stack;
}

void init_stack(STACK* s)
{
	s->top = -1;
	s->capacity = STACK_SIZE;
	s->data = (element*)malloc(sizeof(element) * s->capacity);
}

int is_full(STACK* s)
{
	return (s->top == s->capacity - 1);
}

bool myis_empty(STACK* s)
{
	return (s->top == -1);
}

void push(STACK* s, element _data)
{
	
	if (is_full(s)) {
		s->capacity *= 2;
		s->data = (element*)realloc(s->data, s->capacity * sizeof(element));
	}
	s->data[++(s->top)].ch = _data.ch;
	s->data[(s->top)].index = _data.index;
}

element pop(STACK* s)
{
	if (myis_empty(s)) {
		throw out_of_range("스택이 비어있다.\n");
	}
	return s->data[(s->top)--];
}

int check_matching(STACK* s, char* expr, int& _s, int& _e)
{

	element ch, open_ch;
	int n = strlen(expr);
	int e = 0;
	for (int i = 0; i < n; ++i) {
		ch.ch = expr[i];
		ch.index = i;
		switch (ch.ch) {
		case '(': case'[': case'{':
			push(s, ch);
			break;
		case ')': case']': case '}':
			if (myis_empty(s))
			{
				_e = e; 
				return 2;
			}
			else {
				open_ch = pop(s);
				if ((open_ch.ch == '(' && ch.ch != ')') ||
					(open_ch.ch == '[' && ch.ch != ']') ||
					(open_ch.ch == '{' && ch.ch != '}')) {
					_s = open_ch.index;
					_e = ch.index;
					return 3;
				}
				break;
			}
		}
		_e = i;
	}
	if (!myis_empty(s)) {
		_e = open_ch.index;
		return 2;
	}
	return 1;
}
