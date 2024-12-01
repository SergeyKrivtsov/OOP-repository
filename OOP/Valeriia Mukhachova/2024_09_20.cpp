//2024_09_20
//add coordinates
#include <iostream>
using namespace std;

class Parallelogram
{
    private: 
        int base;
        int height;
    public:
        Parallelogram()
        {
            cout << "Input in class. Please, enther the base\n";
            cin >> base;
            cout << "Please, enther the height\n";
            cin >> height;
        }
        Parallelogram(int base_U, int height_U)
        {
            base = base_U;
            height = height_U;
        }
        void Output_data()
        {
            cout << "Width: " << base << " Length: " << height << "\n";
        }
        int Area()
        {
            return base*height;
        }
        int Perimetr()
        {
            return 2*(base + height);
        }
};

int main()
{
    int base1 = 0, height1 = 0;
    Parallelogram pr1;

    cout << "Input in main. Please, enther the base\n";
    cin >> base1;
    cout << "Please, enther the height\n";
    cin >> height1;

    Parallelogram pr2(base1, height1);

    cout << "Area 1: " << pr1.Area() << " Area 2: " << pr2.Area() <<"\n";
    cout << " Perimetr 1: " << pr1.Perimetr() << " Perimetr 2: " << pr2.Perimetr() <<  "\n"; 


    Parallelogram pr_array[3];

    for (int i = 0; i < 3; i++)
    {
        cout << i << ".";
        pr_array[i].Output_data();
        cout << "Area: " << pr_array[i].Area() << " Perimetr: " << pr_array[i].Perimetr() << "\n";
    }

    return 0;
}

