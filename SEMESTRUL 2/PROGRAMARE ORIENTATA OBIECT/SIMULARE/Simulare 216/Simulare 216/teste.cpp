#include "teste.h"
#include<assert.h>
void teste()
{
	string fisier = "teste.txt";
	Repo repo{ fisier };
	Service service{ repo };
	assert(service.get_all().size() == 3);
	vector<Elev>x = service.sortare();
	assert(x[0].get_nume() =="Ema");
	assert(x[0].get_matricol() ==1234);
	assert(x[0].get_scoala() =="Cosbuc");
	//assert(x[0].get_atelier() =="informatica|jurnalism");
	assert(x[1].get_nume() == "Ioana");
	assert(x[2].get_nume() == "Matei");

}
