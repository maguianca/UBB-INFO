#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
class Participant {
protected:
	bool voluntar = true;
public:
	Participant() = default;
	virtual ~Participant() = default;
	virtual void tipareste() = 0;
	virtual bool eVoluntar() {
		return voluntar;
	}
};
class Personal :public Participant {
private:
	string nume;
public:
	Personal(const string nume) :nume{ nume } {}
	virtual void tipareste() override{
		cout << nume << " ";
	}
};
class Administrator :public Personal {
public:
	Administrator(const string nume) :Personal(nume) {}
	void tipareste() override {
		Personal::tipareste();
		cout << "Administrator" << " ";
	}
};
class Director :public Personal {
public:
	Director(const string nume) :Personal(nume) {}
	void tipareste() override {
		Personal::tipareste();
		cout << "Director" << " ";
	}
};
class Angajat :public Participant {
private:
	Participant* p;
public:
	Angajat(Participant* p) :p{ p } {
		voluntar = false;
	};
	void tipareste() override {
		p->tipareste();
		cout << "angajat" << " ";
	}
	~Angajat() {
		if (p != nullptr)
			delete p;
	}
};
class ONG {
private:
	vector<Participant*>toti;
public:ONG() = default;
	  void add(Participant* p) {
		  toti.push_back(p);
	  }
	  vector<Participant*>getAll(bool voluntar) {
		  vector<Participant*>rez;
		  for (const auto& l : toti) {
			  if (l->eVoluntar() == voluntar)
				  rez.push_back(l);
		  }
		  return rez;
	  }
};
ONG functie2() {
	ONG ob;
	ob.add(new Administrator{ "George" });
	ob.add(new Angajat{ new Administrator{"Ion"} });
	ob.add(new Director{ "Matei" });
	ob.add(new Angajat{ new Director{"Mihai"} });
	return ob;
}
/*
int main() {
	ONG o = functie2();
	vector<Participant*>voluntari = o.getAll(true);
	vector<Participant*>angajati = o.getAll(false);
	for (const auto& l : voluntari)
	{
		l->tipareste();
		cout << endl;
		delete l;
	}
	cout << endl << endl;
	for (const auto& l : angajati)
	{
		l->tipareste();
		cout << endl;
		delete l;
	}
}
*/
template<typename T>
class Cos {
private:
	vector<T>obiecte;
public:
	Cos() = default;
	Cos& operator=(const T& other) {
		if (this != other)
		{
			obiecte = other.obiecte;
		}
		return *this;
	}
	Cos& operator+(const T& ob) {
		obiecte.push_back(ob);
		return *this;
	}
	Cos& undo() {
		if (obiecte.size() > 0)
			obiecte.pop_back();
		return *this;
	}
	void tipareste(ostream& out) {
		for (const auto& l : obiecte) {
			out << l << " ";
		}
	}
};
void cumparaturi() {
	Cos<string> cos;//creaza un cos de cumparaturi
	cos = cos + "Mere"; //adauga Mere in cos
	cos.undo();//elimina Mere din cos
	cos + "Mere"; //adauga Mere in cos
	cos = cos + "Paine" + "Lapte";//adauga Paine si Lapte in cos
	cos.undo().undo();//elimina ultimele doua produse adaugate
	cos.tipareste(cout);//tipareste elementele din cos (Mere)
}
/*
int main() {
	cumparaturi();
	return 0;
}
*/