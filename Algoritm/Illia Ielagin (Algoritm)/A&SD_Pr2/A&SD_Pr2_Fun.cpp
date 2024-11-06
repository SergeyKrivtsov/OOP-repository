#include "A&SD_Pr2_Header.h"

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

void deleteNode(Node*& head, int position) {
    if (head == nullptr || position < 1) {
        cout << "Invalid position or empty list.\n";
        return;
    }
    Node* current = head;

    if (position == 1) {
        head = head->next;
        delete current;
        return;
    }

    Node* prev = nullptr;
    for (int i = 1; i < position && current != nullptr; ++i) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Position out of range.\n";
        return;
    }

    prev->next = current->next;
    delete current;
}

void insertBefore(Node*& head, int position, int value) {
    Node* newNode = new Node{ value, nullptr };

    if (position <= 1 || head == nullptr) {
        newNode->next = head;
        head = newNode;
        return;
    }

    Node* current = head;
    Node* prev = nullptr;

    for (int i = 1; i < position && current != nullptr; ++i) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr && prev != nullptr) {
        prev->next = newNode;
    }
    else {
        prev->next = newNode;
        newNode->next = current;
    }
}

void insertAfter(Node* head, int position, int value) {
    Node* current = head;
    for (int i = 1; i < position && current != nullptr; ++i) {
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Position out of range.\n";
        return;
    }

    Node* newNode = new Node{ value, current->next };
    current->next = newNode;
}

bool isEmpty(Node* head) {
    return head == nullptr;
}

void menu() {
    Node* head = nullptr;
    int choice, position, value;

    do {
        cout << "\nMenu:\n";
        cout << "1. Create list using formLIFO_1\n";
        cout << "2. Create list using formLIFO_2\n";
        cout << "3. Display list\n";
        cout << "4. Check if list is empty\n";
        cout << "5. Delete node at position\n";
        cout << "6. Insert before position\n";
        cout << "7. Insert after position\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            head = formLIFO_1();
            break;
        case 2:
            formLIFO_2(head);
            break;
        case 3:
            cout << "Current list: ";
            printList(head);
            break;
        case 4:
            cout << "Is the list empty? " << (isEmpty(head) ? "Yes" : "No") << endl;
            break;
        case 5:
            cout << "Enter position to delete: ";
            cin >> position;
            deleteNode(head, position);
            break;
        case 6:
            cout << "Enter position to insert before: ";
            cin >> position;
            cout << "Enter value to insert: ";
            cin >> value;
            insertBefore(head, position, value);
            break;
        case 7:
            cout << "Enter position to insert after: ";
            cin >> position;
            cout << "Enter value to insert: ";
            cin >> value;
            insertAfter(head, position, value);
            break;
        case 0:
            cout << "Exiting.\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);
}