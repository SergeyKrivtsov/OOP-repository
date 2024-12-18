#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_best_case(int arr[], int n);
void generate_worst_case(int arr[], int n);
void generate_random_case(int arr[], int n);
void merge(int arr[], int left, int mid, int right, int *comparisons, int *moves);
void mergeSort(int arr[], int left, int right, int *comparisons, int *moves);
void shellSort(int arr[], int n, int *comparisons, int *moves);


int main() 
{
    srand(time(NULL));

    int sizes[] = {100, 1000, 10000, 100000, 1000000};
    int num_sizes = 3;


    for (int i = 0; i < num_sizes; i++) 
    {
        int n = sizes[i];
        int arr_best[n], arr_worst[n], arr_random[n];
        int comparisons, moves;

        //тест на найкращому випадку
        generate_best_case(arr_best, n);
        comparisons = 0; moves = 0;
        shellSort(arr_best, n, &comparisons, &moves);  
        printf("Shell Sort (Best):   Size of the array=%d: Comparisons = %d, Moves = %d\n", n, comparisons, moves);

        //тест на найгіршому випадку
        generate_worst_case(arr_worst, n);
        comparisons = 0; moves = 0;
        shellSort(arr_worst, n, &comparisons, &moves);
        printf("Shell Sort (Worst):  Size of the array=%d: Comparisons = %d, Moves = %d\n", n, comparisons, moves);


        //тест на випадковому випадку
        generate_random_case(arr_random, n);
        comparisons = 0; moves = 0;
        shellSort(arr_random, n, &comparisons, &moves);
        printf("Shell Sort (Random): Size of the array=%d: Comparisons = %d, Moves = %d\n", n, comparisons, moves);

        //тест на найкращому випадку
        generate_best_case(arr_best, n);
        comparisons = 0; moves = 0;
        mergeSort(arr_best, 0, n, &comparisons, &moves);
        printf("Merge Sort (Best):   Size of the array=%d: Comparisons = %d, Moves = %d\n", n, comparisons, moves);

        //тест на найгіршому випадку
        generate_worst_case(arr_worst, n);
        comparisons = 0; moves = 0;
        mergeSort(arr_worst, 0, n, &comparisons, &moves);
        printf("Merge Sort (Worst):  Size of the array=%d: Comparisons = %d, Moves = %d\n", n, comparisons, moves);

        //тест на випадковому випадку
        generate_random_case(arr_random, n);
        comparisons = 0; moves = 0;
        mergeSort(arr_random, 0, n, &comparisons, &moves);
        printf("Merge Sort (Random): Size of the array=%d: Comparisons = %d, Moves = %d\n", n, comparisons, moves);
    }

    return 0;
}

//масив вже відсортований
void generate_best_case(int arr[], int n) 
{
    for (int i = 0; i < n; i++) 
    {
        arr[i] = i + 1;  
    }
}
//масив відсортований у зворотному порядку
void generate_worst_case(int arr[], int n) 
{
    for (int i = 0; i < n; i++) 
    {
        arr[i] = n - i;  
    }
}
//випадковий масив
void generate_random_case(int arr[], int n) 
{
    for (int i = 0; i < n; i++) 
    {
        arr[i] = rand() % 1000;  
    }
}

//отримує два відсортованих масива зливає їх в один
void merge(int arr[], int left, int mid, int right, int *comparisons, int *moves) 
{
    //розрахунок кількості елементів в лівому і правому масивах
    int n1 = mid - left + 1;
    int n2 = right - mid;

    //створення тимчасових масивів
    int L[n1], R[n2];

    //копіювання масивів в тимчасові масиви
    for (int i = 0; i < n1; i++) 
    {
        L[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++) 
    {
        R[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;
    
    //іде по підмасивам
    while (i < n1 && j < n2) 
    {   
        //ящко елемент з лівого меньше то він копіюється в масив
        if (L[i] <= R[j]) 
        {
            arr[k] = L[i];
            i++;
        } 
        else
        //інакше копіюється правий 
        {
            arr[k] = R[j];
            j++;
        }
        k++;
        (*comparisons)++;
        (*moves)++;
    }

    //якщо залишаються елементи в одному з масивів, то копіює їх в основний масив
    while (i < n1) 
    {
        arr[k] = L[i];
        i++;
        k++;
        (*moves)++;
    }

    while (j < n2) 
    {
        arr[k] = R[j];
        j++;
        k++;
        (*moves)++;
    }
}

//рекурсивно сортує половини масива і зливає відсортовані половини
void mergeSort(int arr[], int left, int right, int *comparisons, int *moves) 
{
    if (left < right) 
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid, comparisons, moves);
        mergeSort(arr, mid + 1, right, comparisons, moves);

        merge(arr, left, mid, right, comparisons, moves);
    }
}

//сортування Шелла
void shellSort(int arr[], int n, int *comparisons, int *moves) 
{
    int gap, i, j, temp;

    //починаємо з gap=n/2 зменьшуємо по gap=1
    for (gap = n / 2; gap > 0; gap /= 2) 
    {
        for (i = gap; i < n; i++) 
        {
            temp = arr[i];
            j = i;
            //цикл для переміщення елементів
            while (j >= gap) 
            {
                (*comparisons)++; 
                //порівнює елменти на відстані gap 
                if (arr[j - gap] > temp) 
                {
                    //якщо більше переміщує
                    arr[j] = arr[j - gap];
                    (*moves)++;
                    //зменьшує j
                    j -= gap;
                } 
                else 
                {
                    break;
                }
            }
            //після того як знайдена правильна позиція j для елемента temp вставляємо в масив 
            arr[j] = temp;
            (*moves)++;
        }
    }
}
