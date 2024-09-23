#pragma once
#include<string>
#include<functional>
#include"domeniu.h"
#include"repo.h"
using std::string;
using std::function;
using std::vector;
typedef int(*Sort)(const Turism&, const Turism&);
class Service
{
private:
	Repo& repo;
	vector<Turism> filtrare(const function<bool(const Turism&)>& fct);
public:
	Service(Repo& repo) :repo{ repo }
	{

	}
	Service(const Service& ot) = delete;
	Service() = default;
	void adauga(const string& denumire,const string& destinatie, const string& tip,const  double pret);
	void stergere(const string& denumire,const string& destinatie,const  string& tip,const double pret);
	void modifica(const string& denumire,const string& destinatie,const string& tip,const double pret,const string& tip_nou, const double pret_nou);
	void cautare(const string& denumire, const string& destinatie, const string& tip, const  double pret);
	vector<Turism> filtrare_destinatie(const string& destinatie);
	vector<Turism> filtrare_pret(const double pret);
	vector<Turism>sortare(Sort functieSortare);
	const vector<Turism>&get_all()
	{
		return repo.get_all();
	}
};