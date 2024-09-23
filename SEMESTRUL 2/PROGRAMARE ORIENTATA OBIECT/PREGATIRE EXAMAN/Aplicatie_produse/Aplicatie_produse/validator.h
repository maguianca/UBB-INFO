#pragma once
#include"repo.h"
class ValException {
private:string msg;
public:ValException(const string& msg) :msg{ msg } {};
	  string get_mesaj() { return msg; }
};
class Validator {
private:
	Repo& repo;
public:
	Validator(Repo& repo) :repo{ repo } {};
	//constructor primeste repo
	void valideaza(const Produs& p);
	//valideaza un obiect de tipnprodus dupa id,nume,tip,pret
};