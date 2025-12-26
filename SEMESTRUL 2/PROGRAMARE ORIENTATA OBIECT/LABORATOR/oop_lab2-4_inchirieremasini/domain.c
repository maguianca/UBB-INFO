#include <stdlib.h>
#include <string.h>
#include "Domain.h"

char* get_numar(Masina* masina) {
    //Returneaza numarul masinii
    return masina->numar;
}

char* get_categorie(Masina* masina) {
    //Returneaza categoria masinii
    return masina->categorie;
}

char* get_model(Masina* masina) {
    //Returneaza modelul masinii
    return masina->model;
}
int get_inchiriere(Masina* masina) {
    //Returneaza statusul masinii
    return masina->inchiriata;
}
void set_numar(Masina* masina, char* numar_nou) {
    //Seteaza numarul masinii
    strcpy(masina->numar, numar_nou);
}

void set_categorie(Masina* masina, char* categorie_noua) {
    //Seteaza categoria masinii
    strcpy(masina->categorie, categorie_noua);
}

void set_model(Masina* masina, char* model_nou) {
    //Seteaza modelul masinii
    strcpy(masina->model, model_nou);
}
void set_inchiriere(Masina* masina, int inchiriere)
{
    //Seteaza statusul masinii
    masina->inchiriata = inchiriere;
}
Masina* creare_masina(char* numar, char* categorie, char* model, int inchiriere) {
    //Creeaza o masina
    Masina* masina = (Masina*)malloc(sizeof(Masina));
    //set_numar(&masina, numar);
    //set_categorie(&masina, categorie);
    //set_model(&masina, model);
    int nr =(int) strlen(numar) + 1;
    masina->numar = malloc(nr * sizeof(char));
    strcpy(masina->numar, numar);
    nr = (int)strlen(categorie) + 1;
    masina->categorie = malloc(nr * sizeof(char));
    strcpy(masina->categorie, categorie);
    nr = (int)strlen(model) + 1;
    masina->model = malloc(nr * sizeof(char));
    strcpy(masina->model, model);
    masina->inchiriata = inchiriere;
    return masina;
}

void distruge_masina(Masina* m) {
    //Distruge o masina
    free(m->numar);
    free(m->model);
    free(m->categorie);
    //m->inchiriata = -100;
    free(m);
}