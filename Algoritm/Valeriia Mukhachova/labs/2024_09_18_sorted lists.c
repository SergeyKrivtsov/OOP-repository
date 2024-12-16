//2024_09_18_sorted lists
#include <stdio.h>
#include <malloc.h>

typedef struct Node
{
    int val;
    struct Node *next;
}Node;

int Pop(Node **head);
void Print(Node *head);
void Push(Node **head, int v);
int Delete(Node **head, int info);
int Add_node(Node **head, int input_value);
int check_range(int left, int right);
void special_input(int *arr, int length);

int main()
{   
    Node *head = NULL;
    int del_v = 0;
    int input_v = 0;
    int input_before = 0;

    //add dynamic length instead and add checks that there aren't less or more elements

    printf("Please, enter the length of the list:\n");
    int length = check_range(1, __INT_MAX__);

    int *arr_nodes = (int*)malloc(length*sizeof(int));

    printf("Please, input %d numbers\n", length);
    
    special_input(arr_nodes, length);

    

    for (int i = 0; i < length; i++)
        printf("%d ", *(arr_nodes+i));
    printf("\n");

    int check = 0;

    Push(&head, *(arr_nodes));
    Print(head);

    for (int i = 1; i < length; i++)
    {
        check = Add_node(&head, *(arr_nodes+i));
        
        if (check == 1)
            printf("success\n");
        else
            printf("fail of add node\n");
        Print(head);
    }

    Print(head);
    
    printf("which element you want to delete? numeration starts from 1\n");
    del_v = check_range(1, length)-1;
    
    int del_succ = Delete(&head, del_v);
    if(!del_succ)
        printf("Erorr of delete\n");
    else
        Print(head);


    printf("which element you want to add? input value\n");
    input_v = check_range(-__INT_MAX__, __INT_MAX__);
    
    del_succ = Add_node(&head, input_v);

    if(!del_succ)
        printf("Erorr of add/n");
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

void Print(Node *head)
{
    if(head==NULL)
        printf("erorr of print/n");
    while (head != NULL)
    {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}

int Delete(Node **head, int info)
{
    Node *temp = (Node*)malloc(sizeof(Node));
    Node *prev = (Node*)malloc(sizeof(Node));
    int count = 0;

    if((*head)==NULL)
        return 0;
    if (info==0)
    {
        temp = *head;
        *head = (*head)->next; 
        return 1;
    }
    else
    {
        prev = *head;
        temp = prev->next;
        count++;
        
        while (temp != NULL)
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
        }
    }
    return 0;
}

//add a node on place to sort the list
int Add_node(Node **head, int input_value)
{
    if(head==NULL)
        return 0;
    Node *temp = (Node*)malloc(sizeof(Node));
    Node *prev = (Node*)malloc(sizeof(Node));
    Node *cur = (Node*)malloc(sizeof(Node));

    int count = 0;

    if ((*head)->val >= input_value)
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
        
        while (temp != NULL)
        {
            if (temp->val >= input_value && prev->val <= input_value)
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
            }
        }
           
    }
    if(temp==NULL&& prev->val<=input_value)
    {
        cur->val = input_value;
        cur->next = NULL;
        prev->next = cur;
        return 1;
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

        //перевіряє, що fgets щось отримав
        if((fgets(number, 30, stdin))==NULL) printf("Error of fgets\n");
        

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
    //int var = 0;
    int bad_input = 0;
    int i = 0;
    int count = 0;

    while(1)
    {
        //var = 0;
        count = 0;
        char number[100];
        bad_input = 0;
        i = 0;

        //перевіряє, що fgets щось отримав
        if((fgets(number, 100, stdin))==NULL) printf("Error of fgets\n");

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
            if (((number[i] - '0')<0||(number[i] - '0')>9)&&(number[i]!=' '))
            {    
                bad_input = 1;
                printf("You should only input numbers and space\n");
                break;
            }
            else
            {

                i = 0;
                while(number[i]==' ')
                    i++;    
    
                count = 0;
                while(number[i]!='\0'&&number[i]!='\n')
                {
                    *(arr+count)=0;
                    while (number[i]!=' '&&number[i]!='\0'&&number[i]!='\n')
                    {
                        //якщо це не буква або знак, переводить у число
                        *(arr+count) = *(arr+count)*10 + (number[i] - '0'); 
                        i++;
                    }
                    count++;
                    
                    while (number[i]==' ')
                    {
                        i++;
                    }
                    

                    if(count==length&&number[i]!='\n'&&number[i]!='\0')
                    {
                        while(number[i]!='\n'&&number[i]!='\0')
                        {
                            i++;
                            if(number[i]!=' '&&number[i]!='\n'&&number[i]!='\0')
                            {
                                bad_input = 1;
                                printf("Too many numbers\n");
                                break;
                            }
                        }
                    }
                }
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