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
		string tip, denumire;
		int id, cilindri,item_no=0;
		while (getline(linestream, current_item, ' '))
		{
			if (item_no == 0)id = stoi(current_item);
			if (item_no == 1)denumire = current_item;
			if (item_no == 2)tip = current_item;
			if (item_no == 3)cilindri = stoi(current_item);
			item_no++;
		}
		Utilaj u{ id,denumire,tip,cilindri };
		adauga(u);
	}
	file.close();
}

void Repo::write_to_file()
{
	ofstream file(fisier);
	if (!file.is_open()) { throw exception("nu se poate deschide");
	}
	for (const auto& l : utilaje) {
		file << l.get_id() << " " << l.get_denumire() << " " << l.get_tip() << " " << l.get_cilindri()<< endl;
	}
	file.close();
}

void Repo::adauga(const Utilaj& ob)
{
	auto f = find_if(utilaje.begin(), utilaje.end(), [&](const Utilaj& o) {return o.get_id() == ob.get_id(); });
	if (f != utilaje.end()) {
		throw exception(" exista id");
	}
	utilaje.push_back(ob);
	write_to_file();
}

void Repo::sterge(int id)
{
	auto f = find_if(utilaje.begin(), utilaje.end(), [&](const Utilaj& o) {return o.get_id() == id; });
	if (f == utilaje.end()) {
		throw exception(" nu se poate sterge");
	}
	utilaje.erase(f);
	write_to_file();
}

void Repo::modifica(const Utilaj& ob)
{
	for (auto& l : utilaje) {
		if (l.get_id() == ob.get_id()) {
			l = ob;
			write_to_file();
		}
	}
}
