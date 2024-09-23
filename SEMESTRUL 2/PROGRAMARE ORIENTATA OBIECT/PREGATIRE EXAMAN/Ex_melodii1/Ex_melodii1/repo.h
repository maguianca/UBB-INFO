#pragma once
#include"domeniu.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
class Repo {
private:
	string fisier;
	void load_from_file();
	//citeste datele din fisier
	void write_to_file();
	//supracsrie fisierul
	vector<Melodie>melodii;
public:Repo(const string fisier) :fisier{ fisier } {
	load_from_file();}
	  //constrctor repo primeste fisier string si apeleaza metoda de citire din fisier
	  vector<Melodie>get_all() { return melodii; }
	  //returneaza vectorul de melodii
	  void adauga(const Melodie& m);
	  //adauga o melodie in fisier
	  void sterge(int id);
	  //strege dupa id se reflecta in fisier
	  void modifica(const Melodie& m);
	  //modifica o melodie dupa id si reflecta in fisier
	  Melodie cauta(int id);
};