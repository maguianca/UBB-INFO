#pragma once
#include"repo.h"
class ValException {
private:
	string msg;
public: ValException(string& msg) :msg{ msg } {};
	  string get_mesaj() { return msg; }
};
class Validator {
private:
	Repo& repo;
public:
	Validator(Repo& repo) :repo{ repo } {};
	void valideaza(const Tractor& t);
	void valideaza_modifica(const Tractor& t);
};