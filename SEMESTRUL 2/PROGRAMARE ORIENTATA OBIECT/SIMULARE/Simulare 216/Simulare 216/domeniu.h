#pragma once
#include<iostream>
using namespace std;
class Elev {
private:
	int matricol;
	string nume;
	string scoala;
	string atelier;
public:
	//constructor
	Elev(const int& matricol, const string& nume,const  string& scoala,const string& atelier) :matricol{ matricol }, nume{ nume }, scoala{ scoala }, atelier{ atelier } {}
	Elev() = default;
	//getter returneaza nume
	string get_nume()const { return nume; }
	//getter returneaza scoala
	string get_scoala()const { return scoala; }
	//getter returneaza atelier
	string get_atelier()const { return atelier; }
	//getter returneaza int nr matricol
	int get_matricol()const { return matricol; };
};