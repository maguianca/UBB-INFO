#pragma once

typedef struct {
    char* numar;
    char* categorie;
    char* model;
    int inchiriata;
} Masina;

char* get_numar(Masina* masina);
char* get_categorie(Masina* masina);
char* get_model(Masina* masina);
int get_inchiriere(Masina* masina);
void set_numar(Masina* masina, char* numar_nou);
void set_categorie(Masina* masina, char* categorie_noua);
void set_model(Masina* masina, char* model_nou);
void set_inchiriere(Masina* masina, int inchiriere);
Masina* creare_masina(char* numar, char* categorie, char* model, int inchiriere);
void distruge_masina(Masina* m);