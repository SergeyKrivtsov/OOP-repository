//2024_10_11
//двоспрямований список
//додати фунцкцію для формування списку

//коментарі
//додати менб?
#include <stdio.h> 
#include <malloc.h> 
#include <ctype.h> 
 
 
typedef struct Node 
{ 
    int val; 
    struct Node *next; 
    struct Node *prv;
    
}Node; 
 
int Pop(Node **head); 
void Print(Node *head); 
void Push(Node **head, int v); 
int Delete(Node **head, int info); 
int Put_before(Node **head, int info, int input_value); 
int check_range(int left, int right); 
void special_input(int *arr, int length); 
void formlist(Node **top, Node **tail);
void Print_tail(Node *tail);
void Symmerty(Node *head, Node *tail);
 
 
int main() 
{    
    Node *head = NULL; 
    Node *tail = NULL; 
    int del_v = 0, del_succ = 0; 
    int input_v = 0; 
    int input_before = 0; 
 
    formlist(&head, &tail);
    Print(head); 
    Print_tail(tail);
    printf("success of print\n"); 

    Symmerty(head, tail);
 
    printf("we're gonna put an element. enter the value of the new element\n"); 
    input_v = check_range(-__INT_MAX__, __INT_MAX__); 
     
    printf("now please enter the number of the element, before which were gonna put the new element. numberation starts from 1.\n"); 
    input_before = check_range(1, __INT_MAX__)-1; 
     
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
    temp->prv = NULL; 

    if (*head != NULL) 
    {
        (*head)->prv = temp; 
    }

    *head = temp; 
} 

//виводить з голови
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
 
//виводить з хвоста
void Print_tail(Node *tail) 
{ 
    if(tail==NULL) 
        printf("erorr/n"); 
    while (tail != NULL) 
    { 
        printf("%d ", tail->val); 
        tail = tail->prv; 
    } 
    printf("\n"); 
} 
 
int Delete(Node **head, int info)  
{ 
    Node *cur = *head;
    
    if (cur == NULL) return 0; 

    if (cur->val == info)  
    { 
        if (cur == *head) 
        {
            *head = cur->next;  
            //якщо не нуль
            if (*head != NULL) 
                (*head)->prv = NULL;//обновляє попередне 
        }
        else 
        {
            if (cur->next != NULL)
                cur->next->prv = cur->prv;
            if (cur->prv != NULL)
                cur->prv->next = cur->next;
        }

        free(cur);  
        return 1 + Delete(head, info);  
    }  
    else   
        return Delete(&(cur->next), info);  
}

int Put_before(Node **head, int info, int input_value) 
{
    if (*head == NULL)
        return 0; 

    Node *cur = *head;
    int counter = 0;
    //шукає ноду під номером info
    while (cur != NULL && counter != info)
    {
        counter++;
        cur = cur->next;
    }

    //якщо дійшли до кінця і не знайшли ноду
    if (cur == NULL)
        return 0; 


    Node *temp = (Node*)malloc(sizeof(Node));
    temp->val = input_value;

    //вставляємо перед cur
    temp->next = cur; 
    temp->prv = cur->prv; 

    //якщо не перша то іспрявляємо попередню
    if (cur->prv != NULL)
        cur->prv->next = temp;

    
    cur->prv = temp;

    //якщо перша, то обновляємо голову
    if (cur == *head)
        *head = temp;

    return 1;
}

//перевіряє, що користувач ввів саме число, і що воно попадає між заданих чисел 
int check_range(int left, int right) 
{ 
    int var = 0; 
    int bad_input = 0; 
    int i = 0; 
    int negative = 0;
     
    while(1) 
    { 
        var = 0; 
        char number[30]; 
        bad_input = 0; 
        i = 0; 
        negative = 0;

         
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
                if(i==0&&number[i]=='-')
                {
                    negative = 1; 
                    i++;
                }
                else
                {
                    bad_input = 1;
                    break;
                } 
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

    if(negative==1)
        return -var;
    else
        return var;   
} 
 

//форумє лист
void formlist(Node **top, Node **tail)
{
    printf("Please, enter the first node.\n");
    int value;
    Node *current;
    scanf("%d", &value);
    while (value)
    {
        current = (Node*)malloc(sizeof(Node));
        current->val = value;
        current->next = NULL; //додає останню
        current->prv = *tail; //зв'язує з хвостом

        if (*top == NULL)
        {
            //якщо лист пустий нова і хвіст і голова
            *top = current; 
            *tail = current;
        }
        else
        {
            //якщо не пустий хвост вказує на цю
            (*tail)->next = current; 
            *tail = current;         
        }

        printf("Please, enter a new node, if you want to finish enter 0.\n");
           
        scanf("%d", &value);
    }
    Print(*top);
}

//перевірити чи лист симетричний
void Symmerty(Node *head, Node *tail)
{
    int sym_check = 1;
    while(head!=NULL)
    {
        if(head->val==tail->val)
        {
            head = head->next;
            tail = tail->prv;
        }
        else
        {
            sym_check = 0;
            printf("List is not symmetrical\n");
            break;
        }
    }
    if(sym_check)
        printf("List is symmetrical\n");
}