#include"repo.h"
#include<assert.h>
void Repo::store(const Turism& oferta)
{
	for (const Turism& o : vacante) {
		if (o.get_tip() == oferta.get_tip() && o.get_denumire() == oferta.get_denumire() && o.get_destinatie() == oferta.get_destinatie() && o.get_pret() == oferta.get_pret())
			throw RepoException("Oferta existenta\n");
	}
	vacante.push_back(oferta);
}
void Repo::stergere(Turism& oferta) {
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
const Turism& Repo:: cauta(const string& denumire, const string& destinatie,const string&tip,const double pret) const {
	for (const auto& o : vacante) {
		if (o.get_denumire() == denumire && o.get_destinatie() == destinatie && o.get_tip()==tip && o.get_pret()==pret) {
			return o;
		}
	}
	throw RepoException("Nu exista oferta!\n");
}
