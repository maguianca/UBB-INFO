#pragma once
#include<string>
#include<iostream>
using std::string;
using std::cout;
class Turism
{
private:
	string denumire;
	string destinatie;
	string tip;
	double pret;
public:
	double get_pret()const;
	string get_denumire()const;
	string get_destinatie()const;
	string get_tip()const;
	Turism(string denumire, string destinatie, string tip, double pret) : denumire{ denumire }, destinatie{ destinatie }, tip{ tip }, pret{ pret } {

	}
	Turism(const Turism& ot) :denumire{ ot.denumire }, destinatie{ ot.destinatie }, tip{ ot.tip }, pret{ ot.pret } {
		std::cout << "*\n";
	}
};