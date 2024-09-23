#include "service.h"
#include<algorithm>
vector<Tractor> Service::sorteaza()
{
	vector<Tractor>rez{ repo.get_all() };
	sort(rez.begin(), rez.end(), [](const Tractor& t1, const Tractor& t2) {return t1.get_denumire() < t2.get_denumire(); });
	return rez;
}

void Service::adauga(int id, string denumire, string tip, int nr)
{
	Tractor t{ id,denumire,tip,nr };
	val.valideaza(t);
	repo.adauga(t);
}

int Service::numar(string tip)
{
	int count = 0;
	for (const auto& l : repo.get_all()) {
		if (l.get_tip() == tip)
			count++;
	}
	return count;
}

map<string, int> Service::tipuri()
{
	map<string, int>rez;
	for (const auto& l : repo.get_all()) {
		string t = l.get_tip();
		if (rez.find(t) == rez.end()) {
			rez[t] = 1;
		}
		else
			rez[t]++;
	}
	return rez;
}

void Service::modifica(int id, string denumire, string tip, int nr)
{
	Tractor t{ id,denumire,tip,nr };
	val.m_valideaza(t);
	repo.modifica(t);
}
