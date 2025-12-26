#include "service.h"

vector<Apartament> Service::get_all()
{
	return repo.get_all();
}

vector<Apartament> Service::filtreaza_suprafete(int a, int b)
{
	vector<Apartament>v;
	for (auto& ap : get_all())
	{
		if (ap.get_suprafata() >= a && ap.get_suprafata() <= b)
			v.push_back(ap);
	}
	return v;
}

vector<Apartament> Service::filtreaza_pret(int a, int b)
{
	vector<Apartament>v;
	for (auto& ap : get_all())
	{
		if (ap.get_pret() >= a && ap.get_pret() <= b)
			v.push_back(ap);
	}
	return v;
}

void Service::sterge(int suprafata, string strada, int pret)
{
	Apartament a{ suprafata,strada,pret };
	return repo.sterge(a);
}

string Service::cauta_strada(string text)
{
	return repo.cauta_strada(text);
}

int Service::cauta_pret(string text)
{
	return repo.cauta_pret(text);
}

int Service::cauta_suprafata(string text)
{
	return repo.cauta_suprafata(text);
}
