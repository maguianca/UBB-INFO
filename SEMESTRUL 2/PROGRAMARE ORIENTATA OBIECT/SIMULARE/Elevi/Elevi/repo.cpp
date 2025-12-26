#include "repo.h"

void Repo::load_to_file()
{
	ifstream file(fisier);
	if (!file.is_open())throw::exception("nu se poate deschide fis");
	string line;
	while (getline(file, line))
	{
		int matricol, clasa;
		string nume, prenume;
		float medie;
		stringstream linestream(line);
		string current_item;
		int item_no = 0;
		while (getline(linestream, current_item, ','))
		{
			if (item_no == 0)matricol = stoi(current_item);
			if (item_no == 1)nume = current_item;
			if (item_no == 2)prenume = current_item;
			if (item_no == 3)clasa = stoi(current_item);
			if (item_no == 4)medie = stof(current_item);
			item_no++;
		}
		elev e{ matricol,nume,prenume,clasa,medie };
		adauga(e);
	}
	file.close();
}

void Repo::write_to_file()
{
	ofstream file(fisier);
	if (!file.is_open())throw::exception("nu se poate deschide fis");
	for (auto& l : elevi)
	{
		file << l.get_matricol() << "," << l.get_nume() << "," << l.get_prenume() << "," << l.get_clasa() << "," << l.get_medie()<<endl;
	}
	file.close();
}
void Repo::adauga(elev& x)
{
	elevi.push_back(x);
}

void Repo::stergere(int x)
{
	for (int i=0;i<elevi.size();i++)
	{
		if (x == elevi[i].get_matricol())
			elevi.erase(elevi.begin() + i);
	}
	write_to_file();
}

elev& Repo::cauta(string text)
{
	for (auto& l : elevi) {
		string x = to_string(l.get_matricol()) + "  " + l.get_nume() + "  " + l.get_prenume();
		if (x == text)
			return l;
	}
}
