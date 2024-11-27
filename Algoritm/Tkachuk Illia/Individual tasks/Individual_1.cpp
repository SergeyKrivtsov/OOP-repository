#include <iostream>
#include <cstring>

using namespace std;

struct Student {
   char surname[50];       
   char name[50];          
   char patronymic[50];    
   int birthYear;          
   int course;             
   int groupNumber;        
   double averageGrade;    
   Student* next;          
};

bool isValidName(const char* str) {
   for (int i = 0; str[i] != '\0'; i++) {
      if (!isalpha(str[i])) {
         return false;
      }
   }
   return true;
}

bool isValidBirthYear(int year) {
   return year >= 1970 && year <= 2006;
}

bool isValidCourse(int course) {
   return course >= 1 && course <= 4;
}

bool isValidAverageGrade(double grade) {
   return grade >= 0.0 && grade <= 5.0;
}

bool isValidGroupNumber(int groupNumber) {
   return groupNumber == 101 || groupNumber == 102;
}

void addStudent(Student*& head, const char* surname, const char* name, const char* patronymic, int birthYear, int course, int groupNumber, double averageGrade) {
   Student* newStudent = new Student;
   strcpy(newStudent->surname, surname);
   strcpy(newStudent->name, name);
   strcpy(newStudent->patronymic, patronymic);
   newStudent->birthYear = birthYear;
   newStudent->course = course;
   newStudent->groupNumber = groupNumber;
   newStudent->averageGrade = averageGrade;
   newStudent->next = nullptr;

   if (!head || strcmp(newStudent->surname, head->surname) < 0 ||
      (strcmp(newStudent->surname, head->surname) == 0 && strcmp(newStudent->name, head->name) < 0)) {
      newStudent->next = head;
      head = newStudent;
   } else {
         Student* current = head;
         while (current->next &&
               (strcmp(current->next->surname, newStudent->surname) < 0 ||
               (strcmp(current->next->surname, newStudent->surname) == 0 && strcmp(current->next->name, newStudent->name) < 0))) {
            current = current->next;
      }

      newStudent->next = current->next;
      current->next = newStudent;
   }
}

void printStudents(Student* head) {
   Student* current = head;
   while (current != nullptr) {
        cout << current->surname << " " << current->name << " " << current->patronymic
            << " | Year of birth: " << current->birthYear << " | Course: " << current->course
            << " | Group: " << current->groupNumber << " | Avg Grade: " << current->averageGrade << endl;
        current = current->next;
   }
}

void deleteStudentRecursive(Student*& head, const char* surname = nullptr, const char* name = nullptr, const char* patronymic = nullptr,
                           int groupNumberToDelete = -1, double gradeToDelete = -1.0, int courseToDelete = -1, int birthYearToDelete = -1) {
   if (head == nullptr) {
      return;
    }

    
   bool shouldDelete = (surname && strcmp(head->surname, surname) == 0) ||
                        (name && strcmp(head->name, name) == 0) ||
                        (patronymic && strcmp(head->patronymic, patronymic) == 0) ||
                        (groupNumberToDelete != -1 && head->groupNumber == groupNumberToDelete) ||
                        (gradeToDelete != -1.0 && head->averageGrade == gradeToDelete) ||
                        (courseToDelete != -1 && head->course == courseToDelete) ||
                        (birthYearToDelete != -1 && head->birthYear == birthYearToDelete);

   if (shouldDelete) {
      Student* temp = head;
      head = head->next;
      delete temp;
      deleteStudentRecursive(head, surname, name, patronymic, groupNumberToDelete, gradeToDelete, courseToDelete, birthYearToDelete);
   } else {
      deleteStudentRecursive(head->next, surname, name, patronymic, groupNumberToDelete, gradeToDelete, courseToDelete, birthYearToDelete);
   }
}

void clearList(Student*& head) {
    while (head != nullptr) {
        Student* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
   Student* head = nullptr;

   addStudent(head, "Ivanenko", "Ivan", "Ivanovych", 2000, 3, 101, 4.5);
   addStudent(head, "Ivanenko", "Oleksiy", "Oleksiyovych", 2001, 2, 101, 4.3);
   addStudent(head, "Petrenko", "Petro", "Petrovych", 1999, 4, 102, 4.3);
   addStudent(head, "Sydorenko", "Ilya", "Andriyovych", 2003, 2, 101, 4.8);
   addStudent(head, "Kalyna", "Danyl", "Olegovych", 2005, 1, 102, 3.7);
   addStudent(head, "Shevchenko", "Denys", "Serhiyovych", 1999, 4, 102, 2.2);

   cout << "List of students:" << endl;
   printStudents(head);

   char choice;
   while (true) {
      cout << "\nChoose a criterion to delete by:\n"
            << "1. Surname\n2. Name\n3. Patronymic\n4. Group Number\n5. Average Grade\n6. Course\n7. Birth Year\n8. Exit\nChoice: ";
      cin >> choice;

        char surname[50], name[50], patronymic[50];
        int groupNumber, course, birthYear;
        double grade;

         switch (choice) {
            case '1':
               cout << "Enter surname to delete: ";
               cin >> surname;
               deleteStudentRecursive(head, surname);
               break;
            case '2':
               cout << "Enter name to delete: ";
               cin >> name;
               deleteStudentRecursive(head, nullptr, name);
               break;
            case '3':
               cout << "Enter patronymic to delete: ";
               cin >> patronymic;
               deleteStudentRecursive(head, nullptr, nullptr, patronymic);
               break;
            case '4':
               cout << "Enter group number to delete: ";
               cin >> groupNumber;
               deleteStudentRecursive(head, nullptr, nullptr, nullptr, groupNumber);
               break;
            case '5':
               cout << "Enter average grade to delete: ";
               cin >> grade;
               deleteStudentRecursive(head, nullptr, nullptr, nullptr, -1, grade);
               break;
            case '6':
               cout<<"Enter course to delete: ";
               cin>>course;
               deleteStudentRecursive(head, nullptr, nullptr, nullptr, -1, -1.0, course);
               break;
            case '7':
               cout<<"Enter birth year to delete: ";
               cin>>birthYear;
               deleteStudentRecursive(head, nullptr, nullptr, nullptr, -1, -1.0, -1, birthYear);
               break;
            case '8':
               cout<<"Exiting program."<<endl;
               clearList(head);
               return 0;
            default:
               cout<<"Invalid choice! Try again."<<endl;
               break;
        }

      cout<<"\nList of students after deletion:"<<endl;
      printStudents(head);
    }

    return 0;
}
