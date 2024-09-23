#pragma once
#include"repo.h"
class ValException {
private:
	string msg;
public:ValException(string msg) :msg{ msg } {}
	  //constrctor primeste string mesaj
	  string get_mesaj() { return msg; }
	  //retruneaza mesajul de eroare
};
class Validator {
private:
	Repo& repo;
public:
	Validator(Repo& repo) :repo{ repo } {};
	//constrctor validator primeste repo referinta
	void valideaza(const Tractor& t);
	//valideaza un Tractor si arunca exceptie daca nu respecta anumite cond
	void m_valideaza(const Tractor& t);
	//valideaza un Tractor si arunca exceptie daca nu respecta anumite cond pentr modifica
};