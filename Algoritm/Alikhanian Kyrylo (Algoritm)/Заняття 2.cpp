#include <iostream>
#include <string>
using namespace std;

enum Position { Goalkeeper, Defender, Midfielder, Forward };

// Структура для елемента списку
struct Node {
    int data;
    Node* next;
};

// Структура для футболіста
struct Footballer {
    string surname;
    Position position;
    int age;
    int gamesPlayed;
    int goalsScored;
    Footballer* next;
};

// Функція для створення списку в зворотному порядку (LIFO) з поверненням вказівника на голову
Node* formLIFO_1() {
    int n, value;
    cout << "Enter the number of elements for LIFO (1): ";
    cin >> n;
    Node* head = nullptr;
    for (int i = 0; i < n; ++i) {
        cout << "Enter value: ";
        cin >> value;
        Node* newNode = new Node{ value, head };  // Додаємо новий елемент в початок списку
        head = newNode;
    }
    return head;  // Повертаємо вказівник на голову
}

// Функція для створення списку в зворотному порядку (LIFO) без повернення значення
void formLIFO_2(Node*& head) {
    int n, value;
    cout << "Enter the number of elements for LIFO (2): ";
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cout << "Enter value: ";
        cin >> value;
        Node* newNode = new Node{ value, head };  // Додаємо новий елемент в початок списку
        head = newNode;  // Оновлюємо вказівник на голову
    }
}

// Функція для створення списку в порядку введення елементів (FIFO)
Node* formFIFO() {
    int n, value;
    cout << "Enter the number of elements for FIFO: ";
    cin >> n;
    Node* head = nullptr;
    Node* tail = nullptr;

    for (int i = 0; i < n; ++i) {
        cout << "Enter value: ";
        cin >> value;
        Node* newNode = new Node{ value, nullptr };  // Додаємо новий елемент в кінець списку
        if (head == nullptr) {
            head = tail = newNode;  // Якщо список порожній, обидва вказівники вказують на новий елемент
        }
        else {
            tail->next = newNode;  // Вказівник на наступний елемент
            tail = newNode;  // Оновлюємо хвіст
        }
    }
    return head;  // Повертаємо вказівник на голову
}

// Функція для виведення елементів списку
void printList(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";  // Виводимо значення поточного елемента
        temp = temp->next;  // Переходимо до наступного елемента
    }
    cout << endl;
}

// Функція для додавання нового футболіста в список
Footballer* addFootballer(Footballer* head, const string& surname, Position position, int age, int gamesPlayed, int goalsScored) {
    Footballer* newPlayer = new Footballer{ surname, position, age, gamesPlayed, goalsScored, head };  // Створюємо нового футболіста
    return newPlayer;  // Повертаємо вказівник на голову списку
}

// Функція для знаходження кращого форварда за кількістю забитих голів
Footballer* findBestForward(Footballer* head) {
    Footballer* bestForward = nullptr;
    int maxGoals = -1;
    for (Footballer* temp = head; temp != nullptr; temp = temp->next) {
        if (temp->position == Forward && temp->goalsScored > maxGoals) {  // Якщо це форвард і забив більше голів
            bestForward = temp;  // Оновлюємо кращого форварда
            maxGoals = temp->goalsScored;  // Оновлюємо максимальну кількість голів
        }
    }
    return bestForward;  // Повертаємо кращого форварда
}

// Функція для виведення футболістів, які зіграли більше або рівно 5 ігор
void printPlayersWithMinGames(Footballer* head, int minGames) {
    for (Footballer* temp = head; temp != nullptr; temp = temp->next) {
        if (temp->gamesPlayed >= minGames) {  // Якщо футболіст зіграв більше або рівно 5 ігор
            cout << "Surname: " << temp->surname << ", Position: " << temp->position << ", Age: " << temp->age
                << ", Games Played: " << temp->gamesPlayed << ", Goals Scored: " << temp->goalsScored << endl;
        }
    }
}

int main() {
    Node* list1 = formLIFO_1();  // Створюємо список за допомогою formLIFO_1
    cout << "List created by formLIFO_1 (LIFO): ";
    printList(list1);  // Виводимо список

    Node* list2 = nullptr;
    formLIFO_2(list2);  // Створюємо список за допомогою formLIFO_2
    cout << "List created by formLIFO_2 (LIFO): ";
    printList(list2);  // Виводимо список

    Node* list3 = formFIFO();  // Створюємо список за допомогою formFIFO
    cout << "List created in FIFO order: ";
    printList(list3);  // Виводимо список

    // Створюємо список футболістів
    Footballer* team = nullptr;
    team = addFootballer(team, "Ivanov", Forward, 25, 10, 8);
    team = addFootballer(team, "Petrenko", Midfielder, 27, 15, 3);
    team = addFootballer(team, "Shevchenko", Forward, 30, 12, 15);

    // Знаходимо кращого форварда
    Footballer* bestForward = findBestForward(team);
    if (bestForward != nullptr) {
        cout << "Best Forward: " << bestForward->surname << ", Goals: " << bestForward->goalsScored << endl;
    }

    // Виводимо футболістів, які зіграли 5 і більше ігор
    cout << "Players with at least 5 games played:" << endl;
    printPlayersWithMinGames(team, 5);

    return 0;
}
