#pragma once
#include"domeniu.h"
#include<string>
#include<vector>
#include<exception>
using namespace std;
class Repo {
private:
	vector<Apartament>apartamente;
	string fisier;
	void load_from_file();
	void write_to_file();
public:
	Repo(string fisier) :fisier{ fisier } {
		load_from_file();
	}
	void adauga(const Apartament& ap);
	void sterge(const Apartament& ap);
	vector<Apartament>get_all() {
		return apartamente;
	}
	string cauta_strada(string text);
	int cauta_pret(string text);
	int cauta_suprafata(string text);
};