/*
Описати структуру Футболіст з полями:
    Прізвище
    Амплуа (тип перечислення)
    Вік
    Кількість ігор
    Кількість забитих голів
Створити динамічний масив структур, записати його в бінарний
файл.
Зчитати інформацію з файлу і реалізувати функції:
визначити кращого форварда і вивести інформацію про нього;
вивести відомості про футболістів, які зіграли менше 5-ти ігор.
Реалізувати можливість додавати нових гравців і видаляти тих, хто
пішов з команди:
Написати функцію видалення однієї структури, в якості параметра
передати структуру, яку слід видалити.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_TEXT_SIZE 100

typedef enum {Goalkeeper, Midfielder, Striker, Centre_forward, Winger} amplua;

typedef struct{
    char surname[MAX_TEXT_SIZE];
    int age;
    amplua fb_amplua;
    int amount_of_games;
    int amount_of_goals;
} fp;

void add_players(fp **team, int *amount){
    int status = 0;
    printf("Please, enter footballers:\n");
    do {
        int temp_pos = 0;
        *team = (fp *)realloc(*team, (*amount + 1) * sizeof(fp));
        printf("Please, enter the surname of %d's footballer --> ", *amount + 1);
        getchar();  // Очистка буфера перед использованием fgets
        fgets((*team)[*amount].surname, MAX_TEXT_SIZE, stdin);
        int len = strlen((*team)[*amount].surname);
        if (len > 0 && (*team)[*amount].surname[len-1] == '\n') {
            (*team)[*amount].surname[len-1] = '\0';
        }

        printf("Please, enter the age of %d's footballer --> ", *amount + 1);
        scanf("%d", &(*team)[*amount].age);

        printf("Please, enter the amplua of %d's footballer\n0 - Goalkeeper\n1 - Midfielder\n2 - Striker\n3 - Centre_forward\n4 - Winger\n--> ", *amount + 1);
        scanf("%d", &temp_pos);
        (*team)[*amount].fb_amplua = (amplua)temp_pos;

        printf("Please, enter the amount_of_games of %d's footballer --> ", *amount + 1);
        scanf("%d", &(*team)[*amount].amount_of_games);

        printf("Please, enter the amount_of_goals of %d's footballer --> ", *amount + 1);
        scanf("%d", &(*team)[*amount].amount_of_goals);

        printf("Do you want to enter one more footballer?\n(Current amount is %d)\n0 - Yes\nOther - No --> ", *amount + 1);
        scanf("%d", &status);
        
        (*amount)++;
    } while (status == 0);
}

void write_team(fp* team, int amount){
    FILE *file = fopen("footballers.bin", "ab");
    if (file != NULL) {
        fwrite(team, sizeof(fp), amount, file);
        fclose(file);
    }
}

fp* read_team(int amount) {
    FILE *file = fopen("footballers.bin", "rb");
    if (file == NULL) {
        printf("Error opening file.\n");
        return NULL;
    }
    fp* team = (fp*)malloc(amount * sizeof(fp));
    if (team != NULL) {
        fread(team, sizeof(fp), amount, file);
    }
    fclose(file);
    return team;
}

void best_forward(fp* team, int amount) {
    if (amount == 0) {
        printf("No players available.\n");
        return;
    }
    int max_goals_index = 0;
    for (int i = 1; i < amount; i++) {
        if (team[i].amount_of_goals > team[max_goals_index].amount_of_goals) {
            max_goals_index = i;
        }
    }
    printf("Footballer with the most goals:\n");
    printf("Surname: %s\n", team[max_goals_index].surname);
    printf("Age: %d\n", team[max_goals_index].age);
    printf("Amplua: %d\n", team[max_goals_index].fb_amplua);
    printf("Amount of games: %d\n", team[max_goals_index].amount_of_games);
    printf("Amount of goals: %d\n", team[max_goals_index].amount_of_goals);
    printf("-----------------------------\n");
}

void less_than_five_games(fp* team, int amount){
    printf("Footballers with less than 5 games:\n");
    for (int i = 0; i < amount; i++) {
        if (team[i].amount_of_games < 5) {
            printf("Surname: %s\n", team[i].surname); 
            printf("Age: %d\n", team[i].age);
            printf("Amplua: %d\n", team[i].fb_amplua);
            printf("Amount of games: %d\n", team[i].amount_of_games);
            printf("Amount of goals: %d\n", team[i].amount_of_goals);
            printf("-----------------------------\n");
        }
    }
}

int main()
{
    int fb_amount = 0;
    fp* fb_team = NULL;
    add_players(&fb_team, &fb_amount);
    write_team(fb_team, fb_amount);
    free(fb_team);
    fp* fb_team_read = read_team(fb_amount);
    if (fb_team_read != NULL) {
        best_forward(fb_team_read, fb_amount);
        less_than_five_games(fb_team_read, fb_amount);
        free(fb_team_read);
    }
    return 0;
}