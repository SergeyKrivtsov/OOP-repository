// Створення, заповнення, вивід бінарного дерева та його прямий, симетричний та зворотній обхід.    
#include <iostream>
#include <string>

using namespace std;

struct Node {
    int value;
    Node* right;
    Node* left;

public:
    Node(int val) {
        value = val;
        right = nullptr;
        left = nullptr;
    }
    void insert(Node* head, int val) {
        if (val > (*head).value)
        {
            if ((*head).right == nullptr)
            {
                (*head).right = new Node(val);
            }
            else
            {
                insert((*head).right, val);
            }
        }
        if (val < (*head).value)
        {
            if ((*head).left == nullptr)
            {
                (*head).left = new Node(val);
            }
            else
            {
                insert((*head).left, val);
            }
        }
    }

    void printBT(const string& prefix, const Node* head, bool isLeft)
    {
        if (head != nullptr)
        {
            cout << prefix;

            cout << (isLeft ? "|--" : "---");

            cout << head->value << endl;

            printBT(prefix + (isLeft ? "|   " : "    "), head->left, true);
            printBT(prefix + (isLeft ? "|   " : "    "), head->right, false);
        }
    }

    void printBT(const Node* head)
    {
        printBT("", head, false);
    }

    
    void directLoop(Node* head) {
        cout << (*head).value << " ";
        if ((*head).left != nullptr)
        {
            directLoop((*head).left);
        }
        if ((*head).right != nullptr)
        {
            directLoop((*head).right);
        }
    }
    void symmetricalLoop(Node* head) {
        if ((*head).left != nullptr)
        {
            symmetricalLoop((*head).left);
        }
        cout << (*head).value << " ";
        if ((*head).right != nullptr)
        {
            symmetricalLoop((*head).right);
        }
    }
    void reverseLoop(Node* head) {
        if ((*head).left != nullptr)
        {
            reverseLoop((*head).left);
        }
        if ((*head).right != nullptr)
        {
            reverseLoop((*head).right);
        }
        cout << (*head).value << " ";
    }
};

int main()
{
    int n;
    string str;
    cout << "input value in tree: ";
    cin >> n;
    Node* head = new Node(n);
    cout << "do you want input more values? If yes, then write it. If no, write 'end'." << endl;
    do{
        cout << " Waiting:";
        cin >> str;
        if (str != "end")
        {
            n = stoi(str);
            head->insert(head, n);
        }
    } while (str != "end");
    cout << "your bintree:" << endl;
    head->printBT(head);
    cout << "direct loop of your bintree:" << endl;
    head->directLoop(head);
    cout << endl << "symmetrical loop  of your bintree:" << endl;
    head->symmetricalLoop(head);
    cout << endl << "reverse loop of your bintree:" << endl;
    head->reverseLoop(head);

    return 0;
}

