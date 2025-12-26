#pragma once
#include<iostream>
#include<vector>
#include"repo.h"
using namespace std;
class Service {
private:
	Repo& repo;
public:
	Service(Repo& repo) :repo{ repo } {};
	//constructor service
	vector<Elev>sortare();
	//returneaza un vector sortat;
	vector<Elev>get_all() { return repo.get_all(); }
	//returneaza vectorul de elevi apeland repo
};