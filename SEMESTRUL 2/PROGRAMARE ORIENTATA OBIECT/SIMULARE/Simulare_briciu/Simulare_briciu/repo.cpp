#include "repo.h"

void Repo::load_from_file()
{
	ifstream file(fisier);
	if (!file.is_open())throw::exception("nu se poate deschide");
	string line;
	while (getline(file, line))
	{
		string destinatie, perioada;
		double pret, avans;
		stringstream linestream(line);
		string current_item;
		int item_no = 0;
		while (getline(linestream, current_item, ','))
		{
			if (item_no == 0)destinatie = current_item;
			if (item_no == 1)perioada = current_item;
			if (item_no == 2)pret = stod(current_item);
			if (item_no == 3)avans = stod(current_item);
			item_no++;
		}
		Rezervare r{ destinatie,perioada,pret,avans };
		adauga(r);
	}
	file.close();
}

void Repo::write_to_file()
{
	ofstream file(fisier);
	if (!file.is_open())throw::exception("nu se poate deschide");
	for (auto& l : oferte)
	{
		file << l.get_destinatie() << "," << l.get_perioada() << "," << l.get_pret() << "," << l.get_avans() << endl;
	}
	file.close();
}

void Repo::adauga(Rezervare& r)
{
	oferte.push_back(r);
	write_to_file();
}

void Repo::stergere(Rezervare& r)
{
	for (int i = 0; i < oferte.size();i++) {
		if (oferte[i] == r)
			oferte.erase(oferte.begin() + i);
	}
	write_to_file();
}

void Repo::discount(double p)
{
	for (auto& l : oferte) {
		l.reducere(p);
	}
}

void Repo::export_to_file(vector<Rezervare>v)
{
	ofstream f(fisier_export);
	if (!f.is_open())throw::exception("nu se poate deschide");
	for (auto& p : v) {
		f << p.get_destinatie() << "," << p.get_perioada() << "," << p.get_pret() << "," << p.get_avans() << endl;
	}
	f.close();
}