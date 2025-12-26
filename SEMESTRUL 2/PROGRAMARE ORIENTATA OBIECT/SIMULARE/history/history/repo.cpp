#include "repo.h"
void Repo::load_from_file()
{
	ifstream file(fisier);
	if (!file.is_open())throw::exception("nu se poate deschide");
	string line;
	while (getline(file, line))
	{
		string nume,descriere,start,end;
		int id;
		stringstream linestream(line);
		string current_item;
		int item_no = 0;
		while (getline(linestream, current_item, ','))
		{
			if (item_no == 0)id = stoi(current_item);
			if (item_no == 1)nume = current_item;
			if (item_no == 2)descriere = current_item;
			if (item_no == 3)start = current_item;
			if (item_no == 4)end = current_item;
			item_no++;
		}
		Razboi r{ id,nume,descriere,start,end };
		adauga(r);
	}
	file.close();
}

void Repo::write_to_file()
{
	ofstream file(fisier);
	if (!file.is_open())throw::exception("nu se poate deschide");
	for (auto& l : razboaie)
	{
		file << l.get_id() << "," << l.get_nume() << "," << l.get_descriere() << "," << l.get_start()<<"," << l.get_end()<< endl;
	}
	file.close();
}

void Repo::adauga(Razboi& r)
{
	razboaie.push_back(r);
	write_to_file();
}

void Repo::stergere(int id)
{
	auto f = find_if(razboaie.begin(), razboaie.end(), [&](const Razboi& r) {return id == r.get_id(); });
	if (f != razboaie.end()) {
		razboaie.erase(f);
		write_to_file();
	}
}
