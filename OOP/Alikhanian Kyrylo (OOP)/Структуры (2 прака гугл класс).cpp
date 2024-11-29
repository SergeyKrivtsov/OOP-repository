#include <iostream>
#include <vector>
#include <string>
#include <optional>
#include <iomanip>

using namespace std;

struct Book {
    int id;
    string title;
    string author;
    bool isAvailable;
};

struct Reader {
    int id;
    string name;
    vector<int> borrowedBooks;
};

struct BorrowRecord {
    int bookId;
    int readerId;
    string borrowDate;
    string returnDate;
};

class Library {
private:
    vector<Book> books;
    vector<Reader> readers;
    vector<BorrowRecord> records;
    int nextBookId = 1;
    int nextReaderId = 1;

public:
    void addBook(const string& title, const string& author) {
        books.push_back({ nextBookId++, title, author, true });
        cout << "Книга \"" << title << "\" додана успішно!" << endl;
    }

    void addReader(const string& name) {
        readers.push_back({ nextReaderId++, name, {} });
        cout << "Читач \"" << name << "\" зареєстрований успішно!" << endl;
    }

    bool borrowBook(int bookId, int readerId, const string& date) {
        auto book = find_if(books.begin(), books.end(), [bookId](const Book& b) { return b.id == bookId; });
        auto reader = find_if(readers.begin(), readers.end(), [readerId](const Reader& r) { return r.id == readerId; });

        if (book == books.end() || reader == readers.end()) {
            cout << "Невірний ID книги або читача!" << endl;
            return false;
        }

        if (!book->isAvailable) {
            cout << "Книга недоступна!" << endl;
            return false;
        }

        book->isAvailable = false;
        reader->borrowedBooks.push_back(bookId);
        records.push_back({ bookId, readerId, date, "" });
        cout << "Книга видана успішно!" << endl;
        return true;
    }

    bool returnBook(int bookId, int readerId, const string& date) {
        auto book = find_if(books.begin(), books.end(), [bookId](const Book& b) { return b.id == bookId; });
        auto reader = find_if(readers.begin(), readers.end(), [readerId](const Reader& r) { return r.id == readerId; });

        if (book == books.end() || reader == readers.end()) {
            cout << "Невірний ID книги або читача!" << endl;
            return false;
        }

        auto record = find_if(records.begin(), records.end(), [bookId, readerId](const BorrowRecord& r) {
            return r.bookId == bookId && r.readerId == readerId && r.returnDate.empty();
            });

        if (record == records.end()) {
            cout << "Не знайдено запису про видачу книги!" << endl;
            return false;
        }

        book->isAvailable = true;
        reader->borrowedBooks.erase(remove(reader->borrowedBooks.begin(), reader->borrowedBooks.end(), bookId), reader->borrowedBooks.end());
        record->returnDate = date;
        cout << "Книга повернена успішно!" << endl;
        return true;
    }

    void showBooks() {
        cout << left << setw(5) << "ID" << setw(30) << "Назва" << setw(20) << "Автор" << setw(10) << "Статус" << endl;
        for (const auto& book : books) {
            cout << left << setw(5) << book.id << setw(30) << book.title << setw(20) << book.author
                << setw(10) << (book.isAvailable ? "Доступна" : "Видана") << endl;
        }
    }
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
