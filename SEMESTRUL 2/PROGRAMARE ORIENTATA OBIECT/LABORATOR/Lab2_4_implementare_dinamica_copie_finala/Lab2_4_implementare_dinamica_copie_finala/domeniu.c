#pragma once
#include"domeniu.h"
buget get(int poz, Lista* l) {
	//returneaza un element de tip buget dupa pozitia poz, poz>0
	return l->array[poz];
}
int size(Lista* l) {
	//returneaza lungimea listei l
	return l->len;
}
int get_suma(int poz, Lista* l)
{
	//returneaza suma elementului din lista l de pe pozitia poz ,poz>0
	return l->array[poz].suma;
}
char* get_tip(int poz, Lista* l)
{
	//returneaza tipul elementului din lista l de pe pozitia poz ,poz>0
	return l->array[poz].tip;
}
int get_zi(int poz, Lista* l)
{
	//returneaza ziua elementului din lista l de pe pozitia poz ,poz>0
	return l->array[poz].zi;
}
void set_suma(int poz, Lista* l, int val)
{
	//seteaza suma elementului din lista l de pe pozitia poz ,poz>0 la valoarea val
	l->array[poz].suma = val;
}
void set_zi(int poz, Lista* l, int val)
{
	//seteaza ziua elementului din lista l de pe pozitia poz ,poz>0 la valoarea val
	l->array[poz].zi = val;
}
void set(int poz, Lista* l, buget b)
{
	//suprascrie elementul de pe pozitia poz poz>0 din lista l cu elementul de tip buget b
	l->array[poz] = b;
}
buget cheltuiala(int suma, int zi, char* tip)
{
	//initializeaza campul cheltuaiala cu id,suma,zi,tip
	buget b;
	int nrC = strlen(tip) + 1;
	b.tip = malloc(nrC * sizeof(char));
	b.suma = suma;
	b.zi = zi;
	strcpy_s(b.tip, nrC, tip);
	return b;
}
void adauga(buget c, Lista* l)
{
	/*functie care adauga un element de tip buget c in lista l
	* :params c-elem de tip buget si l-pointer la elem de tip lista
	* incrementeaza lungimea listei
	*/
	if (l->capacitatea <= l->len)
	{
		buget* aux = malloc(sizeof(buget) * (l->capacitatea + 5));
		for (int i = 0; i < l->len; i++)
			aux[i] = l->array[i];
		free(l->array);
		l->array = aux;
		l->capacitatea += 5;
	}
	//set(size(l), l, c);
	l->array[l->len] = c;
	l->len++;
}
Lista lista_goala()
{
	//initializeaza o lista vida si o returneaza 
	Lista l;
	l.capacitatea = 5;
	l.array = malloc(sizeof(buget) * l.capacitatea);
	l.len = 0;
	return l;
}
void distrugere_cheltuiala(buget* b)
{
	free(b->tip);
	//b->suma = NULL;
	//b->zi =NULL;
}
void distrugere(Lista* l)
{
	//distruge o lista l setand lungimea la 0
	for (int i = 0; i < l->len; i++)
	{
		buget b = l->array[i];
		distrugere_cheltuiala(&b);
	}
	l->len = 0;
	free(l->array);
}
/*
void test_domeniu()
{
	buget b = cheltuiala(120, 2, "mancare");
	assert(b.suma == 120);
	assert(b.zi == 2);
	assert(strcmp(b.tip, "mancare") == 0);
	distrugere_cheltuiala(&b);
	Lista lista = lista_goala();
	assert(size(&lista) == 0);
	//Lista list=lista_goala();
	//distrugere(&lista);
	//distrugere(&lista);
	lista = lista_goala();
	adauga(b, &lista);
	assert(get(0, &lista).suma == 120);
	assert(size(&lista) == 1);
	assert(get_suma(0, &lista) == 120);
	//assert(size(&list) == 0);
	b = cheltuiala(120, 2, "mancare");
	adauga(b, &lista);
	assert(size(&lista) == 1);
	//distrugere_cheltuiala(&b);
	distrugere(&lista);
	assert(size(&lista) == 0);
	assert(get_zi(0, &lista) == 2);
	distrugere_cheltuiala(&b);
	//distrugere(&lista);
	//assert(strcmp(get_tip(0, &lista), "mancare") == 0);
	set_suma(0, &lista, 125);
	set_tip(0, &lista, "transport");
	set_zi(0, &lista, 5);
	assert(get_suma(0, &lista) == 125);
	assert(get_zi(0, &lista) == 5);
	assert(strcmp(get_tip(0, &lista), "transport") == 0);
	//distrugere(&lista);
	//distrugere_cheltuiala(&b);
}*/

void test_domeniu()
{
	buget b = cheltuiala(120, 2, "mancare");
	assert(b.suma == 120);
	assert(b.zi == 2);
	assert(strcmp(b.tip, "mancare") == 0);
	distrugere_cheltuiala(&b);

	Lista lista = lista_goala();
	assert(size(&lista) == 0);

	b = cheltuiala(120, 2, "mancare");
	adauga(b, &lista);
	assert(get(0, &lista).suma == 120);
	assert(size(&lista) == 1);
	assert(get_suma(0, &lista) == 120);

	set_suma(0, &lista, 125);

	set_zi(0, &lista, 5);
	assert(get_suma(0, &lista) == 125);
	assert(get_zi(0, &lista) == 5);
	b = cheltuiala(121, 3, "mancare");
	adauga(b, &lista);
	assert(size(&lista) == 2);
	b = cheltuiala(1211, 30, "altele");
	adauga(b, &lista);
	assert(size(&lista) == 3);
	b = cheltuiala(21, 12, "transport");
	adauga(b, &lista);
	assert(size(&lista) == 4);
	b = cheltuiala(89, 20, "altele");
	adauga(b, &lista);
	assert(size(&lista) == 5);
	b = cheltuiala(8, 2, "altele");
	adauga(b, &lista);
	assert(size(&lista) == 6);
	distrugere(&lista);
}