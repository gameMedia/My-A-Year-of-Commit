#include <iostream>
#include <string>
#include <math.h>
using namespace std;

#define EXPR_SIZE 200

typedef struct element
{
	int num; // 피연산자는 여기 

};



typedef struct StackType
{
	char* data;
	int capacity;
	int top;
}STACK;

typedef struct StackType2
{
	int data[30];
	int index;
	int top;
}STACK2;

void infix_to_postfix(char exp[]);
int prec(char op);
char peek(STACK* s);
void init_stack(STACK* s);
char pop(STACK* s);
void push(STACK* s, char _data);
bool myis_empty(STACK* s);
int is_full(STACK* s);
void eval(string str);

void init_stack(STACK2* s);
int pop(STACK2* s);
void push(STACK2* s, int _data);
int is_full(STACK2* s);
bool myis_empty(STACK2* s);
int main()
{

	char c1[EXPR_SIZE] = "10 + 20 * (20 + 10) / 100 +5 - 3";
	char c2[EXPR_SIZE] = "100 + 11 20 * (20 + 10) / 100 + 5 - 3";

	cout << "중위표기 수식 : " << c1 << endl;
	infix_to_postfix(c1);
	cout << "중위표기 수식 : " << c2 << endl;
	infix_to_postfix(c2);
	return 0;
}


void infix_to_postfix(char exp[])
{
	char ch, top_op;
	char number = ' ';
	int len = strlen(exp);
	STACK s;
	STACK posfix;
	string num = "";
	init_stack(&s);

	for (int i = 0; i < len; ++i) {
		ch = exp[i];
		if (ch >= '0' && ch <= '9') {
			num += ch;

		}
		else {
			switch (ch) {
			case '(':
				push(&s, ch);

				break;
			case')':
				while (true) {
					top_op = pop(&s);
					if (top_op == '(')
						break;

					num += top_op;


				}
				break;
			case'+':
			case'-':
			case'*':
			case'/':
				while (!myis_empty(&s) && (prec(ch) <= prec(peek(&s)))) {
					top_op = pop(&s);
					num += top_op;


				}
				push(&s, ch);


			}
		}
		if (number != ' ') {
			if (ch == ' ') {
				num += ' ';

			}
		}
		number = ch;
	}
	while (!myis_empty(&s)) {
		top_op = pop(&s);
		num += top_op;

	}

	cout << "후위표기 수식 : " << num << endl;

	eval(num);


}



void init_stack(STACK* s)
{
	s->top = -1;
	s->capacity = 10;
	s->data = (char*)malloc(sizeof(char) * s->capacity);

}


bool myis_empty(STACK* s)
{
	return (s->top == -1);
}

int prec(char op)
{ // 연산자의 우선 순위를 반환한다.
	switch (op) {
	case'(':case')': return 0;
	case'+':case'-': return 1;
	case'*':case'/': return 2;
	}
	return -1;
}

char peek(STACK* s)
{
	if (myis_empty(s)) {
		cout << "스택이 비어있다.\n";
		exit(1);
	}
	return s->data[s->top];
}

char pop(STACK* s)
{
	if (myis_empty(s)) {
		cout << "스택이 비어있다.\n";
		exit(1);
	}
	else
	{
		char k = s->data[(s->top)];
		s->top -= 1;
		return k;
	}
}

void push(STACK* s, char _data)
{
	if (is_full(s)) {
		s->capacity *= 2;
		s->data = (char*)realloc(s->data, s->capacity * sizeof(char));
	}
	s->data[++(s->top)] = _data;
}

int is_full(STACK* s)
{
	return (s->top == s->capacity - 1);
}

void eval(string str)
{
	int op1, op2;
	int val = 0;
	int len = str.length();
	char ch;
	char number = ' ';
	string check = "";
	STACK2 s;
	int Numcount = 0;
	int Calccount = 0;
	int k = 0;
	init_stack(&s);
	for (int i = 0; i < len; ++i) {
		ch = str[i];
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
			if (ch >= '0' && ch <= '9') {
				check += ch;
			}
			if ((ch == 32 || str[i + 1] == '+' || str[i + 1] == '*' || str[i + 1] == '-' || str[i + 1] == '/') && check != "") { // 공백
				val = stoi(check);
				push(&s, val);
				check = "";
				++Numcount;
			}

		}
		else {
			op2 = pop(&s);
			op1 = pop(&s);
			switch (ch)
			{
			case '+':
				push(&s, op1 + op2);
				++Calccount;
				break;
			case '-':
				push(&s, op1 - op2);
				++Calccount;
				break;
			case '*':
				push(&s, op1 * op2);
				++Calccount;
				break;
			case '/':
				push(&s, op1 / op2);
				++Calccount;
				break;
			}
		}
		number = ch;
	}
	if (Numcount - Calccount == 1) // 피연산자 개수 - 연산자 개수 ==1
		cout << "연산 결과 : " << pop(&s) << endl;
	else
	{
		cout << "수식오류\n";
	}
}

void init_stack(STACK2* s)
{
	s->top = -1;

}

int pop(STACK2* s)
{
	if (myis_empty(s)) {
		cout << "스택이 비어있다.\n";
		exit(1);
	}
	else
	{
		int k = s->data[(s->top)];
		s->top -= 1;
		return k;
	}
}

void push(STACK2* s, int _data)
{

	s->data[++(s->top)] = _data;
}

int is_full(STACK2* s)
{
	return (s->top == 100);
}

bool myis_empty(STACK2* s)
{
	return (s->top == -1);
}
