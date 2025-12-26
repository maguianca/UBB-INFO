#pragma once
#include"repo.h"
#include<vector>
using namespace std;
class Service {
	Repo& repo;
public:
	Service(Repo& r) :repo{ r } {}
	vector<Apartament>get_all();
	vector<Apartament>filtreaza_suprafete(int a, int b);
	vector<Apartament>filtreaza_pret(int a, int b);
	void sterge(int suprafata, string strada, int pret);
	string cauta_strada(string text);
	int cauta_pret(string text);
	int cauta_suprafata(string text);
};