#include <iostream>
#include <vector>

using namespace std;

// ��������� ������� (Set) �� ����� ���-�������
class HashSet {
private:
    static const int TABLE_SIZE = 100; // ����� ���-�������
    vector<vector<string>> table; // ���-�������: ����� ������

    // ���-�������
    int hash(const string& key) const {
        int h = 0;
        for (char ch : key) {
            h = (h * 31 + ch) % TABLE_SIZE;
        }
        return h;
    }

public:
    HashSet() : table(TABLE_SIZE) {}

    // ������ ������� � �������
    void insert(const string& key) {
        int index = hash(key);
        for (const auto& element : table[index]) {
            if (element == key) {
                return; // ������� ��� ����
            }
        }
        table[index].push_back(key);
    }

    // ���������, �� ���� ������� � ������
    bool contains(const string& key) const {
        int index = hash(key);
        for (const auto& element : table[index]) {
            if (element == key) {
                return true;
            }
        }
        return false;
    }

    // ��������� �� �������� � �������
    vector<string> getElements() const {
        vector<string> elements;
        for (const auto& bucket : table) {
            for (const auto& element : bucket) {
                elements.push_back(element);
            }
        }
        return elements;
    }
};

int main() {
    // ������ ���������� �����
    HashSet invited;
    invited.insert("Alice");
    invited.insert("Bob");
    invited.insert("Alastor");
    invited.insert("Charlie");
    invited.insert("Diana");

    // ������ ���, ��� ������
    HashSet arrived;
    arrived.insert("Bob");
    arrived.insert("Charlie");
    arrived.insert("Alastor");
    arrived.insert("Eve");
    arrived.insert("Frank");

    // ��������� ���, ��� ����� ���� ������ � �����������
    vector<string> attending;

    for (const string& person : invited.getElements()) {
        if (arrived.contains(person)) {
            attending.push_back(person);
        }
    }

    // �������� ������ ��������
    cout << "Conference participants:\n";
    for (const auto& person : attending) {
        cout << person << '\n';
    }

    return 0;
}
