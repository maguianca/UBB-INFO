#include <stdio.h>

#include "service.h"
#include "teste.h"

void testAll() {
    // test domain
    test_creeazaMateriePrima();
    test_destroyMateriePrima();
    test_valideazaMateriePrima();
    // test repository
    test_createEmpty();
    test_add();
    test_addCantitate();
    test_delete();
    test_get();
    test_size();
    //    // test service
    test_adaugaMateriePrima();
    test_stergeMateriePrima();
    test_modificaMateriePrima();
    test_filtruMateriePrima();
    test_sortMateriePrima();
}

// Functia ui de adaugare
void uiAdd(List* v) {
    char nume[30], producator[30];
    int cantitate;
    printf("Nume: ");
    scanf_s("%s", nume);
    printf_s("Producator: ");
    scanf_s("%s", producator);
    printf("Cantitate: ");
    scanf_s("%d", &cantitate);
    int succes = adaugaMateriePrima(v, nume, producator, cantitate);
    if (succes)
        printf("Materie Prima adaugata cu succes!\n");
    else
        printf("Materia Prima nu este valida!\n");
}

// Functia ui de modificare
void uiModify(List* v) {
    char nume[30], nume_nou[30], producator[30], producator_nou[30];
    int cantitate;
    printf("De modificat\n");
    printf("Nume: ");
    scanf_s("%s", nume);
    printf("Producator: ");
    scanf_s("%s", producator);
    printf("Nume nou: ");
    scanf_s("%s", nume_nou);
    printf("Producator nou: ");
    scanf_s("%s", producator_nou);
    printf("Cantitate: ");
    scanf_s("%d", &cantitate);
    int succes = modificaMateriePrima(v, nume, producator, nume_nou, producator_nou, cantitate);
    if (succes)
        printf("Modificarea s-a efectuat cu succes!\n");
    else
        printf("Modificarea nu s-a efectuat! Date invalide!\n");
}

// Functia ui de stergere
void uiDelete(List* v) {
    char nume[30], producator[30];
    printf("Numele Materiei Prime de sters: ");
    scanf_s("%s", nume);
    printf("Numele producatorului de sters: ");
    scanf_s("%s", producator);
    int succes = stergeMateriePrima(v, nume, producator);
    if (succes)
        printf("Materie Prima stearsa cu succes!\n");
    else
        printf("Nu exista Materie Prima de acest fel!\n");
}

// Functia ui de afisare a stocului
void uiStoc(List* v) {
    if (v->length == 0)
        printf("Nu este nimic in stoc!\n");
    else {
        printf("STOC: \n");
        for (int i = 0; i < size(v); i++) {
            MateriePrima m = get(v, i);
            printf("Nume: %s | Producator: %s | Cantitate: %d\n", m.nume, m.producator, m.cantitate);
        }
    }
}

// Functia ui de filtrare
void uiFiltru(List* v) {
    char l;
    int cantitate_max;
    printf("Prima litera: ");
    scanf_s(" %c", &l);
    printf("Cantitatea maxima: ");
    scanf_s("%d", &cantitate_max);
    List listaFiltrata = filtruMateriePrima(v, l, cantitate_max);
    uiStoc(&listaFiltrata);
}

// Functia ui de sortare
void uiSort(List* v) {
    List listaSortata = sortMateriaPrima(v);
    uiStoc(&listaSortata);
}

// meniu
void uiMenu() {
    printf("-- MENIU --\n");
    printf("1. Adaugare Materie Prima (daca exista deja in stoc se actualizeaza cantitatea\n");
    printf("2. Modificare Materie Prima\n");
    printf("3. Stergere Materie Prima\n");
    printf("4. Afisare Stoc\n");
    printf("5. Afisare materii prime ale carui nume incepe cu o litera data de utilizator si au cantitatea mai mica decat cea data de utilizator\n");
    printf("6. Afisare stoc sortat dupa nume si cantitate\n");
    printf("0. Iesire din program.\n");
    printf("--\t--\t--\n");
}

// Functia run
void run() {
    List listaMateriePrima = createEmpty();
    int ok = 1, option;
    while (ok) {
        uiMenu();
        printf("Optiune: ");
        scanf_s("%d", &option);
        switch (option) {
        case 1:
            printf("-- ADAUGARE MATERIE PRIMA -- \n");
            uiAdd(&listaMateriePrima);
            printf("--\t--\t--\n");
            break;
        case 2:
            printf("-- MODIFICARE MATERIE PRIMA --\n");
            uiModify(&listaMateriePrima);
            printf("--\t--\t--\n");
            break;
        case 3:
            printf("-- STERGE MATERIE PRIMA -- \n");
            uiDelete(&listaMateriePrima);
            printf("--\t--\t--\n");
            break;
        case 4:
            uiStoc(&listaMateriePrima);
            printf("--\t--\t--\n");
            break;
        case 5:
            printf("-- FILTRARE STOC MATERIE PRIMA --\n");
            uiFiltru(&listaMateriePrima);
            printf("--\t--\t--\n");
            break;
        case 6:
            printf("-- SORTARE STOC MATERIE PRIMA --\n");
            uiSort(&listaMateriePrima);
            printf("--\t--\t--\n");
            break;
        case 0:
            printf("Iesire din program.\n");
            printf("--\t--\t--\n");
            ok = 0;
            destroy(&listaMateriePrima);
            break;
        default:
            printf("Optiunea nu este valida!\n");
            printf("--\t--\t--\n");
            break;
        }
    }
}

int main() {
    testAll();
    run();
    return 0;
}