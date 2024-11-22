#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

enum Position { Goalkeeper, Defender, Midfielder, Forward };

struct Footballer {
    string surname;
    Position position;
    int age;
    int gamesPlayed;
    int goalsScored;
};

void writeToFile(const vector<Footballer>& team, const string& filename) {
    ofstream outFile(filename, ios::binary);
    if (outFile.is_open()) {
        size_t size = team.size();
        outFile.write(reinterpret_cast<char*>(&size), sizeof(size));
        outFile.write(reinterpret_cast<const char*>(team.data()), sizeof(Footballer) * team.size());
        outFile.close();
    }
}

vector<Footballer> readFromFile(const string& filename) {
    vector<Footballer> team;
    ifstream inFile(filename, ios::binary);
    if (inFile.is_open()) {
        size_t size;
        inFile.read(reinterpret_cast<char*>(&size), sizeof(size));
        team.resize(size);
        inFile.read(reinterpret_cast<char*>(team.data()), sizeof(Footballer) * size);
        inFile.close();
    }
    return team;
}

Footballer findBestForward(const vector<Footballer>& team) {
    Footballer bestForward;
    int maxGoals = -1;
    for (const auto& player : team) {
        if (player.position == Forward && player.goalsScored > maxGoals) {
            bestForward = player;
            maxGoals = player.goalsScored;
        }
    }
    return bestForward;
}

void printPlayersWithLessThan5Games(const vector<Footballer>& team) {
    for (const auto& player : team) {
        if (player.gamesPlayed < 5) {
            cout << "Футболіст: " << player.surname << ", Вік: " << player.age << ", Ігор: " << player.gamesPlayed << ", Голів: " << player.goalsScored << endl;
        }
    }
}

void deletePlayer(vector<Footballer>& team, const Footballer& playerToDelete) {
    auto it = find_if(team.begin(), team.end(), [&playerToDelete](const Footballer& player) {
        return player.surname == playerToDelete.surname;
        });
    if (it != team.end()) {
        team.erase(it);
    }
}

int main() {
    vector<Footballer> team = {
        {"Іванов", Forward, 25, 10, 8},
        {"Петренко", Midfielder, 27, 15, 3},
        {"Коваленко", Defender, 24, 8, 1},
        {"Шевченко", Forward, 30, 12, 15},
        {"Гончар", Goalkeeper, 22, 5, 0}
    };
    writeToFile(team, "team.dat");
    vector<Footballer> loadedTeam = readFromFile("team.dat");
    Footballer bestForward = findBestForward(loadedTeam);
    cout << "Кращий форвард: " << bestForward.surname << ", Голів: " << bestForward.goalsScored << endl;
    printPlayersWithLessThan5Games(loadedTeam);
    Footballer playerToDelete = { "Петренко", Midfielder, 27, 15, 3 };
    deletePlayer(loadedTeam, playerToDelete);
    writeToFile(loadedTeam, "team.dat");
    return 0;
}
