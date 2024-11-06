#include <iostream>

using namespace std;

struct Book {
    int id;              
    string title;          
    string author;      
    int year;              
    Book* next;       

    Book(int bookId, const string& bookTitle, const string& bookAuthor, int bookYear) {
        id = bookId;
        title = bookTitle;
        author = bookAuthor;
        year = bookYear;
        next = nullptr;
    }
};

class Library {
private:
    Book* head; 

public:
    Library() {
        head = nullptr;
    }

    ~Library() {
        while (head != nullptr) {
            Book* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addBook(int id, const string& title, const string& author, int year) {
        Book* newBook = new Book(id, title, author, year);
        newBook->next = head;
        head = newBook;
        cout << "Book added: " << title << endl;
    }

    void removeBook(int id) {
        Book* current = head;
        Book* previous = nullptr;

        while (current != nullptr) {
            if (current->id == id) {
                if (previous == nullptr) {
                    head = current->next;
                }
                else {
                    previous->next = current->next;
                }
                cout << "Book removed: " << current->title << endl;
                delete current;
                return;
            }
            previous = current;
            current = current->next;
        }
        cout << "Book with ID " << id << " not found." << endl;
    }

    void listBooks() const {
        if (head == nullptr) {
            cout << "The library is empty." << endl;
            return;
        }

        Book* current = head;
        cout << "List of books in the library:" << endl;
        while (current != nullptr) {
            cout << "ID: " << current->id << ", Title: " << current->title << endl;
            current = current->next;
        }
    }

    void showBookDetails(int id) const {
        Book* current = head;
        while (current != nullptr) {
            if (current->id == id) {
                cout << "Book details:" << endl;
                cout << "ID: " << current->id << endl;
                cout << "Title: " << current->title << endl;
                cout << "Author: " << current->author << endl;
                cout << "Year of publication: " << current->year << endl;
                return;
            }
            current = current->next;
        }
        cout << "Book with ID " << id << " not found." << endl;
    }
};

int main() {
    Library library;

    library.addBook(1, "Book1", "bookAuthor1", 1970);
    library.addBook(2, "Book2", "bookAuthor2", 1949);
    library.addBook(3, "Book3", "bookAuthor3", 1966);

    library.listBooks();

    library.showBookDetails(2);

    library.removeBook(1);

    library.listBooks();

    return 0;
}
