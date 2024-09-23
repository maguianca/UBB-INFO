#include"service.h"
int service_adaugare(int suma, int zi, char* tip,Lista *l)
{
	/*functie de tip int care valideaza datele si apeleaza functia de adaugare din repo
	:returneaza 0 daca s-a efectuat operatia sau rezultatul functiei de validare daca nu s-a
	putut efectua operatia
	:params: suma-int >0, zi-int>0, tip-char si l-pointer de tip Lista*/
	buget b = cheltuiala(suma, zi, tip);
	int rezultat = valideaza(b);
	if (rezultat != 0)
		return rezultat;
	adauga(b, l);
	return 0;
}
int service_modificare(int suma, int zi, char* tip,int m_suma,int m_zi,char*m_tip, Lista*l)
{
	/*functie de tip int care valideaza datele si apeleaza functia de modificare din repo
	:returneaza 0 daca operatia s-a efectuat cu succes sau rezultatul validarii altfel
	:params: suma-int >0,zi-int>0, tip-char, suma,zi,tip componentele unui element de tip buget din Lista l
	         m_suma-int>0, m_zi>0, m_tip-char,componentele unui element de tip buget care ar trb sa inlocuiasca
			 elementul de mai sus
			 l-pointer la un element de tip Lista
	*/
	int rezultat;
	buget b, m;
	b = cheltuiala(suma, zi, tip);
	rezultat = valideaza(b);
	if (rezultat != 0)
		return rezultat;
	m = cheltuiala(m_suma, m_zi, m_tip);
	rezultat = valideaza(m);
	if (rezultat != 0)
		return rezultat;
	return modifica(b, m, l);

}
int service_stergere(int suma, int zi, char* tip, Lista*l)
{
	/*functie int care sterge un element de tip buget din Lista l, valideaza elementul si returneaza 
	rezultatul 0 daca operatie s-a efectuat cu succes sau alta valoare in functie de rezultatul validarii
	:params: suma-int>0 zi-int >0 tip-char, l-pointer de tip Lista
	:return:int 0 sau rezultatul returnat de functia valideaza */
	int rezultat;
	buget b;
	b = cheltuiala(suma, zi, tip);
	rezultat = valideaza(b);
	if (rezultat != 0)
		return rezultat;
	return sterge(b, l);
}
Lista service_filtrare_suma(int suma,Lista *l)
{
	/*functie de tip Lista care adauga intr-o element Lista elemente care corespund filtrarii
	:params: int suma >0 si l-pointer la un element de tip Lista
	:return: element de tip Lista
	*/
	Lista lista_noua = lista_goala();
	//lista_noua.len = 0;
	for (int i = 0; i < size(l); i++)
	{
		if (get_suma(i,l) == suma)
			adauga(get(i,l), &lista_noua);
	}

	return lista_noua;
}
Lista service_filtrare_tip(char* tip,Lista *l)
{
	/*functie de tip Lista care adauga intr-o element Lista elemente care corespund filtrarii
	:params: char tip si l-pointer la un element de tip Lista
	:return: element de tip Lista
	*/
	Lista lista_noua = lista_goala();

	for (int i = 0; i <size(l); i++)
	{
		if(strstr(get(i,l).tip, tip) != NULL)
			adauga(get(i,l), &lista_noua);
	}

	return lista_noua;
}
Lista service_filtrare_zi(int zi,Lista* l)
{
	/*functie de tip Lista care adauga intr-o element Lista elemente care corespund filtrarii
	:params: int zi >0 si l-pointer la un element de tip Lista
	:return: element de tip Lista
	*/
	Lista lista_noua;
	lista_noua.len = 0;
	for (int i = 0; i < size(l); i++)
	{
		if (get_zi(i,l) == zi)
			adauga(get(i,l), &lista_noua);
	}

	return lista_noua;
}
int comparare_tip(buget b1, buget b2, int op)
{
	/*functie care compara doua elemente de tip buget dupa tipul acestora
	:params : b1-elem de tip buget, b2-elem de tip buget si op-int=1 sau 2 reprezinta
	1=pentru ordonare crescatoare dupa tip, respectiv descrescatoare;
	:return:0 daca elementele sunt ordonate dupa optiunea data op altfel 1 daca nu sunt ordonate */
	if (op == 1)
	{
		if (strcmp(b1.tip, b2.tip) < 0)
			return 0;
	}
	else {
		if (op == 2)
			if(strcmp(b1.tip, b2.tip) > 0)
				return 0;
	}
	return 1;
}
int comparare_suma(buget b1, buget b2, int op)
{
	/*functie care compara doua elemente de tip buget dupa suma acestora
	:params : b1-elem de tip buget, b2-elem de tip buget si op-int=1 sau 2 reprezinta
	1=pentru ordonare crescatoare dupa suma, respectiv descrescatoare;
	:return:0 daca elementele sunt ordonate dupa optiunea data op altfel 1 daca nu sunt ordonate */
	if (op == 1) {
		if (b1.suma < b2.suma)
			return 0;
	}
	else
	{
		if (op == 2)
			if(b1.suma > b2.suma)
				return 0;

	}
	return 1;
}
Lista* service_ordonare(int tipul, int ascensiune,Lista* l)
{
	/*functie care ordonareaza Lista curenta l dupa parametrii:tipul si ascensiune
	:params tipul-int reprezinta 1=suma sau 2=tipul
	        ascensiune-int 1=crescator sau 2=descrescator
			l pointer la Lista l
	:returneaza poineter la Lista l sortata corespunzator*/
	if (tipul == 1)
	{
		//suma
		for (int i = 0; i < size(l)-1; i++)
			for (int j = i + 1; j < size(l); j++)
				if (comparare_suma(get(i,l), get(j,l), ascensiune))
				{
					buget aux = get(i,l);
					set(i, l, get(j, l));
					set(j, l, aux);
				}
	}
	else if (tipul == 2)
	{
		for (int i = 0; i <size(l)-1; i++)
			for (int j = i + 1; j < size(l); j++)
				if (comparare_tip(get(i,l), get(j,l), ascensiune))
				{
					buget aux = get(i, l);
					set(i, l, get(j, l));
					set(j, l, aux);
				}
	}
	return l;
}
void test_service_adauga()
{
	//functie de test
	Lista l = lista_goala();
	int erori = service_adaugare(-7, -84, "mancar",&l);
	assert(erori != 0);
	assert(size(&l) == 0);
	erori = service_adaugare(123, 4, "mancare", &l);
	assert(erori== 0);
	assert(size(&l) == 1);
}
void test_service_modifica()
{
	//functie de test
	Lista l = lista_goala();
	int erori;
	erori = service_adaugare(123, 4, "mancare", &l);
	assert(erori == 0);
	assert(size(&l) == 1);
	erori = service_modificare(123, 4, "mancare", 250, 5, "mancare", &l);
	assert(erori == 0);
	assert(size(&l) == 1);
	assert(get(0, &l).suma == 250);
	assert(get(0, &l).zi == 5);
	erori = service_modificare(123, 4, "mancare", 250, 5, "mancare", &l);
	assert(erori == 5);
	erori = service_modificare(-7, 400, "mancare", -0, 5, "mance", &l);
	assert(erori != 0);
	assert(get(0, &l).suma == 250);
	assert(get(0, &l).zi == 5);

}
void test_service_sterge()
{
	//functie de test
	Lista l = lista_goala();
	int erori;
	erori = service_adaugare(123, 4, "mancare", &l);
	assert(erori == 0);
	assert(size(&l) == 1);
	erori = service_adaugare(350, 10, "transport", &l);
	assert(erori == 0);
	assert(size(&l) == 2);
	erori = service_adaugare(35, 11, "transport", &l);
	assert(erori == 0);
	assert(size(&l) == 3);
	erori = service_stergere(200, 4, "altele", &l);
	assert(erori == 5);
	assert(size(&l) == 3);
	erori=service_stergere(123, 4, "mancar", &l);
	assert(erori ==1);
	erori = service_stergere(350, 10, "transport", &l);
	assert(erori == 0);
	assert(size(&l) == 2);

}
void test_service_filtrare_suma()
{
	//functie de test
	Lista l = lista_goala();
	service_adaugare(123, 4, "mancare", &l);
	assert(size(&l) == 1);
	service_adaugare(123, 5, "altele", &l);
	assert(size(&l) == 2);
	service_adaugare(123, 6, "transport", &l);
	assert(size(&l) == 3);
	Lista lista_filtrata = lista_goala();
	lista_filtrata = service_filtrare_suma(123, &l);
	assert(size(&lista_filtrata) == 3);
	lista_filtrata = service_filtrare_suma(12, &l);
	assert(size(&lista_filtrata) == 0);
}
void test_service_filtrare_tip()
{
	//functie de test
	char tip[21]="\0";
	Lista l = lista_goala();
	service_adaugare(13, 4,"mancare", &l);
	assert(size(&l) == 1);
	service_adaugare(190, 4,"mancare", &l);
	assert(size(&l) == 2);
	service_adaugare(3, 5,"altele", &l);
	assert(size(&l) == 3);
	Lista lista_filtrata = lista_goala();
	lista_filtrata = service_filtrare_tip("transport", &l);
	assert(size(&lista_filtrata) == 0);
	strcpy_s(tip, 20, "mancare");
	lista_filtrata = service_filtrare_tip(tip, &l);
	assert(size(&lista_filtrata) == 2);
	lista_filtrata = service_filtrare_tip("altele", &l);
	assert(size(&lista_filtrata) == 1);
}
void test_service_filtrare_zi()
{
	//functie de test
	Lista l = lista_goala();
	service_adaugare(13, 4,"mancare", &l);
	assert(size(&l) == 1);
	service_adaugare(190, 4,"altele", &l);
	assert(size(&l) == 2);
	service_adaugare(3, 5,"transport", &l);
	assert(size(&l) == 3);
	Lista lista_filtrata = lista_goala();
	lista_filtrata = service_filtrare_zi(5, &l);
	assert(size(&lista_filtrata) == 1);
	lista_filtrata = service_filtrare_zi(4, &l);
	assert(size(&lista_filtrata) == 2);
	lista_filtrata = service_filtrare_zi(0, &l);
	assert(size(&lista_filtrata) == 0);
}
void test_comparare_tip()
{
	//functie de test
	buget b1, b2;
	strcpy_s(b1.tip, 20, "mancare");
	strcpy_s(b2.tip, 20, "altele");
	assert(comparare_tip(b1, b2, 1) == 1);
	assert(comparare_tip(b2, b1, 1) == 0);
	assert(comparare_tip(b2, b1, 2) == 1);
	assert(comparare_tip(b1, b2, 2) == 0);
}
void test_comparare_suma()
{
	//functie de test
	buget b1, b2;
	b1.suma = 120;
	b2.suma = 119;
	assert(comparare_suma(b1, b2, 1) == 1);
	assert(comparare_suma(b1, b2, 2) ==0);
}
void test_service_sortare()
{
	//functie de test
	Lista l = lista_goala();
	service_adaugare(13, 4, "mancare", &l);
	assert(size(&l) == 1);
	service_adaugare(190, 4, "transport", &l);
	assert(size(&l) == 2);
	service_adaugare(3, 5, "altele", &l);
	assert(size(&l) == 3);
	Lista* lista_sortata;
	lista_sortata = service_ordonare(1, 1, &l);
	assert(get_suma(0, lista_sortata) == 3);
	assert(get_suma(1, lista_sortata) == 13);
	assert(get_suma(2, lista_sortata) == 190);
	lista_sortata = service_ordonare(2, 2, &l);
	assert(strcmp(get(0, lista_sortata).tip,"transport")==0);
	assert(strcmp(get(1, lista_sortata).tip,"mancare")==0);
	assert(strcmp(get(2, lista_sortata).tip,"altele")==0);
}
void test_service()
{
	//functie care apeleaza toate functiile de test din service

	test_service_adauga();
	test_service_modifica();
	test_service_sterge();
    test_service_filtrare_suma();
	test_service_filtrare_tip();
	test_service_filtrare_zi();
	test_comparare_tip();
	test_comparare_suma();
	test_service_sortare();
}