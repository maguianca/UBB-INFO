#pragma once
#pragma once
#pragma once
#pragma once
#include<vector>
#include<unordered_map>
#include"domeniu.h"
#include<random>
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
class RepoAbstract {
public:
	RepoAbstract() = default;
	RepoAbstract(const RepoAbstract& o) = delete;
	virtual void store(const Turism& oferta) = 0;
	virtual void stergere(const Turism& oferta) = 0;
	virtual const Turism& cauta(const Turism& o) = 0;
	virtual const vector<Turism>& get_all() = 0;
	//virtual void modifica(const Turism& o) = 0;
};
class Repo : public RepoAbstract
{
private:
	vector<Turism>vacante;
public:
	//Constructor Repo
	Repo(const Repo& ot) = delete;
	Repo() = default;
	void store(const Turism& oferta)override;
	/*
	* stocheaza un obiect Turism in lista de vacante
	* return:none
	*/
	void stergere(const Turism& oferta)override;
	/*
		sterge un obiect de tip turism din lista de vacante
	*/
	const Turism& cauta(const Turism& o)override;
	/*
	* cauta un obuiect de tip turism in lista de oferte si returneaza elementul
	*/
	//void modifica(const Turism& o)override;
	/*
	modifica un element de tip turim cu parametrii tip si pret din obiectul transmis prin parametru*/
	const vector<Turism>& get_all()override
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
class RepoLab : public RepoAbstract {
private:
	bool exist(const Turism& o);
	std::unordered_map<int, Turism>oferte;
	double probabilitatea;
	void random()const;
	vector<Turism>toate_ofertele;
public:
	RepoLab() {
		std::mt19937 gen(123);
		std::uniform_real_distribution<double> dis(0.0, 1.0);
		probabilitatea = dis(gen);
	}
	void set_probabilitatea(double pr);
	RepoLab(const Turism& oferta) = delete;
	void store(const Turism& oferta)override;
	/*
	* stocheaza un obiect Turism in lista de vacante
	* return:none
	*/
	void stergere(const Turism& oferta)override;
	/*
		sterge un obiect de tip turism din lista de vacante
	*/
	const Turism& cauta(const Turism& o)override;
	/*
	* cauta un obuiect de tip turism in lista de oferte si returneaza elementul
	*/
	const vector<Turism>& get_all()override;
};