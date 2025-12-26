#include "repo.h"

void Repo::load_from_file()
{
	ifstream file(this->fisier);
	if (!file.is_open())throw::exception("nu se poate deschide fisierul");
	string line;
	while (getline(file, line))
	{
		string denumire, marime, disponibilitate;
		int cod, pret;
		stringstream linestream(line);
		string current_item;
		int item_no = 0;
		while (getline(linestream, current_item, ','))
		{
			if (item_no == 0)cod = stoi(current_item);
			if (item_no == 1)denumire=current_item;
			if (item_no == 2)marime=current_item;
			if (item_no == 3)pret=stoi(current_item);
			if (item_no == 4)disponibilitate=current_item;
			item_no++;
		}
		Rochie r{ cod,denumire,marime,pret,disponibilitate };
		adauga(r);
	}
	file.close();
}
void Repo::write_to_file()
{
	ofstream file(this->fisier);
	if (!file.is_open())throw::exception("nu se poate deschide fisierul");
	for (auto& l : rochii) {
		file <<l.get_cod()<<","<<l.get_denumire()<<","<< l.get_marime() << "," << l.get_pret() << "," <<l.get_disponibilitate()<<endl ;
	}
	file.close();
}
void Repo::adauga(const Rochie& r)
{
	if (!cauta(r.get_cod()))
		rochii.push_back(r);
}

int Repo::cauta(int id)
{
	for (int i = 0; i < rochii.size(); i++) {
		if (rochii[i].get_cod() == id)
			return 1;
	}
	return 0;

}

Rochie& Repo::cautare_rochie(int id)
{
	for (int i = 0; i < rochii.size(); i++) {
		if (rochii[i].get_cod() == id)
			return rochii[i];
	}
	throw::exception("nu exista rochie cu id respectiv");
}

void Repo::seteaza(Rochie& r,const string& text)
{
	r.set_disponibilitate(text);
	write_to_file();
}

void Repo::stergere(int id)
{
	auto it = find_if(rochii.begin(), rochii.end(), [id](const Rochie& r) {
		return id == r.get_cod();
		});
	if (it != rochii.end()) {
		rochii.erase(it);
		write_to_file();
	}
	else 
		throw::exception("nu se poate");
	
}

