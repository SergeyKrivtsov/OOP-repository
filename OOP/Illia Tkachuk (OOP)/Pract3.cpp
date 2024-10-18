#include <iostream>
#include <string>
using namespace std;

struct Student {
    string lastName;
    int studyYear;
    float averageGrade;
};

Student addStudent(const string& lastName, int studyYear, float averageGrade) {
    Student student;
    student.lastName = lastName;
    student.studyYear = studyYear;
    student.averageGrade = averageGrade;
    return student;
}

Student addStudent(const string& lastName, int studyYear) {
    return addStudent(lastName, studyYear, 4.0);
}

Student addStudent(const string& lastName) {
    return addStudent(lastName, 1, 4.0);
}

Student addStudent() {
    return addStudent("Іванов", 1, 4.0);
}

void displayStudent(const Student& student) {
    cout << "Прізвище: " << student.lastName << ", Рік навчання: " << student.studyYear
         << ", Середній бал: " << student.averageGrade << endl;
}

int main() {
    Student student1 = addStudent();
    Student student2 = addStudent("Дмитренко");
    Student student3 = addStudent("Шевцов", 2);
    Student student4 = addStudent("Калиненко", 3, 4.5);

    displayStudent(student1);
    displayStudent(student2);
    displayStudent(student3);
    displayStudent(student4);

    return 0;
}
