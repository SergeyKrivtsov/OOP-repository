// Pr_AiSD_stacks.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

struct Node {
    int val;
    Node* next;
};

void push(Node** head, int r) {
    Node* tmp = new Node;
    tmp->val = r;
    tmp->next = *head;
    *head = tmp;
    delete tmp;
}

int pop(Node** head) {
    Node* prev = NULL;
    int val;
    if (head == NULL)exit(1);
    prev = (*head);
    val = prev->val;
    *head = (*head)->next;
    delete prev;
    return val;
}

void print(Node* head) {
    Node* tmp = head;
    if (head == NULL)exit(1);
    while (tmp != NULL) {
        cout << tmp->val << " ";
        tmp = tmp->next;
    }
    cout << endl;
}

int main()
{
    Node* node1 = new Node;
    int val1;
    int val2;
    cout << "Enter first value" << endl;
    cin >> val1;
    node1->val = val1;
    cout << "Enter second value";
    cin >> val2;
    push(&(node1->next), val2);
    print(node1);

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
