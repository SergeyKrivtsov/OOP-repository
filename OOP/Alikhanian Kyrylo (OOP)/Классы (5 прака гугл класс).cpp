#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Book {
private:
    int id;
    string title;
    string author;
    bool isAvailable;

public:
    Book(int id, const string& title, const string& author);
    bool borrow();
    bool returnBook();
    string getTitle() const;
    string getAuthor() const;
    int getId() const;
    bool checkAvailability() const;
};

class Reader {
private:
    int id;
    string name;
    vector<int> borrowedBooks;

public:
    Reader(int id, const string& name);
    void borrowBook(int bookId);
    void returnBook(int bookId);
    vector<int> getBorrowedBooks() const;
    string getName() const;
    int getId() const;
};

class BorrowRecord {
private:
    int bookId;
    int readerId;
    string borrowDate;
    string returnDate;

public:
    BorrowRecord(int bookId, int readerId, const string& borrowDate);
    void setReturnDate(const string& date);
    bool isReturned() const;
    int getBookId() const;
    int getReaderId() const;
};

class Library {
private:
    vector<Book> books;
    vector<Reader> readers;
    vector<BorrowRecord> records;
    int nextBookId = 1;
    int nextReaderId = 1;

public:
    void addBook(const string& title, const string& author);
    void addReader(const string& name);
    bool borrowBook(int bookId, int readerId, const string& date);
    bool returnBook(int bookId, int readerId, const string& date);
    void showBooks();
};

int main() {
    Library library;

    library.addBook("Гаррі Поттер", "Джоан Роулінг");
    library.addBook("Війна і мир", "Лев Толстой");

    library.addReader("Олександр");
    library.addReader("Марія");

    library.showBooks();

    library.borrowBook(1, 1, "2024-11-22");
    library.showBooks();

    library.returnBook(1, 1, "2024-11-25");
    library.showBooks();

    return 0;
}
