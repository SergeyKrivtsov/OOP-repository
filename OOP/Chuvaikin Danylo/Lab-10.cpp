/*
Реалізувати завдання 9, зробивши клас Figure абстрактним.
Додати винятки в конструктори фігур (наприклад радіус коло повинен буди додатним, якщо ні - згенерувати виняток.
В мейні перехопити і обробити). Додати коментар, що краще, щоб клас Фігура був абстрактним чи ні.
Відповідь обґрунтуйте.
*/
#include <iostream>
#include <stdexcept>
#include <cmath>
using namespace std;
const int FIGURES_A = 3;
class Figure {
    public:
        virtual double area() const = 0;
        virtual double perimeter() const = 0;
    };
class Rectangle : public Figure {
    private:
        double width;
        double height;
    public:
        Rectangle(double w, double h) {
            if (w <= 0 || h <= 0) {
                throw invalid_argument("Width and height of the rectangle must be positive");
            }
            width = w;
            height = h;
        }
        double area() const override {
            return width * height;
        }

        double perimeter() const override {
            return 2 * (width + height);
        }
};
class Circle : public Figure {
    private:
        double radius;
    public:
        Circle(double r) {
            if (r <= 0) {
                throw invalid_argument("Radius of the circle must be positive");
            }
            radius = r;
        }
        double area() const override {
            return M_PI * radius * radius;
        }

        double perimeter() const override {
            return 2 * M_PI * radius;
        }
};
class Triangle : public Figure {
    private:
        double a;
        double b;
        double c;
    public:
        Triangle(double sideA, double sideB, double sideC) {
            if (sideA <= 0 || sideB <= 0 || sideC <= 0) {
                throw invalid_argument("Sides of the triangle must be positive");
            }
            if (sideA + sideB <= sideC || sideA + sideC <= sideB || sideB + sideC <= sideA) {
                throw invalid_argument("The given sides do not form a valid triangle");
            }
            a = sideA;
            b = sideB;
            c = sideC;
        }
        double area() const override {
            double s = (a + b + c) / 2;
            return sqrt(s * (s - a) * (s - b) * (s - c));
        }

        double perimeter() const override {
            return a + b + c;
        }
};
int main() {
    //масив вказівників nullptr для коректного перехоплення помилки 
    Figure* figures[FIGURES_A] = {nullptr};
    try {
        figures[0] = new Rectangle(4.0, 5.0);
        //приклад введення некоректного значення радіусу кола
        figures[1] = new Circle(-3.0);
        figures[2] = new Triangle(3.0, 4.0, 5.0);
        for (int i = 0; i < FIGURES_A; ++i) {
            cout << "Figure number: " << i + 1 
                 << ", Area: " << figures[i]->area() 
                 << ", Perimeter: " << figures[i]->perimeter() << endl;
        }
    }
    catch (const invalid_argument& e) {
        cout << "Error: " << e.what() << endl;
    }
    for (int i = 0; i < FIGURES_A; ++i) {
        delete figures[i];
    }
    return 0;
}
