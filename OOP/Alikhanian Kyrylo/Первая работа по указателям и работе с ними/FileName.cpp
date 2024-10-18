#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;
int cols, rows;

void delete_Array(int** mas) {
    for (int i = 0; i < rows; ++i) {
        delete[] mas[i];
    }
    delete[] mas;
}

int** create_Array() {
    int** mas = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        mas[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            mas[i][j] = rand() % 100;

        }
    }
    return mas;
}

void print_Array(int** mas) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << setw(4) << mas[i][j];
        }
        cout << endl;
    }
}

void set_rangeArray() {
    cout << "Set Cols "; cin >> cols;
    cout << "Set rows "; cin >> rows;
}

int main()
{
    set_rangeArray();
    int** masiv = create_Array();
    print_Array(masiv);
    delete_Array(masiv);
    return 0;
}