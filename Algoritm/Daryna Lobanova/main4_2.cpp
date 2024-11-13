#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

constexpr int HEIGHT = 10;
constexpr int WIDTH = 10;

char maze[HEIGHT][WIDTH]; // Массив для зберігання лабіринту
int posX, posY; // Позиція гравця P
int exitX, exitY; // Позиція виходу E

const string RED = "\033[31m"; // Червоний для гравця
const string BLUE = "\033[34m"; // Синій для виходу
const string RESET = "\033[0m"; // Скидання кольору

// Заповнення лабіринту
void CreateMaze() {
    // Заповнюємо лабіринт стінами #
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            maze[i][j] = '#';

    // Початкова позиція гравця і вихід
    posX = 1; // Гравець (1, 1)
    posY = 1;
    exitX = HEIGHT - 2; // Вихід (HEIGHT-2, WIDTH-2)
    exitY = WIDTH - 2;
    maze[posX][posY] = 'S'; // Старт
    maze[exitX][exitY] = 'E'; // Вихід

    // Створення основного шляху до виходу
    int x = posX, y = posY;
    srand(static_cast<unsigned>(time(0))); // Ініціалізація генератора випадкових чисел
    while (x != exitX || y != exitY) { // Шлях до виходу
        maze[x][y] = '.'; // Позначаємо прохід
        if (x < exitX && (rand() % 2 || y == exitY)) x++; // Рух вниз
        else if (y < exitY && (rand() % 2 || x == exitX)) y++; // Рух вправо
        else if (x > posX && rand() % 2) x--; // Рух вгору
        else if (y > posY && rand() % 2) y--; // Рух вліво
    }

    // Додаємо випадкові тупики і короткі розгалуження
    for (int i = 0; i < 6; i++) { // Кількість тупиків обмежена
        int tx = 1 + rand() % (HEIGHT - 2); // Випадкова позиція для тупика
        int ty = 1 + rand() % (WIDTH - 2);
        if (maze[tx][ty] == '#') { // Якщо це стіна, створюємо прохід і можливі тупики
            maze[tx][ty] = '.';
            if (rand() % 2) { // Додаємо випадковий тупик
                if (tx + 1 < HEIGHT - 1) maze[tx + 1][ty] = '.'; // Прохід вниз
                if (ty + 1 < WIDTH - 1) maze[tx][ty + 1] = '.'; // Прохід вправо
            }
        }
    }
}

// Функція для виведення лабіринту
void displayMaze(int remainingTime) {
    // Інструкції та час
    cout << "Use (W, A, S, D) to move. Reach the Exit (E).\n";
    cout << "Time remaining: " << remainingTime << " seconds\n";

    // Виведення лабіринту
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == posX && j == posY) {
                cout << RED << "P " << RESET;
            } else if (maze[i][j] == 'E') {
                cout << BLUE << "E " << RESET;
            } else {
                cout << maze[i][j] << ' ';
            }
        }
        cout << '\n';
    }
}

// Функція для переміщення
void movePlayer(char direct) {
    int nextX = posX;
    int nextY = posY;
    // Напрямок руху
    switch (direct) {
        case 'W':
        case 'w': nextX--; break;
        case 'A':
        case 'a': nextY--; break;
        case 'S':
        case 's': nextX++; break;
        case 'D':
        case 'd': nextY++; break;
        default: return;
    }

    // Перевірка, чи нова позиція не виходить за лабіринт та не стіна
    if (nextX >= 0 && nextX < HEIGHT && nextY >= 0 && nextY < WIDTH && maze[nextX][nextY] != '#') {
        posX = nextX;
        posY = nextY;
    }
}
int main() {
    CreateMaze(); // Створюємо лабіринт
    char d; // змінна для напрямку
    time_t startTime = time(nullptr); // Час початку гри

    while (true) {
        // Обчислення часу
        int remainingTime = 60 - static_cast<int>(difftime(time(nullptr), startTime));
        if (remainingTime <= 0) {
            cout << "Time's up! You failed to reach the Exit in 1 minute.\n"; // Якщо час вийшов
            break;
        }

        displayMaze(remainingTime); // Виведення лабіринту

        if (posX == exitX && posY == exitY) { // Якщо гравець досяг виходу
            cout << "You reached the Exit!\n";
            break;
        }

        cin >> d; // Введення руху
        movePlayer(d); // Оновлення позиції
    }

    return 0;
}