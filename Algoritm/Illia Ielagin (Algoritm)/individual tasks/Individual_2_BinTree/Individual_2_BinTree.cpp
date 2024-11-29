#include <iostream>
#include <string>

using namespace std;

// Структура вузла дерева
struct Node {
    string value;
    Node* left;
    Node* right;

    Node(string val = "") {
        value = val;
        left = nullptr;
        right = nullptr;
    }
};

// Рекурсивна функція побудови дерева
void buildTree(Node*& root, const string& formula, int& pos) {
    bool restart = true;
    while (restart){
        restart = false;
        // Пропустити пробіли
        while (pos < formula.length() && formula[pos] == ' ') {
        pos++;
        }

        // Перевіряємо межу строки
        if (pos >= formula.length()) return;

        // Якщо поточний символ - число
        if (isdigit(formula[pos])) {
            string num;
            while (pos < formula.length() && isdigit(formula[pos])) {
                num += formula[pos++];
            }

            Node* newNode = new Node(num);
            if (root->value.empty()) {
                root->left = newNode;
            }
            else {
                root->right = newNode;
            }

            restart = true;
            continue;
        }

        // Якщо поточний символ - оператор
        if (formula[pos] == '+' || formula[pos] == '-' || formula[pos] == '*' || formula[pos] == '/') {
            root->value = formula[pos++];
            restart = true;
            continue;
        }

        // Якщо поточний символ - відкриваюча дужка '('
        if (formula[pos] == '(') {
            pos++;
            Node* newNode = new Node();
            if (root->value.empty()) {
                root->left = newNode;
            }
            else {
                root->right = newNode;
            }
            buildTree(newNode, formula, pos);
            restart = true;
            continue;
        }

        // Якщо поточний символ - закриваюча дужка ')'
        if (formula[pos] == ')') {
            pos++;
            return;
        }
    }
}

// Допоміжна функція для тестування (обхід дерева)
void printTree(Node* root, int depth = 0) {
    if (!root) return;
    printTree(root->right, depth + 1);
    cout << string(depth * 4, ' ') << root->value << endl;
    printTree(root->left, depth + 1);
}

// Функція для обчислення значення виразу з дерева
double evaluateTree(Node* root) {
    if (!root) {
        cout << "Errore: Wrong tree." << endl; // Дерево не повинно бути порожнім
        return -999999999;
    }

    // Якщо це лист (число)
    if (!root->left && !root->right) {
        return stod(root->value); // Конвертуємо рядок у число
    }

    // Рекурсивно обчислюємо ліву і праву частини дерева
    double leftValue = evaluateTree(root->left);
    double rightValue = evaluateTree(root->right);

    // Виконуємо операцію залежно від значення вузла
    if (root->value == "+") {
        return leftValue + rightValue;
    }
    else if (root->value == "-") {
        return leftValue - rightValue;
    }
    else if (root->value == "*") {
        return leftValue * rightValue;
    }
    else if (root->value == "/") {
        if (rightValue == 0) {
            cout << "Errore: Division by zero" << endl;
            return -999999999;
        }
        return leftValue / rightValue;
    }
    else {
        cout << "Unknown operator: " << root->value << endl; // Некоректний оператор
        return -999999999;
    }
}

// Функція для друку дерева у префіксній формі (Polish notation)
void printPrefix(Node* root) {
    if (!root) return;

    cout << root->value << " ";

    printPrefix(root->left);
    printPrefix(root->right);
}

// Функція для друку дерева у постфіксній формі (Reverse Polish notation)
void printPostfix(Node* root) {
    if (!root) return;

    printPostfix(root->left);
    printPostfix(root->right);

    cout << root->value << " ";
}

string readFormulaFromFile(const string& filename) {
    FILE* file = nullptr;
    fopen_s(&file, filename.c_str(), "r");  // Відкриваємо файл для читання (режим "r")

    if (!file) {  // Перевірка на помилку відкриття файлу
        cout << "Error opening file!" << endl;
        return ""; 
    }

    string formula;
    char ch;

    // Читаємо файл по символу
    while ((ch = fgetc(file)) != EOF) {
        formula += ch; 
    }

    fclose(file); 
    return formula; 
}

int main() {
    string filename = "formula.txt";  // Назва файлу, що містить формулу
    string formula = readFormulaFromFile(filename);  // Читаємо формулу з файлу

    Node* root = new Node();

    int position = 0;
    buildTree(root, formula, position);

    // Друк дерева
    cout << "The tree is built: " << endl;
    printTree(root);

    // Обчислення дерева
    double result = evaluateTree(root);
    cout << "Result of the expression: " << result << endl;

    // Друк у префіксній формі
    cout << "Prefix notation: ";
    printPrefix(root);
    cout << endl;

    // Друк у постфіксній формі
    cout << "Postfix notation: ";
    printPostfix(root);
    cout << endl;

    return 0;
}
