#pragma once
#include<iostream>
#include<string>
using namespace std;
class Tractor {
private:
	int id;
	string denumire;
	string tip;
	int nr;
public:
	Tractor(int id, const string& denumire,const string& tip, int nr) :id{ id }, denumire{ denumire }, tip{ tip }, nr{ nr } {};
	//constructor id,denumire,tip,nr
	int get_id()const { return id; }
	//metoda getter returneaza id int
	string get_denumire()const { return denumire; }
	//metoda getter returneaza denumire string
	string get_tip()const { return tip; }
	//metoda getter returneaza tip string
	int get_nr()const { return nr; }
	//metoda getter returneaza nr roti int
	bool operator==(const Tractor& t) { return t.get_id() == id; }
	Tractor& operator=(const Tractor&other)
	{
		id = other.id;
		denumire = other.denumire;
		tip = other.tip;
		nr = other.nr;
		return *this;
	}

};