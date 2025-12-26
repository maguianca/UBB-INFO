#pragma once
#include"domeniu.h"
#include<vector>
#include<sstream>
#include<exception>
#include<fstream>
using namespace std;
class Repo {
private:
	string fisier;
	vector<Rochie>rochii;
	void load_from_file();
	void write_to_file();
public:
	//constructor al clasei Repo-atribute-string fisier
	Repo(string& fisier) :fisier{ fisier } {
		load_from_file();
	};
	//returneaza vectorul de rochii
	vector<Rochie>get_all() { return rochii; }
	//adauga un obiect de tip Rochie doar daca are id unic-apeleaza void cauta 
	void adauga(const Rochie& r);
	//metoda care cauta un obiect de tip Rochie dupa un id si returneaza 1 daca il gaseste si 0 alfel;
	int cauta(int id);
	Rochie& cautare_rochie(int id);
	//metoda care returneaza obiectul cu id int 
	void seteaza(Rochie& r,const string& text);
	void stergere(int id);
};