/*
Реалізувати клас Window за допомогою класу Rectangle двома способами (закрите спадкування, композиція).
Забезпечити інтерфейс для переміщення вікна в задану точку, обчислення площі та інших характеристик.
*/
#include <iostream>
using namespace std;
class Rectangle {
    private:
        int width, height;
    public:
        Rectangle(int w, int h){
            width = w;
            height = h;
        }
        int g_Width() const{
            return width; 
        }
        int g_Height() const{
            return height;
        }
        int g_Area() const {
            return width * height;
        }
};
/*
//Закрите наслідування
class Window : private Rectangle {
    private:
        int x, y;
    public:
        Window(int x, int y, int width, int height): Rectangle(width, height){
            this->x = x;
            this->y = y;
        }
        void moveTo(int newX, int newY) {
            x = newX;
            y = newY;
        }
        int getX() const{
            return x;
        }
        int getY() const{
            return y;
        }
        int g_Width() const{
            return Rectangle::g_Width();
        }
        int g_Height() const{
            return Rectangle::g_Height();
        }
        int g_Area() const{
            return Rectangle::g_Area();
        }
        void display() const{
            cout << "Window at (" << x << ", " << y << "), " << "width: " << g_Width() << ", height: " << h_Width() << ", area is: " << g_Area() << endl;
        }
};
*/
// /*
//Композиція
class Window {
    private:
        int x, y;
        Rectangle rect;
    public:
        Window(int x, int y, int width, int height): x(x), y(y), rect(width, height) {}
        void moveTo(int newX, int newY) {
            x = newX;
            y = newY;
        }
        int getX()const{
            return x;
        }
        int getY()const{
            return y;
        }
        int getWidth()const{
            return rect.g_Width();
        }
        int getHeight()const{
            return rect.g_Height();
        }
        int g_Area()const{
            return rect.g_Area();
        }
        void display() const {
            cout << "Window at (" << x << ", " << y << "), " << "width: " << getWidth() << ", height: " << getHeight() << ", area: " << g_Area() << std::endl;
        }
};
// */
int main() {
    Window win1(10, 20, 100, 50);
    win1.display();
    win1.moveTo(30, 40);
    win1.display();
    return 0;
}