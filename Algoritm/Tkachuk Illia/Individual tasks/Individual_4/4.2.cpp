#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

int generateRandom(int minVal, int maxVal) {
    static int seed = 3; 
    seed = (seed * 40 + 5) % 1001;
    return (seed % (maxVal - minVal + 1)) + minVal;
}

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

void generateRandomArrayFile(const string &filename, int size, int minVal, int maxVal) {
   ofstream outFile(filename);
   if (!outFile) {
        cout << "Error: Cannot create file " << filename << endl;
        exit(1);
   }
   vector<int> randomArray(size);
   vector<int> sortedArray(size);
   vector<int> reversedArray(size);

   for (int i = 0; i < size; i++) {
        randomArray[i] = generateRandom(minVal, maxVal);
   }

   for (int i = 0; i < size; i++) {
        sortedArray[i] = randomArray[i];
   }

   for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (sortedArray[j] > sortedArray[j + 1]) {
                swap(sortedArray[j], sortedArray[j + 1]);
            }
        }
   }
   for (int i = 0; i < size; i++) {
        reversedArray[i] = sortedArray[size - 1 - i];
   }

   for (const int &val : randomArray) {
        outFile << val << " ";
   }
   outFile << "\n";

   for (const int &val : sortedArray) {
        outFile << val << " ";
   }
   outFile << "\n";

   for (const int &val : reversedArray) {
        outFile << val << " ";
   }
   outFile << "\n";

   outFile.close();
}

void readArrayFromFile(const string &filename, vector<int> &arr, int lineNumber) {
   ifstream inFile(filename);
   if (!inFile) {
      cout << "Error: Cannot open file " << filename << endl;
      exit(1);
   }

   string line;
   int currentLine = 0;
   while (getline(inFile, line)) {
        if (++currentLine == lineNumber) {
            istringstream iss(line);
            int value;
            while (iss >> value) {
               arr.push_back(value);
            }
            break;
        }
   }
   inFile.close();
}

void writeResultsToFile(const string &filename, int avgComparisons, int avgSwaps,
                     int bestComparisons, int bestSwaps, int worstComparisons, int worstSwaps) {
   ofstream outFile(filename);
   if (!outFile) {
        cout << "Error: Cannot open file " << filename << endl;
        exit(1);
   }

   outFile << "Average case (comparisons, swaps): " << avgComparisons << ", " << avgSwaps << "\n";
   outFile << "Best case (comparisons, swaps): " << bestComparisons << ", " << bestSwaps << "\n";
   outFile << "Worst case (comparisons, swaps): " << worstComparisons << ", " << worstSwaps << "\n";

   outFile.close();
}
void writeResultsToCSV(const string &csvFilename, int avgComparisons, int avgSwaps,
                       int bestComparisons, int bestSwaps, int worstComparisons, int worstSwaps) {
   ofstream csvFile(csvFilename);
   if (!csvFile) {
        cout << "Error: Cannot open CSV file " << csvFilename << endl;
        exit(1);
   }

   csvFile << "Case,Comparisons,Swaps\n";
   csvFile << "Average," << avgComparisons << "," << avgSwaps << "\n";
   csvFile << "Best," << bestComparisons << "," << bestSwaps << "\n";
   csvFile << "Worst," << worstComparisons << "," << worstSwaps << "\n";

   csvFile.close();
}

int main() {
   string inputFilename = "input.txt";
   string outputFilename = "output.txt";
   string csvFilename = "results.csv";

   generateRandomArrayFile(inputFilename, 10000, 1, 10000);

   vector<int> avgArr, bestArr, worstArr;
   readArrayFromFile(inputFilename, avgArr, 1);
   readArrayFromFile(inputFilename, bestArr, 2);
   readArrayFromFile(inputFilename, worstArr, 3);

   int avgComparisons = 0, avgSwaps = 0;
   int bestComparisons = 0, bestSwaps = 0;
   int worstComparisons = 0, worstSwaps = 0;

   mergeSort(avgArr.data(), 0, avgArr.size() - 1, avgComparisons, avgSwaps);
   mergeSort(bestArr.data(), 0, bestArr.size() - 1, bestComparisons, bestSwaps);
   mergeSort(worstArr.data(), 0, worstArr.size() - 1, worstComparisons, worstSwaps);

   writeResultsToFile(outputFilename, avgComparisons, avgSwaps, bestComparisons, bestSwaps, worstComparisons, worstSwaps);
   writeResultsToCSV(csvFilename, avgComparisons, avgSwaps, bestComparisons, bestSwaps, worstComparisons, worstSwaps);

   cout << "Сортировка завершена. Результаты записаны в файлы " << outputFilename << " и " << csvFilename << endl;

   return 0;
}
