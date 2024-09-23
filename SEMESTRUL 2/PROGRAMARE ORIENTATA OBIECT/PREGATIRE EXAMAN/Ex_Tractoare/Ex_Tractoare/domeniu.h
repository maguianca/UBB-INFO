#pragma once
#include<iostream>
using namespace std;
class Tractor {
private:
	int id;
	string denumire;
	string tip;
	int numarRoti;
public:Tractor(const int id, const string denumire, const string tip, const int numar) :id{ id }, denumire{ denumire },
	tip{ tip }, numarRoti{ numar } {};
	  //constrctor primeste id int string denumire tip string numar int
	  int get_id()const { return id; }
	  //metoda returneaza id int
	  string get_tip()const { return tip; }
	  //metoda returneaza tip
	  string get_denumire()const { return denumire; }
	  //metoda returneaza denumire
	  int get_numar()const { return numarRoti; }
	  //metoda returneaza id int
	  Tractor& operator=(const Tractor&t) {
		  if (this != &t)
		  {
			  id = t.id;
			  denumire = t.denumire;
			  tip = t.tip;
			  numarRoti = t.numarRoti;
		  }
		  return *this;
	  }
};
