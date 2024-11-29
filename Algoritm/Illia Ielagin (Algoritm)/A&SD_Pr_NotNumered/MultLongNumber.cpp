#include <iostream>
#include <string>

using namespace std;

void reverseString(string& str) {
    int n = str.size();
    for (int i = 0; i < n / 2; ++i) {
        swap(str[i], str[n - i - 1]);
    }
}

string multiplySingleDigit(const string& num1, char digit, int shift) {
    int carry = 0;
    int d = digit - '0';
    string result(shift, '0'); // Додати нулі для зсуву 

    for (int i = num1.size() - 1; i >= 0; --i) {
        int product = (num1[i] - '0') * d + carry;
        result += (product % 10) + '0';
        carry = product / 10;
    }

    if (carry > 0) {
        result += carry + '0';
    }

    reverseString(result);
    return result;
}

string addStrings(const string& num1, const string& num2) {
    string result;
    int carry = 0;
    int i = num1.size() - 1;
    int j = num2.size() - 1;

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += num1[i--] - '0'; // перетворюємо символ у число за допомогою ASCII 
        if (j >= 0) sum += num2[j--] - '0'; // головна ідея в тому що 0 в аскі дорівнює 48, а 1 = 49 і т.д.
        result += (sum % 10) + '0';
        carry = sum / 10;
    }

    reverseString(result);
    return result;
}

string multiplyStrings(const string& num1, const string& num2) {
    if (num1 == "0" || num2 == "0") return "0";

    string result = "0";
    for (int i = num2.size() - 1, shift = 0; i >= 0; --i, ++shift) {
        string partialResult = multiplySingleDigit(num1, num2[i], shift);
        result = addStrings(result, partialResult);
    }

    return result;
}

int main() {
    string num1, num2;
    cout << "Enter the first number: ";
    cin >> num1;
    cout << "Enter the second number: ";
    cin >> num2;

    string result = multiplyStrings(num1, num2);
    cout << "Multiplication result: " << result << endl;

    return 0;
}
