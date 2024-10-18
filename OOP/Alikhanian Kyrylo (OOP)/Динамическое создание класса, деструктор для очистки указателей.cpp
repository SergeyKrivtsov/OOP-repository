#include <iostream>
#include <Windows.h>

using namespace std;

//class Student {
//	string name;
//	int year;
//public://Конструктор никогда ничего не возвращает
//	Student(string n, int y) {
//
//	}
//	~Student()
//	{
//
//	};
//	void Print() {
//		
//	};
//};

class Pryamougolnik {
	int* a = new int;
	int* b = new int;
public:
	Pryamougolnik(int x, int y) {
		*this->a = x;
		*this->b = y;
	}
	Pryamougolnik() {

	}
	void print(int z) {
		cout << "Була створена фігура прямокутника. Його сторони дорівнюють: " << *a << " та " << *b << " см відповідно." << endl;
		switch (z) {
		case 1: cout << "Площа нашого прямокутника дорівнює: " << count_Square() << " см^2. " << endl; break;
		case 2: cout << "Периметр нашого прямокутника дорівнює: " << count_Perimetr() << " см. " << endl; break;
		default: break;
		}

	}
	void print() {
		cout << "Була створена фігура прямокутника. Його сторони дорівнюють: " << *a << " та " << *b << " см відповідно." << endl;
	}
	//Если 1 то выводит площадь, 2 - периметр
	
	int count_Square() { return (*a) * (*b); }
	int count_Perimetr() { return 2 * (*a + *b); }
	~Pryamougolnik() {
		delete a;
		delete b;
	}
	void setA(int x) { *this->a = x; }
	void setB(int y) { *this->b = y; }
	int getA() { return* a; }
	int getB() { return* b; }
};

class Paralelogram : public Pryamougolnik {
	int h = 0;
public:
	Paralelogram(int a, int b, int ha) {
		setA(a);
		setB(b);
		this->h = ha;
	}
	Paralelogram() {

	}
	int count_Square() { return getA() * h; }
	void print() {
		cout << "Площа нашого паралелограму дорівнює: " << count_Square() << " см^2. " << endl;
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	/*cout << "Була створена фігура прямокутника. Введіть будь-ласка довжину та ширину прямокутника. " << endl;
	cout << "Введіть сторону a: "; cin >> a;
	cout << "Введіть сторону b: "; cin >> b;*/
	/*Paralelogram par(5,6);
	par.print();*/
	int len = 10;
	//Pryamougolnik *arrchik {new Pryamougolnik[len]};
	Paralelogram *par = new Paralelogram(2, 5, 6);
	par->count_Square();
	par->Pryamougolnik::print(1);
	par->count_Square();
	par->print();
	delete par;
	//cout << par.count_Perimetr();
	/*for (size_t i = 0; i < len; i++)
	{
		arrchik[i]()
		arrchik[i].setA(i * 23 % 4);
		arrchik[i].setB()
	}*/
}
