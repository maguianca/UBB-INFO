#pragma once
#include<iostream>
using namespace std;
class Produs {
private:
	int id;
	string nume;
	string tip;
	double pret;
public:
	/// <summary>
	/// constrctor primeste
	/// </summary>
	/// <param name="id">int
	/// <param name="nume">string
	/// <param name="tip"><tip
	/// <param name="pret"><double>
	Produs(int id, const string& nume, const string& tip, double pret) :id{ id }, nume{ nume }, tip{ tip }, pret{ pret } {}
	/// <summary>
	/// getter returneaqza id int
	/// </summary>
	/// <returns></returns>
	int get_id()const { return id; };
	/// <summary>
	/// getter returneaqza nume string
	/// </summary>
	/// <returns></returns>
	string get_nume()const { return nume; };
	/// <summary>
	/// getter returneaqza tip string
	/// </summary>
	/// <returns></returns>
	string get_tip()const { return tip; };
	double get_pret()const { return pret; }

};