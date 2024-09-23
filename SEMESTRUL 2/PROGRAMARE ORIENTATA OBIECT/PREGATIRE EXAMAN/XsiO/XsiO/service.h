#pragma once
#include "rep.h"
#include "validator.h"
#include<algorithm>
#include"observer.h"
class Service:public Observable {
private:
	Repo& repo;
	Validator& val;
public:
	Service(Repo& repo, Validator& val) :repo{ repo }, val{ val } {};
	void adauga(const int id, const int dim, string& joc, string& jucator,const  string& stare);
	void modifica(const int id, const int dim,  string& joc,  string& jucator,const string& stare);
	vector<Joc>sorteaza();
	void mod(int& id, string& joc, string& jucator);
	vector<Joc>get_all() { return repo.get_all(); }
};