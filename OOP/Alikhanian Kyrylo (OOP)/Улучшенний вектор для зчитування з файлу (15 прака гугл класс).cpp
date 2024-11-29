#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
using namespace std;

// Шаблонний клас Vector
template <typename T>
class Vector {
private:
    vector<T> data; // Динамічний масив для збереження елементів

public:
    // Конструктор
    Vector() = default;
    Vector(size_t size, T defaultValue = T()) : data(size, defaultValue) {}

    // Доступ до елементів (з перевіркою)
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

    // Додавання елемента
    void push_back(const T& value) {
        data.push_back(value);
    }

    // Розмір вектора
    size_t size() const {
        return data.size();
    }

    // Перевантаження оператора <<
    friend ofstream& operator<<(ofstream& out, const Vector<T>& v) {
        for (const T& elem : v.data) {
            out << elem << " ";
        }
        return out;
    }

    // Перевантаження оператора >>
    friend ifstream& operator>>(ifstream& in, Vector<T>& v) {
        T temp;
        while (in >> temp) {
            v.push_back(temp);
        }
        return in;
    }

    // Перевантаження арифметичних операцій
    Vector<T> operator+(const Vector<T>& other) const {
        if (data.size() != other.data.size()) {
            throw invalid_argument("Розміри векторів не збігаються!");
        }
        Vector<T> result(data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }

    Vector<T> operator-(const Vector<T>& other) const {
        if (data.size() != other.data.size()) {
            throw invalid_argument("Розміри векторів не збігаються!");
        }
        Vector<T> result(data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            result.data[i] = data[i] - other.data[i];
        }
        return result;
    }

    Vector<T>& operator+=(const Vector<T>& other) {
        if (data.size() != other.data.size()) {
            throw invalid_argument("Розміри векторів не збігаються!");
        }
        for (size_t i = 0; i < data.size(); ++i) {
            data[i] += other.data[i];
        }
        return *this;
    }

    Vector<T>& operator-=(const Vector<T>& other) {
        if (data.size() != other.data.size()) {
            throw invalid_argument("Розміри векторів не збігаються!");
        }
        for (size_t i = 0; i < data.size(); ++i) {
            data[i] -= other.data[i];
        }
        return *this;
    }

    // Метод для виведення вектора в консоль
    void print() const {
        for (const T& elem : data) {
            cout << elem << " ";
        }
        cout << endl;
    }
};

// Користувацький тип Point
class Point {
private:
    int x, y; // Координати точки

public:
    Point(int x = 0, int y = 0) : x(x), y(y) {}

    // Перевантаження оператора <<
    friend ostream& operator<<(ostream& out, const Point& p) {
        out << "(" << p.x << ", " << p.y << ")";
        return out;
    }

    // Перевантаження оператора >>
    friend istream& operator>>(istream& in, Point& p) {
        in >> p.x >> p.y;
        return in;
    }

    // Перевантаження арифметичних операцій для Point
    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }

    Point operator-(const Point& other) const {
        return Point(x - other.x, y - other.y);
    }

    Point& operator+=(const Point& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Point& operator-=(const Point& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
};

int main() {
    try {
        // Тест для стандартного типу (int)
        Vector<int> v1;
        ifstream inFile("input_int.txt");
        if (inFile.is_open()) {
            inFile >> v1; // Зчитування з файлу
            inFile.close();
        }
        cout << "Вектор int після зчитування з файлу: ";
        v1.print();

        ofstream outFile("output_int.txt");
        if (outFile.is_open()) {
            outFile << v1; // Запис у файл
            outFile.close();
        }

        // Тест для користувацького типу (Point)
        Vector<Point> v2;
        ifstream inPointFile("input_points.txt");
        if (inPointFile.is_open()) {
            inPointFile >> v2; // Зчитування з файлу
            inPointFile.close();
        }
        cout << "Вектор Point після зчитування з файлу: ";
        v2.print();

        ofstream outPointFile("output_points.txt");
        if (outPointFile.is_open()) {
            outPointFile << v2; // Запис у файл
            outPointFile.close();
        }
    }
    catch (const exception& e) {
        cerr << "Виняток: " << e.what() << endl;
    }

    return 0;
}
