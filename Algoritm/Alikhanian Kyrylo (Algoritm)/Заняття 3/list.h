#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <string>
using namespace std;

// Структура для елемента списку
struct Node {
    int data;
    Node* next;
};

// Функція для створення порожнього списку
Node* createEmptyList();

// Функція для вставлення елемента в початок списку
void insertAtHead(Node*& head, int value);

// Функція для вставлення елемента в кінець списку
void insertAtTail(Node*& head, int value);

// Функція для вставлення елемента перед заданим
void insertBefore(Node*& head, int target, int value);

// Функція для вставлення елемента після заданого
void insertAfter(Node*& head, int target, int value);

// Функція для видалення елемента зі списку
void deleteNode(Node*& head, int value);

// Функція для пошуку елемента за значенням
Node* findNode(Node* head, int value);

// Функція для перевірки, чи є список порожнім
bool isEmpty(Node* head);

// Функція для виведення всіх елементів списку
void printList(Node* head);

#endif
#pragma once
