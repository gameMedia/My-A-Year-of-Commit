#include <iostream>
#include <time.h>
#include <chrono>
using namespace std;


#define MAX_LIST_SIZE 10000

struct listnode {
	int data;
	struct listnode* link;
};

void addLinkedlist(listnode** head, int _data);
int deleteLinkedlist(listnode* p, int _data);
void clearLinkedlist(listnode* p);
int searchLinkedlist(listnode* p, int _data);
void displayLinkedlist(listnode* p);
int get_length(listnode* p);

listnode* head = NULL;

int main()
{
	srand(unsigned(time(NULL)));

	head = (listnode*)malloc(sizeof(listnode));
	head->link = NULL;

	int iSelect = 0;

	cout << "연결리스트을 이용하여 정렬리스트 만들기" << endl;

	chrono::system_clock::time_point startTime = chrono::system_clock::now();

	for (int i = 0; i < MAX_LIST_SIZE; ++i) {
		int item = rand();
		addLinkedlist(&head, item);
	}
	//displayLinkedlist(head);

	chrono::system_clock::time_point endTime = chrono::system_clock::now();
	chrono::milliseconds  miliSec = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
	cout << MAX_LIST_SIZE << "개, 총 소요시간 " << miliSec.count() << " ms" << endl;
}

void addLinkedlist(listnode** head, int _data)
{
	listnode* newNode = (listnode*)malloc(sizeof(listnode));
	newNode->data = _data;
	newNode->link = NULL;

	if ((*head)->link == NULL) {
		(*head)->link = newNode;
	}
	else
	{
		listnode* p = (*head)->link;
		listnode* prev = NULL;
		if (p->data > newNode->data) {
			newNode->link = (*head)->link;
			(*head)->link = newNode;
		}
		else {
			while (p != NULL && p->data < newNode->data) {
				prev = p;
				p = p->link;
			}

			if (p != NULL) {
				newNode->link = p;
				prev->link = newNode;
			}
			else {
				prev->link = newNode;
			}
		}

	}

}

int deleteLinkedlist(listnode* p, int _data)
{
	listnode* cur = p->link;
	int index = 0;
	if (cur == NULL) return 0;
	if (cur->data == _data) {
		p->link = p->link->link;
		++index;
		return index;
	}
	else {
		listnode* Del = cur->link;
		listnode* prevDel = cur;
		while (Del != NULL && Del->data != _data) {
			prevDel = Del;
			Del = Del->link;
			++index;
		}

		if (Del == NULL) return 0;

		prevDel->link = Del->link;

		free(Del);
		return index;
	}
}

void clearLinkedlist(listnode* p)
{
	listnode* Del = p->link;
	while (p->link != NULL) {
		listnode* next = p->link->link;
		free(p->link);
		p->link = next;
	}
}

int searchLinkedlist(listnode* p, int _data)
{
	listnode* cur = p->link;
	int index = 0;
	while (cur != NULL) {
		if (_data == cur->data) {
			return index;
		}
		else cur = cur->link;

		++index;
	}
	return 0;
}

void displayLinkedlist(listnode* p)
{
	cout << "전체 연결리스트 출력" << endl;
	listnode* cur = p->link;
	while (cur != NULL) {
		cout << " data : " << cur->data << endl;
		cur = cur->link;
	}
}

int get_length(listnode* p)
{
	listnode* cur = p->link;
	int index = 0;
	while (cur != NULL) {
		cur = cur->link;
		++index;

	}
	return index;
}
