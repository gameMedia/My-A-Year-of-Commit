#include <iostream>
using namespace std;

#define SIZE 20

typedef struct PolyNode {
	int coef;	// 계수
	int exp;	// 차수
	struct PolyNode* link;
}node;

void addNode(node* Head, int _coef, int _exp);
void printNode(node* Head);
node* addPoly(node* a, node* b);
node* mulPoly(node* a, node* b);
void freeAllNode(node* Head);

int main()
{
	// a(x) = 3x5 + 4x3 - 2x2 + 1x + 7
	node* Heada = new node;

	Heada->coef = 0;
	Heada->exp = 0;
	Heada->link = nullptr;

	addNode(Heada, 3, 5); // head, coef, exp
	addNode(Heada, 4, 3); // head, coef, exp
	addNode(Heada, -2, 2); // head, coef, exp
	addNode(Heada, 1, 1); // head, coef, exp
	addNode(Heada, 7, 0); // head, coef, exp

	// b(x) = 4x3 + 2x2 - 6x – 3
	node* Headb = new node;

	Headb->coef = 0;
	Headb->exp = 0;
	Headb->link = nullptr;

	addNode(Headb, 4, 3); // head, coef, exp
	addNode(Headb, 2, 2); // head, coef, exp
	addNode(Headb, -6, 1); // head, coef, exp
	addNode(Headb, -3, 0); // head, coef, exp

	cout << "a(x) = ";
	printNode(Heada);
	cout << "b(x) = ";
	printNode(Headb);

	node* Headc = addPoly(Heada, Headb);
	cout << "c(x) = ";
	printNode(Headc);

	node* Headd = mulPoly(Heada, Headb);
	cout << "d(x) = ";
	printNode(Headd);


	freeAllNode(Heada);
	freeAllNode(Headb);
	freeAllNode(Headc);
	//	freeAllNode(Headd);

}


void addNode(node* Head,
	int _coef, int _exp)
{
	node* newNode = new node;
	newNode->coef = _coef;
	newNode->exp = _exp;
	newNode->link = nullptr;

	if (Head->link == nullptr) {
		Head->link = newNode;
	}
	else
	{
		node* p = Head->link;
		node* prev = nullptr;
		while (p != nullptr) {
			prev = p;
			p = p->link;
		}
		prev->link = newNode;
	}
}

void printNode(node* Head)
{

	node* cur = Head->link;
	while (cur != NULL) {

		cout << cur->coef << "x^" << cur->exp << " ";
		cur = cur->link;
	}
	cout << "\n";
}

node* addPoly(node* a, node* b)
{
	node* newHead = new node;
	newHead->coef = 0;
	newHead->exp = 0;
	newHead->link = nullptr;

	int sum;

	node* curA = a->link;
	node* curB = b->link;
	while (curA != nullptr && curB != nullptr) {
		if (curA->exp == curB->exp) { // 차수가 같다
			sum = curA->coef + curB->coef;
			if (sum)
				addNode(newHead, sum, curA->exp);
			curA = curA->link;
			curB = curB->link;
		}
		else if (curA->exp > curB->exp) { // a의 현재 차수가 b의 현재 차수보다 높다
			sum = curA->coef;
			addNode(newHead, sum, curA->exp);
			curA = curA->link;
		}
		else { // a의 현재 차수가 b의 현재 차수보다 작다
			sum = curB->coef;
			addNode(newHead, sum, curB->exp);
			curB = curB->link;
		}
	}

	while (curB != nullptr) {
		addNode(newHead, curB->coef, curB->exp);
		curB = curB->link;
	}
	while (curA != nullptr) {
		addNode(newHead, curA->coef, curA->exp);
		curA = curA->link;
	}

	return newHead;
}

node* mulPoly(node* a, node* b)
{
	node* newHead = new node;
	newHead->coef = 0;
	newHead->exp = 0;
	newHead->link = nullptr;



	node* termB = new node;
	termB->coef = 0;
	termB->exp = 0;
	termB->link = nullptr;

	int exp[SIZE] = {};
	int total_Coef;
	int total_exp;

	node* curA = a->link;
	node* curB = b->link;


	while (curA != nullptr) {
		curB = b->link;
		node* termHead = new node;
		termHead->coef = 0;
		termHead->exp = 0;
		termHead->link = nullptr;
		while (curB != nullptr) {
			total_Coef = curA->coef * curB->coef; // 계수는 곱하고
			total_exp = curA->exp + curB->exp; // 차수는 더하고
			addNode(termHead, total_Coef, total_exp);
			curB = curB->link;
		}
		termB = addPoly(termB, termHead);
		curA = curA->link;



	}


	return termB;
}

void freeAllNode(node* Head)
{
	node* Del = Head->link;
	while (Head->link != NULL) {
		node* next = Head->link->link;
		free(Head->link);
		Head->link = next;
	}
}
