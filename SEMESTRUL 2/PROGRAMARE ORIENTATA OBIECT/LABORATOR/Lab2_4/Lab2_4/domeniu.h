#pragma once
#include<assert.h>
#include<string.h>

typedef struct {
	int zi;
	int suma;
	char tip[21];
}buget;

typedef struct {
	int len;
	buget array[101];
}Lista;
void adauga(buget c, Lista* l);
Lista lista_goala();
buget get(int poz, Lista* l);
int size(Lista* l);
int get_suma(int poz, Lista* l);
char* get_tip(int poz, Lista* l);
int get_zi(int poz, Lista* l);
void set_suma(int poz, Lista* l, int val);
void set_zi(int poz, Lista* l, int val);
void set_tip(int poz, Lista* l, char* val);
void set(int poz, Lista* l, buget b);
buget cheltuiala( int suma, int zi, char* tip);
void distrugere(Lista* l);
void test_domeniu();