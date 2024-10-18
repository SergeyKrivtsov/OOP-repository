#include <iostream>

int to_binary(int number) {
    int multiplier = 1;
    int answer = 0;

    while (number != 0) {
        answer += (number % 2) * multiplier;
        number /= 2;
        multiplier *= 10;
    }

    return answer;
}

int count_ones(int binary) {
    int answer = 0;

    while (binary != 0) {
        if (binary % 10 == 1) {
            answer++;
        }
        binary /= 10;
    }

    return answer;
}

void sorting(int rows, int cols, int** array, int* ones) {
    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < rows - i - 1; j++) {
            if (ones[j] < ones[j + 1]) {
                std::swap(ones[j], ones[j + 1]);
                for (int k = 0; k < cols; k++) {
                    std::swap(array[j][k], array[j + 1][k]);
                }
            }
        }
    }
}

void printMatrix(int** array, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        std::cout << "Array " << i << ": [";
        for (int j = 0; j < cols; j++) {
            std::cout << array[i][j];
            if (j < cols - 1) {
                std::cout << ",";
            }
        }
        std::cout << "]\n";
    }
}

int menu() {
    int choice;

    std::cout << "Menu:\n";
    std::cout << "1. Change element in matrix\n";
    std::cout << "2. Exit the program\n";
    std::cout << "Enter (1/2): ";
    std::cin >> choice;

    return choice;
}

int main() {
    int rows, cols, choice = 0;

    while (choice != 2) {
        choice = menu();
        switch (choice) {
            case 1: {
                std::cout << "Enter the number of rows in your array: ";
                std::cin >> rows;
                std::cout << "Enter the number of columns in each row in your array: ";
                std::cin >> cols;

               
                int** array = new int*[rows];
                for (int i = 0; i < rows; i++) {
                    array[i] = new int[cols];
                }

                int* ones = new int[rows]();

                std::cout << "Fill in your matrix:\n";
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        std::cout << "Enter array[" << i << "][" << j << "]: ";
                        std::cin >> array[i][j];
                    }
                }

                printMatrix(array, rows, cols);

                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        ones[i] += count_ones(to_binary(array[i][j]));
                    }
                }

                for (int i = 0; i < rows; i++) {
                    std::cout << "There are " << ones[i] << " ones in row number " << i << "\n";
                }

                sorting(rows, cols, array, ones);

                std::cout << "Sorted Array:\n";
                printMatrix(array, rows, cols);

                for (int i = 0; i < rows; i++) {
                    delete[] array[i];
                }
                delete[] array;
                delete[] ones;

                break;
            }
            case 2:
                std::cout << "Exit program...\n";
                break;
            default:
                std::cout << "Incorrect choice. Try again\n";
        }
    }
    return 0;
}