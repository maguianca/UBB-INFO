#pragma once
#include<vector>
#include"domeniu.h"
using std::vector;
class RepoException {
	string msg;
public:
	RepoException(string m) :msg{ m } {
		
	}
	string get_mesaj() {
		return msg;
	}

};
class Repo
{
private:
	vector<Turism>vacante;
public:
	Repo(const Repo& ot) = delete;
	Repo() = default;
	void store(const Turism& oferta);
	/*
	* stocheaza un obiect Turism in lista de vacante
	* return:none
	*/
	void stergere(Turism& oferta);
	/*
		sterge un obiect de tip turism din lista de vacante 
	*/
	const Turism& cauta(const string& denumire, const string& destinatie, const string& tip, const double pret) const;
	/*
	* cauta un obuiect de tip turism in lista de oferte si returneaza elementul
	*/
	void modifica(const Turism& o);
	/* 
	modifica un element de tip turim cu parametrii tip si pret din obiectul transmis prin parametru*/
	const vector<Turism>& get_all()
	{
		//returneaza lista totala de obiecte
		return vacante;
	}
};