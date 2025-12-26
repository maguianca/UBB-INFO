
#include <stdio.h>
#include "Repo.h"
#include "Service.h"
#include "Domain.h"
#include "teste.h"
#include "validator.h"
void print_menu() {
    //Afiseaza pe ecran meniul pentru utilizator
    printf("\nAlege una dintre optiunile urmatoare: \n");
    printf("-1.Oprire program\n");
    printf(" 0.Afisare toate masinile\n");
    printf(" 1.Adauga masina \n");
    printf(" 2.Actualizare masina\n");
    printf(" 3.Inchiriere/Returnare masina\n");
    printf(" 4.Vizualizare masina dupa criteriu\n");
    printf(" 5.Sortare masina dupa criteriu\n");
    printf(" 6.Undo\n");
}

void afisare(Repository* MASINI) {
    //Afiseaza toate masinile din lista de masini
    for (int i = 0; i < MASINI->lungime; i++)
    {
        printf("Numar inmatriculare: %s\n", get_numar(MASINI->masini[i]));
        printf("Categorie: %s\n", get_categorie(MASINI->masini[i]));
        printf("Model: %s\n", get_model(MASINI->masini[i]));
        if (get_inchiriere(MASINI->masini[i]) == 1) {
            printf("Stare: Inchiriata\n");
        }
        else {
            printf("Stare: Disponibila\n");
        }
    }
}
/*
void afisare_masini(Repository MASINI) {

    for (int i = 0; i < MASINI.lungime; i++)
    {
        printf("Numar inmatriculare: %s\n", get_numar(&MASINI.masini[i]));
        printf("Categorie: %s\n", get_categorie(&MASINI.masini[i]));
        printf("Model: %s\n", get_model(&MASINI.masini[i]));
        if (MASINI.masini[i].inchiriata == 1) {
            printf("Stare: Inchiriata\n");
        } else {
            printf("Stare: Disponibila\n");
        }
    }
}
*/


int main() {

    //Repository* MASINI;
    //MASINI = creeaza_vid();
    ruleaza_toate_testele();
    Service store = createService();
    int optiune;
    int continua = 1;
    while (continua) {
        print_menu();
        printf("Introduceti optiunea: ");
        scanf("%d", &optiune);

        switch (optiune) {
            case 0: {
                afisare(store.toate_masinile);
                break;
            }
            case 1: {
                char numar[20], categorie[20], model[20];
                printf("Introduceti numar inmatriculare: ");
                scanf("%s", numar);

                printf("Introduceti categorie: ");
                scanf("%s", categorie);

                printf("Introduceti model: ");
                scanf("%s", model);
                int ok;
                ok = adauga(&store, numar, categorie, model, 0);
                if (ok == -1)
                    printf("Datele introduse pentru masina sunt invalide. Va rugam introduceti date valide.\n");
                else if (ok == 1) printf("Masina a fost adaugata cu succes!\n");
                else if (ok == 0)printf("id existent\n");
                break;
            }
            case 2: {
                char numar[20];
                printf("Introduceti numarul de inmatriculare: ");
                scanf("%s", numar);
                char categorie_noua[20], model_nou[20];
                printf("Introdu noua categorie: ");
                scanf("%s", categorie_noua);

                printf("Introdu noul model: ");
                scanf("%s", model_nou);
                int ok;

                ok = actualizare(&store, numar, categorie_noua, model_nou);
                if (ok == -1)
                    printf("Datele introduse pentru masina sunt invalide. Va rugam introduceti date valide.\n");
                else if (ok == 1) printf("Masina a fost actualizata cu succes!");

                break;

            }
            case 3: {
                printf("1. Inchiriere masina\n2.Returnare masina");
                int opt = 0;
                scanf("%d", &opt);
                if (opt == 1) {
                    printf("Introdu numarul de inmatriculare: ");
                    char numar[20];
                    int inchiriat;
                    scanf("%s", numar);
                    inchiriat = inchiriere(&store, numar);
                    if (inchiriat == 1) printf("Masina a fost inchiriata! ");
                    else if (inchiriat == 0) printf("Masina este deja inchiriata! ");
                    else if (inchiriat == -1) printf("Masina cu acest numar de inmatriculare nu exista! ");
                } else if (opt == 2) {
                    printf("Introdu numarul de inmatriculare: ");
                    char numar[20];
                    int returnat;
                    scanf("%s", numar);
                    returnat = returnare(&store, numar);
                    if (returnat == 1) printf("Masina a fost returnata! ");
                    else if (returnat == 0) printf("Masina nu este inchiriata! ");
                    else if (returnat == -1) printf("Masina cu acest numar de inmatriculare nu exista! ");
                } else printf("Optiune invalida!");
                break;
            }
            case 4: {
                printf("1. Dupa categorie \n2. Dupa model \n3. Dupa disponibilitate\nIntrodu optiunea ta: ");
                int opt = 0;
                scanf("%d", &opt);
                if (opt == 1) {
                    printf("Introdu categoria: ");
                    char categorie[20];
                    scanf("%s", categorie);
                    Repository *filtrat = vizualizare_categorie(&store, categorie);
                    afisare(filtrat);
                    distruge(filtrat, distruge_masina);
                } else if (opt == 2) {
                    printf("Introdu modelul: ");
                    char model[20];
                    scanf("%s", model);
                    Repository *filtrat = vizualizare_model(&store, model);
                    afisare(filtrat);
                    distruge(filtrat, distruge_masina);
                    //distruge(vizualizare_model(MASINI, model));
                } else if (opt == 3) {
                    Repository *filtrat = vizualizare_disponibilitate(&store);
                    afisare(filtrat);
                    distruge(filtrat, distruge_masina);
                } else
                    printf("Optiune invalida! ");
                break;
            }
            case 5: {
                printf("1. Dupa categorie \n2. Dupa model \nIntrodu optiunea ta: ");
                int opt = 0;
                scanf("%d", &opt);
                if (opt == 1) {
                    printf("1. Crescator\n2.Descrescator\nIntrodu optiunea ta: ");
                    int opt2 = 0;
                    scanf("%d", &opt2);
                    if (opt2 == 1) {
                        Repository *sort = sortare(&store, comparator_categorie_crescator);
                        afisare(sort);
                        distruge(sort, distruge_masina);
                    } else if (opt2 == 2) {
                        Repository *sort = sortare(&store, comparator_categorie_descrescator);
                        afisare(sort);
                        distruge(sort, distruge_masina);
                    } else printf("Optiune invalida! ");
                } else if (opt == 2) {
                    printf("1. Crescator\n2.Descrescator\nIntrodu optiunea ta: ");
                    int opt2 = 0;
                    scanf("%d", &opt2);
                    if (opt2 == 1) {
                        Repository *sort = sortare(&store, comparator_model_crescator);
                        afisare(sort);
                        distruge(sort, distruge_masina);
                    } else if (opt2 == 2) {
                        Repository *sort = sortare(&store, comparator_model_descrescator);
                        afisare(sort);
                        distruge(sort, distruge_masina);
                    } else printf("Optiune invalida! ");
                } else printf("Optiune invalida! ");
                break;
            }
            case -1: {
                continua = 0;
                distruge_service(&store);
                break;
            }
            case 6: {
                int succ = undo(&store);
                if (succ)
                    printf("undo realizat cu succes.\n");
                else
                    printf("Nu se mai poate face undo.\n");
                break;
            }
            default:
                break;
        }
    }
}