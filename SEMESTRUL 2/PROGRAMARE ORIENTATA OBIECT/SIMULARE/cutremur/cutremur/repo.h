#pragma once
#include"domeniu.h"
#include<iostream>
#include<vector>
#include<fstream>
#include<exception>
#include<string>
#include<sstream>
using namespace std;
class Repo {
private:
	vector<Cutremur>cutremure;
	string file;
	void load_from_file();
public:
	Repo(string& file) :file{ file } {
		load_from_file();
	}
	vector<Cutremur>get_all() { return cutremure; }
	void adaugare(Cutremur& cutremur);
};