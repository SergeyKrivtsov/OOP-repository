/*
Розробити структуру/набір структур для зберігання інформації будь-якої предметної області.
Забезпечити необхідний набір функцій, які реалізують основну функціональність предметної області.
*/
#include <iostream>
using namespace std;
struct Library_Participant{
    string participant_name;
    int reg_year;
    //змінна для того, щоб регулювати, що книга нікому не належить
    bool valid = false;
};
struct Book{
    string book_name;
    string book_author;
    int book_year;
    Library_Participant user_who_took;
};
Library_Participant create_participant(string name, int year){
    Library_Participant temp_p;
    temp_p.participant_name = name;
    temp_p.reg_year = year;
    temp_p.valid = true;
    return temp_p;
}
Book create_book(string name, string author, int year){
    Book temp_b;
    temp_b.book_name = name;
    temp_b.book_author = author;
    temp_b.book_year = year;
    temp_b.user_who_took = Library_Participant();
    return temp_b;
}
void take_book(Book& book, Library_Participant participant){
    if(!book.user_who_took.valid){
        book.user_who_took = participant;
        cout << "-----" << endl;
        cout << "Book was successfully taken by " << book.user_who_took.participant_name << endl;
        cout << "-----" << endl;
    }
    else{
        cout << "-----" << endl;
        cout << "You cant take the book, because it was alredy taken by " << book.user_who_took.participant_name << endl;
        cout << "-----" << endl;
    }
}
void return_book(Book& book){
    if(book.user_who_took.valid){
        cout << "-----" << endl;
        cout << "Book was successfully returned by " << book.user_who_took.participant_name << endl;
        cout << "-----" << endl;
        book.user_who_took = Library_Participant();
    }
    else{
        cout << "-----" << endl;
        cout << "Book was not taken!" << endl;
        cout << "-----" << endl;
    }
}
void print_book_info(Book book){
    cout << "-----" << endl;
    cout << "The name of book is: " << book.book_name << endl;
    cout << "From the Author: " << book.book_author << endl;
    cout << "->" << book.book_year << "<-" << endl;
    if(book.user_who_took.valid){
        cout << "Book was taken by " << book.user_who_took.participant_name << endl;
    }
    else{
        cout << "Book is in library" << endl;
    }
    cout << "-----" << endl;
}
int main(){
    Book fight_club = create_book("Fight Club", "Chuck Palahniuk", 1996);
    Library_Participant tyler_durden = create_participant("Tyler Durden", 2024);
    Library_Participant narrator = create_participant("narrator228", 2024);
    return_book(fight_club);
    print_book_info(fight_club);
    take_book(fight_club, tyler_durden);
    take_book(fight_club, narrator);
    print_book_info(fight_club);
    return_book(fight_club);
    print_book_info(fight_club);
}