#include <iostream>
#include <Windows.h>
#include <time.h>
using namespace std;

#define MAX_QUEUE_SIZE 10000
typedef struct element {
	int N;
	int T;
};
typedef struct {
	int front;
	int rear;
	int size;
	element* data;
	int checkList[MAX_QUEUE_SIZE];
	int count;
}QueueType;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
void init_queue(QueueType* q, int _size);
bool is_full(QueueType* q);
bool myis_empty(QueueType* q);
void pushQueue(QueueType* q, element item);
element popQueue(QueueType* q);
int main()
{
	srand(unsigned(time(NULL)));
	QueueType virus;
	ZeroMemory(&virus, sizeof(QueueType));
	init_queue(&virus, MAX_QUEUE_SIZE);
	element first = { 1,0 };

	element checkingvirus;
	bool b_1 = false;
	bool b_2 = false;

	virus.checkList[virus.count] = first.N;
	++virus.count;
	pushQueue(&virus, first); // 1 0

	int virusNum;
	cout << "현재 바이러스 수 입력 : ";
	cin >> virusNum;

	while (true) {
		checkingvirus = popQueue(&virus);
		if (checkingvirus.N == virusNum) {
			break;
		}

		b_1 = false;
		b_2 = false;
		element multiply_virus;
		element divide_virus;
		multiply_virus.N = checkingvirus.N * 2;
		multiply_virus.T = checkingvirus.T + 1;
		divide_virus.N = checkingvirus.N / 3;
		divide_virus.T = checkingvirus.T + 1;

		for (int i = 0; i < virus.count; ++i) {
			if (virus.checkList[i] == multiply_virus.N) {
				b_1 = true; // true이면 push하지마
			}
			if (virus.checkList[i] == divide_virus.N) {
				b_2 = true; // true이면 push하지마
			}
		}
		if (!b_1) // 순회 했을 때 없었음
		{
			virus.checkList[virus.count] = multiply_virus.N;
			++virus.count;
			if (virus.count >= MAX_QUEUE_SIZE) {
				cout << "큐는 포화 상태입니다." << endl;
				delete[] virus.data;
				virus.data = nullptr;
				return 0;
			}
			pushQueue(&virus, multiply_virus);
		}
		if (!b_2) // 순회 했을때 없었음
		{
			virus.checkList[virus.count] = divide_virus.N;
			++virus.count;
			if (virus.count >= MAX_QUEUE_SIZE) {
				cout << "큐는 포화 상태입니다." << endl;
				delete[] virus.data;
				virus.data = nullptr;
				return 0;
			}
			pushQueue(&virus, divide_virus);
		}
	}
	cout << checkingvirus.N << " 마리가 되는 데 필요한 소요 시간 : " << checkingvirus.T << endl;
	delete[] virus.data;
	virus.data = nullptr;
}

void init_queue(QueueType* q, int _size)
{
	q->rear = 0;
	q->front = 0;
	q->size = _size;
	q->data = new element[_size];
}

bool is_full(QueueType* q)
{
	if ((q->rear + 1) % q->size == q->front)
		return true;
	return false;
}

bool myis_empty(QueueType* q)
{
	if (q->front == q->rear)
		return true;
	return false;
}

void pushQueue(QueueType* q, element item)
{
	if (is_full(q)) {
		cout << "큐가 포화입니다." << endl;
	}
	q->data[(q->rear)] = item;
	q->rear = (q->rear + 1) % q->size;
}

element popQueue(QueueType* q)
{
	if (myis_empty(q)) {
		error((char*)"큐가 공백입니다.");
	}
	element item = q->data[q->front];
	q->front = (q->front + 1) % q->size;
	return item;
}
