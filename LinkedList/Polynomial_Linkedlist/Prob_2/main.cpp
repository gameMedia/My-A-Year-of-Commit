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
	//	1. ���ο� ������ �Է¹޾� ������
	//	2. �����ڷῡ ����� ��� ������ ���
	//	3. ���� �̸����� �˻��Ͽ� �ش� ������ ��� �����.��, ã�����ϴ� �ܾ �̸��� �Ϻ���
	//	��쵵 �˻��Ͽ� �߷�
	//	4. ������ �̸����� �˻��Ͽ� ������.��, ���� �̸��� ��ġ�ϴ� ��츸 ����
	//	5. ���α׷��� ����

	card* NC = new card[SIZE];
	int menu_item = 0;
	int count = initCard(NC);
	bool bLoop = true;
	while (bLoop) {
		printf_menu();
		cin >> menu_item;
		switch (menu_item) {
		case 1:
			cout << "���� �Է�\n";
			cout << "---------------------\n";
			count = PushNewCard(NC, count);
			break;
		case 2:
			cout << "���� ���\n";
			cout << "---------------------\n";
			PrintCardDatas(NC, count);
			break;
		case 3:
			cout << "���� �˻�\n";
			cout << "---------------------\n";
			PrintCardData_ByWord(NC, count);
			break;
		case 4:
			cout << "���� ����\n";
			cout << "---------------------\n";
			count = DeleteCardData_ByName(NC, count);
			break;
		case 5:
			cout << "���α׷� ����\n";
			finalize(NC, count);
			bLoop = false;
			cout << "---------------------\n";
			break;
		default:
			cout << "�������� ����� �Է����ּ���\n";
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
	else // �� ������ ���ٸ�?
	{

	}
	return count;
}

void printf_menu()
{
	cout << "========== Name Card DBMS ==========" << endl;
	cout << "��ɾ �����ϼ���.\n";
	cout << "1. ���� �Է�\n";
	cout << "2. ��� ���� ���\n";
	cout << "3. ���� �˻�\n";
	cout << "4. ���� ����\n";
	cout << "5. ����\n";
	cout << "��� �Է� --- > ";
}

int PushNewCard(card* NC, int count)
{
	card PlusCard;
	string check;
	cout << "���� �Է�\n";
	cout << "-------------------------" << endl;
	cout << "�̸� : ";
	cin >> PlusCard.iName;
	cout << "ȸ�� : ";
	cin >> PlusCard.iCompany;
	cout << "��ȭ : ";
	cin >> PlusCard.iPhoneNumber;
	cout << "�����ұ�� < yes or no > ? :";
	cin >> check;
	if (check == "yes") {
		NC[count++] = PlusCard;
	}
	return count;
}

void PrintCardDatas(card* NC, int count)
{
	for (int i = 0; i < count; ++i) {
		cout << i << ". �̸�:" << NC[i].iName << ", ȸ��:" << NC[i].iCompany << ", ��ȭ:" << NC[i].iPhoneNumber << endl;
	}
	cout << count << "���� ������ ������" << endl;
}

void PrintCardData_ByWord(card* NC, int count)
{
	int kcount = 0;
	string name;
	cout << "���� �˻�\n";
	cout << "------------------" << endl;
	cout << "�˻��� �̸��� �Է��ϼ���. : ";
	cin >> name;
	for (int i = 0; i < count; ++i) {
		if (NC[i].iName.find(name) != string::npos) {
			cout << "�˻��� ���� �̸�:" << NC[i].iName << ", ȸ��:" << NC[i].iCompany << ", ��ȭ:" << NC[i].iPhoneNumber << endl;
			++kcount;
		}
	}
	cout << kcount << "���� ���� �˻���" << endl;
}

int DeleteCardData_ByName(card* NC, int count)
{
	int kcount = 0;
	int pastCount = count;
	string name;
	cout << "���� ����" << endl;
	cout << "--------------------------" << endl;
	cout << "������ �̸��� �Է��ϼ���.:";
	cin >> name;
	for (int i = 0; i < count; ++i) {
		if (NC[i].iName == name) {
			cout << "���� ���� �̸�:" << NC[i].iName << ", ȸ��:" << NC[i].iCompany << ", ��ȭ:" << NC[i].iPhoneNumber << endl;
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
	cout << kcount << "���� ���� ������" << endl;
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
