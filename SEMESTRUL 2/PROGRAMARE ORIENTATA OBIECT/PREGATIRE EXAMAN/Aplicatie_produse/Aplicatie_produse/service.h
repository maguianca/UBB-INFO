#pragma once
#include<algorithm>
#include"repo.h"
#include"validator.h"
#include"observer.h"
#include<map>
class Service:public Observable {
private:
	Repo& repo;
	Validator& val;
public:
	Service(Repo& repo, Validator& val) :repo{ repo }, val{ val } {};
	//constructor repo si valudator
	vector<Produs>get_all()const { return repo.get_all(); }
	//returneaza vect de produse
	vector<Produs>sorteaza();
	void adauga(int id, const string& nume, const string& tip, double pret);
	int voc(const string& text);
	map<string, int>ret_tip();
};

