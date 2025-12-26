#pragma once
#include"repo.h"
#include"domeniu.h"
#include<vector>
using namespace std;
class Service {
	Repo& repo;
public:
	Service(Repo& repo) :repo{ repo } {};
	Service() = default;
	void adauga(string destinatie, string perioada, double pret, double avans);
	vector<Rezervare>get_all() { return repo.get_all(); };
	void stergere(string destinatie, string perioada, double pret, double avans);
	void discount(double p);
	vector<Rezervare>random(int p);
	void export_to_file(vector<Rezervare>v);
	vector<Rezervare>sortare_crescator();
	vector<Rezervare>sortare_descrescator();
};
bool crescator(Rezervare& a, Rezervare& b);
bool descrescator(Rezervare& a, Rezervare& b);