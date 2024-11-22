#include <iostream>

using namespace std;

// Функція для динамічного виділення пам'яті
int** createMatrix(int n) {
    int** matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }
    return matrix;
}

// Функція для введення елем. матриці
void inputMatrix(int** matrix, int n) {
    cout << "Enter elements of matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }
}

// Функція для обробки матриці (обнулення елем., крім трикутника)
void triangleInMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Умова для залишення елементів у "трикутнику"
            if (!((i == 0 && j == n-1) || (i == 1 && j >= n-2) || (i == 2 && j == n-1))) {
                matrix[i][j] = 0;
            }
        }
    }
}

// Функція для виведення матриці
void printMatrix(int** matrix, int n) {
    cout << "Matrix after:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Функція для звільнення виділеної пам'яті
void freeMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
    int n;
    cout << "Size n of matrix (n x n): ";
    cin >> n;

    // Створення матриці
    int **matrix = createMatrix(n);
    // Введення елем.
    inputMatrix(matrix, n);
    // Обробка
    triangleInMatrix(matrix, n);
    // Виведення після обробки
    printMatrix(matrix, n);
    // Звільнення виділеної пам'яті
    freeMatrix(matrix, n);

    return 0;
}