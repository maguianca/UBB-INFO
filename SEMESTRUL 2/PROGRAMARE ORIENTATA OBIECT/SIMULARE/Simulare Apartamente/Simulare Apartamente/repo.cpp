#include "repo.h"
#include<fstream>
#include<sstream>
void Repo::load_from_file()
{
	ifstream file(fisier);
	if (!file.is_open())
		throw std::exception("nu se poate deschide fisierul");
	string line;
	while (getline(file, line))
	{
		string strada;
		int suprafata, pret;
		stringstream linestream(line);
		string current_item;
		int item_no = 0;
		while (getline(linestream, current_item, ','))
		{
			if (item_no == 0)suprafata = stoi(current_item);
			if (item_no == 1)strada = current_item;
			if (item_no == 2)pret = stoi(current_item);
			item_no++;
		}
		Apartament p{ suprafata,strada,pret };
		adauga(p);
	}
	file.close();
}

void Repo::write_to_file()
{
	ofstream file(fisier);
	if (!file.is_open())
		throw std::exception("nu se poate scrie in fisierul");
	for (auto& ap : get_all())
		file << ap.get_suprafata() << "," << ap.get_strada() << "," << ap.get_pret() << endl;
	file.close();
}

void Repo::adauga(const Apartament& ap)
{
	apartamente.push_back(ap);
}

void Repo::sterge(const Apartament& ap)
{
	bool ok = true;
	for (const Apartament& a : apartamente)
	{
		if (a.get_suprafata() == ap.get_suprafata() && a.get_pret() == ap.get_pret() && a.get_strada() == ap.get_strada())
			ok = false;
	}
	if (ok)
		throw std::exception("nu exista oferta");
	for (int i = 0; i < apartamente.size(); i++) {
		if (apartamente[i].get_suprafata() == ap.get_suprafata() && apartamente[i].get_pret() == ap.get_pret() && apartamente[i].get_strada() == ap.get_strada())
			apartamente.erase(apartamente.begin() + i);
	}
	write_to_file();
}

string Repo::cauta_strada(string text)
{
	for (int i = 0; i < apartamente.size(); i++)
	{
		string aux = to_string(apartamente[i].get_suprafata()) + "   " + apartamente[i].get_strada() + "   " + to_string(apartamente[i].get_pret());
		if (text == aux)
		{
			return apartamente[i].get_strada();
		}
	}
	return "";
}

int Repo::cauta_pret(string text)
{
	for (int i = 0; i < apartamente.size(); i++)
	{
		string aux = to_string(apartamente[i].get_suprafata()) + "   " + apartamente[i].get_strada() + "   " + to_string(apartamente[i].get_pret());
		if (text == aux)
		{
			return apartamente[i].get_pret();
		}
	}
	return 0;
}

int Repo::cauta_suprafata(string text)
{
	for (int i = 0; i < apartamente.size(); i++)
	{
		string aux = to_string(apartamente[i].get_suprafata()) + "   " + apartamente[i].get_strada() + "   " + to_string(apartamente[i].get_pret());
		if (text == aux)
		{
			return apartamente[i].get_suprafata();
		}
	}
	return 0;
}
