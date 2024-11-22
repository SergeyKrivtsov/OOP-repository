/* Реалізувати завдання 9, зробивши клас Figure абстрактним.
 * Додати винятки в конструктори фігур
 * (наприклад радіус коло повинен буди додатним, якщо ні - згенерувати виняток.
 * В мейні перехопити і обробити)
 */

#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace std;
const int FIGURES = 3;

// Базовий клас Figure
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
    Rectangle(double w, double h) {
        if (w <= 0 || h <= 0) { // перевірка
            throw invalid_argument("Width and height must be positive");
        }
        width = w;
        height = h;
    }

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
    Circle(double r) {
        if (r <= 0) { // перевірка
            throw invalid_argument("Radius must be a positive");
        }
        radius = r;
    }

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
    Triangle(double side1, double side2, double side3) {
        if (side1 <= 0 || side2 <= 0 || side3 <= 0) { // перевірка
            throw invalid_argument("Sides of a triangle must be positive");
        }
        if (side1 + side2 <= side3 || side1 + side3 <= side2 || side2 + side3 <= side1) { // перевірка
            throw invalid_argument("The sides do not form a triangle");
        }
        a = side1;
        b = side2;
        c = side3;
    }

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

    try {
        // Створення фігур
        figures[0] = new Rectangle(3, 7);
        figures[1] = new Circle(5);
        figures[2] = new Triangle(3, 4, 5);

        // Виведення площі та периметра фігур
        for (int i = 0; i < 3; ++i) {
            cout << "Figure " << i + 1 << ":" << endl;
            cout << "Area: " << figures[i]->area() << endl;
            cout << "Perimeter: " << figures[i]->perimeter() << endl;
            cout << endl;
        }

        // Звільнення пам'яті
        for (int i = 0; i < 3; ++i) {
            delete figures[i];
        }
    } catch (const invalid_argument& e) {
        // Обробка винятку та виведення помилки
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}