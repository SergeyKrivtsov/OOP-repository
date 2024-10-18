//Розробити клас, похідний класу Point. Протестувати раннє
//та пізніше (поліморфне) зв'язування.
#include <iostream>
#include <cstring>
using namespace std;
class Point{
    protected:
        int x;
        int y;
    public:
        Point(int x, int y){
            cout << "I was created!" << endl;
            this->x = x;
            this->y = y;
        }
        virtual void Reflect(){
            x = -x;
            y = -y;
        }
        ~Point(){
            cout << "I was destructed!" << endl;
        }
        void Print() const{
            cout << "(" << x << "," << y << ")" << endl;
        }
};
class NamePoint: public Point{
    public:
        char* name;
        NamePoint(int x, int y, const char* name): Point(x, y){
            cout << "Derived creating" << endl;
            this->x = x;
            this->y = y;
            this->name = new char[strlen(name)+1];
            strcpy(this->name, name);
        }
        ~NamePoint(){
            cout << "Derived destructor!" << endl;
        }
        void Print() const{
            cout << name << ": ";
            Point::Print();
        }
        void Reflect() override {
            x = -x;
            y = -y;
            char* temp_name = new char[strlen(name)];
            strcpy(temp_name, name);
            this->name = new char[strlen(name)+1];
            this->name[0] = '-';
            for(int i = 0; i < strlen(name); i++){
                this->name[i+1] = temp_name[i];
            }
        }
};
int main()
{
    NamePoint A(1, 1, "A2");
    A.Print();
    A.Reflect();
    A.Print();
    Point *p = new NamePoint(10, 10, "G1");
    p->Print();
    return 0;
}