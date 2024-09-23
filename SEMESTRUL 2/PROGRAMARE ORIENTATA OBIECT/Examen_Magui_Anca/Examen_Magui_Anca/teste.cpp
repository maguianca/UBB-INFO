#include "teste.h"

void test()
{
	Repo repo{ "test.txt" };
	Service service{ repo };
	try {
		Repo repo2{ "aaa" };
		assert(false);
	}
	catch (exception) {
		assert(true);
	}
	assert(repo.get_all().size() == 3);
	assert(service.get_all().size() == 3);
	//domeniu
	Utilaj j{ 10,"a","b",2 };
	assert(j.get_id() == 10);
	assert(j.get_denumire() == "a");
	assert(j.get_tip() == "b");
	assert(j.get_cilindri() == 2);
	repo.adauga(j);
	//repo
	assert(repo.get_all().size() == 4);
	try {
		repo.adauga(j);
		assert(false);
	}
	catch (exception) {
		assert(true);
	}
	repo.sterge(10);
	assert(repo.get_all().size() == 3);
	try {
		repo.sterge(10);
		assert(false);

	}
	catch (exception) {
		assert(true);
	}
	repo.adauga(j);
	Utilaj jj{ 10,"aaa","bbb",8 };;
	repo.modifica(jj);
	assert(repo.get_all().size() == 4);
	assert(repo.get_all()[3].get_id() == 10);
	assert(repo.get_all()[3].get_denumire() == "aaa");
	assert(repo.get_all()[3].get_tip() == "bbb");
	assert(repo.get_all()[3].get_cilindri() == 8);
	//service
	service.modifica(10, "uuu", "jjj", 2);
	assert(service.get_all().size() == 4);
	assert(service.get_all()[3].get_denumire() == "uuu");
	assert(service.get_all()[3].get_tip() == "jjj");
	service.sterge(10);
	assert(service.get_all().size() == 3);
	try {
		service.sterge(10);
		assert(false);
	}
	catch (exception) {
		assert(true);
	}
	vector<Utilaj>sort = service.sortare();
	assert(sort[0].get_id() == 1);
	assert(sort[1].get_id() == 3);
	assert(sort[2].get_id() == 2);
	assert(service.nr_cilindri(2) == 0);
	assert(service.nr_cilindri(1) == 2);
	assert(service.nr_cilindri(4) == 1);
	assert(service.tip("sajfkafj") == 0);
	assert(service.tip("aaa") == 1);
}
