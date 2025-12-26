#pragma once
#include<iostream>
#include<string>
using std::string;
class Apartament {
private:
	int suprafata;
	string strada;
	int pret;
public:
	Apartament(int suprafata,string strada,int numar):suprafata{suprafata},strada{strada},pret{numar}{}
	int get_pret() const{
		return pret;
	}
	int get_suprafata()const {
		return suprafata;
	}
	string get_strada()const {
		return strada;
	}
};