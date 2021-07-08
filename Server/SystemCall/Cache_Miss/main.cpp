#include <iostream>
#include <chrono>
#include <Windows.h>


using namespace std;
using namespace chrono;

#define CACHE_LINE_SIZE 64
#define Hundred_Thousand 100'000'000

int main()
{
	for (int i = 0; i < 10; ++i) {
		int size = (1024 * 1024) << i;
		char* a = (char*)malloc(size);
		unsigned int index = 0;
		volatile unsigned int tmp = 0;
		auto start = high_resolution_clock::now();
		for (int j = 0; j < Hundred_Thousand; ++j) {
			tmp += a[index % size];
			index += CACHE_LINE_SIZE * 11;
		}
		auto dur = high_resolution_clock::now() - start;
		cout << "SIZE - " << size / (1024 * 1024) << "M, ";
		cout << "Time - " << duration_cast<milliseconds>(dur).count() << " msec\n";
		free((void*)a);
	}
}