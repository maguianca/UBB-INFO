#pragma once
#include<domeniu.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string.h>
using namespace std;
class Repo {
private:
	string fisier;
	vector<Joc>jocuri;
	void load_from_file();
	void write_to_file();
public:
	Repo(const string& fisier) :fisier{ fisier } {
		load_from_file();
	};
	vector<Joc>get_all() { return jocuri; }
	void adauga(Joc& joc);
	void modifica( Joc& joc);
	void mod(int& id, string& joc, string& jucator);

};