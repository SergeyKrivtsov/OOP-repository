#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int val;
    struct Node *next;
}Node;

// Функція для додавання нового елемента в початок списку
void Push(Node **head, int v){
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->val = v;
    temp->next = (*head);
    (*head) = temp;
}
// Функція для виведення елементів списку
void Print(Node *head){
    Node *temp =  head;
    while(temp != NULL){
        printf("%d ", temp->val);
        temp = temp->next;
    }
    printf("\n");
}
// Функція для множення кожного елем. списку на число x
void Multiply(Node *head, int x) {
    Node *temp = head;
    while (temp != NULL) {
        temp->val *= x; // Множимо елемент на x
        temp = temp->next;
    }
}
// Функція для отримання n-го елем. списку
Node* GetNthElem(Node* head, int n) {
    int count = 0;
    while (count < n && head->next != NULL) {
        head = head->next;
        count++;
    }
    return head;
}

// Функція для вставки елемента на місце n
void Add(Node *head, int n, int v) {
    if (n == 0) {
        // Вставка в початок списку
        Push(&head, v);
        return;
    }

    Node *prev = GetNthElem(head, n - 2);

    // Проверяем, что мы корректно нашли элемент
    if (prev == NULL) {
        printf("Invalid position. Cannot insert at position %d.\n", n);
        return;
    }

    // Створюємо новий вузел для вставки
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->val = v;

    // Вставляємо новий елемент на потрібне місце
    new_node->next = prev->next;
    prev->next = new_node;
}
// Функція для видалення елемента з позиції n
int Delete(Node **head, int n){

    Node *temp = GetNthElem(*head, n-2);
    Node *elm  = temp->next;
    int val = elm->val;

    temp->next = elm->next;
    free(elm);
    return val;
}


int main()
{
    int v, n;
    int x;
    int ins_n, new_v;
    int del_n, del_e;
    int choice;
    Node *head = NULL;

    // Введення довжини списку
    printf("Enter list length n \n");
    scanf("%d", &n);
    printf("Enter values:\n");

    // Введення елементів
    for (int i = 0; i < n; i++) {
        printf("Enter value %d: ", i + 1);
        scanf("%d", &v);
        Push(&head, v); // Додаємо на початок списку
    }
    // Виведення елементів списку
    printf("Elements:\n");
    Print(head);

    do {
        printf("1 - Insert an element\n2 - Delete an element\n0 - Exit\n");

        scanf("%d", &choice);

        switch(choice) {
            case 0:
                printf("Exiting\n");
                break;

            case 1:
                // Введення позиції та значення для вставки
                printf("Enter position to insert a new element:\n");
                scanf("%d", &ins_n);
                printf("Enter value to insert:\n");
                scanf("%d", &new_v);

                // Вставка елемента на позицію ins_n
                Add(head, ins_n, new_v);

                // Виведення списку після вставки
                printf("Elements after insertion:\n");
                Print(head);
                break;

            case 2:
                // Введення позиції для видалення
                printf("Enter position to delete an element:\n");
                scanf("%d", &del_n);

                // Видалення елемента з позиції del_n
                del_e = Delete(&head, del_n);
                printf("deleted element: %d\n", del_e);

                // Виведення списку після видалення
                printf("Elements after deletion:\n");
                Print(head);
                break;

            default:
                printf("Error! Enter 1 or 0.\n");
                break;
        }

    } while(choice != 0);

    // Введення множника x
    printf("Enter multiplier x:\n");
    scanf("%d", &x);

    // Множення всіх елементів на x
    Multiply(head, x);
    printf("Elements after multiplication:\n");
    Print(head);

    return 0;
}