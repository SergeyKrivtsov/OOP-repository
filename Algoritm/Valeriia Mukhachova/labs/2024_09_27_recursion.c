//add element using recusion and delete using recursion 
//2024_09_27 
#include <stdio.h> 
#include <malloc.h> 
#include <ctype.h> 
 
 
typedef struct Node 
{ 
    int val; 
    struct Node *next; 
}Node; 
 
int Pop(Node **head); 
void Print(Node *head); 
void Push(Node **head, int v); 
//deletes by value 
int Delete(Node **head, int info); 
int Put_before(Node **head, int info, int input_value); 
int check_range(int left, int right); 
void special_input(int *arr, int length); 
 
 
int main() 
{    
    Node *head = NULL; 
    int v = 0; 
    int del_v = 0, del_succ = 0; 
    int input_v = 0; 
    int input_before = 0; 
 
    printf("Please, enter the length of the list:\n"); 
    int length = check_range(1, __INT_MAX__); 
 
    int *arr_nodes = (int*)malloc(length*sizeof(int)); 
 
    special_input(arr_nodes, length); 
 
    for (int i = 0; i < length; i++) 
    { 
        Push(&head, *(arr_nodes+i)); 
    } 
 
 
    Print(head); 
    printf("success of print\n"); 
 
    printf("we're gonna put an element. enter the value of the new element\n"); 
    input_v = check_range(-__INT_MAX__, __INT_MAX__); 
     
    printf("now please enter the number of the element, before which were gonna put the new element. numberation starts from 1. if you want to put is last, enter %d\n", length+1 ); 
    input_before = check_range(1, length+1)-1; 
     
    del_succ = Put_before(&head, input_before, input_v); 
    if(del_succ== 0) 
        printf("error of input\n"); 
    else 
        Print(head); 
 
    printf("we're gonna attemp to delete all elements with value n. choose n\n"); 
    del_v = check_range(-__INT_MAX__, __INT_MAX__); 
     
    del_succ = Delete(&head, del_v); 
    if(del_succ== 0) 
        printf("error of delete\n"); 
    else 
        Print(head); 
     
    return 0; 
} 
 
//LIFO 
void Push(Node **head, int v) 
{ 
    Node *temp = (Node*)malloc(sizeof(Node)); 
    temp->val = v; 
    temp->next = *head; 
    *head = temp; 
} 
 
void Print(Node *head) 
{ 
    if(head==NULL) 
        printf("erorr/n"); 
    while (head != NULL) 
    { 
        printf("%d ", head->val); 
        head = head->next; 
    } 
    printf("\n"); 
} 
 
int Delete(Node **head, int info)  
{ 
    Node *cur; 
 
    if (*head == NULL) return 0; 
     
    if ((*head)->val == info)  
    { 
        cur = *head;  
        *head = (*head)->next;  
        free(cur);  
        return 1 + Delete(head, info);  
    }  
    else   
        return Delete(&((*head)->next), info);  
} 
 
int Put_before(Node **head, int info, int input_value) 
{ 
    Node *temp = (Node*)malloc(sizeof(Node)); 
    Node *prev = (Node*)malloc(sizeof(Node)); 
    Node *cur = (Node*)malloc(sizeof(Node)); 
    if(head==NULL) 
        return 0; 
         
    if(info == 0) 
    { 
        temp->val = input_value; 
        temp->next = *head; 
        *head = temp; 
        return 1; 
    } 
    else 
        return Put_before(&(*head)->next, info-1, input_value); 
} 
 
//перевіряє, що користувач ввів саме число, і що воно попадає між заданих чисел 

int check_range(int left, int right) 
{ 
    int var = 0; 
    int bad_input = 0; 
    int i = 0; 
     
     
    while(1) 
    { 
        var = 0; 
        char number[30]; 
        bad_input = 0; 
        i = 0; 

        if (fgets(number, sizeof(number), stdin) == NULL) { 
            printf("Error reading input. Please try again.\n"); 
            clearerr(stdin); 
            continue;  
        } 
         
 
        //перевіряє, що користувач не натиснув тільки Enter 
        if(number[0]==10) 
        {     
            bad_input = 1; 
        } 
         
 
        //перевріяє, що користувач не ввів букви, або спец знаки. 
        while(number[i]!=' '&&number[i]!='\n'&&number[i]!='\0') 
        { 
            if ((number[i] -'0')<0||(number[i] - '0')>9) 
            {     
                bad_input = 1; 
                break; 
            } 
            else 
            {     
                //якщо це не буква або знак, переводить у число 
                var = var*10 + (number[i] - '0');  
                i++; 
            } 
        } 
 
 
        if(bad_input ==1) 
            printf("Please, try again, only numbers.\n"); 
        else 
        { 
            //якщо не попадає в рамки, просить ввести знову 
            if(left==right && var != right) 
                printf("Please, try again and beware of the range.\n"); 
            else 
            { 
                if(var < left || var > right) 
                    printf("Please, try again and beware of the range.\n"); 
                else 
                    //якщо попадає в задані рамки виход з циклу  
                    break; 
            } 
        } 
    } 
     
    return var;   
} 
 
void special_input(int *arr, int length) 
{ 
 
    char number[100]; 
    int bad_input = 0; 
    int i = 0; 
    int count = 0; 
 
    while(1) 
    { 
 
        printf("Please, input exactly %d numbers\n", length); 
 
        //перевіряє, що fgets щось отримав 
        if((fgets(number, 100, stdin))==NULL) printf("Error of fgets\n"); 
 
         
        count = 0; 
        bad_input = 0; 
        i = 0; 
 
        //puts(number); 
        //перевіряє, що користувач не натиснув тільки Enter 
        if(number[0]==10) 
        {     
            bad_input = 1; 
            printf("You only pressed enter\n"); 
        } 
 
        //перевріяє, що користувач не ввів букви, або спец знаки. 
        while(number[i]!='\n'&&number[i]!='\0') 
        { 
            while(number[i] == ' ') i++; 
 
            while(number[i] == ' ') i++; 
 
            if (!isdigit(number[i])) 
            {     
                bad_input = 1; 
                printf("You should only input numbers and space\n"); 
                break; 
            } 
            else 
            { 
                int current_num = 0; 
                while(isdigit(number[i])) { 
                    current_num = current_num * 10 + (number[i] - '0'); 
                    i++; 
                } 
 
                
                if(count < length) { 
                    arr[count] = current_num; 
                    count++; 
                } else { 
                    bad_input = 1; 
                    printf("Too many numbers.\n"); 
                    break; 
                } 
 
                 
                while(number[i] == ' ') i++; 
 
            } 
        } 
 
        if(count<length) 
        { 
            bad_input = 1; 
            printf("Not enough numbers\n"); 
        } 
 
        if(bad_input ==1) 
        { 
            printf("Please, try again, only numbers and pay attention to how many nubmers you should input\n"); 
        } 
        else 
            break; 
    } 
     
}