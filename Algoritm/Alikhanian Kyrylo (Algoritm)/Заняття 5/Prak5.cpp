#include "double_linked_list.h"

void showMenu() {
    cout << "Choose an option:\n";
    cout << "1. Insert element at the head\n";
    cout << "2. Insert element at the tail\n";
    cout << "3. Insert after a value\n";
    cout << "4. Insert before a value\n";
    cout << "5. Delete a value\n";
    cout << "6. Print list forward\n";
    cout << "7. Print list backward\n";
    cout << "8. Check if the list is symmetric\n";
    cout << "0. Exit\n";
}

int main() {
    Node* list = createList();
    int choice, value, target;

    while (true) {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value to insert at the head: ";
            cin >> value;
            insertAtHead(list, value);
            break;
        case 2:
            cout << "Enter value to insert at the tail: ";
            cin >> value;
            insertAtTail(list, value);
            break;
        case 3:
            cout << "Enter target value to insert after: ";
            cin >> target;
            cout << "Enter value to insert: ";
            cin >> value;
            insertAfter(list, target, value);
            break;
        case 4:
            cout << "Enter target value to insert before: ";
            cin >> target;
            cout << "Enter value to insert: ";
            cin >> value;
            insertBefore(list, target, value);
            break;
        case 5:
            cout << "Enter value to delete: ";
            cin >> value;
            list = deleteNode(list, value);
            break;
        case 6:
            cout << "List (forward): ";
            printForward(list);
            break;
        case 7:
            cout << "List (backward): ";
            printBackward(list);
            break;
        case 8:
            if (isSymmetric(list)) {
                cout << "The list is symmetric.\n";
            }
            else {
                cout << "The list is not symmetric.\n";
            }
            break;
        case 0:
            cout << "Exiting program.\n";
            return 0;
        default:
            cout << "Invalid option. Please try again.\n";
        }
    }
}
