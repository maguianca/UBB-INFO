#pragma once
#include"repo.h"
#include"validator.h"
#include<algorithm>
#include<functional>
#include<vector>
#include<map>
using namespace std;
class Service {
private:
	Repo& repo;
	Validator& validator;
public:
	Service(Repo& repo, Validator& validator) :repo{ repo }, validator{ validator } {};
	//constructor repo si validfator
	void adauga(int id, const string& denumire, const string& tip, int nr);
	//adauga un element prin apelare repo si il valideaza mai intai
	vector<Tractor>get_all() { return repo.get_all(); }
	//returneaza vcetorul de tractoare
	vector<Tractor>filtrare(const string& tip);
	int tip(const string& tip);
	vector<Tractor>sortare_denumire();
	map<string, int>returneaza_tip();
	void modifica(int id, const string& denumire, const string& tip, int nr);
};