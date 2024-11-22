#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

void Push(Node **head, int v) {
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->val = v;

    // Якщо список порожній, новий елемент вказує сам на себе
    if (*head == NULL) {
        temp->next = temp;
        *head = temp;
    } else {
        // Якщо список не порожній, шукаємо останній елемент
        Node *last = *head;
        while (last->next != *head) {
            last = last->next;
        }
        // Вставляємо новий елемент в початок списку
        temp->next = *head;
        last->next = temp;
        *head = temp; // Оновлюємо голову списку
    }
}

// Функція для виведення елементів списку
void Print(Node *head) {
    if (head == NULL) return;
    Node *temp = head;
    do {
        printf("%d ", temp->val);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

// Функція для видалення елемента
void DeleteNode(Node **head, Node *prev) {
    Node *del = prev->next;
    if (del == *head) {
        *head = del->next; // Якщо видаляємо голову, оновлюємо її
    }
        prev->next = del->next;
        free(del);
}

void CountingGame(Node **head, int d) {
    Node *current = *head;
    while (*head != NULL && (*head)->next != *head) {
        // Проходимо d-1 елементів
        for (int i = 1; i < d - 1; i++) {
            current = current->next;
        }

        // Видаляємо d-й елемент
        printf("Deleting element: %d\n", current->next->val);
        DeleteNode(head, current);

        // Оновлюємо current
        current = current->next;

        // Виводимо поточний список
        printf("Current List:\n");
        Print(*head);
    }
    // Виводимо останній елемент, що залишився
    if (*head != NULL) {
        printf("Last element is: %d\n", (*head)->val);
    }
}

int main() {
    int n, d;
    Node *head = NULL;

    // Введення довжини списку
    printf("Enter list length n: ");
    scanf("%d", &n);

    // Введення значень
    printf("Enter values:\n");
    for (int i = 0; i < n; i++) {
        int v;
        printf("Enter value %d: ", i + 1);
        scanf("%d", &v);
        Push(&head, v);
    }

    // Введення d (видалення кожного d-го елемента)
    printf("Enter the d (delete every d element): ");
    scanf("%d", &d);

    // Виведення початкового списку
    printf("List:\n");
    Print(head);

    // Виконання рахівнички
    CountingGame(&head, d);

    return 0;
}