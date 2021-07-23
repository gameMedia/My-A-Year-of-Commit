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
struct alignedint {
	alignas(64) volatile int sum;
};
alignedint sums[MAX_THREADS];
mutex ml;

void worker(int num_threads, int thread_id)
{
	
	for (int i = 0; i < LOOP / num_threads; ++i)
	{
		// Data Race를 Local 변수로 작업하고 
		sums[thread_id].sum = sums[thread_id].sum + 2;
	}

}

int main()
{
	for (int nt = 1; nt <= MAX_THREADS; nt *= 2) {
		vector<thread> workers;
		sum = 0;
		for (auto& s : sums)
			s.sum = 0;
		auto start_time = high_resolution_clock::now();

		for (int i = 0; i < nt; ++i) workers.emplace_back(worker, nt,i);
		for (auto& th : workers) th.join();
		for (auto s : sums) sum = sum + s.sum;

		auto end_time = high_resolution_clock::now();
		auto duration = end_time - start_time;

		cout << nt << "Threads, " << "Sum : " << sum << endl;
		cout << "Time : " << duration_cast<milliseconds>(duration).count() << " msecs\n";
	}
}