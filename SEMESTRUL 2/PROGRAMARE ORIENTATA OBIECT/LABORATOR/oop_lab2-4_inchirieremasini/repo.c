#include <stdlib.h>
#include <string.h>
#include "Repo.h"

/*void init(Repository* masini) {
    //Initializeaza lista de masini
    masini->lungime = 0;
}*/

Repository* creeaza_vid() {
    //Initializeaza o lista de masini vida
    Repository* m = (Repository*)(malloc(sizeof(Repository)));
    m->capacitate = 2;
    m->masini = (Elem*)(malloc(sizeof(Elem) * m->capacitate));
    m->lungime = 0;
    return m;
}
Elem get(Repository* masina, int poz)
{
    return masina->masini[poz];
}
Elem set(int poz, Repository* l, Elem masina1) {
    Elem replace = l->masini[poz];
    l->masini[poz] = masina1;
    return replace;
}
Repository* lista_copie(Repository* l)
{
    Repository* rez = creeaza_vid();
    for (int i = 0; i < size(l); i++)
        adaugareR(rez, creare_masina(get_numar(l->masini[i]), get_categorie(l->masini[i]), get_model(l->masini[i]), get_inchiriere(l->masini[i])));
    return rez;
}
void distrugereliste(Repository* masini)
{
    distruge(masini, (DestroyFunction) distruge_masina);
}
void distruge(Repository* masini, DestroyFunction destrF) {
    //Distruge lista de masini
    for (int i = 0; i < size(masini); i++) {
        destrF(masini->masini[i]);
    }
    free(masini->masini);
    free(masini);
}
int size(Repository* MASINI) {
    //returneaza lungimea listei masina
    return MASINI->lungime;
}
void adaugareR(Repository* MASINI, Elem Elem) {
    //Adauga o Elem in lista de masini
    if (MASINI->lungime == MASINI->capacitate) {
        MASINI->capacitate *= 2;

        Masina** masini_noi = (Masina**)(malloc(sizeof(Elem) * MASINI->capacitate));
        for (int i = 0; i < size(MASINI); i++) {
            masini_noi[i] = MASINI->masini[i];
        }
        free(MASINI->masini);
        MASINI->masini = masini_noi;
        //MASINI->masini = masini_noi;
    }
    MASINI->masini[MASINI->lungime++] = Elem;
}
Elem stergere(Repository* lista, int poz)
{
    Elem el = lista->masini[poz];
    for (int i = poz; i < lista->lungime - 1; i++)
        lista->masini[i] = lista->masini[i + 1];
    lista->lungime--;
    return el;
}
void actualizamR(Repository* MASINI, char* numar, char* categorie_noua, char* model_nou) {
    //Actualizeaza o Elem din lista de masini,cu conditia ca numarul de inmatriculare sa fie existent
    for (int i = 0; i < size(MASINI); i++) {
        if (strcmp(get_numar(MASINI->masini[i]), numar) == 0) {
            strcpy(get_categorie(MASINI->masini[i]), categorie_noua);
            strcpy(get_model(MASINI->masini[i]), model_nou);
        }
    }
}