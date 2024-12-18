//2024_09_20 
#include <iostream> 
#include <math.h> 
using namespace std; 
 
class Parallelogram 
{ 
    private:  
        int base; 
        int height; 
        int angle; 
    public: 
        Parallelogram() 
        { 
            cout << "Input in class. Please, enther the base\n"; 
            cin >> base; 
            cout << "Please, enther the height\n"; 
            cin >> height; 
            cout << "Please, enther the interior angle\n"; 
            cin >> angle; 
        } 
        Parallelogram(int base, int height, int angle) 
        { 
            this->base = base; 
            this->height = height; 
            this->angle = angle; 
        } 
        void Output_data() 
        { 
            cout << "Width: " << base << " Length: " << height << " Angle: " << angle << "\n"; 
        } 
        int Area() 
        { 
            return base*height; 
        } 
        int Perimetr() 
        { 
            return 2*(base + height/cos(angle*M_PI/180)); 
        } 
        ~Parallelogram() 
        { 
            cout << "deleting EVERYTHINg\n"; 
        } 
}; 
 
int main() 
{ 
    int base1 = 0, height1 = 0, angle1 = 0; 
    Parallelogram pr1; 
 
    cout << "Input in main. Please, enther the base\n"; 
    cin >> base1; 
    cout << "Please, enther the height\n"; 
    cin >> height1; 
    cout << "Please, enther the angle\n"; 
    cin >> angle1; 
 
 
    Parallelogram pr2(base1, height1, angle1); 
 
    cout << "Area 1: " << pr1.Area() << " Area 2: " << pr2.Area() <<"\n"; 
    cout << "Perimetr 1: " << pr1.Perimetr() << " Perimetr 2: " << pr2.Perimetr() <<  "\n";  
 
 
    Parallelogram * pr_array = new Parallelogram[3]; 
 
    for (int i = 0; i < 3; i++) 
    { 
        cout << i + 1 << "."; 
        pr_array[i].Output_data(); 
        cout << "Area: " << pr_array[i].Area() << " Perimetr: " << pr_array[i].Perimetr() << "\n"; 
    } 
     
    delete [] pr_array; 
 
    return 0; 
}