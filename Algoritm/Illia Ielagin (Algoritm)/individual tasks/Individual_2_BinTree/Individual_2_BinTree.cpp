#include <iostream>
#include <string>

using namespace std;

// ��������� ����� ������
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

// ���������� ������� �������� ������
void buildTree(Node*& root, const string& formula, int& pos) {
    bool restart = true;
    while (restart){
        restart = false;
        // ���������� ������
        while (pos < formula.length() && formula[pos] == ' ') {
        pos++;
        }

        // ���������� ���� ������
        if (pos >= formula.length()) return;

        // ���� �������� ������ - �����
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

        // ���� �������� ������ - ��������
        if (formula[pos] == '+' || formula[pos] == '-' || formula[pos] == '*' || formula[pos] == '/') {
            root->value = formula[pos++];
            restart = true;
            continue;
        }

        // ���� �������� ������ - ���������� ����� '('
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

        // ���� �������� ������ - ���������� ����� ')'
        if (formula[pos] == ')') {
            pos++;
            return;
        }
    }
}

// �������� ������� ��� ���������� (����� ������)
void printTree(Node* root, int depth = 0) {
    if (!root) return;
    printTree(root->right, depth + 1);
    cout << string(depth * 4, ' ') << root->value << endl;
    printTree(root->left, depth + 1);
}

// ������� ��� ���������� �������� ������ � ������
double evaluateTree(Node* root) {
    if (!root) {
        cout << "Errore: Wrong tree." << endl; // ������ �� ������� ���� �������
        return -999999999;
    }

    // ���� �� ���� (�����)
    if (!root->left && !root->right) {
        return stod(root->value); // ���������� ����� � �����
    }

    // ���������� ���������� ��� � ����� ������� ������
    double leftValue = evaluateTree(root->left);
    double rightValue = evaluateTree(root->right);

    // �������� �������� ������� �� �������� �����
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
        cout << "Unknown operator: " << root->value << endl; // ����������� ��������
        return -999999999;
    }
}

// ������� ��� ����� ������ � ��������� ���� (Polish notation)
void printPrefix(Node* root) {
    if (!root) return;

    cout << root->value << " ";

    printPrefix(root->left);
    printPrefix(root->right);
}

// ������� ��� ����� ������ � ���������� ���� (Reverse Polish notation)
void printPostfix(Node* root) {
    if (!root) return;

    printPostfix(root->left);
    printPostfix(root->right);

    cout << root->value << " ";
}

string readFormulaFromFile(const string& filename) {
    FILE* file = nullptr;
    fopen_s(&file, filename.c_str(), "r");  // ³�������� ���� ��� ������� (����� "r")

    if (!file) {  // �������� �� ������� �������� �����
        cout << "Error opening file!" << endl;
        return ""; 
    }

    string formula;
    char ch;

    // ������ ���� �� �������
    while ((ch = fgetc(file)) != EOF) {
        formula += ch; 
    }

    fclose(file); 
    return formula; 
}

int main() {
    string filename = "formula.txt";  // ����� �����, �� ������ �������
    string formula = readFormulaFromFile(filename);  // ������ ������� � �����

    Node* root = new Node();

    int position = 0;
    buildTree(root, formula, position);

    // ���� ������
    cout << "The tree is built: " << endl;
    printTree(root);

    // ���������� ������
    double result = evaluateTree(root);
    cout << "Result of the expression: " << result << endl;

    // ���� � ��������� ����
    cout << "Prefix notation: ";
    printPrefix(root);
    cout << endl;

    // ���� � ���������� ����
    cout << "Postfix notation: ";
    printPostfix(root);
    cout << endl;

    return 0;
}
