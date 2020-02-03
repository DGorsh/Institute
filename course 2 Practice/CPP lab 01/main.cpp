/* ����� ���������� ���������� ���������:
1. ��������� ���������.
2. �������� ��������� � ��������� ������� � ������ ��������. ��� ��� ��������� �������������, �� ��� ������������� �������� �����
"������" � ��� ������ (������ - ������ (1, 6, 5, 3, 1, 3) ������ (1, 1, 3, 3, 5, 6)
*/

#include <string>
#include <iostream>
#include <locale>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>

using namespace std;
char textout;
unsigned int r_time;
bool listread = false;

template <typename T>
T random(T min, T max) {
	return min + rand() % (max + 1 - min);
}

float frandom(float min, float max) {
	return min + (float)rand() / (max + 1 - min);
}


template <template<typename, typename> class C, typename T>
int SearchCollect(const C<T, allocator<T>> &vec, static const  int num) {
	int UsedValue = 0, pov = 0;
	bool status = false;
	bool Unique = true;
	int UElem = 0;
	if (textout && !listread) cout << endl << "���������� ���������:" << endl;
	for (auto i = vec.begin(); i != vec.end(); ++i) {
		//��������� �������
		if (i == prev(vec.end())) status = true;
		switch (status) {
		case true:
			if (*i == *(prev(i))) {
				Unique = false;
				if (UsedValue == 0) {
					if (textout && !listread) cout << *i << ' ';
					UsedValue = 1;
					UElem++;
				}
				else pov++;
			}
			else {
				if (UsedValue == 0) {
					if (textout && !listread) cout << *i << ' ';
					UElem++;
				}
				else UsedValue = 0;
			}
			break;
		//��� ���������
		default:
			if (*i == *(next(i))) {
				Unique = false;
				if (UsedValue == 0) {
					if (textout && !listread) cout << *i << ' ';
					UsedValue = 1;
					UElem++;
				}
				else pov++;
			}
			else {
				if (UsedValue == 0) {
					if (textout && !listread) cout << *i << ' ';
					UElem++;
				}
				else UsedValue = 0;
			}
			break;
		}
	}
	if (Unique) {
		if (!listread)
		cout << endl << "�������� ���! ���! ������ ���� �������-�� ��������� �� ���������� ��-�� �����, � ������ �� ������� ��������! (��, ��������)" << endl;
	}
	else {
		if (!listread)
			cout << endl << "������! ����� ��������, ���� ��������� � ����� �������! � ������ ��-�� ��� ����� � ������� ����� �� ����� ��������..." << endl;
	}
	r_time = clock() - r_time;
	if (!listread)
	cout << "��������� � ���������� ��������� = " << UElem << endl;
	if (!listread)
	cout << "����� ���������� ��������� (������) = " << (double)r_time / ((double)CLOCKS_PER_SEC) << " �." << endl;
	else
		cout << "����� ���������� ��������� (����) = " << (double)r_time / ((double)CLOCKS_PER_SEC) << " �." << endl;
	return pov;
}

int main() {
	srand(time(0));
	int ElemNum, Ret;
	char ch, tx;
	setlocale(LC_ALL, "Russian");
	cout << "����� �������� ������������ �������� ���� � ������ ����� �����? ������� ������ � ���������� ������ �� �������������� �������: \'i\' = int, \'c\' = char, \'f\' = float, \'s\' = string" << endl;
	cout << "������� ���� -> ";
	cin >> ch;
	cout << "������� ���������� ���������, ������� ��� ������ ���������: " << endl;
	cout << "������� ��� -> ";
	cin >> ElemNum;
	cout << "������� �� ��������������� ��������?" << endl << "\'y\' - ��      \'n\' - ���" << endl;
	cin >> tx;
	switch (tx) {
	case 'y': textout = true; break;
	case 'n': textout = false; break;
	default:
		cout << "���� ��������, ��� ���-�� �� ����� �� ���";
		exit(1);
	}
	switch (ch) {
		case 'i': {
			vector<int> ElementData(ElemNum);
			list<int> ListData(0);
			if (textout) cout << "��������� ���� �����:" << endl;
			for (auto i = 0; i < ElementData.size(); i++) {
				ElementData[i] = random(-5000, 5000);
				ListData.push_back(ElementData[i]);
				if (textout) cout << ElementData[i] << ' ';
			}
			r_time = clock();
			sort(ElementData.begin(), ElementData.end());
			Ret = SearchCollect(ElementData, ElemNum);
			listread = true;
			r_time = clock();
			ListData.sort();
			Ret = SearchCollect(ListData, ElemNum);
			cout << "���������� ���������� = " << Ret;
			break;
		}
		case 'c': {
			vector<char> ElementData(ElemNum);
			list<char> ListData(0);
			if (textout) cout << "��������� �������:" << endl;
			for (auto i = 0; i < ElementData.size(); i++) {
				ElementData[i] = random('a', 'z');
				ListData.push_back(ElementData[i]);
				if (textout) cout << ElementData[i] << ' ';
			}
			r_time = clock();
			sort(ElementData.begin(), ElementData.end());
			Ret = SearchCollect(ElementData, ElemNum);
			listread = true;
			r_time = clock();
			ListData.sort();
			Ret = SearchCollect(ListData, ElemNum);
			cout << "���������� ���������� = " << Ret;
			break;
		}
		case 's': {
			int NumElem;
			vector<string> ElementData(ElemNum);
			list<string> ListData(0);
			if (textout) cout << "���� ���� ������. ����������� ������:" << endl;
			for (int i = 0; i < ElemNum; i++) {
				string teststr = "";
				NumElem = random(1, ElemNum);
				for (int j = 0; j < NumElem; j++)
					teststr += random('a', 'z');
				ElementData[i] = teststr;
				ListData.push_back(ElementData[i]);
				if (textout) cout << ElementData[i] << ' ';
			}
			r_time = clock();
			sort(ElementData.begin(), ElementData.end());
			Ret = SearchCollect(ElementData, ElemNum);
			listread = true;
			r_time = clock();
			ListData.sort();
			Ret = SearchCollect(ListData, ElemNum);
			cout << "���������� ���������� = " << Ret;
			break;
		}
		case 'f': {
			vector<float> ElementData(ElemNum);
			list<float> ListData(0);
			if (textout) cout << "������������ ���������:" << endl;
			for (auto i = 0; i < ElementData.size(); i++) {
				ElementData[i] = frandom(-10.0, 30.0);
				ListData.push_back(ElementData[i]);
				if (textout) cout << ElementData[i] << ' ';
			}
			r_time = clock();
			sort(ElementData.begin(), ElementData.end());
			Ret = SearchCollect(ElementData, ElemNum);
			listread = true;
			r_time = clock();
			ListData.sort();
			Ret = SearchCollect(ListData, ElemNum);
			cout << "���������� ���������� = " << Ret;
			break;
		}
		default: {
			cout << "���� �� �����!";
		}
	}
	cin >> ElemNum;
}