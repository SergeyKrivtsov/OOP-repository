//2024_09_25 
//oh no actually this is the cycle horror 
//додати функціб формування
#include <stdio.h> 
#include <malloc.h> 
#include <ctype.h> 
 
typedef struct Node 
{ 
    int val; 
    struct Node *next; 
}Node; 
 
int Pop(Node **head); 
void Print(Node **head); 
void Push(Node **head, int v); 
int Delete_by_pos(Node **head, int info); 
int Put_on_pos(Node **head, int info, int input_value); 
int check_range(int left, int right); 
void special_input(int *arr, int length); 
int Delete_every_nth(Node **head, int info); 
int Delete_by_val(Node **head, int info); 
 
int main() 
{    
    Node *head = NULL; 
    int v = 0; 
    int del_v = 0; 
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
 
    Print(&head); 
 
    printf("Success of print\n"); 
     
     
     
    // printf("now we're deleting every nth element. please, input the n (min -2)\n"); 
 
    // del_v = check_range(2, __INT_MAX__); 
     
    // int del_succ = Delete_every_nth(&head, del_v); 
    // if(!del_succ) 
    //     printf("Erorr of delete\n"); 
    // else 
    //     Print(&head); 
 
 
 
    // printf("which element you want to delete? numeration starts from 1\n"); 
 
    // del_v = check_range(1, length)-1; 
    // int del_succ = Delete_by_pos(&head, del_v); 
    // if(!del_succ) 
    //     printf("Erorr of delete\n"); 
    // else 
    //     Print(&head); 
     
     
 
 
     
    printf("which element you want to delete? input the value, all the elemts that are equal will be deleted\n"); 
 
    del_v = check_range(-__INT_MAX__, __INT_MAX__); 
 
    int del_succ = Delete_by_val(&head, del_v); 
    if(!del_succ) 
        printf("Erorr of delete\n"); 
    else 
        Print(&head); 
         
    printf("success of print\n"); 
 
 
 
 
 
 
 
    // printf("which element you want to add? input value\n"); 
    // input_v = check_range(-__INT_MAX__, __INT_MAX__); 
     
    // printf("before which element?numeration starts from 1\n"); 
    // input_before = check_range(1, length)-1; 
 
    // del_succ = Put_before(&head, input_before, input_v); 
    // if(!del_succ) 
    //     printf("Erorr of add/n"); 
    // else 
    //     Print(head); 
 
    return 0; 
} 
 
//LIFO 
void Push(Node **head, int v) 
{ 
    Node *temp = (Node*)malloc(sizeof(Node)); 
    temp->val = v; 
 
    if(*head==NULL) 
    { 
        temp->next = temp; 
        *head = temp; 
    } 
    else 
    { 
        Node *last = *head;  
        while (last->next != *head)  
        { 
            last = last->next; 
        } 
         
        last->next = temp;  
        temp->next = *head;  
        *head = temp;  
    } 
} 
 
int Pop(Node **head) 
{ 
    Node *prev = NULL; 
    int val; 
    if (head!=NULL) 
    { 
        prev = *head; 
        val = prev->val; 
        *head = (*head)->next; 
        return val; 
    } 
    else return 0; 
} 
 
void Print(Node **head) 
{ 
    Node *temp = (Node*)malloc(sizeof(Node)); 
    temp = *head; 
    if(head==NULL) 
        printf("erorr of print/n"); 
     
    do 
    { 
        printf("%d ", temp->val); 
        temp = temp->next; 
    }while (temp!=*head); 
    printf("\n"); 
} 
 
 
int Delete_by_pos(Node **head, int info) 
{ 
    Node *prev = *head; 
    Node *temp = prev->next; 
     
    int count = 0; 
     
 
    if((*head)==NULL) 
        return 0; 
         
         
         
    if (info==0) 
    { 
        Node *last = *head; 
        while (last->next != *head)  
        { 
            last = last->next; 
        } 
        //if the head is the only node 
        if (*head == (*head)->next)  
        { 
            free(*head); 
            *head = NULL; 
            return 1; 
        } 
 
           
        last->next =prev->next; 
        *head = prev->next;   
        free(prev);   
        temp = *head; 
        return 1; 
    } 
    else 
    { 
        prev = *head; 
        temp = prev->next; 
        count++; 
         
        do  
        { 
            if (count==info) 
            { 
                prev->next = temp->next;  
                free(temp); 
                return 1; 
            } 
            else 
            { 
                prev = temp; 
                temp = temp->next; 
                count++; 
            } 
        }while(prev->next != *head); 
    } 
    return 0; 
} 
 
int Delete_by_val(Node **head, int info) 
{ 
    Node *temp;  
    Node *prev;  
    int count = 1; 
     
    if((*head)==NULL) 
        return 0; 
 
    prev = *head; 
    temp = prev->next; 
     
    while(1) 
    { 
        if(prev->val == info) 
        { 
            
            Node *last = *head; 
            while (last->next != *head)  
            { 
                last = last->next; 
            } 
            if (*head == (*head)->next)  
            { 
                free(*head); 
                *head = NULL; 
                return 1; 
            } 
     
               
            last->next = prev->next; 
            *head = prev->next;   
            free(prev);   
            prev = *head; 
            temp = prev->next; 
            Print(head); 
        } 
        else 
            break; 
    } 
     
    do  
    { 
        if(temp->val==info) 
        { 
            prev->next = temp->next; 
            free(temp); 
 
            temp = prev->next; 
            count++; 
            count++; 
            Print(head); 
        } 
        else 
        { 
            prev = temp; 
            temp = temp->next; 
            count++; 
        } 
    }while(temp != *head); 
     
    Print(head); 
 
    return 1; 
 
} 
 
int Delete_every_nth(Node **head, int info) 
{ 
    Node *temp;  
    Node *prev;  
    int count = 2; 
     
    if((*head)==NULL) 
        return 0; 
 
    prev = *head; 
    temp = prev->next; 
 
   
     
    while(*head != (*head)->next) 
    { 
        if(count==info) 
        { 
            if(temp == *head) 
            { 
                Node *last = *head; 
                while (last->next != *head)   
                { 
                    last = last->next; 
                } 
                last->next = temp->next;   
                *head = temp->next;   
                free(temp);   
                temp = *head;   
            } 
            else 
            { 
                prev->next = temp->next; 
                free(temp); 
                temp = prev->next; 
            } 
             
            count = 1; 
            Print(head); 
        } 
        else 
        { 
            prev = temp; 
            temp = temp->next; 
            count++; 
        } 
    } 
 
    return 1; 
 
} 
 
//doesn't work on cycle's first and last fix it 
int Put_on_pos(Node **head, int info, int input_value) 
{ 
    if(head==NULL) 
        return 0; 
    Node *temp = (Node*)malloc(sizeof(Node)); 
    Node *prev = (Node*)malloc(sizeof(Node)); 
    Node *cur = (Node*)malloc(sizeof(Node)); 
 
    int count = 0; 
     
    if (info==0) 
    { 
        temp->val = input_value; 
        temp->next = *head; 
        *head = temp; 
        return 1; 
    } 
    else 
    { 
        prev = *head; 
        temp = prev->next; 
        count++; 
         
        do 
        { 
            if (count==info) 
            { 
                cur->val = input_value; 
                cur->next = temp; 
                prev->next = cur; 
                return 1; 
            } 
            else 
            { 
                prev = temp; 
                temp = temp->next; 
                count++; 
            } 
 
        }while(temp != *head); 
            
    } 
    return 0; 
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
            if ((number[i] - '0')<0||(number[i] - '0')>9) 
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