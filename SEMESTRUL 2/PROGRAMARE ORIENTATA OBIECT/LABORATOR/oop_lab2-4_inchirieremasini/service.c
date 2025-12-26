#include <stdlib.h>
#include <string.h>
#include "repo.h"
#include "validator.h"
#include "service.h"

Service createService() {

    Service stocare;
    stocare.toate_masinile = creeaza_vid();
    stocare.lista_undo = creeaza_vid();
    return stocare;
}
void distruge_service(Service* stocare)
{
    distruge(stocare->toate_masinile, (DestroyFunction) distruge_masina);
    distruge(stocare->lista_undo, (DestroyFunction) distrugereliste);
}
int adauga(Service* stocare, char* numar, char* categorie, char* model, int inchiriere) {
    //Adauga o masina noua daca este valida
    Masina* masina_noua = creare_masina(numar, categorie, model, inchiriere);
    if (!validate_masina(numar, categorie, model)) {
        distruge_masina(masina_noua);
        return -1;
    }
    int poz = cauta(stocare, numar);
    masina_noua->inchiriata = 0;
    if (poz == -1) {
        adaugareR(stocare->lista_undo, lista_copie(stocare->toate_masinile));
        adaugareR(stocare->toate_masinile, masina_noua);
        return 1;}
    else
    {
        distruge_masina(masina_noua);
        return 0;
    }

}
int cauta(Service* stocare, char* numar)
{
    int poz = -1;
    for (int i = 0; i < stocare->toate_masinile->lungime; i++)
    {
        Masina* m = get(stocare->toate_masinile, i);
        if (strcmp(m->numar, numar) == 0)
        {
            poz = i;
            break;
        }
    }
    return poz;
}

int actualizare(Service* stocare, char* numar, char* categorie_noua, char* model_nou) {
    //Modifica categoria si modelul (daca sunt valide) pentru o masina identificata prin numar de inmatriculare
    if (!validate_masina(numar, categorie_noua, model_nou)) {
        return -1;
    }
    int poz = cauta(stocare, numar);
    if (poz != -1)
    {
        adaugareR(stocare->lista_undo, lista_copie(stocare->toate_masinile));
        Masina* m2 = creare_masina(numar, categorie_noua, model_nou, 0);
        Masina* m = get(stocare->toate_masinile, poz);
        distruge_masina(m);
        set(poz, stocare->toate_masinile, m2);
        return 1;}
    else
        return 0;
}

Repository* vizualizare_categorie(Service* stocare, char* categorie) {
    // Returneaza toate masinile dintr-o anumită categorie
    //Repository* masini2 = (Repository*)malloc(sizeof(Repository));
    Repository* masini2 = creeaza_vid();

    for (int i = 0; i < stocare->toate_masinile->lungime; i++) {
        if (strcmp(get_categorie(stocare->toate_masinile->masini[i]), categorie) == 0) {
            //Masina* x=creare_masina(get_numar(MASINI->masini[i]),get_categorie(MASINI->masini[i]),get_model(MASINI->masini[i]),get_inchiriere(MASINI->masini[i]));
            adaugareR(masini2, creare_masina(get_numar(stocare->toate_masinile->masini[i]), get_categorie(stocare->toate_masinile->masini[i]), get_model(stocare->toate_masinile->masini[i]), get_inchiriere(stocare->toate_masinile->masini[i])));
            //distruge_masina(x);

        }
    }

    return masini2;
}
Repository* vizualizare_disponibilitate(Service* stocare) {
    // Returneaza toate masinile dintr-o anumită categorie
    //Repository* masini2 = (Repository*)malloc(sizeof(Repository));
    Repository* masini2 = creeaza_vid();

    for (int i = 0; i < stocare->toate_masinile->lungime; i++) {
        if (get_inchiriere(stocare->toate_masinile->masini[i]) == 0) {
            //Masina* x=creare_masina(get_numar(MASINI->masini[i]),get_categorie(MASINI->masini[i]),get_model(MASINI->masini[i]),get_inchiriere(MASINI->masini[i]));
            adaugareR(masini2, creare_masina(get_numar(stocare->toate_masinile->masini[i]), get_categorie(stocare->toate_masinile->masini[i]), get_model(stocare->toate_masinile->masini[i]), get_inchiriere(stocare->toate_masinile->masini[i])));
            //distruge_masina(x);

        }
    }

    return masini2;
}

Repository* vizualizare_model(Service* stocare, char* model) {
    // Returneaza toate masinile dintr-un anumit model
    //Repository* masini2 = (Repository*)malloc(sizeof(Repository));
    Repository* masini2 = creeaza_vid();

    for (int i = 0; i < size(stocare->toate_masinile); i++) {
        Elem x = get(stocare->toate_masinile, i);
        if (strcmp(get_model(x), model) == 0) {
            adaugareR(masini2, creare_masina(get_numar(x), get_categorie(x), get_model(x), get_inchiriere(x)));
        }
    }

    return masini2;
}

int comparator_categorie_crescator(const Masina* a, const Masina* b) {
    //Returneaza 1 daca cele 2 masini au categoria in ordine crescatoare, 0 altfel
    return strcmp(a->categorie, b->categorie) > 0;
}

int comparator_categorie_descrescator(const Masina* a, const Masina* b) {
    //Returneaza 1 daca cele 2 masini au categoria in ordine descrescatoare, 0 altfel
    return strcmp(a->categorie, b->categorie) < 0;
}

Repository* sortare(Service* stocare, int (*comparator)(const Masina*, const Masina*)) {
    //Sorteaza masinile in functie de comparator
    Repository* sortat = lista_copie(stocare->toate_masinile);
    int n = stocare->toate_masinile->lungime;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (comparator(sortat->masini[j], sortat->masini[j + 1]))
            {
                Masina* aux = sortat->masini[j];
                sortat->masini[j] = sortat->masini[j + 1];
                sortat->masini[j + 1] = aux;
            }
        }
    }
    return sortat;
}


/*
void sortare_categorie_descrescator(Repository* MASINI) {
    //Sorteaza masinile descrescator dupa categorie
    int n = MASINI->lungime;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(get_categorie(&MASINI->masini[j]), get_categorie(&MASINI->masini[j + 1])) < 0) {
                Masina aux = MASINI->masini[j];
                MASINI->masini[j] = MASINI->masini[j + 1];
                MASINI->masini[j + 1] = aux;
            }
        }
    }
}
*/

int comparator_model_crescator(const Masina* a, const Masina* b) {
    //Returneaza 1 daca cele 2 masini au modelul in ordine crescatoare, 0 altfel
    return strcmp(a->model, b->model) > 0;
}

int comparator_model_descrescator(const Masina* a, const Masina* b) {
    //Returneaza 1 daca cele 2 masini au modelul in ordine descrescatoare, 0 altfel
    return strcmp(a->model, b->model) < 0;
}
/*
void sortare_model_crescator(Repository* MASINI, int (*comparator)(const Masina*, const Masina*)) {
    //Sorteaza masinile crescator dupa model
    int n = MASINI->lungime;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(get_model(&MASINI->masini[j]), get_model(&MASINI->masini[j + 1])) > 0) {
                Masina aux = MASINI->masini[j];
                MASINI->masini[j] = MASINI->masini[j + 1];
                MASINI->masini[j + 1] = aux;
            }
        }
    }
}



void sortare_model_descrescator(Repository* MASINI) {
    //Sorteaza masinile descrescator dupa model
    int n = MASINI->lungime;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(get_model(&MASINI->masini[j]), get_model(&MASINI->masini[j + 1])) < 0) {
                Masina aux = MASINI->masini[j];
                MASINI->masini[j] = MASINI->masini[j + 1];
                MASINI->masini[j + 1] = aux;
            }
        }
    }
}
*/

int inchiriere(Service* stocare, char* numar) {
    //Marcheaza o masina ca fiind inchiriata, in cazul in care aceasta este disponibila
    int inchiriat = -1;
    for (int i = 0; i < stocare->toate_masinile->lungime; i++) {
        if (strcmp(get_numar(stocare->toate_masinile->masini[i]), numar) == 0) {
            if (get_inchiriere(stocare->toate_masinile->masini[i]) == 0) {
                inchiriat = 1;
                adaugareR(stocare->lista_undo, lista_copie(stocare->toate_masinile));
                set_inchiriere(stocare->toate_masinile->masini[i], 1);
            }
            else {
                inchiriat = 0;
            }
        }
    }
    return inchiriat;
}

int returnare(Service* stocare, char* numar) {
    //Marcheaza o masina ca fiind disponibila, in cazul in care aceasta este inchiriata
    int returnat = -1;
    for (int i = 0; i < stocare->toate_masinile->lungime; i++) {
        if (strcmp(get_numar(stocare->toate_masinile->masini[i]), numar) == 0) {
            if (get_inchiriere(stocare->toate_masinile->masini[i]) == 1) {
                returnat = 1;
                adaugareR(stocare->lista_undo, lista_copie(stocare->toate_masinile));
                set_inchiriere(stocare->toate_masinile->masini[i], 0);
            }
            else {
                returnat = 0;
            }
        }
    }
    return returnat;
}
int undo(Service* store) {
    if (size(store->lista_undo) == 0)
        return 0;
    Repository* lista = stergere(store->lista_undo, store->lista_undo->lungime - 1);
    distruge(store->toate_masinile, (DestroyFunction) distruge_masina);
    store->toate_masinile = lista;
    return 1;

}