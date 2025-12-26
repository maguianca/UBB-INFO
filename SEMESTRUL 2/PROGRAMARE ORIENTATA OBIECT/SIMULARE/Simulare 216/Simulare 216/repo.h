#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<exception>
#include"domeniu.h"
using namespace std;
class Repo {
private:
	string fisier;
	vector<Elev>elevi;
	//citeste elevi din fisier si ii adauga in vector
	void load_from_file();
public:
	//constructor repo
	Repo(string& fisier) :fisier{ fisier } {
		load_from_file();
	};
	//returneaza vectorul de elevo
	vector<Elev>get_all() {
		return elevi;
	}
	//adauga in vector un elem de tip Elev
	void adauga(const Elev& e) {
		elevi.push_back(e);
	}
};