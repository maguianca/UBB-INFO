#pragma once
#include<string>
#include<iostream>
using namespace std;


class PlacaDeBaza {
protected:
	string nume;
	string soclu;
	int pret;
public:
	PlacaDeBaza(string nume, string soc, int pret) :nume{ nume }, soclu{ soc }, pret{ pret } {}
	virtual string get_nume()
	{
		return nume;
	}
	virtual string get_soclu()
	{
		return soclu;
	}
	virtual int get_pret()
	{
		return pret;
	}
};

class Procesor1 :protected PlacaDeBaza{
private:
	int numarT;
public:
	Procesor1(string nume, int tr, string soc, int pret) :PlacaDeBaza(nume, soc, pret) {
		this->numarT = tr;
	}
	string get_nume()override {
		return PlacaDeBaza::nume;
	}
	string get_soclu()override {
		return PlacaDeBaza::soclu;
	}
	int get_pret()override {
		return PlacaDeBaza::pret;
	}
	int get_numar() {
		return numarT;
	}
};