#include <iostream>
#include <thread>
#include <vector>

using namespace std;



void thread_func(int myid)
{

	cout << "My thread ID : " << myid << endl;

}

int main()
{
	vector<thread> threads;
	
	for (int i = 0; i < 10; ++i) threads.emplace_back(thread_func,i);
	for (auto& th : threads) th.join();

}