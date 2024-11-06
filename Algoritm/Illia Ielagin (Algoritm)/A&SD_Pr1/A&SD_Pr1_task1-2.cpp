#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

// Перша функція, що повертає вказівник на голову списку
Node* formLIFO_1() {
    int n, value;
    Node* head = nullptr;
    Node* tail = nullptr;

    cout << "Enter the number of items in the list: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cout << "Enter the value of the element: ";
        cin >> value;

        Node* newNode = new Node{ value, nullptr };

        if (head == nullptr) {
            head = newNode;
        }
        else {
            tail->next = newNode;
        }
        tail = newNode;
    }
    return head;
}

// Друга функція, що формує голову списку за допомогою параметру
void formLIFO_2(Node*& head) {
    int n, value;
    Node* tail = nullptr;

    cout << "Enter the number of items in the list: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cout << "Enter the value of the element: ";
        cin >> value;

        Node* newNode = new Node{ value, nullptr };

        if (head == nullptr) {
            head = newNode;
        }
        else {
            tail->next = newNode;
        }
        tail = newNode;
    }
}

void printList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

int main() {
    Node* head1 = formLIFO_1();
    cout << "The list created by the first function: ";
    printList(head1);

    Node* head2 = nullptr;
    formLIFO_2(head2);
    cout << "The list created by the second function: ";
    printList(head2);

    return 0;
}
