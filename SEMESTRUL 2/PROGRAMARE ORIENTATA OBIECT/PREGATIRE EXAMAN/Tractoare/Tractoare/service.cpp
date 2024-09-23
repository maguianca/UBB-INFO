#include "service.h"
void Service::adauga(int id, const string& denumire, const string& tip, int nr)
{
	Tractor t{ id,denumire,tip,nr };
	validator.valideaza(t);
	repo.adauga(t);
}

vector<Tractor> Service::filtrare(const string& tip)
{
	vector<Tractor>rez;
	vector<Tractor>r = repo.get_all();
	copy_if(r.begin(), r.end(), back_inserter(rez), [tip](const Tractor& t) {return t.get_tip() == tip; });
	return rez;
}

int Service::tip(const string& tip)
{
	map < string, int>rez;
	for (const auto& t : get_all()) {
		if (rez.find(t.get_tip()) == rez.end())
			rez[t.get_tip()] = 1;
		else
			rez[t.get_tip()]++;
	}
	return rez[tip];
}

vector<Tractor> Service::sortare_denumire()
{
	vector<Tractor>rez{ repo.get_all() };
	sort(rez.begin(), rez.end(), [&](const Tractor& o1, const Tractor& o2) {return o1.get_denumire() < o2.get_denumire(); });
	return rez;
}

map<string, int> Service::returneaza_tip()
{
	map < string, int>rez;
	for (const auto& t : get_all()) {
		if (rez.find(t.get_tip()) == rez.end())
			rez[t.get_tip()] = 1;
		else
			rez[t.get_tip()]++;
	}
	return rez;
}

void Service::modifica(int id, const string& denumire, const string& tip, int nr)
{
	Tractor t{ id,denumire,tip,nr };
	validator.valideaza_modifica(t);
	repo.modifica(t);
}
