#include <iostream>
#include <cmath>
using namespace std;

class rectangle {
    int len; // Довжина прямокутника
    int h; // Висота прямокутника

public:
    // Конструктор за замовчуванням
    rectangle() {
        do{
            cout << "Enter the length of rectangle:";
            cin >> len;
        }while(len <= 0);

        do{
            cout << "Enter the height of rectangle:";
            cin >> h;
        }while(h <= 0);
    }
    // Конструктор з параметрами
    rectangle(int len, int h) {
        this->len = len;
        this->h = h;
    }
    // Метод для обчислення діагоналі прямокутника
    double diagonal() {
        return sqrt(len*len + h*h);
    }
    // Метод для обчислення периметру прямокутника
    int perimeter() {
        return 2*(len + h);
    }
    // Метод для обчислення площі прямокутника
    int square() {
        return len*h;
    }
    // Метод для виведення всіх параметрів
    void print() {
        cout << "Length of rectangle: " << len << endl;
        cout << "Height of rectangle: " << h << endl;
        cout << "Diagonal of rectangle: " << diagonal() << endl;
        cout << "Square of rectangle: " << square() << endl;
        cout << "Perimeter of rectangle:: " << perimeter() << endl;
    }
};

int main()
{
    // Використання конструктора за замовчуванням
    rectangle rect;
    cout << endl << "First rectangle: " << endl;
    rect.print();

    // Використання конструктора з параметрами
    rectangle rectParams(5, 10);
    cout << endl << "Second rectangle: " << endl;
    rectParams.print();

    return 0;
}





