#include"teste.h"
#include<assert.h>
#include <vector>
void test_repo_adauga()
{
	Repo repo;
	Turism t("vac1", "tunisia", "sejur", 1000);
	repo.store(t);
	const auto& rezultat = repo.get_all();
	assert(rezultat.size() == 1);
	try {
		repo.store(t); assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
	repo.store({ "a","a","a",1 });
	repo.store({ "b","b","b",1 });
	repo.store({ "c","c","c",1 });
	repo.store({ "d","d","d",1 });
	assert(rezultat.size() == 5);
}
void test_repo_stergere()
{
	Repo repo;
	Turism t("vac1", "tunisia", "sejur", 1000);
	repo.store(t);
	const auto& rezultat = repo.get_all();
	assert(rezultat.size() == 1);
	Turism x = Turism("vac1", "tunisia", "sejur", 1000);
	repo.stergere(x);
	assert(rezultat.size() == 0);
	Turism y = Turism("vac1", "tunisia", "sejur", 1000);
	try {
		repo.stergere(y); assert(false);
	}
	catch (RepoException& ex) {
		assert(true);
		assert(ex.get_mesaj() == "Oferta neexistenta, deci nu se poate sterge\n");
	}
}

void test_repo_cauta()
{
	Repo repo;
	Turism t("vac1", "tunisia", "sejur", 1000);
	repo.store(t);
	const auto& rezultat = repo.get_all();
	assert(rezultat.size() == 1);
	Turism obj("vac1", "tunisia", "sejur", 1000);
	Turism x = repo.cauta(obj);
	assert(x.get_destinatie() == "tunisia");
	assert(x.get_denumire() == "vac1");
	assert(x.get_tip() == "sejur");
	assert(x.get_pret() == 1000);
	try {
		Turism c("ba", "da", "dj", 10);
		repo.cauta(c); assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
}
void test_service_adauga()
{
	Repo repo;
	Validator val;
	CosOferte cos{ repo };
	Service service{ repo ,val,cos };
	service.adauga("1", "Cluj", "sej", 100);
	const auto& rez = service.get_all();
	assert(rez.size() == 1);
}

void test_service_modifica()
{
	Repo repo;
	Validator val;
	CosOferte cos{ repo };
	Service service{ repo ,val , cos };
	service.adauga("1", "Cluj", "vac", 50);
	const auto& rez = service.get_all();
	assert(rez.size() == 1);
	service.modifica("1", "Cluj", "vac", 50, "vacanta", 100);
	Turism ex("1", "Cluj", "vacanta", 100);
	const auto x = repo.cauta(ex);
	assert(x.get_tip() == "vacanta");
	assert(x.get_pret() == 100);
}
/*
void test_repo_modifica()
{
	Repo repo;
	Turism t("vac1", "tunisia", "sejur", 1000);
	repo.store(t);
	const auto& rezultat = repo.get_all();
	assert(rezultat.size() == 1);
	Turism y = Turism("vac1", "tuni", "sejur", 1000);
	try {
		repo.modifica(y); assert(false);
	}
	catch (RepoException& ex) {
		assert(true);
		assert(ex.get_mesaj() == "Nu s-a realizat nicio modificare!\n");
	}
	Turism z = Turism("vac1", "tunisia", "sej", 10);
	repo.modifica(z);
	const auto& rezultat1 = repo.get_all();
	assert(rezultat1[0].get_pret() == 10);
}*/
void test_service_stergere()
{
	Repo repo;
	Validator val;
	CosOferte cos{ repo };
	Service service{ repo ,val,cos };
	service.adauga("1", "Cluj", "sej", 100);
	const auto& rez = service.get_all();
	assert(rez.size() == 1);
	service.stergere("1", "Cluj", "sej", 100);
	assert(repo.get_all().size() == 0);
}
void test_service_cautare()
{
	Repo repo;
	Validator val;
	CosOferte cos{ repo };
	Service service{ repo ,val ,cos };
	service.adauga("1", "Cluj", "sej", 100);
	service.adauga("2", "Cuj", "sej", 100);
	const auto& rez = service.get_all();
	assert(rez.size() == 2);
	service.cautare("1", "Cluj", "sej", 100);
}
void test_service_filtrare_destinatie()
{
	Repo repo;
	Validator val;
	CosOferte cos{ repo };
	Service service{ repo,val,cos };
	service.adauga("1", "Cluj", "sej", 100);
	service.adauga("2", "Cluj", "sej", 120);
	service.adauga("5", "Cluj", "sej", 121);
	service.adauga("6", "Baia Mare", "sej", 122);
	service.adauga("7", "Cluj", "sej", 120);
	service.adauga("8", "Cluj", "sej", 121);
	service.adauga("9", "Cluj", "sej", 122);
	const auto& rez = service.get_all();
	assert(rez.size() == 7);
	vector<Turism> lista_filtrata = service.filtrare_destinatie("Cluj");
	assert(lista_filtrata.size() == 6);
	assert(lista_filtrata[0].get_denumire() == "1");
	assert(lista_filtrata[1].get_denumire() == "2");
	assert(lista_filtrata[2].get_denumire() == "5");
	assert(lista_filtrata[3].get_denumire() == "7");
	assert(lista_filtrata[4].get_denumire() == "8");
	assert(lista_filtrata[5].get_denumire() == "9");
}
void test_service_filtrare_pret()
{
	Repo repo;
	Validator val;
	CosOferte cos{ repo };
	Service service{ repo,val,cos };
	service.adauga("1", "Cluj", "sej", 100);
	service.adauga("2", "Cluj", "sej", 120);
	service.adauga("5", "Cluj", "sej", 121);
	service.adauga("6", "Baia Mare", "sej", 122);
	const auto& rez = service.get_all();
	assert(rez.size() == 4);
	vector<Turism> lista_filtrata = service.filtrare_pret(150);
	assert(lista_filtrata.size() == 4);
	assert(lista_filtrata[0].get_denumire() == "1");
	assert(lista_filtrata[1].get_denumire() == "2");
	assert(lista_filtrata[2].get_denumire() == "5");
	assert(lista_filtrata[3].get_denumire() == "6");
	vector<Turism> lista_filtrata1 = service.filtrare_pret(99);
	assert(lista_filtrata1.size() == 0);
}
void test_service_sortare()
{
	Repo repo;
	Validator val;
	CosOferte cos{ repo };
	Service service{ repo ,val,cos };
	service.adauga("1", "Cluj", "alb", 100);
	service.adauga("2", "Cluj", "negru", 120);
	service.adauga("5", "Oradea", "alb", 121);
	service.adauga("6", "Baia Mare", "bej", 122);
	const auto& rez = service.get_all();
	assert(rez.size() == 4);
	vector<Turism> lista_sortata1 = service.sortare_denumire();
	assert(lista_sortata1.size() == 4);
	assert(lista_sortata1[0].get_denumire() == "1");
	assert(lista_sortata1[1].get_denumire() == "2");
	assert(lista_sortata1[2].get_denumire() == "5");
	assert(lista_sortata1[3].get_denumire() == "6");
	vector<Turism> lista_sortata2 = service.sortare_destinatie();
	assert(lista_sortata2.size() == 4);
	assert(lista_sortata2[0].get_denumire() == "6");
	assert(lista_sortata2[1].get_denumire() == "1");
	assert(lista_sortata2[2].get_denumire() == "2");
	assert(lista_sortata2[3].get_denumire() == "5");
	vector<Turism> lista_sortata3 = service.sortare_tip_pret();
	assert(lista_sortata3.size() == 4);
	assert(lista_sortata3[0].get_denumire() == "1");
	assert(lista_sortata3[1].get_denumire() == "5");
	assert(lista_sortata3[2].get_denumire() == "6");
	assert(lista_sortata3[3].get_denumire() == "2");
}
void test_validator()
{
	Turism o{ "","sff","sff",47 };
	Repo repo;
	Validator val;
	CosOferte cos{ repo };
	try {
		val.valideaza_obiect(o); assert(false);
	}
	catch (ValException& ex)
	{
		assert(ex.get_mesaj() == "Denumirea este incorecta!\n");
		assert(true);
	}
	Turism o1{ "vacanta","2u4785","sej",909 };
	try {
		val.valideaza_obiect(o1); assert(false);
	}
	catch (ValException& ex)
	{
		assert(ex.get_mesaj() == "Destinatia nu poate contine numere!\n");
		assert(true);
	}
	Turism o2{ "vacanta","","sej",909 };
	try {
		val.valideaza_obiect(o2); assert(false);
	}
	catch (ValException& ex)
	{
		assert(ex.get_mesaj() == "Destinatia este incorecta!\n");
		assert(true);
	}
	Turism o3{ "vacanta","ewfsf","",909 };
	try {
		val.valideaza_obiect(o3); assert(false);
	}
	catch (ValException& ex)
	{
		assert(ex.get_mesaj() == "Tipul este incorect!\n");
		assert(true);
	}
	Turism o4{ "vacanta","ewfsf","seds",-24 };
	try {
		val.valideaza_obiect(o4); assert(false);
	}
	catch (ValException& ex)
	{
		assert(ex.get_mesaj() == "Pretul este incorect!\n");
		assert(true);
	}
}
void test_cos()
{
	Repo repo;
	Validator valid;
	CosOferte cos{ repo };
	Service service{ repo, valid, cos };
	service.adauga("1", "Oradea", "sejur", 100);
	service.adauga("2", "Cluj", "sejur", 110);
	service.adauga("3", "Brasov", "sejur", 120);
	service.adauga("4", "Constanta", "sejur", 200);
	service.adauga("5", "Bucuresti", "sejur", 250);
	service.cosAdauga("5", "Bucuresti", "sejur", 250);
	assert(service.getAllCos().size() == 1);
	try {
		service.cosAdauga("1", "Opa", "sej", 10); assert(false);
	}
	catch (RepoException& ex) {
		assert(ex.get_mesaj() == "Nu exista oferta!\n");
		assert(true);
	}
	assert(service.getAllCos().size() == 1);
	service.cosSterge();
	service.cosAdaugaRandom(3);
	assert(service.getAllCos().size() == 3);

	string fisier_csv = "C:\\Programare orientata obiect\\Qt Laborator 10-11\\Qt Laborator 10-11\\oferte.csv";
	string fisier_html = "C:\\Programare orientata obiect\\Qt Laborator 10-11\\Qt Laborator 10-11\\oferte.html";
	string fisier_alt = "C:\\Programare orientata obiect\\Qt Laborator 10-11\\Qt Laborator 10-11\\test1222.txt";
	service.cosExport(fisier_csv);
	service.cosExport(fisier_html);
	try {
		service.cosExport(fisier_alt);
	}
	catch (RepoException exception) {
		assert(exception.get_mesaj() == "Fisierul nu este valid, nu are extensia corespunzatoare!");
		assert(true);
	}
}

void test_raport() {
	Repo repo;
	Validator valid;
	CosOferte cos{ repo };
	Service service{ repo, valid, cos };
	service.adauga("1", "romania", "sejur", 100);
	service.adauga("2", "elvetia", "sejur", 50);
	service.adauga("3", "israel", "pelerinaj", 63);
	service.adauga("4", "romania", "m", 100);
	service.adauga("5", "elvetia", "pelerinaj", 50);

	auto map = service.raport();
	assert(map.size() == 3);
	assert(map["sejur"] == 2);
	assert(map["pelerinaj"] == 2);
	assert(map["m"] == 1);
}
void test_undo() {
	Repo repo;
	Validator valid;
	CosOferte cos{ repo };
	Service service{ repo, valid, cos };
	try {
		service.undo();
	}
	catch (RepoException ex) {
		assert(true);
	}
	service.adauga("unu", "a", "lala", 6789);
	service.adauga("doi", "b", "baab", 1022);
	service.modifica("unu", "a", "lala", 6789, "lolo", 456);
	service.stergere("doi", "b", "baab", 1022);
	service.undo();
	assert(service.get_all().size() == 2);
	Turism o("unu", "a", "lolo", 456);
	Turism o1("doi", "b", "baab", 1022);
	auto oferta = repo.cauta(o);
	service.undo();
	service.undo();
	try {
		repo.cauta(o1);
	}
	catch (RepoException ex) {
		assert(true);
	}
	service.undo();
	assert(service.get_all().empty());
}
void test_fisier()
{
	RepoFile repo{ "C:\\Programare orientata obiect\\Qt Laborator 10-11\\Qt Laborator 10-11\\test.txt" };
	Validator valid;
	CosOferte cos{ repo };
	Service service{ repo, valid, cos };
	assert(service.get_all().size() == 2);
	service.adauga("a", "a", "a", 1);
	assert(service.get_all().size() == 3);
	service.stergere("a", "a", "a", 1);
}
void test_repo_lab()
{

	RepoLab repo;
	repo.set_probabilitatea(1);
	Turism oferta1("Paris", "Europa", "City", 1000);
	repo.store(oferta1);

	auto toate = repo.get_all();
	assert(toate.size() == 1);
	assert(toate[0].get_denumire() == "Paris");
	repo.stergere(oferta1);
	auto toate1 = repo.get_all();
	assert(toate1.size() == 0);
	try {
		repo.cauta(oferta1); assert(false);
	}
	catch (RepoException& ex) {
		//assert(true);
		assert(ex.get_mesaj() == "Oferta nu exista!");
	}
	Turism oferta2("Paris", "Europa", "City", 1000);
	Turism oferta3("Paris1", "Europa1", "City1", 1000);
	Turism oferta4("Paris2", "Europa2", "City2", 1000);
	repo.store(oferta2);
	repo.store(oferta3);
	repo.store(oferta4);
	auto x = repo.cauta(oferta3);
	repo.stergere(oferta2);
	try {
		repo.store(oferta3); assert(false);
	}
	catch (RepoException& ex) {
		//assert(true);
		assert(ex.get_mesaj() == "Ofera deja exista!");
	}
	repo.stergere(oferta4);
	repo.set_probabilitatea(0);
	try {
		repo.store(oferta4); assert(false);
	}
	catch (RepoException& ex) {
		//assert(true);
		assert(ex.get_mesaj() == "Nu se poate executa functia de random!");
	}
}
void teste_teste()
{
	test_validator();
	test_repo_adauga();
	test_repo_stergere();
	test_service_modifica();
	test_service_stergere();
	test_service_adauga();
	test_repo_cauta();
	test_service_cautare();
	test_service_filtrare_pret();
	test_service_filtrare_destinatie();
	test_service_sortare();
	//test_repo_modifica();
	test_cos();
	test_raport();
	test_undo();
	test_fisier();
	test_repo_lab();
}