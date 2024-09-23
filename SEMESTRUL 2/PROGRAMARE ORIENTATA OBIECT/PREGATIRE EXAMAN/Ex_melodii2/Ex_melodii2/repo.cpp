#include "repo.h"

void Repo::load_from_file()
{
	ifstream file(fisier);
		if (!file.is_open()) {
			throw exception("nu se poate deschide");
		}
		string line;
		while (getline(file, line)) {
			stringstream linestream(line);
			string current_item;
			string titlu, artist, gen;
			int id, item_no = 0;
			while (getline(linestream, current_item, ' '))
			{
				if (item_no == 0)id = stoi(current_item);
				if (item_no == 1)titlu = current_item;
				if (item_no == 2)artist = current_item;
				if (item_no == 3)gen = current_item;
				item_no++;
			}
			Melodie m{ id,titlu,artist,gen };
			adauga(m);
		}
		file.close();
}

void Repo::write_to_file()
{
	ofstream file(fisier);
	if (!file.is_open()) {
		throw exception("nu se poate deschide");
	}
	for (int i = 0; i < melodii.size(); i++)
	{
		file << melodii[i].get_id() << " " << melodii[i].get_titlu() << " " << melodii[i].get_artist() << " " << melodii[i].get_gen() << endl;
	}
	file.close();
}

void Repo::adauga(const Melodie& m)
{
	auto f = find_if(melodii.begin(), melodii.end(), [&](const Melodie& o) {return m.get_id() == o.get_id(); });
	if (f != melodii.end())
	{
		throw exception("nu se poate adauga");
	}
	melodii.push_back(m);
	write_to_file();
}

void Repo::sterge(const int id)
{
	auto f = find_if(melodii.begin(), melodii.end(), [&](const Melodie& o) {return id == o.get_id(); });
	if (f == melodii.end())
	{
		throw exception("nu se poate sterge");
	}
	melodii.erase(f);
	write_to_file();
}

