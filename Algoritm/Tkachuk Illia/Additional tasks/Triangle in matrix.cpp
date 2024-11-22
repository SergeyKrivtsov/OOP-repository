#include <iostream>
using namespace std;

int main() {
    int n;
    
    cout<<"Enter the matrix size: ";
    cin>> n;

    int** matrix = new int*[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {

            if (j > n -2 - i && j> i-1 ) {
                matrix[i][j] = 1;
            } else {
                matrix[i][j] = 0;
            }
        }
    }

    cout << "Matrix:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}