#pragma once
#include<iostream>
#include<vector>
#include<string.h>
using namespace std;
class Task {
private:
	int id;
	string descriere;
	vector<string>programatori;
	string stare;
public:
	Task(const int& id, const string& descriere, const vector<string>programatori, const string& stare) :
		id{ id }, descriere{ descriere }, programatori{ programatori }, stare{ stare } {};
	//constructor id-int,string descriere, vector<int>programatori,string stare
	int get_id() const{ return id; }//returneaza id-int 
	string get_stare()const { return stare; }//returneaza stare-string
	string get_descriere()const { return descriere; }//returneaza descriere
	vector<string>get_programatori()const { return programatori; }//returneaza programatori
	//concateneaza vectorul de programatori intr un string rez sring
	string get_programatori_string()const {
		string rez = "";
		for (int i = 0; i < programatori.size();i++) {
			rez += programatori[i];
			if(i!=programatori.size()-1)
				rez += " ";
		}
		return rez;
	}
	void set_stare(const string& ex) {
		stare = ex;
	}//setter seteaza stare la ex-string
};