#include <iostream>
using namespace std;

class Rectangle {
private:
    int length;
    int width;
public:
    Rectangle(int l, int w) {
        length = l;
        width = w;
    }
    Rectangle(int l) {
        length = l;
        width = 15;
    }
    int Area() {
        return length * width;
    }
    int Perimetr() {
        return (length + width) * 2;
    }
};

int main()
{
    int length1;
    int width;
    cout << "Enter lenght ";
    cin >> length1;
    cout << "Enter width ";
    cin >> width;

    Rectangle* userRect = new Rectangle(length1, width);
    int area = userRect->Area();
    cout << area << endl;
    int perimetr = userRect->Perimetr();
    cout << perimetr << endl;

    return 0;
}
