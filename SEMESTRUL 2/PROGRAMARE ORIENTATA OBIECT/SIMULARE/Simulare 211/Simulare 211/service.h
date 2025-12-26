#pragma once
#include"repo.h"
#include<vector>
#include<algorithm>
using namespace std;
class Service {
private:
	Repo& repo;
public:
	Service(Repo& repo) :repo{ repo } {}
	//constructor al clasei service primeste atribut repo
	vector<Rochie>get_all() { return repo.get_all(); }
	//metoda care apeleaza metoda get_all() din repo returneaza vectorul de rochii
	vector<Rochie>sorteaza_marime();
	//metoda carec sorteaza vectorul de rochii si il returneaza dupa atributul marime
	vector<Rochie>sorteaza_pret();
	//metoda carec sorteaza vectorul de rochii si il returneaza dupa atributul pret
	Rochie& cautare_rochie(int id) { return repo.cautare_rochie(id); }//metoda care apleaza cautare rochie din repo
	void seteaza(Rochie& r,const string& text);
	void stergere(int id) { return repo.stergere(id); };
	vector<Rochie>filtreaza();
};