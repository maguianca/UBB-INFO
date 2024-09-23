#include"teste.h"
#include<assert.h>
#include"vector.h"
#include <vector>
void test_repo_adauga()
{
	Repo repo;
	Turism t("vac1", "tunisia", "sejur", 1000);
	repo.store(t);
	const auto& rezultat = repo.get_all();
	assert(rezultat.size() == 1);
	try {
		repo.store(t);assert(false);
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
		repo.stergere(y);assert(false);
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
		repo.cauta(c);assert(false);}
	catch (RepoException&) {
		assert(true);
	}
}
void test_service_adauga()
{
	Repo repo;
	Validator val;
	Service service{ repo ,val};
	service.adauga("1", "Cluj", "sej", 100);
	const auto& rez = service.get_all();
	assert(rez.size() == 1);
}

void test_service_modifica()
{
	Repo repo;
	Validator val;
	Service service{ repo ,val};
	service.adauga("1", "Cluj", "vac", 50);
	const auto& rez = service.get_all();
	assert(rez.size() == 1);
	service.modifica("1", "Cluj", "vacanta", 100);
	Turism ex("1", "Cluj", "vacanta", 100);
	const auto x = repo.cauta(ex);
	assert(x.get_tip() == "vacanta");
	assert(x.get_pret() == 100);
}
void test_repo_modifica()
{
	Repo repo;
	Turism t("vac1", "tunisia", "sejur", 1000);
	repo.store(t);
	const auto& rezultat = repo.get_all();
	assert(rezultat.size() == 1);
	Turism y = Turism("vac1", "tuni", "sejur", 1000);
	try {
		repo.modifica(y);assert(false);
	}
	catch (RepoException& ex) {
		assert(true);
		assert(ex.get_mesaj() == "Nu s-a realizat nicio modificare!\n");
	}
}
void test_service_stergere()
{
	Repo repo;
	Validator val;
	Service service{ repo ,val};
	service.adauga("1", "Cluj", "sej", 100);
	const auto& rez = service.get_all();
	assert(rez.size() == 1);
	service.stergere("1", "Cluj", "sej", 100);
	assert(repo.get_all().size()==0);
}
void test_service_cautare()
{
	Repo repo;
	Validator val;
	Service service{ repo ,val};
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
	Service service{ repo,val };
	service.adauga("1", "Cluj", "sej", 100);
	service.adauga("2", "Cluj", "sej", 120);
	service.adauga("5", "Cluj", "sej", 121);
	service.adauga("6", "Baia Mare", "sej", 122);
	service.adauga("7", "Cluj", "sej", 120);
	service.adauga("8", "Cluj", "sej", 121);
	service.adauga("9", "Cluj", "sej", 122);
	const auto& rez = service.get_all();
	assert(rez.size() == 7);
	VectD<Turism> lista_filtrata = service.filtrare_destinatie("Cluj");
	assert(lista_filtrata.size() == 6);
	assert(lista_filtrata.get(0).get_denumire() == "1");
	assert(lista_filtrata.get(1).get_denumire() == "2");
	assert(lista_filtrata.get(2).get_denumire() == "5");
	assert(lista_filtrata.get(3).get_denumire() == "7");
	assert(lista_filtrata.get(4).get_denumire() == "8");
	assert(lista_filtrata.get(5).get_denumire() == "9");
}
void test_service_filtrare_pret()
{
	Repo repo;
	Validator val;
	Service service{ repo,val };
	service.adauga("1", "Cluj", "sej", 100);
	service.adauga("2", "Cluj", "sej", 120);
	service.adauga("5", "Cluj", "sej", 121);
	service.adauga("6", "Baia Mare", "sej", 122);
	const auto& rez = service.get_all();
	assert(rez.size() == 4);
	VectD<Turism> lista_filtrata = service.filtrare_pret(150);
	assert(lista_filtrata.size() == 4);
	assert(lista_filtrata.get(0).get_denumire() == "1");
	assert(lista_filtrata.get(1).get_denumire() == "2");
	assert(lista_filtrata.get(2).get_denumire() == "5");
	assert(lista_filtrata.get(3).get_denumire() == "6");
	VectD<Turism> lista_filtrata1 = service.filtrare_pret(99);
	assert(lista_filtrata1.size()==0);
}
int sort_denumire1(const Turism& o1, const Turism& o2) {
	return o1.get_denumire() > o2.get_denumire();
}

int sort_destinatie1(const Turism& o1, const Turism& o2) {
	return o1.get_destinatie() > o2.get_destinatie();
}
int sort_tip_pret1(const Turism& o1, const Turism& o2) {
	if (o1.get_tip() == o2.get_tip()) {
		return o1.get_pret() > o2.get_pret();
	}
	return o1.get_tip() > o2.get_tip();
}
void test_service_sortare()
{
	Repo repo;
	Validator val;
	Service service{ repo ,val};
	service.adauga("1", "Cluj", "alb", 100);
	service.adauga("2", "Cluj", "negru", 120);
	service.adauga("5", "Oradea", "alb", 121);
	service.adauga("6", "Baia Mare", "bej", 122);
	const auto& rez = service.get_all();
	assert(rez.size() == 4);
	VectD<Turism> lista_sortata1 = service.sortare(sort_denumire1);
	assert(lista_sortata1.size() == 4);
	assert(lista_sortata1.get(0).get_denumire() == "1");
	assert(lista_sortata1.get(1).get_denumire() == "2");
	assert(lista_sortata1.get(2).get_denumire() == "5");
	assert(lista_sortata1.get(3).get_denumire() == "6");
	VectD<Turism> lista_sortata2 = service.sortare(sort_destinatie1);
	assert(lista_sortata2.size() == 4);
	assert(lista_sortata2.get(0).get_denumire() == "6");
	assert(lista_sortata2.get(1).get_denumire() == "1");
	assert(lista_sortata2.get(2).get_denumire() == "2");
	assert(lista_sortata2.get(3).get_denumire() == "5");
	VectD<Turism> lista_sortata3 = service.sortare(sort_tip_pret1);
	assert(lista_sortata3.size() == 4);
	assert(lista_sortata3.get(0).get_denumire() == "1");
	assert(lista_sortata3.get(1).get_denumire() == "5");
	assert(lista_sortata3.get(2).get_denumire() == "6");
	assert(lista_sortata3.get(3).get_denumire() == "2");
}
void test_validator()
{
	Turism o{ "","sff","sff",47 };
	Repo repo;
	Validator val;
	try {
		val.valideaza_obiect(o);assert(false);
	}
	catch (ValException&ex)
	{
		assert(ex.get_mesaj() == "Denumirea este incorecta!\n");
		assert(true);
	}
	Turism o1{ "vacanta","2u4785","sej",909 };
	try {
		val.valideaza_obiect(o1);assert(false);
	}
	catch (ValException&ex)
	{
		assert(ex.get_mesaj() == "Destinatia nu poate contine numere!\n");
		assert(true);
	}
	Turism o2{ "vacanta","","sej",909 };
	try {
		val.valideaza_obiect(o2);assert(false);
	}
	catch (ValException& ex)
	{
		assert(ex.get_mesaj() == "Destinatia este incorecta!\n");
		assert(true);
	}
	Turism o3{ "vacanta","ewfsf","",909 };
	try {
		val.valideaza_obiect(o3);assert(false);
	}
	catch (ValException& ex)
	{
		assert(ex.get_mesaj() == "Tipul este incorect!\n");
		assert(true);
	}
	Turism o4{ "vacanta","ewfsf","seds",-24 };
	try {
		val.valideaza_obiect(o4);assert(false);
	}
	catch (ValException& ex)
	{
		assert(ex.get_mesaj() == "Pretul este incorect!\n");
		assert(true);
	}
}
/*
///teste vector
template <typename MyVector>
MyVector testCopyIterate(MyVector v) {

	Turism f{ "Ex","Paris","city break",1000};
	v.add(f);
	return v;
}

template <typename MyVector>
void adaugare_oferte(MyVector& v, int nr) {
	for (int i = 0; i < nr; i++) {
		Turism f{ "Excursie" + (char)(i + 1) ,"Paris","sejur" + (char)(i + 1), (double)800+i };
		v.add(f);
	}
}
template <typename MyVector>
void testCreateCopyAssign() {
	MyVector v;//default constructor
	adaugare_oferte(v, 100);
	assert(v.size() == 100);
	assert(v.get(1).get_pret() == 801);

	MyVector v2{ v };//constructor de copiere
	assert(v2.size() == 100);
	assert(v2.get(99).get_pret() == 899);

	MyVector v3;//default constructor
	v3 = v;//operator=   assignment
	assert(v3.size() == 100);
	assert(v3.get(2).get_pret() == 802);

	auto v4 = testCopyIterate(v3);
	assert(v4.size() == 101);
	assert(v4.get(50).get_pret() == 850);
}


  //Test pentru move constructor si move assgnment
template <typename MyVector>
void testMoveConstrAssgnment() {
	std::vector<MyVector> v;
	//adaugam un vector care este o variabila temporara
	//se v-a apela move constructor
	v.push_back(MyVector{});

	//inseram, la fel se apeleaza move costructor de la vectorul nostru
	v.insert(v.begin(), MyVector{});

	assert(v.size() == 2);

	MyVector v2;
	adaugare_oferte(v2, 50);

	v2 = MyVector{};//move assignment

	assert(v2.size() == 0);

}
template <typename MyVector>
void testVector() {
	testCreateCopyAssign<MyVector>();
	testMoveConstrAssgnment<MyVector>();
}
*/
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
	test_repo_modifica();
	//testVector<VectD<Turism>>();
}