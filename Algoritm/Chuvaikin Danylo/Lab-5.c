/*
Навчитися обходити бінарне дерево:
	В прямому порядку або зверху вниз.
	В симетричному порядку або зліва направо.
	В зворотному порядку або знизу уверх.
	1. Напишіть функцію для створення довільного бінарного дерева за
даними, введеними з клавіатури.
	2. Напишіть функції обходу бінарного дерева в прямому,
симетричному та зворотному порядках.
	3. Напишіть функцію, яка повертає кількість елементів дерева, що
дорівнюють значенню, заданому в параметрі функції.
*/

#include <stdio.h>
#include <stdlib.h>
//Структура для вузла бінарного дерева
struct Node {
    //Значення вузла
    int data;
    //Вказівник на лівий вузол
    struct Node* left;
    //Вказівник на правий вузол
    struct Node* right;
};
//Функція створення вузла
struct Node* new_Node(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
struct Node* fill_Node(struct Node* node, int data) {
    if (node == NULL) 
        return new_Node(data);
    else if (data < node->data)
        node->left = fill_Node(node->left, data);
    else if (data >= node->data)
        node->right = fill_Node(node->right, data);
    return node;
}

// Прямий обхід
void gerade_Order(struct Node* node) {
    if (node == NULL)
        return;
    printf("%d ", node->data);
    gerade_Order(node->left);
    gerade_Order(node->right);
}
// Симметричний обхід
void symmertic_Order(struct Node* node) {
    if (node == NULL)
        return;
    symmertic_Order(node->left);
    printf("%d ", node->data);
    symmertic_Order(node->right);
}
// Обернений обхід
void reverse_Order(struct Node* node) {
    if (node == NULL)
        return;
    reverse_Order(node->left);
    reverse_Order(node->right);
    printf("%d ", node->data);
}
int countValue(struct Node* root, int value) {
    if (root == NULL) 
        return 0;
    int count;
    if(root->data == value){
        count = 1;
    }
    else{
        count = 0;
    }
    count += countValue(root->left, value);
    count += countValue(root->right, value);
    return count;
}
int main()
{
    //Створюємо корінь
    struct Node* root = NULL;
    int value;
    while (1) {
        printf("Enter value\n|\nv\n");
        scanf("%d", &value);
        if (value == 0)
            break;
        root = fill_Node(root, value);
    }
    gerade_Order(root);
    printf("\n");
    symmertic_Order(root);
    printf("\n");
    reverse_Order(root);
    printf("\n");
    
    printf("Count value is %d\n", countValue(root, 8));
    printf("Count value is %d\n", countValue(root, 11));
    printf("Count value is %d\n", countValue(root, 1));
    printf("Count value is %d\n", countValue(root, 800));
    return 0;
}