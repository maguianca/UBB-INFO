#include "teste.h"

void test()
{
	Repo repo{ "teste.txt" };
	Validator val{ repo };
	Service service{ repo,val };
	assert(repo.get_all().size() == 3);
	assert(service.get_all().size() == 3);
	vector<string>l{ "ana", "ioana" };
	Task t{ 100,"apa",l,"close" };
	Task t1{ 122,"apa",l,"close" };
	assert(t.get_id() == 100);
	assert(t.get_descriere() == "apa");
	assert(t.get_programatori_string()=="ana ioana");
	assert(t.get_programatori()==l);
	assert(t.get_stare() == "close");
	repo.adauga(t);
	assert(repo.get_all().size() == 4);
	repo.sterge(100);
	assert(repo.get_all().size() == 3);
	service.adauga(100, "apa", l, "close");
	assert(service.get_all().size() == 4);
	repo.sterge(100);
	assert(service.get_all().size() == 3);
	try {
		repo.adauga(t1);
		assert(false);
	}
	catch (exception& ex)
	{
		assert(true);
	}
	try {
		service.adauga(122, "", l, "closesfhnj");
		assert(false);
	}
	catch (ValException& ex)
	{
		assert(true);
	}

	vector<Task>filt = service.filtrare("Enache Iustin");
	assert(filt.size() == 1);
	assert(filt[0].get_id() == 122);
	vector<Task>sortare = service.sorteaza();
	assert(sortare.size() == 3);
	assert(sortare[0].get_id() == 22);
	assert(sortare[1].get_id() == 122);
	assert(sortare[2].get_id() == 12);
	assert(repo.get_all()[1].get_stare() == "inprogress");
	repo.modificare(122, "close");
	assert(repo.get_all()[1].get_stare() == "close");
	vector<Task>v = service.stare("close");
	assert(v.size() == 2);
	assert(v[1].get_id() == 122);
	repo.modificare(122, "inprogress");
	vector<Task>vii = service.stare("close");
	assert(vii.size() == 1);
	try {
		service.modifica(22, "adhj");
		assert(false);
	}
	catch (ValException& ex) {
		assert(ex.get_mesaj() == "stare invalida");
	}
	service.modifica(22, "open");
	assert(service.get_all()[0].get_stare() == "open");
	vector<Task>v1 = service.stare("open");
	assert(v1.size() == 2);
	//validator
	service.modifica(22, "close");
	try {
		vector<string>li;
		Task ttt{ 122,"",li,"" };
		val.valideaza(ttt);
	}
	catch (ValException& ex)
	{
		assert(ex.get_mesaj() == "id existent\ndescriere invalida\nnr programatori invalid\nstare invalida");
	}
}
