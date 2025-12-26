#include "service.h"
#include<algorithm>
#include<random>
void Service::adauga(string destinatie, string perioada, double pret, double avans)
{
	Rezervare r{ destinatie,perioada,pret,avans };
	return repo.adauga(r);
}

void Service::stergere(string destinatie, string perioada, double pret, double avans)
{
	Rezervare r{ destinatie,perioada,pret,avans };
	return repo.stergere(r);
}

void Service::discount(double p)
{
	return repo.discount(p);
}
void Service::export_to_file(vector<Rezervare>v)
{
	return repo.export_to_file(v);
}
vector<Rezervare> Service::sortare_crescator()
{
	vector<Rezervare>v{ repo.get_all() };
    sort(v.begin(), v.end(), crescator);
	return v;
}
vector<Rezervare> Service::sortare_descrescator()
{
	vector<Rezervare>v{ repo.get_all() };
	sort(v.begin(), v.end(), descrescator);
	return v;
}
bool crescator(Rezervare& a, Rezervare& b) {
	return a.get_pret() < b.get_pret();
}
bool descrescator(Rezervare& a, Rezervare& b) {
	return a.get_pret() > b.get_pret();
}
vector<Rezervare> Service::random(int p)
{
	vector<Rezervare>v;
	for (int i = 0; i < p; i++)
	{
		vector<Rezervare>vrepo = repo.get_all();
	   shuffle(vrepo.begin(), vrepo.end(), std::default_random_engine(std::random_device{}()));
	   if (v.size() < p && !vrepo.empty()) {
		   v.push_back(vrepo.back());
		   vrepo.pop_back();
	   }
	}
	return v;
}
