#include <iostream>
#include <ctime> // Для роботи з таймером

using namespace std; // Додаємо using namespace std

constexpr int HEIGHT = 10;
constexpr int WIDTH = 10;

char maze[HEIGHT][WIDTH] = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', 'S', '.', '.', '#', '.', '.', '.', '.', '#'},
        {'#', '#', '#', '.', '#', '.', '#', '#', '.', '#'},
        {'#', '.', '.', '.', '.', '.', '.', '#', '.', '#'},
        {'#', '#', '#', '#', '#', '.', '#', '#', '.', '#'},
        {'#', '.', '.', '.', '#', '.', '.', '.', '.', '#'},
        {'#', '#', '#', '.', '#', '#', '.', '#', '#', '#'},
        {'#', '.', '#', '.', '.', '.', '.', '.', '.', '#'},
        {'#', '.', '.', '.', '#', '#', '.', '.', 'E', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
};

// Початкова позиція гравця (позиція 'S')
int posX = 1;
int posY = 1;

const string RED = "\033[31m";
const string BLUE = "\033[34m";
const string RESET = "\033[0m";

void displayMaze(int remainingTime) {
    cout << "Use (W, A, S, D) to move. Reach the Exit (E).\n";
    cout << "Time remaining: " << remainingTime << " seconds\n"; // Відображення залишкового часу

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

void movePlayer(char direct) {
    int nextX = posX;
    int nextY = posY;

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

    // Перевірка меж лабіринту і наявності стіни ('#')
    if (nextX >= 0 && nextX < HEIGHT && nextY >= 0 && nextY < WIDTH && maze[nextX][nextY] != '#') {
        posX = nextX;
        posY = nextY;
    }
}

int main() {
    char d;

    // Инициализация таймера
    time_t startTime = time(nullptr); // Получаем текущее время

    while (true) {
        // Обчислення часу, що залишився (60 секунд)
        int remainingTime = 60 - static_cast<int>(difftime(time(nullptr), startTime));

        // Проверка на истечение времени (1 минута)
        if (remainingTime <= 0) {
            cout << "Time's up! You failed to reach the Exit in 1 minute.\n";
            break;
        }

        displayMaze(remainingTime);

        if (maze[posX][posY] == 'E') {
            cout << "Congratulations! You reached the Exit!\n";
            break;
        }

        cin >> d;
        movePlayer(d);
    }

    return 0;
}