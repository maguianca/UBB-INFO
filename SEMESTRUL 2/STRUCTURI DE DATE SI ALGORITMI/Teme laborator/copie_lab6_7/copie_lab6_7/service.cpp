#include"service.h"
#include"repo.h"
#include<assert.h>
void Service::adauga(const string& denumire, const string& destinatie,const  string& tip,const double pret)
{
	Turism t(denumire, destinatie, tip, pret);
	repo.store(t);
}
void Service::stergere(const string& denumire,const string& destinatie, const string& tip,const double pret)
{
	Turism t = repo.cauta(denumire, destinatie,tip,pret);
	repo.stergere(t);
}

void Service::modifica(const string& denumire, const string& destinatie, const string& tip_nou, const double pret_nou) {
	Turism nou = Turism(denumire, destinatie, tip_nou, pret_nou);
	repo.modifica(nou);

}
void Service::cautare(const string& denumire, const string& destinatie, const string& tip, const double pret) {
	Turism o = repo.cauta(denumire, destinatie,tip,pret);
}
vector<Turism> Service::filtrare(const function<bool(const Turism&)>& fct) {
	vector<Turism> rez;
	for (const auto& oferta : repo.get_all()) {
		if (fct(oferta)) {
			rez.push_back(oferta);
		}
	}
	return (rez);
}
vector<Turism> Service::filtrare_destinatie(const string& destinatie)
{
	return filtrare([destinatie](const Turism& oferta) {
		return oferta.get_destinatie() == destinatie;
		});
}
vector<Turism> Service::filtrare_pret(const double pret)
{
	return filtrare([pret](const Turism& oferta) {
		return oferta.get_pret() <= pret;
		});
}
vector<Turism> Service::sortare(Sort functieSortare) {
	vector<Turism> lista_sortata;
	vector<Turism> lista = repo.get_all();
	for (int i = 0; i < (int)lista.size(); i++) {
		lista_sortata.push_back(Turism(lista[i]));
	}
	bool sorted = false;
	while (!sorted) {
		sorted = true;
		for (int i = 0; i <(int) lista_sortata.size() - 1; i++) {
			if (functieSortare(lista_sortata[i], lista_sortata[i + 1]) > 0) {
				Turism aux = lista_sortata[i];
				lista_sortata[i] = lista_sortata[i + 1];
				lista_sortata[i + 1] = aux;
				sorted = false;
			}
		}
	}
	return lista_sortata;
}