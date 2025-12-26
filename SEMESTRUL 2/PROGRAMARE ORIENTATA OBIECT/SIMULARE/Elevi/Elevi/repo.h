#pragma once
#include"domeniu.h"
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
using namespace std;
class Repo {
private:
	string fisier;
	vector<elev>elevi;
	void load_to_file();
	void write_to_file();//rescrie datele in fisier supracsrie
	//citeste datele din fisier si le adauga in vectorul de elevi
public:
	Repo(string& fisier) :fisier{ fisier } {
		load_to_file();
	}
	//constructor
	vector<elev>get_all() { return elevi; }//returneaza vectorul de elevi
	void adauga(elev& x);// adauga un elev x in vectorul de elevi
	void stergere(int x);
	elev& cauta(string text);
};