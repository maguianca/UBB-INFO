#include"Repo.h"


int modifica(buget c, buget m, Lista* l)
{
	/*modifica un element de tip buget b cu un element buget c- suprascrie
	:params c-elem buget initial, m-elem c initial dupa modificare, l pointer la un elm de tip Lista
	:returneaza 0 daca s-a putut efectua operatia adica daca s-a gasit elementul de tip buget c,
	altfel returneaza 5*/
	int ok = 5;
	for (int i = 0; i < size(l); i++)
	{
		if (get(i, l).suma == c.suma && get(i, l).zi == c.zi && strcmp(get(i, l).tip, c.tip) == 0)
		{
			ok = 0;
			//cheltuiala(m.suma, m.zi, m.tip)
			set(i, l, cheltuiala(m.suma, m.zi, m.tip));
		}
	}
	distrugere_cheltuiala(&m);
	distrugere_cheltuiala(&c);
	return ok;
}
int sterge(buget c, Lista* l)
{
	/*
	Sterge un element de tip buget din lista si modifica lungimea listei.
	:param c - element de tip buget si l - pointer de tip Lista.
	:returneaza 0 daca s-a gasit elementul c in lista, altfel 5.
	*/
	int ok = 5, parcurs = 0;
	for (int i = 0; i < size(l); i++)
	{
		buget current = get(i, l);
		if (current.suma == c.suma && current.zi == c.zi && strcmp(current.tip, c.tip) == 0)
		{
			ok = 0;
			distrugere_cheltuiala(&l->array[i]);
			for (int j = i; j < size(l) - 1; j++)
			{
				if (j != i)
					distrugere_cheltuiala(&l->array[j]);
				set(j, l, cheltuiala(get(j + 1, l).suma, get(j + 1, l).zi, get(j + 1, l).tip));
				parcurs = 1;
			}
			if (parcurs == 1)
				distrugere_cheltuiala(&l->array[size(l) - 1]);
			break;

		}
	}
	if (ok == 0)
	{
		l->len--;
	}
	distrugere_cheltuiala(&c);
	return ok;
}
int delete(int poz, Lista* l) {
	buget b = get(poz, l);
	for (int i = poz; i < l->len - 1; i++) {
		set(i, l, cheltuiala(get(i + 1, l).suma, get(i + 1, l).zi, get(i + 1, l).tip));
		//l->array[i] = l->array[i + 1];
	}
	l->len--;
	return 0;
}
/*int sterge(buget c, Lista* l)
{
	int ok = 5;
	for (int i = 0; i < size(l); i++)
	{
		if (get(i, l).suma == c.suma && get(i, l).zi == c.zi && strcmp(get(i, l).tip, c.tip) == 0) {
			ok = 0;
			distrugere_cheltuiala(&l->array[i]);
		}
		if (!ok && i <size(l) - 1)
			set(i, l, cheltuiala(get(i+1, l).suma, get(i+1, l).zi, get(i+1, l).tip));
		//if(!ok && i==size(l)-1)
			//set(i-1, l, cheltuiala(get(i, l).suma, get(i, l).zi, get(i, l).tip));
	}
	if (ok == 0)
		l->len--;
	distrugere_cheltuiala(&c);
	return ok;
}*/
void test_repo_adauga()
{
	//test
	Lista l = lista_goala();
	//l.len = 0;
	buget b;
	b = cheltuiala(1000, 3, "mancare");
	adauga(b, &l);
	assert(l.array[0].suma == 1000);
	assert(strcmp(l.array[0].tip, "mancare") == 0);
	assert(l.array[0].zi == 3);
	distrugere(&l);
}
void test_repo_modifica()
{
	//test
	Lista l = lista_goala();;
	buget b, c;
	b = cheltuiala(1000, 3, "mancare");
	adauga(b, &l);

	c = cheltuiala(999, 2, "transport");
	assert(modifica(b, c, &l) == 0);
	assert(l.array[0].suma == 999);
	assert(strcmp(l.array[0].tip, "transport") == 0);

	b = cheltuiala(1000, 3, "mancare");
	c = cheltuiala(999, 2, "transport");
	assert(modifica(b, c, &l) != 0);


	b = cheltuiala(1000, 3, "mancare");
	c = cheltuiala(-100, -9, "traort");
	assert(modifica(b, c, &l) != 0);
	distrugere(&l);
	//distrugere_cheltuiala(&c);
	//distrugere_cheltuiala(&b);
}
void test_repo_sterge()
{
	//test
	Lista l = lista_goala();
	buget b, c;
	b = cheltuiala(1000, 3, "mancare");
	adauga(b, &l);
	c = cheltuiala(999, 2, "transport");
	assert(sterge(c, &l) != 0);
	b = cheltuiala(1000, 3, "mancare");
	assert(sterge(b, &l) == 0);
	assert(size(&l) == 0);
	distrugere(&l);
}
int test_delete() {
	Lista lista = lista_goala();
	assert(size(&lista) == 0);
	buget b = cheltuiala(1000, 3, "mancare");
	adauga(b, &lista);
	//distrugere_cheltuiala(&b);
	buget c = cheltuiala(999, 2, "transport");
	adauga(c, &lista);
	assert(size(&lista) == 2);
	delete(0, &lista);
	assert(size(&lista) == 1);
	//distrugere_cheltuiala(&c);
	//assert(strcmp(l->array[0].tip, "transport") == 0);
	assert(strcmp(get_tip(0, &lista), "transport") == 0);
	assert(get_suma(0, &lista) == 999);
	assert(get_zi(0, &lista) == 2);
	distrugere_cheltuiala(&b);
	distrugere_cheltuiala(&c);
	distrugere(&lista);
	assert(size(&lista) == 0);
}
void test_repo()
{
	//functie de test care apeleaza toate functiile de test din repo
	test_repo_adauga();
	test_repo_modifica();
	test_repo_sterge();
	test_delete();
}
