//Розробити клас Figure.Успадкувати від нього класи
//Rectangle(прямокутник), Circle(коло) Triangle(трикутник).Створити масив
//різних фігур та забезпечити обчислення периметра та площі кожної фігури залежно
//від її типу.

#include <iostream>

using namespace std;

class Figure {
    string Color = "Transparent";
public:
    Figure() {

    }
    Figure(string Col) {
        Color = Col;
    }
    virtual double countSquare() {
        return 0;
    }
    virtual double countPerimetr() {
        return 0;
    }
};

class Rectangle : public Figure{
    int a= 0, b = 0;
public:
    Rectangle(int a, int b) {
        this->a = a;
        this->b = b;
    }
    Rectangle() {

    }
    double countSquare() {
        return a * b;
    }
    double countPerimetr() {
        return (2*(a + b));
    }
};

class Circle : public Figure{
    int R;
public:
    Circle(int R) {
        this->R = R;
    }
    double countSquare() override{
        return (3.14 * R * R);
    }
    double countPerimetr() override{
        return (2 * 3.14 * R);
    }
};

class Triangle : public Figure {//Будем ураховувати, що трикутник правильний
    int a;
public:
    Triangle(int a) {
        this->a = a;
    }
    Triangle() {

    }
    double countSquare() override{
        return ((a * a * sqrt(3)) / 4);
    }
    double countPerimetr() override{
        return (3 * a);
    }
};

int main()
{
    setlocale(LC_CTYPE, "ukr");

    Figure *masik[5]{
        new Rectangle(5,8), new Circle(5), new Triangle(8), new Circle(12), new Triangle(5)
    };
    int key = 0;
    cout << "Наразі ми маємо список фігур який виглядає наступним чином: \n"
        << "Прямокутник зі сторонами 5 та 8\n"
        << "Круг з радіусом 5\n"
        << "Трикутник зі стороною 8\n"
        << "Круг з радіусом 8\n"
        << "Трикутник зі строною 2\n";
    cout << "Введіть 1 чи 2 для розрахування площі та периметру відповідно, введіть 0 для закінчення роботи програми" << endl;
    do
    {
        cin >> key;
        switch (key)
        {
        case 1://Рахує площину
            for (size_t i = 0; i < 5; i++)
            {
                cout << "Площа"<<i+1<< "-ої фігури дорівнює " << masik[i]->countSquare() << endl;
            }
            break;
        case 2://Рахує периметр
            for (size_t i = 0; i < 5; i++)
            {
                cout << "Периметр" << i + 1 << "-ої фігури дорівнює " << masik[i]->countPerimetr() << endl;
             }
            break;
        default:
            break;
        }
    } while (key!=0);
    for (size_t i = 0; i < 5; i++)
    {
        delete masik[i];
    }
    delete[] masik;
    cout << "Hello World!\n";
}

