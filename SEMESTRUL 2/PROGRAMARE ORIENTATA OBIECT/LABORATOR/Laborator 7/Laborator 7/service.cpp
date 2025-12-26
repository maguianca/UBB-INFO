#include"service.h"
#include"repo.h"
#include<assert.h>
void Service::adauga(const string& denumire, const string& destinatie, const  string& tip, const double pret)
{
	Turism t(denumire, destinatie, tip, pret);
	validator.valideaza_obiect(t);
	repo.store(t);
}
void Service::stergere(const string& denumire, const string& destinatie, const string& tip, const double pret)
{
	Turism t(denumire, destinatie, tip, pret);
	validator.valideaza_obiect(t);
	repo.stergere(t);
}

void Service::modifica(const string& denumire, const string& destinatie, const string& tip_nou, const double pret_nou) {
	Turism nou = Turism(denumire, destinatie, tip_nou, pret_nou);
	validator.valideaza_obiect(nou);
	repo.modifica(nou);

}
void Service::cautare(const string& denumire, const string& destinatie, const string& tip, const double pret) {
	Turism o =Turism(denumire, destinatie, tip, pret);
	validator.valideaza_obiect(o);
	repo.cauta(o);
}
VectD<Turism> Service::filtrare(const function<bool(const Turism&)>& fct) {
	VectD<Turism> rez;
	VectD<Turism> lista = repo.get_all();
	for (const auto& oferta : lista) {
		if (fct(oferta)) {
			rez.add(oferta);
		}
	}
	return (rez);
}
VectD<Turism> Service::filtrare_destinatie(const string& destinatie)
{
	return filtrare([destinatie](const Turism& oferta) {
		return oferta.get_destinatie() == destinatie;
		});
}
VectD<Turism> Service::filtrare_pret(const double pret)
{
	return filtrare([pret](const Turism& oferta) {
		return oferta.get_pret() <= pret;
		});
}
VectD<Turism> Service::sortare(Sort functieSortare) {
	VectD<Turism> lista_sortata;
	VectD<Turism> lista = repo.get_all();
	for (int i = 0; i < (int)lista.size(); i++) {
		lista_sortata.add(Turism(lista.get(i)));
	}
	bool sorted = false;
	while (!sorted) {
		sorted = true;
		for (int i = 0; i < (int)lista_sortata.size() - 1; i++) {
			if (functieSortare(lista_sortata.get(i), lista_sortata.get(i+1)) > 0) {
				Turism aux = lista_sortata.get(i);
				lista_sortata.get(i) = lista_sortata.get(i+1);
				lista_sortata.get(i+1) = aux;
				sorted = false;
			}
		}
	}
	return lista_sortata;
}
