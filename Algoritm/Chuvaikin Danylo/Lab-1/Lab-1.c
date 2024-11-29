/*
Завдання 1. Напишіть дві функції для створення списків за
даними, введеними з клавіатури.
Перша функція повертає вказівник на голову списку.
Друга – не повертає значення, а формує голову списку за допомогою
параметру.
Напишіть функцію виведення на екран елементів списку.
Напишіть головну функцію та протестуйте в ній всі функції.
pnode formLIFO_1 ( ... ) void formLIFO_2 ( ... )
{ {
... ...
} }
Завдання 2. Поміркуйте, як створити список так, щоб елементи в
списку були розміщені в тому ж порядку, що й при введенні з
клавіатури, а не в зворотному. Напишіть відповідну функцію.
Завдання 3.
Створіть список структур Футболіст (структура, яка створена в 1
практичній).
Реалізуйте функції:
визначити кращого форварда і вивести інформацію про нього;
вивести відомості про футболістів, які зіграли не менше 5-ти
ігор.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Завдання 1
// Функція formLIFO_1 повертає голову списку (для LIFO-списку)
Node* formLIFO_1() {
    Node* head = NULL;
    int data, choice;
    do {
        printf("Enter data for new element: ");
        scanf("%d", &data);

        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data = data;
        new_node->next = head;
        head = new_node;

        printf("Add another element? (0 - No, 1 - Yes): ");
        scanf("%d", &choice);
    } while (choice == 1);
    return head;
}

// Функція formLIFO_2 формує список, використовуючи параметр для голови
void formLIFO_2(Node** head_ref) {
    int data, choice;
    do {
        printf("Enter data for new element: ");
        scanf("%d", &data);

        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data = data;
        new_node->next = *head_ref;
        *head_ref = new_node;

        printf("Add another element? (0 - No, 1 - Yes): ");
        scanf("%d", &choice);
    } while (choice == 1);
}

// Функція для виведення списку
void printList(Node* head) {
    Node* temp = head;
    printf("List: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Завдання 2
// Функція формування FIFO-списку
Node* formFIFO() {
    Node* head = NULL;
    Node* tail = NULL;
    int data, choice;
    do {
        printf("Enter data for new element: ");
        scanf("%d", &data);
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data = data;
        new_node->next = NULL;

        if (head == NULL) {
            head = new_node;
        } else {
            tail->next = new_node;
        }
        tail = new_node;
        printf("Add another element? (0 - No, 1 - Yes): ");
        scanf("%d", &choice);
    } while (choice == 1);
    return head;
}

// Завдання 3
#define MAX_TEXT_SIZE 100
typedef enum { Goalkeeper, Midfielder, Striker, Centre_forward, Winger } amplua;
typedef struct {
    char surname[MAX_TEXT_SIZE];
    int age;
    amplua fb_amplua;
    int amount_of_games;
    int amount_of_goals;
} Footballer;

// Функція для додавання футболістів
void add_players(Footballer** team, int* amount) {
    int status = 0;
    printf("Please, enter footballers:\n");
    do {
        *team = (Footballer*)realloc(*team, (*amount + 1) * sizeof(Footballer));
        printf("Please, enter the surname of %d's footballer --> ", *amount + 1);
        getchar();
        fgets((*team)[*amount].surname, MAX_TEXT_SIZE, stdin);
        (*team)[*amount].surname[strcspn((*team)[*amount].surname, "\n")] = '\0';

        printf("Please, enter the age of %d's footballer --> ", *amount + 1);
        scanf("%d", &(*team)[*amount].age);

        printf("Please, enter the amplua of %d's footballer\n0 - Goalkeeper\n1 - Midfielder\n2 - Striker\n3 - Centre_forward\n4 - Winger\n--> ", *amount + 1);
        int temp_pos;
        scanf("%d", &temp_pos);
        (*team)[*amount].fb_amplua = (amplua)temp_pos;

        printf("Please, enter the amount_of_games of %d's footballer --> ", *amount + 1);
        scanf("%d", &(*team)[*amount].amount_of_games);

        printf("Please, enter the amount_of_goals of %d's footballer --> ", *amount + 1);
        scanf("%d", &(*team)[*amount].amount_of_goals);

        printf("Do you want to enter one more footballer? (0 - Yes, Other - No): ");
        scanf("%d", &status);
        (*amount)++;
    } while (status == 0);
}

// Функція для визначення кращого форварда
void best_forward(Footballer* team, int amount) {
    int max_goals_index = -1;
    for (int i = 0; i < amount; i++) {
        if (team[i].fb_amplua == Striker || team[i].fb_amplua == Centre_forward) {
            if (max_goals_index == -1 || team[i].amount_of_goals > team[max_goals_index].amount_of_goals) {
                max_goals_index = i;
            }
        }
    }
    if (max_goals_index != -1) {
        printf("Best forward:\nSurname: %s\nAge: %d\nAmplua: %d\nGames: %d\nGoals: %d\n",
               team[max_goals_index].surname, team[max_goals_index].age,
               team[max_goals_index].fb_amplua, team[max_goals_index].amount_of_games,
               team[max_goals_index].amount_of_goals);
    } else {
        printf("No forward found.\n");
    }
}

// Функція для виведення футболістів, які зіграли не менше 5-ти ігор
void players_with_min_games(Footballer* team, int amount) {
    printf("Footballers with 5 or more games:\n");
    for (int i = 0; i < amount; i++) {
        if (team[i].amount_of_games >= 5) {
            printf("Surname: %s\nAge: %d\nAmplua: %d\nGames: %d\nGoals: %d\n",
                   team[i].surname, team[i].age, team[i].fb_amplua, team[i].amount_of_games, team[i].amount_of_goals);
        }
    }
}

int main() {
    // Тестування завдань 1 і 2
    Node* head1 = formLIFO_1();
    printf("LIFO List (formLIFO_1): ");
    printList(head1);
    
    Node* head2 = NULL;
    formLIFO_2(&head2);
    printf("LIFO List (formLIFO_2): ");
    printList(head2);

    Node* fifo_head = formFIFO();
    printf("FIFO List: ");
    printList(fifo_head);

    // Тестування завдання 3
    int fb_amount = 0;
    Footballer* fb_team = NULL;
    add_players(&fb_team, &fb_amount);

    best_forward(fb_team, fb_amount);
    players_with_min_games(fb_team, fb_amount);

    free(fb_team);

    // Звільнення пам'яті для списків
    while (head1) { Node* temp = head1; head1 = head1->next; free(temp); }
    while (head2) { Node* temp = head2; head2 = head2->next; free(temp); }
    while (fifo_head) { Node* temp = fifo_head; fifo_head = fifo_head->next; free(temp); }
    return 0;
}
