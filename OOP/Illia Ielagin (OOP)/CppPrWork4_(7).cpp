#include <iostream>

using namespace std;

class Point {
protected:
    int x;
    int y;
public:
    Point(int _x, int _y){
        x = _x;
        y = _y;
    }
    void print()const {
        cout << "(" << x << "," << y << ")" << endl;
    }
    virtual void mirror() {
        x = -x;
        y = -y;
    }
};

class Cpoint: public Point {
    char title;
public:
    Cpoint(int _x, int _y, char _t):
        Point(_x, _y) {
            this->title = _t;
        }
    void cPrint()const {
        cout << title;
        Point::print();
    }
    void mirror() override {
        title = 'R';
        x = -x;
        y = -y;
    }
};

int main()
{
    Cpoint cp(2, 5, 'W');
    cp.cPrint();
    cp.mirror();
    cp.cPrint();
    Point* rp = new Cpoint(3, 9, 'M');
    rp->print();
    rp->mirror();
    rp->print();
}
