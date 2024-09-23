#pragma once
#include<vector>
#include<fstream>
#include<sstream>
#include<string>
#include"domeniu.h"
class Repo {
private:
	string fisier;
	vector<Produs>produse;
	void load_from_file();
	//citeste din fisier
	void write_to_file();
	//suprascrie in fisier
public:
	Repo(const string& fisier) :fisier{ fisier } {
		load_from_file();
	};
	//constructor fisier string
	void adauga(const Produs& p);
	//adauga iun produs daca id unic
	void sterge(const Produs& p);
	//strege un produs cu id daca il gaseste
	vector<Produs>get_all()const { return produse; }
	//returneaza vectorul de produse
};