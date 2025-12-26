#include "service.h"

vector<PlacaDeBaza> Service::get_all_placi()
{
	return repo.get_all_placi();
}

vector<Procesor1> Service::get_all_procesoare()
{
	return repo.get_all_procesoare();
}

void Service::adauga(string nume, string soclu, int pret)
{
	PlacaDeBaza p(nume, soclu, pret);
	repo.adauga(p);
}
void Service::adauga_procesor(string nume, int tr, string soclu, int pret) {
	Procesor1 p{ nume,tr,soclu,pret };
	repo.adauga_procesor(p);
}

vector<PlacaDeBaza> Service::filtrare(string soclu)
{
	vector<PlacaDeBaza>v;
	for  (auto&placa:get_all_placi())
	{
		if (placa.get_soclu() == soclu)
			v.push_back(placa);
	}
	return v;
}

string Service::cauta(string text)
{
	return repo.cauta(text);
}
int Service::numar(string text)
{
	return repo.numar(text);
}
int Service::numar_2(string text)
{
	return repo.numar_2(text);
}
