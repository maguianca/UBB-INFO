#include "repo.h"

void Repo::load_from_file()
{
	ifstream file(fisier);
	if (!file.is_open()) {
		throw exception("nu se poate");
	}
	string line;
	while (getline(file, line)) {
		stringstream linestream(line);
		string artist, titlu,current_item;
		int rank, id, item_no = 0;
		while (getline(linestream, current_item, ' ')) {
			if (item_no == 0)id = stoi(current_item);
			if (item_no == 1)titlu=current_item;
			if (item_no == 2)artist=current_item;
			if (item_no == 3)rank = stoi(current_item);
			item_no++;
		}
		Melodie m{ id,titlu,artist,rank };
		adauga(m);
	}
	file.close();
}

void Repo::write_to_file()
{
	ofstream file(fisier);
	if (!file.is_open()) {
		throw exception("nu se poate");
	}
	for (const auto& l : melodii) {
		file << l.get_id() << " " << l.get_titlu() << " " << l.get_artist() << " " << l.get_rank() << endl;
	}
	file.close();
}

void Repo::adauga(const Melodie& m)
{
	auto f = find_if(melodii.begin(), melodii.end(), [&](const Melodie& o) {return m.get_id() == o.get_id(); });
	if (f != melodii.end()) {
		throw exception("nu se poate adauga");
	}
	melodii.push_back(m);
	write_to_file();
}

void Repo::sterge(int id)
{
	auto f = find_if(melodii.begin(), melodii.end(), [&](const Melodie& o) {return id == o.get_id(); });
	if (f == melodii.end()) {
		throw exception("nu se poate sterge");
	}
	melodii.erase(f);
	write_to_file();
}

void Repo::modifica(const Melodie& m)
{
	for (auto& l : melodii) {
		if (l.get_id() == m.get_id()) {
			l = m;
			write_to_file();
		}
	}
}

Melodie Repo::cauta(int id)
{
		for (const auto& m : melodii) { // Assuming `melodii` is the container holding all `Melodie` objects
			if (m.get_id() == id) {
				return m;
			}
		}
		throw std::runtime_error("Melodie not found");
}
