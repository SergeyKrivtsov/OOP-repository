#include "double_linked_list.h"

// Створення порожнього списку
Node* createList() {
    return nullptr;
}

// Вставка в початок списку
void insertAtHead(Node*& head, int value) {
    Node* newNode = new Node{ value, nullptr, nullptr };
    if (head != nullptr) {
        head->prev = newNode;
    }
    newNode->next = head;
    head = newNode;
}

// Вставка в кінець списку
void insertAtTail(Node*& head, int value) {
    Node* newNode = new Node{ value, nullptr, nullptr };
    if (head == nullptr) {
        head = newNode;
        return;
    }

    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// Вставка після заданого елемента
void insertAfter(Node* head, int target, int value) {
    Node* temp = head;
    while (temp != nullptr && temp->data != target) {
        temp = temp->next;
    }

    if (temp != nullptr) {
        Node* newNode = new Node{ value, temp->next, temp };
        if (temp->next != nullptr) {
            temp->next->prev = newNode;
        }
        temp->next = newNode;
    }
}

// Вставка перед заданим елементом
void insertBefore(Node*& head, int target, int value) {
    if (head == nullptr) return;

    Node* temp = head;
    while (temp != nullptr && temp->data != target) {
        temp = temp->next;
    }

    if (temp != nullptr) {
        Node* newNode = new Node{ value, temp, temp->prev };
        if (temp->prev != nullptr) {
            temp->prev->next = newNode;
        }
        else {
            head = newNode;
        }
        temp->prev = newNode;
    }
}

// Видалення елемента
Node* deleteNode(Node*& head, int value) {
    Node* temp = head;
    while (temp != nullptr && temp->data != value) {
        temp = temp->next;
    }

    if (temp == nullptr) return nullptr;

    if (temp->prev != nullptr) {
        temp->prev->next = temp->next;
    }
    else {
        head = temp->next;
    }

    if (temp->next != nullptr) {
        temp->next->prev = temp->prev;
    }

    delete temp;
    return head;
}

// Виведення елементів списку в прямому порядку
void printForward(Node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

// Виведення елементів списку в зворотному порядку
void printBackward(Node* head) {
    if (head == nullptr) return;

    while (head->next != nullptr) {
        head = head->next;
    }

    while (head != nullptr) {
        cout << head->data << " ";
        head = head->prev;
    }
    cout << endl;
}

// Перевірка симетрії списку
bool isSymmetric(Node* head) {
    if (head == nullptr) return true;

    Node* tail = head;
    while (tail->next != nullptr) {
        tail = tail->next;
    }

    while (head != nullptr && tail != nullptr) {
        if (head->data != tail->data) return false;
        head = head->next;
        tail = tail->prev;
    }

    return true;
}
