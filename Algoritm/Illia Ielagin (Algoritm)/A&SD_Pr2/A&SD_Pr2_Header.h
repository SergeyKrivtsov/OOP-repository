#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* formLIFO_1();
void formLIFO_2(Node*& head);

void printList(Node* head);
void deleteNode(Node*& head, int position);
void insertBefore(Node*& head, int position, int value);
void insertAfter(Node* head, int position, int value);
bool isEmpty(Node* head);

void menu();
