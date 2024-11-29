#include <iostream>
#include <vector>

using namespace std;

// Реалізація множини (Set) на основі хеш-таблиці
class HashSet {
private:
    static const int TABLE_SIZE = 100; // Розмір хеш-таблиці
    vector<vector<string>> table; // Хеш-таблиця: масив списків

    // Хеш-функція
    int hash(const string& key) const {
        int h = 0;
        for (char ch : key) {
            h = (h * 31 + ch) % TABLE_SIZE;
        }
        return h;
    }

public:
    HashSet() : table(TABLE_SIZE) {}

    // Додати елемент у множину
    void insert(const string& key) {
        int index = hash(key);
        for (const auto& element : table[index]) {
            if (element == key) {
                return; // Елемент вже існує
            }
        }
        table[index].push_back(key);
    }

    // Перевірити, чи існує елемент у множині
    bool contains(const string& key) const {
        int index = hash(key);
        for (const auto& element : table[index]) {
            if (element == key) {
                return true;
            }
        }
        return false;
    }

    // Повернути всі елементи з множини
    vector<string> getElements() const {
        vector<string> elements;
        for (const auto& bucket : table) {
            for (const auto& element : bucket) {
                elements.push_back(element);
            }
        }
        return elements;
    }
};

int main() {
    // Список запрошених людей
    HashSet invited;
    invited.insert("Alice");
    invited.insert("Bob");
    invited.insert("Alastor");
    invited.insert("Charlie");
    invited.insert("Diana");

    // Список тих, хто прибув
    HashSet arrived;
    arrived.insert("Bob");
    arrived.insert("Charlie");
    arrived.insert("Alastor");
    arrived.insert("Eve");
    arrived.insert("Frank");

    // Визначаємо тих, хто дійсно бере участь у конференції
    vector<string> attending;

    for (const string& person : invited.getElements()) {
        if (arrived.contains(person)) {
            attending.push_back(person);
        }
    }

    // Виводимо список учасників
    cout << "Conference participants:\n";
    for (const auto& person : attending) {
        cout << person << '\n';
    }

    return 0;
}
