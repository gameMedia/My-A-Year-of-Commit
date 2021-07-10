#include <iostream>
#include <time.h>
#include <chrono>
using namespace std;

#define MAX_LIST_SIZE 10'000

typedef int element;

typedef struct a {
	element data[MAX_LIST_SIZE];
	int size;
}ArrayListType;

ArrayListType arrayList;

void arrayInit(ArrayListType* _list);
void sortInsert(int _index, ArrayListType* _list, element _item);
int arrayAdd(ArrayListType* _list, element _item);
int arrayDelete(ArrayListType* _list, element _item);
void arrayClear(ArrayListType* _list);
int is_in_array(ArrayListType* _list, element _item);
int get_length(ArrayListType* _list);
int is_emptyArray(ArrayListType* _list);
int is_fullArray(ArrayListType* _list);
void displayArray(ArrayListType* _list);

int main()
{
	srand(unsigned(time(NULL)));
	arrayInit(&arrayList);

	int iSelect = 0;
	element checkElement = {};

	cout << "배열을 이용하여 정렬리스트 만들기" << endl;

	chrono::system_clock::time_point startTime = chrono::system_clock::now();

	for (int i = 0; i < MAX_LIST_SIZE; ++i) {
		element item = rand();
		arrayAdd(&arrayList, item);
	}

	chrono::system_clock::time_point endTime = chrono::system_clock::now();
	chrono::milliseconds  miliSec = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
	cout << MAX_LIST_SIZE << "개, 총 소요시간 " << miliSec.count() << " ms" << endl;
}

void arrayInit(ArrayListType* _list)
{
	for (int i = 0; i < MAX_LIST_SIZE; ++i) {
		_list->data[i] = 0;
	}
	_list->size = 0;
}

void sortInsert(int _index, ArrayListType* _list, element _item)
{
	memmove(_list->data + _index + 1, _list->data + _index, sizeof(element) * (_list->size - _index));
	++_list->size;
	_list->data[_index] = _item;
}


int arrayAdd(ArrayListType* _list, element _item)
{
	if (is_fullArray(_list)) {
		cout << "가득차 있어요" << endl;
		return 0;
	}
	if (_list->size == 0) {
		_list->data[_list->size] = _item;
		++_list->size;
	}
	else {
		for (int i = 0; i < _list->size; ++i) {
			element temp1 = _list->data[i];
			if (_item < temp1) { // _item이 현재 data보다 작으면 그자리에 넣어야지
				sortInsert(i, _list, _item);
				return 1;
			}
			else if (i == _list->size - 1) { // 끝까지 탐색헀을때 없으면
				_list->data[_list->size] = _item;
				++_list->size;
				return 1;
			}
		}
	}
}



int arrayDelete(ArrayListType* _list, element _item)
{
	int check = 0;
	for (int i = 0; i < _list->size; ++i) {
		if (_list->data[i] == _item) {
			if (i == _list->size) return 0; // 없음
			check = i;
			break;
		}
	}

	for (int j = check; j < _list->size - 1; ++j) {
		_list->data[j] = _list->data[j + 1];
	}

	--_list->size;

	return check;
}

void arrayClear(ArrayListType* _list)
{
	for (int i = 0; i < _list->size; ++i) {
		_list->data[i] = 0;
	}
	_list->size = 0;
}

int is_in_array(ArrayListType* _list, element _item)
{
	int check = 0;
	for (int i = 0; i < _list->size; ++i) {
		if (_list->data[i] == _item) {
			if (i == _list->size) return 0; // 없음
			check = i;
			break;
		}
	}
	return check;
}

int get_length(ArrayListType* _list)
{
	return _list->size;
}

int is_emptyArray(ArrayListType* _list)
{
	return _list->size == 0;
}

int is_fullArray(ArrayListType* _list)
{
	return _list->size == MAX_LIST_SIZE;
}

void displayArray(ArrayListType* _list)
{
	for (int i = 0; i < _list->size; ++i) {
		cout << _list->data[i] << " ";
	}
}
