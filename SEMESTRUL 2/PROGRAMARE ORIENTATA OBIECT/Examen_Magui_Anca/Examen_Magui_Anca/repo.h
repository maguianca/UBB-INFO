#pragma once
#include"domeniu.h"
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
using namespace std;
class Repo {
private:
	string fisier;
	void load_from_file();
	//citeste date din fisier
	void write_to_file();
	//suprascrie fisierul
	vector<Utilaj>utilaje;
public:
	Repo(const string fisier) :fisier{ fisier } {
		load_from_file();
	}
	//constructor repo primeste string fisier
	vector<Utilaj>get_all() { return utilaje; }
	//returneza vectorul de utilaje
	void adauga(const Utilaj& ob);
	//adauga un element in vector daca are id unic
	void sterge(int id);
	//sterge un element daca gaseste id
	void modifica(const Utilaj& ob);
	//modifica un element si suprascrie elementul
};