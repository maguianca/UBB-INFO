#pragma once
#include"repo.h"
class Service {
private:
	Repo& repo;
public:
	Service(Repo& repo) :repo{ repo } {}
	vector<Razboi>get_all() { return repo.get_all(); };
	void sterge(int id);
};