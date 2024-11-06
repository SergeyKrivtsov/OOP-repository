#include <iostream>
#include <string>
using namespace std;

struct Book {
    string title;
    string author;
    int year;
    int pages;
};

Book* addBook(Book* library, int& count, const string& title, const string& author, int year, int pages) {
    Book* newLibrary = new Book[count + 1];
    for (int i = 0; i < count; i++) {
        newLibrary[i] = library[i];
    }
    newLibrary[count].title = title;
    newLibrary[count].author = author;
    newLibrary[count].year = year;
    newLibrary[count].pages = pages;
    count++;
    delete[] library;
    cout << "Книга додана: " << title << endl;
    return newLibrary;
}

Book* removeBook(Book* library, int& count, const string& title) {
    int indexToRemove = -1;
    for (int i = 0; i < count; i++) {
        if (library[i].title == title) {
            indexToRemove = i;
            break;
        }
    }

    if (indexToRemove == -1) {
        cout << "Книга не знайдена: " << title << endl;
        return library;
    }

    Book* newLibrary = new Book[count - 1];
    for (int i = 0, j = 0; i < count; i++) {
        if (i != indexToRemove) {
            newLibrary[j++] = library[i];
        }
    }
    count--;
    delete[] library;
    cout << "Книга видалена: " << title << endl;
    return newLibrary;
}

void searchBooksByAuthor(Book* library, int count, const string& author) {
    bool found = false;
    cout << "Книги автора " << author << ":" << endl;
    for (int i = 0; i < count; i++) {
        if (library[i].author == author) {
            cout << "Назва: " << library[i].title << ", Рік: " << library[i].year << ", Сторінок: " << library[i].pages << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Книг цього автора не знайдено." << endl;
    }
}

void displayAllBooks(Book* library, int count) {
    if (count == 0) {
        cout << "Бібліотека порожня." << endl;
        return;
    }
    cout << "Список усіх книг у бібліотеці:" << endl;
    for (int i = 0; i < count; i++) {
        cout << "Назва: " << library[i].title << ", Автор: " << library[i].author << ", Рік: " << library[i].year << ", Сторінок: " << library[i].pages << endl;
    }
}

void freeLibrary(Book* library) {
    delete[] library;
}

int main() {
    Book* library = nullptr;
    int count = 0;
    int choice;

    while (true) {
        cout << "\nМеню:\n";
        cout << "1. Додати книгу\n";
        cout << "2. Видалити книгу\n";
        cout << "3. Пошук книг за автором\n";
        cout << "4. Вивести всі книги\n";
        cout << "5. Вихід\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string title, author;
                int year, pages;
                cout << "Введіть назву книги: ";
                cin >> title;
                cout << "Введіть автора: ";
                cin >> author;
                cout << "Введіть рік видання: ";
                cin >> year;
                cout << "Введіть кількість сторінок: ";
                cin >> pages;
                library = addBook(library, count, title, author, year, pages);
                break;
            }
            case 2: {
                string title;
                cout << "Введіть назву книги для видалення: ";
                cin >> title;
                library = removeBook(library, count, title);
                break;
            }
            case 3: {
                string author;
                cout << "Введіть ім'я автора для пошуку: ";
                cin >> author;
                searchBooksByAuthor(library, count, author);
                break;
            }
            case 4:
                displayAllBooks(library, count);
                break;
            case 5:
                freeLibrary(library);
                cout << "Вихід з програми." << endl;
                return 0;
            default:
                cout << "Неправильний вибір. Спробуйте ще раз." << endl;
        }
    }
    return 0;
}
