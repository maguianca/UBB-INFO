#include "teste.h"
void test() {
	string file = "test.txt";
	Repo repo{ file };
	Service service{ repo };
	assert(repo.get_all().size() == 3);
	Persoana p{ "ema","bucatar","hired",2 };
	assert(repo.modificare(p)==true);
	assert(service.cauta(2) == p);
	vector<Persoana>v = service.get_all();
	assert(v[1].get_nume() == "ema");
	assert(service.modificare( "anca","it","hired",2 ) == true);
	vector<Persoana>x = service.filtrare("anca");
	assert(x.size() == 1);
	assert(x[0].get_job() == "it");
	assert(x[0].get_status() == "hired");
	assert(x[0].get_id() == 2);
	assert(service.modificare("", "", "", 0) == false);
	try {
		service.cauta(5);
	}
	catch(std::exception){
		assert(true);
	}
}