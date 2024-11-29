#include <iostream>
#include <cmath>

using namespace std;

class Rectangle {
protected:
    double width, height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}

    virtual double area() const {
        return width * height;
    }

    virtual double perimeter() const {
        return 2 * (width + height);
    }

    virtual void move(double x, double y) {
        cout << "Переміщено на точку (" << x << ", " << y << ")" << endl;
    }
};

class Window : public Rectangle {
public:
    Window(double w, double h) : Rectangle(w, h) {}

    void move(double x, double y) override {
        cout << "Вікно переміщено до точки (" << x << ", " << y << ")" << endl;
    }
};

int main() {
    Window window(4.0, 5.0);
    cout << "Площа вікна: " << window.area() << endl;
    cout << "Периметр вікна: " << window.perimeter() << endl;
    window.move(10.0, 20.0);
    return 0;
}
