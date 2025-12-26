#pragma once
#include<iostream>
#include"repo.h"
#include<vector>
class Service {
	Repo& repo;
public:
	Service(Repo& repo) :repo{ repo } {};
	vector<Persoana>get_all() { return repo.get_all(); };
	bool modificare(string nume, string job, string status, int id);
	vector<Persoana>filtrare(string nume);
	Persoana cauta(int id);
};