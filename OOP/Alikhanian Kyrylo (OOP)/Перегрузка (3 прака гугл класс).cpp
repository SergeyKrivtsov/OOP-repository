#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct Student {
    string surname;
    int year;
    double averageGrade;
};

class TractorCourses {
private:
    vector<Student> students;

public:
    void addStudent(const string& surname = "Іванов", int year = 1, double averageGrade = 4.0) {
        students.push_back({ surname, year, averageGrade });
    }

    void addStudent(const string& surname, double averageGrade) {
        students.push_back({ surname, 1, averageGrade });
    }

    void showStudents() {
        cout << left << setw(20) << "Прізвище" << setw(10) << "Рік" << setw(10) << "Середній бал" << endl;
        for (const auto& student : students) {
            cout << left << setw(20) << student.surname << setw(10) << student.year << setw(10) << student.averageGrade << endl;
        }
    }
};

int main() {
    TractorCourses courses;

    courses.addStudent();
    courses.addStudent("Петров", 2, 4.5);
    courses.addStudent("Сидоров", 3.8);
    courses.addStudent("Іванов", 3, 4.2);
    courses.showStudents();

    return 0;
}
