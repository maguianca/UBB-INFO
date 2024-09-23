#pragma once
#include<string>
#include<iostream>
using std::string;
class Turism
{
private:
	string denumire;
	string destinatie;
	string tip;
	double pret;
public:
	//metoda getter
	double get_pret()const;
	//metoda getter
	string get_denumire()const;
	//metoda getter
	string get_destinatie()const;
	//metoda getter
	string get_tip()const;
	//metoda getter
	void set_pret(double pret_nou)
	{
		//metoda setter
		pret = pret_nou;
	}
	void set_tip(string tip_nou)
	{
		//metoda setter
		tip = tip_nou;
	}
	Turism() = default;
	Turism(const string denumire, string destinatie, string tip, double pret) : denumire{ denumire }, destinatie{ destinatie }, tip{ tip }, pret{ pret } {
		//constructor Turism dupa parametrii denumire,destinatie,tip,pret
	}
	Turism(const Turism& ot) :denumire{ ot.denumire }, destinatie{ ot.destinatie }, tip{ ot.tip }, pret{ ot.pret } {
		//std::cout << "*\n";
		//constructor de copiere
	}
};

