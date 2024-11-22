#include <iostream>
using namespace std;

// Структура для елемента бінарного дерева
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Функція для створення дерева
Node* createTree() {
    int value;
    cout << "Enter value for node (enter -1 for no node): ";
    cin >> value;

    if (value == -1) return nullptr;

    Node* newNode = new Node(value);

    cout << "Enter left child of " << value << ":\n";
    newNode->left = createTree();

    cout << "Enter right child of " << value << ":\n";
    newNode->right = createTree();

    return newNode;
}

// Прямий обхід (Pre-order: root, left, right)
void preorderTraversal(Node* root) {
    if (root == nullptr) return;
    cout << root->data << " ";  // Вивести корінь
    preorderTraversal(root->left);  // Пройти ліве піддерево
    preorderTraversal(root->right);  // Пройти праве піддерево
}

// Симетричний обхід (In-order: left, root, right)
void inorderTraversal(Node* root) {
    if (root == nullptr) return;
    inorderTraversal(root->left);  // Пройти ліве піддерево
    cout << root->data << " ";  // Вивести корінь
    inorderTraversal(root->right);  // Пройти праве піддерево
}

// Зворотний обхід (Post-order: left, right, root)
void postorderTraversal(Node* root) {
    if (root == nullptr) return;
    postorderTraversal(root->left);  // Пройти ліве піддерево
    postorderTraversal(root->right);  // Пройти праве піддерево
    cout << root->data << " ";  // Вивести корінь
}

// Функція для підрахунку елементів, що дорівнюють заданому значенню
int countElements(Node* root, int value) {
    if (root == nullptr) return 0;

    int count = (root->data == value) ? 1 : 0;  // Якщо значення кореня дорівнює заданому, збільшуємо лічильник
    count += countElements(root->left, value);  // Рекурсивно шукаємо в лівому піддереві
    count += countElements(root->right, value);  // Рекурсивно шукаємо в правому піддереві

    return count;
}

// Головна функція з меню
int main() {
    Node* root = nullptr;
    int choice, value;

    // Створення бінарного дерева
    cout << "Create binary tree:\n";
    root = createTree();

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Pre-order traversal\n";
        cout << "2. In-order traversal\n";
        cout << "3. Post-order traversal\n";
        cout << "4. Count elements equal to a given value\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Pre-order traversal: ";
            preorderTraversal(root);
            cout << endl;
            break;
        case 2:
            cout << "In-order traversal: ";
            inorderTraversal(root);
            cout << endl;
            break;
        case 3:
            cout << "Post-order traversal: ";
            postorderTraversal(root);
            cout << endl;
            break;
        case 4:
            cout << "Enter value to count: ";
            cin >> value;
            cout << "Count of elements equal to " << value << ": ";
            cout << countElements(root, value) << endl;
            break;
        case 0:
            cout << "Exiting program.\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
