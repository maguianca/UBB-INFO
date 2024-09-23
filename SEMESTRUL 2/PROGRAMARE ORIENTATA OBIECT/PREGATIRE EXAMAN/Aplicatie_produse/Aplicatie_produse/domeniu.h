#pragma once
#include<iostream>
using namespace std;
class Produs {
private:
	int id;
	string nume;
	string tip;
	double pret;
public:
	Produs(int id, const string& nume, const string& tip, double pret) :id{ id }, nume{ nume }, tip{ tip }, pret{ pret } {}
	//constructor id nume tip pret
	int get_id()const { return id; }
	//returneaza id int
	string get_nume()const { return nume; }
	//returneaza nume string
	string get_tip()const { return tip; }
	//returneaza tip string
	double get_pret()const { return pret; }
	//returneaza pret double
};