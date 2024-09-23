#include "repo.h"

void Repo::load_from_file()
{
	ifstream file(fisier);
	if (!file.is_open()) {
		throw exception("nu se poate deschide fisierul");
	}
	string line;
	while (getline(file, line))
	{
		stringstream linestream(line);
		string current_item;
		int item_no = 0;
		string descriere;
		int id;
		string stare;
		vector<string>programatori;
		while (getline(linestream, current_item, ' '))
		{
			if (item_no == 0)id = stoi(current_item);
			if (item_no == 1)descriere = current_item;
			if (item_no == 2) {
				stringstream linestream2(current_item);
				string item;
				while (getline(linestream2, item, ','))
				{
					programatori.push_back(item);
				}
			}
			if (item_no == 3)stare = current_item;
			item_no++;
		}
		Task t{ id,descriere,programatori,stare };
		adauga(t);
	}
	file.close();
}

void Repo::write_to_file()
{
	ofstream file(fisier);
	if (!file.is_open()) {
		throw exception("nu se poate deschide fisierul");
	}
	for (int i = 0; i < taskuri.size(); i++) {
		file << taskuri[i].get_id() << " " << taskuri[i].get_descriere() << " ";
		vector<string>all = taskuri[i].get_programatori();
		for (int j = 0; j < all.size(); j++) {
			file << all[j];
			if (j != all.size() - 1) {
				file << ",";
			}
			else
				file << " ";
		}
		file << taskuri[i].get_stare() << endl;
	}
	file.close();
}

void Repo::adauga(const Task& t)
{
	auto f = find_if(taskuri.begin(), taskuri.end(), [=](const Task& o2) {return t.get_id() == o2.get_id();});
	if (f != taskuri.end()) {
		throw exception("id existent");
	}
	else {
		taskuri.push_back(t);
		write_to_file();
	}
}

void Repo::modificare(const int& id,const string& stare)
{
	for (auto&l : taskuri)
	{
		if (l.get_id() == id)
		{
			l.set_stare(stare);
			write_to_file();
		}
	}
}

void Repo::sterge(const int id)
{
	auto f = find_if(taskuri.begin(), taskuri.end(), [=](const Task& o2) {return id == o2.get_id(); });
	if (f != taskuri.end()) {
		taskuri.erase(f);
		write_to_file();
	}
}
