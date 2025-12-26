#pragma once
#include<iostream>
using namespace std;
class Rochie {
private:
	int cod;
	string denumire;
	string marime;
	int pret;
	string disponibilitate;
public:
	Rochie(const int& cod,const string& denumire,const string& marime, const int& pret,const string& disponibilitate) :cod{ cod }, denumire{ denumire }, marime{ marime },
		pret{ pret }, disponibilitate{ disponibilitate } {}
	//contructor al clasei rochie
	//metoda getter returneaza denumire-string
	string get_denumire()const { return denumire; };
	//metoda getter returneaza marime-string
	string get_marime()const { return marime; };
	//metoda getter returneaza disponibilitate-string
	string get_disponibilitate()const { return disponibilitate; };
	//metoda getter returneaza pret-int
	int get_pret() const{ return pret; };
	//metoda getter returneaza cod-int
	int get_cod() const{ return cod; };
	//metoda setter seteaza atributul clasei rochie la atributul string text
	void set_disponibilitate(const string& text) { disponibilitate = text; }
	bool operator==(const Rochie& a)const {
		return a.get_cod() == cod;
	}
};