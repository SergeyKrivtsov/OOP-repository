#include <iostream>
#include <cstring>
using namespace std;

class Point {
protected:
    int x, y;
public:
    Point(int x, int y) {
        this->x=x;
        this->y=y;
    }

    virtual void print() const {
        cout << "Point(" << x << ", " << y << ")" << endl;
    }

    void getCoordinates() const {
        cout << "X: " << x << ", Y: " << y << endl;
    }

    virtual ~Point() {}
};

class ColoredPoint : public Point {
public:
string color;
    ColoredPoint(int x, int y, string color):Point(x,y) {
        this->x=x;
        this->y=y;
        this->color=color;
    }
    
    void print() const  {
        cout << "ColoredPoint(" << x << ", " << y << ", Color: " << color << ")" << endl;
    }
};

void displayPoint(const Point& p) {
    p.print();
}

int main() {
    Point p(1, 2);          
    ColoredPoint cp(3, 4, "red"); 

    p.getCoordinates();// Раннее
    cp.getCoordinates();


    displayPoint(p);//Позднее
    displayPoint(cp);

    return 0;
}
