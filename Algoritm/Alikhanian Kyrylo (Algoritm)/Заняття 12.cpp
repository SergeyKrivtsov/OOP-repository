#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Глобальні змінні для підрахунку порівнянь і переміщень
long long comparisons = 0;
long long swaps = 0;

// Функція для обміну елементів
void swap(int& a, int& b) {
    swaps++;
    int temp = a;
    a = b;
    b = temp;
}

// Розділяє масив для QuickSort
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Рекурсивна реалізація QuickSort
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Функція для тестування QuickSort
void testQuickSort(int size) {
    vector<int> arr(size);
    srand(time(0));

    // Заповнення масиву випадковими числами
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 10000;
    }

    comparisons = 0;
    swaps = 0;

    quickSort(arr, 0, size - 1);

    cout << "Розмір масиву: " << size << endl;
    cout << "Кількість порівнянь: " << comparisons << endl;
    cout << "Кількість переміщень: " << swaps << endl;
    cout << "--------------------------" << endl;
}

int main() {
    // Тестування для різних розмірів масиву
    vector<int> sizes = { 100, 1000, 10000, 100000 };
    for (int size : sizes) {
        testQuickSort(size);
    }

    return 0;
}
