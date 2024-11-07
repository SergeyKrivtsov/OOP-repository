#include <iostream>
using namespace std;

const int WIDTH = 10;
const int HEIGHT = 10;

int playerX, playerY;

char maze[HEIGHT][WIDTH] = {
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', 'S', '.', '.', '#', '.', '.', '.', '.', '#'},
    {'#', '#', '#', '.', '#', '.', '#', '#', '#', '#'},
    {'#', 'E', '#', '.', '.', '.', '.', '#', '.', '#'},
    {'#', '.', '#', '#', '#', '.', '#', '#', '.', '#'},
    {'#', '.', '.', '.', '#', '.', '.', '.', '.', '#'},
    {'#', '#', '#', '.', '#', '#', '#', '.', '#', '#'},
    {'#', '.', '#', '.', '.', '.', '#', '.', '.', '#'},
    {'#', '.', '.', '#', '#', '.', '.', '.', '.', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
};

void findStartPosition() {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (maze[i][j] == 'S') {
                playerX = i;
                playerY = j;
                maze[i][j] = 'P';
                return;
            }
        }
    }
}

void displayMaze() {
    system("cls");
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            cout << maze[i][j] << ' ';
        }
        cout << endl;
    }
}

bool movePlayer(int dx, int dy) {
    int newX = playerX + dx;
    int newY = playerY + dy;

    if (maze[newX][newY] == '#') {
        return false;
    }

    if (maze[newX][newY] == 'E') {
        displayMaze();
        cout << "Congratulations, you have reached the exit!" << endl;
        return true;
    }

    maze[playerX][playerY] = '.';
    playerX = newX;
    playerY = newY;
    maze[playerX][playerY] = 'P';

    return false;
}

int main() {
    char input;
    bool gameWon = false;

    findStartPosition(); 

    while (!gameWon) {
        displayMaze();
        cout << "Enter the command (w - up, s - down, a - left, d - right): ";
        cin >> input;

        switch (input) {
        case 'w': gameWon = movePlayer(-1, 0); break;
        case 's': gameWon = movePlayer(1, 0); break;
        case 'a': gameWon = movePlayer(0, -1); break;
        case 'd': gameWon = movePlayer(0, 1); break;
        }
    }

    return 0;
}
