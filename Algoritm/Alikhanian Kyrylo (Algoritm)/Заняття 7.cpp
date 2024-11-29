#include <iostream>
#include <string>
using namespace std;

// Структура для зберігання даних про студента
struct Student {
    string name;
    double grade;
};

// Структура для вузла бінарного дерева пошуку
struct Node {
    Student student;
    Node* left;
    Node* right;

    Node(Student s) : student(s), left(nullptr), right(nullptr) {}
};

// Функція для створення дерева пошуку
Node* insertNode(Node* root, Student student) {
    if (root == nullptr) {
        return new Node(student);
    }
    if (student.grade < root->student.grade) {
        root->left = insertNode(root->left, student);
    }
    else {
        root->right = insertNode(root->right, student);
    }
    return root;
}

// Функція для симетричного обходу дерева (In-order: лівий, корінь, правий)
void inorderTraversal(Node* root) {
    if (root == nullptr) return;
    inorderTraversal(root->left);
    cout << root->student.name << " - " << root->student.grade << endl;
    inorderTraversal(root->right);
}

// Функція для видалення вузла з дерева
Node* deleteNode(Node* root, double grade) {
    if (root == nullptr) return root;

    // Якщо оцінка студента менша, шукаємо в лівому піддереві
    if (grade < root->student.grade) {
        root->left = deleteNode(root->left, grade);
    }
    // Якщо оцінка студента більша, шукаємо в правому піддереві
    else if (grade > root->student.grade) {
        root->right = deleteNode(root->right, grade);
    }
    // Якщо знайшли вузол з такою ж оцінкою
    else {
        // Якщо у вузла немає лівого піддерева, замінюємо його правим піддеревом
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        // Якщо у вузла немає правого піддерева, замінюємо його лівим піддеревом
        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Якщо у вузла є обидва піддерева, знаходимо мінімальний елемент з правого піддерева
        Node* temp = root->right;
        while (temp && temp->left != nullptr) {
            temp = temp->left;
        }

        // Замінюємо поточний вузол мінімальним елементом з правого піддерева
        root->student = temp->student;
        root->right = deleteNode(root->right, temp->student.grade);
    }
    return root;
}

// Функція для пошуку студентів з оцінкою менше заданої
void findStudentsWithLowerGrades(Node* root, double grade) {
    if (root == nullptr) return;
    findStudentsWithLowerGrades(root->left, grade);
    if (root->student.grade < grade) {
        cout << root->student.name << " - " << root->student.grade << endl;
    }
    findStudentsWithLowerGrades(root->right, grade);
}

// Головна функція
int main() {
    Node* root = nullptr;
    int choice;
    Student student;
    double grade;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add student\n";
        cout << "2. Display students in descending order of grades\n";
        cout << "3. Delete student by grade\n";
        cout << "4. Find students with grades less than a given value\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter student's name: ";
            cin.ignore();
            getline(cin, student.name);
            cout << "Enter student's grade: ";
            cin >> student.grade;
            root = insertNode(root, student);
            break;
        case 2:
            cout << "Students in descending order of grades:\n";
            inorderTraversal(root);  // Виведення в порядку зменшення оцінок
            break;
        case 3:
            cout << "Enter grade of student to delete: ";
            cin >> grade;
            root = deleteNode(root, grade);
            break;
        case 4:
            cout << "Enter grade to find students with lower grades: ";
            cin >> grade;
            cout << "Students with grades less than " << grade << ":\n";
            findStudentsWithLowerGrades(root, grade);
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
