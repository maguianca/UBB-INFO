#include "rep.h"

void Repo::load_from_file()
{
	ifstream file(fisier);
	if (!file.is_open())
	{
		throw exception("nu se poate deschide");
		}
	string line;
	while (getline(file, line))
	{
		stringstream linestream(line);
		string current_item;
		int item_no = 0;
		int id, dim;
		string stare,joc,jucator;
		while (getline(linestream, current_item,','))
		{
			if (item_no == 0)id = stoi(current_item);
			if (item_no == 1)dim = stoi(current_item);
			if (item_no == 2)joc = current_item;
			if (item_no == 3)jucator = current_item;
			if (item_no == 4)stare = current_item;
			item_no++;
		}
		Joc j{ id, dim,joc,jucator, stare };
		adauga(j);
	}
	file.close();
}

void Repo::write_to_file()
{
	ofstream file(fisier);
	if (!file.is_open())
	{
		throw exception("nu se poate deschide");
	}
	for (auto& l : jocuri)
	{
		file << l.get_id() << "," << l.get_dim() << "," <<l.get_joc()<<","<<l.get_jucator()<<","<<l.get_stare() << endl;
	}
	file.close();
}

void Repo::adauga(Joc& joc)
{
	auto f = find_if(jocuri.begin(), jocuri.end(), [&](Joc& j) {return joc.get_id() == j.get_id(); });
	if (f != jocuri.end())
	{
		throw exception("id existent");
	}
	else {
		jocuri.push_back(joc);
		write_to_file();
	}
}

void Repo::modifica(Joc& joc)
{
	for (auto& l : jocuri)
	{
		if (l.get_id() == joc.get_id()) {
			l = joc;
			write_to_file();
		}
	}
}

void Repo::mod(int& id, string& joc, string& jucator)
{
	for (auto& l : jocuri)
	{
		if (l.get_id() == id) {
			if (jucator == "O")
				l.set_jucator("X");
			else
				l.set_jucator("O");
			l.set_joc(joc);
			write_to_file();
		}
		
	}
}
