#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Medicin {
public:
    virtual ~Medicin() {}
    virtual void displayInfo() const = 0;
    virtual void saveToFile(ofstream& out) const = 0;
    virtual double getCost() const = 0;
};

class Tablets : public Medicin {
private:
    string name;
    double dosage;
    double cost;

public:
    Tablets(const string& n, double d, double c) : name(n), dosage(d), cost(c) {}

    void displayInfo() const override {
        cout << "Tablets: " << name << ", Dosage: " << dosage << " mg, Cost: $" << cost << endl;
    }

    void saveToFile(ofstream& out) const override {
        out << "Tablets " << name << " " << dosage << " mg $" << cost << endl;
    }

    double getCost() const override {
        return cost;
    }
};

class Syrup : public Medicin {
private:
    string name;
    double volume;
    double cost;

public:
    Syrup(const string& n, double v, double c) : name(n), volume(v), cost(c) {}

    void displayInfo() const override {
        cout << "Syrup: " << name << ", Volume: " << volume << " ml, Cost: $" << cost << endl;
    }

    void saveToFile(ofstream& out) const override {
        out << "Syrup " << name << " " << volume << " ml $" << cost << endl;
    }

    double getCost() const override {
        return cost;
    }
};

class Ampoule : public Medicin {
private:
    string name;
    double volume;
    double cost;

public:
    Ampoule(const string& n, double v, double c) : name(n), volume(v), cost(c) {}

    void displayInfo() const override {
        cout << "Ampoule: " << name << ", Volume: " << volume << " ml, Cost: $" << cost << endl;
    }

    void saveToFile(ofstream& out) const override {
        out << "Ampoule " << name << " " << volume << " ml $" << cost << endl;
    }

    double getCost() const override {
        return cost;
    }
};

void ensureFileExists(const string& filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error creating file: " << filename << endl;
    }
    file.close();
}

void populateMedicinesFile(int& instanceCount) {
    ofstream outFile("medicines.txt");
    if (!outFile) {
        cerr << "Error opening medicines.txt for writing." << endl;
        return;
    }

    vector<Medicin*> medicines;

    medicines.push_back(new Tablets("Paracetamol", 500, 0.5));
    instanceCount++;
    medicines.push_back(new Tablets("Ibuprofen", 200, 0.7));
    instanceCount++;
    medicines.push_back(new Syrup("Cough Syrup", 150, 3.0));
    instanceCount++;
    medicines.push_back(new Syrup("Vitamin D Syrup", 200, 4.5));
    instanceCount++;
    medicines.push_back(new Ampoule("Painkiller", 5, 2.0));
    instanceCount++;
    medicines.push_back(new Ampoule("Vitamin B12", 2, 1.5));
    instanceCount++;

    for (size_t i = 0; i < medicines.size(); ++i) {
        medicines[i]->saveToFile(outFile);
        delete medicines[i];
        instanceCount--;
    }

    outFile.close();
}

void displayMedicines() {
    ifstream inFile("medicines.txt");
    if (!inFile) {
        cerr << "Error opening medicines.txt for reading." << endl;
        return;
    }

    string line;
    int lineNumber = 1;
    cout << "Available medicines:\n";
    while (getline(inFile, line)) {
        cout << lineNumber++ << ". " << line << endl;
    }
    inFile.close();
}

void buyMedicines() {
    ifstream inFile("medicines.txt");
    if (!inFile) {
        cerr << "Error opening medicines.txt for reading." << endl;
        return;
    }

    vector<string> medicines;
    vector<double> costs;
    string line;
    while (getline(inFile, line)) {
        medicines.push_back(line);
        size_t pos = line.rfind('$');
        if (pos != string::npos) {
            costs.push_back(stod(line.substr(pos + 1)));
        } else {
            costs.push_back(0.0);
        }
    }
    inFile.close();

    ofstream outFile("check.txt");
    if (!outFile) {
        cerr << "Error opening check.txt for writing." << endl;
        return;
    }

    double totalCost = 0.0;

    while (true) {
        cout << "Enter the number of the medicine you want to buy (or 0 to finish):\n";
        int number;
        cin >> number;

        if (number == 0) {
            break;
        }

        if (number > 0 && number <= static_cast<int>(medicines.size())) {
            cout << "Enter the quantity of the medicine: ";
            int quantity;
            cin >> quantity;

            if (quantity > 0) {
                outFile << medicines[number - 1] << " x" << quantity << endl;
                double cost = costs[number - 1] * quantity;
                totalCost += cost;
                cout << "Medicine added to your check. Cost: $" << cost << ". Continue selecting or press 0 to finish.\n";
            } else {
                cerr << "Invalid quantity. Try again.\n";
            }
        } else {
            cerr << "Invalid medicine number. Try again.\n";
        }
    }

    outFile.close();

    ifstream checkFile("check.txt");
    if (!checkFile) {
        cerr << "Error opening check.txt for reading." << endl;
        return;
    }

    cout << "\nYour selection:\n";
    while (getline(checkFile, line)) {
        cout << line << endl;
    }
    checkFile.close();

    cout << "\nTotal cost of your purchase: $" << totalCost << endl;
}

int main() {
    int instanceCount = 0;

    ensureFileExists("medicines.txt");
    ensureFileExists("check.txt");
    populateMedicinesFile(instanceCount);

    int choice;
    do {
        cout << "Choose an option:\n";
        cout << "1. Display available medicines\n";
        cout << "2. Buy medicines\n";
        cout << "3. Exit\n";
        cin >> choice;

        if (choice == 1) {
            displayMedicines();
        } else if (choice == 2) {
            buyMedicines();
        } else if (choice == 3) {
            cout << "Exiting the program. Goodbye!\n";
        } else {
            cerr << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}
