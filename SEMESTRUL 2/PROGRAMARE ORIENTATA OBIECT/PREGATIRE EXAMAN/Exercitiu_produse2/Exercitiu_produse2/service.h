#pragma once
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
	vector<Produs>get_all() { return repo.get_all(); }
	vector<Produs>sortare();
	void adaugare(int id, string nume, string tip, double pret);
	int nr_voc(string text);
	map<string, int>tipuri();
};