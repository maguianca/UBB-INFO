#pragma once
#include<iostream>
using namespace std;
class Cutremur {
private:
	string locatie;
	string data;
	int intensitate;
	int adancime;
public:
	Cutremur(string loc, string d, int intens, int adanc) :locatie{ loc }, data{ d }, intensitate{ intens }, adancime{ adanc } {}
	Cutremur() = default;
	string get_data() { return data; }
	string get_locatie() { return locatie; }
	int get_intensitate() { return intensitate; }
	int get_adancime() { return adancime; }
};