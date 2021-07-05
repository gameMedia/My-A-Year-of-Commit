#include <iostream>
#include <algorithm>
#include <time.h>
using namespace std;

struct node { // 이중연결리스트
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


	cout << SIZE << "개의 정수" << endl;
	cout << '\n';
	printNode();
	
	time_t startTime = time(NULL); // 정렬전 시간
	printf("연결리스트 정렬 전 시간 - %f\n", (double)startTime);

	Head = sortNode(Head, tail, SIZE);

	time_t endTime = time(NULL); // 정렬 후 실행 시간
	printf("연결리스트 정렬 후 시간 - %f\n", (double)endTime);
	printf("연결리스트 정렬 수행 시간 - %f\n", (double)endTime - startTime);
	
	printNode();

	cout << "\n";

	cout << "배열 첫번째 원소 - " << myArray[0] << ",\t마지막 원소 - " << myArray[SIZE - 1] << endl;

	startTime = time(NULL); // 정렬전 시간
	printf("배열 정렬 전 시간 - %f\n", (double)startTime);

	sort(myArray, myArray + SIZE);

	endTime = time(NULL); // 정렬 후 실행 시간
	printf("배열 정렬 후 시간 - %f\n", (double)endTime);
	printf("배열 정렬 수행 시간 - %f\n", (double)endTime - startTime);
	
	cout << "배열 첫번째 원소 - " << myArray[0] << ",\t마지막 원소 - " << myArray[SIZE - 1] << endl;


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
	cout << "연결리스트 첫번째 노드 - " << cur->data << ",\t";
	while (cur->right != nullptr) {
		cur = cur->right;
	}
	cout <<"마지막 노드 - "<<cur->data << " ";
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
