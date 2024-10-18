/*
У селі Іванівка більшість мешканців мають прізвище Іванов.
При записі на курси трактористів для кожного
вступника зберігається прізвище, початковий рік навчання (за замовчуванням –
перший) та середній бал атестату (float) (у ільшості – 4).
Використовуючи перевантаження функцій та параметри за
замовчуванням, реалізувати мінімальну кількість функцій для комфортного
введення інформації про вступників (при виклику функцій задавати лише значення
параметрів, які відрізняються від замовчуваних).
*/
#include <iostream>
using namespace std;
class Tr_Student{
    private:
        string name;
        int study_year;
        float avg_atestat;
    public:
        Tr_Student(float avg_atestat = 4.0, string name = "Ivanov", int study_year = 1){
            this->name = name;
            this->study_year = study_year;
            this->avg_atestat = avg_atestat;
        }
        Tr_Student(int study_year){
            this->name = "Ivanov";
            this->study_year = study_year;
            this->avg_atestat = 4.0;
        }
        Tr_Student(string name){
            this->name = name;
            this->study_year = 1;
            this->avg_atestat = 4.0;
        }
        Tr_Student(float avg_atestat, int study_year){
            this->name = "Ivanov";
            this->study_year = study_year;
            this->avg_atestat = avg_atestat;
        }
        Tr_Student(string name, int study_year){
            this->name = name;
            this->study_year = study_year;
            this->avg_atestat = 4.0;
        }
        void print_Student() {
            cout << "The name of student is " << name << endl;
            cout << "The study year of student is " << study_year << endl;
            cout << "The avg atestat of student is " << avg_atestat << endl;
            cout << "-------" << endl;
        }
};
int main(){
    cout << "Call with all parameters by default" << endl;
    Tr_Student St0;
    St0.print_Student();
    cout << "Call only with an avg" << endl;
    Tr_Student St1((float)2.8);
    St1.print_Student();
    cout << "Call only with a name" << endl;
    Tr_Student St2("Petrov");
    St2.print_Student();
    cout << "Call only with a year" << endl;
    Tr_Student St3(3);
    St3.print_Student();
    cout << "Call with an avg and name" << endl;
    Tr_Student St4(1.9, "Makarov");
    St4.print_Student();
    cout << "Call with an avg and year" << endl;
    Tr_Student St5(1.9, 2);
    St5.print_Student();
    cout << "Call with an name and year" << endl;
    Tr_Student St6("NeIvanov", 4);
    St6.print_Student();
    cout << "Call with all changed" << endl;
    Tr_Student St7(4.9, "Chuvaikin", 2);
    St7.print_Student();
}