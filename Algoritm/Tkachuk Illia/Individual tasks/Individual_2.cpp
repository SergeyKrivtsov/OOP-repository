#include <iostream>
#include <string>
using namespace std;

struct Node {
    string value;
    Node* left;
    Node* right;

    Node(string val) : value(val), left(nullptr), right(nullptr) {}
};

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void applyOperator(Node* operands[], int& operandIndex, char operators[], int& operatorIndex) {
    Node* right = operands[operandIndex--];
    Node* left = operands[operandIndex--];
    char op = operators[operatorIndex--];
    Node* newNode = new Node(string(1, op));
    newNode->left = left;
    newNode->right = right;
    operands[++operandIndex] = newNode;
}

bool isValidExpression(const string& expression) {
    int balance = 0;
    bool expectOperand = true;

    for (size_t i = 0; i < expression.length(); ++i) {
        char c = expression[i];

        if (c == '(') {
            balance++;
            expectOperand = true;
        } 
        else if (c == ')') {
            balance--;
            if (balance < 0) return false;
            expectOperand = false;
        } 
        else if (isdigit(c)) {
            while (i < expression.length() && isdigit(expression[i])) i++;
            i--;
            expectOperand = false;
        } 
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            if (expectOperand) return false;

            if (i + 1 < expression.length() && expression[i + 1] != '(' && !isdigit(expression[i + 1])) {
                return false;
            }
            expectOperand = true;
        } 
        else {
            return false;
        }
    }

    return balance == 0 && !expectOperand;
}

Node* parseExpression(const string& expression) {
    Node* operands[100];
    char operators[100];
    int operandIndex = -1;
    int operatorIndex = -1;

    for (size_t i = 0; i < expression.length(); ++i) {
        char c = expression[i];
        if (isdigit(c)) {
            string num;
            while (i < expression.length() && isdigit(expression[i])) {
                num += expression[i++];
            }
            --i;
            operands[++operandIndex] = new Node(num);
        }
        else if (c == '(') {
            operators[++operatorIndex] = c;
        }
        else if (c == ')') {
            while (operatorIndex >= 0 && operators[operatorIndex] != '(') {
                applyOperator(operands, operandIndex, operators, operatorIndex);
            }
            operatorIndex--;
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (operatorIndex >= 0 && precedence(operators[operatorIndex]) >= precedence(c)) {
                applyOperator(operands, operandIndex, operators, operatorIndex);
            }
            operators[++operatorIndex] = c;
        }
    }

    while (operatorIndex >= 0) {
        applyOperator(operands, operandIndex, operators, operatorIndex);
    }

    return operands[0];
}

int calculate(Node* node) {
    if (!node->left && !node->right)
        return stoi(node->value);

    int leftVal = calculate(node->left);
    int rightVal = calculate(node->right);

    if (node->value == "+") return leftVal + rightVal;
    if (node->value == "-") return leftVal - rightVal;
    if (node->value == "*") return leftVal * rightVal;
    if (node->value == "/") return leftVal / rightVal;

    return 0;
}

void printStraight(Node* node) {
    if (!node) return;
    cout << node->value << " ";
    printStraight(node->left);
    printStraight(node->right);
}

void printReversed(Node* node) {
    if (!node) return;
    printReversed(node->left);
    printReversed(node->right);
    cout << node->value << " ";
}

void printTree(Node* node, int space = 0, int level = 0) {
    if (node == nullptr) return;

    int indent = 4;
    space += indent;

    printTree(node->right, space, level);

    cout << endl;
    for (int i = indent; i < space; i++)
        cout << " ";
    cout << node->value << endl;

    printTree(node->left, space, level);
}

void deleteTree(Node* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

int main() {
    string expressions[] = {
        "3+5",
        "(3+5)*2",
        "(3+5)*(2-1)",
        "((2+3)*4)-5",
        "10/(2+3)"
    };

for (int i = 0; i < 5; i++) {
    string expr = expressions[i];
    cout << "Проверка выражения: " << expr << endl;
    if (!isValidExpression(expr)) {
        cout << "Некорректное выражение!" << endl;
        cout << "------------------------" << endl;
        continue;
    }
    Node* solution = parseExpression(expr);
    cout << "Прямой польский запис: ";
    printStraight(solution);
    cout << "\nРезультат вычисления: " << calculate(solution) << endl;
    cout << "Зворотный польский запис: ";
    printReversed(solution);
    cout << "\nРезультат вычисления: " << calculate(solution) << endl;
    cout << "\nДерево выражения:\n";
    printTree(solution);
    cout << "------------------------" << endl;
    deleteTree(solution);
}
    return 0;
}
