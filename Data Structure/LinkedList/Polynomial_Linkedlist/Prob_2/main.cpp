#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define SIZE 1000

typedef struct nameCard
{
	string iName;
	string iCompany;
	int iPhoneNumber;
}card;

int initCard(card* NC);
void printf_menu();
int PushNewCard(card* NC, int count);
void PrintCardDatas(card* NC, int count);
void PrintCardData_ByWord(card* NC, int count);
int DeleteCardData_ByName(card* NC, int count);
void finalize(card* NC, int _count);

int main() {
	//	1. 새로운 명함을 입력받아 저장함
	//	2. 명함자료에 저장된 모든 명함을 출력
	//	3. 명함 이름으로 검색하여 해당 정보를 모두 출력함.단, 찾고자하는 단어가 이름의 일부인
	//	경우도 검색하여 추력
	//	4. 명함을 이름으로 검색하여 삭제함.단, 명함 이름과 일치하는 경우만 삭제
	//	5. 프로그램을 종료

	card* NC = new card[SIZE];
	int menu_item = 0;
	int count = initCard(NC);
	bool bLoop = true;
	while (bLoop) {
		printf_menu();
		cin >> menu_item;
		switch (menu_item) {
		case 1:
			cout << "명함 입력\n";
			cout << "---------------------\n";
			count = PushNewCard(NC, count);
			break;
		case 2:
			cout << "명함 출력\n";
			cout << "---------------------\n";
			PrintCardDatas(NC, count);
			break;
		case 3:
			cout << "명함 검색\n";
			cout << "---------------------\n";
			PrintCardData_ByWord(NC, count);
			break;
		case 4:
			cout << "명함 삭제\n";
			cout << "---------------------\n";
			count = DeleteCardData_ByName(NC, count);
			break;
		case 5:
			cout << "프로그램 종료\n";
			finalize(NC, count);
			bLoop = false;
			cout << "---------------------\n";
			break;
		default:
			cout << "정상적인 명령을 입력해주세요\n";
			break;
		}
		cout << "\n";
	}

	delete[] NC;

}

card _Card[SIZE];
int initCard(card* NC)
{


	for (int i = 0; i < SIZE; ++i) {
		NC[i].iCompany = "";
		NC[i].iName = "";
		NC[i].iPhoneNumber = 0;
	}
	string name;
	string company;
	int phone;
	int count = 0;
	ifstream filein("namecard.txt");
	if (filein)
	{
		while (!filein.eof()) {

			filein >> name;
			filein >> company;
			filein >> phone;
			_Card[count].iName = name;
			_Card[count].iCompany = company;
			_Card[count].iPhoneNumber = phone;
			++count;
		}
		for (int i = 0; i < count; ++i) {
			NC[i].iName = _Card[i].iName;
			NC[i].iCompany = _Card[i].iCompany;
			NC[i].iPhoneNumber = _Card[i].iPhoneNumber;
		}
	}
	else // 열 파일이 없다면?
	{

	}
	return count;
}

void printf_menu()
{
	cout << "========== Name Card DBMS ==========" << endl;
	cout << "명령어를 선택하세요.\n";
	cout << "1. 명함 입력\n";
	cout << "2. 모든 명함 출력\n";
	cout << "3. 명함 검색\n";
	cout << "4. 명함 삭제\n";
	cout << "5. 종료\n";
	cout << "명령 입력 --- > ";
}

int PushNewCard(card* NC, int count)
{
	card PlusCard;
	string check;
	cout << "명함 입력\n";
	cout << "-------------------------" << endl;
	cout << "이름 : ";
	cin >> PlusCard.iName;
	cout << "회사 : ";
	cin >> PlusCard.iCompany;
	cout << "전화 : ";
	cin >> PlusCard.iPhoneNumber;
	cout << "저장할까요 < yes or no > ? :";
	cin >> check;
	if (check == "yes") {
		NC[count++] = PlusCard;
	}
	return count;
}

void PrintCardDatas(card* NC, int count)
{
	for (int i = 0; i < count; ++i) {
		cout << i << ". 이름:" << NC[i].iName << ", 회사:" << NC[i].iCompany << ", 전화:" << NC[i].iPhoneNumber << endl;
	}
	cout << count << "개의 명함이 존재함" << endl;
}

void PrintCardData_ByWord(card* NC, int count)
{
	int kcount = 0;
	string name;
	cout << "명함 검색\n";
	cout << "------------------" << endl;
	cout << "검색할 이름을 입력하세요. : ";
	cin >> name;
	for (int i = 0; i < count; ++i) {
		if (NC[i].iName.find(name) != string::npos) {
			cout << "검색한 명함 이름:" << NC[i].iName << ", 회사:" << NC[i].iCompany << ", 전화:" << NC[i].iPhoneNumber << endl;
			++kcount;
		}
	}
	cout << kcount << "개의 명함 검색함" << endl;
}

int DeleteCardData_ByName(card* NC, int count)
{
	int kcount = 0;
	int pastCount = count;
	string name;
	cout << "명함 삭제" << endl;
	cout << "--------------------------" << endl;
	cout << "삭제할 이름을 입력하세요.:";
	cin >> name;
	for (int i = 0; i < count; ++i) {
		if (NC[i].iName == name) {
			cout << "삭제 명함 이름:" << NC[i].iName << ", 회사:" << NC[i].iCompany << ", 전화:" << NC[i].iPhoneNumber << endl;
			NC[i].iName = "";
			++kcount;
			for (int i = 0; i < pastCount; ++i) {
				if (NC[i].iName == "") {
					NC[i].iName = NC[i + 1].iName;
					NC[i].iCompany = NC[i + 1].iCompany;
					NC[i].iPhoneNumber = NC[i + 1].iPhoneNumber;
				}
			}
			pastCount -= 1;
		}
	}
	cout << kcount << "개의 명함 삭제함" << endl;
	return pastCount;
}

void finalize(card* NC, int _count)
{
	for (int i = 0; i < _count; ++i) {
		_Card[i].iName = NC[i].iName;
		_Card[i].iCompany = NC[i].iCompany;
		_Card[i].iPhoneNumber = NC[i].iPhoneNumber;
	}

	ofstream out("namecard.txt");


	string Name = "";
	string Company = "";
	int iPhone = 0;
	for (int i = 0; i < _count; ++i) {
		Name = _Card[i].iName;
		Company = _Card[i].iCompany;
		iPhone = _Card[i].iPhoneNumber;

		out << Name;
		out << " ";
		out << Company;
		out << " ";
		out << iPhone;
		if (i == _count - 1)
			out.eof();
		else
			out << " ";
	}


}
