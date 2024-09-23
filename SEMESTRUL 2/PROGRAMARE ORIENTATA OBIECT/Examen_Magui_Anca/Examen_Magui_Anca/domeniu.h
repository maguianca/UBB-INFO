#pragma once
#include<iostream>
using namespace std;
class Utilaj {
private:
	int id;
	string denumire;
	string tip;
	int cilindri;
public:
	Utilaj(int id, const string denumire, const string tip, int cilindri) :id{ id }, denumire{ denumire }, tip{ tip }, cilindri{ cilindri } {}
	//constructor primeste int id,string denumire tip si int cilindri
	int get_id()const { return id; }
	//metoda getter id int
	string get_denumire()const { return denumire; }
	//metoda getter returbeaza denumire string
	string get_tip()const { return tip; }
	//metoda getter returbeaza tip string
	int get_cilindri()const { return cilindri;}
	//metoda getter returneaza cilindri int 
	//seteaza un obiect la alt obiect
	Utilaj& operator=(const Utilaj& other) {
		if (this != &other) {
			id = other.id;
			denumire = other.denumire;
			tip = other.tip;
			cilindri = other.cilindri;
		}
		return *this;
	}
};