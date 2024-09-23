#include "teste.h"

void test()
{
	Repo repo{ "test.txt" };
	Validator val{};
	Service service{ repo,val };
	assert(repo.get_all().size() == 3);
	assert(service.get_all().size() == 3);
	//domeniu
	Melodie m{ 1234,"a","b",1 };
	assert(m.get_id() == 1234);
	assert(m.get_titlu() == "a");
	assert(m.get_artist() == "b");
	assert(m.get_rank() == 1);
	Melodie a{ 1234,"a","a",2 };
	m = a;
	assert(m.get_id() == 1234);
	assert(m.get_titlu() == "a");
	assert(m.get_artist() == "a");
	assert(m.get_rank() == 2);
	//repo
	try {
		Repo repo1{ "aaa" };
		assert(false);
	}
	catch (exception) {
		assert(true);
	}
	assert(repo.get_all().size() == 3);
	repo.adauga(m);
	assert(repo.get_all().size() == 4);
	try {
		repo.adauga(m);
	}
	catch (exception) {
		assert(true);
	}
	repo.sterge(1234);
	assert(repo.get_all().size() == 3);
	try {
		repo.sterge(1234);
		assert(false);
	}
	catch (exception) {
		assert(true);
	}
	repo.adauga(m);
	repo.modifica(a);
	assert(repo.get_all()[3].get_rank() == 2);
	repo.sterge(1234);
	//service
	assert(service.get_all().size() == 3);
	repo.adauga(m);
	service.modifica(1234, "x", "x", 1);
	assert(service.get_all()[3].get_artist() == "x");
	try {
		service.modifica(1234, "", "", 1);
		assert(false);
	}
	catch (ValException) {
		assert(true);
	}
	service.sterge(1234);
	assert(service.get_all().size() == 3);
	try {
		service.sterge(1234);
		assert(false);
	}
	catch (exception)
	{
		assert(true);
	}
	assert(service.get_all().size() == 3);
	vector<Melodie>s = service.sorteaza();
	assert(s.size() == 3);
	assert(s[0].get_id() == 6);
	assert(s[1].get_id() == 2);
	assert(s[2].get_id() == 9);
	assert(service.rank(2) == 0);
	assert(service.rank(5) == 1);
	assert(service.rank(4) == 1);
	assert(service.artist("ha") == 2);
	assert(service.artist("") == 0);
}
