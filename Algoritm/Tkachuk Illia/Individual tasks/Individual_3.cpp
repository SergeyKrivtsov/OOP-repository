#include <iostream>
#include <vector>
#include <string>

#define Green "\033[32m"  
#define Red "\033[31m"    
#define Reset "\033[0m"   
using namespace std;

class SortedSet {
private:
    int TABLE_SIZE = 50;
    int MAX_ROW = 10;
    int MAX_COL = 5;

   struct Node {
      int value;
      Node* next;
      Node(int v) : value(v), next(nullptr) {}
   };

   vector<Node*> table;

   int hash(int key) const {
      return key % TABLE_SIZE;
   }

   bool existsInList(Node* head, int key) const {
      Node* current = head;
      while (current) {
         if (current->value == key) {
            return true;
         }
         current = current->next;
      }
      return false;
   }

   void sortList(Node*& head) {
      if (!head || !head->next) return;

      Node* sorted = nullptr;

      while (head) {
         Node* current = head;
         head = head->next;

            if (!sorted || current->value <= sorted->value) {
               current->next = sorted;
               sorted = current;
            }else {
               Node* temp = sorted;
               while (temp->next && temp->next->value < current->value) {
                  temp = temp->next;
               }
               current->next = temp->next;
               temp->next = current;
            }
        }
        head = sorted;
   }

public:
   SortedSet() : table(TABLE_SIZE, nullptr) {}

   bool add(int key) {
      int index = hash(key);
      Node*& bucket = table[index];

      if (existsInList(bucket, key)) {
         return false;
      }

      Node* newNode = new Node(key);
      newNode->next = bucket;
      bucket = newNode;

      sortList(bucket);
      return true;
   }


   bool contains(int key) const {
      int index = hash(key);
      Node* bucket = table[index];
      return existsInList(bucket, key);
   }

   void display() const {
      cout << "Місця (заброньовані позначені 'X', вільні позначені 'O'):" << endl;

      for (int row = 1; row <= MAX_ROW; ++row) {
            for (char col = 'A'; col < 'A' + MAX_COL; ++col) {
               int seat = (row - 1) * 5 + (col - 'A');
               if (contains(seat)) {
                  cout << Red << row << col << ": X\t" << Reset;
               } else {
                  cout << Green << row << col << ": O\t" << Reset;
               }
            }
            cout << endl;
      }
   }

   void showFreeSeats() const {
      vector<string> freeSeats;

        for (int row = 1; row <= MAX_ROW; ++row) {
            for (char col = 'A'; col < 'A' + MAX_COL; ++col) {
               int seat = (row - 1) * 5 + (col - 'A');
                if (!contains(seat)) {
                  freeSeats.push_back(to_string(row) + col);
               }
            }
        }

      if (freeSeats.empty()) {
            cout << "Сорри, вільних місць немає." << endl;
      }else {
            cout << "\nВільні місця: ";
            for (size_t i = 0; i < freeSeats.size(); ++i) {
               cout << freeSeats[i];
               if (i != freeSeats.size() - 1) {
                  cout << ", ";
                }
            }
            cout << endl;
        }
   }

   bool isValidSeat(const string& seat) const {
      if (seat.size() != 2) return false;

      int row = seat[0] - '0'; 
      char col = seat[1];     

      if (row < 1 || row > MAX_ROW) return false;
      if (col < 'A' || col >= 'A' + MAX_COL) return false;

      return true;
   }

   void bookSeats() {
      int numSeats;
      cout << "\nСкільки місць ви хочете забронювати? ";
      cin >> numSeats;

        for (int i = 0; i < numSeats; ++i) {
            string seat;
            bool validSeat = false;
            while (!validSeat) {
               cout << "Введіть номер місця (наприклад, 3B): ";
               cin >> seat;

               if (isValidSeat(seat)) {
                  int row = seat[0] - '0'; 
                  char col = seat[1];     
                  int seatIndex = (row - 1) * 5 + (col - 'A');

                  if (!contains(seatIndex)) {
                     add(seatIndex);
                     cout << "Місце " << seat << " успішно заброньоване!" << endl;
                     validSeat = true;
                  }else {
                     cout << "Місце " << seat << " вже зайняте. Спробуйте ще раз." << endl;
                  }
               }else {
                    cout << "Неправильний номер місця. Будь ласка, введіть коректне місце (наприклад, 3B)." << endl;
               }
            }
        }

      cout << "\nОновлений стан місць: " << endl;
      display();
   }
};

int main() {
   SortedSet seats;
   seats.add(0);  
   seats.add(7);  
   seats.add(11); 
   seats.add(22); 
   seats.add(49);
   seats.add(25);
   seats.add(31);
   seats.add(15);
   seats.add(29);
   seats.display();
   int choice;
   do {
      cout << "\nМеню:";
      cout << "\n1. Забронювати місця";
      cout << "\n2. Показати вільні місця";
      cout << "\n3. Вийти";
      cout << "\nВиберіть опцію: ";
      cin >> choice;

      switch (choice) {
            case 1:
               seats.bookSeats();
               break;
            case 2:
               seats.showFreeSeats();
               break;
            case 3:
               cout << "Завершення програми..." << endl;
               break;
            default:
               cout << "Невірний вибір, спробуйте ще раз." << endl;
        }
   } while (choice != 3);

   return 0;
}
