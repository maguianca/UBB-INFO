#include "service.h"
#include<algorithm>
vector<Cutremur> Service::get_all()
{
	return repo.get_all();
}

void Service::adaugare(string locatie, string data, int intensitate, int adancime)
{
	Cutremur c{ locatie,data,intensitate,adancime };
	val.valideaza(c);
	repo.adaugare(c);
}

vector<Cutremur> Service::filtrare(string locatie, int intensitate)
{
	vector<Cutremur>v;
	for (auto& c : repo.get_all())
	{
		if (locatie != "None") {
			if (c.get_locatie() == locatie && c.get_intensitate() <= intensitate)
				v.push_back(c);
		}
		else
				v.push_back(c);
	}
	return v;
}

set<string> Service::get_locatii()
{
	set<string>v;
	for (auto& c : repo.get_all())
	{
			v.insert(c.get_locatie());
	}
	return v;
}
