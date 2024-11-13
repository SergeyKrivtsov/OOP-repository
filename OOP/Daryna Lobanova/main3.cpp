#include <iostream>
#include <cmath>
using namespace std;

class Parallelogram {
    int a;
    int b;
    double angle; // Кут між сторонами у градусах

public:

    // Конструктор за замовчуванням
    Parallelogram() {
        do {
            cout << "Enter the side a of parallelogram: ";
            cin >> a;
        } while (a <= 0);

        do {
            cout << "Enter the side b of parallelogram: ";
            cin >> b;
        } while (b <= 0);

        do {
            cout << "Enter the angle (in degrees) between sides a and b: ";
            cin >> angle;
        } while (angle <= 0 || angle >= 180); // Угол между 0 и 180
    }

    // Конструктор с параметрами
    Parallelogram(int a, int b, double angle) {
        this->a = a;
        this->b = b;
        this->angle = angle;
    }

    // Перетворення кута з градусів у радіани
    double toRadians() const {
        return angle * M_PI / 180.0;
    }

    // Метод для обчислення діагоналі
    double diagonal() {
        double angleRad = toRadians();
        return sqrt(a*a + b*b - 2*a*b*cos(angleRad));
    }

    // Метод для обчислення периметра паралелограма
    int perimeter() {
        return 2*(a + b);
    }

    // Метод для обчислення площі паралелограма
    double square() {
        double angleRad = toRadians();
        return a*b*sin(angleRad);
    }

    // Метод для виведення всіх параметрів
    void print() {
        cout << "Side a of parallelogram: " << a << endl;
        cout << "Side b of parallelogram: " << b << endl;
        cout << "Angle between sides: " << angle << " degrees" << endl;
        cout << "Diagonal of parallelogram: " << diagonal() << endl;
        cout << "Perimeter of parallelogram: " << perimeter() << endl;
        cout << "Square of parallelogram: " << square() << endl;
    }
};

int main() {
    // Використання конструктора за замовчуванням
    Parallelogram para;
    cout << endl << "First parallelogram: " << endl;
    para.print();

    // Використання конструктора з параметрами
    Parallelogram paraParams(5, 10, 60);
    cout << endl << "Second parallelogram: " << endl;
    paraParams.print();

    return 0;
}