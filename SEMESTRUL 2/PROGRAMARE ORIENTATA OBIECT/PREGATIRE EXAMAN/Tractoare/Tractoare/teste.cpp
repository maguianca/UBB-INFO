#include"teste.h"
void teste() {
	Repo repo{ "teste.txt" };
	Validator val{ repo };
	Service service{ repo,val };
	assert(repo.get_all().size() == 4);
	Tractor t{ 10,"M1","N1",1 };
	assert(t.get_denumire() == "M1");
	assert(t.get_tip() == "N1");
	assert(t.get_id() == 10);
	assert(t.get_nr() == 1);
	repo.adauga(t);
	Tractor e{ 10,"MM","NN",1 };
	repo.modifica(e);
	assert(repo.get_all().size() == 5);
	assert(repo.get_all().at(4).get_denumire() == "MM");
	repo.sterge(10);
	assert(repo.get_all().size() == 4);
	assert(service.get_all().size() == 4);
	service.adauga(100, "a", "a", 2);
	assert(service.get_all().size() == 5);
	service.modifica(100, "b", "b", 2);
	assert(service.get_all().at(4).get_denumire() == "b");
	repo.sterge(100);
	assert(service.get_all().size() == 4);
	try {
		service.adauga(1, "", "a", 1);
		assert(false);
	}
	catch (ValException& val)
	{
		assert(val.get_mesaj() == "id existent denumire invalida nr roti invalid ");
		assert(true);
	}
	vector<Tractor>s = service.sortare_denumire();
	assert(s[0].get_id() == 1);
	assert(s[1].get_id() == 2);
	assert(s[2].get_id() == 3);
	assert(service.tip("T2") == 3);
	assert(service.tip("T1") == 1);
	vector<Tractor>tr = service.filtrare("T2");
	assert(tr.size() == 3);
	assert(tr[0].get_id() == 1);
	map<string, int>ret_tip = service.returneaza_tip();
	assert(ret_tip["T2"] == 3);
	assert(ret_tip["T1"] == 1);

}