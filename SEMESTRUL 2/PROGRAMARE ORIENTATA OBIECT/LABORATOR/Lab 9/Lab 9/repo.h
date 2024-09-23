#pragma once
#pragma once
#pragma once
#include<vector>
#include<unordered_map>
#include"domeniu.h"
//#include"vector.h"
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
	//Constructor Repo
	Repo(const Repo& ot) = delete;
	Repo() = default;
	virtual void store(const Turism& oferta);
	/*
	* stocheaza un obiect Turism in lista de vacante
	* return:none
	*/
	virtual void stergere(const Turism& oferta);
	/*
		sterge un obiect de tip turism din lista de vacante
	*/
	const Turism& cauta(const Turism& o);
	/*
	* cauta un obuiect de tip turism in lista de oferte si returneaza elementul
	*/
	void modifica(const Turism& o);
	/*
	modifica un element de tip turim cu parametrii tip si pret din obiectul transmis prin parametru*/
	const vector<Turism>& get_all()const
	{
		//returneaza lista totala de obiecte
		return vacante;
	}
	bool exist(const Turism& o);
};
class RepoFile :public Repo {
private:
	string fileName;
	void load_from_file();
	void write_to_file();
public:
	explicit RepoFile(string fileName) :Repo(), fileName{ fileName } {
		load_from_file();
	}
	void store(const Turism& oferta) override
	{
		Repo::store(oferta);
		write_to_file();
	}
	void stergere(const Turism& oferta)override 
	{
		Repo::stergere(oferta);
		write_to_file();
	}
};