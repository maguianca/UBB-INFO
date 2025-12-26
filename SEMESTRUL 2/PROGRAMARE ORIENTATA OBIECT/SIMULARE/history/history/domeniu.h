#pragma once
#include<iostream>
#include<string.h>
using namespace std;
class Razboi {
private:
	int id;
	string nume;
	string descriere;
	string start;
	string end;
public:
	Razboi(int id, string nume, string descriere, string start, string end) :id{ id }, nume{ nume }, descriere{ descriere }, start{ start }, end{ end } {}
	int get_id()const { return id; }
	string get_nume()const { return nume; }
	string get_descriere()const { return descriere; }
	string get_start()const { return start; }
	string get_end()const { return end; }

};