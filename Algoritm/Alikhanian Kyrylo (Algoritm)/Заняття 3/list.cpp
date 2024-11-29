#include "list.h"

// Функція для створення порожнього списку
Node* createEmptyList() {
    return nullptr;
}

// Функція для вставлення елемента в початок списку
void insertAtHead(Node*& head, int value) {
    Node* newNode = new Node{ value, head };
    head = newNode;
}

// Функція для вставлення елемента в кінець списку
void insertAtTail(Node*& head, int value) {
    Node* newNode = new Node{ value, nullptr };
    if (head == nullptr) {
        head = newNode;
    }
    else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Функція для вставлення елемента перед заданим
void insertBefore(Node*& head, int target, int value) {
    if (head == nullptr) return;

    if (head->data == target) {
        insertAtHead(head, value);
        return;
    }

    Node* temp = head;
    while (temp->next != nullptr && temp->next->data != target) {
        temp = temp->next;
    }

    if (temp->next != nullptr) {
        Node* newNode = new Node{ value, temp->next };
        temp->next = newNode;
    }
}

// Функція для вставлення елемента після заданого
void insertAfter(Node*& head, int target, int value) {
    Node* temp = findNode(head, target);
    if (temp != nullptr) {
        Node* newNode = new Node{ value, temp->next };
        temp->next = newNode;
    }
}

// Функція для видалення елемента зі списку
void deleteNode(Node*& head, int value) {
    if (head == nullptr) return;

    if (head->data == value) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* temp = head;
    while (temp->next != nullptr && temp->next->data != value) {
        temp = temp->next;
    }

    if (temp->next != nullptr) {
        Node* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
    }
}

// Функція для пошуку елемента за значенням
Node* findNode(Node* head, int value) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == value) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

// Функція для перевірки, чи є список порожнім
bool isEmpty(Node* head) {
    return head == nullptr;
}

// Функція для виведення всіх елементів списку
void printList(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}
