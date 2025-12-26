#include "repo.h"

void Repo::load_from_file()
{
	ifstream file(this->file);
	if (!file.is_open()) throw::exception("nu se poate deschide fisierul");
	string line;
	while (getline(file, line))
	{
		string locatie, data;
		int intensitate, adancime;
		string current_item;
		stringstream linestream(line);
		int item_no = 0;
		while (getline(linestream, current_item, ','))
		{
			if (item_no == 0)locatie = current_item;
			if (item_no == 1)data = current_item;
			if (item_no == 2)intensitate = stoi(current_item);
			if (item_no == 3)adancime = stoi(current_item);
			item_no++;
		}
		Cutremur c{ locatie,data,adancime,intensitate };
		Repo::adaugare(c);
	}
}

void Repo::adaugare(Cutremur& cutremur)
{
	cutremure.push_back(cutremur);
}
