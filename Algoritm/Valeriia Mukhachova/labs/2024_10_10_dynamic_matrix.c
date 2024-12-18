#include <stdio.h>
#include <malloc.h>

int Menu();
void Work(int i);
void Input(int **array, int matr_size);
void Triangle(int **array, int matr_size);
void Output(int **array, int matr_size);


int main()
{ 
    int menu_switch;
    char ch = 'y';
    while (ch=='y'||ch=='Y')
    {
        menu_switch = Menu();
        Work(menu_switch);
        printf("Would you like to continue? Enter 'y' if yes, 'n' if no \n");
        getchar();
        ch = getchar();
        getchar();
    }
    return 0;
}



int Menu()
{
    int i = 0;
    printf("If you would like to input the matrix and change non-diagonal elements to 0: Enter 1\n");
    scanf ("%d", &i);
    return i;
}

void Work(int i)
{
    switch (i)
    {
        case 1: 
        {
            int **arr;
            int size_matrix;
            printf("Please, enter the size of the matrix \n");
            scanf ("%d", &size_matrix);
            arr=(int**)malloc(size_matrix*sizeof(int*));
            for (int i=0; i<size_matrix; i++)
                arr[i] = (int*)malloc(size_matrix*sizeof(int));
            
            Triangle(arr, size_matrix);
            Output (arr, size_matrix);
            
            for (int i=0; i<size_matrix; i++)
                free(arr[i]);
                
            free(arr);
            
        }
    }
}


void Triangle(int **array, int matr_size)
{
    for (int i=0; i<matr_size; i++)
    {
        for (int j=0; j<matr_size; j++)
        {
            if((i>=matr_size-j-1 && i<=matr_size/2)||(i>=matr_size/2+1 && i<=j))
                *(*(array+i)+j)=1;
            else
                *(*(array+i)+j)=0;
        }
    }
}

void Output(int **array, int matr_size)
{
    printf ("-----------\n");
    for (int i=0; i<matr_size; i++)
    {
        for (int j=0; j<matr_size; j++)
        {
            printf ("%d ", *(*(array+i)+j));
        }
        printf("\n");
    }
}
