#include <iostream>

using namespace std;

struct Data {
	int age;
	char name[100];
	int balance;
};

int main()
{
	typedef struct tageSize
	{
		int		iSize; // 4 바이트
		float	fSize;
		double	dSize;
		char	chSize;
	}SIZE;
	
	cout << sizeof(SIZE) << endl;

	typedef struct tageSize2
	{
		int		iSize; // 4 바이트
		float	fSize; // 4 바이트
		char	chSize; // 1 바이트
	}SIZE2;

	cout << sizeof(SIZE2) << endl; // 12바이트

	typedef struct tageSize3
	{
		int		iSize; // 4 바이트
		float	fSize; // 4 바이트
		char	chSize; // 1 바이트
		char	chSize2; // 1 바이트
		char	chSize3; // 1 바이트
	}SIZE3;

	cout << sizeof(SIZE3) << endl; // 12바이트

	//Data user01 = 21;
	//Data user02(33, "이순신", 20000);
	//Data user03{ 33, "이순신", 20000 };
	//Data user04{ 33, "이순신", 20000 };
	//Data user05();
}