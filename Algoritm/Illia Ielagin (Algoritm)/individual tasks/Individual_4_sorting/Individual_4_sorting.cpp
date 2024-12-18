#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

// Лічильники для алгоритмів
int comparisons = 0, movements = 0;

// Сортування злиттям (з попереднього прикладу)
void merge(vector<int>& arr, int left, int mid, int right);
void mergeSort(vector<int>& arr, int left, int right);

// Генерація даних
vector<int> generateData(int size, const string& type) {
    vector<int> data(size);
    if (type == "best") {
        // Найкращий випадок: вже відсортовані дані
        for (int i = 0; i < size; ++i) data[i] = i;
    }
    else if (type == "worst") {
        // Найгірший випадок: дані відсортовані у зворотному порядку
        for (int i = 0; i < size; ++i) data[i] = size - i;
    }
    else if (type == "average") {
        // Середній випадок: випадкові дані
        srand(static_cast<unsigned>(time(nullptr)));
        for (int i = 0; i < size; ++i) data[i] = rand() % size;
    }
    return data;
}

// Тестування сортування злиттям
void testMergeSort(int size, const string& caseType, FILE* file) {
    vector<int> data = generateData(size, caseType);
    comparisons = movements = 0; // Обнулити лічильники

    clock_t start = clock();
    mergeSort(data, 0, data.size() - 1);
    clock_t end = clock();

    double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;

    // Запис результатів у файл
    fprintf(file, "%d,%s,%d,%d,%.2f\n", size, caseType.c_str(), comparisons, movements, duration);
    printf("Size: %d, Case: %s, Comparisons: %d, Movements: %d, Time: %.2f ms\n",
        size, caseType.c_str(), comparisons, movements, duration);
}

// Реалізація функцій merge та mergeSort
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) {
        L[i] = arr[left + i];
        movements++;
    }
    for (int i = 0; i < n2; ++i) {
        R[i] = arr[mid + 1 + i];
        movements++;
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        comparisons++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        movements++;
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        movements++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        movements++;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    vector<int> sizes = { 100, 1000, 10000, 100000, 1000000 };
    vector<string> cases = { "best", "average", "worst" };

    FILE* file;
    errno_t err = fopen_s(&file, "results.txt", "w");
    if (err != 0) {
        cerr << "Не вдалося відкрити файл для запису!" << endl;
        return 1;
    }

    fprintf(file, "Size,Case,Comparisons,Movements,Time(ms)\n"); // Заголовок CSV

    for (int size : sizes) {
        for (const string& caseType : cases) {
            testMergeSort(size, caseType, file);
        }
    }

    fclose(file);
    cout << "The results are saved in results.txt." << endl;

    return 0;
}
