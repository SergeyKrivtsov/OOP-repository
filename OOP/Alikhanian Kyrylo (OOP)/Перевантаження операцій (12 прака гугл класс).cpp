#include <iostream>
#include <stdexcept>
#include <cmath>
#include <numeric>

using namespace std;

class Fraction {
private:
    int numerator;  // Чисельник
    int denominator;  // Знаменник

    // Функція для скорочення дробу
    void reduce() {
        if (denominator == 0) {
            throw invalid_argument("Ділити на нуль неможливо!");
        }
        int gcd_val = gcd(abs(numerator), abs(denominator));
        numerator /= gcd_val;
        denominator /= gcd_val;
        if (denominator < 0) {  // Завжди маємо знаменник позитивним
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    // Конструктор за замовчуванням
    Fraction(int num = 0, int denom = 1) {
        if (denom == 0) {
            throw invalid_argument("Знаменник не може бути нулем!");
        }
        numerator = num;
        denominator = denom;
        reduce();
    }

    // Операції порівняння
    bool operator==(const Fraction& other) const {
        return numerator == other.numerator && denominator == other.denominator;
    }

    bool operator!=(const Fraction& other) const {
        return !(*this == other);
    }

    bool operator<(const Fraction& other) const {
        return numerator * other.denominator < other.numerator * denominator;
    }

    bool operator>(const Fraction& other) const {
        return other < *this;
    }

    bool operator<=(const Fraction& other) const {
        return !(*this > other);
    }

    bool operator>=(const Fraction& other) const {
        return !(*this < other);
    }

    // Арифметичні операції
    Fraction operator+(const Fraction& other) const {
        int num = numerator * other.denominator + other.numerator * denominator;
        int denom = denominator * other.denominator;
        return Fraction(num, denom);
    }

    Fraction operator-(const Fraction& other) const {
        int num = numerator * other.denominator - other.numerator * denominator;
        int denom = denominator * other.denominator;
        return Fraction(num, denom);
    }

    Fraction operator*(const Fraction& other) const {
        int num = numerator * other.numerator;
        int denom = denominator * other.denominator;
        return Fraction(num, denom);
    }

    Fraction operator/(const Fraction& other) const {
        if (other.numerator == 0) {
            throw invalid_argument("Ділення на нуль не можливе!");
        }
        int num = numerator * other.denominator;
        int denom = denominator * other.numerator;
        return Fraction(num, denom);
    }

    // Інкремент і декремент
    Fraction& operator++() {
        numerator += denominator;
        reduce();
        return *this;
    }

    Fraction operator++(int) {
        Fraction temp = *this;
        ++(*this);
        return temp;
    }

    Fraction& operator--() {
        numerator -= denominator;
        reduce();
        return *this;
    }

    Fraction operator--(int) {
        Fraction temp = *this;
        --(*this);
        return temp;
    }

    // Операції з цілими числами
    Fraction operator+(int val) const {
        return *this + Fraction(val);
    }

    Fraction operator-(int val) const {
        return *this - Fraction(val);
    }

    Fraction operator*(int val) const {
        return *this * Fraction(val);
    }

    Fraction operator/(int val) const {
        if (val == 0) {
            throw invalid_argument("Ділення на нуль неможливе!");
        }
        return *this / Fraction(val);
    }

    // Перетворення в дійсне число
    operator double() const {
        return static_cast<double>(numerator) / denominator;
    }

    // Виведення
    friend ostream& operator<<(ostream& out, const Fraction& frac) {
        out << frac.numerator << "/" << frac.denominator;
        return out;
    }

    // Введення
    friend istream& operator>>(istream& in, Fraction& frac) {
        char slash;
        in >> frac.numerator >> slash >> frac.denominator;
        if (frac.denominator == 0) {
            throw invalid_argument("Знаменник не може бути нулем!");
        }
        frac.reduce();
        return in;
    }
};

int main() {
    try {
        Fraction f1(3, 4);
        Fraction f2(5, 6);
        Fraction f3;

        cout << "Введіть дріб (формат: чисельник/знаменник): ";
        cin >> f3;

        cout << "Фракція 1: " << f1 << endl;
        cout << "Фракція 2: " << f2 << endl;
        cout << "Фракція 3: " << f3 << endl;

        cout << "Сума: " << f1 + f2 << endl;
        cout << "Різниця: " << f1 - f2 << endl;
        cout << "Множення: " << f1 * f2 << endl;
        cout << "Ділення: " << f1 / f2 << endl;

        cout << "Інкремент фракції 1: " << ++f1 << endl;
        cout << "Декремент фракції 2: " << --f2 << endl;

        cout << "Фракція як дійсне число: " << double(f1) << endl;

        cout << "Фракція 1 порівняно з фракцією 2: " << (f1 > f2 ? "більше" : "менше або рівне") << endl;

        int intVal = 2;
        cout << "Фракція 1 + ціле число: " << f1 + intVal << endl;

        Fraction f4 = f1 / 0;  // Це викличе виняток
    }
    catch (const invalid_argument& e) {
        cout << "Помилка: " << e.what() << endl;
    }

    return 0;
}
