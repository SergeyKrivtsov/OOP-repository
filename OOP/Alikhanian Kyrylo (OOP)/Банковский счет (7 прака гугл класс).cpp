#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class BankAccount {
private:
    string accountHolder;
    double balance;
    static double interestRate;
    static double totalBalance;

public:
    BankAccount(const string& holder, double initialDeposit) {
        accountHolder = holder;
        balance = initialDeposit;
        totalBalance += initialDeposit;
    }

    ~BankAccount() {
        totalBalance -= balance;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            totalBalance += amount;
            cout << "Депозит у розмірі " << amount << " успішно здійснено!" << endl;
        }
        else {
            cout << "Сума депозиту повинна бути більшою за 0!" << endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            totalBalance -= amount;
            cout << "Зняття у розмірі " << amount << " успішно здійснено!" << endl;
        }
        else {
            cout << "Недостатньо коштів або некоректна сума!" << endl;
        }
    }

    void accrueInterest() {
        double interest = balance * (interestRate / 100);
        balance += interest;
        totalBalance += interest;
        cout << "Відсотки у розмірі " << interest << " нараховані!" << endl;
    }

    double getBalance() const {
        return balance;
    }

    static double getTotalBalance() {
        return totalBalance;
    }

    static void setInterestRate(double newRate) {
        if (newRate >= 0) {
            interestRate = newRate;
            cout << "Процентна ставка змінена на " << newRate << "%" << endl;
        }
        else {
            cout << "Процентна ставка повинна бути не меншою за 0!" << endl;
        }
    }
};

double BankAccount::interestRate = 2.5;
double BankAccount::totalBalance = 0.0;

int main() {
    BankAccount account1("Олександр", 1000);
    BankAccount account2("Марія", 2000);

    cout << fixed << setprecision(2);
    cout << "Баланс Олександра: " << account1.getBalance() << endl;
    cout << "Баланс Марії: " << account2.getBalance() << endl;

    account1.withdraw(200);
    account2.deposit(500);

    account1.accrueInterest();
    account2.accrueInterest();

    cout << "Загальний баланс усіх рахунків: " << BankAccount::getTotalBalance() << endl;

    BankAccount::setInterestRate(3.0);

    account1.accrueInterest();
    account2.accrueInterest();

    cout << "Загальний баланс усіх рахунків після нарахування відсотків: " << BankAccount::getTotalBalance() << endl;

    return 0;
}
