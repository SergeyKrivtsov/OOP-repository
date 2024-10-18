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
		int S = Figure::getL() * Figure::getW();//����� ������� �������������
		cout << "����� ������ ������� = " << S << " ��^3" << endl;
	}
	void print() {
		cout << "�� ���� ������������ � ��������� " << getL() << " ��, " << getW() << " ��, " << getH() << " ��. " << endl;
	}
};

class Obiem : public Figure {
public:
	Obiem(int l, int w, int h) : Figure(l, w, h) {}
	void fig_Vol() {
		int V = Figure::getL() * Figure::getW() * Figure::getH();//��'�� ����
		cout << "��'�� ������ ���� ������� = " << V << " ��^3" << endl;
	}
};
//���� ���������
struct fig {
	int a, b, c;
};
//������� ��� ��������� ������
fig createfig() {
	fig f;
	cout << "������ �������: "; cin >> f.a;
	cout << "������ ������: "; cin >> f.b;
	cout << "������ ������: "; cin >> f.c;
	//cout << endl << f.a << f.b << f.c << endl; //��������
	return f;
}
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "������ ����. � ����� ������ � ���� �������� ��� ������� ������������ ���� �++. " << endl
		<< "�� ������� ������ ���������� ��������� �����, ������������ ������������, �����������," << endl
		<< "����������� �����, ��������� ��������, �� ���������� ����� �������." << endl
		<< "��������� �������� ������� ��� ��������� �������� ������ �������� �����." << endl << endl;
	system("pause"); cout << endl;
	cout << "����� � ��� ������� ������ ��� 6-�� �����." << endl << endl;
	int size_x = 2; //ʳ������ ��������
	int size_y = 3; //ʳ������ �������� � ����������
	fig** mas = new fig * [size_x]; //��������� �������
	for (int i = 0; i < size_x; ++i) {
		mas[i] = new fig[size_y];
	} //�������� ���'�� �� �������
	// ���������� ������ ���� �������
	// [0,0][0,1][0,2]
	// [1,0][1,1][1,2]
	for (size_t i = 0; i < size_x; i++)
	{
		for (size_t j = 0; j < size_y; j++)
		{
			string x = to_string(j + 1);
			if (i == 1) x = to_string(j + 4);
			cout << "������ ��� ��� " << x << " - � ������" << endl;
			mas[i][j] = createfig();
			cout << endl;
		}
	} //���������� ���� ������� ���������� �� �����������
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
	} //��������� ��'����

	for (int i = 0; i < size_x; ++i) {
		delete[] mas[i];
	}
	delete [] mas; //��������� ���'��

	system("pause");

	cout << endl << "����� ��� ������ �� ��������� ����������� �������. �� ����� ����� ���� ����� ���������� �� ������ ���������" << endl
		<< "��������� �� ��� �++." << endl;
}
