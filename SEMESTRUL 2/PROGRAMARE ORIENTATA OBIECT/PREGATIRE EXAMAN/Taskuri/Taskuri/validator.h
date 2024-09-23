#pragma once
#include"repo.h"
#include<iostream>
class ValException {
private:
	string msg;
public:
	ValException(const string& msg) :msg{ msg } {};
	string get_mesaj()const { return msg; }
};
//clasa de exceptii contine metoda get_mesaj care returneaza mesaj-string
class Validator {
private:
	Repo& repo;
public:
	Validator(Repo& repo) :repo{ repo } {};
	//constructor primeste referinta repo
	void valideaza(Task& t);
	void valideaza_stare(string text);
	//valideaza un obiect dupa campurile sale 
};
