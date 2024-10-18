#include<iostream>
#include <Windows.h>
#include <string>
using namespace std;

class Figure {
private:
	int l;
	int w;
	int h;
public:
	Figure(int l, int w, int h) {
		this->l = l;
		this->w = w;
		this->h = h;
	}
	int setL(int a) { this->l = a; }
	int setW(int b) { this->w = b; }
	int setH(int c) { this->h = c; }
	~Figure() {
	}
protected:
	int getL() { return l; }
	int getW() { return w; }
	int getH() { return h; }
};

class Osnova : public Figure {
public:
	Osnova(int l, int w, int h) : Figure(l, w, h) {}
	void fig_baseArea() {
		int S = Figure::getL() * Figure::getW();//Площа сторони паралелепіпеду
		cout << "Площа основи дорівнює = " << S << " см^3" << endl;
	}
	void print() {
		cout << "Ми маємо паралелепіпед зі сторонами " << getL() << " см, " << getW() << " см, " << getH() << " см. " << endl;
	}
};

class Obiem : public Figure {
public:
	Obiem(int l, int w, int h) : Figure(l, w, h) {}
	void fig_Vol() {
		int V = Figure::getL() * Figure::getW() * Figure::getH();//Об'єм кубу
		cout << "Об'єм нашого кубу дорівнює = " << V << " см^3" << endl;
	}
};
//Опис структури
struct fig {
	int a, b, c;
};
//Функція для створення фігури
fig createfig() {
	fig f;
	cout << "Введіть довжину: "; cin >> f.a;
	cout << "Введіть ширину: "; cin >> f.b;
	cout << "Введіть висоту: "; cin >> f.c;
	//cout << endl << f.a << f.b << f.c << endl; //Проверка
	return f;
}
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Добрий день. У цьому проекті я хочу показати свої навички використання мови С++. " << endl
		<< "На прикладі будемо розглядати створення класів, використання конструкторів, деструкторів," << endl
		<< "наслідування класів, створення структур, їх повернення через фукнцію." << endl
		<< "Створення маленької матриці для зрозуміння принципу роботи виділення даних." << endl << endl;
	system("pause"); cout << endl;
	cout << "Зараз я вас попрошу ввести дані 6-ти фігур." << endl << endl;
	int size_x = 2; //Кількість стовбців
	int size_y = 3; //Кількість елементів у стовпчиках
	fig** mas = new fig * [size_x]; //Створення матриці
	for (int i = 0; i < size_x; ++i) {
		mas[i] = new fig[size_y];
	} //Виділення пам'яті під матрицю
	// Приблизний вигляд нашої матриці
	// [0,0][0,1][0,2]
	// [1,0][1,1][1,2]
	for (size_t i = 0; i < size_x; i++)
	{
		for (size_t j = 0; j < size_y; j++)
		{
			string x = to_string(j + 1);
			if (i == 1) x = to_string(j + 4);
			cout << "Введіть дані для " << x << " - ої фігури" << endl;
			mas[i][j] = createfig();
			cout << endl;
		}
	} //Заповнення нашої матриці інформцією від користувача
	for (size_t i = 0; i < size_x; i++)
	{
		for (size_t j = 0; j < size_y; j++)
		{
			Osnova k(mas[i][j].a, mas[i][j].b, mas[i][j].c);
			k.print();
			k.fig_baseArea();
			Obiem ob(mas[i][j].a, mas[i][j].b, mas[i][j].c);
			ob.fig_Vol();
			cout << endl;
		}
	} //Створення об'єктів

	for (int i = 0; i < size_x; ++i) {
		delete[] mas[i];
	}
	delete [] mas; //Звільнення пам'яті

	system("pause");

	cout << endl << "Звісно цей проект не стосується професійного проекту. На ньому можно лише тільки подивитись як працює синтаксис" << endl
		<< "указателів на мові С++." << endl;
}
