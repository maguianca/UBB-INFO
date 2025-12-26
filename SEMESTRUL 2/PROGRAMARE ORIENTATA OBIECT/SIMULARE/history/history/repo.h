#pragma once
#include"domeniu.h"
#include<iostream>
#include<sstream>
#include<fstream>
#include"string.h"
#include<vector>
class Repo {
private:
	string fisier;
	void load_from_file();
	void write_to_file();
	vector<Razboi>razboaie;
public:
	Repo(const string& fisier) :fisier{ fisier }{
		load_from_file();
	};
	void adauga(Razboi& r);
	vector<Razboi>get_all() { return razboaie; };
	void stergere(int id);

};