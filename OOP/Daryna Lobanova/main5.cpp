#include <iostream>
#include <cstring>
using namespace std;

class Point{
protected:
    int x;
    int y;

public:
    // Конструктор базового класу
    Point(int x, int y){
        cout<<"Base constructor"<<endl;
        this->x = x;
        this->y = y;
    }
    // Віртуальний деструктор
    virtual~Point(){
        cout<<"Base destructor"<<endl;
    }
    // Віртуальний метод для виведення координат
    virtual void print()const {
        cout<<"("<<x<<","<<y<<")";
    }
};

// Клас нащадок ColorPoint, який успадковує Point
class ColorPoint: public Point{
public:
    char* color;
    // Конструктор
    ColorPoint(int x, int y, const char* color):Point(x,y){
        cout<<"Derived constructor"<<endl;
        this->color = new char[strlen(color)+1];
        strcpy(this->color, color);
    }
    // Деструктор
    ~ColorPoint(){
        cout<<"Derived destructor"<<endl;
        delete[] color;
    }
    // Перевизначений метод для виведення координат та кольору
    void print()const override {
        Point::print();
        cout<<" "<<color<<endl;
    }
};

int main()
{
    // Створення об'єкта класу Point
    Point p(1, 2);
    p.print(); // виклик методу print()
    cout << endl;
    // Створення об'єкта класу ColorPoint
    ColorPoint cp(3, 4, "Red");
    cp.print(); // виклик перевизначеного методу print()
    cout << endl;

    return 0;
}