/*
Розробити клас Figure. Успадкувати від нього класи
Rectangle (прямокутник), Circle (коло) Triangle (трикутник). Створити масив
різних фігур та забезпечити обчислення периметра та площі кожної фігури залежно
від її типу.
*/
#include <iostream>
#include <cstdlib>
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
        Rectangle(double w, double h){
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
        Circle(double r){
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
        Triangle(double sideA, double sideB, double sideC){
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
    Figure* figures[FIGURES_A];
    figures[0] = new Rectangle(4.0, 5.0);
    figures[1] = new Circle(3.0);
    figures[2] = new Triangle(3.0, 4.0, 5.0);
    for (int i = 0; i < FIGURES_A; ++i) {
        cout << "Fihure number: " << i + 1 << ", Area: " << figures[i]->area() << ", Perimetr: " << figures[i]->perimeter() << endl;
    }
    for (int i = 0; i < FIGURES_A; ++i) {
        delete figures[i];
    }
    return 0;
}