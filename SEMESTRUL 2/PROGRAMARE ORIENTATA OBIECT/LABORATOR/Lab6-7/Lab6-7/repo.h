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
	void stergere(Turism& oferta);
	const Turism& cauta(const string& denumire, const string& destinatie,const string& tip, const double pret) const;
	const vector<Turism>& get_all()
	{
		return vacante;
	}
};