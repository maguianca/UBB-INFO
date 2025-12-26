#include "domeniu.h"
#include<assert.h>
#include "teste.h"
using namespace std;
void test_domeniu()
{
	Procesor1 p{ "i7",4,"s",2 };
	assert(p.get_nume() == "i7");
	assert(p.get_soclu() == "s");
	assert(p.get_pret() == 2);
	assert(p.get_numar() == 4);
	PlacaDeBaza p1{ "p1","soc",4 };
	assert(p1.get_nume() == "p1");
	assert(p1.get_soclu() == "soc");
	assert(p1.get_pret() == 4);

}
void test()
{
	test_domeniu();
}