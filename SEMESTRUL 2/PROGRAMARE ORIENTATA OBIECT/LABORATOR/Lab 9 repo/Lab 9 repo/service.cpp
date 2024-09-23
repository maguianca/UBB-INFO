#include"service.h"
#include"repo.h"
#include<assert.h>
#include<iostream>
#include<fstream>
#include<sstream>
void Service::adauga(const string& denumire, const string& destinatie, const  string& tip, const double pret)
{
	Turism t(denumire, destinatie, tip, pret);
	validator.valideaza_obiect(t);
	repo.store(t);
	undoActions.push_back(std::make_unique<UndoAdauga>(repo, t));
}
void Service::stergere(const string& denumire, const string& destinatie, const string& tip, const double pret)
{
	Turism t(denumire, destinatie, tip, pret);
	validator.valideaza_obiect(t);
	repo.stergere(t);
	undoActions.push_back(std::make_unique<UndoSterge>(repo, t));
}

void Service::modifica(const string& denumire, const string& destinatie, const string& tip, const double pret, const string& tip_nou, const double pret_nou) {
	/*Turism nou = Turism(denumire, destinatie, tip_nou, pret_nou);
	validator.valideaza_obiect(nou);
	repo.modifica(nou);*/
	Turism o = Turism(denumire, destinatie, tip, pret);
	validator.valideaza_obiect(o);
	Turism c = repo.cauta(o);
	repo.stergere(c);
	Turism nou = Turism(denumire, destinatie, tip_nou, pret_nou);
	validator.valideaza_obiect(nou);
	repo.store(nou);
	undoActions.push_back(std::make_unique<UndoModifica>(repo, c, nou));
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
void Service::cosAdauga(const string& denumire, const string& destinatie, const string& tip, const double pret) {
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
void Service::undo() {
	if (undoActions.empty())
		throw RepoException("nu mai exista operatii pentru Undo");
	undoActions.back()->doUndo();
	undoActions.pop_back();
}
void Service::cosExport(const string& fileName) {
	if (fileName.find(".csv") == std::string::npos && fileName.find(".html") == std::string::npos) {
		//        cout<<"Fisierul nu este valid! Fisierul poate fi doar .CSV sau .HTML"<<endl;
		throw RepoException("Fisierul nu este valid, nu are extensia corespunzatoare!");}
	else {
		std::ofstream fout(fileName);
		if (fileName.find(".html") != std::string::npos) {
			fout << "<html>";
			fout << "<style> table, th, td {border:1px solid black} body{background-color: #C54B6A;} </style>";
			fout << "<body>";
			fout << "<h1> WISHLIST </h1>";
			//fout << "<table><tr><th>Denumire</th> <th>Destinatie</th> <th>Tip</th> <th>tip </th><th>Pret</th></tr>";
			fout << "<table><tr><th>Denumire</th> <th>Destinatie</th> <th>Tip</th> ><th>Pret</th></tr>";
			for (auto& o : getAllCos()) {
				fout << "<tr><td>" << o.get_denumire() << "<td>" << o.get_destinatie() << "</td><td>" << o.get_tip()
					<< "</td><td>" << o.get_pret() << "</td></tr>";
			}
			fout << "</table></body>";
			fout << "<html>";
		}
		else {
			for (auto& o : getAllCos()) {
				fout << o.get_denumire() << ";" << o.get_destinatie() << ";" << o.get_tip()
					<< ";" << o.get_pret() << "\n";
			}
		}
		fout.close();
	}
}

