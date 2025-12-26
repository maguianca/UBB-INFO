#include "repo.h"

void Repo::load_from_file()
{
	ifstream file(this->file);
	if (!file.is_open())throw::exception("nu se poate decshide fisierul");
	string line;
	while (getline(file, line)) {
		string nume, job, status;
		int id;
		stringstream linestream(line);
		string current_item;
		int item_no = 0;
		while (getline(linestream, current_item, ','))
		{
			if (item_no == 0)nume = current_item;
			if (item_no == 1)job = current_item;
			if (item_no == 2)status = current_item;
			if (item_no == 3)id = stoi(current_item);
			item_no++;
		}
		Persoana p{ nume,job,status,id };
		adauga(p);
	}
	file.close();
}

void Repo::write_to_file()
{
	ofstream file(this->file);
	if (!file.is_open())throw::exception("nu se poate scrie in fisier");
	for (auto& l : angajati)
	{
		file << l.get_nume() << "," << l.get_job() << "," << l.get_status() << "," << l.get_id()<<endl;
	}
	file.close();
}

bool Repo::modificare(Persoana& p)
{
	for (auto& l : angajati) {
		if (l == p) {
			l = p;
			write_to_file();
			return true;
		}
	}
	return false;
}

void Repo::adauga(Persoana& p)
{
	angajati.push_back(p);
}

Persoana Repo::cauta(int id)
{
	for (auto& l : angajati) {
		if (l.get_id() == id)
			return l;
	}
	throw::exception("nu exista");
}
