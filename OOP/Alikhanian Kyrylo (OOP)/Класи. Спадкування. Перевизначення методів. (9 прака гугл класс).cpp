#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Figure {
public:
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual ~Figure() = default;
};

class Rectangle : public Figure {
private:
    double width, height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}

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
    Circle(double r) : radius(r) {}

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
    Triangle(double sideA, double sideB, double sideC) : a(sideA), b(sideB), c(sideC) {
        if (a + b <= c || a + c <= b || b + c <= a) {
            throw invalid_argument("Трикутник із такими сторонами не може існувати");
        }
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

        for (auto& figure : figures) {
            delete figure;
        }
    }
    catch (const exception& e) {
        cout << "Помилка: " << e.what() << endl;
    }

    return 0;
}
