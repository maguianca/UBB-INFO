#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<exception>
#include"domeniu.h"
class Repo {
private:
	string fisier;
	string fisier_export;
	vector<Rezervare>oferte;
	void load_from_file();
	void write_to_file();
public:
	Repo(string& fisier, string& f) :fisier{ fisier }, fisier_export{ f } {
		load_from_file();
	};
	void adauga(Rezervare& r);
	vector<Rezervare>get_all() { return oferte; };
	void stergere(Rezervare& r);
	void discount(double p);
	void export_to_file(vector<Rezervare>v);

};