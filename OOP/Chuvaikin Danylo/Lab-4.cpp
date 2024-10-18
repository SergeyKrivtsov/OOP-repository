//Розробити клас прямокутник, задати розумну поведінку та протестувати на 
//об'єктах класу, покажчиках на об'єкт класу, масиві об'єктів.
#include <iostream>
using namespace std;
class Rectangle{
    private:
        int width;
        int height;
    public:
        Rectangle(int w, int h){
            width = w;
            height = h;
        }
        Rectangle(){
            width = 1;
            height = 1;
        }
        int Perimetr(){
            return width * 2 + height * 2;
        }
        int Square(){
            return width * height;
        }
};
int main()
{
    //Тестування на об'єктах класу
    Rectangle rect_1(10, 10);
    cout << "The square of this rect is " << rect_1.Square() << endl;
    //Тестування на масиві об'єктів.
    Rectangle* dynamic_rect = new Rectangle(10, 10);
    cout << "The square of dynamic rect is " << dynamic_rect->Square() << endl;
    //Тестування на масивах
    int amount;
    Rectangle rect_massive[amount];
    cout << "Enter how many par you want to enter" << endl;
    cin >> amount;
    for(int i = 0; i < amount; i ++){
        int temp_w, temp_h;
        cout << "Enter width of " << i + 1 << " Rectangle" << endl;
        cin >> temp_w;
        cout << "Enter heigt of " << i + 1 << " Rectangle" << endl;
        cin >> temp_h;
        Rectangle temp_rect(temp_w, temp_h);
        rect_massive[i] = temp_rect;
    }
    for(int i = 0; i < amount; i ++){
        cout << "The square of " << i+1 << " rect is: " << rect_massive[i].Square() << endl;
        cout << "The perimetr of " << i+1 << " rect is: " << rect_massive[i].Perimetr() << endl;
    }
}