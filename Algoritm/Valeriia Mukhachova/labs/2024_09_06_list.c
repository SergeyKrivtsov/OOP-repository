//2024_09_06
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
int Put_before(Node **head, int info, int input_value);

int main()
{   
    Node *head = NULL;
    int v = 0;
    int del_v = 0;
    int input_v = 0;
    int input_before = 0;

    //add dynamic length instead and add checks that there aren't less or more elements

    int length = 5;

    printf("Please, input %d numbers\n", length);
    
    for (int i = 0; i < length; i++)
    {
        scanf("%d", &v);
        Push(&head, v);
    }

    Print(head);
    
    printf("which element you want to delete? numeration starts from 0\n");
    while (1)
    {
        scanf("%d", &del_v);
        if(del_v<0 || del_v>=length)
            printf("Please, try again and beware of the range - min - 0, max - %d\n", length-1);
    }

    int del_succ = Delete(&head, del_v);
    if(!del_succ)
        printf("Erorr of delete\n");
    else
        Print(head);


    printf("which element you want to add? input value\n");
    scanf("%d", &input_v);
    
    printf("before which element?numeration starts from 0\n");
    while (1)
    {
        scanf("%d", &input_before);
        if(input_before<0 || input_before>=length)
            printf("Please, try again and beware of the range - min - 0, max - %d\n", length-1);
    }

    del_succ = Put_before(&head, input_before, input_v);
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

int Put_before(Node **head, int info, int input_value)
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
        
        while (temp != NULL)
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

        }
           
    }
    return 0;
}
