#pragma once
#include"repo.h"
#include"validator.h"
#include<map>
class Service {
private:
	Repo& repo;
	Validator& val;
public:Service(Repo& repo, Validator& val) :repo{ repo }, val{ val } {};
	  //constrctor service primeste ca referinte repo si validator
	  vector<Tractor>get_all() { return repo.get_all(); };
	  //returneaza vectorul de tractoare
	  vector<Tractor>sorteaza();
	  //vector sortat dupa denumire
	  void adauga(int id, string denumire, string tip, int nr);
	  //adauga un tractor in vectorul de tractoare
	  int numar(string tip);
	  //returneaza numaurl de tract cu acelasi tip
	  map<string, int>tipuri();
	  //returneaza un dictionar cu tipuri de tractaorele si numar de tractoare aferente
	  void modifica(int id, string denumire, string tip, int nr);
	  //modifica un tractor

};