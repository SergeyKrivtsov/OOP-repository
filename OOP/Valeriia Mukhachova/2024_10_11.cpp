//  Розробити клас, похідний класу Point. Протестувати раннє
// та пізніше (поліморфне) зв'язування.

#include <iostream>
#include <math.h>
#include <cstring>

using namespace std;

class Point
{
    protected:
        int x;
        int y;
    public:
        Point(int x, int y)
        {
            cout<< "Base Contsructor"<<endl;
            this->x = x;
            this->y = y;
        }
        ~Point()
        {
            cout<<"base destructor"<<endl;
        }

        void Print()const
        {
            cout<< "x: " << x << ", y: " << y << endl ;
        }
};

class ColorPoint: public Point
{
    public:
        char* color;

    ColorPoint(int x, int y, const char* color):Point(x, y)
    {
        cout << "Color construcor" << endl;
        this->x = x;
        this->y = y;
        this->color = new char[strlen(color)+1];
        strcpy(this->color, color);
    }
    ~ColorPoint()
    {
        cout<<"Color destructor"<<endl;
    }
    void Print()const
    {
        Point::Print();
        cout<< " "<< color << endl; 
    }
};

class Point3D: public Point
{
    public:
        int z;

    Point3D(int x, int y, int z): Point(x,y)
    {
        cout << "3D Constructor"<< endl;
        this->x = x;
        this->y = y;
        this->z = z;
    }
    ~Point3D()
    {
        cout<< "3D dectrucor"<< endl;
    }
    void Print()const
    {
        cout<< "Special print x: " << x << ", y: " << y << " z: "<< z << endl;;
    }
};

int main()
{
    Point p1(4, 4);
    p1.Print();
    
    Point3D poin(1, 2, 3);
    poin.Print();

    ColorPoint colorp(1, 3, "red");
    colorp.Print();

    Point *p = new Point3D (1, 1, 1);

    p->Print();

    delete p;

    return 0;
}