#include <iostream>
#include <cmath>
using namespace std;

class Vektor {
    int size;
    int *elem;

public:
    // Конструктор
    Vektor(int size, int *elem) {
        cout << "Constructor" << endl;
        this->size = size;
        this->elem = new int[size];
        for (int i = 0; i < size; i++) {
            this->elem[i] = elem[i];
        }
    }

    // Конструктор копіювання
    Vektor(const Vektor &vek) {
        cout << "Copy Constructor" << endl;
        this->size = vek.size;
        elem = new int[vek.size];
        for (int i = 0; i < vek.size; i++) {
            this->elem[i] = vek.elem[i];
        }
    }

    // Метод для обчислення довжини вектора
    double length() const {
        double sum = 0;
        for (int i = 0; i < size; i++) {
            sum += elem[i] * elem[i];
        }
        return sqrt(sum);
    }

    // Метод для зміни елемента вектора за індексом
    void setElement(int index, int val) {
        if (index >= 0 && index < size) {
            elem[index] = val;
        } else {
            cout << "Index out of bounds." << endl;
        }
    }

    // Метод для виведення вектора
    void print() const;

    // Деструктор
    ~Vektor() {
        cout << "Destructor" << endl;
        delete[] elem;
    }
};

// Визначення методу print поза класом
void Vektor::print() const {
    cout << "(";
    for (int i = 0; i < size; i++) {
        cout << elem[i];
        if (i != size - 1) cout << ", ";
    }
    cout << ")" << endl;
}

// Зовнішня функція для обчислення довжини вектора
void length(Vektor v) {
    cout << "The length is " << v.length() << endl;
}

int main() {
    int size;

    // Введення розміру вектора
    cout << "Enter the size of the vector: " << endl;
    while (true) {
        cin >> size;
        if (size > 1) break;
        cout << "Please enter a integer >1 for the size: ";
    }

    int* elem = new int[size]; // Виділення пам'яті для елем. вектора

    // Введення елементів вектора
    cout << "Enter the elements of the vector: " << endl;
    for (int i = 0; i < size; i++) {
        cout << "Element " << (i + 1) << ": ";
        cin >> elem[i];
    }

    Vektor v(size, elem);
    v.print();

    int changeElem;
    // Цикл для можливості зміни елементів вектора
    do {
        cout << "Do you want to change an element? (1 for yes, 0 for no): ";
        cin >> changeElem;

        switch (changeElem) {
            case 1: {
                int index, newVal;
                cout << "Enter the index of the element to change (0 to " << size - 1 << "): ";
                cin >> index;
                cout << "Enter the new value: ";
                cin >> newVal;

                v.setElement(index, newVal);
                v.print(); // Вектор после
                break;
            }
            case 0:
                break;
            default:
                cout << "Error. Please enter 1 or 0." << endl;
                break;
        }
    } while (changeElem != 0);

    // Виклик зовнішньої функції для обчислення довжини
    length(v);

    return 0;
}
