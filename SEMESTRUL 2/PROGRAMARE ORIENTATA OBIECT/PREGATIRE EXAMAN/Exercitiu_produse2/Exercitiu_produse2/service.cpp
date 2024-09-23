#include "service.h"
#include<algorithm>
#include<map>
vector<Produs> Service::sortare()
{
	vector<Produs>rez{ repo.get_all() };
	sort(rez.begin(), rez.end(), [](const Produs& p1, const Produs& p2) {return p1.get_pret() < p2.get_pret(); });
	return rez;
}

void Service::adaugare(int id, string nume, string tip, double pret)
{
	Produs p{ id,nume,tip,pret };
	val.validator(p);
	repo.adauga(p);
	notify();
}

int Service::nr_voc(string text)
{
	int count = 0;
	vector<char>voc{ 'a','e','i','o','u','A','E','I','O','U' };
	for (int i = 0; i < text.size(); i++)
		for (int j = 0; j < voc.size(); j++)
			if (text[i] == voc[j])
				count++;
	return count;
}

map<string, int> Service::tipuri()
{
	map<string, int>rez;
	for (const auto& l:repo.get_all()) {
		if (rez.find(l.get_tip()) == rez.end())
			rez[l.get_tip()] = 1;
		else
			rez[l.get_tip()]++;
	}
	return rez;
}
