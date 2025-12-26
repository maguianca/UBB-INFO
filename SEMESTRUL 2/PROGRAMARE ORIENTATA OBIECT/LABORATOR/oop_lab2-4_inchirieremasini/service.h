#pragma once
#include <stdlib.h>
typedef struct {
    Repository* toate_masinile;
    Repository* lista_undo;
}Service;
Service createService();
void distruge_service(Service* stocare);
int adauga(Service* stocare, char* numar, char* categorie, char* model, int inchiriere);
int actualizare(Service* stocare, char* numar, char* categorie_noua, char* model_nou);
Repository* vizualizare_categorie(Service* stocare, char* categorie);
Repository* vizualizare_model(Service* stocare, char* model);
int comparator_categorie_crescator(const Masina* a, const Masina* b);
int comparator_categorie_descrescator(const Masina* a, const Masina* b);
int comparator_model_crescator(const Masina* a, const Masina* b);
int comparator_model_descrescator(const Masina* a, const Masina* b);
Repository* sortare(Service* stocare, int (*comparator)(const Masina*, const Masina*));
Repository* vizualizare_disponibilitate(Service* stocare);
/*
void sortare_categorie_descrescator(Repository* MASINI);
void sortare_model_crescator(Repository* MASINI);
void sortare_model_descrescator(Repository* MASINI);
 */
int inchiriere(Service* stocare, char* numar);
int returnare(Service* stocare, char* numar);
int undo(Service* store);
int cauta(Service* stocare, char* numar);