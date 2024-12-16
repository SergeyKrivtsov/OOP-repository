//додати структуру позиції, випадкову генерацію лабиринту з можливістю задати розмір, функцію руху, таймер в 10 сек 
//додати алгоритм автоматичного знаходження шляху і знаходити найкоротший
//початок часу - після першого руху
//чистити консоль
// якщо ввести неправильну букву воно все одно рахує це як мув в counter
// коментарі
#include <iostream>
#include <ctime>
#include <math.h>
#include <algorithm>

using namespace std;

//const int maze_height = 10;
//const int maze_width = 10;

struct Position 
{
    int i;
    int j;
};

void Maze_output(int maze_height, int maze_width, char** maze);
void move_wasd(char** &maze, Position &player, int i_add, int j_add);
int Random_maze(char** &maze, Position &player, Position &end, int &maze_height, int &maze_width);
int is_solvable(char** maze, Position player, Position end, int maze_height, int maze_width);
int dfs(char** maze, int i, int j, Position end, int maze_height, int maze_width);

int main()
{
    int maze_height = 0;
    int maze_width = 0;
    char** maze = nullptr;
    Position player;
    Position start;
   
    Position end = {8, 8};    // кінцева позиція
    time_t end_time;
    char move;

    int path = Random_maze(maze, player, end, maze_height, maze_width);
     start = {player.i, player.j};
    
    // char maze[maze_height][maze_width] = {
    // {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    // {'#', 'S', '.', '.', '#', '.', '.', '.', '.', '#'},
    // {'#', '#', '#', '.', '#', '.', '#', '#', '.', '#'},
    // {'#', '.', '.', '.', '.', '.', '.', '#', '.', '#'},
    // {'#', '#', '#', '#', '#', '.', '#', '#', '.', '#'},
    // {'#', '.', '.', '.', '#', '.', '.', '.', '.', '#'},
    // {'#', '#', '#', '.', '#', '#', '.', '#', '#', '#'},
    // {'#', '.', '#', '.', '.', '.', '.', '.', '.', '#'},
    // {'#', '.', '.', '.', '#', '#', '.', '.', 'E', '#'},
    // {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}};

    cout << "Welcome to the maze!" << endl;
    cout << "I want to play a game." << endl;
    cout << "Use WASD to move." << endl;
    cout << "One move at the time. You start at S." << endl;

    Maze_output(maze_height, maze_width, maze);
    
   

    end_time = time(NULL)+90;

    int counter = 0;
    
    while(1)
    {
        counter++;
        cout << "You have " << end_time - time(NULL) << "seconds left" << endl;
        cout << "Input the move" << endl;
        cin >> move;
        if(move!='W'&&move!='A'&&move!='S'&&move!='D'&& move!='w'&&move!='a'&&move!='s'&&move!='d')
        {
            cout << "Sorry, wrong letter." << endl;
        }
        else
        {
            if(move=='W'||move=='w')
            {
                move_wasd(maze, player, -1, 0);
            }
            if(move=='A'||move=='a')
            {
                move_wasd(maze, player, 0, -1);
            }
            if(move=='S'||move=='s')
            {
                move_wasd(maze, player, 1, 0);
            }
            if(move=='D'||move=='d')
            {
                move_wasd(maze, player, 0, 1);
            }
            if(!(player.i==start.i&&player.j==start.j))
                maze[start.i][start.j]='S';
            Maze_output(maze_height, maze_width, maze);
            if(player.i==end.i&&player.j==end.j)
            {
                cout << "Congrats! You have reached the end!"<<endl;
                if(end_time<time(NULL))
                    cout << "But you have spent too much time :(" << endl;
                else
                    cout << "And you did it in " << 90 - end_time + time(NULL) << "seconds." << endl;
                if(counter!=path)
                    cout << "But you didn't choose the shortest path" << endl;
                else
                    cout << "And you chose the shortest route." << endl;
                break;
            }
        }
    }

    for (int i = 0; i < maze_height; i++)
    {
        delete[] maze[i];
    }
    delete[] maze;

    return 0;
}

void Maze_output(int maze_height, int maze_width, char** maze)
{
    for(int i = 0; i<maze_height; i++)
    {
        for(int j = 0; j<maze_width; j++)
        {
            cout << maze[i][j] << "  ";
        }
        cout << endl;
    }
}

void move_wasd(char** &maze, Position &player, int i_add, int j_add)
{
    if(maze[player.i+i_add][player.j+j_add]=='#')
        cout<< "Sorry, there is a wall there." << endl;
    else
    {
        maze[player.i][player.j]='.';
        (player.i)+=i_add;
        (player.j)+=j_add;
        maze[player.i][player.j]='P';
    }
}

int Random_maze(char** &maze, Position &player, Position &end, int &maze_height, int &maze_width)
{
    srand(time(0)); 

    while(1)
    {   
        maze_height = 5 + (rand()%10);
        maze_width = 5 + (rand()%10);
        
        maze = new char*[maze_height];
        for (int i = 0; i < maze_height; i++)
        {
            maze[i] = new char[maze_width];
        }

        //заповнюємо лабіринт стінами
        for(int i = 0; i < maze_height; i++)
        {
            for(int j = 0; j < maze_width; j++)
            {
                if(i!=0 &&i!=maze_height-1&&j!=0&&j!=maze_width-1)
                    maze[i][j] = (rand() % 2 == 0) ? '#' : '.';
                else
                    maze[i][j] = '#';
            }
        }

        player.i = 1 + (rand() % (maze_height-2));
        player.j = 1 + (rand() % (maze_width-2));

        while (1)
        {
            end.i = 1 + (rand() % ((maze_height-2)));
            end.j = 1 + (rand() % ((maze_width-2)));
            if(!(end.i==player.i && end.j==player.j))
                break;
        }

        
        maze[player.i][player.j] = 'S'; 
        maze[end.i][end.j] = 'E';       
        
        //перевірка що лабіринт можно пройти
        int path = is_solvable(maze, player, end, maze_height, maze_width);
       
        if(path)
            return path;
        else
        {
            for (int i = 0; i < maze_height; i++)
            {
                delete[] maze[i];
            }
            delete[] maze;
        }
    }

    return 0;
}

//перевірка, чи можна пройти лабіринт
int is_solvable(char** maze, Position player, Position end, int maze_height, int maze_width)
{
    char** maze_copy = new char*[maze_height];
    for (int i = 0; i < maze_height; i++)
    {
        maze_copy[i] = new char[maze_width];
    }

    //копія лабіринту
    for(int i = 0; i < maze_height; i++)
        for(int j = 0; j < maze_width; j++)
            maze_copy[i][j] = maze[i][j];

    int result = dfs(maze_copy, player.i, player.j, end, maze_height, maze_width);
    
    if(result!=INT32_MAX&&result>5)
    {
        for (int i = 0; i < maze_height; i++)
        {
            delete[] maze_copy[i];
        }
        delete[] maze_copy;
        return result;
    }
    else
        return 0;
}

int dfs(char** maze, int i, int j, Position end, int maze_height, int maze_width)
{    
    if(i < 0 || i >= maze_height || j < 0 || j >= maze_width || maze[i][j] == '#')
        return INT32_MAX; 

    
    if(i == end.i && j == end.j)
        return 0;

    
    maze[i][j] = '#';

    
    int up = dfs(maze, i - 1, j, end, maze_height, maze_width);
    int down = dfs(maze, i + 1, j, end, maze_height, maze_width);
    int left = dfs(maze, i, j - 1, end, maze_height, maze_width);
    int right = dfs(maze, i, j + 1, end, maze_height, maze_width);

    maze[i][j] = '.'; 
    
    int min_path = min(up, min(down, min(left, right)));

    return (min_path == INT32_MAX) ? INT32_MAX : 1 + min_path;
}
