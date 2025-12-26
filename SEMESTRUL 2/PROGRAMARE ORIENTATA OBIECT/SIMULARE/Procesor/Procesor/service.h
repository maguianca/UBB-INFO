#pragma once
#include "repo.h"
#include<iostream>
using namespace std;
class Service {
	Repo& repo;
public:
	Service(Repo&r):repo(r){}
	vector<PlacaDeBaza>get_all_placi();
	vector<Procesor1>get_all_procesoare();
	void adauga(string nume, string soclu, int pret);
    void adauga_procesor(string nume,int tr,string soclu,int pret);
	vector<PlacaDeBaza>filtrare(string soclu);
	string cauta(string text);
	int numar(string text);
	int numar_2(string text);
};