#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

// Абстрактний клас Animal
class Animal {
protected:
    string name;
    int age;
public:
    // Конструктор для ініціалізації полів
    Animal(const string& name, int age) : name(name), age(age) {}

    // Віртуальний деструктор
    virtual ~Animal() {}

    // Чисто віртуальний метод для звуку
    virtual void makeSound() const = 0;

    // Метод для виведення інформації про тварину
    virtual void displayInfo() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }

    string getName() const { return name; }
    int getAge() const { return age; }
};

// Клас Dog успадкований від Animal
class Dog : public Animal {
    string breed; // Порода
    static int dogCount; // Статична змінна для підрахунку собак
public:
    // Конструктор для ініціалізації і збільшення лічильника собак
    Dog(const string& name, int age, const string& breed)
            : Animal(name, age), breed(breed) {
        dogCount++;
    }

    // Деструктор, який зменшує лічильник собак
    ~Dog() {
        dogCount--;
    }

    // Перевизначений метод для звуку собаки
    void makeSound() const override {
        cout << name << " says: Woof!" << endl;
    }

    // Перевизначений метод для виведення інформації про собаку
    void displayInfo() const override {
        Animal::displayInfo();
        cout << "Breed: " << breed << endl;
    }

    // Статичний метод для отримання кількості собак
    static int getDogCount() {
        return dogCount;
    }
};
int Dog::dogCount = 0; // Ініціалізація статичної змінної

// Клас Cat успадкований від Animal
class Cat : public Animal {
    string color;
    static int catCount; // Статична змінна для підрахунку котів
public:
    // Конструктор для ініціалізації і збільшення лічильника котів
    Cat(const string& name, int age, const string& color)
            : Animal(name, age), color(color) {
        catCount++;
    }

    // Деструктор, який зменшує лічильник котів
    ~Cat() {
        catCount--;
    }

    // Перевизначений метод для звуку кота
    void makeSound() const override {
        cout << name << " says: Meow!" << endl;
    }

    // Перевизначений метод для виведення інформації про кота
    void displayInfo() const override {
        Animal::displayInfo();
        cout << "Color: " << color << endl;
    }

    // Статичний метод для отримання кількості котів
    static int getCatCount() {
        return catCount;
    }
};
int Cat::catCount = 0; // Ініціалізація статичної змінної

// Функція для отримання загальної кількості тварин
int getTotalAnimalCount() {
    return Dog::getDogCount() + Cat::getCatCount();
}

// Функція для запису даних про тварину у файл
void writeToFile(const string& filename, const Animal& animal) {
    ofstream file(filename, ios::app); // Відкриття файлу для додавання даних
    if (!file) {
        throw runtime_error("Error opening file for writing.");
    }
    // Запис імені і віку тварини у файл
    file << animal.getName() << " " << animal.getAge() << endl;
    file.close();
}

// Функція для запису кількості собак, котів і загальної кількості тварин у файл
void writeCountsToFile(const string& filename) {
    ofstream file(filename, ios::app);
    if (!file) {
        throw runtime_error("Error opening file for writing.");
    }
    // Запис кількості собак, котів і загальної кількості у файл
    file << "Total dogs: " << Dog::getDogCount() << endl;
    file << "Total cats: " << Cat::getCatCount() << endl;
    file << "Total animals: " << getTotalAnimalCount() << endl;
    file.close();
}

// Функція для читання даних із файлу
void readFromFile(const string& filename) {
    ifstream file(filename); // Відкриття файлу для читання
    if (!file) {
        throw runtime_error("Error opening file for reading.");
    }
    string line;
    while (getline(file, line)) { // Зчитування
        cout << line << endl;
    }
    file.close();
}

int main() {
    try {
        // Створення об'єктів тварин
        Dog dog1("Buddy", 3, "Golden Retriever");
        Cat cat1("Whiskers", 2, "Gray");
        Cat cat2("Mittens", 1, "White");

        // Виклик методів для собак і котів
        dog1.makeSound();
        dog1.displayInfo();

        cat1.makeSound();
        cat1.displayInfo();

        cat2.makeSound();
        cat2.displayInfo();

        // Виведення кількості тварин у консоль
        cout << "Total dogs: " << Dog::getDogCount() << endl;
        cout << "Total cats: " << Cat::getCatCount() << endl;
        cout << "Total animals: " << getTotalAnimalCount() << endl;

        // Запис даних у файл
        try {
            writeToFile("animals.txt", dog1);
            writeToFile("animals.txt", cat1);
            writeToFile("animals.txt", cat2);
        } catch (const runtime_error& e) {
            cerr << "File write error: " << e.what() << endl;
        }

        // Запис кількості у файл
        try {
            writeCountsToFile("animals.txt");
        } catch (const runtime_error& e) {
            cerr << "File write error: " << e.what() << endl;
        }

        // Зчитування і виведення даних із файлу
        try {
            cout << "\nData from file:" << endl;
            readFromFile("animals.txt");
        } catch (const runtime_error& e) {
            cerr << "File read error: " << e.what() << endl;
        }

    } catch (const exception& e) {
        // Обробка винятків
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}