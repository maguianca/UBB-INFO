#pragma once
#include"domeniu.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<fstream>
#include<string.h>
#include<vector>
class Repo {
private:
	string fisier;
	void load_from_file();
	//scrie datele din fisier
	void write_to_file();
	//suprascrie fisierul
	vector<Tractor>tractoare;
public:Repo(const string fisier) :fisier{ fisier } {
	load_from_file();
}
	  void adauga(const Tractor& t);
	  //adauga un tractor in vectorul de trcatoare si suprascrie fisierul
	  void sterge(int id);
	  //se sterge dupa id daca id existent se reflecta in fisier
	  vector<Tractor>get_all() { return tractoare; }
	  //returneaza vectorul de tractoare-vector
	  void modifica(const Tractor& t);
	  //modifica un tractor t
};