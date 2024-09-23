#include "repo.h"

void Repo::load_from_file()
{
	ifstream file(fisier);
	if (!file.is_open())
		throw::exception("nu se poate deschide fisierul");
	string line;
	while (getline(file, line))
	{
		stringstream linestream(line);
		string current_item;
		int item_no = 0;
		string nume, tip;
		double pret;
		int id;
		while (getline(linestream, current_item, ' '))
		{
			if (item_no == 0)id = stoi(current_item);
			if (item_no == 1)nume = current_item;
			if (item_no == 2)tip = current_item;
			if (item_no == 3)pret =stod( current_item);
			item_no++;
		}
		Produs p{ id,nume,tip,pret };
		adauga(p);
	}
	file.close();
}

void Repo::write_to_file()
{
	ofstream file(fisier);
	if (!file.is_open())
		throw::exception("nu se poate deschide fisierul");
	for (const auto& p : produse)
	{
		file << p.get_id() << " " << p.get_nume() << " " << p.get_tip() << " " << p.get_pret() << endl;
	}
	file.close();
}

void Repo::adauga(const Produs& p)
{
	auto f = find_if(produse.begin(), produse.end(), [&](const Produs& o) {return o.get_id() == p.get_id(); });
	if (f == produse.end())
	{
		produse.push_back(p);
		write_to_file();
	}
	else
		throw::exception("id existent");
}

void Repo::sterge(const Produs& p)
{
	auto f = find_if(produse.begin(), produse.end(), [&](const Produs& o) {return o.get_id() == p.get_id(); });
	if (f != produse.end())
	{
		produse.erase(f);
		write_to_file();
	}
	else
		throw::exception("id nub exista");
}
