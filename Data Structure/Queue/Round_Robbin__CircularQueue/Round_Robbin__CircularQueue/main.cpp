#include <iostream>
using namespace std;

#define WAIT_QUEUE_SIZE 1000 // 대기큐
#define READY_QUEUE_SIZE 10 // 준비큐
#define NUM_JOBS 1000
#define TIME_SLOT 10

typedef struct DATA_ELEMENT {
	int Job_id;
	int Priority;
	int Arrival_time;
	int Run_time;
	int Remaning_time;
	int Run_count;
	int Delay_time;
}data_element;

typedef struct QueueNode {
	data_element data;
	struct QueueNode* link;

}QueueNode;

typedef struct {
	QueueNode* queue;
	int size; // 크기 최대 담을 수 있는 갯수
	int count; // 담긴 갯수
}PriorityQueue;

typedef struct {
	int front;
	int rear;
	data_element data[READY_QUEUE_SIZE];
}ReadyQueue;

DATA_ELEMENT jobs[NUM_JOBS];
int Delay_Time = 0;
int Jobcount = 0;

void init_Readyqueue(ReadyQueue* q);
bool is_Readyfull(ReadyQueue* q);
bool myis_Readyempty(ReadyQueue* q);
void pushReadyQueue(ReadyQueue* q, data_element _item);
data_element popReadyQueue(ReadyQueue* q);

void init_Priorityqueue(PriorityQueue* q, int _size);
bool is_Priorityfull(PriorityQueue* q);
bool myis_Priorityempty(PriorityQueue* q);
void pushPriorityQueue(PriorityQueue** q, data_element item);
data_element popPriorityQueue(PriorityQueue* q);

int job_create(DATA_ELEMENT* _jobs, int _count, PriorityQueue* _waitQueue, int _processTime);
void job_dispatcher(PriorityQueue* _wait, ReadyQueue* _Ready);
int job_process(PriorityQueue* _wait, ReadyQueue* _Ready, int _processTime);

int main()
{
	PriorityQueue Wait_Q;
	ReadyQueue Ready_Q;
	int remain_job_count = NUM_JOBS;
	int processing_time = 0;
	// 테스트할 JOB 생성
	for (int i = 0; i < NUM_JOBS; ++i) {
		jobs[i].Job_id = i;
		jobs[i].Priority = rand() % 10;					// priority;
		jobs[i].Arrival_time = rand();					// arrival_time
		jobs[i].Run_time = (rand() % 10 + 5) * 10;		// run_time
		jobs[i].Remaning_time = jobs[i].Run_time;
		jobs[i].Run_count = 0;
		jobs[i].Delay_time = 0;

	}


	// 대기 큐와 준비 큐 초기화
	init_Priorityqueue(&Wait_Q, WAIT_QUEUE_SIZE);
	init_Readyqueue(&Ready_Q);

	// 프로세스 스케줄링
	while (1) {
		remain_job_count -= job_create(jobs, remain_job_count, &Wait_Q,
			processing_time);

		job_dispatcher(&Wait_Q, &Ready_Q);
		processing_time = job_process(&Wait_Q, &Ready_Q, processing_time);

		++processing_time; // CPU 시간이 흐름

		if (remain_job_count == 0 && myis_Priorityempty(&Wait_Q) && myis_Readyempty(&Ready_Q))
			break;
	}

	cout << Jobcount << endl;



}

void init_Readyqueue(ReadyQueue* q)
{
	q->front = 0;
	q->rear = 0;
}

bool is_Readyfull(ReadyQueue* q)
{
	if ((q->rear + 1) % READY_QUEUE_SIZE == q->front)
		return true;
	return false;
}

bool myis_Readyempty(ReadyQueue* q)
{
	if (q->front == q->rear)
		return true;
	return false;
}

void pushReadyQueue(ReadyQueue* q, data_element _item)
{
	if (is_Readyfull(q)) {
		cout << "준비 큐가 포화" << endl;
		return;
	}
	q->data[q->rear] = _item;
	q->rear = (q->rear + 1) % READY_QUEUE_SIZE;
}

data_element popReadyQueue(ReadyQueue* q)
{
	if (myis_Readyempty(q)) {
		cout << "준비 큐가 비었다" << endl;
		data_element nullEle = {};
		return nullEle;
	}
	data_element data = q->data[q->front];
	q->front = (q->front + 1) % READY_QUEUE_SIZE;
	return data;
}

void init_Priorityqueue(PriorityQueue* q, int _size)
{
	q->queue = nullptr;
	q->size = _size; // 사이즈만큼
	q->count = 0;
}

bool is_Priorityfull(PriorityQueue* q)
{
	return q->count == q->size;
}

bool myis_Priorityempty(PriorityQueue* q)
{
	return q->count == 0;
}

void pushPriorityQueue(PriorityQueue** q, data_element item)
{
	if (is_Priorityfull(*q)) {
		cout << "큐가 포화입니다." << endl;
		return;
	}

	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
	temp->data = item;
	temp->link = nullptr;

	if (myis_Priorityempty(*q)) { // 큐에 데이터가 없으면
		(*q)->queue = temp;
	}
	else { // 하나라도 있으면

		QueueNode* p = (*q)->queue;
		QueueNode* prev = nullptr;

		while (p) {
			if (p->data.Priority > temp->data.Priority)
				break;
			prev = p;
			p = p->link;
		}
		if (prev == nullptr) {
			temp->link = (*q)->queue;
			(*q)->queue = temp;
		}
		else {
			temp->link = prev->link;
			prev->link = temp;
		}

	}
	++((*q)->count);
}

data_element popPriorityQueue(PriorityQueue* q)
{
	if (myis_Priorityempty(q)) {
		cout << "큐가 공백입니다." << endl;
		data_element nullEle = {};
		return nullEle;
	}

	QueueNode* cur = nullptr;
	cur = q->queue;
	data_element data;
	data = cur->data;
	q->queue = q->queue->link;
	free(cur);
	--q->count;

	return data;

}

int job_create(DATA_ELEMENT* _jobs, int _count, PriorityQueue* _waitQueue, int _processTime)
{
	int count = 0;
	for (int i = 0; i < NUM_JOBS; ++i) {
		if (_jobs[i].Arrival_time == _processTime) {
			pushPriorityQueue(&_waitQueue, _jobs[i]);
			++count;
		}
	}
	return count;
}

void job_dispatcher(PriorityQueue* _wait, ReadyQueue* _Ready)
{
	if (!myis_Priorityempty(_wait)) { // 대기큐에 작업이 존재
		if (myis_Readyempty(_Ready)) { // 준비큐가 비었으면
			data_element data = popPriorityQueue(_wait);
			data.Delay_time = Delay_Time;
			// 우선 순위가 가장 높은 작업을 대기큐에서 준비큐로 이동
			pushReadyQueue(_Ready, data);
		}
	}
	else {
		++Delay_Time;
	}
}

int p = 0;
bool workCheck = false;
data_element CPUdata;
int job_process(PriorityQueue* _wait, ReadyQueue* _Ready, int _processTime)
{

	if (!workCheck) { // CPU가 할당되어있지 않으면
		// 프로세서는 준비 큐에 작업이 존재하면
		if (!myis_Readyempty(_Ready)) {
			// 가장 앞에 있는 작업을 읽어와서
			p = 0;
			CPUdata = popReadyQueue(_Ready);
			workCheck = true;
		}
	}
	else {
		// 주어진 시간량만큼 수행한다.
		CPUdata.Remaning_time -= 1;
		++p;
		if (CPUdata.Remaning_time <= 0) {
			// 해당 작업을 종료하고 결과 출력
			++CPUdata.Run_count; // 실행횟수 1회 추가하고
			cout << "시간 " << _processTime
				<< " : 작업 " << CPUdata.Job_id
				<< " 종료(도착시간 : " << CPUdata.Arrival_time
				<< ", 실행시간 : " << CPUdata.Run_time
				<< ", 실행횟수 : " << CPUdata.Run_count
				<< ", 지연시간 " << _processTime - CPUdata.Arrival_time
				<< ")" << endl;
			workCheck = false;
		}
		else if (p > TIME_SLOT) { // 시간량 내에 작업이 종료되지 않으면
			++CPUdata.Priority; // 우선순위를 1감소 시키고
			++CPUdata.Run_count; // 실행횟수 1회 추가
			workCheck = false;
			pushReadyQueue(_Ready, CPUdata); // 대기큐로 보낸다.
		}
	}

	return _processTime;


}
