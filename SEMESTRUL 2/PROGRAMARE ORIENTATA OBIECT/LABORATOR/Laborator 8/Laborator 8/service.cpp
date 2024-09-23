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
	Turism o = Turism(denumire, destinatie, tip, pret);
	validator.valideaza_obiect(o);
	repo.cauta(o);
}
vector<Turism> Service::filtrare_destinatie(const string& destinatie)
{
	/*
	return filtrare([destinatie](const Turism& oferta) {
		return oferta.get_destinatie() == destinatie;
		});
		*/	
	const vector<Turism>& oferte = get_all();
	vector<Turism>vectorfiltrat;
	std::copy_if(oferte.begin(), oferte.end(), back_inserter(vectorfiltrat), [destinatie](const Turism& o)
		{
			return o.get_destinatie() == destinatie;
		});
	return(vectorfiltrat);
}
vector<Turism> Service::filtrare_pret(const double pret)
{
	/*
	return filtrare([pret](const Turism& oferta) {
		return oferta.get_pret() <= pret;
		});
		*/
	const vector<Turism>& oferte = get_all();
	vector<Turism>vectorfiltrat;
	std::copy_if(oferte.begin(), oferte.end(), back_inserter(vectorfiltrat), [pret](const Turism& o)
		{
			return o.get_pret() <= pret;
		});
	return(vectorfiltrat);
}
vector<Turism> Service::sortare(Sort functieSortare)
{
	vector<Turism> sortedvector{ repo.get_all() };
	sort(sortedvector.begin(), sortedvector.end(), functieSortare);
	return (sortedvector);
}
std::unordered_map<string, int> Service::raport() {
	std::unordered_map<string, int> map;
	vector<Turism> lista = this->get_all();
	for (const auto& i : lista) {
		if (map.find(i.get_destinatie()) != map.end())
			map[i.get_destinatie()]++;
		else
			map[i.get_destinatie()] = 1;
	}
	return map;
}
void Service::cosAdauga(const string& denumire, const string& destinatie,const string& tip, const double pret) {
	Turism o = Turism(denumire, destinatie, tip, pret);
	const auto& oferta = repo.cauta(o);
	cos.adaugaOfertaCos(oferta);
}

int Service::cosAdaugaRandom(int cate) {
	cos.adaugaOfertaRandomCos(repo.get_all(), cate);
	return (int)cos.getAllCos().size();
}

const vector<Turism>& Service::getAllCos()const {
	return cos.getAllCos();
}

void Service::cosSterge() {
	cos.stergeCos();
}

