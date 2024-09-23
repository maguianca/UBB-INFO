#pragma once
#include<string>
#include<functional>
#include"domeniu.h"
#include"repo.h"
#include"validator.h"
//#include"vector.h"
using std::string;
using std::function;
//using std::vector;
typedef int(*Sort)(const Turism&, const Turism&);
class Service
{
private:
	Repo& repo;
	VectD<Turism> filtrare(const function<bool(const Turism&)>& fct);
	Validator& validator;
public:
	Service(Repo& repo,Validator & validator) :repo{ repo },validator {validator}
	{

	}
	Service(const Service& ot) = delete;
	Service() = default;
	void adauga(const string& denumire, const string& destinatie, const string& tip, const  double pret);
	/*
	adauga un element prin parametrii string denumire,destinatie,tip si double pret
	param:const string& denumire, const string& destinatie, const string& tip, const  double pret
	return none
	*/
	void stergere(const string& denumire, const string& destinatie, const  string& tip, const double pret);
	/* stergee un element care are toate cele 4 atribute denumire,destinatie,tip si pret
	param:const string& denumire, const string& destinatie, const string& tip, const  double pret
	return none*/
	void modifica(const string& denumire, const string& destinatie, const string& tip_nou, const double pret_nou);
	/* modifica un element care are denumire si destinatia din parametrii si modifica parametrii tip si pret cu tip_nou si pret_nou
	param:const string& denumire, const string& destinatie, const string& tip, const  double pret
	return none*/
	void cautare(const string& denumire, const string& destinatie, const string& tip, const  double pret);
	/*cauta un element care are toti cei patru parametri
	param:const string& denumire, const string& destinatie, const string& tip, const  double pret
	return none*/
	VectD<Turism> filtrare_destinatie(const string& destinatie);
	/*returneaza o lista filtrata dupa destinatie
	param:const string& denumire, const string& destinatie, const string& tip, const  double pret
	return none*/
	VectD<Turism> filtrare_pret(const double pret);
	/* returneaza o lista filtrata dupa pret
	param:const string& denumire, const string& destinatie, const string& tip, const  double pret
	return vector*/
	VectD<Turism>sortare(Sort functieSortare);
	/* returneaza o lista sortata dupa o functie
	param:const string& denumire, const string& destinatie, const string& tip, const  double pret
	return vector*/
	const VectD<Turism>& get_all()
	{
		//returneaza referinta la vectorul vacante
		return repo.get_all();
	}

};