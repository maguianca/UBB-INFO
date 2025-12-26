#include"teste.h"
void teste() {
	string file = "test.txt";
	Repo repo{ file };
	Service service{ repo };
	assert(repo.get_all().size() == 3);
	elev e{ 1234,"Tina","Ana",2,9.90 };
	repo.adauga(e);
	assert(service.get_all().size() == 4);
	elev x = repo.get_all()[3];
	assert(x.get_nume() == "Tina");
	assert(x.get_prenume() == "Ana");
	assert(x.get_matricol() == 1234);
	assert(x.get_clasa() == 2);
	assert(x.get_medie() > 9.89);
	vector<elev>s1 = service.sortare_clasa();
	assert(s1[0].get_clasa () == 2);
	vector<elev>s2 = service.sortare_nume();
	assert(s2[0].get_nume() == "Salcedo");
	vector<elev>s3 = service.sortare_medie();
	assert(s3[0].get_nume() == "Sarb");
	assert(service.get_all().size() == 4);
	service.stergere(1234);
	assert(service.get_all().size() == 3);
}