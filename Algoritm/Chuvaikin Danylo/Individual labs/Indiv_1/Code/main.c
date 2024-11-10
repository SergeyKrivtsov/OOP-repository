#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 200
#define MAX_NAME_LEN 100
#define MAX_SUBJ_LEN 50
#define MIN_SCORE 50
#define SUBJECTS_FILE "subjects.txt"

typedef struct SubjectGrade{
    char subject[MAX_SUBJ_LEN];
    int grade;
    struct SubjectGrade* next;
} SubjectGrade;

typedef struct StudentRecord{
    char name[MAX_NAME_LEN];
    SubjectGrade* grades;
    struct StudentRecord* next;
} StudentRecord;

void clearConsole(){
    system("cls");
}

// Створення нового студента
StudentRecord* createStudent(const char* name){
    StudentRecord* newStudent = (StudentRecord*)malloc(sizeof(StudentRecord));
    strncpy(newStudent->name, name, MAX_NAME_LEN - 1);
    newStudent->name[MAX_NAME_LEN - 1] = '\0';
    newStudent->grades = NULL;
    newStudent->next = NULL;
    return newStudent;
}

// Додавання оцінки студенту
void addGrade(StudentRecord* student, const char* subject, int grade){
    SubjectGrade* newGrade = (SubjectGrade*)malloc(sizeof(SubjectGrade));
    strncpy(newGrade->subject, subject, MAX_SUBJ_LEN - 1);
    newGrade->subject[MAX_SUBJ_LEN - 1] = '\0';
    newGrade->grade = grade;
    newGrade->next = student->grades;
    student->grades = newGrade;
}

// Додавання студента у відсортований список
void addStudentSorted(StudentRecord** head, StudentRecord* student){
    if (*head == NULL || strcmp((*head)->name, student->name) > 0){
        student->next = *head;
        *head = student;
    } 
    else{
        StudentRecord* current = *head;
        while (current->next != NULL && strcmp(current->next->name, student->name) < 0){
            current = current->next;
        }
        student->next = current->next;
        current->next = student;
    }
}

// Пошук студента за ім'ям
StudentRecord* findStudent(StudentRecord* head, const char* name){
    while (head != NULL){
        if (strcmp(head->name, name) == 0){
            return head;
        }
        head = head->next;
    }
    return NULL;
}

// Отримання назви предмета без розширення
void extractSubjectName(const char* filename, char* subject){
    strncpy(subject, filename, MAX_SUBJ_LEN - 1);
    subject[MAX_SUBJ_LEN - 1] = '\0';
    char* dotPosition = strrchr(subject, '.');
    if (dotPosition) *dotPosition = '\0';
}

// Зчитування файлу з оцінками для предмета
void readSubjectFile(StudentRecord** head, const char* filename){
    FILE* file = fopen(filename, "r");
    if (file == NULL){
        puts("Error opening file");
        return;
    }
    char line[MAX_LINE_LEN];
    char name[MAX_NAME_LEN];
    int grade;
    char subject[MAX_SUBJ_LEN];
    extractSubjectName(filename, subject);

    while (fgets(line, sizeof(line), file)){
        line[strcspn(line, "\n")] = 0;

        char* lastSpace = strrchr(line, ' ');
        if (lastSpace == NULL){
            printf("Error in line format: %s\n", line);
            continue;
        }
        grade = atoi(lastSpace + 1);
        *lastSpace = '\0';
        strncpy(name, line, MAX_NAME_LEN);
        StudentRecord* student = findStudent(*head, name);
        if (student == NULL){
            student = createStudent(name);
            addStudentSorted(head, student);
        }
        addGrade(student, subject, grade);
    }
    fclose(file);
}

// Друк студентів із хвостами по предметах
void printStudentsWithFails(StudentRecord* head){
    printf("List of students with failing grades:\n");
    while (head != NULL){
        int hasFails = 0;
        SubjectGrade* grade = head->grades;
        while (grade != NULL){
            if (grade->grade < MIN_SCORE){
                if (!hasFails){
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
// Додавання предмету до файлу
void addSubjectToFile(const char* subject){
    FILE* subjectsFile = fopen(SUBJECTS_FILE, "a");
    if (subjectsFile){
        fseek(subjectsFile, 0, SEEK_END);
        long fileSize = ftell(subjectsFile);
        if (fileSize > 0){
            fprintf(subjectsFile, "\n%s", subject);
        }
        else{
            fprintf(subjectsFile, "%s", subject);
        }
        fclose(subjectsFile);
    }
}
// Додавання студента до файлу
void addStudentToFile(StudentRecord** head){
    char name[MAX_NAME_LEN];
    char filename[MAX_SUBJ_LEN];
    int grade;
    printf("Enter the subject filename (e.g., math): ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';

    char fullFilename[MAX_SUBJ_LEN + 5];
    snprintf(fullFilename, sizeof(fullFilename), "%s.txt", filename);

    FILE* file = fopen(fullFilename, "r");
    if (file == NULL){
        printf("File %s does not exist. Do you want to create it? (y/n): ", fullFilename);
        char response;
        scanf(" %c", &response);
        getchar();
        if (response == 'y' || response == 'Y'){
            file = fopen(fullFilename, "w");
            if (file == NULL){
                puts("Error creating file");
                return;
            }
            fclose(file);
            addSubjectToFile(filename);
        }
        else{
            printf("Operation cancelled.\n");
            return;
        }
    }
    else{
        fclose(file);
    }
    printf("Enter student's full name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    printf("Enter grade: ");
    scanf("%d", &grade);
    getchar();
    file = fopen(fullFilename, "a");
    if (file == NULL){
        puts("Error opening file");
        return;
    }
    // Пишемо з нового рядка тільки якщо файл не пустий
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    if(fileSize > 0){
        fprintf(file, "\n%s %d", name, grade);
    } 
    else{
        fprintf(file, "%s %d", name, grade);
    }
    fclose(file);
    StudentRecord* student = findStudent(*head, name);
    if(student == NULL){
        student = createStudent(name);
        addStudentSorted(head, student);
    }
    addGrade(student, filename, grade);
}

// Видалення студента з системи та файлу
void deleteStudent(StudentRecord** head, const char* name, const char* filename){
    StudentRecord *current = *head, *prev = NULL;
    while (current != NULL && strcmp(current->name, name) != 0){
        prev = current;
        current = current->next;
    }
    if (current == NULL){
        printf("Student not found.\n");
        return;
    }
    if (prev == NULL){
        *head = current->next;
    }
    else{
        prev->next = current->next;
    }
    free(current);
    FILE* file = fopen(filename, "r");
    if (file == NULL){
        puts("Error opening file");
        return;
    }
    FILE* tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL){
        puts("Error opening temporary file");
        fclose(file);
        return;
    }
    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), file)){
        if (strstr(line, name) == NULL || !strstr(line, " ")){
            fprintf(tempFile, "%s", line);
        }
    }
    fclose(file);
    fclose(tempFile);
    remove(filename);
    rename("temp.txt", filename);
    printf("Student %s deleted successfully.\n", name);
}

// Пошук студентів з "хвостами" по предмету
void searchFailsBySubject(StudentRecord* head, const char* subject){
    printf("Students with failing grades in %s:\n", subject);
    int found = 0;
    while (head != NULL){
        SubjectGrade* grade = head->grades;
        while (grade != NULL){
            if (strcmp(grade->subject, subject) == 0 && grade->grade < MIN_SCORE){
                printf("  %s - %d\n", head->name, grade->grade);
                found = 1;
            }
            grade = grade->next;
        }
        head = head->next;
    }
    if (!found){
        printf("No failing students found for %s.\n", subject);
    }
}

// Зчитування предметів із файла subjects.txt
void loadSubjects(StudentRecord** head){
    FILE* subjectsFile = fopen(SUBJECTS_FILE, "r");
    if (subjectsFile){
        char subject[MAX_SUBJ_LEN];
        while (fgets(subject, sizeof(subject), subjectsFile)){
            subject[strcspn(subject, "\n")] = '\0';
            char filename[MAX_SUBJ_LEN + 5];
            snprintf(filename, sizeof(filename), "%s.txt", subject);
            readSubjectFile(head, filename);
        }
        fclose(subjectsFile);
    }
}

// Основне меню
void menu(StudentRecord** head){
    int choice;
    char filename[MAX_SUBJ_LEN];
    char name[MAX_NAME_LEN];
    char subject[MAX_SUBJ_LEN];
    do{
        clearConsole();
        printf("\nHello! What do you want to do:\n");
        printf("1. Add a student\n");
        printf("2. Delete a student\n");
        printf("3. Show failing students\n");
        printf("4. Search fails by subject\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        getchar();

        switch (choice){
            case 1:
                addStudentToFile(head);
                break;
            case 2:
                printf("Enter student name to delete: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                printf("Enter subject filename (e.g., math): ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                snprintf(subject, sizeof(subject), "%s.txt", filename);
                deleteStudent(head, name, subject);
                break;
            case 3:
                printStudentsWithFails(*head);
                break;
            case 4:
                printf("Enter subject name to search for failing students: ");
                fgets(subject, sizeof(subject), stdin);
                subject[strcspn(subject, "\n")] = '\0';
                searchFailsBySubject(*head, subject);
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }

        printf("\nPress Enter to continue...");
        getchar();

    } while (choice != 5);
}

// Головна функція
int main(){
    StudentRecord* head = NULL;
    loadSubjects(&head);
    menu(&head);
    return 0;
}
