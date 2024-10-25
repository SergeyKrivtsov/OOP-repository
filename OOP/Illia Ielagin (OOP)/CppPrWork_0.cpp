/*Множення матриць одна на другу*/

#include <iostream>
using namespace std;

void inputarr(int string, int column, int** arr);

void multiply(int string1, int column1, int column2, int** arr1, int** arr2, int** mult_arr);

void output_multarr(int string1, int column2, int** mult_arr);

int main() {
    int row1, col1, row2, col2;

    cout << "Enter the number of rows of the first matrix." << endl;
    cin >> row1;
    cout << "Enter the number of columns of the first matrix." << endl;
    cin >> col1;

    cout << "Enter the number of rows of the second matrix." << endl;
    cin >> row2;
    cout << "Enter the number of columns of the second matrix." << endl;
    cin >> col2;

    if (col1 != row2) {
        cout << "Your matrices cannot be multiplied." << endl;
        return 1;
    }

    int** arr1 = new int* [row1];
    int** arr2 = new int* [row2];

    inputarr(row1, col1, arr1);
    inputarr(row2, col2, arr2);

    int** mult_arr = new int* [row1];
    for (int i = 0; i < row1; i++) {
        mult_arr[i] = new int[col2];
    }

    multiply(row1, col1, col2, arr1, arr2, mult_arr);

    output_multarr(row1, col2, mult_arr);

    for (int i = 0; i < row1; i++) {
        delete[] arr1[i];
    }
    delete[] arr1;

    for (int i = 0; i < row2; i++) {
        delete[] arr2[i];
    }
    delete[] arr2;

    for (int i = 0; i < row1; i++) {
        delete[] mult_arr[i];
    }
    delete[] mult_arr;

    return 0;
}

void inputarr(int row, int col, int** arr) {
    for (int i = 0; i < row; i++) {
        arr[i] = new int[col];
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << "Enter a value for " << i << " element of a row " << j << " column." << endl;
            cin >> arr[i][j];
        }
    }
}

void multiply(int row1, int col1, int col2, int** arr1, int** arr2, int** mult_arr) {
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col2; j++) {
            mult_arr[i][j] = 0;
            for (int k = 0; k < col1; k++) {
                mult_arr[i][j] += arr1[i][k] * arr2[k][j];
            }
        }
    }
}

void output_multarr(int row1, int col2, int** mult_arr) {
    cout << "Multiplication result." << endl;

    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col2; j++) {
            cout << mult_arr[i][j] << " ";
        }
        cout << endl;
    }
}