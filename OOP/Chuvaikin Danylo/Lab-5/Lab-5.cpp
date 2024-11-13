/*
Перетворити структуру, розроблену у завданні 2
(структури), на класи. Реалізувати основну функціональність у вигляді прототипів методів та псевдокоду.
*/
#include <iostream>
using namespace std;
class Library_Participant{
    private:
        string participant_name;
        int reg_year;
        //змінна для того, щоб регулювати, що книга нікому не належить
        bool valid;
    public:
        Library_Participant(string name = "", int year = 0){
            participant_name = name;
            reg_year = year;
            valid = (!name.empty());
        }
        bool is_valid(){
            return valid;
        }
        string get_name(){
            return participant_name;
        }
};
class Book{
    private:
        string book_name;
        string book_author;
        int book_year;
        Library_Participant user_who_took;
    public:
        Book(string name, string author, int year){
            book_name = name;
            author = author;
            book_year = year;
        }
        void take_book(Library_Participant participant){
            if(!user_who_took.is_valid()){
                user_who_took = participant;
                cout << "-----" << endl;
                cout << "Book was successfully taken by " << user_who_took.get_name() << endl;
                cout << "-----" << endl;
            }
            else{
                cout << "-----" << endl;
                cout << "You cant take the book, because it was alredy taken by " << user_who_took.get_name() << endl;
                cout << "-----" << endl;
            }
        }
        void return_book(){
                if (user_who_took.is_valid()){
                    cout << "-----" << endl;
                    cout << "Book was successfully returned by " << user_who_took.get_name() << endl;
                    cout << "-----" << endl;
                    user_who_took = Library_Participant();
                }
                else{
                    cout << "-----" << endl;
                    cout << "Book was not taken!" << endl;
                    cout << "-----" << endl;
                }
            }
        void print_info(){
            cout << "-----" << endl;
            cout << "The name of the book is: " << book_name << endl;
            cout << "From the Author: " << book_author << endl;
            cout << "Published in: " << book_year << endl;
            if (user_who_took.is_valid()) {
                cout << "Book was taken by " << user_who_took.get_name() << endl;
            }
            else{
                cout << "Book is in the library" << endl;
            }
            cout << "-----" << endl;
        }
};
int main(){
    Book fight_club("Fight Club", "Chuck Palahniuk", 1996);
    Library_Participant tyler_durden("Tyler Durden", 2024);
    Library_Participant narrator("narrator228", 2024);
    fight_club.return_book();
    fight_club.print_info();
    fight_club.take_book(tyler_durden);
    fight_club.take_book(narrator);
    fight_club.print_info();
    fight_club.return_book();
    fight_club.print_info();
}