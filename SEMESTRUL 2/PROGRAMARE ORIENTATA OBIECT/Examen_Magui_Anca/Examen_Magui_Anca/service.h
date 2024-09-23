#pragma once
#include"repo.h"
class Service {
private:
	Repo& repo;
public:
	Service(Repo& repo) :repo{ repo } {};\
	//constructor service primeste referinta repo
	vector<Utilaj>get_all() { return repo.get_all(); };
	//returneaza vectorul de utilaje apeland repo
	vector<Utilaj>sortare();
	//sorteaza vectorul dupa tipuri daca sunt egale atunci dupa denumire
	void sterge(int id);
	//sterge dupa id int 
	void modifica(int id,string denumire,string tip,int cilindri);
	//modifica un element
	int tip(string text);
	//returneaza numarul de Utilaje care au tip egal cu string text
	int nr_cilindri(int x);
	//returneaza cati cilindri de tipul x exista 
};