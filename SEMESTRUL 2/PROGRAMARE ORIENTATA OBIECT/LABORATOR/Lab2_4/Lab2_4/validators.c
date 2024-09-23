#include "validators.h"

int valideaza(buget b)
{
	/*valideaza un element de tip buget dupa cele 3 campuri:suma,tip si zi
	:returneaza 0 daca este valid, 1 daca tipul este invalid,2 daca ziua este invalida sau 3 daca suma
	este negativa
	:param;b element de tip buget */
	if (strcmp(b.tip, "mancare")!=0 && strcmp(b.tip, "transport") != 0
		&& strcmp(b.tip, "telefon&internet") != 0 && strcmp(b.tip, "imbracaminte") != 0 && strcmp(b.tip, "altele") != 0)
		return 1;
	if (b.zi<0 || b.zi>32)
		return 2;
	if (b.suma < 0)
		return 3;
	return 0;
}
int validare_tipul(char tip[21])
{
	/*verfica daca un string poate fi camp intr-un element de tip buget
	:return 0 daca este de tipul respectiv sau 1 altfel
	:params char-tipul*/
	if (strcmp(tip, "mancare") != 0 && strcmp(tip, "transport") != 0
		&& strcmp(tip, "telefon&internet") != 0 && strcmp(tip, "imbracaminte") != 0 && strcmp(tip, "altele") != 0)
		return 1;
	return 0;
}
int valideaza_zi(int zi)
{
	/*verifica daca un element poate fi o zi calendaristica
	:params int zi
	:return 1 daca nr e negativ, 2 daca e pozitiv dar e mai mare ca si 31 sau 0 daca poate fi o data 
	calendaristica*/
	if (zi < 0)
		return 1;
	if (zi > 32)
		return 2;
	return 0;
}
int validare_negativ(int x)
{
	/*verifica daca un numar este negativ
	:params; x-int
	:return 0 daca e pozitiv,altfel 1*/
	if(x<0)
		return 1;
	return 0;
}
void test_tipul()
{
	//test
	assert(validare_tipul("mancare") == 0);
	assert(validare_tipul("transport") == 0);
	assert(validare_tipul("telefon&internet") == 0);
	assert(validare_tipul("imbracaminte") == 0);
	assert(validare_tipul("altele") == 0);
	assert(validare_tipul("ajsfff") == 1);
	assert(validare_tipul("Altele") == 1);
	assert(validare_tipul("ManCare") == 1);
}

void test_negativ()
{
	//test
	assert(validare_negativ(139897) == 0);
	assert(validare_negativ(0) == 0);
	assert(validare_negativ(-990) == 1);
	assert(validare_negativ(-2) == 1);
}
void test_valideaza()
{
	//test
	buget b;
	b.zi = 12;
	strcpy_s(b.tip,20,"mancare");
	b.suma = 123;
	assert(valideaza(b) == 0);
	b.zi = -12;
	assert(valideaza(b) == 2);
	b.zi = 1;
	b.suma = -2;
	assert(valideaza(b) == 3);
	b.suma = 2;
	strcpy_s(b.tip, 20, "mancar");
	assert(valideaza(b) == 1);

}
void test_valideaza_zi()
{
	//test
	assert(valideaza_zi(1) == 0);
	assert(valideaza_zi(-1) == 1);
	assert(valideaza_zi(100) == 2);
	assert(valideaza_zi(0) == 0);
}
void test_validators()
{
	//functie care apeleaza functiile de test din modulul validators
	test_tipul();
	test_negativ();
	test_valideaza();
	test_valideaza_zi();
}