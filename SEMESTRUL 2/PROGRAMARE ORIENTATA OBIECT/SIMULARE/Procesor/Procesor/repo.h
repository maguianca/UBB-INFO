#pragma once
#include<vector>
#include"domeniu.h"
#include<fstream>
#include<exception>
using namespace std;

class Repo {
private:
	vector<Procesor1>procesoare;
	vector<PlacaDeBaza>placi;
	string fisier1;
	string fisier2;
	void load_from_file_1();
	void load_from_file_2();
	void write_to_file_2();

public:
	Repo(string fisier1, string fisier2) :fisier1{ fisier1 },fisier2 { fisier2 } {
		load_from_file_1();
		load_from_file_2();
	}
	void adauga(const PlacaDeBaza& placa);
	void adauga_procesor(const Procesor1& p);
	vector<Procesor1> get_all_procesoare() {
		return procesoare;
	}
	vector<PlacaDeBaza>get_all_placi() {
		return placi;
	}
	string cauta(string text);
	int numar(string text);
	int numar_2(string text);
};