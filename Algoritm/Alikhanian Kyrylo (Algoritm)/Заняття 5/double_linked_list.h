#pragma once
#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include <iostream>
using namespace std;

// ��������� ��� �������� ��������������� ������
struct Node {
    int data;
    Node* next;
    Node* prev;
};

// ������� ��� ������ � �������������� �������
Node* createList();  // ��������� ���������� ������
void insertAtHead(Node*& head, int value);  // ������� � ������� ������
void insertAtTail(Node*& head, int value);  // ������� � ����� ������
void insertAfter(Node* head, int target, int value);  // ������� ���� ��������
void insertBefore(Node*& head, int target, int value);  // ������� ����� ���������
Node* deleteNode(Node*& head, int value);  // ��������� ��������
void printForward(Node* head);  // ��������� �������� ������ � ������� �������
void printBackward(Node* head);  // ��������� �������� ������ � ���������� �������
bool isSymmetric(Node* head);  // �������� ������ ������

#endif
