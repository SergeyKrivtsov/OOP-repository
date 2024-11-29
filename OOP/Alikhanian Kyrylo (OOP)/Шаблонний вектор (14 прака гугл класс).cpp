#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

// Шаблонний клас Vector
template <typename T>
class Vector {
private:
    vector<T> data; // Динамічний масив для збереження елементів
    T defaultValue; // Значення за замовчуванням для ініціалізації елементів

public:
    // Конструктор із вказанням розміру та значення за замовчуванням
    Vector(size_t size, T defaultValue = T()) : data(size, defaultValue), defaultValue(defaultValue) {}

    // Перевантаження оператора індексації []
    T& operator[](size_t index) {
        if (index >= data.size()) {
            throw out_of_range("Індекс виходить за межі вектора!");
        }
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= data.size()) {
            throw out_of_range("Індекс виходить за межі вектора!");
        }
        return data[index];
    }

    // Перевантаження оператора =
    Vector<T>& operator=(const Vector<T>& other) {
        if (this != &other) {
            data = other.data;
            defaultValue = other.defaultValue;
        }
        return *this;
    }

    // Перевантаження оператора порівняння ==
    bool operator==(const Vector<T>& other) const {
        return data == other.data;
    }

    // Перевантаження арифметичних операцій
    Vector<T> operator+(const Vector<T>& other) const {
        if (data.size() != other.data.size()) {
            throw invalid_argument("Розміри векторів не збігаються!");
        }
        Vector<T> result(data.size(), defaultValue);
        for (size_t i = 0; i < data.size(); ++i) {
            result[i] = data[i] + other[i];
        }
        return result;
    }

    Vector<T> operator-(const Vector<T>& other) const {
        if (data.size() != other.data.size()) {
            throw invalid_argument("Розміри векторів не збігаються!");
        }
        Vector<T> result(data.size(), defaultValue);
        for (size_t i = 0; i < data.size(); ++i) {
            result[i] = data[i] - other[i];
        }
        return result;
    }

    Vector<T> operator*(T scalar) const {
        Vector<T> result(data.size(), defaultValue);
        for (size_t i = 0; i < data.size(); ++i) {
            result[i] = data[i] * scalar;
        }
        return result;
    }

    Vector<T>& operator+=(const Vector<T>& other) {
        if (data.size() != other.data.size()) {
            throw invalid_argument("Розміри векторів не збігаються!");
        }
        for (size_t i = 0; i < data.size(); ++i) {
            data[i] += other[i];
        }
        return *this;
    }

    Vector<T>& operator-=(const Vector<T>& other) {
        if (data.size() != other.data.size()) {
            throw invalid_argument("Розміри векторів не збігаються!");
        }
        for (size_t i = 0; i < data.size(); ++i) {
            data[i] -= other[i];
        }
        return *this;
    }

    // Метод для виведення вектора
    void print() const {
        for (const T& elem : data) {
            cout << elem << " ";
        }
        cout << endl;
    }
};

// Тестування класу Vector
int main() {
    try {
        Vector<int> v1(5, 1); // Вектор із 5 елементів, значення за замовчуванням = 1
        Vector<int> v2(5, 2); // Вектор із 5 елементів, значення за замовчуванням = 2

        cout << "Початкові вектори:" << endl;
        v1.print();
        v2.print();

        // Додавання векторів
        Vector<int> v3 = v1 + v2;
        cout << "Результат v1 + v2:" << endl;
        v3.print();

        // Віднімання векторів
        Vector<int> v4 = v1 - v2;
        cout << "Результат v1 - v2:" << endl;
        v4.print();

        // Множення на скаляр
        Vector<int> v5 = v1 * 3;
        cout << "Результат v1 * 3:" << endl;
        v5.print();

        // Оператори += та -=
        v1 += v2;
        cout << "Результат v1 += v2:" << endl;
        v1.print();

        v1 -= v2;
        cout << "Результат v1 -= v2:" << endl;
        v1.print();

        // Спроба доступу до неіснуючого елемента
        cout << "Елемент за межами: " << v1[10] << endl;
    }
    catch (const exception& e) {
        cerr << "Виняток: " << e.what() << endl;
    }

    return 0;
}
