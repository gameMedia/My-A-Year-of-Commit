#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
using namespace std;

#define WORK_TIME 1000
#define MAX_QUEUE_SIZE10 10
#define MAX_QUEUE_SIZE20 20
#define MAX_QUEUE_SIZE30 30
#define MAX_QUEUE_SIZE40 40

// Menu 0	 5��
// Menu 1	10��
// Menu 2	15��
// Menu 3	20��
// Menu 4	25��

typedef struct element {
	int menu;
	int startTime;
};

typedef struct QueueType {
	int front;
	int rear;
	int size;
	element* menu;
};
typedef struct server {
	bool busy;
	int process_time;
};

typedef struct Burger {
	int takeOut_count;// �ȸ� ����
	int waitingTime; // ���� ��� �ð�
	double averageService_Time; // ��� ���� �ð�
};

typedef struct Checklist {
	Burger take0;
	Burger take1;
	Burger take2;
	Burger take3;
	Burger take4;
	int failOrder; // ���� �ֹ�
};

void init_queue(QueueType* q, int _size);
int is_full(QueueType* q);
int myis_empty(QueueType* q);
void Queue_push_back(QueueType* q, element item);
element Queue_pop_front(QueueType* q);


int main()
{
	QueueType burgerQueue1;
	QueueType burgerQueue2;
	QueueType burgerQueue3;
	QueueType burgerQueue4;
	server busyServer1;	// ������ 1
	server busyServer2;	// ������ 2
	element myJob1, myJob2;
	srand(unsigned(time(NULL)));
	int time;
	int menuSelect;
	Checklist check;
	ZeroMemory(&burgerQueue1, sizeof(QueueType));
	ZeroMemory(&burgerQueue2, sizeof(QueueType));
	ZeroMemory(&burgerQueue3, sizeof(QueueType));
	ZeroMemory(&burgerQueue4, sizeof(QueueType));

	init_queue(&burgerQueue1, MAX_QUEUE_SIZE10);
	init_queue(&burgerQueue2, MAX_QUEUE_SIZE20);
	init_queue(&burgerQueue3, MAX_QUEUE_SIZE30);
	init_queue(&burgerQueue4, MAX_QUEUE_SIZE40);

	busyServer1.busy = false;
	busyServer1.process_time = 0;
	busyServer2.busy = false;
	busyServer2.process_time = 0;
	time = 0;
	menuSelect = 0;
	ZeroMemory(&check, sizeof(Checklist));



	while (time < WORK_TIME) {
		if (time % 5 == 0) { // �� �մ� �ֹ�
			if (is_full(&burgerQueue1)) { // �� �ֹ��� �� �ֳ�?
				++check.failOrder;
			}
			else
			{ // q�� �������� �ʾ����� �ֹ�����
				menuSelect = rand() % 5; // �޴� ��
				element Menu;
				Menu.startTime = time;
				Menu.menu = menuSelect;
				Queue_push_back(&burgerQueue1, Menu); // q�� ���Ÿ� ����ְ�
				switch (menuSelect)
				{
				case 0:
					++check.take0.takeOut_count;
					break;
				case 1:
					++check.take1.takeOut_count;
					break;
				case 2:
					++check.take2.takeOut_count;
					break;
				case 3:
					++check.take3.takeOut_count;
					break;
				case 4:
					++check.take4.takeOut_count;
					break;
				default:
					break;
				}
			}
		}

		if (!busyServer1.busy) { // �ȹٻڸ� ���� 
			myJob1 = Queue_pop_front(&burgerQueue1);
			switch (myJob1.menu)
			{
			case 0:
				busyServer1.process_time = 5;
				busyServer1.busy = true;
				break;
			case 1:
				busyServer1.process_time = 10;
				busyServer1.busy = true;
				break;
			case 2:
				busyServer1.process_time = 15;
				busyServer1.busy = true;
				break;
			case 3:
				busyServer1.process_time = 20;
				busyServer1.busy = true;
				break;
			case 4:
				busyServer1.process_time = 25;
				busyServer1.busy = true;
				break;
			default:
				break;
			}

			//continue;
		}
		else if (busyServer1.busy && busyServer1.process_time == 0) {
			// �ٻ� ���� ���µ� ���� ������ �ȹٻ۰���
			busyServer1.busy = false;
			switch (myJob1.menu)
			{
			case 0:
				check.take0.waitingTime += time - myJob1.startTime;
				break;
			case 1:
				check.take1.waitingTime += time - myJob1.startTime;
				break;
			case 2:
				check.take2.waitingTime += time - myJob1.startTime;
				break;
			case 3:
				check.take3.waitingTime += time - myJob1.startTime;
				break;
			case 4:
				check.take4.waitingTime += time - myJob1.startTime;
				break;
			}
		}

		if (!busyServer2.busy) { // �ȹٻڸ� ���� 
			myJob2 = Queue_pop_front(&burgerQueue1);
			switch (myJob2.menu)
			{
			case 0:
				busyServer2.process_time = 5;
				busyServer2.busy = true;
				break;
			case 1:
				busyServer2.process_time = 10;
				busyServer2.busy = true;
				break;
			case 2:
				busyServer2.process_time = 15;
				busyServer2.busy = true;
				break;
			case 3:
				busyServer2.process_time = 20;
				busyServer2.busy = true;
				break;
			case 4:
				busyServer2.process_time = 25;
				busyServer2.busy = true;
				break;
			default:
				break;
			}

			//continue;
		}
		else if (busyServer2.busy && busyServer2.process_time == 0) {
			// �ٻ� ���� ���µ� ���� ������ �ȹٻ۰���
			busyServer2.busy = false;
			switch (myJob2.menu)
			{
			case 0:
				check.take0.waitingTime += time - myJob2.startTime;
				break;
			case 1:
				check.take1.waitingTime += time - myJob2.startTime;
				break;
			case 2:
				check.take2.waitingTime += time - myJob2.startTime;
				break;
			case 3:
				check.take3.waitingTime += time - myJob2.startTime;
				break;
			case 4:
				check.take4.waitingTime += time - myJob2.startTime;
				break;
			}
		}

		++time;
		// server1�� �ð� 1 ����
		if (busyServer1.process_time > 0)
			--busyServer1.process_time;
		// server2�� �ð� 2 ����
		if (busyServer2.process_time > 0)
			--busyServer2.process_time;
	}
	if (check.take0.takeOut_count != 0)
		check.take0.averageService_Time = (double)(check.take0.waitingTime / check.take0.takeOut_count);
	if (check.take1.takeOut_count != 0)
		check.take1.averageService_Time = (double)(check.take1.waitingTime / check.take1.takeOut_count);
	if (check.take2.takeOut_count != 0)
		check.take2.averageService_Time = (double)(check.take2.waitingTime / check.take2.takeOut_count);
	if (check.take3.takeOut_count != 0)
		check.take3.averageService_Time = (double)(check.take3.waitingTime / check.take3.takeOut_count);
	if (check.take4.takeOut_count != 0)
		check.take4.averageService_Time = (double)(check.take4.waitingTime / check.take4.takeOut_count);

	cout << "ť�� ũ�Ⱑ " << MAX_QUEUE_SIZE10 << endl;
	cout << "========== Results ==========" << endl;
	cout << "MENU-0 " << check.take0.takeOut_count << "�� ����, �������ð� " << check.take0.waitingTime << ", ��ռ��񽺽ð� " << check.take0.averageService_Time << endl;
	cout << "MENU-1 " << check.take1.takeOut_count << "�� ����, �������ð� " << check.take1.waitingTime << ", ��ռ��񽺽ð� " << check.take1.averageService_Time << endl;
	cout << "MENU-2 " << check.take2.takeOut_count << "�� ����, �������ð� " << check.take2.waitingTime << ", ��ռ��񽺽ð� " << check.take2.averageService_Time << endl;
	cout << "MENU-3 " << check.take3.takeOut_count << "�� ����, �������ð� " << check.take3.waitingTime << ", ��ռ��񽺽ð� " << check.take3.averageService_Time << endl;
	cout << "MENU-4 " << check.take4.takeOut_count << "�� ����, �������ð� " << check.take4.waitingTime << ", ��ռ��񽺽ð� " << check.take4.averageService_Time << endl;
	cout << "��ҵ� �ֹ� " << check.failOrder << " ��" << endl;
	cout << "=============================" << endl;

	busyServer1.busy = false;
	busyServer1.process_time = 0;
	busyServer2.busy = false;
	busyServer2.process_time = 0;
	time = 0;
	menuSelect = 0;
	ZeroMemory(&check, sizeof(Checklist));



	while (time < WORK_TIME) {
		if (time % 5 == 0) { // �� �մ� �ֹ�
			if (is_full(&burgerQueue2)) { // �� �ֹ��� �� �ֳ�?
				++check.failOrder;
			}
			else
			{ // q�� �������� �ʾ����� �ֹ�����
				menuSelect = rand() % 5; // �޴� ��
				element Menu;
				Menu.startTime = time;
				Menu.menu = menuSelect;
				Queue_push_back(&burgerQueue2, Menu); // q�� ���Ÿ� ����ְ�
				switch (menuSelect)
				{
				case 0:
					++check.take0.takeOut_count;
					break;
				case 1:
					++check.take1.takeOut_count;
					break;
				case 2:
					++check.take2.takeOut_count;
					break;
				case 3:
					++check.take3.takeOut_count;
					break;
				case 4:
					++check.take4.takeOut_count;
					break;
				default:
					break;
				}
			}
		}

		if (!busyServer1.busy) { // �ȹٻڸ� ���� 
			myJob1 = Queue_pop_front(&burgerQueue2);
			switch (myJob1.menu)
			{
			case 0:
				busyServer1.process_time = 5;
				busyServer1.busy = true;
				break;
			case 1:
				busyServer1.process_time = 10;
				busyServer1.busy = true;
				break;
			case 2:
				busyServer1.process_time = 15;
				busyServer1.busy = true;
				break;
			case 3:
				busyServer1.process_time = 20;
				busyServer1.busy = true;
				break;
			case 4:
				busyServer1.process_time = 25;
				busyServer1.busy = true;
				break;
			default:
				break;
			}

			//continue;
		}
		else if (busyServer1.busy && busyServer1.process_time == 0) {
			// �ٻ� ���� ���µ� ���� ������ �ȹٻ۰���
			busyServer1.busy = false;
			switch (myJob1.menu)
			{
			case 0:
				check.take0.waitingTime += time - myJob1.startTime;
				break;
			case 1:
				check.take1.waitingTime += time - myJob1.startTime;
				break;
			case 2:
				check.take2.waitingTime += time - myJob1.startTime;
				break;
			case 3:
				check.take3.waitingTime += time - myJob1.startTime;
				break;
			case 4:
				check.take4.waitingTime += time - myJob1.startTime;
				break;
			}
		}

		if (!busyServer2.busy) { // �ȹٻڸ� ���� 
			myJob2 = Queue_pop_front(&burgerQueue2);
			switch (myJob2.menu)
			{
			case 0:
				busyServer2.process_time = 5;
				busyServer2.busy = true;
				break;
			case 1:
				busyServer2.process_time = 10;
				busyServer2.busy = true;
				break;
			case 2:
				busyServer2.process_time = 15;
				busyServer2.busy = true;
				break;
			case 3:
				busyServer2.process_time = 20;
				busyServer2.busy = true;
				break;
			case 4:
				busyServer2.process_time = 25;
				busyServer2.busy = true;
				break;
			default:
				break;
			}

			//continue;
		}
		else if (busyServer2.busy && busyServer2.process_time == 0) {
			// �ٻ� ���� ���µ� ���� ������ �ȹٻ۰���
			busyServer2.busy = false;
			switch (myJob2.menu)
			{
			case 0:
				check.take0.waitingTime += time - myJob2.startTime;
				break;
			case 1:
				check.take1.waitingTime += time - myJob2.startTime;
				break;
			case 2:
				check.take2.waitingTime += time - myJob2.startTime;
				break;
			case 3:
				check.take3.waitingTime += time - myJob2.startTime;
				break;
			case 4:
				check.take4.waitingTime += time - myJob2.startTime;
				break;
			}
		}

		++time;
		// server1�� �ð� 1 ����
		if (busyServer1.process_time > 0)
			--busyServer1.process_time;
		// server2�� �ð� 2 ����
		if (busyServer2.process_time > 0)
			--busyServer2.process_time;
	}
	if (check.take0.takeOut_count != 0)
		check.take0.averageService_Time = (double)(check.take0.waitingTime / check.take0.takeOut_count);
	if (check.take1.takeOut_count != 0)
		check.take1.averageService_Time = (double)(check.take1.waitingTime / check.take1.takeOut_count);
	if (check.take2.takeOut_count != 0)
		check.take2.averageService_Time = (double)(check.take2.waitingTime / check.take2.takeOut_count);
	if (check.take3.takeOut_count != 0)
		check.take3.averageService_Time = (double)(check.take3.waitingTime / check.take3.takeOut_count);
	if (check.take4.takeOut_count != 0)
		check.take4.averageService_Time = (double)(check.take4.waitingTime / check.take4.takeOut_count);

	cout << "ť�� ũ�Ⱑ " << MAX_QUEUE_SIZE20 << endl;
	cout << "========== Results ==========" << endl;
	cout << "MENU-0 " << check.take0.takeOut_count << "�� ����, �������ð� " << check.take0.waitingTime << ", ��ռ��񽺽ð� " << check.take0.averageService_Time << endl;
	cout << "MENU-1 " << check.take1.takeOut_count << "�� ����, �������ð� " << check.take1.waitingTime << ", ��ռ��񽺽ð� " << check.take1.averageService_Time << endl;
	cout << "MENU-2 " << check.take2.takeOut_count << "�� ����, �������ð� " << check.take2.waitingTime << ", ��ռ��񽺽ð� " << check.take2.averageService_Time << endl;
	cout << "MENU-3 " << check.take3.takeOut_count << "�� ����, �������ð� " << check.take3.waitingTime << ", ��ռ��񽺽ð� " << check.take3.averageService_Time << endl;
	cout << "MENU-4 " << check.take4.takeOut_count << "�� ����, �������ð� " << check.take4.waitingTime << ", ��ռ��񽺽ð� " << check.take4.averageService_Time << endl;
	cout << "��ҵ� �ֹ� " << check.failOrder << " ��" << endl;
	cout << "=============================" << endl;

	busyServer1.busy = false;
	busyServer1.process_time = 0;
	busyServer2.busy = false;
	busyServer2.process_time = 0;
	time = 0;
	menuSelect = 0;
	ZeroMemory(&check, sizeof(Checklist));



	while (time < WORK_TIME) {
		if (time % 5 == 0) { // �� �մ� �ֹ�
			if (is_full(&burgerQueue3)) { // �� �ֹ��� �� �ֳ�?
				++check.failOrder;
			}
			else
			{ // q�� �������� �ʾ����� �ֹ�����
				menuSelect = rand() % 5; // �޴� ��
				element Menu;
				Menu.startTime = time;
				Menu.menu = menuSelect;
				Queue_push_back(&burgerQueue3, Menu); // q�� ���Ÿ� ����ְ�
				switch (menuSelect)
				{
				case 0:
					++check.take0.takeOut_count;
					break;
				case 1:
					++check.take1.takeOut_count;
					break;
				case 2:
					++check.take2.takeOut_count;
					break;
				case 3:
					++check.take3.takeOut_count;
					break;
				case 4:
					++check.take4.takeOut_count;
					break;
				default:
					break;
				}
			}
		}

		if (!busyServer1.busy) { // �ȹٻڸ� ���� 
			myJob1 = Queue_pop_front(&burgerQueue3);
			switch (myJob1.menu)
			{
			case 0:
				busyServer1.process_time = 5;
				busyServer1.busy = true;
				break;
			case 1:
				busyServer1.process_time = 10;
				busyServer1.busy = true;
				break;
			case 2:
				busyServer1.process_time = 15;
				busyServer1.busy = true;
				break;
			case 3:
				busyServer1.process_time = 20;
				busyServer1.busy = true;
				break;
			case 4:
				busyServer1.process_time = 25;
				busyServer1.busy = true;
				break;
			default:
				break;
			}

			//continue;
		}
		else if (busyServer1.busy && busyServer1.process_time == 0) {
			// �ٻ� ���� ���µ� ���� ������ �ȹٻ۰���
			busyServer1.busy = false;
			switch (myJob1.menu)
			{
			case 0:
				check.take0.waitingTime += time - myJob1.startTime;
				break;
			case 1:
				check.take1.waitingTime += time - myJob1.startTime;
				break;
			case 2:
				check.take2.waitingTime += time - myJob1.startTime;
				break;
			case 3:
				check.take3.waitingTime += time - myJob1.startTime;
				break;
			case 4:
				check.take4.waitingTime += time - myJob1.startTime;
				break;
			}
		}

		if (!busyServer2.busy) { // �ȹٻڸ� ���� 
			myJob2 = Queue_pop_front(&burgerQueue3);
			switch (myJob2.menu)
			{
			case 0:
				busyServer2.process_time = 5;
				busyServer2.busy = true;
				break;
			case 1:
				busyServer2.process_time = 10;
				busyServer2.busy = true;
				break;
			case 2:
				busyServer2.process_time = 15;
				busyServer2.busy = true;
				break;
			case 3:
				busyServer2.process_time = 20;
				busyServer2.busy = true;
				break;
			case 4:
				busyServer2.process_time = 25;
				busyServer2.busy = true;
				break;
			default:
				break;
			}

			//continue;
		}
		else if (busyServer2.busy && busyServer2.process_time == 0) {
			// �ٻ� ���� ���µ� ���� ������ �ȹٻ۰���
			busyServer2.busy = false;
			switch (myJob2.menu)
			{
			case 0:
				check.take0.waitingTime += time - myJob2.startTime;
				break;
			case 1:
				check.take1.waitingTime += time - myJob2.startTime;
				break;
			case 2:
				check.take2.waitingTime += time - myJob2.startTime;
				break;
			case 3:
				check.take3.waitingTime += time - myJob2.startTime;
				break;
			case 4:
				check.take4.waitingTime += time - myJob2.startTime;
				break;
			}
		}

		++time;
		// server1�� �ð� 1 ����
		if (busyServer1.process_time > 0)
			--busyServer1.process_time;
		// server2�� �ð� 2 ����
		if (busyServer2.process_time > 0)
			--busyServer2.process_time;
	}
	if (check.take0.takeOut_count != 0)
		check.take0.averageService_Time = (double)(check.take0.waitingTime / check.take0.takeOut_count);
	if (check.take1.takeOut_count != 0)
		check.take1.averageService_Time = (double)(check.take1.waitingTime / check.take1.takeOut_count);
	if (check.take2.takeOut_count != 0)
		check.take2.averageService_Time = (double)(check.take2.waitingTime / check.take2.takeOut_count);
	if (check.take3.takeOut_count != 0)
		check.take3.averageService_Time = (double)(check.take3.waitingTime / check.take3.takeOut_count);
	if (check.take4.takeOut_count != 0)
		check.take4.averageService_Time = (double)(check.take4.waitingTime / check.take4.takeOut_count);

	cout << "ť�� ũ�Ⱑ " << MAX_QUEUE_SIZE30 << endl;
	cout << "========== Results ==========" << endl;
	cout << "MENU-0 " << check.take0.takeOut_count << "�� ����, �������ð� " << check.take0.waitingTime << ", ��ռ��񽺽ð� " << check.take0.averageService_Time << endl;
	cout << "MENU-1 " << check.take1.takeOut_count << "�� ����, �������ð� " << check.take1.waitingTime << ", ��ռ��񽺽ð� " << check.take1.averageService_Time << endl;
	cout << "MENU-2 " << check.take2.takeOut_count << "�� ����, �������ð� " << check.take2.waitingTime << ", ��ռ��񽺽ð� " << check.take2.averageService_Time << endl;
	cout << "MENU-3 " << check.take3.takeOut_count << "�� ����, �������ð� " << check.take3.waitingTime << ", ��ռ��񽺽ð� " << check.take3.averageService_Time << endl;
	cout << "MENU-4 " << check.take4.takeOut_count << "�� ����, �������ð� " << check.take4.waitingTime << ", ��ռ��񽺽ð� " << check.take4.averageService_Time << endl;
	cout << "��ҵ� �ֹ� " << check.failOrder << " ��" << endl;
	cout << "=============================" << endl;

	busyServer1.busy = false;
	busyServer1.process_time = 0;
	busyServer2.busy = false;
	busyServer2.process_time = 0;
	time = 0;
	menuSelect = 0;
	ZeroMemory(&check, sizeof(Checklist));



	while (time < WORK_TIME) {
		if (time % 5 == 0) { // �� �մ� �ֹ�
			if (is_full(&burgerQueue4)) { // �� �ֹ��� �� �ֳ�?
				++check.failOrder;
			}
			else
			{ // q�� �������� �ʾ����� �ֹ�����
				menuSelect = rand() % 5; // �޴� ��
				element Menu;
				Menu.startTime = time;
				Menu.menu = menuSelect;
				Queue_push_back(&burgerQueue4, Menu); // q�� ���Ÿ� ����ְ�
				switch (menuSelect)
				{
				case 0:
					++check.take0.takeOut_count;
					break;
				case 1:
					++check.take1.takeOut_count;
					break;
				case 2:
					++check.take2.takeOut_count;
					break;
				case 3:
					++check.take3.takeOut_count;
					break;
				case 4:
					++check.take4.takeOut_count;
					break;
				default:
					break;
				}
			}
		}

		if (!busyServer1.busy) { // �ȹٻڸ� ���� 
			myJob1 = Queue_pop_front(&burgerQueue4);
			switch (myJob1.menu)
			{
			case 0:
				busyServer1.process_time = 5;
				busyServer1.busy = true;
				break;
			case 1:
				busyServer1.process_time = 10;
				busyServer1.busy = true;
				break;
			case 2:
				busyServer1.process_time = 15;
				busyServer1.busy = true;
				break;
			case 3:
				busyServer1.process_time = 20;
				busyServer1.busy = true;
				break;
			case 4:
				busyServer1.process_time = 25;
				busyServer1.busy = true;
				break;
			default:
				break;
			}

			//continue;
		}
		else if (busyServer1.busy && busyServer1.process_time == 0) {
			// �ٻ� ���� ���µ� ���� ������ �ȹٻ۰���
			busyServer1.busy = false;
			switch (myJob1.menu)
			{
			case 0:
				check.take0.waitingTime += time - myJob1.startTime;
				break;
			case 1:
				check.take1.waitingTime += time - myJob1.startTime;
				break;
			case 2:
				check.take2.waitingTime += time - myJob1.startTime;
				break;
			case 3:
				check.take3.waitingTime += time - myJob1.startTime;
				break;
			case 4:
				check.take4.waitingTime += time - myJob1.startTime;
				break;
			}
		}

		if (!busyServer2.busy) { // �ȹٻڸ� ���� 
			myJob2 = Queue_pop_front(&burgerQueue4);
			switch (myJob2.menu)
			{
			case 0:
				busyServer2.process_time = 5;
				busyServer2.busy = true;
				break;
			case 1:
				busyServer2.process_time = 10;
				busyServer2.busy = true;
				break;
			case 2:
				busyServer2.process_time = 15;
				busyServer2.busy = true;
				break;
			case 3:
				busyServer2.process_time = 20;
				busyServer2.busy = true;
				break;
			case 4:
				busyServer2.process_time = 25;
				busyServer2.busy = true;
				break;
			default:
				break;
			}

			//continue;
		}
		else if (busyServer2.busy && busyServer2.process_time == 0) {
			// �ٻ� ���� ���µ� ���� ������ �ȹٻ۰���
			busyServer2.busy = false;
			switch (myJob2.menu)
			{
			case 0:
				check.take0.waitingTime += time - myJob2.startTime;
				break;
			case 1:
				check.take1.waitingTime += time - myJob2.startTime;
				break;
			case 2:
				check.take2.waitingTime += time - myJob2.startTime;
				break;
			case 3:
				check.take3.waitingTime += time - myJob2.startTime;
				break;
			case 4:
				check.take4.waitingTime += time - myJob2.startTime;
				break;
			}
		}

		++time;
		// server1�� �ð� 1 ����
		if (busyServer1.process_time > 0)
			--busyServer1.process_time;
		// server2�� �ð� 2 ����
		if (busyServer2.process_time > 0)
			--busyServer2.process_time;
	}
	if (check.take0.takeOut_count != 0)
		check.take0.averageService_Time = (double)(check.take0.waitingTime / check.take0.takeOut_count);
	if (check.take1.takeOut_count != 0)
		check.take1.averageService_Time = (double)(check.take1.waitingTime / check.take1.takeOut_count);
	if (check.take2.takeOut_count != 0)
		check.take2.averageService_Time = (double)(check.take2.waitingTime / check.take2.takeOut_count);
	if (check.take3.takeOut_count != 0)
		check.take3.averageService_Time = (double)(check.take3.waitingTime / check.take3.takeOut_count);
	if (check.take4.takeOut_count != 0)
		check.take4.averageService_Time = (double)(check.take4.waitingTime / check.take4.takeOut_count);

	cout << "ť�� ũ�Ⱑ " << MAX_QUEUE_SIZE40 << endl;
	cout << "========== Results ==========" << endl;
	cout << "MENU-0 " << check.take0.takeOut_count << "�� ����, �������ð� " << check.take0.waitingTime << ", ��ռ��񽺽ð� " << check.take0.averageService_Time << endl;
	cout << "MENU-1 " << check.take1.takeOut_count << "�� ����, �������ð� " << check.take1.waitingTime << ", ��ռ��񽺽ð� " << check.take1.averageService_Time << endl;
	cout << "MENU-2 " << check.take2.takeOut_count << "�� ����, �������ð� " << check.take2.waitingTime << ", ��ռ��񽺽ð� " << check.take2.averageService_Time << endl;
	cout << "MENU-3 " << check.take3.takeOut_count << "�� ����, �������ð� " << check.take3.waitingTime << ", ��ռ��񽺽ð� " << check.take3.averageService_Time << endl;
	cout << "MENU-4 " << check.take4.takeOut_count << "�� ����, �������ð� " << check.take4.waitingTime << ", ��ռ��񽺽ð� " << check.take4.averageService_Time << endl;
	cout << "��ҵ� �ֹ� " << check.failOrder << " ��" << endl;
	cout << "=============================" << endl;

}

void init_queue(QueueType* q, int _size)
{
	q->rear = 0;
	q->front = 0;
	q->size = _size;
	q->menu = new element[_size];
}

int is_full(QueueType* q)
{
	if ((q->rear + 1) % q->size == q->front)
		return 1;

	return 0;

}

int myis_empty(QueueType* q)
{
	if (q->front == q->rear)
		return 1;

	return 0;
}

void Queue_push_back(QueueType* q, element item)
{
	if (is_full(q)) {

		return;
	}
	q->menu[(q->rear)] = item;
	q->rear = (q->rear + 1) % q->size;
}

element Queue_pop_front(QueueType* q)
{
	if (myis_empty(q)) {
		element empty;
		empty.menu = 8;
		return empty;
	}
	q->front = (q->front + 1) % q->size;
	element item = q->menu[q->front];
	return item;
}
