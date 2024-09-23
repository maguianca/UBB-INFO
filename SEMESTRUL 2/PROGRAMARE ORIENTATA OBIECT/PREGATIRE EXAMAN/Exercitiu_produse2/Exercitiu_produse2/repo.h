#pragma once
#include"domeniu.h"
#include<fstream>
#include<sstream>
#include<iostream>
#include<vector>
#include<string.h>
class Repo {
private:
	string fisier;
	void load_data_from_file();
	void write_to_file();
	vector<Produs>produse;
public:
	Repo(string fisier) :fisier{ fisier } {
		load_data_from_file();
	}
	void adauga(const Produs& p);
	vector < Produs>get_all() { return produse; }
	void sterge(const int id);
};