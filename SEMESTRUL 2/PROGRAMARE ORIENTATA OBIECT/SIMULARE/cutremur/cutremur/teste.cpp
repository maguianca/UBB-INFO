#include"teste.h"
void test() {
	string fisier = "test.txt";
	Repo repo{ fisier };
	assert(repo.get_all().size() == 3);
	Cutremur c{ "Bistrita","12.03",2,4 };
	repo.adaugare(c);
	assert(repo.get_all().size() == 4);
	Validator val;
	Service service{ repo,val };
	service.adaugare("Cluj", "22.09", 6, 7);
	assert(service.get_all().size() == 5);
	vector<Cutremur>v, m;
	v = service.filtrare("Cluj", 8);
	assert(v.size() == 2);
	m = service.filtrare("Const", 7);
	assert(m.size() == 0);
	try {
		service.adaugare("", "", -10, -10);
	}
	catch (ValException& ex) {
		assert(true);
		//assert(ex.get_mesaj() == "data invalida\nlocatie invalida\nadancime invalida\nintensitate invalida\n");
	}
}
void toate_testele() {
	test();
}