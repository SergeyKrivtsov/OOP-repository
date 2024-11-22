#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>

class LongNumber {
private:
    std::string value;

    // Функція для перевірки, чи рядок є числом
    bool isValidNumber(const std::string& str) const {
        return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
    }

public:
    LongNumber(const std::string& str) {
        if (!isValidNumber(str)) {
            throw std::invalid_argument("Некоректне представлення числа");
        }
        value = str;
    }

    LongNumber(const char* str) {
        std::string temp(str);
        if (!isValidNumber(temp)) {
            throw std::invalid_argument("Некоректне представлення числа");
        }
        value = temp;
    }

    // Функція для отримання значення числа як рядка
    std::string getValue() const {
        return value;
    }

    // Операція додавання
    LongNumber operator+(const LongNumber& other) const {
        int carry = 0;
        std::string result;
        int maxLength = std::max(value.size(), other.value.size());

        // Додаємо числа по цифрі з урахуванням переносу
        for (int i = 0; i < maxLength || carry != 0; ++i) {
            int digit1 = (i < value.size()) ? value[value.size() - 1 - i] - '0' : 0;
            int digit2 = (i < other.value.size()) ? other.value[other.value.size() - 1 - i] - '0' : 0;
            int sum = digit1 + digit2 + carry;
            carry = sum / 10;
            result.push_back(sum % 10 + '0');
        }

        std::reverse(result.begin(), result.end());
        return LongNumber(result);
    }

    // Операція додавання з рядком
    LongNumber operator+(const char* str) const {
        return *this + LongNumber(str);
    }

    // Операція додавання з рядковим представленням
    LongNumber operator+(const std::string& str) const {
        return *this + LongNumber(str);
    }

    // Операція порівняння
    bool operator==(const LongNumber& other) const {
        return value == other.value;
    }

    bool operator!=(const LongNumber& other) const {
        return value != other.value;
    }

    bool operator<(const LongNumber& other) const {
        return value.size() < other.value.size() || (value.size() == other.value.size() && value < other.value);
    }

    bool operator>(const LongNumber& other) const {
        return other < *this;
    }

    // Операція виведення
    void display() const {
        std::cout << value << std::endl;
    }
};

int main() {
    try {
        LongNumber num1("123456789");
        LongNumber num2("987654321");

        LongNumber result = num1 + num2;
        result.display(); // Виведе: 1111111110

        LongNumber num3("543678");
        result = num1 + num3;
        result.display(); // Виведе: 123456789543678

        // Змішане додавання з рядком
        result = num1 + "555555";
        result.display(); // Виведе: 123456789555555
    }
    catch (const std::exception& e) {
        std::cout << "Помилка: " << e.what() << std::endl;
    }

    return 0;
}
