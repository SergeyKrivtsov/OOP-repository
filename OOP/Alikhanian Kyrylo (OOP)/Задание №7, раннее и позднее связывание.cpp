// Розробити клас, похідний класу Point. Протестувати раннє
//та пізніше(поліморфне) зв'язування

#include <iostream>

using namespace std;

class Shapee {
	public:
	virtual void draw() {
		cout << "I`m Shape" << endl;
	}
};

class Circle : public Shapee {
public:
	void draw() override {
		cout << "I`m Circle" << endl;
	}
};

class Square : public Shapee {
public:
	void draw() override {
		cout << "I`m Square" << endl;
	}
};

class Triangle : public Shapee {
public:
	void draw() override {
		cout << "I`m Triangle" << endl;
	}
};

class Oval : public Circle {
public:
	void draw() override {
		cout << "I`m Oval" << endl;
	}
};

class Rect : public Square {
public:
	void draw() override {
		cout << "I`m Rectangle" << endl;
	}
};

//static Shapee RandomShape() {
//	switch ((rand()%1+5))
//	{
//	case 1: return Circle();
//		break;
//	case 2: return Square();
//		break;
//	case 3: return Triangle();
//		break;
//	case 4: return Oval();
//		break;
//	case 5: return Rect();
//		break;
//	default:
//		break;
//	}
//}

void printchislo(int a) {
	cout << "Chislo = " << a << endl;
 }

void printchislo(double a) {
	cout << "SupermegapupaChislo = " << a << endl;
}

int main()
{
	printchislo(2);
	printchislo(2.5);
	/*Shapee* mas = new Shapee[5]{
		RandomShape(),RandomShape(),RandomShape(),RandomShape(),RandomShape()
	};
	for (size_t i = 0; i < 5; i++)
	{
		mas[i].draw();
	}*/
	Shapee* shap0 = new Shapee();
	Shapee* shap1 = new Circle();
	Shapee* shap2 = new Triangle();
	Shapee* shap3 = new Square();
	Shapee* shap4 = new Oval();
	Shapee* shap5 = new Rect();
	shap0->draw();
	shap1->draw();
	shap2->draw();
	shap3->draw();
	shap4->draw();
	shap5->draw();
	delete shap0;
	delete shap1;
	delete shap2;
	delete shap3;
	delete shap4;
	delete shap5;
}
