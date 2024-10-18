#include <iostream>
#include <cmath>
using namespace std;

class Vector {
private:
    int size;
    int* coords;
public:
    Vector(int size, int* enteredCoords) {
        this->size = size;
        coords = new int[size];
        for (int i = 0; i < size; i++) {
            coords[i] = enteredCoords[i];
        }
    }

    Vector(const Vector& another) {
        cout << "Was copied" << endl;
        this->size = another.size;
        this->coords = new int[size];
        for (int i = 0; i < size; i++) {
            this->coords[i] = another.coords[i];
        }
    }

    double norma() const {
        int sum = 0;
        for (int i = 0; i < size; i++) {
            sum += coords[i] * coords[i];
        }
        return sqrt(sum);
    }

    void print() const {
        cout << "(";
        for (int i = 0; i < size; i++) {
            cout << coords[i];
            if (i < size - 1) {
                cout << ", ";
            }
        }
        cout << ")";
    }

    void setCoord(int index, int value) {
        if (index < 0 || index >= size) {
            cout << "Index is out of bounds!";
            return;
        }
        coords[index] = value;
    }

    ~Vector() {
        cout << "Deleted!" << endl;
        delete[] coords;
    }
};

double length(const Vector& v) {
    return v.norma();
}

int main() {
    int coords1[] = {1, 2, 3};
    Vector v1(3, coords1);
    cout << "Vector 1: ";
    v1.print();
    cout << "\nLength of Vector 1: " << length(v1) << endl;
    
    cout<<"\n";

    Vector v2 = v1;
    cout << "Copied Vector 2: ";// copying
    v2.print();
    cout << "\nLength of Vector 2: " << length(v2) << endl;

cout<<"\n";

    v2.setCoord(0, 10);
    cout << "Modified Vector 2: ";//change coordinates
    v2.print();
    cout << "\nLength of Modified Vector 2: " << length(v2) << endl;

cout<<"\n";

    int coords2[] = {5, 9};
    Vector v3(2, coords2);
    cout << "Vector 3: ";
    v3.print();
    cout << "\nLength of Vector 3: " << length(v3) << endl;

    Vector* vectors[3]
    vectors[0]= new Vector(coords3,4);
    vectors[1]= new Vector(coords10,2);
    vectors[2]= new Vector(coords4,1);
    for(int i=0;i<3;i++){
        
    cout<<"Vector "<<(i+1)<<":";
    vectors[i]->print();
    vector ;
    }

    return 0;
}