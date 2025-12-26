#include "service.h"

 bool Service::modificare(string nume, string job, string status, int id)
{
	Persoana p{ nume,job,status,id };
	return repo.modificare(p);
}

vector<Persoana> Service::filtrare(string nume)
{
	vector<Persoana>v;
	for (auto& l : repo.get_all())
	{
		if (l.get_nume() == nume)
			v.push_back(l);
	}
	return v;
}

Persoana Service::cauta(int id)
{
	return repo.cauta(id);
}
