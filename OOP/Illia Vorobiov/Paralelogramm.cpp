#include <iostream>
using namespace std;

class Paralelogramm {
    private:
        int _a;
        int _b;
        int _h;
    public:
        Paralelogramm(int a, int b, int h){
            _a = a;
            _b = b;
            _h = h;
        }
        int Perimeter(){
            return (_a * 2) + (_b * 2);
        }
        int Area(){
            return (_a * _h);
        }
        
};

int main()
{
    Paralelogramm * example = new Paralelogramm(5,5,3);
    cout << "Perimeter: " << example->Perimeter() << endl;
    cout << "Area: " << example->Area() << endl;
}