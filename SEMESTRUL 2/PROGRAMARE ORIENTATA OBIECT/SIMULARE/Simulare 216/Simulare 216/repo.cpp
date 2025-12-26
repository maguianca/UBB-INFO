#include "repo.h"

void Repo::load_from_file()
{
	ifstream file(this->fisier);
    if (!file.is_open())
		throw::exception("nu se poate deschide fisierul");
	string line;
	while (getline(file, line))
	{
		string nume, scoala, atelier;
		int numar;
		stringstream linestream(line);
		string current_item;
		int item_no = 0;
		while (getline(linestream, current_item, ','))
		{
			if (item_no == 0)numar = stoi(current_item);
			if (item_no == 1)nume = current_item;
			if (item_no == 2)scoala = current_item;
			if (item_no == 0)atelier= current_item;
			item_no++;
		}
		Elev e{ numar,nume,scoala,atelier };
		adauga(e);
	}
	file.close();
}

