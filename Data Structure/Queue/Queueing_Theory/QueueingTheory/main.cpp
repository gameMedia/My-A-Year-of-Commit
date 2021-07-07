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

// Menu 0	 5초
// Menu 1	10초
// Menu 2	15초
// Menu 3	20초
// Menu 4	25초

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
	int takeOut_count;// 팔린 갯수
	int waitingTime; // 누적 대기 시간
	double averageService_Time; // 평균 서비스 시간
};

typedef struct Checklist {
	Burger take0;
	Burger take1;
	Burger take2;
	Burger take3;
	Burger take4;
	int failOrder; // 실패 주문
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
	server busyServer1;	// 종업원 1
	server busyServer2;	// 종업원 2
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
		if (time % 5 == 0) { // 새 손님 주문
			if (is_full(&burgerQueue1)) { // 더 주문할 수 있나?
				++check.failOrder;
			}
			else
			{ // q가 가득차지 않았으면 주문가능
				menuSelect = rand() % 5; // 메뉴 고름
				element Menu;
				Menu.startTime = time;
				Menu.menu = menuSelect;
				Queue_push_back(&burgerQueue1, Menu); // q에 버거를 집어넣고
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

		if (!busyServer1.busy) { // 안바쁘면 일해 
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
			// 바쁜 상태 였는데 일이 끝나면 안바쁜거임
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

		if (!busyServer2.busy) { // 안바쁘면 일해 
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
			// 바쁜 상태 였는데 일이 끝나면 안바쁜거임
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
		// server1의 시간 1 감소
		if (busyServer1.process_time > 0)
			--busyServer1.process_time;
		// server2의 시간 2 감소
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

	cout << "큐의 크기가 " << MAX_QUEUE_SIZE10 << endl;
	cout << "========== Results ==========" << endl;
	cout << "MENU-0 " << check.take0.takeOut_count << "개 서비스, 누적대기시간 " << check.take0.waitingTime << ", 평균서비스시간 " << check.take0.averageService_Time << endl;
	cout << "MENU-1 " << check.take1.takeOut_count << "개 서비스, 누적대기시간 " << check.take1.waitingTime << ", 평균서비스시간 " << check.take1.averageService_Time << endl;
	cout << "MENU-2 " << check.take2.takeOut_count << "개 서비스, 누적대기시간 " << check.take2.waitingTime << ", 평균서비스시간 " << check.take2.averageService_Time << endl;
	cout << "MENU-3 " << check.take3.takeOut_count << "개 서비스, 누적대기시간 " << check.take3.waitingTime << ", 평균서비스시간 " << check.take3.averageService_Time << endl;
	cout << "MENU-4 " << check.take4.takeOut_count << "개 서비스, 누적대기시간 " << check.take4.waitingTime << ", 평균서비스시간 " << check.take4.averageService_Time << endl;
	cout << "취소된 주문 " << check.failOrder << " 개" << endl;
	cout << "=============================" << endl;

	busyServer1.busy = false;
	busyServer1.process_time = 0;
	busyServer2.busy = false;
	busyServer2.process_time = 0;
	time = 0;
	menuSelect = 0;
	ZeroMemory(&check, sizeof(Checklist));



	while (time < WORK_TIME) {
		if (time % 5 == 0) { // 새 손님 주문
			if (is_full(&burgerQueue2)) { // 더 주문할 수 있나?
				++check.failOrder;
			}
			else
			{ // q가 가득차지 않았으면 주문가능
				menuSelect = rand() % 5; // 메뉴 고름
				element Menu;
				Menu.startTime = time;
				Menu.menu = menuSelect;
				Queue_push_back(&burgerQueue2, Menu); // q에 버거를 집어넣고
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

		if (!busyServer1.busy) { // 안바쁘면 일해 
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
			// 바쁜 상태 였는데 일이 끝나면 안바쁜거임
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

		if (!busyServer2.busy) { // 안바쁘면 일해 
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
			// 바쁜 상태 였는데 일이 끝나면 안바쁜거임
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
		// server1의 시간 1 감소
		if (busyServer1.process_time > 0)
			--busyServer1.process_time;
		// server2의 시간 2 감소
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

	cout << "큐의 크기가 " << MAX_QUEUE_SIZE20 << endl;
	cout << "========== Results ==========" << endl;
	cout << "MENU-0 " << check.take0.takeOut_count << "개 서비스, 누적대기시간 " << check.take0.waitingTime << ", 평균서비스시간 " << check.take0.averageService_Time << endl;
	cout << "MENU-1 " << check.take1.takeOut_count << "개 서비스, 누적대기시간 " << check.take1.waitingTime << ", 평균서비스시간 " << check.take1.averageService_Time << endl;
	cout << "MENU-2 " << check.take2.takeOut_count << "개 서비스, 누적대기시간 " << check.take2.waitingTime << ", 평균서비스시간 " << check.take2.averageService_Time << endl;
	cout << "MENU-3 " << check.take3.takeOut_count << "개 서비스, 누적대기시간 " << check.take3.waitingTime << ", 평균서비스시간 " << check.take3.averageService_Time << endl;
	cout << "MENU-4 " << check.take4.takeOut_count << "개 서비스, 누적대기시간 " << check.take4.waitingTime << ", 평균서비스시간 " << check.take4.averageService_Time << endl;
	cout << "취소된 주문 " << check.failOrder << " 개" << endl;
	cout << "=============================" << endl;

	busyServer1.busy = false;
	busyServer1.process_time = 0;
	busyServer2.busy = false;
	busyServer2.process_time = 0;
	time = 0;
	menuSelect = 0;
	ZeroMemory(&check, sizeof(Checklist));



	while (time < WORK_TIME) {
		if (time % 5 == 0) { // 새 손님 주문
			if (is_full(&burgerQueue3)) { // 더 주문할 수 있나?
				++check.failOrder;
			}
			else
			{ // q가 가득차지 않았으면 주문가능
				menuSelect = rand() % 5; // 메뉴 고름
				element Menu;
				Menu.startTime = time;
				Menu.menu = menuSelect;
				Queue_push_back(&burgerQueue3, Menu); // q에 버거를 집어넣고
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

		if (!busyServer1.busy) { // 안바쁘면 일해 
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
			// 바쁜 상태 였는데 일이 끝나면 안바쁜거임
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

		if (!busyServer2.busy) { // 안바쁘면 일해 
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
			// 바쁜 상태 였는데 일이 끝나면 안바쁜거임
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
		// server1의 시간 1 감소
		if (busyServer1.process_time > 0)
			--busyServer1.process_time;
		// server2의 시간 2 감소
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

	cout << "큐의 크기가 " << MAX_QUEUE_SIZE30 << endl;
	cout << "========== Results ==========" << endl;
	cout << "MENU-0 " << check.take0.takeOut_count << "개 서비스, 누적대기시간 " << check.take0.waitingTime << ", 평균서비스시간 " << check.take0.averageService_Time << endl;
	cout << "MENU-1 " << check.take1.takeOut_count << "개 서비스, 누적대기시간 " << check.take1.waitingTime << ", 평균서비스시간 " << check.take1.averageService_Time << endl;
	cout << "MENU-2 " << check.take2.takeOut_count << "개 서비스, 누적대기시간 " << check.take2.waitingTime << ", 평균서비스시간 " << check.take2.averageService_Time << endl;
	cout << "MENU-3 " << check.take3.takeOut_count << "개 서비스, 누적대기시간 " << check.take3.waitingTime << ", 평균서비스시간 " << check.take3.averageService_Time << endl;
	cout << "MENU-4 " << check.take4.takeOut_count << "개 서비스, 누적대기시간 " << check.take4.waitingTime << ", 평균서비스시간 " << check.take4.averageService_Time << endl;
	cout << "취소된 주문 " << check.failOrder << " 개" << endl;
	cout << "=============================" << endl;

	busyServer1.busy = false;
	busyServer1.process_time = 0;
	busyServer2.busy = false;
	busyServer2.process_time = 0;
	time = 0;
	menuSelect = 0;
	ZeroMemory(&check, sizeof(Checklist));



	while (time < WORK_TIME) {
		if (time % 5 == 0) { // 새 손님 주문
			if (is_full(&burgerQueue4)) { // 더 주문할 수 있나?
				++check.failOrder;
			}
			else
			{ // q가 가득차지 않았으면 주문가능
				menuSelect = rand() % 5; // 메뉴 고름
				element Menu;
				Menu.startTime = time;
				Menu.menu = menuSelect;
				Queue_push_back(&burgerQueue4, Menu); // q에 버거를 집어넣고
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

		if (!busyServer1.busy) { // 안바쁘면 일해 
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
			// 바쁜 상태 였는데 일이 끝나면 안바쁜거임
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

		if (!busyServer2.busy) { // 안바쁘면 일해 
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
			// 바쁜 상태 였는데 일이 끝나면 안바쁜거임
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
		// server1의 시간 1 감소
		if (busyServer1.process_time > 0)
			--busyServer1.process_time;
		// server2의 시간 2 감소
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

	cout << "큐의 크기가 " << MAX_QUEUE_SIZE40 << endl;
	cout << "========== Results ==========" << endl;
	cout << "MENU-0 " << check.take0.takeOut_count << "개 서비스, 누적대기시간 " << check.take0.waitingTime << ", 평균서비스시간 " << check.take0.averageService_Time << endl;
	cout << "MENU-1 " << check.take1.takeOut_count << "개 서비스, 누적대기시간 " << check.take1.waitingTime << ", 평균서비스시간 " << check.take1.averageService_Time << endl;
	cout << "MENU-2 " << check.take2.takeOut_count << "개 서비스, 누적대기시간 " << check.take2.waitingTime << ", 평균서비스시간 " << check.take2.averageService_Time << endl;
	cout << "MENU-3 " << check.take3.takeOut_count << "개 서비스, 누적대기시간 " << check.take3.waitingTime << ", 평균서비스시간 " << check.take3.averageService_Time << endl;
	cout << "MENU-4 " << check.take4.takeOut_count << "개 서비스, 누적대기시간 " << check.take4.waitingTime << ", 평균서비스시간 " << check.take4.averageService_Time << endl;
	cout << "취소된 주문 " << check.failOrder << " 개" << endl;
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
