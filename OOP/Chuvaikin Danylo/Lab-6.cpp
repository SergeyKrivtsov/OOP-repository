/*
Розробити клас Vector для роботи з математичним
n-вимірним вектором, забезпечити розумну поведінку (обчислення довжини вектора,
отримання установка елементів, виведення на екран, …), конструктор копії,
деструктор. Протестувати клас на об'єктах, покажчиках на об'єктах, масивах.
Створити зовнішню функцію обчислення довжини будь-якого вектора.
*/
#include <iostream>
#include <cmath>
using namespace std;
class Vector {
    private:
        int Dimension;
        double* coords;
    public:
        Vector(double* inputCoords, int Dimension) {
            this->Dimension = Dimension;
            this->coords = new double[Dimension]; 
            for (int i = 0; i < Dimension; i++) {
                this->coords[i] = inputCoords[i];
            }
        }
        Vector(const Vector& other) {
            cout << "I was copied" << endl;
            this->Dimension = other.Dimension; 
            this->coords = new double[Dimension];
            for (int i = 0; i < Dimension; i++) {
                this->coords[i] = other.coords[i];
            }
        }
        double norm() const {
            double sum = 0.0;
            for (int i = 0; i < Dimension; i++) {
                sum += coords[i] * coords[i]; 
            }
            return sqrt(sum);
        }
        void print() const {
            cout << "(";
            for (int i = 0; i < Dimension; i++) {
                cout << coords[i];
                if (i < Dimension - 1) {
                    cout << ", ";
                }
            }
            cout << ")";
        }
        void setCoord(int index, double value) {
            if (index < 0 || index >= Dimension) {
                cout << "Vektor has smaller dimention!";
                return;
            }
            coords[index] = value;
        }
        ~Vector() {
            cout << "I was destructed" << endl;
            delete[] coords;
        }
};
//Зовнішня функція для обчислення довжини будь-якого вектора
double Callculate_lenght(const Vector& v){
    return v.norm();
}
int main()
{
    //Тестування на на об'єктах
    double coords1[] = {3.0, 4.0};
    Vector v1(coords1, 2);
    cout << "Vector 1: ";
    v1.print();
    cout << " | Length: " << v1.norm() << endl;
    cout << "And for testing function: " << Callculate_lenght(v1) << endl;
    
    cout << "Vector 1 (edited): ";
    v1.setCoord(1, 10);
    v1.print();
    cout << " | Length: " << v1.norm() << endl;
    
    double coords2[] = {1.0, 2.0, 2.0};
    Vector v2(coords2, 3);
    cout << "Vector 2: ";
    v2.print();
    cout << " | Length: " << v2.norm() << endl;

    double coords3[] = {0.0, 0.0, 0.0};
    Vector v3(coords3, 3);
    cout << "Vector 3: ";
    v3.print();
    cout << " | Length: " << v3.norm() << endl;
    
    //Тестування на на покажчиках на об'єктах
    double coords4[] = {1, 1};
    Vector* v4 = new Vector(coords4, 2);
    cout << "Vector 4: ";
    v4->print();
    cout << " | Length: " << v4->norm() << endl;
    
    //Тестування на масивах
    Vector* vectors[3];
    vectors[0] = new Vector(coords1, 2);
    vectors[1] = new Vector(coords2, 3);
    vectors[2] = new Vector(coords3, 3);
    for (int i = 0; i < 3; i++) {
        std::cout << "Vector " << (i + 1) << ": ";
        vectors[i]->print();
        std::cout << " | Length: " << vectors[i]->norm() << std::endl;
    }
    for (int i = 0; i < 3; i++) {
        delete vectors[i];
    }
}