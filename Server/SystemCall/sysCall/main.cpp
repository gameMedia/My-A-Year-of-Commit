#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace chrono;

#define Ten_Thousand 10'000'000

int main()
{
	volatile long long temp = 0;
	auto start = high_resolution_clock::now();

	for (int i = 0; i < Ten_Thousand; ++i) {
		temp += i;
		this_thread::yield();
	}

	auto duration = high_resolution_clock::now() - start;
	cout << "Time - " << duration_cast<milliseconds>(duration).count() << " msec\n";
	cout << "Result - " << temp << endl;
}