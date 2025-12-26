#pragma once
#include<iostream>
using namespace std;
class elev {
private:
	int matricol;
	int clasa;
	float medie;
	string nume;
	string prenume;
public:
	//contructor
	elev(int matricol, string nume, string prenume, int clasa, float medie) :matricol{ matricol }, nume{ nume }, prenume{ prenume }, clasa{ clasa }, medie{ medie } {}
	int get_matricol()const { return matricol; }//returneaza nr matricol
	int get_clasa()const { return clasa; }//returneaza clasa
	float get_medie()const { return medie; }//returneaza float medie
	string get_nume()const { return nume; }//returneaza numele 
	string get_prenume()const{ return prenume; }//returneaza prenumele
	bool operator==(elev& x)
	{
		return matricol == x.get_matricol();
	}//operator de egalitate
};