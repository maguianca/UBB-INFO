#include"repo.h"
#include<assert.h>
#include<iostream>
#include<fstream>
#include<sstream>
void Repo::store(const Turism& oferta)
{
	if (exist(oferta))
		throw RepoException("Oferta existenta\n");
	vacante.push_back(oferta);
}
void Repo::stergere(const Turism& oferta) {
	bool ok = true;
	for (const Turism& o : vacante) {
		if (o.get_tip() == oferta.get_tip() && o.get_denumire() == oferta.get_denumire() && o.get_destinatie() == oferta.get_destinatie() && o.get_pret() == oferta.get_pret())
			ok = false;
	}
	if (ok)
		throw RepoException("Oferta neexistenta, deci nu se poate sterge\n");
	for (unsigned int i = 0; i < vacante.size(); i++) {
		if (vacante[i].get_destinatie() == oferta.get_destinatie()) {
			vacante.erase(vacante.begin() + i);
		}
	}
}
/*void Repo::modifica(const Turism& o)
{
	bool ok = false;
	for (auto& i : vacante)
		if (i.get_denumire() == o.get_denumire() && i.get_destinatie() == o.get_destinatie())
		{
			i.set_pret(o.get_pret());
			i.set_tip(o.get_tip());
			ok = true;
			break;
		}
	if (!ok)
		throw RepoException("Nu s-a realizat nicio modificare!\n");
}*/
const Turism& Repo::cauta(const Turism& oferta) {
	/*for (auto& o : vacante) {
		if (o.get_denumire() == oferta.get_denumire() && o.get_destinatie() == oferta.get_destinatie() && o.get_tip() == oferta.get_tip() && o.get_pret() == oferta.get_pret()) {
			return o;
		}
	}
	throw RepoException("Nu exista oferta!\n");
	*/
	auto f = std::find_if(this->vacante.begin(), this->vacante.end(), [=](const Turism& o) {
		return (o.get_denumire() == oferta.get_denumire() && o.get_destinatie() == oferta.get_destinatie() && o.get_tip() == oferta.get_tip() && o.get_pret() == oferta.get_pret());
		});
	if (f != this->vacante.end())
		return (*f);
	else
		throw RepoException("Nu exista oferta!\n");}
bool Repo::exist(const Turism& o) {
	try {
		cauta(o);
		return true;
	}
	catch (RepoException&) {
		return false;}
}
void RepoFile::load_from_file() {
	std::ifstream in(fileName);
	if (!in.is_open()) throw RepoException("Eroare la deschiderea fisierului!!!");

	std::string line;
	while (std::getline(in, line)) {
		std::istringstream iss(line);
		std::string denumire, destinatie, tip;
		double pret;

		if (!(iss >> denumire >> destinatie >> tip >> pret)) {throw RepoException("Eroare la citirea din fisier!!!");
		}

		Turism o{ denumire, destinatie, tip, pret };
		Repo::store(o);
	}
	in.close();
}
void RepoFile::write_to_file() {
	std::ofstream out(fileName);
	if (!out.is_open())throw RepoException("Eroare la deschiderea fisierului!!!");

	for (auto& o : Repo::get_all()) {
		out << o.get_denumire() << " ";
		out << o.get_destinatie() << " ";
		out << o.get_tip() << " ";
		out << o.get_pret();
		out << std::endl;
	}
	out.close();
}
