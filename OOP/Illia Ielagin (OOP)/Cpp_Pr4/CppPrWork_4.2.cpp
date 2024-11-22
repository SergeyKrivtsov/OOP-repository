#include <iostream>
using namespace std;

class Rectangle {
private:
    int length;
    int side;
    int high;
public:
    Rectangle(int l, int s, int h) {
        length = l;
        side = s;
        high = h;
    }
    Rectangle(int l) {
        length = l;
        side = 15;
        high = 5;
    }
    int area() {
        return length * high;
    }
    int perimetr() {
        return (length + side) * 2;
    }
};

int main()
{
    int length;
    int side;
    int high;
    cout << "Enter lenght ";
    cin >> length;
    cout << "Enter side ";
    cin >> side;
    cout << "Enter high ";
    cin >> high;

    Rectangle userRect(length, side, high);
    int area = userRect.area();
    cout << area << endl;
    int perimetr = userRect.perimetr();
    cout << perimetr << endl;

    return 0;
}

