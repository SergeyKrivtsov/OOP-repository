#include <iostream>

using namespace std;

class Creature {
private:
	int Rost = 0, Weight = 0, Age = 0;
	string Name;
	void setRost(int Rost) { this->Rost = Rost; }
	void setAge(int Age) { this->Age = Age; }
	void setWeight(int Weight) { this->Weight = Weight; }
	void setName(string Name) { this->Name = Name; }
public: 
	Creature () {}
	Creature(string Name, int Age, int Rost, int Weight) {
		setAge(Age);
		setRost(Rost);
		setWeight(Weight);
		setName(Name);
	}
	void Print() {
		cout << "We have Creature:" << endl;
		cout << "Its Name:" << getName() << endl;
		cout << "Its Age: " << getAge() << endl;
		cout << "Its Rost: " << getRost() << endl;
		cout << "Its Weight: " << getWeight() << endl;
	}
	/*static void Print(string Name, string Surname, int Age) {
		cout << "Your creature is called: " << Name << " " << Surname << ", and it's " << Age << " years old" << endl;
	}
	static void Print(string Name, string Surname, int Age, string Company) {
		cout << "Your creature is called: " << Name << " " << Surname << ", and it's " << Age << " years old" << endl
			<< "It works in " << Company << " company" << endl;;
	}*/
	int getRost() { return Rost; }
	int getAge() { return Age; }
	int getWeight() { return Weight; }
	string getName() { return Name; }
};

class Human : public Creature {
private:
	string Surname;
	void setSurname(string Surname) { this->Surname = Surname; }
public:
	Human () : Creature () {}
	Human(string Name, string Surname,int Age, int Rost, int Weight) : Creature(Name, Age, Rost, Weight) {
		setSurname(Surname);
	}
	void Print() {
		cout << "We have Human: " << endl;
		cout << "His Name: " << getName() << endl;
		cout << "His Surname: " << getSurname() << endl;
		cout << "His Age: " << getAge() << " years old" << endl;
		cout << "His Rost: " << getRost() << " cm" << endl;
		cout << "His Weight: " << getWeight() << " kg" << endl;
	}
	double Schitat(double a, double b, char Znak) {
		switch (Znak) {
		case '+': return a + b; break;
		case '-': return a - b; break;
		case '*': return a * b; break;
		case '/': return a / b; break;
		}
	}
	double Schitat(double a, double b, double c, char Znak) {
		switch (Znak) {
		case '+': return a + b + c; break;
		case '-': return a - b - c; break;
		case '*': return a * b * c; break;
		case '/': return a / b / c; break;
		}
	}
	string getSurname() { return Surname; }
};

void main() {
	//Creature::Print("Kirill", "Alikhanian", 21, "Karasina");
	Human chelovek("Kirill", "Alikhanian", 21, 183, 70);
	chelovek.Print();
	cout << "Human ymeet schitat : " << chelovek.Schitat(25, 10, 2, '/') << endl;
}