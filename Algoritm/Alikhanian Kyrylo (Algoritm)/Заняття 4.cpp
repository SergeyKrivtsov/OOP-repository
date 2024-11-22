#include <iostream>
using namespace std;

// Структура для елемента списку
struct Node {
    int data;
    Node* next;
};

// Функція для створення порожнього списку
Node* createEmptyList() {
    return nullptr;
}

// Рекурсивна функція для вставлення елемента в упорядкований список
Node* insertOrdered(Node* head, int value) {
    if (head == nullptr || head->data >= value) {
        Node* newNode = new Node{ value, head };
        return newNode;
    }
    head->next = insertOrdered(head->next, value);
    return head;
}

// Рекурсивна функція для вставлення елемента в початок списку
Node* insertAtHead(Node* head, int value) {
    Node* newNode = new Node{ value, head };
    return newNode;
}

// Рекурсивна функція для вставлення елемента в кінець списку
Node* insertAtTail(Node* head, int value) {
    if (head == nullptr) {
        Node* newNode = new Node{ value, nullptr };
        return newNode;
    }
    head->next = insertAtTail(head->next, value);
    return head;
}

// Рекурсивна функція для вставлення елемента перед заданим
Node* insertBefore(Node* head, int target, int value) {
    if (head == nullptr) return nullptr;

    if (head->data == target) {
        Node* newNode = new Node{ value, head };
        return newNode;
    }

    head->next = insertBefore(head->next, target, value);
    return head;
}

// Рекурсивна функція для вставлення елемента після заданого
Node* insertAfter(Node* head, int target, int value) {
    if (head == nullptr) return nullptr;

    if (head->data == target) {
        Node* newNode = new Node{ value, head->next };
        head->next = newNode;
        return head;
    }

    head->next = insertAfter(head->next, target, value);
    return head;
}

// Рекурсивна функція для видалення елемента зі списку
Node* deleteNode(Node* head, int value) {
    if (head == nullptr) return nullptr;

    if (head->data == value) {
        Node* temp = head->next;
        delete head;
        return temp;
    }

    head->next = deleteNode(head->next, value);
    return head;
}

// Рекурсивна функція для пошуку елемента за значенням
Node* findNode(Node* head, int value) {
    if (head == nullptr || head->data == value) return head;
    return findNode(head->next, value);
}

// Рекурсивна функція для перевірки, чи є список порожнім
bool isEmpty(Node* head) {
    return head == nullptr;
}

// Рекурсивна функція для виведення всіх елементів списку
void printList(Node* head) {
    if (head == nullptr) return;
    cout << head->data << " ";
    printList(head->next);
}

// Функція для відображення меню
void showMenu() {
    cout << "Choose an option:\n";
    cout << "1. Insert element in an ordered list\n";
    cout << "2. Insert at the head\n";
    cout << "3. Insert at the tail\n";
    cout << "4. Insert before a value\n";
    cout << "5. Insert after a value\n";
    cout << "6. Delete a value\n";
    cout << "7. Find a value\n";
    cout << "8. Check if list is empty\n";
    cout << "9. Print list\n";
    cout << "0. Exit\n";
}

// Головна функція
int main() {
    Node* list = createEmptyList();  // Початковий порожній список
    int choice, value, target;

    while (true) {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value to insert in ordered list: ";
            cin >> value;
            list = insertOrdered(list, value);
            break;
        case 2:
            cout << "Enter value to insert at the head: ";
            cin >> value;
            list = insertAtHead(list, value);
            break;
        case 3:
            cout << "Enter value to insert at the tail: ";
            cin >> value;
            list = insertAtTail(list, value);
            break;
        case 4:
            cout << "Enter target value to insert before: ";
            cin >> target;
            cout << "Enter value to insert: ";
            cin >> value;
            list = insertBefore(list, target, value);
            break;
        case 5:
            cout << "Enter target value to insert after: ";
            cin >> target;
            cout << "Enter value to insert: ";
            cin >> value;
            list = insertAfter(list, target, value);
            break;
        case 6:
            cout << "Enter value to delete: ";
            cin >> value;
            list = deleteNode(list, value);
            break;
        case 7:
            cout << "Enter value to find: ";
            cin >> value;
            if (findNode(list, value)) {
                cout << "Value found in the list.\n";
            }
            else {
                cout << "Value not found.\n";
            }
            break;
        case 8:
            if (isEmpty(list)) {
                cout << "The list is empty.\n";
            }
            else {
                cout << "The list is not empty.\n";
            }
            break;
        case 9:
            cout << "List: ";
            printList(list);
            cout << endl;
            break;
        case 0:
            cout << "Exiting program.\n";
            return 0;
        default:
            cout << "Invalid option. Please try again.\n";
        }
    }
}
