/*
Створити клас паралелограм, який задається трьома координатами у двовимірному просторі
*/
#include <iostream>
#include <cmath>
using namespace std;
class Paralelogram{
    private:
        double first_cord[2];
        double second_cord[2];
        double third_cord[2];
    public:
        Paralelogram(double first[2], double second[2], double third[2]){
            for(int i = 0; i <= 1; i++){
                first_cord[i] = first[i];
                second_cord[i] = second[i];
                third_cord[i] = third[i];
            }
        }
        Paralelogram(double second[2], double third[2]){
            double first[2] = {0, 0};
            for(int i = 0; i <= 1; i++){
                first_cord[i] = first[i];
                second_cord[i] = second[i];
                third_cord[i] = third[i];
            }
        }
        double Square(){
            double mod_1 = sqrt(pow((second_cord[0] - first_cord[0]), 2) + pow((second_cord[1] - first_cord[1]), 2));
            double mod_2 = sqrt(pow((third_cord[0] - first_cord[0]), 2) + pow((third_cord[1] - first_cord[1]), 2));
            double square = mod_1*mod_2*sqrt((1 - pow(((second_cord[0] - first_cord[0]) * (third_cord[0] - first_cord[0]) + (second_cord[1] - first_cord[1]) * (third_cord[1] - first_cord[1]))/(mod_1 * mod_2), 2)));
            return square;
        }
        double Perimetr(){
            return 2* (sqrt(pow((second_cord[0] - first_cord[0]), 2) + pow((second_cord[1] - first_cord[1]), 2)) + sqrt(pow((third_cord[0] - first_cord[0]), 2) + pow((third_cord[1] - first_cord[1]), 2)));
        }
        ~Paralelogram(){
            cout << "I died :((" << endl;
        }
};
int main()
{
    double f[] = {0,1};
    double s[] = {1,1};
    double t[] = {1,6};
    Paralelogram par1(f, s, t);
    cout << "Sqare: " << par1.Square() << endl;
    cout << "Perimetr: " << par1.Perimetr() << endl;
    return 0;
}