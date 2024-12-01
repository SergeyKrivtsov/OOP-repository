// Розробити клас Vector для роботи з математичним
// n-вимірним вектором, забезпечити розумну поведінку (обчислення довжини вектора,
// отримання установка елементів, виведення на екран, …), конструктор копії,
// деструктор. Протестувати клас на об'єктах, покажчиках на об'єктах, масивах.
// Створити зовнішню функцію обчислення довжини будь-якого вектора.
//add a method to add two vectors and multiplz
//first n in main, then by the user
#include <iostream>
#include <math.h>
using namespace std;

class Vector
{
    private:
        int x1;
        int x2;
    public:
        //constructor
        Vector()
        {
            cout << "Input the x1 coordinate of the vector:\n";
            cin >> x1;
            cout << "Input the x2 coordinate of the vector:\n";
            cin >> x2;
        }
        //copy constructor
        Vector(Vector& v)
        {
            this->x1 = v.x1;
            this->x2 = v.x2;
        }
        void set_x1(int x1)
        {
            this->x1 = x1;
        }
        void set_x2(int x2)
        {
            this->x2 = x2;
        }
        int get_x1()
        {
            return this->x1;
        }
        int get_x2()
        {
            return this->x2;
        }
        int find_length()
        {
            cout << sqrt(pow(x1, 2) + pow(x2, 2))<<endl;
            return sqrt(pow(x1, 2) + pow(x2, 2));
        }
        void Output()
        {
            cout << "x1 coor: " << x1 << "// x2 coor: " << x2 << endl;
        }
        void add_vector(Vector& v)
        {
            this->x1 += v.x1;
            this->x2 += v.x2; 
        }
        //destructor
        ~Vector()
        {
            cout << "If i had to write a destructor\n";
        }
};

int main()
{
    Vector v1; 
    Vector v2 = v1;
    v1.Output();
    v2.Output();

    cout << "The length of the first vecotr: " << v1.find_length() << endl;
    cout << "The length of the second vecotr: " << v2.find_length() << endl;

    v1.add_vector(v2);

    v1.Output();

    return 0;
}