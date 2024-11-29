// Лабиринт.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <iomanip>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>

using namespace std;

int const MAZE_HEIGHT = 10;
int const MAZE_WIDTH = 10;
char Br = ' '; // Border
char P = 'P'; // Player position
char ps = '.'; //pass - проход в лабиринте
char maze[MAZE_HEIGHT][MAZE_WIDTH] = {
    {Br, Br, Br, Br, Br, Br, Br, Br, Br, Br},
    {Br, 'S', ps, ps, Br, ps, ps, ps, ps, Br},//1,1
    {Br, Br, Br, ps, Br, ps, Br, Br, ps, Br},
    {Br, ps, ps, ps, ps, ps, ps, Br, ps, Br},
    {Br, Br, ps, Br, Br, ps, Br, Br, ps, Br},
    {Br, ps, ps, ps, Br, ps, ps, ps, ps, Br},
    {Br, Br, Br, ps, Br, Br, Br, Br, Br, Br},
    {Br, ps, Br, ps, ps, ps, ps, Br, ps, Br},
    {Br, ps, ps, ps, Br, Br, ps, ps, 'E', Br},
    {Br, Br, Br, Br, Br, Br, Br, Br, Br, Br}
};

void printColoredBackgroundChar(char ch, const string& textColor, const string& backgroundColor) {
    cout << setw(1) << textColor << backgroundColor << ch << "\033[0m";  // Сбрасываем цвет после символа
}
string redText = "\033[31m";
string yellowBackground = "\033[43m";
string blueBackground = "\033[44m";

struct CurrentPos {
    int x;
    int y;
};

const int dx[4] = { 0,1,0,-1 };
const int dy[4] = { -1,0,1,0 };

vector<vector<char>> mazerand(MAZE_HEIGHT, vector<char>(MAZE_WIDTH, Br));

bool isInside(int x, int y) {
    return x < MAZE_WIDTH && x >= 0 && y < MAZE_HEIGHT && y >= 0;
}

void generateMaze(int x, int y) { // Рекурсивная функция для прокладывания маршрута заменяя стены в массиве 
    mazerand[y][x] = ps; // Прокдадывание маршрута

    //Перемешивание рандомного направления
    vector<int> directions = { 0,1,2,3 };
    random_shuffle(directions.begin(), directions.end());

    for (size_t i = 0; i < 4; i++)
    {
        int nx = x + dx[directions[i]*2];
        int ny = y + dy[directions[i]*2];
        if (isInside(nx,ny)&&mazerand[ny][nx]==Br)
        {
            mazerand[y + dy[directions[i]]][x + dx[directions[i]]] = ps;
            generateMaze(nx, ny);
        }
    }
}
//Рекурсивная функция для проверки существования пути
//Принимает в себя матрицу буллов которые заполнены false, проверяет клетки и связь между ними, отмечает true если клетка посещена

bool isPathExists(int x, int y, vector<vector<bool>>& visited) {
    if (x == MAZE_WIDTH - 1 && y == MAZE_HEIGHT - 1) return true;//если сразу конец лабиринта, а именно правый нижний угол, то сразу возвращает тру
    visited[y][x] = true;// Помечает клетку как посещенную 
    for (size_t i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        //Если координаты после сдвига в массиве и там есть проход и эта координата не посещена то мы снова запускаем эту функцию, которая отмечает ее как посещенную
        //Пока не дойдем до конца и не получим тру варианта
        if (isInside(nx, ny) && mazerand[ny][nx] == ps && !visited[ny][nx]) {
            if (isPathExists(nx, ny, visited)) return true;
        }
    }
    //В случае если пути не существует
    return false;
}
int main()
{
    setlocale(LC_CTYPE, "rus");
    char key = ' ';
    CurrentPos position, endposition;
    position.x = 1; position.y = 1;
    endposition.x = 0; endposition.y = 0; //E Pos
    bool VariantOfGenerationLabirint = false; // false - Статическое лабиринт, true - рандомный
    cout << "Добро пожаловать в лабиринт, вам надо выбраться!\n";
    cout << "Для перемещения по лабиринту используйте клавиши W,A,S,D.\n"
        << "На данный момент вы находить в точке S - Start, начните движение и увидите свою фигурку.\n"
        << "Для того чтобы выйти из игры, нажмите E." << endl;
    if (VariantOfGenerationLabirint)
    {
        //Генерация начиная с нулевых координат
        generateMaze(0, 0);
        //Вот там самая матрица false`ов
        vector<vector<bool>> visited(MAZE_HEIGHT, vector<bool>(MAZE_WIDTH, false));
        do
        {
            int a = 0;
            a++;
            cout << "Attempt #" << a << endl;
        } while (isPathExists(0,0,visited));
        cout << "Path exist!" << endl;
        for (size_t i = 0; i < MAZE_HEIGHT; i++)
        {
            for (size_t j = 0; j < MAZE_WIDTH; j++)
            {
                cout << mazerand[i][j];
            }
            cout << endl;
        }
    }
    else
    {
        for (int i = 0; i < MAZE_HEIGHT; i++) {
            for (int j = 0; j < MAZE_WIDTH; j++) {
                if (maze[i][j] == 'E') {
                    endposition.x = i; endposition.y = j;
                    break;
                }
            }
        }
        // сделать позицию пользователя структурой
        // сделать случайную генерацию алгоритмом
        // таймер пройти за 10 секунд
        do
        {
            key = _getch();
            switch (key)
            {
            case 'w':
                if (maze[position.x - 1][position.y] != NULL && maze[position.x - 1][position.y] != Br)
                {
                    maze[position.x - 1][position.y] = P;
                    maze[position.x][position.y] = ps;
                    position.x -= 1;
                }
                break;
            case 'a':
                if (maze[position.x][position.y - 1] != NULL && maze[position.x][position.y - 1] != Br)
                {
                    maze[position.x][position.y - 1] = P;
                    maze[position.x][position.y] = ps;
                    position.y -= 1;
                }
                break;
            case 's':
                if (maze[position.x + 1][position.y] != NULL && maze[position.x + 1][position.y] != Br)
                {
                    maze[position.x + 1][position.y] = P;
                    maze[position.x][position.y] = ps;
                    position.x += 1;
                }

                break;
            case 'd':
                if (maze[position.x][position.y + 1] != NULL && maze[position.x][position.y + 1] != Br)
                {
                    maze[position.x][position.y + 1] = P;
                    maze[position.x][position.y] = ps;
                    position.y += 1;
                }

                break;
            case 0:
                break;
            default:
                break;
            }
            system("cls");
            for (size_t i = 0; i < MAZE_HEIGHT; i++) {
                for (size_t j = 0; j < MAZE_WIDTH; j++) {
                    if (maze[i][j] == Br) {
                        printColoredBackgroundChar(maze[i][j], redText, yellowBackground);
                    }
                    else if (maze[i][j] == P)
                    {
                        printColoredBackgroundChar(Br, redText, redText);
                    }
                    else if (maze[i][j] == 'E')
                    {
                        printColoredBackgroundChar(maze[i][j], redText, blueBackground);
                    }
                    else
                        printColoredBackgroundChar(Br, blueBackground, blueBackground);
                }
                cout << endl;
            }
            if (position.x == endposition.x && position.y == endposition.y)
            {
                cout << "Вы выбрались из лабиринта!" << endl;
                break;
            }
        } while (key != 'e');
    }
}

