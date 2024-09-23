#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
class Pizza {
private:
	int pret;
public:
	Pizza(const int pret) :pret{ pret } {}
	virtual ~Pizza() = default;
	virtual string descriere() = 0;
	virtual int getPret() {
		return pret;
	}
};
class BasicPizza :public Pizza {
private:
	string denumire;
public:
	BasicPizza(const string denumire, const int pret) :denumire{ denumire }, Pizza(pret) {}
    int getPret()override {
		return Pizza::getPret();
	}
	string descriere()override {
		return denumire;
	}
};
class PizzaCuPeperoni :public Pizza {
private:
	Pizza* p;
public:
	PizzaCuPeperoni(Pizza* p) :Pizza(p->getPret()), p{ p } {}
	~PizzaCuPeperoni() {
		if (p != nullptr)
			delete p;
	}
	int getPret()override {
		return p->getPret() + 2;
	}
	string descriere()override {
		return p->descriere() + " cu peperoni ";
	}
};
class PizzaCuCiuperci :public Pizza {
private:
	Pizza* p;
public:
	PizzaCuCiuperci(Pizza* p) :Pizza(p->getPret()), p{ p } {}
	~PizzaCuCiuperci() {
		if (p != nullptr)
			delete p;
	}
	int getPret()override {
		return p->getPret() + 3;
	}
	string descriere()override {
		return p->descriere() + " cu ciuperci ";
	}
};
vector<Pizza*>functie2() {
	vector<Pizza*>rez;
	rez.push_back(new PizzaCuCiuperci(new BasicPizza{ "Salami",33 }));
	rez.push_back(new BasicPizza{ "Salami",33 });
	rez.push_back(new PizzaCuCiuperci(new PizzaCuPeperoni(new BasicPizza{ "Diavola",35 })));
	return rez;
}
/*
int main() {
	vector<Pizza*>rez = functie2();
	sort(rez.begin(), rez.end(), [](Pizza* p1, Pizza* p2) {return p1->getPret() > p2->getPret(); });
	for (auto& l : rez)
		cout << l->descriere() << " " << l->getPret() << endl;
	return 0;
}*/
//EXERCITIUL 4
template<typename T>
class Catalog {
private:
	string materie;
	vector<T>note;
public:
	Catalog(const string materie) :materie{ materie } {};
	Catalog& operator+(const T& op) {
		note.push_back(op);
		return *this;
	}
	Catalog& operator=(const T& other)
	{
		if (this != other) {
			note = other.note;
			materie = other.materie;
		}
		return *this;
	}
	typename vector<T>::iterator end() {
		return note.end();
	}
	typename vector<T>::iterator begin() {
		return note.begin();
	}
};
void catalog() {
	Catalog<int> cat{ "OOP" };//creaza catalog cu note intregi
	cat + 10; //adauga o nota in catalog
	cat = cat + 8 + 6;
	int sum = 0;
	for (auto n : cat) { sum += n; } //itereaza notele din catalog
	std::cout << "Suma note:" << sum << "\n";
}

/*
int main() {
	catalog();
	return 0;
}*/