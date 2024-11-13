/*
Розробити клас «Банківський рахунок», забезпечити
можливість додавання та зняття грошей з рахунку, перевірки поточного балансу, а
також нарахування відсотків. Використовувати статичні змінні для зберігання
процентної ставки та підрахунку загального балансу за всіма рахунками.
*/
#include <iostream>
using namespace std;
class Bank_Account{
    private:
        double konto_balance;
        static double prozent;
        static double ganz_balance;
    public:
        Bank_Account(double initial_balance = 0){
            konto_balance = initial_balance;
            ganz_balance += initial_balance;
            cout << "Thank you for opening new balance with " << konto_balance << " amount of money" << endl;
        }
        ~Bank_Account(){
            ganz_balance -= konto_balance;
        }
        void add_money(double amount_to_add){
            konto_balance += amount_to_add;
            ganz_balance += amount_to_add;
            cout << "Successfully added " << amount_to_add << " money to your account!" << endl;
            check_konto_balance();
        }
        void withdraw_money(double amount_to_withdraw){
            if(konto_balance >= amount_to_withdraw){
                konto_balance -= amount_to_withdraw;
            }
            cout << "Successfully withdrawed " << amount_to_withdraw << " money from your account!" << endl;
            check_konto_balance();
        }
        void check_konto_balance(){
            cout << "Your Balance now is: " << konto_balance << endl;
        }
        void add_prozent(){
            double prozent_to_add = konto_balance * (prozent/100);
            cout << "We added " << prozent_to_add << " prozent money to your balance" << endl;
            konto_balance += prozent_to_add;
            ganz_balance += prozent_to_add;
            check_konto_balance();
        }
        void change_prozent(double new_prozent_value){
            cout << "Your prozent was successfully changed to " << new_prozent_value << " from " << prozent << endl;
            prozent = new_prozent_value;
        }
        void check_total(){
            cout << "Your Total Balance now is: " << ganz_balance << endl;
        }
};
double Bank_Account::ganz_balance = 0.0;
double Bank_Account::prozent = 15.0;
int main(){
    Bank_Account Bc1;
    Bank_Account Bc2(125.6);
    Bc1.add_money(1500);
    Bc2.add_money(100);
    Bc1.withdraw_money(100);
    Bc1.check_total();
    Bc2.add_prozent();
    Bc1.change_prozent(10);
    Bc1.add_prozent();
    Bc2.check_total();
}