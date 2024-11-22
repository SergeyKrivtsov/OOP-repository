#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>

using namespace std;

class Figure {
public:
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual ~Figure() = default; // Віртуальний деструктор для коректного видалення похідних об'єктів
};

class Rectangle : public Figure {
private:
    double width, height;

public:
    Rectangle(double w, double h) {
        if (w <= 0 || h <= 0) {
            throw invalid_argument("Ширина та висота прямокутника повинні бути більшими за 0.");
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
            throw invalid_argument("Радіус кола повинен бути більшим за 0.");
        }
        radius = r;
    }

    double area() const override {
        return 3.14 * radius * radius;
    }

    double perimeter() const override {
        return 2 * 3.14 * radius;
    }
};

class Triangle : public Figure {
private:
    double a, b, c;

public:
    Triangle(double sideA, double sideB, double sideC) {
        if (sideA <= 0 || sideB <= 0 || sideC <= 0) {
            throw invalid_argument("Сторони трикутника повинні бути більшими за 0.");
        }
        if (sideA + sideB <= sideC || sideA + sideC <= sideB || sideB + sideC <= sideA) {
            throw invalid_argument("Задані сторони не утворюють трикутник.");
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
    vector<Figure*> figures;

    try {
        figures.push_back(new Rectangle(5.0, 10.0));
        figures.push_back(new Circle(7.0));
        figures.push_back(new Triangle(3.0, 4.0, 5.0));

        for (const auto& figure : figures) {
            cout << "Площа: " << figure->area() << ", Периметр: " << figure->perimeter() << endl;
        }

        figures.push_back(new Circle(-5.0)); // Тест на виняток
    }
    catch (const invalid_argument& e) {
        cout << "Помилка: " << e.what() << endl;
    }

    for (auto& figure : figures) {
        delete figure;
    }

    return 0;
}
