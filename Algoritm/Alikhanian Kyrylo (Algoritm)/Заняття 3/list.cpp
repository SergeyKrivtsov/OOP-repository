#include "list.h"

// ������� ��� ��������� ���������� ������
Node* createEmptyList() {
    return nullptr;
}

// ������� ��� ���������� �������� � ������� ������
void insertAtHead(Node*& head, int value) {
    Node* newNode = new Node{ value, head };
    head = newNode;
}

// ������� ��� ���������� �������� � ����� ������
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

// ������� ��� ���������� �������� ����� �������
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

// ������� ��� ���������� �������� ���� ��������
void insertAfter(Node*& head, int target, int value) {
    Node* temp = findNode(head, target);
    if (temp != nullptr) {
        Node* newNode = new Node{ value, temp->next };
        temp->next = newNode;
    }
}

// ������� ��� ��������� �������� � ������
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

// ������� ��� ������ �������� �� ���������
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

// ������� ��� ��������, �� � ������ �������
bool isEmpty(Node* head) {
    return head == nullptr;
}

// ������� ��� ��������� ��� �������� ������
void printList(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}
