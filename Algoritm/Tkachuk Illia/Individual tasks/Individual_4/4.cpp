#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm> 
using namespace std;

void merge(int arr[], int left, int mid, int right, int &comparisons, int &swaps) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    int leftArr[n1], rightArr[n2];
    
    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++) {
        rightArr[i] = arr[mid + 1 + i];
    }
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        comparisons++; 
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
        swaps++; 
    }
    
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
        swaps++; 
    }
    
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
        swaps++; 
    }
}

void mergeSort(int arr[], int left, int right, int &comparisons, int &swaps) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        mergeSort(arr, left, mid, comparisons, swaps);
        mergeSort(arr, mid + 1, right, comparisons, swaps);
        
        merge(arr, left, mid, right, comparisons, swaps);
    }
}

void testMergeSort(int size) {
    vector<int> arr(size);

    for (int i = 0; i < size; i++) {
        arr[i] = i + 1;
    }
    int best_comparisons = 0, best_swaps = 0;
    mergeSort(arr.data(), 0, size - 1, best_comparisons, best_swaps);

    for (int i = 0; i < size; i++) {
        arr[i] = size - i;
    }
    int worst_comparisons = 0, worst_swaps = 0;
    mergeSort(arr.data(), 0, size - 1, worst_comparisons, worst_swaps);

    for (int i = 0; i < size; i++) {
        arr[i] = i + 1;
    }
    random_shuffle(arr.begin(), arr.end());
    int avg_comparisons = 0, avg_swaps = 0;
    mergeSort(arr.data(), 0, size - 1, avg_comparisons, avg_swaps);

    cout << "Size: " << size << endl;
    cout << "Best case (comparisons, swaps): " << best_comparisons << ", " << best_swaps << endl;
    cout << "Worst case (comparisons, swaps): " << worst_comparisons << ", " << worst_swaps << endl;
    cout << "Average case (comparisons, swaps): " << avg_comparisons << ", " << avg_swaps << endl;
    cout << "------------------------------------" << endl;
}

int main() {
    for (int size : {100, 1000, 10000, 100000, 1000000}) {
        testMergeSort(size);
    }
    return 0;
}