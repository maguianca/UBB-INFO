#pragma once
#include"repo.h"
#include"validator.h"
#include<algorithm>
class Service {
private:
	Repo& repo;
public:
	Service(Repo& repo) :repo{ repo } {}
	//constrctor service primeste referinta la repo
	vector<Melodie>get_all() { return repo.get_all(); }
	//returneaza veftorul de melodii
	void adauga(string titlu, string artist, string gen);
	//adauga un element dupa id,titlu,artist gen
	vector<Melodie>sorteaza();
	//sorteaza vectorul de melodii dupa autor
	int artist(string artist);
	//returneaza cate melodii cu artist -string exista
	int gen(string gen);
	//returneaza cate melodii cu gen -string exista
	int ret_id();
	//returneaza un id inexistent
	void sterge(int id);
	//strege un obiect dupa id
};