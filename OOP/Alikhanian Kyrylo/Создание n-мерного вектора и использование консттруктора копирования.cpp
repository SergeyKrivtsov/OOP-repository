#include <iostream>
#include <vector>
#include <algorithm> // Для std::sort
#include <Windows.h>
#include <cmath> 
#include <list>

using namespace std;

class vectorik {
	int *koordstart;
	int *koordend;
	int vimirnist = 0;
public:
	vectorik(int vimirnist) {
		this->koordstart = new int[vimirnist];
		this->koordend = new int[vimirnist];
		this->vimirnist = vimirnist;
	}
	vectorik(vectorik const& v) {
		cout << "constructor copy" << endl;
		this->koordstart = new int[v.vimirnist];
		this->koordend = new int[v.vimirnist];
		for (size_t i = 0; i < v.vimirnist; i++)
		{
			this->koordstart[i] = v.koordstart[i];
			this->koordend[i] = v.koordend[i];
		}
		this->vimirnist = v.vimirnist;
	}
	/*template<typename... Args>
	int fulling(Args... args) {	}*/
	void fulling() {
		int a, b;
		for (size_t i = 0; i < vimirnist; i++)
		{
			cout << "Введіть початкову координату: "; cin >> a;
			koordstart[i] = a;
		}
		for (size_t i = 0; i < vimirnist; i++)
		{
			cout << "Введіть кінцеву координату: "; cin >> b;
			koordend[i] = b;
		}
		cout << "Вектор був заповнений" << endl;
	}
	int length_of_vector() {
		int sum = 0;
		for (size_t i = 0; i < vimirnist; i++)
		{
			sum += pow((koordend[i]-koordstart[i]), 2);
		}
		return sqrt(sum);
	}
	int *getKoordstart() { return koordstart; }
	int *getKoordend() { return koordend; }
	int getVimirnist() { return vimirnist; }
	~vectorik() {
		delete[] koordstart;
		delete[] koordend;
	}
};
//Зовнішня функція для рахування довжини вектору
int length_of_any_vector(vectorik a) {
	return a.length_of_vector();
}
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	vectorik a(4);
	a.fulling();
	for (size_t i = 0; i < 4; i++)
	{
		cout << "Початкова координата: " << a.getKoordstart()[i] << "\tВідповідна кінцева: " << a.getKoordend()[i] << endl;
	}
	cout << "Length : " << length_of_any_vector(a) << endl;
	for (size_t i = 0; i < 4; i++)
	{
		cout << "Початкова координата: " << a.getKoordstart()[i] << "\tВідповідна кінцева: " << a.getKoordend()[i] << endl;
	}
	/*SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int vimir = 1, kilkist = 1;
	cout << "Введіть вимірність для усіх наших векторів (за замовчуванням вимірність дорівнює 1): "; cin >> vimir;
	cout << "Введіть кількість наших векторів (за замовчуванням кількість дорівнює 1): "; cin >> kilkist;
	list<vectorik> arr;
	for (size_t i = 0; i < kilkist; i++)
	{
		cout << "Заповнення " << i+1 << "-го вектору: " << endl;
		vectorik a(vimir);
		a.fulling();
		arr.push_back(a);
	}
	cout << "\nЗараз ми маємо список векторів, який виглядає наступним чином: " << endl;
	int it = 0;
	for (vectorik j : arr)
	{
		cout << it + 1 <<"-ий вектор: " << endl;
		for (size_t i = 0; i < vimir; i++)
		{
			cout << "Початкова координата: " << j.getKoordstart()[i] << "\tВідповідна кінцева: " << j.getKoordend()[i] << endl;
		}
		it++;
	}
	int key = 99; it = 0;
	cout << "\nВи попали у меню керування векторами.\n";
	while (key != 0) {
		cout << "\nНатисніть 1, якщо бажаєте вивести довжину усіх векторів." 
		<< "\nНатисніть 2, для перевірки зовнішньої функції на визначення довжини першого вектору"
		<< "\nНатисніть 0 для того щоб завершити програму."
		<< endl;
		cin >> key;
		switch (key) {
		case 1:
			for (vectorik j : arr)
			{
				cout << "Довжина " << it + 1 << "-го вектору дорівнює " << j.length_of_vector() << endl;
				it++;
 			}
			break;
		case 2:
			cout << "На данному прикладі ми визначемо довжину першого вектору з нашого списку, використовуючи зовнішню фукнцію: " << endl;
			cout << "Довжина першого вектору дорівнює: " << length_of_any_vector(arr.front()) << endl;
			break;
		case 0:
			break;
		default:
			break;
		}
		cout << endl;
	};
	//cout << "Длина вектора: " << vectorchik.length_of_vector() << endl;*/
	return 0;
}
