#include <iostream>
using namespace std;

#define WAIT_QUEUE_SIZE 1000 // ���ť
#define READY_QUEUE_SIZE 10 // �غ�ť
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
	int size; // ũ�� �ִ� ���� �� �ִ� ����
	int count; // ��� ����
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
	// �׽�Ʈ�� JOB ����
	for (int i = 0; i < NUM_JOBS; ++i) {
		jobs[i].Job_id = i;
		jobs[i].Priority = rand() % 10;					// priority;
		jobs[i].Arrival_time = rand();					// arrival_time
		jobs[i].Run_time = (rand() % 10 + 5) * 10;		// run_time
		jobs[i].Remaning_time = jobs[i].Run_time;
		jobs[i].Run_count = 0;
		jobs[i].Delay_time = 0;

	}


	// ��� ť�� �غ� ť �ʱ�ȭ
	init_Priorityqueue(&Wait_Q, WAIT_QUEUE_SIZE);
	init_Readyqueue(&Ready_Q);

	// ���μ��� �����ٸ�
	while (1) {
		remain_job_count -= job_create(jobs, remain_job_count, &Wait_Q,
			processing_time);

		job_dispatcher(&Wait_Q, &Ready_Q);
		processing_time = job_process(&Wait_Q, &Ready_Q, processing_time);

		++processing_time; // CPU �ð��� �帧

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
		cout << "�غ� ť�� ��ȭ" << endl;
		return;
	}
	q->data[q->rear] = _item;
	q->rear = (q->rear + 1) % READY_QUEUE_SIZE;
}

data_element popReadyQueue(ReadyQueue* q)
{
	if (myis_Readyempty(q)) {
		cout << "�غ� ť�� �����" << endl;
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
	q->size = _size; // �����ŭ
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
		cout << "ť�� ��ȭ�Դϴ�." << endl;
		return;
	}

	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
	temp->data = item;
	temp->link = nullptr;

	if (myis_Priorityempty(*q)) { // ť�� �����Ͱ� ������
		(*q)->queue = temp;
	}
	else { // �ϳ��� ������

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
		cout << "ť�� �����Դϴ�." << endl;
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
	if (!myis_Priorityempty(_wait)) { // ���ť�� �۾��� ����
		if (myis_Readyempty(_Ready)) { // �غ�ť�� �������
			data_element data = popPriorityQueue(_wait);
			data.Delay_time = Delay_Time;
			// �켱 ������ ���� ���� �۾��� ���ť���� �غ�ť�� �̵�
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

	if (!workCheck) { // CPU�� �Ҵ�Ǿ����� ������
		// ���μ����� �غ� ť�� �۾��� �����ϸ�
		if (!myis_Readyempty(_Ready)) {
			// ���� �տ� �ִ� �۾��� �о�ͼ�
			p = 0;
			CPUdata = popReadyQueue(_Ready);
			workCheck = true;
		}
	}
	else {
		// �־��� �ð�����ŭ �����Ѵ�.
		CPUdata.Remaning_time -= 1;
		++p;
		if (CPUdata.Remaning_time <= 0) {
			// �ش� �۾��� �����ϰ� ��� ���
			++CPUdata.Run_count; // ����Ƚ�� 1ȸ �߰��ϰ�
			cout << "�ð� " << _processTime
				<< " : �۾� " << CPUdata.Job_id
				<< " ����(�����ð� : " << CPUdata.Arrival_time
				<< ", ����ð� : " << CPUdata.Run_time
				<< ", ����Ƚ�� : " << CPUdata.Run_count
				<< ", �����ð� " << _processTime - CPUdata.Arrival_time
				<< ")" << endl;
			workCheck = false;
		}
		else if (p > TIME_SLOT) { // �ð��� ���� �۾��� ������� ������
			++CPUdata.Priority; // �켱������ 1���� ��Ű��
			++CPUdata.Run_count; // ����Ƚ�� 1ȸ �߰�
			workCheck = false;
			pushReadyQueue(_Ready, CPUdata); // ���ť�� ������.
		}
	}

	return _processTime;


}
