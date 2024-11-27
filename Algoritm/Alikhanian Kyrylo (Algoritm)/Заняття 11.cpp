#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <cstdlib>

struct SortStats {
    long long comparisons = 0;
    long long swaps = 0;
};

void bubbleSort(std::vector<int>& arr, SortStats& stats) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            stats.comparisons++;
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                stats.swaps++;
            }
        }
    }
}

void insertionSort(std::vector<int>& arr, SortStats& stats) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        stats.comparisons++;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            stats.swaps++;
            j--;
            if (j >= 0) stats.comparisons++;
        }
        arr[j + 1] = key;
        stats.swaps++;
    }
}

void merge(std::vector<int>& arr, int left, int mid, int right, SortStats& stats) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (int i = 0; i < n2; ++i) R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        stats.comparisons++;
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        }
        else {
            arr[k++] = R[j++];
        }
        stats.swaps++;
    }

    while (i < n1) {
        arr[k++] = L[i++];
        stats.swaps++;
    }

    while (j < n2) {
        arr[k++] = R[j++];
        stats.swaps++;
    }
}

void mergeSort(std::vector<int>& arr, int left, int right, SortStats& stats) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, stats);
        mergeSort(arr, mid + 1, right, stats);
        merge(arr, left, mid, right, stats);
    }
}

void quickSort(std::vector<int>& arr, int low, int high, SortStats& stats) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            stats.comparisons++;
            if (arr[j] < pivot) {
                i++;
                std::swap(arr[i], arr[j]);
                stats.swaps++;
            }
        }
        std::swap(arr[i + 1], arr[high]);
        stats.swaps++;

        int pi = i + 1;
        quickSort(arr, low, pi - 1, stats);
        quickSort(arr, pi + 1, high, stats);
    }
}

std::vector<int> generateData(int n, const std::string& type) {
    std::vector<int> data(n);
    if (type == "best") {
        for (int i = 0; i < n; ++i) data[i] = i;
    }
    else if (type == "worst") {
        for (int i = 0; i < n; ++i) data[i] = n - i;
    }
    else {
        for (int i = 0; i < n; ++i) data[i] = rand() % 10000;
    }
    return data;
}

void testSort(void (*sortFunc)(std::vector<int>&, SortStats&), const std::string& name, const std::string& caseType) {
    std::ofstream results("results.csv", std::ios::app);
    if (results.tellp() == 0) {
        results << "Method,Case,Size,Comparisons,Swaps\n";
    }

    for (int size : {100, 1000, 10000, 100000}) {
        std::vector<int> data = generateData(size, caseType);
        SortStats stats;

        clock_t start = clock();
        sortFunc(data, stats);
        clock_t end = clock();

        results << name << "," << caseType << "," << size << "," << stats.comparisons << "," << stats.swaps << "\n";
        std::cout << name << " (" << caseType << ", " << size << " elements): "
            << "Comparisons = " << stats.comparisons
            << ", Swaps = " << stats.swaps
            << ", Time = " << double(end - start) / CLOCKS_PER_SEC << "s\n";
    }
    results.close();
}

int main() {
    srand(time(0));

    testSort(bubbleSort, "BubbleSort", "best");
    testSort(bubbleSort, "BubbleSort", "worst");
    testSort(bubbleSort, "BubbleSort", "random");

    testSort(insertionSort, "InsertionSort", "best");
    testSort(insertionSort, "InsertionSort", "worst");
    testSort(insertionSort, "InsertionSort", "random");

    testSort([](std::vector<int>& data, SortStats& stats) { mergeSort(data, 0, data.size() - 1, stats); }, "MergeSort", "best");
    testSort([](std::vector<int>& data, SortStats& stats) { mergeSort(data, 0, data.size() - 1, stats); }, "MergeSort", "worst");
    testSort([](std::vector<int>& data, SortStats& stats) { mergeSort(data, 0, data.size() - 1, stats); }, "MergeSort", "random");

    return 0;
}
