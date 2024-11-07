#include <iostream>
#include <string>

using namespace std;

class Book {
public:
    string title;
    string author;
    int year;
    int pages;

    Book(const string& t, const string& a, int y, int p)
        : title(t), author(a), year(y), pages(p) {}

    // коонструктор по умолчанию
    Book() : title(""), author(""), year(0), pages(0) {}

    void display() const {
        cout << "Назва: " << title << ", Автор: " << author << ", Рік: " << year << ", Сторінок: " << pages << endl;
    }
};

class Library {
private:
    Book* books;
    int count;

public:
    Library() : books(nullptr), count(0) {}

    ~Library() {
        delete[] books;
    }

    void addBook(const string& title, const string& author, int year, int pages) {
        Book* newLibrary = new Book[count + 1];
        for (int i = 0; i < count; i++) {
            newLibrary[i] = books[i];
        }
        newLibrary[count] = Book(title, author, year, pages);
        delete[] books;
        books = newLibrary;
        count++;
        cout << "Книга додана: " << title << endl;
    }

    void removeBook(const string& title) {
        int indexToRemove = -1;
        for (int i = 0; i < count; i++) {
            if (books[i].title == title) {
                indexToRemove = i;
                break;
            }
        }

        if (indexToRemove == -1) {
            cout << "Книга не знайдена: " << title << endl;
            return;
        }

        Book* newLibrary = new Book[count - 1];
        for (int i = 0, j = 0; i < count; i++) {
            if (i != indexToRemove) {
                newLibrary[j++] = books[i];
            }
        }

        delete[] books;
        books = newLibrary;
        count--;
        cout << "Книга видалена: " << title << endl;
    }

    void searchBooksByAuthor(const string& author) const {
        bool found = false;
        cout << "Книги автора " << author << ":" << endl;
        for (int i = 0; i < count; i++) {
            if (books[i].author == author) {
                books[i].display();
                found = true;
            }
        }
        if (!found) {
            cout << "Книг цього автора не знайдено." << endl;
        }
    }

    void displayAllBooks() const {
        if (count == 0) {
            cout << "Бібліотека порожня." << endl;
            return;
        }
        cout << "Список усіх книг у бібліотеці:" << endl;
        for (int i = 0; i < count; i++) {
            books[i].display();
        }
    }
};

int main() {
    Library library;
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
                cin.ignore();
                getline(cin, title);
                cout << "Введіть автора: ";
                getline(cin, author);
                cout << "Введіть рік видання: ";
                cin >> year;
                cout << "Введіть кількість сторінок: ";
                cin >> pages;
                library.addBook(title, author, year, pages);
                break;
            }
            case 2: {
                string title;
                cout << "Введіть назву книги для видалення: ";
                cin.ignore();
                getline(cin, title);
                library.removeBook(title);
                break;
            }
            case 3: {
                string author;
                cout << "Введіть ім'я автора для пошуку: ";
                cin.ignore
                getline(cin, author);
                library.searchBooksByAuthor(author);
                break;
            }
            case 4:
                library.displayAllBooks();
                break;
            case 5:
                cout << "Вихід з програми." << endl;
                return 0;
            default:
                cout << "Неправильний вибір. Спробуйте ще раз." << endl;
        }
    }
    return 0;
}
