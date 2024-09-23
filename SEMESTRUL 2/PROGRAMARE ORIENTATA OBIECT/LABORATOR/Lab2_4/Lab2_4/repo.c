#include"Repo.h"


int modifica(buget c,buget m, Lista* l)
{
	/*modifica un element de tip buget b cu un element buget c- suprascrie
	:params c-elem buget initial, m-elem c initial dupa modificare, l pointer la un elm de tip Lista
	:returneaza 0 daca s-a putut efectua operatia adica daca s-a gasit elementul de tip buget c,
	altfel returneaza 5*/
	int ok = 5;
	for (int i = 0; i < size(l); i++)
	{
		if (get(i,l).suma == c.suma && get(i,l).zi == c.zi && strcmp(get(i,l).tip, c.tip) == 0)
		{
			ok = 0;
			set(i, l, m);
		}
	}
	return ok;
}
int sterge(buget c, Lista* l)
{
	/*sterge un element de tip buget din lista si modifica lungimea listei
	:params c-elem de tip buget si l -pointer de tip Lista
	:returneaza 0 daca s-a gasit elementul c in lista altfel 5
	*/
	int ok = 5;
	for (int i = 0; i <size(l); i++)
	{
		if (get(i,l).suma == c.suma && get(i,l).zi == c.zi && strcmp(get(i,l).tip, c.tip) == 0)
			ok = 0;
		if (!ok && i < size(l) - 1)
			set(i, l, get(i + 1, l));
	}
	if (ok == 0)
		l->len--;
	return ok;
}
void test_repo_adauga()
{
	//test
	Lista l;
	l.len = 0;
	buget b;
	b.suma = 1000;
	strcpy_s(b.tip, 20, "mancare");
	b.zi = 3;
	adauga(b, &l);
	assert(l.array[0].suma == 1000);
	assert(strcmp(l.array[0].tip, "mancare") == 0);
	assert(l.array[0].zi == 3);
}
void test_repo_modifica()
{
	//test
	Lista l;
	l.len = 0;
	buget b,c;
	b.suma = 1000;
	strcpy_s(b.tip, 20, "mancare");
	b.zi = 3;
	adauga(b, &l);

	c.suma = 999;
	c.zi = 2;
	strcpy_s(c.tip, 20, "transport");
	assert(modifica(b,c,&l)==0);
	assert(l.array[0].suma == 999);
	assert(strcmp(l.array[0].tip, "transport") == 0);
	b.suma = 1001;
	assert(modifica(b, c, &l) != 0);
	c.suma = -100;
	c.zi = -9;
	strcpy_s(c.tip, 20, "traort");
	assert(modifica(b, c, &l) != 0);

}
void test_repo_sterge()
{
	//test
	Lista l;
	l.len = 0;
	buget b, c;
	b.suma = 1000;
	strcpy_s(b.tip, 20, "mancare");
	b.zi = 3;
	adauga(b, &l);
	c.suma = 999;
	c.zi = 2;
	strcpy_s(c.tip, 20, "transport");
	assert(sterge(c, &l) != 0);
	assert(sterge(b, &l) == 0);
	assert(size(&l) == 0);

}
void test_repo()
{
	//functie de test care apeleaza toate functiile de test din repo
	test_repo_adauga();
	test_repo_modifica();
	test_repo_sterge();
}