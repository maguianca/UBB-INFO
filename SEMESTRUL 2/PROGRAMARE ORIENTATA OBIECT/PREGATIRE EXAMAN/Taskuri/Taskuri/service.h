#pragma once
#include<iostream>
#include"validator.h"
#include"repo.h"
#include<algorithm>
#include"observer.h"
class Service:public Observable {
private:
	Repo& repo;
	Validator& val;
public:
	Service(Repo& repo,Validator&val) :repo{ repo }, val{ val } {};
	//constructor apeleaza service
	vector<Task>get_all() { return repo.get_all(); }
	//returneaza vectrorul de taskuri apland repo
	vector<Task>sorteaza();
	//returneaza vectorul sortat dupa stare
	void adauga(int id, string denumire, vector<string>programatori, string stare);
	//adauga un element in vector si in valideaza
	vector<Task>filtrare(const string text);
	//filtreaza vectorul de taskuri daca are in programator field text-string
	vector<Task>stare(const string text);
	//returneaza vacetorul filtrat cu stare text
	void modifica(const int id, const string stare);
	//modifica un element dupa id-int schimband atributul stare cu string-stare
};