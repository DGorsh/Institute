/* метод нахождения уникальных элементов:
1. Сортируем коллекцию.
2. Проходим коллекцию и проверяем смежные с каждым элементы. Так как коллекция отсортирована, то все повторяющиеся элементы будут
"лежать" в ней подряд (пример - вектор (1, 6, 5, 3, 1, 3) станет (1, 1, 3, 3, 5, 6)
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
	if (textout && !listread) cout << endl << "Уникальная коллекция:" << endl;
	for (auto i = vec.begin(); i != vec.end(); ++i) {
		//последний элемент
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
		//все остальные
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
		cout << endl << "Повторов нет! Ура! Теперь Саша наконец-то избавился от комплексов из-за Влада, и теперь он реально счастлив! (ну, наверное)" << endl;
	}
	else {
		if (!listread)
			cout << endl << "Кошмар! После перебора, Саша ужаснулся и нашел повторы! И теперь из-за его слета с катушек никто не сдаст практику..." << endl;
	}
	r_time = clock() - r_time;
	if (!listread)
	cout << "Элементов в уникальной коллекции = " << UElem << endl;
	if (!listread)
	cout << "Время выполнения алгоритма (вектор) = " << (double)r_time / ((double)CLOCKS_PER_SEC) << " с." << endl;
	else
		cout << "Время выполнения алгоритма (лист) = " << (double)r_time / ((double)CLOCKS_PER_SEC) << " с." << endl;
	return pov;
}

int main() {
	srand(time(0));
	int ElemNum, Ret;
	char ch, tx;
	setlocale(LC_ALL, "Russian");
	cout << "Какие элементы предпочитает собирать Саша в данное время суток? Введите символ в коммандную строку по установленному образцу: \'i\' = int, \'c\' = char, \'f\' = float, \'s\' = string" << endl;
	cout << "Вводить сюда -> ";
	cin >> ch;
	cout << "Введите количество элементов, которые уже собрал Александр: " << endl;
	cout << "Вводить тут -> ";
	cin >> ElemNum;
	cout << "Выводим ли сгенерированные элементы?" << endl << "\'y\' - да      \'n\' - нет" << endl;
	cin >> tx;
	switch (tx) {
	case 'y': textout = true; break;
	case 'n': textout = false; break;
	default:
		cout << "Саша негодует, ибо что-то вы ввели не так";
		exit(1);
	}
	switch (ch) {
		case 'i': {
			vector<int> ElementData(ElemNum);
			list<int> ListData(0);
			if (textout) cout << "Коллекция Саши чисел:" << endl;
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
			cout << "Количество повторений = " << Ret;
			break;
		}
		case 'c': {
			vector<char> ElementData(ElemNum);
			list<char> ListData(0);
			if (textout) cout << "Коллекция буковок:" << endl;
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
			cout << "Количество повторений = " << Ret;
			break;
		}
		case 's': {
			int NumElem;
			vector<string> ElementData(ElemNum);
			list<string> ListData(0);
			if (textout) cout << "Саша люби читать. Прочитанные строки:" << endl;
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
			cout << "Количество повторений = " << Ret;
			break;
		}
		case 'f': {
			vector<float> ElementData(ElemNum);
			list<float> ListData(0);
			if (textout) cout << "Рациональная коллекция:" << endl;
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
			cout << "Количество повторений = " << Ret;
			break;
		}
		default: {
			cout << "Ввод не верен!";
		}
	}
	cin >> ElemNum;
}