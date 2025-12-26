#pragma once
#include<iostream>
#include<algorithm>
#include"repo.h"
class Service {
private:
	Repo& repo;
public:
	Service(Repo& repo) :repo{ repo } {}
	//constructor
	vector<elev>sortare_clasa();//sorteaza elevi in fct de clasa
	vector<elev>sortare_medie();//sorteaza elevi in fct de medie
	vector<elev>sortare_nume();//sorteaza elevi in fct de nume
	vector<elev>get_all() { return repo.get_all(); }//returneaza vectorul de elevi din repo
	void stergere(int matricol);//sterge dupa numar matricol
	elev& cauta(string text);
};
bool s_nume(elev& a, elev& b);
bool s_medie(elev& a, elev& b);
bool s_clasa(elev& a, elev& b);