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
		int		iSize; // 4 ����Ʈ
		float	fSize;
		double	dSize;
		char	chSize;
	}SIZE;
	
	cout << sizeof(SIZE) << endl;

	typedef struct tageSize2
	{
		int		iSize; // 4 ����Ʈ
		float	fSize; // 4 ����Ʈ
		char	chSize; // 1 ����Ʈ
	}SIZE2;

	cout << sizeof(SIZE2) << endl; // 12����Ʈ

	typedef struct tageSize3
	{
		int		iSize; // 4 ����Ʈ
		float	fSize; // 4 ����Ʈ
		char	chSize; // 1 ����Ʈ
		char	chSize2; // 1 ����Ʈ
		char	chSize3; // 1 ����Ʈ
	}SIZE3;

	cout << sizeof(SIZE3) << endl; // 12����Ʈ

	//Data user01 = 21;
	//Data user02(33, "�̼���", 20000);
	//Data user03{ 33, "�̼���", 20000 };
	//Data user04{ 33, "�̼���", 20000 };
	//Data user05();
}