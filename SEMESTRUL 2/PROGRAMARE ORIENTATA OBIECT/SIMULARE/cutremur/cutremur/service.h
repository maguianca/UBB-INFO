#pragma once
#include<iostream>
#include<vector>
#include<set>
#include"repo.h"
#include "validator.h"
class Service {
	Repo& repo;
	Validator& val;
public:
	Service(Repo& repo, Validator& val) :repo{ repo }, val{ val } {}
	vector<Cutremur>get_all();
	void adaugare(string locatie, string data, int intensitate, int adancime);
	vector<Cutremur> filtrare(string locatie, int intensitate);
	set<string>get_locatii();
};