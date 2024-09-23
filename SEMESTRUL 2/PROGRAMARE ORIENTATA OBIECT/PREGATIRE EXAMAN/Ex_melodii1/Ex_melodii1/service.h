#pragma once
#include"repo.h"
#include"validator.h"
#include<algorithm>
#include"undo.h"
#include<functional>
class Service {
private:
	Repo& repo;
	Validator& val;
	std::vector<std::unique_ptr<UndoA>>l_undo;
public:
	Service(Repo& repo, Validator& val) :repo{ repo }, val{ val } {}
	//constrctor service primeste repo si validator
	vector<Melodie>get_all() { return repo.get_all(); }
	//returneaza vectorul de melodii
	vector<Melodie>sorteaza();
	//vector sortat dupa rank
	void modifica(int id, string titlu, string artist, int rank);
	//modifica o melodie in fisier
	void sterge(int id);
	//strege o melodie dupa id;
	int rank(int r);
	//returneaza bnr de melodii care au ranku; egal cu r
	int artist(string artist);
	//returneaza cate melodii are artistul string
	void undo();
};