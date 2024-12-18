#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <string>
using namespace std;

// Константа для обмеження розміру масиву
const int MAX_BOOKS = 100;

//абстрактний клас (інтерфейс)
class Book 
{
    protected:
        string title;
        string author;
        //статична змінна
        static int bookCount; 

    public:
        //конструктор
        Book(const string& t, const string& a) : title(t), author(a) 
        {
            bookCount++;
        }
        //деструктор
        virtual ~Book() 
        {
            bookCount--;
        }

        static int getBookCount() 
        {
            return bookCount;
        }

        string getTitle() const 
        {
            return title;
        }

        string getAuthor() const 
        {
            return author;
        }

        //віртуальна функція для виводу інфо про книгу
        virtual void displayInfo() const = 0; 

        //віртуальна функція для запису книги у файл
        virtual void saveToFile(ofstream& file) const = 0;
};

//ініціалізація статичної змінної
int Book::bookCount = 0;

//перший клас-нащадок
class Fiction : public Book 
{
    private:
        string genre;

    public:
        //конструктор
        Fiction(const string& t, const string& a, const string& g) : Book(t, a), genre(g) {}
        //перевизначення віртуальної функції
        void displayInfo() const override 
        {
            cout << "Fiction Book: " << title << ", Author: " << author << ", Genre: " << genre << endl;
        }

        //перезавантаження saveToFile
        void saveToFile(ofstream& file) const override 
        {
            file << "Fiction," << title << "," << author << "," << genre << endl;
        }

        string getGenre() const 
        {
            return genre;
        }
};

//другий клас-нащадок
class NonFiction : public Book 
{
    private:
        string subject;

    public:
        //конструктор
        NonFiction(const string& t, const string& a, const string& s) : Book(t, a), subject(s) {}
        //перевізначення віртуальної функції
        void displayInfo() const override 
        {
            cout << "Non-Fiction Book: " << title << ", Author: " << author << ", Subject: " << subject << endl;
        }

        string getSubject() const 
        {
            return subject;
        }

        //перезавантаження saveToFile
        void saveToFile(ofstream& file) const override 
        {
            file << "NonFiction," << title << "," << author << "," << subject << endl;
        }
};

//читає книги з файлу, записує в масив
int readBooksFromFile(const string& filename, Book* books[]) 
{
    ifstream file(filename);
    if (!file.is_open()) 
    {
        throw runtime_error("Cannot open file: " + filename);
    }

    string line;
    int count = 0;

    while (getline(file, line) && count < MAX_BOOKS) 
    {
        istringstream iss(line);
        string type, title, author, extra;

        if (getline(iss, type, ',') && getline(iss, title, ',') &&
            getline(iss, author, ',') && getline(iss, extra)) 
        {
            if (type == "Fiction") 
            {
                books[count++] = new Fiction(title, author, extra);
            } 
            else if (type == "NonFiction") 
            {
                books[count++] = new NonFiction(title, author, extra);
            }
        }
    }

    file.close();
    return count;
}

//записує книги з масиву в файл
void writeBooksToFile(const string& filename, Book* books[], int count) 
{
    ofstream file(filename, ios::app);
    
    if (!file.is_open()) 
    {
        throw runtime_error("Cannot open file: " + filename);
    }

    for (int i = 0; i < count; i++) 
    {
        books[i]->saveToFile(file);
    }

    file.close();
}

int main() 
{
    try 
    {
        //масив книг
        Book* books[MAX_BOOKS]; 
        int bookCount = 0;

        //додавання книг вручну
        books[bookCount++] = new Fiction("Project Hail Mary", "Andy Weir", "Science fiction");
        books[bookCount++] = new NonFiction("Will My Cat Eat My Eyeballs?", "Caitlin Doughty", "Science");

        //запис у файл
        string filename = "newfile.txt";
        writeBooksToFile(filename, books, bookCount);

        //читання з файлу
        filename = "books.txt";
        Book* loadedBooks[MAX_BOOKS];
        int loadedBookCount = readBooksFromFile(filename, loadedBooks);

        //вивід кількості книг
        cout << "Total books: " << Book::getBookCount() << endl;

        //вивід інформації про книги
        for (int i = 0; i < loadedBookCount; i++) 
        {
            loadedBooks[i]->displayInfo();
            delete loadedBooks[i]; 
        }

        //очищення пам'яті
        for (int i = 0; i < bookCount; i++) 
        {
            delete books[i];
        }

        //вивід кількості книг
        cout << "Total books: " << Book::getBookCount() << endl;

    } 
    catch (const exception& e) 
    {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}