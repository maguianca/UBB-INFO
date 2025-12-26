#pragma once
#include "Domain.h"
typedef void* Elem;
typedef void(*DestroyFunction)(Elem);
typedef struct {
    Elem* masini;
    int lungime;
    int capacitate;
}Repository;

//void init(Repository* masini);
Elem get(Repository* masina, int poz);
void adaugareR(Repository* MASINI, Elem Elem);
void actualizamR(Repository* MASINI, char* numar, char* categorie_noua, char* model_nou);
Repository* lista_copie(Repository* l);
int size(Repository* MASINI);
//void distruge(Repository* masini);
void distruge(Repository* masini, DestroyFunction destrF);
void distrugereliste(Repository* masini);
Elem set(int poz, Repository* l, Elem masina1);
Repository* creeaza_vid();
Elem stergere(Repository* lista, int poz);