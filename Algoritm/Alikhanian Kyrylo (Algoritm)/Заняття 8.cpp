#include <iostream>
#include <stack>
#include <cctype>
#include <string>
#include <algorithm>
using namespace std;

// Структура для вузла АВЛ-дерева
struct AVLNode {
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int value) : key(value), left(nullptr), right(nullptr), height(1) {}
};

// Структура для дерева виразу
struct ExprNode {
    char value;
    ExprNode* left;
    ExprNode* right;

    ExprNode(char val) : value(val), left(nullptr), right(nullptr) {}
};

// Функція для отримання висоти вузла
int height(AVLNode* node) {
    if (node == nullptr) return 0;
    return node->height;
}

// Функція для отримання балансу вузла (різниця висот лівого та правого піддерева)
int balanceFactor(AVLNode* node) {
    if (node == nullptr) return 0;
    return height(node->left) - height(node->right);
}

// Праве обертання
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Ліве обертання
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Вставка елемента в АВЛ-дерево з балансуванням
AVLNode* insert(AVLNode* node, int key) {
    if (node == nullptr) return new AVLNode(key);

    if (key < node->key) {
        node->left = insert(node->left, key);
    }
    else if (key > node->key) {
        node->right = insert(node->right, key);
    }
    else {
        return node;  // Ключ вже існує в дереві
    }

    node->height = max(height(node->left), height(node->right)) + 1;

    int balance = balanceFactor(node);

    // Лівий лівий випадок
    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }

    // Правий правий випадок
    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }

    // Лівий правий випадок
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Правий лівий випадок
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Видалення вузла з АВЛ дерева
AVLNode* deleteNode(AVLNode* root, int key) {
    if (root == nullptr) return root;

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    }
    else {
        if (root->left == nullptr || root->right == nullptr) {
            AVLNode* temp = root->left ? root->left : root->right;
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            }
            else {
                *root = *temp;
            }
            delete temp;
        }
        else {
            AVLNode* temp = root->right;
            while (temp->left != nullptr) temp = temp->left;

            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == nullptr) return root;

    root->height = max(height(root->left), height(root->right)) + 1;

    int balance = balanceFactor(root);

    if (balance > 1 && balanceFactor(root->left) >= 0)
        return rightRotate(root);
    if (balance < -1 && balanceFactor(root->right) <= 0)
        return leftRotate(root);
    if (balance > 1 && balanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && balanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Функція для виведення дерева у симетричному порядку
void inorder(AVLNode* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

// Функція для перевірки, чи є символ оператором
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Функція для створення дерева з префіксного виразу
ExprNode* constructTree(const string& expr) {
    stack<ExprNode*> st;

    for (int i = expr.length() - 1; i >= 0; i--) {
        char c = expr[i];

        if (isOperator(c)) {
            ExprNode* node = new ExprNode(c);
            node->left = st.top(); st.pop();
            node->right = st.top(); st.pop();
            st.push(node);
        }
        else if (isdigit(c)) {
            st.push(new ExprNode(c));
        }
    }

    return st.top();
}

// Функція для виведення дерева (постфіксна нотація)
void postorder(ExprNode* root) {
    if (root != nullptr) {
        postorder(root->left);
        postorder(root->right);
        cout << root->value << " ";
    }
}

// Головна функція
int main() {
    // АВЛ дерево
    AVLNode* root = nullptr;
    int data[] = { 12, 8, 7, 9, 14, 11, 10, 50, 70, 90, 25, 20, 30, 80, 25, 48, 77, 16, 10, 20, 62 };
    for (int i = 0; i < 21; i++) {
        root = insert(root, data[i]);
    }

    cout << "Inorder traversal of the AVL tree: ";
    inorder(root);
    cout << endl;

    // Видалення елемента з АВЛ дерева
    root = deleteNode(root, 50);
    cout << "Inorder traversal after deletion of 50: ";
    inorder(root);
    cout << endl;

    // Створення дерева арифметичного виразу
    string expr = "*+23+45";  // Префіксний вираз для (2+3)*(4+5)

    ExprNode* exprRoot = constructTree(expr);

    cout << "Postorder traversal of the expression tree: ";
    postorder(exprRoot);
    cout << endl;

    return 0;
}
