#include "teste.h"

void teste()
{
	string fisier = "teste.txt";
	Repo repo{ fisier };
	Service service{ repo };
	assert(service.get_all().size() == 3);
	assert(repo.cauta(5) == 0);
	assert(repo.cauta(1) == 1);
	Rochie r{ 1,"rochie cu paiete","s",890,"True"};
	assert(repo.cautare_rochie(1)==r);
	try {
		service.cautare_rochie(1111);
	}
	catch (exception) {
		assert(true);
	}
	vector<Rochie>v = service.sorteaza_marime();
	assert(v[0].get_denumire() == "fusta aurie");
	assert(v[1].get_cod() == 1);
	assert(v[2].get_marime() == "xs");
	assert(v[2].get_pret() == 8900);
	assert(v[2].get_disponibilitate() == "False");
	//v[2].set_disponibilitate("True");
	service.seteaza(v[2], "True");
	assert(v[2].get_disponibilitate() == "True");
	vector<Rochie>v1 = service.sorteaza_pret();
	assert(v1[0].get_pret() == 125);
	assert(v1[1].get_pret() == 890);
	assert(v1[2].get_pret() == 8900);

}
