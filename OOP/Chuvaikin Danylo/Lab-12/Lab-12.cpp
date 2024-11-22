/*
Реалізувати клас «Звичайний дріб». Забезпечити
можливість скорочення дробу, всі арифметичні операції, включаючи обидві форми
інкременту та декременту, операції порівняння, виведення та введення зі
стандартних потоків, а також можливість використання в операціях цілих чи дійсних
типів. Забезпечити опрацювання виняткових ситуацій.
*/
#include <iostream>
#include <stdexcept>
using namespace std;
class Simple_Drib{
    private:
        int numerator;
        int denominator;
        void cut() {
            if (denominator < 0 && numerator < 0) {
                numerator = -numerator;
                denominator = -denominator;
            }
            int nod = numerator, b = denominator;
            while (b != 0) {
                int temp = b;
                b = nod % b;
                nod = temp;
            }
            numerator /= nod;
            denominator /= nod;
        }
    public:
        Simple_Drib(int num = 1, int denom = 1){
            numerator = num;
            denominator = denom;
            if (denominator == 0) {
                throw invalid_argument("Denominator cannot be zero!");
            }
            cut();
        }
        Simple_Drib  operator+(const Simple_Drib & other) const{
            return Simple_Drib (numerator * other.denominator + other.numerator * denominator, denominator * other.denominator);
        }
        Simple_Drib  operator-(const Simple_Drib & other) const{
            return Simple_Drib (numerator * other.denominator - other.numerator * denominator, denominator * other.denominator);
        }
        Simple_Drib  operator*(const Simple_Drib & other) const{
            return Simple_Drib (numerator * other.numerator, denominator * other.denominator);
        }
        Simple_Drib  operator/(const Simple_Drib & other) const{
            if (other.numerator == 0) {
                throw invalid_argument("Division by zero");
            }
            return Simple_Drib (numerator * other.denominator, denominator * other.numerator);
        }
        bool operator==(const Simple_Drib & other) const{
            return numerator == other.numerator && denominator == other.denominator;
        }
        bool operator!=(const Simple_Drib & other) const{
            return !(*this == other);
        }
        bool operator<(const Simple_Drib & other) const{
            return numerator * other.denominator < other.numerator * denominator;
        }
        bool operator<=(const Simple_Drib & other) const{
            return *this < other || *this == other;
        }
        bool operator>(const Simple_Drib & other) const{
            return !(*this <= other);
        }
        bool operator>=(const Simple_Drib & other) const{
            return !(*this < other);
        }
        Simple_Drib & operator++(){
            numerator += denominator;
            return *this;
        }
        Simple_Drib  operator++(int){
            Simple_Drib  temp = *this;
            ++(*this);
            return temp;
        }
        Simple_Drib & operator--(){
            numerator -= denominator;
            return *this;
        }
        Simple_Drib  operator--(int){
            Simple_Drib  temp = *this;
            --(*this);
            return temp;
        }
        friend ostream& operator<<(ostream& os, const Simple_Drib & frac){
            os << frac.numerator << "/" << frac.denominator;
            return os;
        }
        friend istream& operator>>(istream& is, Simple_Drib & frac) {
            char ch;
            is >> frac.numerator >> ch >> frac.denominator;
            if (frac.denominator == 0) {
                throw invalid_argument("Denominator cannot be zero");
            }
            frac.cut();
            return is;
        }
        operator int() const {
            return numerator / denominator;
        }
        operator double() const {
            return static_cast<double>(numerator) / denominator;
        }
};
Simple_Drib  operator+(const Simple_Drib & frac, int value){
    return frac + Simple_Drib (value);
}
Simple_Drib  operator-(const Simple_Drib & frac, int value){
    return frac - Simple_Drib (value);
}
Simple_Drib  operator*(const Simple_Drib & frac, int value){
    return frac * Simple_Drib (value);
}
Simple_Drib  operator/(const Simple_Drib & frac, int value){
    return frac / Simple_Drib (value);
}
Simple_Drib  operator+(int value, const Simple_Drib & frac){
    return Simple_Drib (value) + frac;
}
Simple_Drib  operator-(int value, const Simple_Drib & frac){
    return Simple_Drib (value) - frac;
}
Simple_Drib  operator*(int value, const Simple_Drib & frac){
    return Simple_Drib (value) * frac;
}
Simple_Drib  operator/(int value, const Simple_Drib & frac){
    return Simple_Drib (value) / frac;
}
int main() {
    try {
        Simple_Drib  f1(3, 4);
        Simple_Drib  f2(1, 2);
        cout << "f1 = " << f1 << "\n";
        cout << "f2 = " << f2 << "\n";

        cout << "f1 + f2 = " << f1 + f2 << "\n";
        cout << "f1 - f2 = " << f1 - f2 << "\n";
        cout << "f1 * f2 = " << f1 * f2 << "\n";
        cout << "f1 / f2 = " << f1 / f2 << "\n";

        cout << "f1++ = " << f1++ << "\n";
        cout << "f1+3 = " << f1+3 << "\n";
        cout << "f1-- = " << f1-- << "\n";

        cout << "f1 == f2: " << (f1 == f2) << "\n";
        cout << "f1 < f2: " << (f1 < f2) << "\n";

        Simple_Drib  f3;
        cout << "Enter a Simple_Drib  in the form a/b: ";
        cin >> f3;
        cout << "You entered: " << f3 << "\n";
    }
    catch (const exception& ex) {
        cout << "Error: " << ex.what() << "\n";
    }
    return 0;
}
