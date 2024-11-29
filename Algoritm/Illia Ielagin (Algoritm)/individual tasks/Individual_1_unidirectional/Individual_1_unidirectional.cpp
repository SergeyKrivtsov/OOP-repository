#include <iostream>

using namespace std;

// ����� ��� ������ ������ �����
struct LineNode {
    int line;
    LineNode* next;

    LineNode(int l){ 
        line = l; 
        next = nullptr;
    }
};

// ����� ��� ������ �������� ���
struct KeywordNode {
    string word;
    LineNode* lines;  // ������ ������ ������ �����
    KeywordNode* next;

    KeywordNode(const string& w) {
        word = w;
        lines = nullptr;
        next = nullptr;
    }
};

// ��������� ��� ����������� ���������
struct SubjectIndex {
    KeywordNode* head;  // ������ ������ �������� ���

    SubjectIndex(){ 
        head = nullptr; 
    }

    // ��������� ������ ��������� �����
    void addKeyword(const string& keyword) {
        if (!findKeyword(keyword)) {
            KeywordNode* newNode = new KeywordNode(keyword);
            if (!head || head->word > keyword) {
                newNode->next = head;
                head = newNode;
            }
            else {
                KeywordNode* current = head;
                while (current->next && current->next->word < keyword) {
                    current = current->next;
                }
                newNode->next = current->next;
                current->next = newNode;
            }
        }
    }

    // ��������� ��������� �����
    void removeKeyword(const string& keyword) {
        if (!head) return;

        if (head->word == keyword) {
            KeywordNode* temp = head;
            head = head->next;
            clearLines(temp->lines);
            delete temp;
            return;
        }

        KeywordNode* current = head;
        while (current->next && current->next->word != keyword) {
            current = current->next;
        }

        if (current->next) {
            KeywordNode* temp = current->next;
            current->next = temp->next;
            clearLines(temp->lines);
            delete temp;
        }
    }

    // ��������� ������ ����� ��� ��������� �����
    void addLineForKeyword(const string& keyword, int line) {
        KeywordNode* keywordNode = findKeyword(keyword);
        if (!keywordNode) return;

        LineNode* current = keywordNode->lines;
        LineNode* newNode = new LineNode(line);

        // ������ � ������ � ��������������
        if (!current || current->line > line) {
            newNode->next = current;
            keywordNode->lines = newNode;
        }
        else {
            while (current->next && current->next->line < line) {
                current = current->next;
            }
            if (!current->next || current->next->line != line) {
                newNode->next = current->next;
                current->next = newNode;
            }
        }
    }

    // ��������, �� � ������� ����� � ������
    bool keywordInLine(const string& keyword, int line) {
        KeywordNode* keywordNode = findKeyword(keyword);
        if (!keywordNode) return false;

        LineNode* current = keywordNode->lines;
        while (current) {
            if (current->line == line) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // ��������� ����������� ���������
    void printIndex() const {
        KeywordNode* current = head;
        while (current) {
            cout << current->word << ": ";
            LineNode* lineCurrent = current->lines;
            while (lineCurrent) {
                cout << lineCurrent->line << " ";
                lineCurrent = lineCurrent->next;
            }
            cout << "\n";
            current = current->next;
        }
    }

    // �������� ���'�� ��� �������� ������ ������ �����
    void clearLines(LineNode* lineHead) {
        while (lineHead) {
            LineNode* temp = lineHead;
            lineHead = lineHead->next;
            delete temp;
        }
    }

    // �������� ���'�� ��� �������� ����������� ���������
    ~SubjectIndex() {
        while (head) {
            KeywordNode* temp = head;
            head = head->next;
            clearLines(temp->lines);
            delete temp;
        }
    }

private:
    // ����� ��������� ����� � ������
    KeywordNode* findKeyword(const string& keyword) {
        KeywordNode* current = head;
        while (current) {
            if (current->word == keyword) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
};

// ������� ����� �� �����
bool readFile(const char* fileName, string text[], int& lineCount, string keywords[], int& keywordCount) {
    FILE* file;
    if (fopen_s(&file, fileName, "r") != 0) {
        cerr << "File opening error: " << fileName << "\n";
        return false;
    }

    char buffer[1024];
    bool readingText = true;

    while (fgets(buffer, sizeof(buffer), file)) {
        string line(buffer);
        if (!line.empty() && (line.back() == '\n' || line.back() == '\r')) {
            line.pop_back();
        }

        if (line.empty()) {
            if (!readingText) {
                break;
            }
            readingText = false;
            continue;
        }

        if (readingText) {
            text[lineCount++] = line;
        }
        else {
            keywords[keywordCount++] = line;
        }
    }

    fclose(file);
    return true;
}

int main() {
    const char* fileName = "input.txt";
    string text[1000];
    int lineCount = 0;
    string keywords[100];
    int keywordCount = 0;

    if (!readFile(fileName, text, lineCount, keywords, keywordCount)) {
        return 1;
    }

    SubjectIndex subjectIndex;

    // ��������� �������� ���
    for (int i = 0; i < keywordCount; ++i) {
        subjectIndex.addKeyword(keywords[i]);
    }

    // �������� ����������� ���������
    for (int i = 0; i < lineCount; ++i) {
        for (int j = 0; j < keywordCount; ++j) {
            if (text[i].find(keywords[j]) != string::npos) {
                subjectIndex.addLineForKeyword(keywords[j], i + 1);
            }
        }
    }

    // ��������� ����������
    cout << "\nSubject index:\n";
    subjectIndex.printIndex();

    // ��������� ��������� �����
    subjectIndex.removeKeyword(keywords[0]);

    cout << "\nExample of removing a keyword.\n";
    cout << "\nSubject index:\n";
    subjectIndex.printIndex();

    return 0;
}
