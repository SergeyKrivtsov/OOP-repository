#include <iostream>
#include <Windows.h>

using namespace std;

void printlist(int** mas, int razm) {
	for (size_t i = 0; i < razm; i++)
	{
		for (size_t j = 0; j < razm; j++) cout << mas[i][j];
		cout << endl;
	}
}

void printTreugolnik(int** mas, int razm) {
	int additional_counter = razm - 1;
	int letzt = razm - 1;
	int mitte = (razm / 2) + 0.5;
	//cout << "Mitte = " << mitte << endl;
	for (size_t i = 0; i < razm; i++)
	{
		for (size_t j = 0; j < razm; j++)
		{
			if (j >= (additional_counter) && j != letzt)
				cout << mas[i][j];
			else if (j == letzt)
				cout << mas[i][j];
			else
				cout << " ";
		}
		if (i >= mitte)
			additional_counter += 1;
		else
			additional_counter -= 1;

		cout << endl;
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int razm = 5;
	cout << "Введите размер матрицы: "; cin >> razm;
	int** mas = new int* [razm];
	for (size_t i = 0; i < razm; i++) {
		mas[i] = new int[razm];
		for (size_t j = 0; j < razm; j++)
		{
			mas[i][j] = 1;
		}
	}
	//printlist(mas, razm);
	cout << endl << endl;
	printTreugolnik(mas, razm);
	for (size_t i = 0; i < razm; i++)
	{
		delete mas[i];
	}
	delete[] mas;
}