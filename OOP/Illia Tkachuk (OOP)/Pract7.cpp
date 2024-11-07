#include <iostream>

using namespace std;

class BankAccount {
private:
    double balance;
    static double stavka;
    static double vsedengi;

public:

    BankAccount(double basicBalance = 0.0) : balance(basicBalance) {
        vsedengi += balance;
    }

    ~BankAccount() {
        vsedengi -= balance;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            vsedengi += amount;
        } else {
            cout << "Сума повинна бути більше нуля.\n";
        }
    }

    void vyvod(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            vsedengi -= amount;
        } else {
            cout << "Недостатньо коштів або некоректна сума.\n";
        }
    }

    double getBalance() const {
        return balance;
    }

    void addProcent() {
        double Procent = balance * stavka;
        balance += Procent;
        vsedengi += Procent;
    }

    static void setstavka(double change_stavka) {
        if (change_stavka >= 0) {
            stavka = change_stavka;
        } else {
            cout << "Процентна ставка повинна бути не від'ємною.\n";
        }
    }
    static double getvsedengi() {
        return vsedengi;
    }
};

double BankAccount::stavka = 0.01;
double BankAccount::vsedengi = 0.0;

int main() {
    BankAccount acc1(1000.0);
    BankAccount acc2(500.0);

    int choice, accountChoice;
    double amount;

    while (true) {
        cout << "\n--- Меню ---\n";
        cout << "1. Поповнити рахунок\n";
        cout << "2. Зняти гроші з рахунку\n";
        cout << "3. Переглянути баланс рахунків\n";
        cout << "4. Нарахувати відсотки\n";
        cout << "5. Встановити процентну ставку\n";
        cout << "6. Вийти\n";
        cout << "Виберіть дію: ";
        cin >> choice;

        if (choice == 6) break;

        switch (choice) {
            case 1:
            do{
                cout << "Виберіть рахунок (1 або 2): ";
                cin >> accountChoice;
            } while (accountChoice != 1 && accountChoice != 2);
                cout << "Введіть суму для поповнення: ";
                cin >> amount;
                if (accountChoice == 1) {
                    acc1.deposit(amount);
                    cout << "Баланс рахунку 1 після поповнення: " << acc1.getBalance() << "\n";
                } else {
                    acc2.deposit(amount);
                    cout << "Баланс рахунку 2 після поповнення: " << acc2.getBalance() << "\n";
                }
                break;

            case 2:
                  do {
                     cout << "Виберіть рахунок (1 або 2): ";
                     cin >> accountChoice;
                  } while (accountChoice != 1 && accountChoice != 2);

                     cout << "Введіть суму для зняття: ";
                     cin >> amount;

                     if (accountChoice == 1) {
                        acc1.vyvod(amount);
                        cout << "Баланс рахунку 1 після зняття: " << acc1.getBalance() << "\n";
                     } else {
                         acc2.vyvod(amount);
                        cout << "Баланс рахунку 2 після зняття: " << acc2.getBalance() << "\n";
                     }  
                break;

            case 3:
                cout << "Баланс рахунку 1: " << acc1.getBalance() << "\n";
                cout << "Баланс рахунку 2: " << acc2.getBalance() << "\n";
                cout << "Загальний баланс всіх рахунків: " << BankAccount::getvsedengi() << "\n";
                break;

            case 4:
                acc1.addProcent();
                acc2.addProcent();
                cout << "Відсотки нараховано.\n";
                cout << "Баланс рахунку 1: " << acc1.getBalance() << "\n";
                cout << "Баланс рахунку 2: " << acc2.getBalance() << "\n";
                cout << "Загальний баланс всіх рахунків: " << BankAccount::getvsedengi() << "\n";
                break;

            case 5:
                cout << "Введіть нову процентну ставку (наприклад, 0.05 для 5%): ";
                cin >> amount;
                BankAccount::setstavka(amount);
                cout << "Процентна ставка змінена на " << amount * 100 << "%\n";
                break;

            default:
                cout << "Невірний вибір. Спробуйте знову.\n";
                break;
        }
    }

    return 0;
}
