#include "A&SD_Pr2_Header.h"

int main() {
    Node* head1 = formLIFO_1();
    cout << "The list created by the first function: ";
    printList(head1);

    /*
    Node* head2 = nullptr;
    formLIFO_2(head2);
    cout << "The list created by the second function: ";
    printList(head2);
    */

    cout << "Inserting 99 before position 2:\n";
    insertBefore(head1, 2, 99);
    printList(head1);

    cout << "Inserting 100 after position 3:\n";
    insertAfter(head1, 3, 100);
    printList(head1);

    cout << "Deleting node at position 2:\n";
    deleteNode(head1, 2);
    printList(head1);

    cout << "Is the list empty? " << (isEmpty(head1) ? "Yes" : "No") << endl;

    //menu();

    return 0;
}
