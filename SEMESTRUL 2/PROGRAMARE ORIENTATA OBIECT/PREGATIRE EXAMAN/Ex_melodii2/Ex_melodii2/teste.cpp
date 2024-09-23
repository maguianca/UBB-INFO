#include "teste.h"

void test()
{
	Repo repo{ "test.txt" };
	Service service{ repo };
	assert(repo.get_all().size() == 3);
	assert(service.get_all().size() == 3);
	Melodie m{ 111,"aa","bb","cc" };
	assert(m.get_id() == 111);
	assert(m.get_titlu() == "aa");
	assert(m.get_artist() == "bb");
	assert(m.get_gen() == "cc");
	repo.adauga(m);
	try {
		repo.adauga(m);
		assert(false);
	}
	catch (exception) {
		assert(true);
	}
	assert(repo.get_all().size() == 4);
	repo.sterge(111);
	assert(repo.get_all().size() == 3);
	try {
		repo.sterge(111);
		assert(false);
	}
	catch (exception) {
		assert(true);
	}
	assert(service.ret_id() == 4);
	service.adauga("a", "b", "c");
	assert(service.get_all().size() == 4);
	assert(service.get_all()[3].get_id() == 4);
	service.adauga("a", "b", "c");
	assert(service.get_all().size() == 5);
	service.sterge(4);
	service.sterge(5);
	assert(service.get_all().size() == 3);
	try {
		service.sterge(5);
		assert(false);
	}
	catch (exception) {
		assert(true);
	}
	vector<Melodie>mel1 = service.sorteaza();
	assert(mel1[0].get_id() == 3);
	assert(mel1[1].get_id() == 1);
	assert(mel1[2].get_id() == 2);
	assert(service.artist("bana") == 1);
	service.adauga("a", "bana", "a");
	assert(service.artist("bana") == 2);
	assert(service.gen("disco") == 2);
	service.sterge(4);
	assert(service.get_all().size() == 3);
}
