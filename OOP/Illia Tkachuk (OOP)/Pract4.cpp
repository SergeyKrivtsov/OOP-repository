#include <iostream>
using namespace std;

class Rectangle {
private:
    int a;
    int b;

public:
    
    Rectangle(int width, int length) {
        a = width;
        b = length;
    }

    Rectangle() {
        cout << "Enter a width: ";
        cin >> a;
        cout << "Enter a length: ";
        cin >> b;
    }

    int Perimeter() {
        return (a + b) * 2;
    }

    int Square() {
        return a * b;
    }
};

int main() {
    int n;
    cout << "How many rectangles do you want to create? ";
    cin >> n;

    Rectangle* data_array = new Rectangle[n];
  
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ": Perimeter is: " << data_array[i].Perimeter() << "\n";
        cout << "Square is: " << data_array[i].Square() << "\n";
    }

    delete[] data_array;

    return 0;
}