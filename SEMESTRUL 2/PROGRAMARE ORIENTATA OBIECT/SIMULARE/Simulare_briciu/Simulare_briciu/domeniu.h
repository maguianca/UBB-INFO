#pragma once
#include<iostream>
#include<string>
using namespace std;
class Rezervare {
private:
	string destinatie, perioada;
	double pret, avans;
public:
	Rezervare(string destinatie, string perioada, double pret, double avans) :destinatie{ destinatie }, perioada{ perioada },
		pret{ pret }, avans{ avans } {};
	Rezervare() = default;
	double get_pret() { return pret; }
	double get_avans() { return avans; }
	string get_destinatie() { return destinatie; }
	string get_perioada() { return perioada; }
	bool operator==(Rezervare& r) {
		return (destinatie == r.get_destinatie() && perioada == r.get_perioada() && pret == r.get_pret() && avans == get_avans());
	}
	void reducere(int procent)
	{
		pret -= pret * procent / 100;
	}
};