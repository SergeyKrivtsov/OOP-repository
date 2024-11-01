#include <iostream>
#include <cstdlib>
using namespace std;
char maze[10][10] = {
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', 'S', '.', '.', '#', '.', '.', '.', '.', '#'},
    {'#', '#', '#', '.', '#', '.', '#', '#', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '.', '#', '.', '#'},
    {'#', '#', '#', '#', '#', '.', '#', '#', '.', '#'},
    {'#', '.', '.', '.', '#', '.', '.', '.', '.', '#'},
    {'#', '#', '#', '.', '#', '#', '.', '#', '#', '#'},
    {'#', '.', '#', '.', '.', '.', '.', '#', '.', '#'},
    {'#', '.', '.', '.', '#', '#', '.', '.', 'E', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
};
class Maze_runner {
    private:
        char maze[10][10];
        int playerX, playerY;

    public:
        Maze_runner(char i_maze[10][10]) {
            for(int i = 0; i < 10; i++) {
                for(int j = 0; j < 10; j++) {
                    maze[i][j] = i_maze[i][j];
                    if (maze[i][j] == 'S') {
                        playerX = i;
                        playerY = j;
                        maze[i][j] = 'P';
                    }
                }
            }
        }
        void print_maze() {
            system("cls"); 
            cout << "Current pos:" << playerX << ", " << playerY << ")" << endl;
            for(int i = 0; i < 10; i++) {
                for(int j = 0; j < 10; j++) {
                    cout << maze[i][j] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
        bool move_player(char direction) {
            int newX = playerX;
            int newY = playerY;
            switch (direction) {
                case 'W': newX -= 1; break;
                case 'S': newX += 1; break;
                case 'A': newY -= 1; break;
                case 'D': newY += 1; break;
                default: cout << "Error!" << endl; return true;
            }
            if (newX < 0 || newX >= 10 || newY < 0 || newY >= 10 || maze[newX][newY] == '#') {
                cout << "Can't move!" << endl;
                return true;
            }
            if (maze[newX][newY] == 'E') {
                cout << "U won!" << endl;
                return false;
            }
            maze[playerX][playerY] = '.'; 
            playerX = newX;
            playerY = newY;
            maze[playerX][playerY] = 'P';
            return true;
        }
};

int main() {
    Maze_runner runner(maze);
    char cur_command;
    bool not_yet_escaped = true;
    cout << "Well well well! WASD to move" << endl;
    while (not_yet_escaped) {
        runner.print_maze();
        cout << "(WASD):";
        cin >> cur_command;
        not_yet_escaped = runner.move_player(cur_command);
    }
    return 0;
}
