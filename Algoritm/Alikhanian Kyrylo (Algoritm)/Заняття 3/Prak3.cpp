#include "list.h"

void showMenu() {
    cout << "Choose an option:\n";
    cout << "1. Insert at the head\n";
    cout << "2. Insert at the tail\n";
    cout << "3. Insert before a value\n";
    cout << "4. Insert after a value\n";
    cout << "5. Delete a value\n";
    cout << "6. Find a value\n";
    cout << "7. Check if list is empty\n";
    cout << "8. Print list\n";
    cout << "0. Exit\n";
}

int main() {
    Node* list = createEmptyList();  // Початковий порожній список
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
            cout << "Enter target value to insert before: ";
            cin >> target;
            cout << "Enter value to insert: ";
            cin >> value;
            insertBefore(list, target, value);
            break;
        case 4:
            cout << "Enter target value to insert after: ";
            cin >> target;
            cout << "Enter value to insert: ";
            cin >> value;
            insertAfter(list, target, value);
            break;
        case 5:
            cout << "Enter value to delete: ";
            cin >> value;
            deleteNode(list, value);
            break;
        case 6:
            cout << "Enter value to find: ";
            cin >> value;
            if (findNode(list, value)) {
                cout << "Value found in the list.\n";
            }
            else {
                cout << "Value not found.\n";
            }
            break;
        case 7:
            if (isEmpty(list)) {
                cout << "The list is empty.\n";
            }
            else {
                cout << "The list is not empty.\n";
            }
            break;
        case 8:
            cout << "List: ";
            printList(list);
            break;
        case 0:
            cout << "Exiting program.\n";
            return 0;
        default:
            cout << "Invalid option. Please try again.\n";
        }
    }
}
