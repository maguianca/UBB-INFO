#include "service.h"
#include<map>
#include"observer.h"
vector<Produs> Service::sorteaza()
{
	vector<Produs>rez{ repo.get_all() };
	sort(rez.begin(), rez.end(), [&](const Produs& o1, const Produs& o2) {return o1.get_pret() < o2.get_pret(); });
	return rez;
}

void Service::adauga(int id, const string& nume, const string& tip, double pret)
{
	Produs p{ id,nume,tip,pret };
	val.valideaza(p);
	repo.adauga(p);
	notify();
}

int Service::voc(const string& text)
{
	vector<char>r = { 'a','e','i','o','u','A','E','O','U','I'};
	int count = 0;
	int i = 0;
	for (auto& p : text) {
		for(int i=0;i<10;i++)
			if (p == r[i])
				count++;
	}
	return count;
}

map<string, int> Service::ret_tip()
{
	map<string, int>rez;
	for (const auto& p : repo.get_all())
	{
		if (rez.find(p.get_tip()) == rez.end())
			rez[p.get_tip()] = 1;
		else
			rez[p.get_tip()]++;
	}
	return rez;
}
