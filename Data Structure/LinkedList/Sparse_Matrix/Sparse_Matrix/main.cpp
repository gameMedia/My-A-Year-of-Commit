#include <iostream>
#include <stdlib.h>
using namespace std;

typedef struct { //	하나의 희소행렬의 요소를 저장하는 구조체
	int row;
	int col;
	int value;
}element;

typedef struct NODE { // 희소 행렬의 항을 연결리스트 관리하기 위한 자기참조 구조체
	element data;
	NODE* link;
}node;

typedef struct HEAD { // 희소행렬 관리 구조체
	int m_row, m_col;
	node* link;
}head;

head* init_list();
void insert_node(head** _head, element _Data);
void init_matrix(head* _head, int row, int col);

element getNode(head* mat_a, int row, int col);
element getaddNode(head* mat_a, head* mat_b, int row, int col);
element getsubNode(head* mat_a, head* mat_b, int row, int col);
head* add_matrix(head* mat_a, head* mat_b); // 두 행렬 더하는 함수
head* sub_matrix(head* mat_a, head* mat_b); // 두 행렬의 뺄셈을 수행하는 함수
head* matrix_transpose(head* h); // 전치 행렬을 구하는 함수
void display_matrix(head* h); // 행렬 형태로 출력
void display_list(head* h); // 연결리스트 형식으로 출력

int main()
{
	head* A;
	head* B;
	head* C;
	head* D;
	head* E;
	//head* result;
	int row, col;

	A = init_list();
	B = init_list();



	cin >> row;
	cin >> col;
	init_matrix(A, row, col);
	init_matrix(B, row, col);

	// A
	cout << "행렬 A" << endl;
	display_matrix(A);
	display_list(A);
	// B
	cout << "행렬 B" << endl;
	display_matrix(B);
	display_list(B);

	//C
	cout << "행렬 A + 행렬 B = 행렬 C" << endl;
	C = add_matrix(A, B);
	display_matrix(C);
	display_list(C);

	// D
	cout << "행렬 A - 행렬 B = 행렬 D" << endl;
	D = sub_matrix(A, B);
	display_matrix(D);
	display_list(D);

	// D
	cout << "행렬 A의 전치행렬 = 행렬 E" << endl;
	E = matrix_transpose(A);
	display_matrix(E);
	display_list(E);

}

head* init_list()
{
	head* plist = (HEAD*)malloc(sizeof(HEAD));
	plist->m_row = 0;
	plist->m_col = 0;
	plist->link = NULL;
	return plist;
}

void insert_node(head** _head, element _Data)
{
	node* newNode = (node*)malloc(sizeof(node));
	newNode->data = _Data;
	newNode->link = NULL;

	if ((*_head)->link == NULL) {
		(*_head)->link = newNode;
	}
	else
	{
		node* p = (*_head)->link;
		node* prev = NULL;
		while (p != NULL) {
			prev = p;
			p = p->link;
		}

		prev->link = newNode;
	}
}

void init_matrix(head* _head, int row, int col)
{
	_head->m_row = row;
	_head->m_col = col;
	element temp;
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			temp.row = i;
			temp.col = j;
			cin >> temp.value;
			insert_node(&_head, temp);
		}
	}
}

element getNode(head* mat_a, int row, int col)
{
	node* curA = mat_a->link;
	element TempA;
	while (curA != NULL) {
		if (curA->data.row == row && curA->data.col == col) {
			TempA.col = curA->data.row;
			TempA.row = curA->data.col;
			TempA.value = curA->data.value;
			break;
		}
		curA = curA->link;
	}
	return TempA;
}

element getaddNode(head* mat_a, head* mat_b, int row, int col)
{
	node* curA = mat_a->link;
	node* curB = mat_b->link;
	element TempA;
	element TempB;
	element result;
	while (curA != NULL) {
		if (curA->data.row == row && curA->data.col == col) {
			TempA.row = curA->data.row;
			TempA.col = curA->data.col;
			TempA.value = curA->data.value;
			break;
		}
		curA = curA->link;
	}

	while (curB != NULL) {
		if (curB->data.row == row && curB->data.col == col) {
			TempB.row = curB->data.row;
			TempB.col = curB->data.col;
			TempB.value = curB->data.value;
			break;
		}
		curB = curB->link;
	}

	result.row = TempA.row;
	result.col = TempA.col;
	result.value = TempA.value + TempB.value;

	return result;
}

element getsubNode(head* mat_a, head* mat_b, int row, int col)
{
	node* curA = mat_a->link;
	node* curB = mat_b->link;
	element TempA;
	element TempB;
	element result;
	while (curA != NULL) {
		if (curA->data.row == row && curA->data.col == col) {
			TempA.row = curA->data.row;
			TempA.col = curA->data.col;
			TempA.value = curA->data.value;
			break;
		}
		curA = curA->link;
	}

	while (curB != NULL) {
		if (curB->data.row == row && curB->data.col == col) {
			TempB.row = curB->data.row;
			TempB.col = curB->data.col;
			TempB.value = curB->data.value;
			break;
		}
		curB = curB->link;
	}

	result.row = TempA.row;
	result.col = TempA.col;
	result.value = TempA.value - TempB.value;

	return result;
}

head* add_matrix(head* mat_a, head* mat_b)
{
	head* addMat = init_list();
	addMat->m_col = mat_a->m_col;
	addMat->m_row = mat_a->m_row;
	int row = mat_a->m_row;
	int col = mat_a->m_col;
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			element temp = getaddNode(mat_a, mat_b, i, j);
			insert_node(&addMat, temp);
		}
	}
	return addMat;
}

head* sub_matrix(head* mat_a, head* mat_b)
{
	head* subMat = init_list();
	subMat->m_col = mat_a->m_col;
	subMat->m_row = mat_a->m_row;
	int row = mat_a->m_row;
	int col = mat_a->m_col;
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			element temp = getsubNode(mat_a, mat_b, i, j);
			insert_node(&subMat, temp);
		}
	}
	return subMat;
}

head* matrix_transpose(head* h)
{
	head* transposeMat = init_list();
	transposeMat->m_row = h->m_row;
	transposeMat->m_col = h->m_col;
	int row = h->m_row;
	int col = h->m_col;
	int p = 0;
	p = 0;

	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			element Temp = getNode(h, j, i);
			insert_node(&transposeMat, Temp);
		}
	}

	return transposeMat;
}

void display_matrix(head* h)
{
	cout << "행렬 출력" << endl;
	node* cur = h->link;
	while (cur != NULL) {
		cout << cur->data.value << " ";
		if (cur->data.col == h->m_col - 1) cout << "\n";
		cur = cur->link;
	}
	cout << "\n";
}

void display_list(head* h)
{
	cout << "연결리스트 노드 출력" << endl;
	node* cur = h->link;
	while (cur != NULL) {
		if (cur->data.value)
			cout << "<" << cur->data.row << ", " << cur->data.col << "> = " << cur->data.value << endl;
		cur = cur->link;
	}
	cout << "\n";
}
