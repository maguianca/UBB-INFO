#pragma once
#include<iostream>
#include<vector>
#include<string.h>
#include<fstream>
#include<sstream>
#include"domeniu.h"
class Repo {
private:
	string fisier;
	void load_from_file();
	//citeste din fisier 
	void write_to_file();
	//supracsrie fisierul
	vector<Task>taskuri;
public:
	Repo(const string& fisier) :fisier{ fisier } {
		load_from_file();
	}
	void adauga(const Task& t);
	//adauga un obiect in vector
	void modificare(const int& id, const string& stare);
	//modifica un obiect si reflecta in fisier
	vector<Task>get_all() { return taskuri; }
	//returneaza vectorul de taskuri
	void sterge(int id);
	//sterge un obiect dupa id
};