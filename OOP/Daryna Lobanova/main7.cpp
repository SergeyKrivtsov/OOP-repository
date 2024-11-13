#include <iostream>
#include <cmath>

using namespace std;
const int FIGURES = 3;

// Базовий клас
class Figure {
public:
    // Чисто віртуальна функція для площі
    virtual double area() const = 0;
    // Чисто віртуальна функція для периметра
    virtual double perimeter() const = 0;
    // Віртуальний деструктор
    virtual ~Figure() {}
};

// Клас Rectangle успадкований від Figure
class Rectangle : public Figure {
private:
    double width;
    double height;
public:
    // Конструктор з параметрами для ініціалізації ширини та висоти
    Rectangle(double w, double h) : width(w), height(h) {}

    // Перевизначення методу для обчислення площі
    double area() const override {
        return width * height;
    }

    // Перевизначення методу для обчислення периметра
    double perimeter() const override {
        return 2*(width + height);
    }
};

// Клас Circle успадкований від Figure
class Circle : public Figure {
private:
    double radius;
public:
    // Конструктор з параметром для ініціалізації радіуса
    Circle(double r) : radius(r) {}

    // Перевизначення методу для обчислення площі
    double area() const override {
        return M_PI * radius * radius;
    }

    // Перевизначення методу для обчислення периметра (довжини кола)
    double perimeter() const override {
        return 2 * M_PI * radius;
    }
};

// Клас Triangle успадкований від Figure
class Triangle : public Figure {
private:
    double a, b, c; // сторони
public:
    // Конструктор з параметрами для ініціалізації сторін
    Triangle(double s1, double s2, double s3) : a(s1), b(s2), c(s3) {}

    // Перевизначення методу для обчислення площі
    double area() const override {
        double p = perimeter() / 2; // півпериметр
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }

    // Перевизначення методу для обчислення периметра
    double perimeter() const override {
        return a + b + c;
    }
};

int main() {
    Figure* figures[FIGURES]; // масив вказівників на фігури

    // Створення фігур
    figures[0] = new Rectangle(3, 7);
    figures[1] = new Circle(5);
    figures[2] = new Triangle(3, 4, 5);

    // Виведення площі та периметра фігур
    for (int i = 0; i < 3; ++i) {
        cout << "Figure " << i + 1 << ":" << endl;
        cout << "Area " << figures[i]->area() << endl;
        cout << "Perimeter " << figures[i]->perimeter() << endl;
        cout << endl;
    }

    // Звільнення пам'яті
    for (int i = 0; i < 3; ++i) {
        delete figures[i];
    }

    return 0;
}