#include <iostream>

using namespace std;

enum Role { GOALKEEPER, DEFENDER, MIDFIELDER, FORWARD };

struct FootballPlayer {
    char name[50];
    Role role;
    int age;
    int gamesPlayed;
    int goalsScored;
};

struct Node {
    FootballPlayer player;
    Node* next;
};

void addPlayer(Node*& head, FootballPlayer player) {
    Node* newNode = new Node{ player, nullptr };
    if (head == nullptr) {
        head = newNode;
    }
    else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

FootballPlayer getBestForward(Node* head) {
    FootballPlayer bestForward = { "not found", FORWARD, 0, 0, -1 };
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->player.role == FORWARD && temp->player.goalsScored > bestForward.goalsScored) {
            bestForward = temp->player;
        }
        temp = temp->next;
    }
    return bestForward;
}

void printPlayersWithLessThan5Games(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->player.gamesPlayed < 5) {
            cout << "Name: " << temp->player.name
                << ", Role: " << temp->player.role
                << ", Age: " << temp->player.age
                << ", Games: " << temp->player.gamesPlayed
                << ", Goals: " << temp->player.goalsScored << endl;
        }
        temp = temp->next;
    }
}

void deleteList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Node* players = nullptr;

    addPlayer(players, { "Ivan", FORWARD, 23, 10, 5 });
    addPlayer(players, { "Petr", DEFENDER, 30, 2, 0 });
    addPlayer(players, { "Vasja", DEFENDER, 30, 4, 3 });
    addPlayer(players, { "Serega", MIDFIELDER, 28, 7, 2 });

    FootballPlayer bestForward = getBestForward(players);
    cout << "The best forward: " << bestForward.name << ", Goals: " << bestForward.goalsScored << endl;

    cout << "Players with less than 5 games:" << endl;
    printPlayersWithLessThan5Games(players);

    deleteList(players);

    return 0;
}
