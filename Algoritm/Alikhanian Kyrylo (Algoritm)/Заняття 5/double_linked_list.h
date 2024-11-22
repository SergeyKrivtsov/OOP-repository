#pragma once
#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include <iostream>
using namespace std;

// Структура для елемента двоспрямованого списку
struct Node {
    int data;
    Node* next;
    Node* prev;
};

// Функції для роботи з двоспрямованим списком
Node* createList();  // Створення порожнього списку
void insertAtHead(Node*& head, int value);  // Вставка в початок списку
void insertAtTail(Node*& head, int value);  // Вставка в кінець списку
void insertAfter(Node* head, int target, int value);  // Вставка після елемента
void insertBefore(Node*& head, int target, int value);  // Вставка перед елементом
Node* deleteNode(Node*& head, int value);  // Видалення елемента
void printForward(Node* head);  // Виведення елементів списку в прямому порядку
void printBackward(Node* head);  // Виведення елементів списку в зворотному порядку
bool isSymmetric(Node* head);  // Перевірка симетрії списку

#endif
