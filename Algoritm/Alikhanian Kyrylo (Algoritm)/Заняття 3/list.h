#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <string>
using namespace std;

// ��������� ��� �������� ������
struct Node {
    int data;
    Node* next;
};

// ������� ��� ��������� ���������� ������
Node* createEmptyList();

// ������� ��� ���������� �������� � ������� ������
void insertAtHead(Node*& head, int value);

// ������� ��� ���������� �������� � ����� ������
void insertAtTail(Node*& head, int value);

// ������� ��� ���������� �������� ����� �������
void insertBefore(Node*& head, int target, int value);

// ������� ��� ���������� �������� ���� ��������
void insertAfter(Node*& head, int target, int value);

// ������� ��� ��������� �������� � ������
void deleteNode(Node*& head, int value);

// ������� ��� ������ �������� �� ���������
Node* findNode(Node* head, int value);

// ������� ��� ��������, �� � ������ �������
bool isEmpty(Node* head);

// ������� ��� ��������� ��� �������� ������
void printList(Node* head);

#endif
#pragma once
