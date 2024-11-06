#include <iostream>
#include <string>

using namespace std;

enum Role { GOALKEEPER, DEFENDER, MIDFIELDER, FORWARD };

struct FootballPlayer {
    char name[50];
    Role role;
    int age;
    int gamesPlayed;
    int goalsScored;
};

void writeToFile(FootballPlayer* players, int count, const char* filename) {
    FILE* file;
    errno_t err = fopen_s(&file, filename, "wb");
    if (err != 0 || file == nullptr) {
        cerr << "File could not be opened for writing." << endl;
        return;
    }
    fwrite(&count, sizeof(int), 1, file);
    for (int i = 0; i < count; i++) {
        fwrite(&players[i], sizeof(FootballPlayer), 1, file);
    }
    fclose(file);
}

FootballPlayer* readFromFile(int& count, const char* filename) {
    FILE* file;
    errno_t err = fopen_s(&file, filename, "rb");
    if (err != 0 || file == nullptr) {
        cerr << "File could not be opened for reading." << endl;
        return nullptr;
    }
    fread(&count, sizeof(int), 1, file);
    FootballPlayer* players = new FootballPlayer[count];
    for (int i = 0; i < count; i++) {
        fread(&players[i], sizeof(FootballPlayer), 1, file);
    }
    fclose(file);
    return players;
}

FootballPlayer getBestForward(FootballPlayer* players, int count) {
    FootballPlayer bestForward = { "not found", FORWARD, 0, 0, -1 };
    for (int i = 0; i < count; i++) {
        if (players[i].role == FORWARD && players[i].goalsScored > bestForward.goalsScored) {
            bestForward = players[i];
        }
    }
    return bestForward;
}

void printPlayersWithLessThan5Games(FootballPlayer* players, int count) {
    for (int i = 0; i < count; i++) {
        if (players[i].gamesPlayed < 5) {
            cout << "Name: " << players[i].name << ", Role: " << players[i].role
                << ", Age: " << players[i].age << ", Games: " << players[i].gamesPlayed
                << ", Goals: " << players[i].goalsScored << endl;
        }
    }
}

FootballPlayer* addPlayer(FootballPlayer* players, int& count, const FootballPlayer& player) {
    FootballPlayer* newPlayers = new FootballPlayer[count + 1];
    for (int i = 0; i < count; i++) {
        newPlayers[i] = players[i];
    }
    newPlayers[count] = player; 
    delete[] players;
    count++;
    return newPlayers;
}


FootballPlayer* removePlayer(FootballPlayer* players, int& count, const FootballPlayer& playerToRemove) {
    int newCount = 0;
    for (int i = 0; i < count; i++) {
        if (!(strcmp(players[i].name, playerToRemove.name) == 0 &&
            players[i].role == playerToRemove.role &&
            players[i].age == playerToRemove.age)) {
            newCount++;
        }
    }

    FootballPlayer* newPlayers = new FootballPlayer[newCount];
    int j = 0;
    for (int i = 0; i < count; i++) {
        if (!(strcmp(players[i].name, playerToRemove.name) == 0 &&
            players[i].role == playerToRemove.role &&
            players[i].age == playerToRemove.age)) {
            newPlayers[j++] = players[i];
        }
    }
    delete[] players;
    count = newCount;
    return newPlayers;
}

int main() {
    int count = 4;
    FootballPlayer* players = new FootballPlayer[count]{
        {"Ivan", FORWARD, 23, 10, 5},
        {"Petr", DEFENDER, 30, 2, 0},
        {"Vasja", DEFENDER, 30, 4, 3},
        {"Serega", MIDFIELDER, 28, 7, 2}
    };

    writeToFile(players, count, "file.bin");

    delete[] players;
    players = readFromFile(count, "file.bin");

    if (players) {
        FootballPlayer newPlayer = { "Kovalenko", GOALKEEPER, 26, 3, 0 };
        players = addPlayer(players, count, newPlayer);

        {
            int i = 999999;
            while (i > count - 1 || i < 0)
            {
                cout << "Who will be removed?" << "(" << count << ") ";
                cin >> i;
            }
            players = removePlayer(players, count, players[i]);
        }

        FootballPlayer bestForward = getBestForward(players, count);
        cout << "The best forward: " << bestForward.name << ", Goals: " << bestForward.goalsScored << endl;

        cout << "Players with less than 5 games:" << endl;
        printPlayersWithLessThan5Games(players, count);

        writeToFile(players, count, "file.bin");
        delete[] players;
    }

    return 0;
}
