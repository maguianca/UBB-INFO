#pragma once
#include<string>
#include<functional>
#include"domeniu.h"
#include"repo.h"
#include"validator.h"
#include"CosOferte.h"
#include"Undo.h"
#include <unordered_map>
#include<vector>
#include<fstream>
#include<iostream>
//#include"vector.h"
using std::string;
using std::function;
using std::vector;
//typedef bool(*Sort)(const Turism&, const Turism&);
class Service
{
private:
	RepoAbstract& repo;
	Validator& validator;
	CosOferte& cos;
	vector<std::unique_ptr<ActiuneUndo >> undoActions;
public:
	//Constructor Service
	Service(RepoAbstract& repo, Validator& validator, CosOferte& cos) :repo{ repo }, validator{ validator }, cos{ cos }
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
	void modifica(const string& denumire, const string& destinatie, const string& tip, const double pret, const string& tip_nou, const double pret_nou);
	/* modifica un element care are denumire si destinatia din parametrii si modifica parametrii tip si pret cu tip_nou si pret_nou
	param:const string& denumire, const string& destinatie, const string& tip, const  double pret
	return none*/
	void cautare(const string& denumire, const string& destinatie, const string& tip, const  double pret);
	/*cauta un element care are toti cei patru parametri
	param:const string& denumire, const string& destinatie, const string& tip, const  double pret
	return none*/
	vector<Turism> filtrare_destinatie(const string& destinatie);
	/*returneaza o lista filtrata dupa destinatie
	param:const string& denumire, const string& destinatie, const string& tip, const  double pret
	return none*/
	vector<Turism> filtrare_pret(const double pret);
	/* returneaza o lista filtrata dupa pret
	param:const string& denumire, const string& destinatie, const string& tip, const  double pret
	return vector*/
	vector<Turism>sortare_destinatie();
	/* returneaza o lista sortata dupa o functie
	param:const string& denumire, const string& destinatie, const string& tip, const  double pret
	return vector*/
	vector<Turism>sortare_denumire();
	/* returneaza o lista sortata dupa o functie
	param:const string& denumire, const string& destinatie, const string& tip, const  double pret
	return vector*/
	vector<Turism>sortare_tip_pret();
	/* returneaza o lista sortata dupa o functie
	param:const string& denumire, const string& destinatie, const string& tip, const  double pret
	return vector*/
	const vector<Turism>& get_all() const
	{
		//returneaza referinta la vectorul vacante
		return repo.get_all();
	}
	void cosAdauga(const string& denumire, const string& destinatie, const string& tip, const double pret);

	/*
	 * Adauga un numar de oferte random in cos
	 * param nr: numarul de oferte random ce se adauga
	 * return: numarul de oferte random ce au fost adaugate
	 */
	int cosAdaugaRandom(int nr);

	/*
	 * Returneaza toate ofertele din cos
	 */
	const vector<Turism>& getAllCos()const;

	/*
	 * Goleste toate ofertele din cos
	 */
	void cosSterge();
	/*afiseaza un raport ce indicata destinatiile si numar de oferte aferente
	returneaza un map
	*/
	std::unordered_map<string, int> raport();
	void undo();
	void cosExport(const string& fileName);
	CosOferte& getCos() {
		return cos;
	}
};
bool sort_denumire(const Turism& o1, const Turism& o2);
bool sort_destinatie(const Turism& o1, const Turism& o2);
bool sort_tip_pret(const Turism& o1, const Turism& o2);