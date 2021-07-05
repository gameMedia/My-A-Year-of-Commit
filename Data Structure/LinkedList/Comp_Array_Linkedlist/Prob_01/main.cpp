#include <iostream>
#include <algorithm>
#include <time.h>
using namespace std;

struct node { // ���߿��Ḯ��Ʈ
	int data;
	struct node* left;
	struct node* right;
};

node* Head = nullptr;
node* tail = nullptr;

void addNode(int data);
void printNode();
node* sortNode(node* head, node* tail, int size);
void MyQuickSort(node* head, node* tail, int left, int right);
void Swap(int* a, int* b);
#define SIZE 200'000

int myArray[SIZE] = {};

int main()
{
	srand(unsigned(time(NULL)));


	for (int i = 0; i < SIZE; ++i) {
		int data = rand();
		addNode(data);
		myArray[i] = data;
	}


	cout << SIZE << "���� ����" << endl;
	cout << '\n';
	printNode();
	
	time_t startTime = time(NULL); // ������ �ð�
	printf("���Ḯ��Ʈ ���� �� �ð� - %f\n", (double)startTime);

	Head = sortNode(Head, tail, SIZE);

	time_t endTime = time(NULL); // ���� �� ���� �ð�
	printf("���Ḯ��Ʈ ���� �� �ð� - %f\n", (double)endTime);
	printf("���Ḯ��Ʈ ���� ���� �ð� - %f\n", (double)endTime - startTime);
	
	printNode();

	cout << "\n";

	cout << "�迭 ù��° ���� - " << myArray[0] << ",\t������ ���� - " << myArray[SIZE - 1] << endl;

	startTime = time(NULL); // ������ �ð�
	printf("�迭 ���� �� �ð� - %f\n", (double)startTime);

	sort(myArray, myArray + SIZE);

	endTime = time(NULL); // ���� �� ���� �ð�
	printf("�迭 ���� �� �ð� - %f\n", (double)endTime);
	printf("�迭 ���� ���� �ð� - %f\n", (double)endTime - startTime);
	
	cout << "�迭 ù��° ���� - " << myArray[0] << ",\t������ ���� - " << myArray[SIZE - 1] << endl;


	while (Head != NULL) {
		node* next = Head->right;
		delete Head;
		Head = next;
	}
}



void addNode(int data)
{
	node* newNode = new node;
	newNode->data = data;
	newNode->left = nullptr;
	newNode->right = nullptr;

	if (Head == nullptr) {
		newNode->left = nullptr;
		Head = tail = newNode;
	}
	else
	{
		tail->right = newNode;
		newNode->left = tail;
		tail = newNode;

	}



}

void printNode()
{


	
	node* cur = Head;
	cout << "���Ḯ��Ʈ ù��° ��� - " << cur->data << ",\t";
	while (cur->right != nullptr) {
		cur = cur->right;
	}
	cout <<"������ ��� - "<<cur->data << " ";
	cout << "\n";
}

node* sortNode(node* head, node* tail, int size)
{
	MyQuickSort(head, tail, 0, size - 1);
	return head;
}

void MyQuickSort(node* head, node* tail, int left, int right)
{
	if (left >= right) return;
	int L = left;
	int R = right + 1;
	node* Lnode = head;
	node* Lprev = head->left;
	node* Rnode = tail;
	
	node* Rnext = tail->right;
	node* dump = new node;
	Rnode->right = dump;
	dump->left = Rnode;
	Rnode = Rnode->right;
	while (L < R) {
		do {
			L++;
			Lnode = Lnode->right;
		} while (L <= right && Lnode->data < head->data);
		do {
			R--;
			Rnode = Rnode->left;
		} while (R > left && Rnode->data > head->data);
		if (L < R) Swap(&Lnode->data, &Rnode->data);
	}
	Swap(&head->data, &Rnode->data);
	free(dump);
	tail->right = Rnext;

	MyQuickSort(head, Rnode->left, left, R - 1);
	MyQuickSort(Rnode->right, tail, R + 1, right);
}

void Swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

node* sortNode()
{
	return nullptr;
}
