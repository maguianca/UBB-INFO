#pragma once
#include"domeniu.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<string.h>
#include<vector>
class Repo {
private:
	string fisier;
	void load_from_file();
	//citeste date din fisier
	void write_to_file();
	//scrie date in fisier
	vector<Melodie>melodii;
public:
	Repo(const string fisier) :fisier{ fisier } {
		load_from_file();
	}
	//constrctor repo primeste string fisier si citeste datele din fisier
	void adauga(const Melodie& m);
	//adauga un element de tup meldoie in vectorul de elemente si scrie in fisier daca are id valid
	void sterge(const int id);
	//daca gaseste id sterge elementul de tip melodie si suprascrie fisierul
	vector<Melodie>get_all() { return melodii; }
	//returneaza vectorul de melodii
};