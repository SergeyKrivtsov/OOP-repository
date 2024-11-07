/*
Наказ про відрахування. Є набір текстових файлів – відомості з
предметів. Ім'я файлу містить назву предмета, а файл містить набір рядків,
у кожному з яких ПІБ студента та його оцінка з цього предмета. Потрібно
створити інформацію для наказу на відрахування у вигляді списку
списків; список ПІБ студентів, упорядкований за абеткою, і для кожного
студента – список назв предметів, за якими у нього хвіст (менше 50 балів).
Забезпечити операції додавання, видалення та розумного пошуку
інформації, виведення інформації в розумному вигляді (наприклад, список
всіх «хвостистів» з конкретного предмету з кількістю балів).
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLEAR_COMMAND "cls"
#define MAX_NAME_LEN 100
#define MAX_SUBJ_LEN 50
#define PASSING_SCORE 50

typedef struct SubjectGrade {
    char subject[MAX_SUBJ_LEN];
    int grade;
    struct SubjectGrade* next;
} SubjectGrade;

typedef struct StudentRecord {
    char name[MAX_NAME_LEN];
    SubjectGrade* grades;
    struct StudentRecord* next;
} StudentRecord;

void clearConsole() {
    system(CLEAR_COMMAND);
}

StudentRecord* createStudent(const char* name) {
    StudentRecord* newStudent = (StudentRecord*)malloc(sizeof(StudentRecord));
    strncpy(newStudent->name, name, MAX_NAME_LEN - 1);
    newStudent->name[MAX_NAME_LEN - 1] = '\0';
    newStudent->grades = NULL;
    newStudent->next = NULL;
    return newStudent;
}

void addGrade(StudentRecord* student, const char* subject, int grade) {
    SubjectGrade* newGrade = (SubjectGrade*)malloc(sizeof(SubjectGrade));
    strncpy(newGrade->subject, subject, MAX_SUBJ_LEN - 1);
    newGrade->subject[MAX_SUBJ_LEN - 1] = '\0';
    newGrade->grade = grade;
    newGrade->next = student->grades;
    student->grades = newGrade;
}

void addStudentSorted(StudentRecord** head, StudentRecord* student) {
    if (*head == NULL || strcmp((*head)->name, student->name) > 0) {
        student->next = *head;
        *head = student;
    } else {
        StudentRecord* current = *head;
        while (current->next != NULL && strcmp(current->next->name, student->name) < 0) {
            current = current->next;
        }
        student->next = current->next;
        current->next = student;
    }
}

StudentRecord* findStudent(StudentRecord* head, const char* name) {
    while (head != NULL) {
        if (strcmp(head->name, name) == 0) return head;
        head = head->next;
    }
    return NULL;
}

void readSubjectFile(StudentRecord** head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char line[200];
    char name[MAX_NAME_LEN];
    int grade;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        char* lastSpace = strrchr(line, ' ');
        if (lastSpace == NULL) {
            printf("Error in line format: %s\n", line);
            continue;
        }

        grade = atoi(lastSpace + 1);
        *lastSpace = '\0';

        strncpy(name, line, MAX_NAME_LEN);
        StudentRecord* student = findStudent(*head, name);
        if (student == NULL) {
            student = createStudent(name);
            addStudentSorted(head, student);
        }
        addGrade(student, filename, grade);
    }

    fclose(file);
}

void printStudentsWithFails(StudentRecord* head) {
    printf("List of students with failing grades:\n");
    while (head != NULL) {
        int hasFails = 0;
        SubjectGrade* grade = head->grades;
        while (grade != NULL) {
            if (grade->grade < PASSING_SCORE) {
                if (!hasFails) {
                    printf("%s:\n", head->name);
                    hasFails = 1;
                }
                printf("  %s - %d\n", grade->subject, grade->grade);
            }
            grade = grade->next;
        }
        head = head->next;
    }
}

void addStudentToFile(StudentRecord** head, const char* filename) {
    char name[MAX_NAME_LEN];
    char subject[MAX_SUBJ_LEN];
    int grade;

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: File %s does not exist.\n", filename);
        return;
    }
    fclose(file);

    printf("Enter student's full name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Enter subject: ");
    fgets(subject, sizeof(subject), stdin);
    subject[strcspn(subject, "\n")] = '\0';

    printf("Enter grade: ");
    scanf("%d", &grade);
    getchar(); // Clear buffer

    file = fopen(filename, "a");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    fprintf(file, "\n%s %d", name, grade);
    fclose(file);

    StudentRecord* student = findStudent(*head, name);
    if (student == NULL) {
        student = createStudent(name);
        addStudentSorted(head, student);
    }
    addGrade(student, subject, grade);
}

void deleteStudent(StudentRecord** head, const char* name, const char* filename) {
    StudentRecord *current = *head, *prev = NULL;

    while (current != NULL && strcmp(current->name, name) != 0) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Student not found.\n");
        return;
    }

    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }
    free(current);

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    FILE* tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        perror("Error opening temporary file");
        fclose(file);
        return;
    }

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, name) == NULL || !strstr(line, " ")) {
            fprintf(tempFile, "%s", line);
        }
    }

    fclose(file);
    fclose(tempFile);
    remove(filename);
    rename("temp.txt", filename);

    printf("Student %s deleted successfully.\n", name);
}

void menu(StudentRecord** head) {
    int choice;
    char filename[MAX_SUBJ_LEN];
    char name[MAX_NAME_LEN];

    do {
        clearConsole();
        printf("\nMenu:\n");
        printf("1. Display list of students with failing grades\n");
        printf("2. Add student and grade to file\n");
        printf("3. Delete student from list and file\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printStudentsWithFails(*head);
                break;
            case 2:
                printf("Enter file name (e.g., math.txt): ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                addStudentToFile(head, filename);
                break;
            case 3:
                printf("Enter student name to delete: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                printf("Enter file name (e.g., math.txt): ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                deleteStudent(head, name, filename);
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

        printf("\nPress Enter to return to the menu...");
        getchar();
    } while (choice != 4);
}
void freeStudentList(StudentRecord* head) {
    while (head != NULL) {
        StudentRecord* tmp = head;
        head = head->next;

        SubjectGrade* grade = tmp->grades;
        while (grade != NULL) {
            SubjectGrade* tmpGrade = grade;
            grade = grade->next;
            free(tmpGrade);
        }
        free(tmp);
    }
}

int main() {
    StudentRecord* head = NULL;

    readSubjectFile(&head, "math.txt");
    readSubjectFile(&head, "history.txt");
    readSubjectFile(&head, "physics.txt");

    menu(&head);

    freeStudentList(head);
    return 0;
}