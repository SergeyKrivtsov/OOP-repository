/*
Виконати будь-яке завдання першого семестру на динамічні масиви та матриці з використанням операцій
виділення та звільнення пам'яті (new, delete) та потокового введення-виведення.
Бажано матриці взяти прямокутного розміру MxN
Приклад вхідних даних:
|1||4|   |1||2||1||2|   |9||6||9||6|
|2||5| x |2||1||2||1| = |12||9||12||9|
|3||6|                  |15||12||15||12|
Вхід:
3
2
2
4
1
1 2 3
4 5 6
1
1
1 2
2 1
1 2
2 1
1
Вихід:
|9||6||9||6|
|12||9||12||9|
|15||12||15||12|*/
#include <iostream>
#include <cstdlib>
using namespace std;
//Функція для створення матриці
int** Create_matrix(int columns, int rows) {
    int** matrix = new int*[columns];
    for (int i = 0; i < columns; i++) {
        matrix[i] = new int[columns];
    }
    return matrix;
}
//Функція для видалення матриці
void Free_Matrix(int** matrix, int columns) {
    for (int i = 0; i < columns; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}
//Функція для роздрукування матриці у консоль
void Print_matrix(int columns_matrix, int rows_matrix, int** matrix){
    cout << "Your matrix is: " << endl;
    for (int row = 0; row < rows_matrix; row++){
        for (int column = 0; column < columns_matrix; column++){
            cout << "|" << matrix[column][row] << "|";
        }
        cout << endl;
    }
    cout << endl;
}
//Функція для множення матриць
void Multiply_matrix(int columns_1, int rows_1, int** matrix_1, int columns_2, int rows_2, int** matrix_2, int** out){
    for (int column = 0; column < columns_2; column++) {
        for (int row = 0; row < rows_1; row++) {
            out[column][row] = 0;
            for (int c_1 = 0; c_1 < columns_1; c_1++) {
                out[column][row] += matrix_1[c_1][row] * matrix_2[column][c_1];
            }
        }
    }
}
//Функція для введення матриці (з випадковими значеннями або зі значеннями, які вводить користувач)
void Input_matrix(int columns_matrix, int rows_matrix, int** matrix){
    int Status = 0;
    do{
        cout << "-----------------------------------" << endl;
        cout << "What do you want to do?\n1 - Enter matrix\n2 - Enter random values for matrix" << endl;
        cout << "-----------------------------------" << endl;
        cin >> Status;
        switch(Status){
            case 1:
                for (int column = 0; column < columns_matrix; column++){
                    cout << "Enter column number " << column+1 << "(" << rows_matrix << " numbers):" << endl;
                    for (int row = 0; row < rows_matrix; row++){
                        cin >> matrix[column][row];
                    }
                }
                break;
            case 2:
                for (int column = 0; column < columns_matrix; column++){
                    for (int row = 0; row < rows_matrix; row++){
                        matrix[column][row] = rand() % 20;
                    }
                }
                break;
            default:
                Status = 0;
                cout << "-----------------------------------" << endl;
                cout << "Invalid input!" << endl;
                cout << "-----------------------------------" << endl;
                break;
        }
        cout << "-----------------------------------" << endl;
        cout << "Great!" << endl;
        Print_matrix(columns_matrix, rows_matrix, matrix);
        cout << "Do you want to enter it again?:(\n1 - No\nAny other - Yes" << endl;
        cout << "-----------------------------------" << endl;
        cin >> Status;
        if (Status != 1){
            Status = 0;
        }
    }while(Status == 0);
}
//Функція для введення розмірів матриці
void Input_parameters(int* rows_1, int* cols_1, int* rows_2, int* cols_2){
    do
    {
        cout << "Enter rows in first matrix:" << endl;
        cin >> *rows_1;
        cout << "Enter columns in first matrix:" << endl;
        cin >> *cols_1;
        cout << "Enter rows in second matrix:" << endl;
        cin >> *rows_2;
        cout << "Enter columns in second matrix:" << endl;
        cin >> *cols_2;
        if (*cols_1 != *rows_2){
            cout << "Invalid input! Cols in first matrix must be equal to rows in second!";
        } 
    } while (*cols_1 != *rows_2);
}
int main(){
    int rows_matrix_1, columns_matrix_1, rows_matrix_2, columns_matrix_2;
    Input_parameters(&rows_matrix_1, &columns_matrix_1, &rows_matrix_2, &columns_matrix_2);
    int **matrix_1 = Create_matrix(columns_matrix_1, rows_matrix_1);
    int **matrix_2 = Create_matrix(columns_matrix_2, rows_matrix_2);
    int **output = Create_matrix(columns_matrix_2, rows_matrix_1);
    Input_matrix(columns_matrix_1, rows_matrix_1, matrix_1);
    Input_matrix(columns_matrix_2, rows_matrix_2, matrix_2);
    Multiply_matrix(columns_matrix_1, rows_matrix_1, matrix_1, columns_matrix_2, rows_matrix_2, matrix_2, output);
    Print_matrix(columns_matrix_2, rows_matrix_1, output);
    Free_Matrix(matrix_1, columns_matrix_1);
    Free_Matrix(matrix_2, columns_matrix_2);
    Free_Matrix(output, columns_matrix_2);
}