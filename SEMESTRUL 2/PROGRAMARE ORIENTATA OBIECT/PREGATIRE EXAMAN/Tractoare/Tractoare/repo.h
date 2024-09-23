#pragma once
#include"domeniu.h"
#include<vector>
#include<sstream>
#include<fstream>
#include<string.h>
class Repo {
private:
	string fisier;
	vector<Tractor>tractoare;
	void load_from_file();
	//citeste datele din fisier si le introduce in vector
	void write_to_file();
	//suprascrie fisierul iterand obiectele din vector
public:
	Repo(const string& fisier) :fisier{ fisier } {
		load_from_file();
	}
	void adauga(const Tractor& t);
	//adauga un obiect tractor daca are id unic
	vector<Tractor>get_all()const {
		return tractoare;
	}
	void sterge(int id);
	//returneaza vectorul de tractoare
	void modifica(Tractor& t);
};