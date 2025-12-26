#pragma once
#include<iostream>
#include<sstream>
#include<fstream>
#include"domeniu.h"
#include<vector>
#include<exception>
#include<string>
using namespace std;
class Repo {
private:
	string file;
	vector<Persoana>angajati;
	void load_from_file();
	void write_to_file();
public:
	Repo(string& file) :file{ file } {
		load_from_file();
	};
	vector<Persoana>get_all() {
		return angajati;
	}
	bool modificare(Persoana& p);
	void adauga(Persoana& p);
	Persoana cauta(int id);
};