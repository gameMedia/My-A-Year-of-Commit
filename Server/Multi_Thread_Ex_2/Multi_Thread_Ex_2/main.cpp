#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;
using namespace chrono;

constexpr int LOOP = 50'000'000;
constexpr int MAX_THREADS = 32;

// 컴파일러가 너무 똑똑해서 실행속도가 말도 안되게 측정된다.
volatile int sum = 0;
mutex ml;

void worker(int num_threads)
{
	volatile int local_sum = 0;
	for (int i = 0; i < LOOP / num_threads; ++i)
	{
		local_sum = local_sum + 2;

	}
	ml.lock();
	sum = sum + local_sum;
	ml.unlock();
}

int main()
{
	for (int nt = 1; nt <= MAX_THREADS; nt *= 2) {
		vector<thread> workers;
		sum = 0;
		auto start_time = high_resolution_clock::now();

		for (int i = 0; i < nt; ++i) workers.emplace_back(worker, nt);
		for (auto& th : workers) th.join();

		auto end_time = high_resolution_clock::now();
		auto duration = end_time - start_time;

		cout << nt << "Threads, " << "Sum : " << sum << endl;
		cout << "Time : " << duration_cast<milliseconds>(duration).count() << " msecs\n";
	}
}