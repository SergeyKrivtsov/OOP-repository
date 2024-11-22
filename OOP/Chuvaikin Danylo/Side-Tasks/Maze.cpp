/*
Генерація лабіринту, переміщення по лабіринту через WASD, пошук шляху від входу до виходу
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
const int WIDTH = 10;
const int HEIGHT = 10;
const char WALL = '#';
const char PATH = '.';
const char START = 'S';
const char END = 'E';
const char PLAYER = 'P';
const char VISITED = '*';
const char SHORTEST_PATH = '+';
void generate_maze(char maze[WIDTH][HEIGHT]) {
    srand(time(0));
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            maze[i][j] = WALL;
        }
    }
    int start_h = rand() % HEIGHT;
    int start_w = rand() % WIDTH;
    maze[start_h][start_w] = START;
    int current_h = start_h, current_w = start_w;
    int tales = rand()%5+20;
    for(int i = 1; i<=tales; i++){
        if (rand() % 2 == 0) {
            if (current_h + 1 < HEIGHT){
                if(maze[current_h + 1][current_w] != PATH){
                    current_h++;
                }
            }
            else if (current_h - 1 >= 0){
                if(maze[current_h - 1][current_w] != PATH){
                    current_h--;
                }
            }
        } else {
            if (current_w + 1 < WIDTH){
                if(maze[current_h][current_w + 1] != PATH){
                    current_w++;
                }
            }
            else if (current_w - 1 >= 0){
                if(maze[current_h][current_w - 1] != PATH){
                    current_w--;
                }
            }
        } 
        maze[current_h][current_w] = PATH;
    }
    maze[current_h][current_w] = END;
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++){
            if(rand()%5==0 && maze[i][j] != START && maze[i][j] != END){
                maze[i][j] = PATH;
            }
        }
    }
}
class Maze_runner {
private:
    char maze[WIDTH][HEIGHT];
    int playerX, playerY, startX, startY, endX, endY;

    void find_start_end() {
        for (int i = 0; i < WIDTH; i++) {
            for (int j = 0; j < HEIGHT; j++) {
                if (maze[i][j] == START) {
                    startX = i;
                    startY = j;
                    playerX = i;
                    playerY = j;
                    maze[i][j] = PLAYER;
                } else if (maze[i][j] == END) {
                    endX = i;
                    endY = j;
                }
            }
        }
    }
    bool find_path(int x, int y) {
        if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT || maze[x][y] == WALL || maze[x][y] == VISITED) {
            return false;
        }
        if (x == endX && y == endY) {
            return true;
        }
        maze[x][y] = VISITED;
        
        if (find_path(x + 1, y) || find_path(x - 1, y) || find_path(x, y + 1) || find_path(x, y - 1)) {
            maze[x][y] = SHORTEST_PATH;
            return true;
        }
        maze[x][y] = PATH;
        return false;
    }
public:
    Maze_runner(char i_maze[WIDTH][HEIGHT]) {
        for (int i = 0; i < WIDTH; i++) {
            for (int j = 0; j < HEIGHT; j++) {
                maze[i][j] = i_maze[i][j];
            }
        }
        find_start_end();
    }

    void print_maze() {
        system("cls");
        for (int i = 0; i < WIDTH; i++) {
            for (int j = 0; j < HEIGHT; j++) {
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
            default: cout << "Error! Invalid input." << endl; return true;
        }
        if (newX < 0 || newX >= HEIGHT || newY < 0 || newY >= WIDTH || maze[newX][newY] == WALL) {
            cout << "Can't move!" << endl;
            return true;
        }
        if (maze[newX][newY] == END) {
            maze[playerX][playerY] = PATH;
            playerX = newX;
            playerY = newY;
            maze[playerX][playerY] = PLAYER;
            print_maze();
            cout << "You won!" << endl;
            return false;
        }
        maze[playerX][playerY] = PATH;
        playerX = newX;
        playerY = newY;
        maze[playerX][playerY] = PLAYER;
        print_maze();
        return true;
    }
    void find_shortest_path() {
        if (find_path(startX, startY)) {
            maze[startX][startY] = START;
            maze[endX][endY] = END;
        }
    }
    void show_path_until_exit() {
        find_shortest_path();
        char exit_char;
        while (true) {
            print_maze();
            cout << "Showing the path. Press '1' to go back to the menu." << endl;
            cin >> exit_char;
            if (exit_char == '1') break;
        }
    }
};
int main() {
    char maze[WIDTH][HEIGHT];
    bool keep_playing = true;
    generate_maze(maze);
    while (keep_playing) {
        Maze_runner runner(maze);
        runner.print_maze();
        int choice;
        cout << "Menu:\n1. Regenerate Level\n2. Show Path\n3. Control Player\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Regenerating maze..." << endl;
                generate_maze(maze);
                runner = Maze_runner(maze);
                runner.print_maze();
                break;
            case 2:
                runner.show_path_until_exit();
                break;
            case 3: {
                char cur_command;
                bool not_yet_escaped = true;
                while (not_yet_escaped) {
                    runner.print_maze();
                    cout << "(WASD to move): ";
                    cin >> cur_command;
                    not_yet_escaped = runner.move_player(cur_command);
                }
                break;
            }
            case 4:
                keep_playing = false;
                cout << "Ok..." << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    }
    return 0;
}